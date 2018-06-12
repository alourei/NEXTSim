//The neutronDetector Physics List

#include "nDetPhysicsList.hh"
#include "nDetPhysicsMessenger.hh"
#include "G4Scintillation.hh"
#include "G4VUserPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4HadronElasticPhysicsHP.hh"
#include "G4HadronPhysicsQGSP_BERT_HP.hh"
#include "G4StoppingPhysics.hh"
#include "G4IonPhysics.hh"
#include "G4OpticalPhysics.hh"
#include "NEXTOpticalPhysicsList.hh"
nDetPhysicsList::nDetPhysicsList() :QGSP_BERT_HP() {

    fPhysicsMessenger = new nDetPhysicsMessenger(this);

    useOpticalPhotons = true;
    useScintillationByPID = true;
    usePIDScintillation = true;


}

nDetPhysicsList::~nDetPhysicsList() {
    delete fPhysicsMessenger;
}



void nDetPhysicsList::AddOpticalPhysics() {

    if(useOpticalPhotons&&!usePIDScintillation) {
        G4cout << "nDetPhysicsList::AddOpticalPhysics()->Enabled " << G4endl;
        G4OpticalPhysics *theOpticalPhysics = new G4OpticalPhysics;
        RegisterPhysics(theOpticalPhysics);
        theOpticalPhysics->SetScintillationByParticleType(useScintillationByPID);
    }
    if(useOpticalPhotons&&usePIDScintillation){

        G4cout << "nDetPhysicsList::AddOpticalPhysics()->NEXT Enabled " << G4endl;


        NEXTOpticalPhysicsList *theOpticalPhysics= new NEXTOpticalPhysicsList();
        RegisterPhysics(theOpticalPhysics);
        theOpticalPhysics->SetScintillationByParticleType(useScintillationByPID);

    }

}


void nDetPhysicsList::SetCuts() {
    SetCutsWithDefault();
}



