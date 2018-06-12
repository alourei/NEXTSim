//
// Created by David Pérez Loureiro on 6/1/18.
//

#include "NEXTOpticalPhysicsList.hh"
#include "G4OpticalPhoton.hh"
#include "G4Proton.hh"
#include "G4GenericIon.hh"
#include "G4Scintillation.hh"
#include "G4ProcessManager.hh"
NEXTOpticalPhysicsList::NEXTOpticalPhysicsList() : G4OpticalPhysics()
{;}

NEXTOpticalPhysicsList::~NEXTOpticalPhysicsList(){;}


void NEXTOpticalPhysicsList::ConstructParticle(){

    G4OpticalPhoton::OpticalPhotonDefinition();
    G4Proton::ProtonDefinition();
    G4GenericIon::GenericIonDefinition();
}


void NEXTOpticalPhysicsList::ConstructProcess() {

    G4OpticalPhysics::ConstructProcess();

    G4Scintillation *theProtonScintillation = new G4Scintillation("Scintillation_proton");
    theProtonScintillation->SetScintillationExcitationRatio(0.493);// Comrie et al. PoS(TIPP2014) 251
    theProtonScintillation->SetScintillationByParticleType(true);
    theProtonScintillation->SetTrackSecondariesFirst(true);

    G4ProcessManager *pManager = G4Proton::Definition()->GetProcessManager();


    G4ProcessVector *theProcessVector=pManager->GetProcessList();

    pManager->SetProcessOrdering((*theProcessVector)[9],idxAtRest,ordInActive);
    pManager->SetProcessOrdering((*theProcessVector)[9],idxPostStep,ordInActive);

    pManager->RemoveProcess(9);

    pManager->AddProcess(theProtonScintillation);

    pManager->SetProcessOrdering(theProtonScintillation,idxAtRest,ordLast);
    pManager->SetProcessOrdering(theProtonScintillation,idxPostStep,ordLast);


    //pManager->DumpInfo();


    G4Scintillation *theIonScintillation= new G4Scintillation("Scintillation_ion");

    theIonScintillation ->SetScintillationByParticleType(true);
    theIonScintillation->SetScintillationExcitationRatio(0.493);
    theIonScintillation->SetTrackSecondariesFirst(true);
    pManager= G4GenericIon::Definition()->GetProcessManager();

    theProcessVector=pManager->GetProcessList();


    pManager->SetProcessOrdering((*theProcessVector)[5],idxAtRest,ordInActive);
    pManager->SetProcessOrdering((*theProcessVector)[5],idxPostStep,ordInActive);


    pManager->RemoveProcess(5);

    pManager->AddProcess(theIonScintillation);

    pManager->SetProcessOrdering(theIonScintillation,idxAtRest,ordLast);
    pManager->SetProcessOrdering(theIonScintillation,idxPostStep,ordLast);



    //pManager->DumpInfo();

}
