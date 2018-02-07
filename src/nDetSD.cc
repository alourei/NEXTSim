//
// $Id: nDetSD.hh,v 1.0 Sept., 2015 $
//  Written by Dr. Xiaodong Zhang
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "nDetSD.hh"
#include "nDetHits.hh"
#include "G4Step.hh"
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4ios.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4ProcessManager.hh"
#include "G4Neutron.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
nDetSD::nDetSD(G4String name)
:G4VSensitiveDetector(name)
{
  G4cout<<"nDetSD::nDetSD(): Constructing Sensitive Detector"<< G4endl;
  G4String HCname;
  collectionName.insert(HCname="SciCollection");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
nDetSD::~nDetSD(){;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void nDetSD::Initialize(G4HCofThisEvent* HCE)
{
  static int HCID = -1;
  hitsCollection = new nDetHitsCollection
                      (SensitiveDetectorName,collectionName[0]); 
  if(HCID<0)
  { HCID = GetCollectionID(0); }
  HCE->AddHitsCollection(HCID,hitsCollection);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4bool nDetSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{

    //G4cout<<"nDetSD::ProcessHits()->"<< G4endl;


	/*
	G4cout<<"**************** SD start ************"<< G4endl;
	G4cout<<"Process name:"<<aStep->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName()<<G4endl;
	G4String name = aStep->GetTrack()->GetVolume()->GetName();
	G4cout<<"Physical volume name:"<<name<<G4endl;
	G4cout<<"Length of this Step: "<<aStep->GetStepLength()<<" mm"<<G4endl;
	G4cout<<"**************** SD stop ************"<< G4endl;
	*/


        if(aStep->GetStepLength()>0){
          /* 
          G4cout<<"**************** SD start ************"<< G4endl;
          G4cout<<"Process name:"<<aStep->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName()<<G4endl;
          G4String name = aStep->GetTrack()->GetVolume()->GetName();
          G4cout<<"Physical volume name:"<<name<<G4endl;
          G4cout<<"Length of this Step: "<<aStep->GetStepLength()/mm<<" mm"<<G4endl;
          G4cout<<"**************** SD stop ************"<< G4endl;
          */
            if(aStep->GetTrack()->GetDefinition() != G4OpticalPhoton::OpticalPhotonDefinition()){
              //if(aStep->GetTrack()->GetDefinition() == G4Neutron::NeutronDefinition()){
                    G4double edep=aStep->GetTotalEnergyDeposit();
          const G4VProcess *theProcess = aStep->GetPostStepPoint()->GetProcessDefinedStep();
          G4String processName = theProcess->GetProcessName();
	      nDetHit* newHit = new nDetHit();
          newHit->SetProcessName(processName);
          newHit->SetParticleName(aStep->GetTrack()->GetDefinition()->GetParticleName());
  	      newHit->SetTime( aStep->GetPostStepPoint()->GetGlobalTime() );
          newHit->SetPos( aStep->GetPostStepPoint()->GetPosition() );
          newHit->SetEdep(edep);
          newHit->SetTrackID(aStep->GetTrack()->GetTrackID());
          //newHit->SetEdep_first(aStep->GetDeltaEnergy());
          newHit->SetEdep_first(-(aStep->GetPostStepPoint()->GetKineticEnergy()
                                  -aStep->GetPreStepPoint()->GetKineticEnergy()));

          hitsCollection->insert( newHit );
        }
        }
        else{
          aStep->GetTrack()->SetTrackStatus(fStopAndKill);
        }

  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4bool nDetSD::ProcessHits(const G4Step* aStep)
{
/*
        G4cout<<"**************** SD start ************"<< G4endl;
        G4cout<<"Process name:"<<aStep->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName()<<G4endl;
        G4String name = aStep->GetTrack()->GetVolume()->GetName();
        G4cout<<"Physical volume name:"<<name<<G4endl;
        G4cout<<"Physical volume of prestep point: " << aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName()<<G4endl;
        G4cout<<"Physical volume of poststep point: " << aStep->GetPostStepPoint()->GetPhysicalVolume()->GetName()<<G4endl;
        G4cout<<"Length of this Step: "<<aStep->GetStepLength()/mm<<" mm"<<G4endl;
        G4cout<<"**************** SD stop ************"<< G4endl;
        /// old codes used to pick off the information about hit in SD
        nDetHit* newHit = new nDetHit();
        newHit->SetTime( aStep->GetPreStepPoint()->GetGlobalTime() );
        newHit->SetPos( aStep->GetPreStepPoint()->GetPosition() );
        hitsCollection->insert( newHit );
*/  
  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void nDetSD::EndOfEvent(G4HCofThisEvent*)
{
    G4int NbHits = hitsCollection->entries();

    if (verboseLevel>1) {
     G4cout << "\n-------->Hits Collection: in this event they are " << NbHits
            << " hits in the scintillator: " << G4endl;
     for (G4int i=0;i<NbHits;i++) (*hitsCollection)[i]->Print();
  }
  if(verboseLevel>0){
     G4cout << "nDetSD::EndOfEvent()->Hit Number in Scint: " << NbHits << G4endl;
     }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void nDetSD::clear()
{
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void nDetSD::DrawAll()
{
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void nDetSD::PrintAll()
{
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
