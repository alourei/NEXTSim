//
// $Id: nDetRunAction.hh,v1.0 Sept., 2015 $
//   Written by Dr. Xiaodong Zhang
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


/**
 * \file nDetRunAction.hh
 * \brief Definition of the nDetRunAction class
 * \authors X. Zhang, K. Schmidt, D. Perez-Loureiro
 * \date 2018/07/13
 * \version 1.1
 *
 *  Created on: Sept., 2015
 */

#ifndef nDetRunAction_h
#define nDetRunAction_h 1

#include "globals.hh"
#include "G4UserRunAction.hh"

#include "nDetAnalysisManager.hh"

#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"

#include "TH1F.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Timer;
class G4Run;

/** \class nDetRunAction
 *  \brief This class implements the Pure virtual class G4UserRunAction
 *
 */
class nDetRunAction : public G4UserRunAction
{
  public:

    /**
     * Constructor
     */
    nDetRunAction();
    /**
     * Destructor
     */
    virtual ~nDetRunAction();

  public:
    /**
     * Actions to be done at the beginning of the run
     * @param aRun pointer to the current run
     */
    void BeginOfRunAction(const G4Run* aRun);

    /**
     * Actions to be done at the end of the run
     * @param aRun pointer to the current run
     */
    void EndOfRunAction(const G4Run* aRun);

    //TODO DPL: Remove all this. The information is already stored in the Analysis manager output!

    bool fillBranch(); // deposited energy in YAP

    void setRunNb(G4long rNb) { runNb = rNb; };
    void setEventNb(G4long evtNb) { eventNb = evtNb; }

    void setNeutronIncidentPositionX(G4double aPX) { neutronIncidentPositionX = aPX; };
    void setNeutronIncidentPositionY(G4double aPY) { neutronIncidentPositionY = aPY; };
    void setNeutronIncidentPositionZ(G4double aPZ) { neutronIncidentPositionZ = aPZ; };

    void setDepEnergy(G4double depE) { depEnergy = depE; };

    void vTimeOfPhotonInSD1PushBack(double pT1) { vTimeOfPhotonInSD1.push_back(pT1); };
    void vTimeOfPhotonInSD2PushBack(double pT2) { vTimeOfPhotonInSD2.push_back(pT2); };
    void vTimeOfPhotonInEJ200PushBack(double pT0) { vTimeOfPhotonInEJ200.push_back(pT0); };

    void vPrimaryPhotonPositionXPushBack(double pPX) { vPrimaryPhotonPositionX.push_back(pPX); };
    void vPrimaryPhotonPositionYPushBack(double pPY) { vPrimaryPhotonPositionY.push_back(pPY); };
    void vPrimaryPhotonPositionZPushBack(double pPZ) { vPrimaryPhotonPositionZ.push_back(pPZ); };

    void vSD1PhotonPositionXPushBack(double pPX) { vSD1PhotonPositionX.push_back(pPX); };
    void vSD1PhotonPositionYPushBack(double pPY) { vSD1PhotonPositionY.push_back(pPY); };
    void vSD1PhotonPositionZPushBack(double pPZ) { vSD1PhotonPositionZ.push_back(pPZ); };

    void vSD2PhotonPositionXPushBack(double pPX) { vSD2PhotonPositionX.push_back(pPX); };
    void vSD2PhotonPositionYPushBack(double pPY) { vSD2PhotonPositionY.push_back(pPY); };
    void vSD2PhotonPositionZPushBack(double pPZ) { vSD2PhotonPositionZ.push_back(pPZ); };

    //Following lines added by Kyle
    void particleNamePushBack(std::string name) { particleName.push_back(name); };
    void particleChargePushBack(double charge) {particleCharge.push_back(charge); };
    //end
    // clear all the vector for the next event
    void vectorClear(){
			vTimeOfPhotonInSD1.clear();
                        vTimeOfPhotonInSD2.clear();
                        vTimeOfPhotonInEJ200.clear();
			vPrimaryPhotonPositionX.clear();
			vPrimaryPhotonPositionY.clear();
                        vPrimaryPhotonPositionZ.clear(); 
                        vSD1PhotonPositionX.clear();
                        vSD1PhotonPositionY.clear();
                        vSD1PhotonPositionZ.clear();
                        vSD2PhotonPositionX.clear();
                        vSD2PhotonPositionY.clear();
                        vSD2PhotonPositionZ.clear();
                        particleName.clear();
                        particleCharge.clear();
			};

  private:  // function member
    bool openRootFile(const G4Run* aRun); 
  
  private:  // data member
    G4Timer* timer;  // able to measure elasped user/system process time.

    char fileName[300];
    TFile        *fFile;    // define root file
    TTree        *fTree;    // tree and its branches
    TBranch      *fBranch;
    bool defineRootBranch; 

    G4long       runNb;
    G4long       eventNb;

    G4double     neutronIncidentPositionX;
    G4double     neutronIncidentPositionY;
    G4double     neutronIncidentPositionZ;

    G4double     depEnergy; // energy deposition inside of the EJ200 scintillator

    std::vector<double>     vTimeOfPhotonInSD1;
    std::vector<double>     vTimeOfPhotonInSD2;
    std::vector<double>     vTimeOfPhotonInEJ200;

    // record the position of the initial photons inside the EJ200 scintillator
    std::vector<double>     vPrimaryPhotonPositionX;
    std::vector<double>     vPrimaryPhotonPositionY;
    std::vector<double>     vPrimaryPhotonPositionZ;  

    std::vector<double>     vSD1PhotonPositionX;
    std::vector<double>     vSD1PhotonPositionY;
    std::vector<double>     vSD1PhotonPositionZ;

    std::vector<double>     vSD2PhotonPositionX;
    std::vector<double>     vSD2PhotonPositionY;
    std::vector<double>     vSD2PhotonPositionZ;

//The following are added by Kyle
    std::vector<std::string> particleName;
    std::vector<double>      particleCharge;

    nDetAnalysisManager *fAnalysisManager;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif /*nDetRunAction_h*/

// Class description:
//
// This is  the base class of a user's action class which defines the 
// user's action at the beginning and the end of each run. The user can
// override the following two methods but the user should not change 
// any of the contents of G4Run object.

// Description of G4Run
// This class represents a run. An object of this class is constructed 
// and deleted by G4RunManager. Basically the user should use only 
// the get methods. All properties are set by G4RunManager.
//
