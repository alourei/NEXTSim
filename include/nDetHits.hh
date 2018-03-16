//
// $Id: nDetHit.hh,v 1.0 Sept., 2015 $
//  Written by Dr. Xiaodong Zhang
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


#ifndef nDetHit_h
#define nDetHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class nDetHit : public G4VHit
{
  public:

      nDetHit();
      ~nDetHit();
      nDetHit(const nDetHit &right);
      const nDetHit& operator=(const nDetHit &right);
      G4int operator==(const nDetHit &right) const;

      inline void *operator new(size_t);
      inline void operator delete(void *aHit);

      void Draw();
      void Print();

      void SetTime(G4double t) { time = t; };
      G4double GetTime() { return time; };
      void SetPos(G4ThreeVector xyz) { pos = xyz; };
      G4ThreeVector GetPos() { return pos; };
      void SetEdep(G4double e) { edep = e; };
      G4double GetEdep() { return edep; };
      void SetEdep_first(G4double e) { edep_first = e; };
      G4double GetEdep_first() { return edep_first; };
      G4bool IsFirst() {return first;}
      void SetFirst() { first= true;}
      void SetParticleName(G4String name){particle=name;};
      G4String GetParticleName(){return particle;}
      void SetProcessName(G4String name){processName=name;};
      G4String GetProcessName(){return processName;}
      void SetTrackID(G4int num){TrackID = num;}
      G4int GetTrackID(){return TrackID;}
      void SetLayerNumber(G4int num){layerNumber = num;}
      G4int GetLayerNumber(){return layerNumber;}
      void SetMomentum(G4ThreeVector xyz) { momentum = xyz; };
      G4ThreeVector GetMomentum() { return momentum; };
      void SetEkin(G4double e) { ekin = e; };
      G4double GetEkin() { return ekin; };
      void SetScatteringAngle(G4double angle) { scatteringAngle = angle; };
      G4double GetScatteringAngle() { return scatteringAngle; };





private:
      G4double time;
      G4ThreeVector pos;
      G4ThreeVector momentum;
      G4double edep=0;
      G4double ekin=0;
      G4double edep_first;
      G4double scatteringAngle;
      G4bool first=false;
      G4String particle;
      G4String processName;
      G4int TrackID;
      G4int layerNumber;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
typedef G4THitsCollection<nDetHit> nDetHitsCollection;

extern G4Allocator<nDetHit> nDetHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void* nDetHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) nDetHitAllocator.MallocSingle();
  return aHit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void nDetHit::operator delete(void *aHit)
{
  nDetHitAllocator.FreeSingle((nDetHit*) aHit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif

