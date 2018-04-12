//
// Created by David Pérez Loureiro on 12/7/17.
//

#include "nDetUserEventInformation.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nDetUserEventInformation::nDetUserEventInformation()
        :fDetections(0),fAbsortions(0){}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nDetUserEventInformation::~nDetUserEventInformation() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nDetUserEventInformation::Print() const {

    G4cout<<"nDetUserEventInformation::Print()-> Total Number of Detections:"<<GetDetectionCount()<<G4endl;
    G4cout<<"nDetUserEventInformation::Print()-> Total Number of Absorptions:"<<GetAbsortionCount()<<G4endl;

}