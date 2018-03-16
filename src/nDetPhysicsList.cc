//The neutronDetector Physics List

#include "nDetPhysicsList.hh"
#include "nDetPhysicsMessenger.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4HadronElasticPhysicsHP.hh"
#include "G4HadronPhysicsQGSP_BERT_HP.hh"
#include "G4StoppingPhysics.hh"
#include "G4IonPhysics.hh"
#include "G4OpticalPhysics.hh"

nDetPhysicsList::nDetPhysicsList() :QGSP_BERT_HP() {

    fPhysicsMessenger = new nDetPhysicsMessenger(this);

    useOpticalPhotons = false;
    useScintillationByPID = true;

}

nDetPhysicsList::~nDetPhysicsList() {
    delete fPhysicsMessenger;
}



void nDetPhysicsList::AddOpticalPhysics() {

    if(useOpticalPhotons) {
        G4cout<<"nDetPhysicsList::AddOpticalPhysics()->Enabled "<<G4endl;
        G4OpticalPhysics *theOpticalPhysics= new G4OpticalPhysics;
        RegisterPhysics(theOpticalPhysics);
        theOpticalPhysics->SetScintillationByParticleType(useScintillationByPID);
    }
}

void nDetPhysicsList::SetCuts() {
    SetCutsWithDefault();
}
