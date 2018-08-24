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

/** \class nDetAnalysisManager
 *  \brief This class is used to manage the output of the simulation.
 *
 *  The information is a stored in a ROOT TFile containing of a TTree with TBranch of TClonesArray of
 *  ScintHit and OptPhotonHit. Each entry of the Tree corresponds to a simulated event
 */

class nDetAnalysisManager:public G4RootAnalysisManager {

    public:
    /** Default constructor */
    nDetAnalysisManager();
    /** Default constructor */
    ~nDetAnalysisManager();
     /** Returns the pointer to the ROOT Tree
     *
     * @return pointer to the Tree
     */
    TTree* GetTree(){return fTree;}
    /** Sets the  ROOT Tree
     *
     * @param[in] theTree pointer to the Tree
     */
    void SetTree(TTree* theTree){fTree=theTree;}
    /** Opens the ROOT file and initializes the the Tree branches
     *
     */
    void OpenROOTFile();
    /** Writes the output ROOT file to disk
     *
     */
    void WriteFile();
    /** Closes the ROOT file
     *
     */
    void CloseROOTFile();
    /** Fills the Tree
     *
     */
    void FillTree();
    /** Resets the event
     *
     */
    void ResetEvent();
    /** Performs the actions needed at the beginning of each Run.
     *
     */
    void BeginOfRunAction(const G4Run *aRun);
    /** Performs the actions needed at the end of each Run.
     * @param[in] aRun pointer the the current G4Run
     */
    void EndOfRunAction(const G4Run *aRun);
    /** Performs the actions needed at the beginning of each Event.
     * @param[in] aRun pointer the the current G4Run
     */
    void BeginOfEventAction(const G4Event *anEvent);
    /** Performs the actions needed at the end of each Event.
     * @param[in] anEvent pointer the the current G4Event
     */
    void EndOfEventAction(const G4Event *anEvent);
    /** Performs the actions at the beginning of the tracking.
     * @param[in] aTrack pointer the the current G4Track
     */
    void ClassifyNewTrack(const G4Track * aTrack);

    void OnceAWhileDoIt(const G4bool DoItNow=false);
    /** Performs the actions during event generation
     * @param[in] anEvent pointer the the current G4Event
     */
    void GeneratePrimaries(const G4Event *anEvent);
    /** Performs the actions at the end of the tracking.
     * @param[in] aTrack pointer the the current G4Track
     */
    void PostUserTrackingAction (const G4Track *aTrack);
    /** Sets the name of the ROOT output file.
     * @param[in] OutputName the name of the output file
     */
    void SetOutputFileName(const G4String OutputName){fFileName=OutputName;}


    /** Fills the Optical Photon Hits.
     * @param[in] anEvent pointer to the current GEANT4 event
     */
    void FillOptPhotonHits( const G4Event *anEvent);
    /** Fills the Scintillator Hits.
      * @param[in] anEvent pointer to the current GEANT4 event
      */
    void FillScintHits(const G4Event *anEvent);

private:

    G4String fFileName; ///< The name of the ROOT output file

    TFile *fFile; ///< Pointer to the ROOT file

    TTree *fTree; ///< Pointer to the ROOT tree

    G4long fRunNb;  ///< Run Number
    G4long fEventNb; ///< The Event Number

    time_t LastDoItTime;

    G4int fScintCollectionID; ///< The Hit Collection Identifier of the Scintillator
    G4int fSiPMCollectionID;  ///< The Hit Collection Identifier of the Silicon PMs

    G4int  fNbOfPhotons=0;  ///< Number of scintillation photons produced
    G4int  fNbOfDetectedPhotons; ///< Number of scintillation photons detected
    G4int  fNbOfDetectors; ///<< Number of detectors

    G4int fNbOfAbsorptions;

    nDetAnalysisMessenger *fMessenger; ///< Pointer to the Analysis Messenger


    TClonesArray            *fCANeutronPosition;
    TClonesArray            *fCANeutron4Momentum;


    TClonesArray            *fCAOptPhotonHits; ///< Pointer to the  TClonesArray of Optical Photon Hits
    TClonesArray            *fCAScintHits; ///< Pointer to the  TClonesArray of Scintillator Hits


    G4double     neutronIncidentPositionX;
    G4double     neutronIncidentPositionY;
    G4double     neutronIncidentPositionZ;
    G4double     neutronIncidentEnergy;
    G4String     incidentparticle;

    G4double     depEnergy=0; ///< Energy deposition inside of the scintillator
    G4double     firstEnergy; ///< Energy deposited in the first interaction

    std::vector<double>     fvPrimaryPhotonPositionX;
    std::vector<double>     fvPrimaryPhotonPositionY;
    std::vector<double>     fvPrimaryPhotonPositionZ;
    std::vector<double>     fvPrimaryPhotonTime;
    std::vector<int>        fvPrimaryPhotonTrackID;



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

