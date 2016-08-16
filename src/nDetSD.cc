//
// $Id: nDetSD.hh,v 1.0 Sept., 2015 $
//  Written by Dr. Xiaodong Zhang
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "nDetSD.hh"
#include "nDetHits.hh"
#include "G4Step.hh"
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4ios.hh"

#include "G4OpBoundaryProcess.hh"
#include "G4ProcessManager.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
nDetSD::nDetSD(G4String name)
:G4VSensitiveDetector(name)
{
  G4String HCname;
  collectionName.insert(HCname="hitsCollection");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
nDetSD::~nDetSD(){;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void nDetSD::Initialize(G4HCofThisEvent* HCE)
{
  static int HCID = -1;
  hitsCollection = new nDetHitsCollection
                      (SensitiveDetectorName,collectionName[0]); 
  if(HCID<0)
  { HCID = GetCollectionID(0); }
  HCE->AddHitsCollection(HCID,hitsCollection);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4bool nDetSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
        /*
	G4cout<<"**************** SD start ************"<< G4endl;
	G4cout<<"Process name:"<<aStep->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName()<<G4endl;
	G4String name = aStep->GetTrack()->GetVolume()->GetName();
	G4cout<<"Physical volume name:"<<name<<G4endl;
	G4cout<<"Length of this Step: "<<aStep->GetStepLength()/mm<<" mm"<<G4endl;
	G4cout<<"**************** SD stop ************"<< G4endl;
	*/

        if(aStep->GetStepLength()>0){
          /* 
          G4cout<<"**************** SD start ************"<< G4endl;
          G4cout<<"Process name:"<<aStep->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName()<<G4endl;
          G4String name = aStep->GetTrack()->GetVolume()->GetName();
          G4cout<<"Physical volume name:"<<name<<G4endl;
          G4cout<<"Length of this Step: "<<aStep->GetStepLength()/mm<<" mm"<<G4endl;
          G4cout<<"**************** SD stop ************"<< G4endl;
          */

	  nDetHit* newHit = new nDetHit();
  	  newHit->SetTime( aStep->GetPreStepPoint()->GetGlobalTime() );
  	  newHit->SetPos( aStep->GetPreStepPoint()->GetPosition() );
  	  hitsCollection->insert( newHit );
        }
        else{
          aStep->GetTrack()->SetTrackStatus(fStopAndKill);
        }

  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4bool nDetSD::ProcessHits(const G4Step* aStep)
{
/*
        G4cout<<"**************** SD start ************"<< G4endl;
        G4cout<<"Process name:"<<aStep->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName()<<G4endl;
        G4String name = aStep->GetTrack()->GetVolume()->GetName();
        G4cout<<"Physical volume name:"<<name<<G4endl;
        G4cout<<"Physical volume of prestep point: " << aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName()<<G4endl;
        G4cout<<"Physical volume of poststep point: " << aStep->GetPostStepPoint()->GetPhysicalVolume()->GetName()<<G4endl;
        G4cout<<"Length of tghis Step: "<<aStep->GetStepLength()/mm<<" mm"<<G4endl;
        G4cout<<"**************** SD stop ************"<< G4endl;
        /// old codes used to pick off the information about hit in SD
        nDetHit* newHit = new nDetHit();
        newHit->SetTime( aStep->GetPreStepPoint()->GetGlobalTime() );
        newHit->SetPos( aStep->GetPreStepPoint()->GetPosition() );
        hitsCollection->insert( newHit );
*/  
  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void nDetSD::EndOfEvent(G4HCofThisEvent*)
{

  if (verboseLevel>0) {
     G4int NbHits = hitsCollection->entries();
     G4cout << "\n-------->Hits Collection: in this event they are " << NbHits
            << " hits in the readout pixel cathode: " << G4endl;
     for (G4int i=0;i<NbHits;i++) (*hitsCollection)[i]->Print();
     G4cout << "Hit Number: " << NbHits << G4endl;
     }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void nDetSD::clear()
{
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void nDetSD::DrawAll()
{
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void nDetSD::PrintAll()
{
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
