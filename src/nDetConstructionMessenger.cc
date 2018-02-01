//
// Created by David Pérez Loureiro on 1/31/17.
//

#include "nDetConstructionMessenger.hh"

#include "nDetConstruction.hh"
#include "G4UIcommand.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
nDetConstructionMessenger::nDetConstructionMessenger(nDetConstruction* detector)
        :fDetector(detector){

    fDetectorDir=new G4UIdirectory("/nDet/detector/");
    fDetectorDir->SetGuidance("Detector geometry control");

    fGeometryCmd=new G4UIcmdWithAString("/nDet/detector/setGeometry",this);
    fGeometryCmd->SetGuidance("Defines the Geometry of the detector");
    fGeometryCmd->SetGuidance("Default is the disk");
    fGeometryCmd->SetCandidates("disk hexagon ellipse rectangle array bent");
    fGeometryCmd->SetParameterName("geometry",true);
    fGeometryCmd->SetDefaultValue("disk");
    fGeometryCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fSiliconDimensionsCmd=new G4UIcmdWithADoubleAndUnit("/nDet/detector/setSiPMdimensions",this);
    fSiliconDimensionsCmd->SetGuidance("Defines the size of the SiPMs (default mm)");
    fSiliconDimensionsCmd->SetDefaultUnit("mm");

    fDetectorLengthCmd=new G4UIcmdWithADoubleAndUnit("/nDet/detector/setDetectorLength",this);
    fDetectorLengthCmd->SetGuidance("Defines the size of the plastic (default cm)");
    fDetectorLengthCmd->SetDefaultUnit("cm");

    fDetectorWidthCmd=new G4UIcmdWithADoubleAndUnit("/nDet/detector/setDetectorWidth",this);
    fDetectorWidthCmd->SetGuidance("Defines the width of the plastic (default cm)");
    fDetectorWidthCmd->SetDefaultUnit("cm");

    fDetectorThicknessCmd=new G4UIcmdWithADoubleAndUnit("/nDet/detector/setDetectorThickness",this);
    fDetectorThicknessCmd->SetGuidance("Defines the thickness of the plastic (default mm)");
    fDetectorThicknessCmd->SetDefaultUnit("mm");

    fMylarThicknessCmd=new G4UIcmdWithADoubleAndUnit("/nDet/detector/setMylarThickness",this);
    fMylarThicknessCmd->SetGuidance("Defines the thickness of mylar the mylar (default mm, 0 for no mylar)");
    fMylarThicknessCmd->SetDefaultUnit("mm");

    fTrapezoidLengthCmd=new G4UIcmdWithADoubleAndUnit("/nDet/detector/setTrapezoidLength",this);
    fTrapezoidLengthCmd->SetGuidance("Defines the length of the trapezoidal part of ellipse (default cm)");
    fTrapezoidLengthCmd->SetDefaultUnit("cm");

    fUpdateCmd=new G4UIcommand("/nDet/detector/update",this);
    fUpdateCmd->SetGuidance("Updates the detector Geometry");
    //std::cout<<"nDetConstructionMessenger::nDetConstructionMessenger()->"<<fGeometryCmd<<std::endl;

    fDistanceCmd=new G4UIcmdWithADoubleAndUnit("/nDet/detector/setDistance",this);
    fDistanceCmd->SetGuidance("Defines the distance between the detector and the origin for curved geometries (default cm)");
    fDistanceCmd->SetDefaultUnit("cm");

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

    delete fDistanceCmd;

    //G4cout<<"nDetConstructionMessenger::~nDetConstructionMessenger()->"<<fGeometryCmd<<G4endl;
}

void nDetConstructionMessenger::SetNewValue(G4UIcommand* command,G4String newValue){

    if(command == fGeometryCmd){
        fDetector->SetGeometry(newValue);
    }

    if(command == fSiliconDimensionsCmd) {
        G4double dimensions=fSiliconDimensionsCmd->ConvertToDimensionedDouble(newValue);
        fDetector->SetSiPM_dimension(dimensions/2);
    }

    if(command == fDetectorLengthCmd) {
        G4double length=fDetectorLengthCmd->ConvertToDimensionedDouble(newValue);
        fDetector->SetDetectorLength(length);
    }

    if(command == fDetectorWidthCmd) {
        G4double length=fDetectorWidthCmd->ConvertToDimensionedDouble(newValue);
        fDetector->SetDetectorWidth(length);
    }

    if(command == fDetectorThicknessCmd) {
        G4double thickness=fDetectorThicknessCmd->ConvertToDimensionedDouble(newValue);
        fDetector->SetDetectorThickness(thickness);
    }


    if(command == fTrapezoidLengthCmd) {
        G4double length=fTrapezoidLengthCmd->ConvertToDimensionedDouble(newValue);
        fDetector->SetTrapezoidLength(length);
    }

    if(command == fMylarThicknessCmd) {
        G4double val=fMylarThicknessCmd->ConvertToDimensionedDouble(newValue);
        fDetector->SetMylarThickness(val);
    }

    if(command == fUpdateCmd){
       fDetector->UpdateGeometry();
    }

    if(command == fDistanceCmd){
        G4double val =fDistanceCmd->ConvertToDimensionedDouble(newValue);
        fDetector->SetDistance(val);
    }
}
