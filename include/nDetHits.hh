//
// $Id: nDetHit.hh,v 1.0 Sept., 2015 $
//  Written by Dr. Xiaodong Zhang
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


#ifndef nDetHit_h
#define nDetHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4Types.hh"
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
  private:
      G4double time;
      G4ThreeVector pos;
      G4double edep;
      G4double edep_first;
      G4bool first=false;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
typedef G4THitsCollection<nDetHit> nDetHitsCollection;

extern G4ThreadLocal G4Allocator<nDetHit>* nDetHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void* nDetHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) nDetHitAllocator->MallocSingle();
  return aHit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void nDetHit::operator delete(void *aHit)
{
  nDetHitAllocator->FreeSingle((nDetHit*) aHit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif

