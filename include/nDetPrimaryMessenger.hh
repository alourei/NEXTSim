//
// Created by David Pérez Loureiro on 7/11/18.
//

#ifndef NEXTSIM_NDETPRIMARYMESSENGER_HH
#define NEXTSIM_NDETPRIMARYMESSENGER_HH

#include "G4UImessenger.hh"
#include "globals.hh"

class nDetPrimaryGeneratorAction;

class G4UIcommand;
class G4UIcmdWithABool;
class G4UIcmdWithAString;
class G4UIcmdWithADouble;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;

class nDetPrimaryMessenger: public G4UImessenger {

public:

    /**
     * Default constructor
     * @param [in]: thePrimaryAction pointer to the Primary Generator Action
     */
    nDetPrimaryMessenger(nDetPrimaryGeneratorAction *thePrimaryAction);
    /**
     * Default destructor
     */
    virtual ~nDetPrimaryMessenger();
    /**
     * Sets the new values for the given command
     * @param [in]: command pointer to the G4UIcommand
     * @param [in]: newValue  string that contains the new values to set
     */
    virtual void SetNewValue(G4UIcommand* command,G4String newValue);
private:

    nDetPrimaryGeneratorAction *fPrimaryAction; ///< Pointer to the primary Action
    G4UIdirectory*    fPrimaryDir; ///< Pointer to the Command Directory
    G4UIcmdWithAString *fGeneratorTypeCmd; ///< Pointer to the Command

};


#endif //NEXTSIM_NDETPRIMARYMESSENGER_HH
