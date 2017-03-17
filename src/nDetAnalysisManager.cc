//
// Created by David Pérez Loureiro on 2/6/17.
//

#include "nDetAnalysisManager.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "nDetSD.hh"
#include "SiPMSD.hh"
#include "G4SystemOfUnits.hh"

#include "TSystem.h"
nDetAnalysisManager::nDetAnalysisManager(){

    G4cout << "nDetAnalysisManager::nDetAnalysisManager()->"<<this<< G4endl;
    G4cout<<"fvPrimaryPhotonPositionX "<<fvPrimaryPhotonPositionX.size()<<G4endl;
    //std::vector<double>().swap(fvPrimaryPhotonPositionX);
    //fvPrimaryPhotonPositionY.clear();
    //std::vector<double>().swap(fvPrimaryPhotonPositionY);
    G4cout<<"fvPrimaryPhotonPositionY "<<fvPrimaryPhotonPositionY.size()<<G4endl;
    //fvPrimaryPhotonPositionZ.clear();
    //std::vector<double>().swap(fvPrimaryPhotonPositionZ);
    G4cout<<"fvPrimaryPhotonPositionZ "<<fvPrimaryPhotonPositionZ.size()<<G4endl;

    fScintCollectionID=-1;
    fSiPMCollectionID=-1;
    //ResetEvent();
}


nDetAnalysisManager::~nDetAnalysisManager(){


    G4cout << "nDetAnalysisManager::~nDetAnalysisManager()->"  << G4endl;


    //delete fTree;
     //   delete fFile;


}

void nDetAnalysisManager::OpenROOTFile( const G4String fileName){

    G4cout << "nDetAnalysisManager::OpenROOTFile()->fFile " << fFile<< "." << G4endl;
    fFileName=fileName;
    fFile = new TFile(fileName,"RECREATE");
    //fFile = new TFile("cona.root","RECREATE");

    G4cout << "nDetAnalysisManager::OpenROOTFile()->" << fFileName << " has been opened." << G4endl;

    //if(gSystem)
    //    gSystem->ProcessEvents();

    //fFile->cd();
    //fFile->cd();

    fTree=new TTree("theTree","NEXTSim Output Tree");

    G4cout << "nDetAnalysisManager::OpenROOTFile()->fTree " << fTree << G4endl;

    //fTree->SetAutoSave(1000000000); // autosave when 1 Gbyte written

    //if(defineRootBranch == false){
    G4int bufsize = 64000;
    fTree->Branch("runNb", &fRunNb, "runNb/L", bufsize);
    fTree->Branch("eventNb", &fEventNb, "enevtNb/L", bufsize);

//    fTree->Branch("neutronIncidentPositionX",&neutronIncidentPositionX,"neutronIncidentPositionX/D",bufsize);
//    fTree->Branch("neutronIncidentPositionY",&neutronIncidentPositionY,"neutronIncidentPositionY/D",bufsize);
//    fTree->Branch("neutronIncidentPositionZ",&neutronIncidentPositionZ,"neutronIncidentPositionZ/D",bufsize);

    fTree->Branch("depositedEnergy", &depEnergy, "depEnergy/D", bufsize);


    fTree->Branch("vPrimaryPhotonPositionX", &fvPrimaryPhotonPositionX);
    fTree->Branch("vPrimaryPhotonPositionY", &fvPrimaryPhotonPositionY);
    fTree->Branch("vPrimaryPhotonPositionZ", &fvPrimaryPhotonPositionZ);
    fTree->Branch("vTimeOfPhotonInEJ200", &fvPrimaryPhotonTime);

    fTree->Branch("vSDPhotonPositionX", &fvSDPhotonPositionX);
    fTree->Branch("vSDPhotonPositionY", &fvSDPhotonPositionY);
    fTree->Branch("vSDPhotonPositionZ", &fvSDPhotonPositionZ);
    fTree->Branch("vSDPhotonTime", &fvSDPhotonTime);
    fTree->Branch("vSDDetectorNumber", &fvSDNumber);

    //Following branches are added by Kyle.
//    fTree->Branch("particleCharge", &fparticleCharge);
//    fTree->Branch("particleName", &fparticleName);

    G4cout << "nDetAnalysisManager::OpenROOTFile()->" << fTree->GetName() << " has been created." << G4endl;

    //OnceAWhileDoIt();

    return;

}

void nDetAnalysisManager::WriteFile() {

    //fFile->cd();
    if(fTree) {
        fTree->Write();

        G4cout << "nDetAnalysisManager::WriteFile()->" << fFileName << " has been written." << G4endl;
    }

}


void nDetAnalysisManager::CloseROOTFile() {

    if(fFile){
        //fFile->cd();
        fFile->Close();
    }
}

void nDetAnalysisManager::FillTree(){

    //G4cout<<"Filling Tree-> "<<fTree->GetName()<<G4endl;
    //fTree->Print();
    //fFile->cd();
    if(fTree)
    fTree->Fill();
}


void nDetAnalysisManager::ResetEvent() {

    //G4cout<<"nDetAnalysisManager::ResetEvent()"<<G4endl;

    //if(gSystem)
    //    gSystem->ProcessEvents();

    fEventNb=0;

    neutronIncidentPositionX=0;
    neutronIncidentPositionY=0;
    neutronIncidentPositionZ=0;

    //fvPrimaryPhotonPositionX.resize(1);
    //fvPrimaryPhotonPositionY.resize(1);
    //fvPrimaryPhotonPositionZ.resize(1);

    depEnergy=0; // energy deposition inside of the EJ200 scintillator
    //G4cout<<"fvPrimaryPhotonPositionX "<<fvPrimaryPhotonPositionX.size()<<G4endl;
    //G4cout<<"fvPrimaryPhotonPositionY "<<fvPrimaryPhotonPositionY.size()<<G4endl;
    //G4cout<<"fvPrimaryPhotonPositionZ "<<fvPrimaryPhotonPositionZ.size()<<G4endl;


    //G4cout<<"nDetAnalysisManager::ResetEvent()->Clearing Vectors..."<<G4endl;
    //fvPrimaryPhotonPositionX.clear();
    std::vector<double>().swap(fvPrimaryPhotonPositionX);
    //G4cout<<"fvPrimaryPhotonPositionX "<<fvPrimaryPhotonPositionX.size()<<G4endl;
    //fvPrimaryPhotonPositionY.clear();
    std::vector<double>().swap(fvPrimaryPhotonPositionY);
    //G4cout<<"fvPrimaryPhotonPositionY "<<fvPrimaryPhotonPositionY.size()<<G4endl;
    //fvPrimaryPhotonPositionZ.clear();
    std::vector<double>().swap(fvPrimaryPhotonPositionZ);
    //G4cout<<"fvPrimaryPhotonPositionZ "<<fvPrimaryPhotonPositionZ.size()<<G4endl;
    //fvPrimaryPhotonTime.clear();




    std::vector<double>().swap(fvSDPhotonPositionX);
    std::vector<double>().swap(fvSDPhotonPositionY);
    std::vector<double>().swap(fvSDPhotonPositionZ);
    std::vector<double>().swap(fvSDPhotonTime);
    std::vector<int>().swap(fvSDNumber);
//
//    fparticleName.clear();
//    fparticleCharge.clear();
    //G4cout<<"nDetAnalysisManager::ResetEvent()->Vectors cleared"<<G4endl;

    //G4cout<<"nDetAnalysisManager::ResetEvent()->HERE"<<G4endl;

    //OnceAWhileDoIt();
    return;
}


void nDetAnalysisManager::BeginOfRunAction(const G4Run *aRun) {

    //SetVerboseLevel(2);

    //G4cout<<"nDetAnalysisManager::BeginOfRunAction()"<<G4endl;


    fRunNb=aRun->GetRunID();


    OpenROOTFile("DPL_test.root");

    //ResetEvent();

    //if(gSystem) {
    //   gSystem->ProcessEvents();
    //}
    //G4cout<<"HERE!"<<G4endl;

    //OnceAWhileDoIt(true);

    //G4cout<<"HERE2!"<<G4endl;
    return;

    }


void nDetAnalysisManager::EndOfRunAction(const G4Run *aRun) {

    //G4cout<<"nDetAnalysisManager::EndOfRunAction()"<<G4endl;

    //if(gSystem)
    //    gSystem->ProcessEvents();

    WriteFile();
    CloseROOTFile();

    //OnceAWhileDoIt(true);
    return;


}


