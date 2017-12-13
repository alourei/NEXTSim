//
// Created by David Pérez Loureiro on 2/6/17.
//

#include "nDetAnalysisManager.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "nDetSD.hh"
#include "SiPMSD.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4PrimaryVertex.hh"
#include "nDetUserTrackingInformation.hh"
#include "nDetUserEventInformation.hh"
#include "TSystem.h"

#include "G4UIcommand.hh"

#include "G4Threading.hh"
nDetAnalysisManager::nDetAnalysisManager(){

    G4cout << "nDetAnalysisManager::nDetAnalysisManager()->"<<this<< G4endl;
    fFileName="Out";
    //fgossipFileName ="GossipOut.bin";
    fMessenger = new nDetAnalysisMessenger(this);
    fScintCollectionID=-1;
    fSiPMCollectionID=-1;

    fNbOfDetectors =2;
    //ResetEvent();
}


nDetAnalysisManager::~nDetAnalysisManager(){


    G4cout << "nDetAnalysisManager::~nDetAnalysisManager()->"  << G4endl;


    //delete fTree;
     //   delete fFile;


}

void nDetAnalysisManager::OpenROOTFile(){

    G4cout << "nDetAnalysisManager::OpenROOTFile()->fFile " << fFile<< "." << G4endl;
    //fFileName=fileName;

    G4String name;

#ifdef G4MULTITHREADED

    G4String s = G4UIcommand::ConvertToString(G4Threading::G4GetThreadId());
    name=fFileName +"_"+s+".root";

#else

    name=fFileName + ".root";
#endif

    fFileName= name;
    fFile = new TFile(fFileName,"RECREATE");

    //fFile = new TFile("cona.root","RECREATE");

    if(fFile->IsOpen())
        G4cout << "nDetAnalysisManager::OpenROOTFile()->" << fFileName << " has been opened." << G4endl;
    else
    return;
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

    fTree->Branch("neutronIncidentPositionX",&neutronIncidentPositionX,"neutronIncidentPositionX/D",bufsize);
    fTree->Branch("neutronIncidentPositionY",&neutronIncidentPositionY,"neutronIncidentPositionY/D",bufsize);
    fTree->Branch("neutronIncidentPositionZ",&neutronIncidentPositionZ,"neutronIncidentPositionZ/D",bufsize);

    fTree->Branch("depositedEnergy", &depEnergy, "depEnergy/D", bufsize);
    fTree->Branch("firstEnergy", &firstEnergy, "fEnergy/D", bufsize);
    fTree->Branch("NumberofPhotons",&fNbOfPhotons,"Ngammas/I");
    fTree->Branch("NumberofDetectedPhotons",&fNbOfDetectedPhotons,"NgammasDet/I");


    fTree->Branch("TrackLength",&fvTrackLength);
    //fTree->Branch("TrackTime",&fvTrackTime);


    fTree->Branch("vPrimaryPhotonPositionX", &fvPrimaryPhotonPositionX);
    fTree->Branch("vPrimaryPhotonPositionY", &fvPrimaryPhotonPositionY);
    fTree->Branch("vPrimaryPhotonPositionZ", &fvPrimaryPhotonPositionZ);
    fTree->Branch("vTimeOfPhotonInEJ200", &fvPrimaryPhotonTime);
    fTree->Branch("vPhotonTrackIDEJ200", &fvPrimaryPhotonTrackID);

    fTree->Branch("vSDPhotonPositionX", &fvSDPhotonPositionX);
    fTree->Branch("vSDPhotonPositionY", &fvSDPhotonPositionY);
    fTree->Branch("vSDPhotonPositionZ", &fvSDPhotonPositionZ);
    fTree->Branch("vSDPhotonTime", &fvSDPhotonTime);
    fTree->Branch("vSDPhotonWavelength", &fvSDPhotonWavelength);
    fTree->Branch("vSDDetectorNumber", &fvSDNumber);
    fTree->Branch("vSDTrackID", &fvSDPhotonTrackID);

    fTree->Branch("NofReflections",&fvTrackReflections);



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

    neutronIncidentPositionX=-990;
    neutronIncidentPositionY=-990;
    neutronIncidentPositionZ=-990;

    //fvPrimaryPhotonPositionX.resize(1);
    //fvPrimaryPhotonPositionY.resize(1);
    //fvPrimaryPhotonPositionZ.resize(1);

    depEnergy=0; // energy deposition inside of the EJ200 scintillator
    firstEnergy=0;
    //G4cout<<"fvPrimaryPhotonPositionX "<<fvPrimaryPhotonPositionX.size()<<G4endl;
    //G4cout<<"fvPrimaryPhotonPositionY "<<fvPrimaryPhotonPositionY.size()<<G4endl;
    //G4cout<<"fvPrimaryPhotonPositionZ "<<fvPrimaryPhotonPositionZ.size()<<G4endl;

    fNbOfPhotons=0;
    fNbOfDetectedPhotons=0;
    std::vector<double>().swap(fvPrimaryPhotonPositionX);
    std::vector<double>().swap(fvPrimaryPhotonPositionY);
    std::vector<double>().swap(fvPrimaryPhotonPositionZ);
    std::vector<double>().swap(fvPrimaryPhotonTime);
    std::vector<int>().swap(fvPrimaryPhotonTrackID);

    std::vector<double>().swap(fvSDPhotonPositionX);
    std::vector<double>().swap(fvSDPhotonPositionY);
    std::vector<double>().swap(fvSDPhotonPositionZ);
    std::vector<double>().swap(fvSDPhotonTime);
    std::vector<double>().swap(fvSDPhotonWavelength);
    std::vector<double>().swap(fvTrackLength);
    std::vector<double>().swap(fvTrackTime);
    std::vector<int>().swap(fvSDPhotonTrackID);

    std::vector<int>().swap(fvSDNumber);
    std::vector<int>().swap(fvTrackReflections);

    for(G4int i=0;i<fphotons.size();i++){

        fphotons.at(i)->clear();
    }

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

    //OpenGossipFile();


    OpenROOTFile();

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

    //CloseGossipFile();

    //OnceAWhileDoIt(true);
    return;


}


