//
// $Id: nDetHit.hh,v 1.0 Jan., 2014 $
//  Written by Dr. Xiaodong Zhang
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include <G4SIunits.hh>
#include "nDetHits.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4UnitsTable.hh"

G4Allocator<nDetHit> nDetHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
nDetHit::nDetHit(){;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
nDetHit::~nDetHit(){;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
nDetHit::nDetHit(const nDetHit &right)
  : G4VHit()
{ 
  time = right.time;
  pos = right.pos;
  edep = right.edep;
  particle = right.particle;
  TrackID = right.TrackID;
  layerNumber = right.layerNumber;
  processName = right.processName;
  ekin = right.ekin;
  momentum = right.momentum;
  scatteringAngle = right.scatteringAngle;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
const nDetHit& nDetHit::operator=(const nDetHit &right)
{
  time = right.time;
  pos = right.pos;
  edep = right.edep;
  particle = right.particle;
  processName = right.processName;
  TrackID = right.TrackID;
  layerNumber = right.layerNumber;
  ekin = right.ekin;
  momentum = right.momentum;
  scatteringAngle = right.scatteringAngle;
  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4int nDetHit::operator==(const nDetHit &right) const
{
  return (this==&right) ? 1 : 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void nDetHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager)
  {
    G4Circle circle(pos);
    circle.SetScreenSize(0.04);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1.,0.,0.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void nDetHit::Print()
{

  G4cout << "  particle: " << GetParticleName()
         << "  process: " << GetProcessName()
         << "  time: " << G4BestUnit(time,"Time")
         << "  position: " << G4BestUnit(pos,"Length")
         << "  Kinetic Energy: " << G4BestUnit(ekin,"Energy")
         << "  momentum: " << momentum
         << "  Scattering Angle: " << scatteringAngle/degree << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