void nDetAnalysisManager::BeginOfEventAction(const G4Event *anEvent) {

    //G4cout<<"nDetAnalysisManager::BeginOfEventAction()"<<G4endl;

    //if(gSystem)
    //    gSystem->ProcessEvents();


    ResetEvent();

    G4SDManager *man=G4SDManager::GetSDMpointer();

    if(fScintCollectionID<0)
        fScintCollectionID=man->GetCollectionID("SciCollection");
    if(fSiPMCollectionID<0)
        fSiPMCollectionID=man->GetCollectionID("SiPMCollection");
    fEventNb=anEvent->GetEventID();


    //OnceAWhileDoIt();

    return;
 }



void nDetAnalysisManager::EndOfEventAction(const G4Event *anEvent){

    //G4cout<<"nDetAnalysisManager::EndOfEventAction()"<<G4endl;




    //G4cout<<"ScintCollectionID->"<<fScintCollectionID<<G4endl;
    //G4cout<<"SiPMCollectionID->"<<fSiPMCollectionID<<G4endl;

    G4HCofThisEvent *HCE=anEvent->GetHCofThisEvent();

    nDetHitsCollection *DHC_Sci=0;
    SiPMHitsCollection *DHC_SiPM=0;

    if(HCE) {

        //G4cout<<"nDetAnalysisManager::EndOfEventAction()->HCE->GetNumberOfCollections(): "
        //      <<HCE->GetNumberOfCollections()<<G4endl;
        if(fScintCollectionID>=0)DHC_Sci=(nDetHitsCollection*)(HCE->GetHC(fScintCollectionID));
        if(fSiPMCollectionID>=0)DHC_SiPM=(SiPMHitsCollection*)(HCE->GetHC(fSiPMCollectionID));

        //G4cout<<"nDetAnalysisManager::EndOfEventAction()->DHC_Sci "<<DHC_Sci<<G4endl;
        //G4cout<<"nDetAnalysisManager::EndOfEventAction()->DHC_SiPM "<<DHC_SiPM<<G4endl;
    }

    if(DHC_Sci){

        G4int NbHits=DHC_Sci->entries();

        //G4cout<<"nDetAnalysisManager::EndOfEventAction()->Nb of Hits in Scint "<<NbHits<<G4endl;

        for(Int_t i=0;i<NbHits;i++){

            G4ThreeVector pos = (*DHC_Sci)[i]->GetPos();
            G4double ptime = (*DHC_Sci)[i]->GetTime()/ns;
            G4double energy=(*DHC_Sci)[i]->GetEdep()/keV;
            depEnergy+=energy;
            fvPrimaryPhotonPositionX.push_back(pos.x()/mm);
            fvPrimaryPhotonPositionY.push_back(pos.y()/mm);
            fvPrimaryPhotonPositionZ.push_back(pos.z()/mm);
            fvPrimaryPhotonTime.push_back(ptime);
            //(*DHC_Sci)[i]->Print();
        }




    }

    if(DHC_SiPM) {

        G4int NbHits = DHC_SiPM->entries();

        //G4cout << "nDetAnalysisManager::EndOfEventAction()->Nb of Hits in SiPM " << NbHits << G4endl;

       for (Int_t i = 0; i < NbHits; i++) {

            G4ThreeVector pos = (*DHC_SiPM)[i]->GetPos();
            G4double ptime = (*DHC_SiPM)[i]->GetTime() / ns;
            G4int detector=(*DHC_SiPM)[i]->GetSiPMNumber();
            //(*DHC_SiPM)[i]->Print();

             fvSDPhotonPositionX.push_back(pos.x()/mm);
             fvSDPhotonPositionY.push_back(pos.y()/mm);
             fvSDPhotonPositionZ.push_back(pos.z()/mm);
             fvSDPhotonTime.push_back(ptime);
             fvSDNumber.push_back(detector);

       }

    }
    else{
        //G4cout << "nDetAnalysisManager::EndOfEventAction()->No Hits in SiPM !"<< G4endl;

    }
    FillTree();
    //ResetEvent();

    //OnceAWhileDoIt();

    return;

}


void nDetAnalysisManager::OnceAWhileDoIt(const G4bool DoItNow) {
    time_t Now = time(0); // get the current time (measured in seconds)
    if ( (!DoItNow) && (LastDoItTime > (Now - 10)) ) return; // every 10 seconds
    LastDoItTime = Now;

    G4cout<<"Doing it!"<<G4endl;

    if (gSystem) gSystem->ProcessEvents();

}
