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

/** \file nDetConstruction.hh
 *
 */

class  G4VisAttributes;
/** \class nDetConstruction
 *  \brief This class defines the geometry of the detector.
 *
 *  Defines the geometry of the detector
 */

class nDetConstruction : public G4VUserDetectorConstruction
{
  public:
  /** Default constructor */
    nDetConstruction();
  /** Default destructor */
    ~nDetConstruction();

  public:

    /// Constructs the Detector
    G4VPhysicalVolume* Construct();
    G4VPhysicalVolume* ConstructDetector();
    /// Constructs the Sensitive Detectors and Fields
    virtual void ConstructSDandField();
    /** Sets the geometry of the detectors
     *
     * @param [in] geom: the geometry type (disk,hexagon, ellipse, rectangle, array, bent currently available)
     */
    void SetGeometry(G4String geom){fGeometry=geom;}
    /** Sets the dimensions of the SiPMs
     *
     * @param [in] dim: the dimensions of the Silicon photomultiplier
     */
    void SetSiPM_dimension(G4double dim){SiPM_dimension=dim;}
    /** Sets the full length of the detector
     *
     * @param [in] length: the full length of the detector
     */
    void SetDetectorLength(G4double length){fDetectorLength=length;}
    /** Sets the length of the trapezoid
     *
     * @param [in] length: the length of the trapezoid
     */
    void SetTrapezoidLength(G4double val){fTrapezoidLength=val;}
    /** Sets the thickness of the plastic scintillator
     *
     * @param [in] thickness: the thickness of the scintillator
     */
    void SetDetectorThickness(G4double thickness){fDetectorThickness=thickness;}
    /** Sets the thickness of the mylar layer (0 means no mylar layer)
     *
     * @param [in] thickness: the thickness of the mylar
     */
    void SetTeflonThickness(G4double thickness){fTeflonThickness=thickness;}
    /** Sets the thickness of the teflon layer (0 means no mylar layer)
     *
     * @param [in] thickness: the thickness of the teflon
     */
    void SetMylarThickness(G4double thickness){fMylarThickness=thickness;}

    /** Sets the width of the detector
     *
     * @param [in] width: the detector width
     */
    void SetDetectorWidth(G4double width){fDetectorWidth=width;}
    /** Sets the radius of the hexagon for hexagonal geometries
     *
     * @param [in] radius: the radius of the hexagon
     */
    void SetHexagonRadius(G4double radius){fHexagonRadius=radius;}
    /** Sets the distance  between the source and the detector for the calculation of the angle for bent geometry
     *
     * @param [in] distance: the distance
     */
    void SetDistance(G4double distance){fDistance=distance;}
    /** Returns the Geometry type
     *
     * @return the String with the geometry type
     */
    G4String GetGeometry(){return fGeometry;}
    /** Returns the distance between the detector and the source for bent geometry
     *
     * @return the distance between detector and source
     */
    G4double GetDistance(){return fDistance;}
    /** Updates the geometry after setting new geometry parameters
     *
     */
    void UpdateGeometry();
    /** Sets the wrapping Material for the scintillator
     *
     * @param [in]  aMaterial: tha name of the wrapping material
     */
    void SetWrappingMaterial(G4String aMaterial){fWrappingMaterial = aMaterial;}
    /**
     *
     * @return the string with the wrapping material name
     */
    G4String GetWrappingMaterial(){ return fWrappingMaterial;}

    /** Sets the wrapping Material for the scintillator
      *
      * @param [in]  aMaterial: the name of the scintillator material
      */
    void SetScintillatorMaterial(G4String aMaterial){fScintillatorMaterial = aMaterial;}
    /** Returns the Wrapping Material
     *
     * @return the string with the scintillator material name
     */
    G4String GetScintillatorMaterial(){ return fScintillatorMaterial;}
    /** Sets the number of detectors per scintillator in the array
     *  @param [in] nDetectors: the number of detectors
     */
    void SetNDetectors(G4int nDetectors){ fNdetectors=nDetectors;}

private:

    nDetConstructionMessenger *fDetectorMessenger;
    // data of detector structure; half of size
    G4double expHallX;		///< Width of the experimental hall volume
    G4double expHallY;		///< Length of the experimental hall volume
    G4double expHallZ;		///< Depth of the experimental hall volume

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

    G4double fDistance;

    G4bool fCheckOverlaps;
    G4String fGeometry;

    G4String fWrappingMaterial;
    G4String fScintillatorMaterial;


    G4double fWrappingThickness;

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

    G4Element* fB;
    G4Element* fNa;
    G4Element* fK;
    G4Element* fCs;
    G4Element* fSb;


    G4Material* fAir;
    G4Material* fTeflon;
    G4Material* fEJ200;
    G4Material *fEJ299;
    G4Material* fGrease;
    G4Material* fSiO2;
    G4Material* fSil;
    G4Material* fMylar;
    G4Material* fPterphenyl;

    G4Material* fBorosilicate;
    G4Material* fBialkali;

    G4Material* fWrapping;
    G4Material *fScintillator;

    //Material table properties
    G4MaterialPropertiesTable* fAirMPT;
    G4MaterialPropertiesTable* fTeflonMPT;
    G4MaterialPropertiesTable* fEJ200MPT;
    G4MaterialPropertiesTable* fEJ299MPT;
    G4MaterialPropertiesTable* fGreaseMPT;
    G4MaterialPropertiesTable* fSiO2MPT;
    G4MaterialPropertiesTable* fSilMPT;
    G4MaterialPropertiesTable* fMylarMPT;
    G4MaterialPropertiesTable* fPterphenylMPT;

    G4MaterialPropertiesTable* fBorosilicateMPT;
    G4MaterialPropertiesTable* fBialkaliMPT;

    //Optical Surfaces
    G4OpticalSurface* fTeflonOpticalSurface;
    G4OpticalSurface* fSiliconPMOpticalSurface;
    G4OpticalSurface* fMylarOpticalSurface;

    //Logical Skins

    G4LogicalSkinSurface* fWrapSkinSurface;
    G4LogicalSkinSurface* fSiPMSkinSurface;
    G4LogicalBorderSurface* fMylarSurface;


    G4VisAttributes *mylar_VisAtt;


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
    G4AssemblyVolume* ConstructArray(G4String name);

    void PlaceNEXTModule(G4RotationMatrix *theRotation,G4ThreeVector &thePosition, const G4String theName,
                         G4LogicalVolume *theMotherLogical,G4int CopyNo);

    void DefineMaterials();


    void buildSiPMs();


};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif /*nDetConstruction_h*/