void nDetAnalysisManager::BeginOfEventAction(const G4Event *anEvent) {

    //G4cout<<"nDetAnalysisManager::BeginOfEventAction()"<<G4endl;

    //if(gSystem)
    //    gSystem->ProcessEvents();


    //ResetEvent();

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


    nDetUserEventInformation *theEventInfo=(nDetUserEventInformation*)anEvent->GetUserInformation();

    G4int nDetections=theEventInfo->GetDetectionCount();
    G4int nAbsorptions=theEventInfo->GetAbsortionCount();

    //G4cout<<"SiPMCollectionID->"<<fSiPMCollectionID<<G4endl;
    //theEventInfo->Print();

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
            G4double energy0=(*DHC_Sci)[i]->GetEdep_first()/keV;
            depEnergy+=energy;
            if(firstEnergy==0)
                firstEnergy=-energy0;
            //fvPrimaryPhotonPositionX.push_back(pos.x()/mm);
            //fvPrimaryPhotonPositionY.push_back(pos.y()/mm);
            //fvPrimaryPhotonPositionZ.push_back(pos.z()/mm);
            //fvPrimaryPhotonTime.push_back(ptime);
            //(*DHC_Sci)[i]->Print();
        }




    }

    if(DHC_SiPM) {

        unsigned int eventNumber=(unsigned int)fEventNb;

        //fgossipOut->write((char*)&eventNumber, sizeof(unsigned int));

        G4int NbHits = DHC_SiPM->entries();
        fNbOfDetectedPhotons=NbHits;

        unsigned int photonNumber=(unsigned int)fNbOfDetectedPhotons;

        //fgossipOut->write((char*)&photonNumber, sizeof(unsigned int));

        //G4cout << "nDetAnalysisManager::EndOfEventAction()->Nb of Hits in SiPM " << NbHits << G4endl;



       for (Int_t i = 0; i < NbHits; i++) {

            G4ThreeVector pos = (*DHC_SiPM)[i]->GetPos();
            G4double ptime = (*DHC_SiPM)[i]->GetTime() / ns;
            G4int detector=(*DHC_SiPM)[i]->GetSiPMNumber();
            G4int trackID=(*DHC_SiPM)[i]->GetTrackID();
            G4double wavelength=(*DHC_SiPM)[i]->GetWaveLength();
           //(*DHC_SiPM)[i]->Print();

             fvSDPhotonPositionX.push_back(pos.x()/mm);
             fvSDPhotonPositionY.push_back(pos.y()/mm);
             fvSDPhotonPositionZ.push_back(pos.z()/mm);
             fvSDPhotonTime.push_back(ptime);
             fvSDPhotonWavelength.push_back(wavelength);

           float x=(float)pos.x()/mm;
           float y=(float)pos.y()/mm;
           float z=(float)pos.z()/mm;
           float t=(float)ptime;
           float wl=(float)wavelength;
           //fgossipOut->write((char*)&x, sizeof(float));
           //fgossipOut->write((char*)&y, sizeof(float));
           //fgossipOut->write((char*)&z, sizeof(float));
           //fgossipOut->write((char*)&t, sizeof(float));
           //fgossipOut->write((char*)&wl, sizeof(float));

           fvSDNumber.push_back(detector);
           fvSDPhotonTrackID.push_back(trackID);

       }

    }
    else{
        //G4cout << "nDetAnalysisManager::EndOfEventAction()->No Hits in SiPM !"<< G4endl;

    }
    if(fNbOfPhotons>0)
    FillTree();
    ResetEvent();

    //OnceAWhileDoIt();

    return;

}


