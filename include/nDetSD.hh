//
// $Id: nDetSD.hh,v 1.0 Sept., 2015 $
//  Written by Dr. Xiaodong Zhang
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef nDetSD_h
#define nDetSD_h 1

#include "G4VSensitiveDetector.hh"
#include "nDetHits.hh"


class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class nDetSD : public G4VSensitiveDetector
{

  public:
      nDetSD(G4String name);
      ~nDetSD();

      void Initialize(G4HCofThisEvent *HCE);
      G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist);
      G4bool ProcessHits(const G4Step *aStep);
      void EndOfEvent(G4HCofThisEvent *HCE);

      // to be added....
      void clear();
      void DrawAll();
      void PrintAll();

  private:
      nDetHitsCollection *hitsCollection;

  public:
};

#endif

