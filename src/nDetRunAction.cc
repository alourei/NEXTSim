//
// $Id: nDetRunAction.cc,v1.0 Sept., 2015 $
// Written by Dr. Xiaodong Zhang
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// Make this appear first!
#include "G4Timer.hh"
#include "time.h"

// Selfdefine classes
#include "nDetRunAction.hh"

// geant4 class
#include "G4Run.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nDetRunAction::nDetRunAction()
{

    G4cout << "nDetRunAction::nDetRunAction()->"<< G4endl;

    G4cout << "nDetRunAction::nDetRunAction()->fAnalysisManager: "<<fAnalysisManager<< G4endl;

    timer = new G4Timer;
    fAnalysisManager= (nDetAnalysisManager*)nDetAnalysisManager::Instance();

    G4cout << "nDetRunAction::nDetRunAction()->fAnalysisManager: "<<fAnalysisManager<< G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nDetRunAction::~nDetRunAction()
{
    delete timer;
    fAnalysisManager = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nDetRunAction::BeginOfRunAction(const G4Run* aRun)
{

  G4cout << "nDetRunAction::BeginOfRunAction()->"<< G4endl;
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl; 
  timer->Start();

  // open a root file.
  //openRootFile(aRun);

    if(fFile)
    G4cout << "### File " << fFile->GetName() << " opened." << G4endl;

    // get RunId
  setRunNb(aRun->GetRunID());



 if (fAnalysisManager)
     fAnalysisManager->BeginOfRunAction(aRun);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nDetRunAction::EndOfRunAction(const G4Run* aRun)
{   
  timer->Stop();
  G4cout << "number of event = " << aRun->GetNumberOfEvent() 
         << " " << *timer << G4endl;


    if (fAnalysisManager)
        fAnalysisManager->EndOfRunAction(aRun);


    // close the root file.
    //fFile->cd();
  if(fFile->IsOpen()){

    if (IsMaster()){
        fFile->Write();
        fFile->Close();
        G4cout << "*** " << fileName << " is created." << G4endl;
    }
  }
  else
    G4cout << "*** No output file created." << G4endl;

}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool nDetRunAction::openRootFile(const G4Run* aRun)
{
  if (IsMaster()){

  //The file is saved in the ./output/ folder and
  //this file is now becoming the current directory.
  //and then create a ROOT tree and branches

  // get the system time, and use it to create the filename of root file.
  time_t rawtime;
  struct tm * timeinfo;
  char buffer[180];

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );

  strftime (buffer,180,"_%H:%M:%S_%a_%b_%d_%Y",timeinfo);

  // create a root file for the current run
  sprintf(fileName, "./output/run_%03d%s.root",aRun->GetRunID(), buffer);

  //std::cout<<fileName<<std::endl;

  //create a ROOT file
  fFile = new TFile(fileName,"RECREATE","ROOT file for high resolution neutron detector simulation");

      if (fFile->IsZombie()) {
          G4cout << "Error opening file" << G4endl;
          //exit(-1);
      }
      else{
          G4cout << "File Opened!!" << G4endl;
      }

      //create root tree
  //fFile->cd();

  fTree = new TTree("neutronEvent","Photons produced by thermal neutrons");

  if(fTree) G4cout << "nDetRunAction::openRootFile()->fTree "<<fTree<< G4endl;

  //fTree->SetAutoSave(1000000000); // autosave when 1 Gbyte written

  //fFile->ls();

      G4cout << "HERE!!" << G4endl;


      //if(defineRootBranch == false){
    int bufsize = 64000;
    fBranch = fTree->Branch("runNb", &runNb, "runNb/L", bufsize);
    fBranch = fTree->Branch("eventNb", &eventNb, "enevtNb/L", bufsize);

     fTree->Branch("neutronIncidentPositionX",&neutronIncidentPositionX,"neutronIncidentPositionX/D",bufsize);
     fTree->Branch("neutronIncidentPositionY",&neutronIncidentPositionY,"neutronIncidentPositionY/D",bufsize);
     fTree->Branch("neutronIncidentPositionZ",&neutronIncidentPositionZ,"neutronIncidentPositionZ/D",bufsize);

    fTree->Branch("depositedEnergy", &depEnergy, "depEnergy/D", bufsize);

    fTree->Branch("vTimeOfPhotonInSD1", &vTimeOfPhotonInSD1);
    fTree->Branch("vTimeOfPhotonInSD2", &vTimeOfPhotonInSD2);
    fTree->Branch("vTimeOfPhotonInEJ200", &vTimeOfPhotonInEJ200);

    fTree->Branch("vPrimaryPhotonPositionX", &vPrimaryPhotonPositionX);
    fTree->Branch("vPrimaryPhotonPositionY", &vPrimaryPhotonPositionY);
    fTree->Branch("vPrimaryPhotonPositionZ", &vPrimaryPhotonPositionZ);

    fTree->Branch("vSD1PhotonPositionX", &vSD1PhotonPositionX);
    fTree->Branch("vSD1PhotonPositionY", &vSD1PhotonPositionY);
    fTree->Branch("vSD1PhotonPositionZ", &vSD1PhotonPositionZ);

    fTree->Branch("vSD2PhotonPositionX", &vSD2PhotonPositionX);
    fTree->Branch("vSD2PhotonPositionY", &vSD2PhotonPositionY);
    fTree->Branch("vSD2PhotonPositionZ", &vSD2PhotonPositionZ);

//Following branches are added by Kyle.
    fBranch = fTree->Branch("particleCharge", &particleCharge);
    fBranch = fTree->Branch("particleName", &particleName);


      defineRootBranch = true;
  //}
  }
  return false; // in case of success.
}//end of open root file...

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool nDetRunAction::fillBranch()
{
    //fFile->cd();
  if(fTree)
  fTree->Fill();// fill the tree
  //nEvent++;

  return false; // in case of success
}//end of fill events method

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
