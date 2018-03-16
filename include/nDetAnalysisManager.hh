//
// Created by David Pérez Loureiro on 2/6/17.
//

#ifndef NEXTMULTIPLESCATTERING_NDETANALYSISMANAGER_HH
#define NEXTMULTIPLESCATTERING_NDETANALYSISMANAGER_HH

#include "G4RootAnalysisManager.hh"
#include "nDetAnalysisMessenger.hh"
#include "TTree.h"
#include "TFile.h"
#include "TROOT.h"
#include "TGraph.h"
#include <vector>
#include "G4Run.hh"
#include "G4Event.hh"
#include "G4Track.hh"
#include "time.h"
#include "TVector3.h"
#include "TLorentzVector.h"
#include "TClonesArray.h"

#include "sipmMC.hh"
#include "PhotonList.hh"
#include <fstream>

#include "SiPMHits.hh"

#include "OptPhotonHit.hh"
#include "ScintHit.hh"


class OptPhotonHit;
class ScintHit;


class nDetAnalysisManager:public G4RootAnalysisManager {

    public:

    nDetAnalysisManager();
    ~nDetAnalysisManager();

    TTree* GetTree(){return fTree;}
    void SetTree(TTree* theTree){fTree=theTree;}
    void OpenROOTFile();
    void WriteFile();
    void CloseROOTFile();
    void FillTree();
    void ResetEvent();

    void BeginOfRunAction(const G4Run *aRun);
    void EndOfRunAction(const G4Run *aRun);

    void BeginOfEventAction(const G4Event *anEvent);
    void EndOfEventAction(const G4Event *anEvent);

    void ClassifyNewTrack(const G4Track * aTrack);

    void OnceAWhileDoIt(const G4bool DoItNow=false);

    void GeneratePrimaries(const G4Event *anEvent);

    void PostUserTrackingAction (const G4Track *aTrack);

    void SetOutputFileName(const G4String OutputName){fFileName=OutputName;}

    void SetGossipFileName(const G4String OutputName){fgossipFileName=OutputName;}

    void OpenGossipFile();

    void CloseGossipFile();

    void InitGossip();

    void ProcessGossip( const SiPMHitsCollection *DHC_SiPM);

    void FillOptPhotonHits( const G4Event *anEvent);
    void FillScintHits(const G4Event *anEvent);

private:

    G4String fFileName;

    TFile *fFile;

    TTree *fTree;

    G4long fRunNb;
    G4long fEventNb;

    time_t LastDoItTime;

    G4int fScintCollectionID;
    G4int fSiPMCollectionID;

    G4int  fNbOfPhotons=0;
    G4int  fNbOfDetectedPhotons;
    G4int  fNbOfDetectors;

    G4int fNbOfAbsorptions;

    nDetAnalysisMessenger *fMessenger;


    G4double     neutronIncidentPositionX;
    G4double     neutronIncidentPositionY;
    G4double     neutronIncidentPositionZ;
    G4double     neutronIncidentEnergy;
    G4String     incidentparticle;

    G4double     depEnergy=0; // energy deposition inside of the EJ200 scintillator
    G4double     firstEnergy;

    std::vector<double>     fvPrimaryPhotonPositionX;
    std::vector<double>     fvPrimaryPhotonPositionY;
    std::vector<double>     fvPrimaryPhotonPositionZ;
    std::vector<double>     fvPrimaryPhotonTime;
    std::vector<int>        fvPrimaryPhotonTrackID;

    TClonesArray            *fCANeutronPosition;
    TClonesArray            *fCANeutron4Momentum;


    TClonesArray            *fCAOptPhotonHits;

    TClonesArray            *fCAScintHits;


    std::vector<int>        fvhitNumber;
    std::vector<int>        fvTrackID;
    std::vector<int>        fvLayerNumber;
    std::vector<double>     fvScatteringAngle;


    std::vector<double>     fvSDPhotonPositionX;
    std::vector<double>     fvSDPhotonPositionY;
    std::vector<double>     fvSDPhotonPositionZ;
    std::vector<double>     fvSDPhotonTime;
    std::vector<double>     fvSDPhotonLocalTime;
    std::vector<double>     fvSDPhotonWavelength;
    std::vector<int>        fvSDNumber;
    std::vector<int>        fvSDPhotonTrackID;

    std::vector<std::string> fparticleName;
    std::vector<std::string> fprocessName;
    std::vector<double>      fparticleCharge;
    std::vector<double>      fvTrackLength;
    std::vector<double>      fvTrackTime;

    std::vector<int>         fvTrackReflections;





    //Gossip Stuff
    G4String                   fgossipFileName;
    ofstream                   *fgossipOut;

    sipmMC                     *fsipm;
    std::vector<PhotonList*>   fphotons;


};



class NEXTData:public TObject{

public:

    NEXTData();
    ~NEXTData();
    void Reset();
    void Fill();

ClassDef(NEXTData,1);
};


#endif //NEXTMULTIPLESCATTERING_NDETANALYSISMANAGER_HH

