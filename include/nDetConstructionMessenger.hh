//
// Created by David Pérez Loureiro on 1/31/17.
//

#ifndef NEXTMULTIPLESCATTERING_NDETCONSTRUCTIONMESSENGER_HH
#define NEXTMULTIPLESCATTERING_NDETCONSTRUCTIONMESSENGER_HH 1


#include "G4UImessenger.hh"
#include "globals.hh"


class nDetConstruction;
class G4UIcommand;
class G4UIcmdWithABool;
class G4UIcmdWithAString;
class G4UIcmdWithADouble;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class nDetConstructionMessenger:public G4UImessenger
{
public:

//Constructor
nDetConstructionMessenger(nDetConstruction*);
//Destructor
virtual ~nDetConstructionMessenger();

virtual void SetNewValue(G4UIcommand*,G4String);

private:

    nDetConstruction* fDetector;
    G4UIdirectory*    fDetectorDir;

    G4UIcmdWithAString*  fGeometryCmd;
    G4UIcmdWithADouble *fSiliconDimensionsCmd;
    G4UIcmdWithADouble *fDetectorLengthCmd;
    G4UIcmdWithADouble *fDetectorWidthCmd;
    G4UIcmdWithADouble *fDetectorThicknessCmd;
    G4UIcmdWithADouble *fTrapezoidLengthCmd;
    G4UIcmdWithADouble *fMylarThicknessCmd;
    G4UIcmdWithADoubleAndUnit *fDistanceCmd;
    G4UIcommand*         fUpdateCmd;

};


#endif //NEXTMULTIPLESCATTERING_NDETCONSTRUCTIONMESSENGER_HH
