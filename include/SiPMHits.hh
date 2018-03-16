//
// Created by David Pérez Loureiro on 1/9/17.
//

#ifndef NEXTMULTIPLESCATTERING_SIPMHITS_HH
#define NEXTMULTIPLESCATTERING_SIPMHITS_HH

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"


class SiPMHit:public G4VHit
{
public:
    SiPMHit();
    ~SiPMHit();
    SiPMHit(const SiPMHit &right);

    const SiPMHit& operator=(const SiPMHit &right);
    G4int operator==(const SiPMHit &right) const;

    inline void *operator new(size_t);
    inline void operator delete(void *aHit);

    void Draw();
    void Print();

    void SetTime(G4double t) { time = t; };
    G4double GetTime() { return time; };
    void SetLocalTime(G4double t) { local_time = t; };
    G4double GetLocalTime() { return local_time; };
    void SetPos(G4ThreeVector xyz) { pos = xyz; };
    G4ThreeVector GetPos() { return pos; };
    void SetSiPMNumber(G4int num) { SiPMnumber = num; }
    G4int GetSiPMNumber() {return SiPMnumber;}
    void SetEventID(G4int num) { EventID = num; }
    G4int GetEventID() { return EventID; }
    void SetTrackID(G4int num) { TrackID = num; }
    G4int GetTrackID() { return TrackID; }
    void SetWaveLength(G4double length) { Wavelength = length; }
    G4double GetWaveLength() { return Wavelength; }
    void SetModuleNumber(G4int aModuleNumber) { ModuleNumber = aModuleNumber; }
    G4double GetModuleNumber() { return ModuleNumber; }
    G4String GetDetectorName(){ return DetectorName;}
    void SetDetectorName(G4String aName){DetectorName= aName;}


private:
    G4double time;
    G4double local_time;
    G4ThreeVector pos;
    G4int SiPMnumber;
    G4double Wavelength;
    G4int EventID;
    G4int TrackID;
    G4int ModuleNumber;
    G4String DetectorName;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
typedef G4THitsCollection<SiPMHit> SiPMHitsCollection;

extern G4Allocator<SiPMHit> SiPMHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void* SiPMHit::operator new(size_t)
{
    void *aHit;
    aHit = (void *) SiPMHitAllocator.MallocSingle();
    return aHit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void SiPMHit::operator delete(void *aHit)
{
    SiPMHitAllocator.FreeSingle((SiPMHit*) aHit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



#endif //NEXTMULTIPLESCATTERING_SIPMHITS_HH
