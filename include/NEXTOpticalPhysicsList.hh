//
// Created by David Pérez Loureiro on 6/1/18.
//

#ifndef NEXTSIM_NEXTOPTICALPHYSICSLIST_HH
#define NEXTSIM_NEXTOPTICALPHYSICSLIST_HH



/** \file NEXTOpticalPhysicsList
 *  \author D. Perez Loureiro
 *  \date 03/02/2018
 *
 */

#include <G4OpticalPhysics.hh>

/** \class NEXTOpticalPhysicsList
 *  \brief Optical Physics List adapted from the G4OpticsPhysics
 *  Adds Pulse shape discrimination
 *
 */
class NEXTOpticalPhysicsList :public G4OpticalPhysics {

public:
    NEXTOpticalPhysicsList();
    ~NEXTOpticalPhysicsList();
    void ConstructParticle();
    void ConstructProcess();


};

#endif //NEXTSIM_NEXTOPTICALPHYSICSLIST_HH
