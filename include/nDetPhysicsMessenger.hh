//
// Created by David Pérez Loureiro on 2/19/18.
//

/** \file nDetPhyicsMessenger
 *  \author David Perez Loureiro
 *  \class nDetPhysicsMessenger
 *  \brief Messenger to the nDetPhysicsList class
 */


#ifndef NEXTMULTIPLESCATTERING_NDETPHYSICSMESSENGER_HH
#define NEXTMULTIPLESCATTERING_NDETPHYSICSMESSENGER_HH

#include "G4UImessenger.hh"
#include "globals.hh"

class nDetPhysicsList;

class G4UIcommand;
class G4UIcmdWithABool;
class G4UIcmdWithAString;
class G4UIcmdWithADouble;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;


class nDetPhysicsMessenger: public G4UImessenger  {

public:
    /**
     * Default constructor
     * @param [in]: thePhysicsList pointer to the Physics List
     */
    nDetPhysicsMessenger(nDetPhysicsList *thePhysicsList);
    /**
     * Default Destructor
     */
    virtual ~nDetPhysicsMessenger();
    /**
     * Sets the new values for the given command
     * @param [in]: command pointer to the G4UIcommand
     * @param [in]: newValue  string that contains the new values to set
     */
    virtual void SetNewValue(G4UIcommand* command,G4String newValue);

private:
    nDetPhysicsList*  fPhysicsList;   ///< Pointer to the physics list
    G4UIdirectory*    fPhysicsDir;    ///< Pointer to the Command Directory
    G4UIcmdWithABool* fUseOpticalCmd; ///< Pointer to the command
    G4UIcmdWithABool* fUseScintbyPIDCmd; ///< Pointer to the command

};


#endif //NEXTMULTIPLESCATTERING_NDETPHYSICSMESSENGER_HH
