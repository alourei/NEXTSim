//
// $Id: nDetPrimaryGeneratorAction.cc, v1.0 Sept., 2015  $
// Written by Dr. Xiaodong Zhang 
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include <G4Geantino.hh>
#include "nDetPrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4Alpha.hh"
#include "G4Electron.hh"
#include "G4Gamma.hh"
#include "G4Neutron.hh"
#include "G4Triton.hh"
#include "G4Deuteron.hh"
#include "Randomize.hh"
#include "G4GeneralParticleSource.hh"
#include "nDetAnalysisManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nDetPrimaryGeneratorAction::nDetPrimaryGeneratorAction(nDetRunAction* run)
: runAct(run)
{
  G4int n_particle = 1;
  particleGun = new G4ParticleGun(n_particle);
  //particleGun = new G4GeneralParticleSource();
  //default kinematic
  //
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();

  //G4ParticleDefinition* particle = G4Neutron::NeutronDefinition();
  //G4ParticleDefinition* particle = G4Alpha::AlphaDefinition();
  //G4ParticleDefinition* particle = G4Gamma::GammaDefinition();
  //G4ParticleDefinition* particle = G4Electron::ElectronDefinition();

    G4ParticleDefinition *particle =G4Geantino::GeantinoDefinition();
    SetNeutronDecayData("85As.dat");

  particleGun->SetParticleDefinition(particle);

  /*
  particleGun->SetParticleMomentumDirection(G4ThreeVector(0, -1., 0)); // along the y-axis direction
 // particleGun->SetParticleEnergy(10*MeV);
  //changed to 1 MeV KS 5/20/16
  particleGun->SetParticleEnergy(662.*keV);
  */
   }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nDetPrimaryGeneratorAction::~nDetPrimaryGeneratorAction()
{
    delete particleGun;
    delete [] DaughterExEng;
    delete [] IntensityRaw;
    delete [] ProbRaw;
    delete [] ProbLimit;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nDetPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{

//  this code is used to shoot one quater of the small unit of the structure
//  G4double x = G4UniformRand()*0.00075; 
//  G4double y = G4UniformRand()*0.00075; //

// one unit of the small structure
  //G4double x = 0*mm; //(G4UniformRand()-5/6.0)*0.0015;
  // changing the neutron incident position to study the position performance
  //  G4double y = 100*mm;
  //  G4double z = 0*mm; // center of one pixel

//  x=-2*mm;
//  y=0;
//  z=0;

    G4ThreeVector direction(0,0,0);

    G4double Pi=4*atan(1.0);

    G4double theta = atan(12.5/100)*rad;
    G4double phi0 = -atan(.3/100)*radian;
    G4double phi = atan(.3/100)*radian;

    GenerateIsotropicDirectionDistribution(&direction,Pi/2-theta,Pi/2+theta,phi0,phi);

    particleGun->SetParticleMomentumDirection(direction);

    particleGun->SetParticleEnergy(GetNeutronEng()*keV);

    particleGun->GeneratePrimaryVertex(anEvent);

    G4ThreeVector VertexPosition= particleGun->GetParticlePosition();

    nDetAnalysisManager *theManager=(nDetAnalysisManager*)nDetAnalysisManager::Instance();

    theManager->GeneratePrimaries(anEvent);

  runAct->setNeutronIncidentPositionX(VertexPosition.x());
  runAct->setNeutronIncidentPositionY(VertexPosition.y());
  runAct->setNeutronIncidentPositionZ(VertexPosition.z());

}


void nDetPrimaryGeneratorAction::SetNeutronDecayData(G4String theFileName){

    G4cout<<"Getting Energies for neutrons"<<G4endl;


    std::fstream theFile;
    theFile.open(theFileName, std::fstream::in );
    theFile >> NumberOfLines;

    DaughterExEng = new G4double[NumberOfLines];
    IntensityRaw = new G4double[NumberOfLines];
    ProbRaw = new G4double[NumberOfLines];
    ProbLimit = new G4double[NumberOfLines];
    Normalization = 0.;

    if(theFile.good())
    {
        G4cout << "Loading Data For FileName = " << theFileName << G4endl;
        for(G4int i=0; i<NumberOfLines; i++)
        {
            G4double theEnergy = 0.;    // Nucleus (23Mg) excitation eng.
            G4double theIntensity = 0.;  // absolute (not in percent)

            theFile >> theEnergy >> theIntensity;

            G4cout << theEnergy << "  " << theIntensity << G4endl;

            DaughterExEng[i] = theEnergy;
            IntensityRaw[i] = theIntensity;
            Normalization += theIntensity;
        }
        G4cout << "Successfully Loaded !  Normalization = " << Normalization << G4endl;
        theFile.close();

        for(G4int i=0; i<NumberOfLines; i++)
        {
            ProbRaw[i] = IntensityRaw[i]/Normalization;
        }
    }

    else
    {
        G4cerr << "File = " << theFileName << " not found or in improper format." << G4endl;
        G4ExceptionDescription description;
        description<< "File not found!!";
        G4Exception("nDetPrimaryGeneratorAction::SetNeutronDecayData()","DecayData_002",FatalException,description);
    }

    // Setup Limits and Distances

    for(G4int i=0; i<NumberOfLines; i++)
    {
        if(i == 0)
        {ProbLimit[i] = ProbRaw[i];}
        else
        {ProbLimit[i] = ProbLimit[i-1]+ProbRaw[i];}
    }

}




G4double nDetPrimaryGeneratorAction::GetNeutronEng(){

    G4double RecRandnum = G4UniformRand();
    // Search for Prob Interval ----

    //G4cout<<"RANDOM "<<RecRandnum<<G4endl;

    G4int ProbInt = 0;

    for(G4int k=0; k<NumberOfLines; k++)
    {
        if(k == 0 && RecRandnum < ProbLimit[k] && ProbRaw[k] > 0.)
        { ProbInt = k; }
        else if( k > 0 && RecRandnum >= ProbLimit[k-1] && RecRandnum < ProbLimit[k] && ProbRaw[k] > 0.)
        { ProbInt = k; }
        //else
        // ProbInt = NumberOfLines;
    }

    G4double EnergyOut = DaughterExEng[ProbInt];

    //G4cout<<"Energy "<<ProbInt<<" "<<DaughterExEng[ProbInt]<<G4endl;

    return EnergyOut;

}



void nDetPrimaryGeneratorAction::GenerateIsotropicDirectionDistribution
        (G4ThreeVector* direction,
         G4double thetaMin,
         G4double thetaMax,
         G4double phiMin,
         G4double phiMax)
{
    G4double cosThetaMin = cos(thetaMin);
    G4double cosThetaMax = cos(thetaMax);

    //assumption: cosThetaMin > cosThetaMax
    G4double randomCosTheta = G4UniformRand()*(cosThetaMin-cosThetaMax) + cosThetaMax;
    G4double randomSinTheta = sqrt(1.0 - randomCosTheta * randomCosTheta);
    G4double randomPhi = G4UniformRand()*(phiMax-phiMin) + phiMin;

    *direction = G4ThreeVector(cos(randomPhi)*randomSinTheta, sin(randomPhi)*randomSinTheta, randomCosTheta);
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

