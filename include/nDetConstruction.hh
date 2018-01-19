//
// $Id: nDetConstruction.hh,v 1.0 Sept., 2015 $
//  Written by Dr. Xiaodong Zhang
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef nDetConstruction_h
#define nDetConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

#include "nDetSD.hh"

#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4Element.hh"
#include "G4Isotope.hh"
#include "G4ElementTable.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Polyhedra.hh"
#include "G4Trap.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"
#include "G4PVPlacement.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4PVParameterised.hh"
#include "G4VNestedParameterisation.hh"

#include "G4SubtractionSolid.hh"

#include "nDetConstructionMessenger.hh"


// Replica 
// Assembly volumes
// no assembly is used currently
#include "G4AssemblyVolume.hh"
#include "SiPMSD.hh"
#include "nDetSD.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class nDetConstruction : public G4VUserDetectorConstruction
{
  public:
    nDetConstruction();
   ~nDetConstruction();

  public:
    G4VPhysicalVolume* Construct();
    G4VPhysicalVolume* ConstructDetector();
    virtual void ConstructSDandField();
    void SetGeometry(G4String geom){fGeometry=geom;}
    void SetSiPM_dimension(G4double dim){SiPM_dimension=dim;}
    void SetDetectorLength(G4double val){fDetectorLength=val;}
    void SetTrapezoidLength(G4double val){fTrapezoidLength=val;}
    void SetDetectorThickness(G4double val){fDetectorThickness=val;}
    void SetMylarThickness(G4double val){fMylarThickness=val;}
    void SetDetectorWidth(G4double val){fDetectorWidth=val;}
    void SetHexagonRadius(G4double val){fHexagonRadius=val;}

    G4String GetGeometry(){return fGeometry;}
    void UpdateGeometry();


private:

    nDetConstructionMessenger *fDetectorMessenger;
    // data of detector structure; half of size
    G4double expHallX;		// width
    G4double expHallY;		// length
    G4double expHallZ;		// thickness

    G4double assemblyBoxX;
    G4double assemblyBoxY;
    G4double assemblyBoxZ;

    G4double assemblyPx;
    G4double assemblyPy;
    G4double assemblyPz;

    G4double ej200X;
    G4double ej200Y;
    G4double ej200Z;

    G4double greaseX;
    G4double greaseY;
    G4double greaseZ;

    G4double qwSiPMx;
    G4double qwSiPMy;
    G4double qwSiPMz;

    G4double psSiPMx;
    G4double psSiPMy;
    G4double psSiPMz;

    G4double SiPM_dimension;
    G4double fTeflonThickness;
    G4double fMylarThickness;
    G4double fDetectorLength;
    G4double fDetectorThickness;
    G4double fDetectorWidth;
    G4double fTrapezoidLength;
    G4double fHexagonRadius;

    G4int fNdetectors;

    G4bool fCheckOverlaps;
    G4String fGeometry;

    // logical and physical volume
    G4LogicalVolume* expHall_logV;
    G4LogicalVolume* assembly_logV;

    G4LogicalVolume* ej200_logV;    // ej200 scintillator
    G4LogicalVolume *mylar_logV;
    G4LogicalVolume* grease_logV;
    G4LogicalVolume* qwSiPM_logV;
    G4LogicalVolume* psSiPM_logV;

    G4VPhysicalVolume* expHall_physV;
    G4VPhysicalVolume* assembly_physV;

    SiPMSD *fSiPMSD;
    nDetSD *fScintSD;

    //Materials and elements

    G4Element* fH;
    G4Element* fC;
    G4Element* fO;
    G4Element* fF;
    G4Element* fSi;
    G4Element* fAl;

    G4Material* fAir;
    G4Material* fTeflon;
    G4Material* fEJ200;
    G4Material *fEJ299;
    G4Material* fGrease;
    G4Material* fSiO2;
    G4Material* fSil;
    G4Material* fMylar;

    //Material table properties
    G4MaterialPropertiesTable* fAirMPT;
    G4MaterialPropertiesTable* fTeflonMPT;
    G4MaterialPropertiesTable* fEJ200MPT;
    G4MaterialPropertiesTable* fEJ299MPT;
    G4MaterialPropertiesTable* fGreaseMPT;
    G4MaterialPropertiesTable* fSiO2MPT;
    G4MaterialPropertiesTable* fSilMPT;
    G4MaterialPropertiesTable* fMylarMPT;

    //Optical Surfaces
    G4OpticalSurface* fTeflonOpticalSurface;
    G4OpticalSurface* fSiliconPMOpticalSurface;
    G4OpticalSurface* fMylarOpticalSurface;

    //Logical Skins

    G4LogicalSkinSurface* fWrapSkinSurface;
    G4LogicalSkinSurface* fSiPMSkinSurface;
    G4LogicalBorderSurface* fMylarSurface;



    // member functions
    void buildExpHall();
    void buildAssembly();
    void buildDisk();
    void buildDisk2();
    void buildEllipse();
    void buildEllipse2();
    void buildRectangle();
    void buildArray();
    void buildCylinder();
    G4AssemblyVolume* MakeSiPM();

    G4VSolid* ConstructEllipse(G4String name,G4ThreeVector dimensions,G4double thickness);

    G4VSolid* ConstructHexagon(G4String name,G4double radius,G4double thickness,G4ThreeVector Boxdimensions);
    G4VSolid* ConstructHexagon(G4String name,G4double radius,G4double thickness);
    G4VSolid* ConstructNextModule(G4String name,G4double length,G4double width1,G4double width2,G4double thickness);

    //G4LogicalVolume* ConstructArray(G4String name, G4int NDetectors);
    G4AssemblyVolume* ConstructArray(G4String name, G4int NDetectors);

    void DefineMaterials();


    void buildSiPMs();


};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif /*nDetConstruction_h*/
