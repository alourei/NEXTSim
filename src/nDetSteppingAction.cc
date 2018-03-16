//
// $Id: nDetSteppingAction.hh,v 1.0 Sept., 2015 $
// by Dr. Xiaodong Zhang
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "nDetSteppingAction.hh"

//#include "nDetConstruction.hh"
//#include "nDetEventAction.hh"
#include "nDetSD.hh"
#include "G4Step.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4OpAbsorption.hh"
#include "G4ProcessManager.hh"
#include "G4SDManager.hh"
#include "G4UnitsTable.hh"
#include "nDetUserTrackingInformation.hh"
#include "nDetUserEventInformation.hh"
#include "G4ParticleDefinition.hh"
#include "G4Alpha.hh"
#include "G4Electron.hh"
#include "G4Gamma.hh"
#include "G4Neutron.hh"
#include "G4Triton.hh"
#include "G4EventManager.hh"
#define DEBUG 0

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nDetSteppingAction::nDetSteppingAction( 
					nDetConstruction* det,
					nDetRunAction* runAct,
                                        nDetEventAction* evtAct)
//:runAction(runAct), evtAction(evtAct)
:detector(det), runAction(runAct), evtAction(evtAct)
{

  eventID = -1;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nDetSteppingAction::~nDetSteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nDetSteppingAction::UserSteppingAction(const G4Step* aStep)
{

  // collect energy step by step only if 
  // the energy deposited in the CsI are recorded.
  // used for debug...
  //G4cout<<aStep->GetTrack()->GetVolume()->GetName()<<G4endl;


  //Print the Secondaries information
    const std::vector<const G4Track *> *theSecondaries=aStep->GetSecondaryInCurrentStep();

    G4int size=theSecondaries->size();

/*
    for (G4int i=0;i<size;i++) {

        G4Track *theTrack = (G4Track *) (theSecondaries)->at(i);

        if (theTrack->GetParentID() == 2) {

            G4cout << "Secondary created " << theTrack->GetDefinition()->GetParticleName() << G4endl
                   << "Process Name " << theTrack->GetCreatorProcess()->GetProcessName() << G4endl;
        }
    }
*/

  G4String name = aStep->GetTrack()->GetMaterial()->GetName();

    if (aStep->GetTrack()->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition() && name == "G4_AIR") {

        aStep->GetTrack()->SetTrackStatus(fStopAndKill);

    //    G4cout << "Transmitted Optical Photon Track Killed" << G4endl;
    }


    nDetUserTrackingInformation *theTrackingInfo;
    theTrackingInfo = static_cast<nDetUserTrackingInformation*>( aStep->GetTrack()->GetUserInformation());

    nDetUserEventInformation *theEventInfo;
    theEventInfo = static_cast<nDetUserEventInformation*>(G4EventManager::GetEventManager()->GetUserInformation());


  if( (name.find("EJ") != name.npos ) && aStep->GetTotalEnergyDeposit() > 0 ){
    G4double edep = aStep->GetTotalEnergyDeposit();

//Xiaodong says we can put some code here.  GetParticleName 
//step->track->particlename

  //  G4String pname = aStep->GetTrack()->GetParticleDefinition()->GetParticleName();
  //  G4cout << pname << G4endl;

    /* 
    G4cout<<G4BestUnit(edep,"Energy")<<"**";
    G4cout<<aStep->GetTrack()->GetMaterial()->GetName()<<G4endl;
    */
    evtAction->AddDepE(edep);
  }

  // collect detected photons in the siPM
  G4OpBoundaryProcessStatus boundaryStatus=Undefined;
  G4OpBoundaryProcess* boundary=NULL;
  if(!boundary) {
      G4ProcessManager *pm
              = aStep->GetTrack()->GetDefinition()->GetProcessManager();
      G4int nprocesses = pm->GetProcessListLength();
      G4ProcessVector *pv = pm->GetProcessList();
      G4int i;
      for (i = 0; i < nprocesses; i++) {
          if ((*pv)[i]->GetProcessName() == "OpBoundary") {
              boundary = (G4OpBoundaryProcess *) (*pv)[i];
              //G4cout<<boundary->GetStatus()<<G4endl;
              break;
          }
      }

      if (i < nprocesses) {
          boundaryStatus = boundary->GetStatus();
          if (aStep->GetPostStepPoint()->GetStepStatus() == fGeomBoundary) {

              switch (boundaryStatus) {
                  case Detection: {
                      //Trigger sensitive detector manually since photon is
                      //absorbed but status was Detection
                      G4SDManager *SDman = G4SDManager::GetSDMpointer();
                      G4String sdName = "/theSiPMSD";
                      SiPMSD *sipmSD = (SiPMSD *) SDman->FindSensitiveDetector(sdName);
                      if (sipmSD && sipmSD->isActive())
                          sipmSD->ProcessHits_constStep(aStep, NULL);
                      G4String vName = aStep->GetPostStepPoint()->GetPhysicalVolume()->GetName();
                      G4double time = aStep->GetPostStepPoint()->GetGlobalTime();
                      //G4cout<<"Detect one photon in SiPM"<< vName<<" Global time: "<<time<<" at the position of "<<aStep->GetPostStepPoint()->GetPosition().x()<<G4endl;
                      //G4cout<<"Detection in "<<vName<<G4endl;
                      theTrackingInfo->IncDetections();
                      theEventInfo->IncDetections();
                      if (vName.find("psSiPM") && aStep->GetPostStepPoint()->GetPosition().z() > 0) {
                          runAction->vTimeOfPhotonInSD1PushBack(time);
                          runAction->vSD1PhotonPositionXPushBack(aStep->GetPostStepPoint()->GetPosition().x());
                          runAction->vSD1PhotonPositionYPushBack(aStep->GetPostStepPoint()->GetPosition().y());
                          runAction->vSD1PhotonPositionZPushBack(aStep->GetPostStepPoint()->GetPosition().z());
                      }
                      if (vName.find("psSiPM") && aStep->GetPostStepPoint()->GetPosition().z() < 0) {
                          runAction->vTimeOfPhotonInSD2PushBack(time);
                          runAction->vSD2PhotonPositionXPushBack(aStep->GetPostStepPoint()->GetPosition().x());
                          runAction->vSD2PhotonPositionYPushBack(aStep->GetPostStepPoint()->GetPosition().y());
                          runAction->vSD2PhotonPositionZPushBack(aStep->GetPostStepPoint()->GetPosition().z());
                      }
                      break;
                  }
                  case FresnelReflection:
                  case TotalInternalReflection:
                  case LambertianReflection:
                  case LobeReflection:
                  case SpikeReflection:
                  case BackScattering: {
                      //G4cout << "Reflection of "<<aStep->GetTrack()->GetParticleDefinition()->GetParticleName()<<
                       //                         " in " << aStep->GetPostStepPoint()->GetPhysicalVolume()->GetName() << G4endl;
                      theTrackingInfo->IncReflections();
                  }
                      break;
                  case Absorption: {
                      theTrackingInfo->IncAbsortions();
                      theEventInfo->IncAbsortions();
                      //G4cout<<"Absortion in "<<aStep->GetPostStepPoint()->GetPhysicalVolume()->GetName()
                      //      <<" "<<theEventInfo->GetAbsortionCount()<<G4endl;
                    break;
                    }
                  default:
                      //G4cout<<"Other Boundary effect in "<<aStep->GetPostStepPoint()->GetPhysicalVolume()->GetName()
                      //     <<" "<<boundaryStatus<<G4endl;
                    break;

              }
          }
      }

  }
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



