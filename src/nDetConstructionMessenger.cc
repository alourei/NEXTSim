//
// Created by David Pérez Loureiro on 1/31/17.
//

#include "nDetConstructionMessenger.hh"

#include "nDetConstruction.hh"
#include "G4UIcommand.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
nDetConstructionMessenger::nDetConstructionMessenger(nDetConstruction* detector)
        :fDetector(detector){

    fDetectorDir=new G4UIdirectory("/nDet/detector/");
    fDetectorDir->SetGuidance("Detector geometry control");

    fGeometryCmd=new G4UIcmdWithAString("/nDet/detector/setGeometry",this);
    fGeometryCmd->SetGuidance("Defines the Geometry of the detector");
    fGeometryCmd->SetGuidance("Default is the disk");
    fGeometryCmd->SetCandidates("disk hexagon ellipse rectangle array");
    fGeometryCmd->SetParameterName("geometry",true);
    fGeometryCmd->SetDefaultValue("disk");
    fGeometryCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fSiliconDimensionsCmd=new G4UIcmdWithADouble("/nDet/detector/setSiPMdimensions",this);
    fSiliconDimensionsCmd->SetGuidance("Defines the size of the SiPMs in mm");

    fDetectorLengthCmd=new G4UIcmdWithADouble("/nDet/detector/setDetectorLength",this);
    fDetectorLengthCmd->SetGuidance("Defines the size of the plastic in cm");

    fDetectorWidthCmd=new G4UIcmdWithADouble("/nDet/detector/setDetectorWidth",this);
    fDetectorWidthCmd->SetGuidance("Defines the width of the plastic in cm");

    fDetectorThicknessCmd=new G4UIcmdWithADouble("/nDet/detector/setDetectorThickness",this);
    fDetectorThicknessCmd->SetGuidance("Defines the thickness of the plastic in mm");


    fMylarThicknessCmd=new G4UIcmdWithADouble("/nDet/detector/setMylarThickness",this);
    fMylarThicknessCmd->SetGuidance("Defines the thickness of  the mylar in mm (0 for no mylar)");


    fTrapezoidLengthCmd=new G4UIcmdWithADouble("/nDet/detector/setTrapezoidLength",this);
    fTrapezoidLengthCmd->SetGuidance("Defines the length of the trapezoidal part of ellipse in cm");

    fUpdateCmd=new G4UIcommand("/nDet/detector/update",this);
    fUpdateCmd->SetGuidance("Updates the detector Geometry");
    //std::cout<<"nDetConstructionMessenger::nDetConstructionMessenger()->"<<fGeometryCmd<<std::endl;

}

nDetConstructionMessenger::~nDetConstructionMessenger(){

    //G4cout<<"nDetConstructionMessenger::~nDetConstructionMessenger()->"<<fGeometryCmd<<G4endl;

    delete fDetectorDir;

    delete fSiliconDimensionsCmd;

    delete fGeometryCmd;

    delete fDetectorWidthCmd;

    delete fDetectorLengthCmd;

    delete fDetectorThicknessCmd;

    delete fTrapezoidLengthCmd;

    delete fMylarThicknessCmd;

    delete fUpdateCmd;

    //G4cout<<"nDetConstructionMessenger::~nDetConstructionMessenger()->"<<fGeometryCmd<<G4endl;
}

void nDetConstructionMessenger::SetNewValue(G4UIcommand* command,G4String newValue){

    if(command == fGeometryCmd){
        fDetector->SetGeometry(newValue);
    }

    if(command == fSiliconDimensionsCmd) {
        G4double dimensions=fSiliconDimensionsCmd->ConvertToDouble(newValue);
        fDetector->SetSiPM_dimension(dimensions/2.*mm);
    }

    if(command == fDetectorLengthCmd) {
        G4double length=fDetectorLengthCmd->ConvertToDouble(newValue);
        fDetector->SetDetectorLength(length*cm);
    }

    if(command == fDetectorWidthCmd) {
        G4double length=fDetectorWidthCmd->ConvertToDouble(newValue);
        fDetector->SetDetectorWidth(length*cm);
    }

    if(command == fDetectorThicknessCmd) {
        G4double thickness=fDetectorThicknessCmd->ConvertToDouble(newValue);
        fDetector->SetDetectorThickness(thickness*mm);
    }


    if(command == fTrapezoidLengthCmd) {
        G4double length=fTrapezoidLengthCmd->ConvertToDouble(newValue);
        fDetector->SetTrapezoidLength(length*cm);
    }

    if(command == fMylarThicknessCmd) {
        G4double val=fMylarThicknessCmd->ConvertToDouble(newValue);
        fDetector->SetMylarThickness(val*mm);
    }

    if(command == fUpdateCmd){

       fDetector->UpdateGeometry();
    }
}
