// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************





/// \file neutronDetectorDesign.cc
/// \brief Main program of the NEXTSim package
///
/// ********************************************************************
// * The neutron detector program is used to simulate an	       *
// * optimize the performance of the scintillation detector in the    *
// * framework of Geant4.10.00.p01 and ROOT v5.34.14.                 *
// *  by Dr. Xiaodong Zhang on Sept., 2015.                            *
// *                                                                  *
// ********************************************************************


//
// ********************************************************************
// * The neutron detector program is used to simulate an	       *
// * optimize the performance of the scintillation detector in the    * 
// * framework of Geant4.10.00.p01 and ROOT v5.34.14.                 *
// *  by Dr. Xiaodong Zhang on Sept., 2015.                            *
// *                                                                  *
// ********************************************************************
//
// log: nDet.cc,v1.0  Sept., 2015
// --------------------------------------------------------------
//


                                                                         
// c/c++ headers

// Geant4 base classes
#include "G4MTRunManager.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

// using the modular physics list
#include "G4VModularPhysicsList.hh"
//#include "LBE.hh"
#include "QGSP_BERT_HP.hh"

//trying Sergei's physics list
#include "LENSLongPhysicsList.hh"

// selfdefine classes
#include "nDetConstruction.hh"
#include "nDetPrimaryGeneratorAction.hh"
#include "nDetRunAction.hh"
#include "nDetEventAction.hh"
#include "nDetStackingAction.hh"
#include "nDetSteppingAction.hh"
#include "nDetAnalysisManager.hh"
#include "nDetTrackingAction.hh"
#include "nDetPhysicsList.hh"
//#include "nDetActionInitialization.hh"

#include "G4OpticalPhysics.hh"

#include "Randomize.hh"
#include "time.h"

int main(int argc, char** argv)
{
  //make random number seeds different in different runs in Geant4 simulation
  //////////////////////////////////////
  //choose the Random engine
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine());
  //set random seed with system time
  G4long seed = time(NULL);
  CLHEP::HepRandom::setTheSeed(seed);
  //////////////////////////////////////


  // Construct the default run manager
#ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
  runManager->SetNumberOfThreads(G4Threading::G4GetNumberOfCores());
#else
  G4RunManager* runManager = new G4RunManager;
#endif


  //G4RunManager *runManager = new G4RunManager;

  // set mandatory initialization classes
  // Initialize the detector
  nDetConstruction* detector = new nDetConstruction;
  runManager->SetUserInitialization( detector );

  std::cout<<"nDetConstruction()-->"<<detector<<std::endl;

/*  // Initialize the physics lists
  // The LBE modular physics list is used in this program
  // For details about this physics list, please reference source code
  // 
  G4VModularPhysicsList* physics = new LBE();
  runManager->SetUserInitialization( physics );
  */
 
/*// Using the VANDLE (Sergei) physics list.
  LENSLongPhysicsList* physicsList = new LENSLongPhysicsList;
  runManager->SetUserInitialization( physicsList );
that didn't work... this is horribly deprecated*/


//Using "high precision" neutron scattering model.  Warning: this will be slow.


  //nDetPhysicsList* physics = (nDetPhysicsList*)new QGSP_BERT_HP();
    //nDetPhysicsList* physics = new nDetPhysicsList();
  G4VModularPhysicsList* physics = new QGSP_BERT_HP();

  G4OpticalPhysics *theOpticalPhysics=new G4OpticalPhysics();
  theOpticalPhysics->SetScintillationByParticleType(true);
  theOpticalPhysics->SetFiniteRiseTime(false);
  physics->ReplacePhysics(theOpticalPhysics);
  runManager->SetUserInitialization( physics );

#ifdef G4VIS_USE
  // add visulization manager
  G4VisManager *visManager = new G4VisExecutive;
  visManager->Initialize();
#endif

  //set optional user action classes

    nDetAnalysisManager *theManager= new nDetAnalysisManager();

  //Geant complains we need ot change this for multithreading.  Moving the following to nDetActionInitialization.cc
  nDetRunAction* runAction =
                        new nDetRunAction();
  runManager->SetUserAction( runAction );

  G4VUserPrimaryGeneratorAction* primaryGeneratorAction = 
			new nDetPrimaryGeneratorAction(runAction);
  runManager->SetUserAction( primaryGeneratorAction );

  nDetEventAction* eventAction = 
			new nDetEventAction(runAction);
  runManager->SetUserAction( eventAction );

  nDetSteppingAction* steppingAction = 
	new nDetSteppingAction(detector, runAction, eventAction);
  runManager->SetUserAction(steppingAction);
  
  nDetStackingAction* stackingAction = new nDetStackingAction(runAction);
  runManager->SetUserAction(stackingAction);

  nDetTrackingAction*  trackingAction = new nDetTrackingAction();
  runManager->SetUserAction(trackingAction);

//So we do this instead K Schmitt 6/16/16
//  runManager->SetUserInitialization(new nDetActionInitialization());
//end of Kyle's changes

  // Initialize G4 kernel
  runManager->Initialize();
  
  // get the pointer to the UI manager and set verbosities
  G4UImanager *UImanager = G4UImanager::GetUIpointer();

  if (argc==1)   // Define UI session for interactive mode
    {
#ifdef G4UI_USE
      G4UIExecutive * ui;
      ui = new G4UIExecutive(argc,argv,"");
#ifdef G4VIS_USE
      UImanager->ApplyCommand("/control/execute ./mac/vis.mac");
#endif
      // start interactive session
      ui->SessionStart();
      delete ui;
#endif
    }
  else         // Batch mode
    {
      G4String command = "/control/execute ";
      G4String fileName = argv[1];
      UImanager->ApplyCommand(command+fileName);
    }
 
  // job termination
#ifdef G4VIS_USE
  delete visManager;
#endif
  delete runManager;
    //std::cout<<"runManager is deleted"<<std::endl;
  //delete verbosity;
  
  return 0;
}//END of main() function