void nDetAnalysisManager::ClassifyNewTrack(const G4Track *aTrack) {

    if(aTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition())
    { // particle is optical photon
        fNbOfPhotons++;
        //if(aTrack->GetParentID()>0)  // primary particle, neutron, ID =0, then either proton, or others, their IDs are larger than 0, and then photons
            if( aTrack->GetVolume()->GetName().find("ej200"))
            { // particle is secondary and happens in the EJ200 scintillator
                //std::cout<<aTrack->GetVolume()->GetName()<<"....in ej200..."<<aTrack->GetGlobalTime()<<"..."<<aTrack->GetDynamicParticle()->GetDefinition()->GetParticleName()<<"...."<<aTrack->GetPosition()<<std::endl;
                //fNbOfPhotons++;

                G4double ptime = aTrack->GetGlobalTime();
                G4ThreeVector pos = aTrack->GetPosition();

                fvPrimaryPhotonTrackID.push_back(aTrack->GetTrackID());
                fvPrimaryPhotonPositionX.push_back(pos.x()/mm);
                fvPrimaryPhotonPositionY.push_back(pos.y()/mm);
                fvPrimaryPhotonPositionZ.push_back(pos.z()/mm);
                fvPrimaryPhotonTime.push_back(ptime);
            }
            else{ // note that only the first volume is kept...
                //std::cout<<aTrack->GetVolume()->GetName()<<"...."<<aTrack->GetGlobalTime()<<"..."<<aTrack->GetDynamicParticle()->GetDefinition()->GetParticleName()<<"...."<<aTrack->GetPosition()<<std::endl;
            }

    }
    return;
}


void nDetAnalysisManager::GeneratePrimaries(const G4Event *anEvent) {

//G4cout<<"nDetAnalysisManager::GeneratePrimaries()"<<G4endl;

    G4PrimaryVertex *theVertex=anEvent->GetPrimaryVertex();

    G4String pname=theVertex->GetPrimary()->GetG4code()->GetParticleName();

    neutronIncidentPositionX=theVertex->GetX0();
    neutronIncidentPositionY=theVertex->GetY0();
    neutronIncidentPositionZ=theVertex->GetZ0();

    incidentparticle=pname;

    return;
}


void nDetAnalysisManager::PostUserTrackingAction(const G4Track *aTrack) {

    nDetUserTrackingInformation *theInfo=(nDetUserTrackingInformation*)aTrack->GetUserInformation();

    if(theInfo->GetDetectionCount()==1) {
        fvTrackLength.push_back(aTrack->GetTrackLength());
        fvTrackTime.push_back(aTrack->GetGlobalTime());
        fvTrackReflections.push_back(theInfo->GetReflectionCount());
    }
}


void nDetAnalysisManager::OpenGossipFile() {

    fgossipOut = new ofstream(fgossipFileName.data(),std::ios::out | std::ios::app | std::ios::binary);


}

void nDetAnalysisManager::CloseGossipFile() {

    fgossipOut->close();
}


void nDetAnalysisManager::InitGossip() {

    fsipm = new sipmMC();

    fsipm->GetParaFile("input/MPPC_6x6.txt");

    TFile f("input/SpectralSensitivity.root");
    fsipm->SetSpectralSensitivity((TGraph*)f.Get("MPPC_noRef"));
    f.Close();

    for(Int_t i=0; i<fNbOfDetectors;i++) {

        PhotonList *theList=new PhotonList();
        fphotons.push_back(theList);
    }

}

void nDetAnalysisManager::OnceAWhileDoIt(const G4bool DoItNow) {
    time_t Now = time(0); // get the current time (measured in seconds)
    if ( (!DoItNow) && (LastDoItTime > (Now - 10)) ) return; // every 10 seconds
    LastDoItTime = Now;

    G4cout<<"Doing it!"<<G4endl;

    if (gSystem) gSystem->ProcessEvents();

}

