//
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
//
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/// \file nDetPhysicsList.hh
/// \class nDetPhysicsList
/// \brief Definition of the PhysicsList for NEXTsim
/// \author David Perez Loureiro


#ifndef NEXTMULTIPLESCATTERING_NDETPHYSICSLIST_HH
#define NEXTMULTIPLESCATTERING_NDETPHYSICSLIST_HH


#include "G4VModularPhysicsList.hh"
#include "G4OpticalPhysics.hh"
#include "QGSP_BERT_HP.hh"

class nDetPhysicsMessenger;


class nDetPhysicsList: public QGSP_BERT_HP {

public:

    /**
     * Default Constructor
     */
    nDetPhysicsList();
    /**
     * Default destructor
     */
    virtual ~nDetPhysicsList();
    virtual void SetCuts();
    /** Enables/Disables the Optical Photon Emission in the scintillator Material
     * \param [in] value: true/false for enable/disable
    */
    void EnableOptical(G4bool value = true){useOpticalPhotons = value;}
    /** Enables/Disables different scintillation by Particle type
     * \param [in] value: true/false for enable/disable
     */
    void EnableScintByPID(G4bool value = true){useScintillationByPID = value;}

    void AddOpticalPhysics();


private:
    nDetPhysicsMessenger *fPhysicsMessenger; ///< Pointer to the Physics Messenger
    G4bool useOpticalPhotons;                ///< Flag for Optical Photons
    G4bool useScintillationByPID;            ///< Flag for different scintillation by Particle type
    G4bool usePIDScintillation;              ///< Flag for different scintillation by Particle type for PID purposes

};

#endif //NEXTMULTIPLESCATTERING_NDETPHYSICSLIST_HH
