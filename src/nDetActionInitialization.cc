//
// Created by David Pérez Loureiro on 12/11/17.
//

#include "nDetActionInitialization.hh"


#include "nDetRunAction.hh"
#include "nDetPrimaryGeneratorAction.hh"
#include "nDetEventAction.hh"
#include "nDetStackingAction.hh"
#include "nDetTrackingAction.hh"
#include "nDetSteppingAction.hh"
#include "nDetConstruction.hh"

nDetActionInitialization::nDetActionInitialization(nDetConstruction *detector) : G4VUserActionInitialization(), fDetectorConstruction(detector) {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nDetActionInitialization::~nDetActionInitialization() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void nDetActionInitialization::BuildForMaster() const {

    SetUserAction(new nDetRunAction);

}


void nDetActionInitialization::Build() const{

    nDetRunAction *theRunAction=new nDetRunAction;

    SetUserAction(theRunAction);
    SetUserAction(new nDetPrimaryGeneratorAction(theRunAction));
    nDetEventAction *theEventAction=new nDetEventAction(theRunAction);
    SetUserAction(theEventAction);
    SetUserAction(new nDetTrackingAction);
    SetUserAction(new nDetStackingAction(theRunAction));
    SetUserAction(new nDetSteppingAction(fDetectorConstruction,theRunAction,theEventAction));
}