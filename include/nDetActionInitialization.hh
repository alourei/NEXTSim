//
// Created by David Pérez Loureiro on 12/11/17.
//

#ifndef NEXTMULTIPLESCATTERING_NDETACTIONINITIALIZATION_HH
#define NEXTMULTIPLESCATTERING_NDETACTIONINITIALIZATION_HH

#endif //NEXTMULTIPLESCATTERING_NDETACTIONINITIALIZATION_HH

#include "G4VUserActionInitialization.hh

class nDetConstruction;
class nDetActionInitialization : public G4VUserActionInitialization{

public:
    nDetActionInitialization(nDetConstruction *detector);
    ~nDetActionInitialization();
    virtual void BuildForMaster() const;
    virtual void Build();

private:

    nDetConstruction *fDetectorConstruction;


};