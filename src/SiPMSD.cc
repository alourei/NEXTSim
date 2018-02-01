//
// Created by David Pérez Loureiro on 1/10/17.
//

#include "SiPMSD.hh"
#include "G4ParticleTypes.hh"
#include "G4SIunits.hh"

#include "sipmMC.hh"
#include "PhotonList.hh"
#include "TFile.h"

SiPMSD::SiPMSD(G4String name) : G4VSensitiveDetector(name) {

    G4cout<<"SiPMSD::SiPMSD(): Constructing Sensitive Detector"<< G4endl;

    G4String HCname;
    collectionName.insert(HCname="SiPMCollection");

    //fsipm = new sipmMC();

    //fsipm->GetParaFile("input/MPPC_6x6.txt");

    TFile f("input/SpectralSensitivity.root");
    //fsipm->SetSpectralSensitivity((TGraph*)f.Get("MPPC_noRef"));
    //f.Close();

    //fphotons = new PhotonList();
}

SiPMSD::~SiPMSD() {
;

    G4cout<<"SiPMSD::~SiPMSD()"<<G4endl;
    //delete fsipm;
    //delete fphotons;
}

void SiPMSD::Initialize(G4HCofThisEvent *HCE) {

    static int HCID = -1;
    hitsCollection = new SiPMHitsCollection
            (SensitiveDetectorName, collectionName[0]);
    if(HCID<0) {
        HCID = GetCollectionID(0);
    }
        HCE->AddHitsCollection(HCID,hitsCollection);

    //fphotons->clear();
}

G4bool SiPMSD::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) {
    return false;
}

G4bool SiPMSD::ProcessHits_constStep(const G4Step *aStep, G4TouchableHistory *ROhist){

    //need to know if this is an optical photon
    if(aStep->GetTrack()->GetDefinition()
       != G4OpticalPhoton::OpticalPhotonDefinition()) return false;

    G4TouchableHandle theTouchable=aStep->GetPreStepPoint()->GetTouchableHandle();

    G4int SipmNumber=
            aStep->GetPostStepPoint()->GetTouchable()->GetReplicaNumber();
    //G4cout<<"SiPM number "<<SipmNumber<<G4endl;

    G4VPhysicalVolume* physVol=
            aStep->GetPostStepPoint()->GetTouchable()->GetVolume();

    //G4cout<<"SiPMSD::ProcessHits_constStep()-->"<<physVol->GetName()<<" "<<physVol->GetMultiplicity()<<G4endl;
    //G4cout<<"SiPMSD::ProcessHits_constStep()-->"<<aStep->GetPostStepPoint()->GetTouchable()->GetVolume()->GetName()
    //      <<" "<<aStep->GetPostStepPoint()->GetTouchable()->GetReplicaNumber()<<G4endl;


    G4ThreeVector worldPosition=aStep->GetPreStepPoint()->GetPosition();

    //G4ThreeVector pos = aStep->GetPostStepPoint()->GetPosition();

    G4ThreeVector pos = theTouchable->GetHistory()->GetTopTransform().TransformPoint(worldPosition);
    G4double  time = aStep->GetPostStepPoint()->GetGlobalTime();
    G4double  wavelength = CLHEP::h_Planck*CLHEP::c_light/aStep->GetTrack()->GetTotalEnergy()*1e6;

    SiPMHit* hit = new SiPMHit(); //so create new hit
    hit->SetSiPMNumber(SipmNumber);
    hit->SetTime( aStep->GetPostStepPoint()->GetGlobalTime() );
    //DPL TODO change back to global time for TOF
    hit->SetLocalTime( aStep->GetPostStepPoint()->GetLocalTime() );
    hit->SetPos( aStep->GetPostStepPoint()->GetPosition() );
    hit->SetTrackID(aStep->GetTrack()->GetTrackID());
    hit->SetWaveLength(wavelength);


    //fphotons->AddPhoton(pos.x(),pos.y(),time,wavelength);


    //G4cout<<"hit->GetWaveLength()->"<<hit->GetWaveLength()<<G4endl;
    //G4cout<<"hit->GetEnergy()->"<<aStep->GetTrack()->GetTotalEnergy()<<G4endl;
    //hit->SetEventID(aStep->Ge)


    hitsCollection->insert(hit);

    //G4cout<<"hit->Size "<<hitsCollection->GetSize()<<G4endl;
    //G4cout<<"hit->Size "<<hitsCollection->GetSize()<<G4endl;

    //hit->IncPhotonCount(); //increment hit for the selected pmt

    return true;

}

void SiPMSD::EndOfEvent(G4HCofThisEvent *HCE){

    //fsipm->Generate(*fphotons);

    if (verboseLevel>1)
        PrintAll();
    G4int NbHits = hitsCollection->entries();
if(verboseLevel >0) {
    if (NbHits >= 0) {
        G4cout << "SiPMSD::EndOfEvent()->Hit Number in SiPMs: " << NbHits << G4endl;
    }
}

}

void SiPMSD::clear() {
    G4VSensitiveDetector::clear();
}

void SiPMSD::DrawAll() {
    G4VSensitiveDetector::DrawAll();
}

void SiPMSD::PrintAll() {

        G4int NbHits = hitsCollection->entries();
    if(verboseLevel>1) {
        if (NbHits > 0) {
            G4cout << "\n-------->Hits Collection: in this event they are " << NbHits
                   << " hits in the SiPMs cathodes: " << G4endl;
            for (G4int i = 0; i < NbHits; i++) (*hitsCollection)[i]->Print();
        }
    }
}


