//
// Created by David Pérez Loureiro on 1/9/17.
//

#include "SiPMHits.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4UnitsTable.hh"



G4Allocator<SiPMHit> SiPMHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
SiPMHit::SiPMHit(){;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
SiPMHit::~SiPMHit(){;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
SiPMHit::SiPMHit(const SiPMHit &right)
        : G4VHit()
{
    time = right.time;
    pos = right.pos;
    SiPMnumber=right.SiPMnumber;
    Wavelength=right.Wavelength;
    local_time=right.local_time;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
const SiPMHit& SiPMHit::operator=(const SiPMHit &right)
{
    time = right.time;
    pos = right.pos;
    SiPMnumber=right.SiPMnumber;
    Wavelength=right.Wavelength;
    local_time=right.local_time;
    return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4int SiPMHit::operator==(const SiPMHit &right) const
{
    return (this==&right) ? 1 : 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void SiPMHit::Draw()
{
    G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
    if(pVVisManager)
    {
        G4Circle circle(pos);
        circle.SetScreenSize(0.08);
        circle.SetFillStyle(G4Circle::filled);
        //Red circle
        G4Colour colour(1.,0.,0.);
        G4VisAttributes attribs(colour);
        circle.SetVisAttributes(attribs);
        pVVisManager->Draw(circle);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void SiPMHit::Print()
{
    G4cout << "  time: " << G4BestUnit(time,"Time")
           << "  local time: " << G4BestUnit(local_time,"Time")
           << "  position: " << G4BestUnit(pos,"Length") << G4endl
           << "  wavelength: " << G4BestUnit(Wavelength,"Length") << G4endl
            << "  detector name: " << GetDetectorName() << G4endl
            << "  detector number: " << GetSiPMNumber() << G4endl
           << "  module number: " << GetModuleNumber() << G4endl;

}
