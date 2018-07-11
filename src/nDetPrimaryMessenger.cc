//
// Created by David Pérez Loureiro on 7/11/18.
//

#include "nDetPrimaryMessenger.hh"

#include "nDetPrimaryGeneratorAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcommand.hh"

nDetPrimaryMessenger::nDetPrimaryMessenger(nDetPrimaryGeneratorAction *theAction) : fPrimaryAction(theAction) {

    G4cout << "nDetPrimaryMessenger::nDetPrimaryMessenger()" << G4endl;
    fPrimaryDir = new G4UIdirectory("/nDet/primary/");
    fPrimaryDir->SetGuidance("Primary Generator Action control");

    fGeneratorTypeCmd = new G4UIcmdWithAString("/nDet/primary/setSourceType", this);
    fGeneratorTypeCmd->SetGuidance("Set the type of Primary Generator");
    fGeneratorTypeCmd->SetDefaultValue("gun");
    fGeneratorTypeCmd->SetCandidates("gun gps decay");
    fGeneratorTypeCmd->AvailableForStates(G4State_PreInit,G4State_Init,G4State_Idle);

}



nDetPrimaryMessenger::~nDetPrimaryMessenger(){

    G4cout<<"nDetPrimaryMessenger::~nDetPrimaryMessenger()"<<G4endl;
    delete fPrimaryDir;
    delete fGeneratorTypeCmd;

}

void nDetPrimaryMessenger::SetNewValue(G4UIcommand* command,G4String newValue){


    if (command == fGeneratorTypeCmd)
        fPrimaryAction->SetGeneratorType(newValue);
    G4cout<<"nDet/primary/setSourceType-> "<<newValue<<G4endl;

    return;
}