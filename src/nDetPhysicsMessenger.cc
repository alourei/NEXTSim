//
// Created by David Pérez Loureiro on 2/19/18.
//

#include "nDetPhysicsMessenger.hh"

#include "nDetPhysicsList.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcommand.hh"

nDetPhysicsMessenger::nDetPhysicsMessenger(nDetPhysicsList *thePhysicsList):
        fPhysicsList(thePhysicsList){

    G4cout<<"nDetPhysicsMessenger::nDetPhysicsMessenger()"<<G4endl;
    fPhysicsDir = new G4UIdirectory("/nDet/phys/");
    fPhysicsDir->SetGuidance("Physics List control");

    fUseOpticalCmd = new G4UIcmdWithABool("/nDet/phys/EnableOpticalPhotons",this);
    fUseOpticalCmd->SetGuidance("Enables/Disables the Optical Photon Emission in the scintillator Material");
    fUseOpticalCmd->SetDefaultValue("true");
    fUseOpticalCmd->AvailableForStates(G4State_PreInit);

    fUseScintbyPIDCmd =new G4UIcmdWithABool("/nDet/phys/EnableScintillationByParticleType",this);
    fUseScintbyPIDCmd->SetGuidance("Enables/Disables different scintillation by Particle type");
    fUseScintbyPIDCmd->SetDefaultValue("true");
    //fUseScintbyPIDCmd->AvailableForStates(G4State_PreInit,G4State_Init);
}

nDetPhysicsMessenger::~nDetPhysicsMessenger(){

    G4cout<<"nDetPhysicsMessenger::~nDetPhysicsMessenger()"<<G4endl;
    delete fPhysicsDir;
    delete fUseOpticalCmd;
    delete fUseScintbyPIDCmd;

}


void nDetPhysicsMessenger::SetNewValue(G4UIcommand* command,G4String newValue){

if(command == fUseOpticalCmd){
G4bool value = fUseOpticalCmd->GetNewBoolValue(newValue);
fPhysicsList->EnableOptical(value);
fPhysicsList->AddOpticalPhysics();
}
if(command == fUseScintbyPIDCmd){
G4bool value = fUseOpticalCmd->GetNewBoolValue(newValue);
fPhysicsList->EnableScintByPID(value);
}
}