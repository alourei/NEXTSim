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

nDetPhysicsList::nDetPhysicsList() :QGSP_BERT_HP() {

    fPhysicsMessenger = new nDetPhysicsMessenger(this);

    useOpticalPhotons = false;
    useScintillationByPID = true;
    usePIDScintillation = true;


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

    if(usePIDScintillation){

        G4PhysicsListHelper *ph = G4PhysicsListHelper::GetPhysicsListHelper();


        G4Scintillation *theProtonScintillation= new G4Scintillation("Scintillation_proton");
        theProtonScintillation->SetScintillationExcitationRatio(0.493);

        G4Scintillation *theIonScintillation= new G4Scintillation("Scintillation_ion");
        theIonScintillation->SetScintillationExcitationRatio(0.493);

        G4Proton* theproton = G4Proton::Definition();
        G4GenericIon *theIon= G4GenericIon::Definition();

        ph->RegisterProcess(theProtonScintillation,theproton);

        ph->RegisterProcess(theIonScintillation,theIon);

    }

    }


}


void nDetPhysicsList::SetCuts() {
    SetCutsWithDefault();
}


