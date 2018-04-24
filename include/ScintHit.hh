//
// Created by David Pérez Loureiro on 3/5/18.
//

#ifndef NEXTSIM_SCINTHIT_HH
#define NEXTSIM_SCINTHIT_HH

#include "TObject.h"
#include "TROOT.h"
#include "TLorentzVector.h"


/**
 * \class ScintHit
 * \brief class to store the scintillator hits
 * \author D. Perez Loureiro
 */
class ScintHit: public TObject {

private:

    TLorentzVector fPosition;
    TLorentzVector fMomentum;
    Int_t fHitNo;
    Int_t fLayerNo;
    Int_t fTrackID;
    Double_t fDeltaE;
    Double_t fDepositedEnergy;
    TString fParticleName;
    TString fProcessName;

public:
    /**
     * Default constructor
     */
    ScintHit();
    /**
     * Default destructor
     */
    virtual ~ScintHit();
    //Getters
    /**
     *
     * @return The position of the hit
     */
    TLorentzVector GetPosition(){ return fPosition;}
    /**
     *
     * @return The momentum of the particle after the hit
     */
    TLorentzVector GetMomentum(){ return fMomentum;}
    /**
     *
     * @return The Hit number
     */
    Int_t GetHitNo(){ return fHitNo;}
    /**
     *
     * @return The layer Number
     */
    Int_t GetLayerNo(){ return  fLayerNo;}
    /**
     *
     * @return The Track ID
     */
    Int_t GetTrackID(){ return  fTrackID;}
    /**
     *
     * @return The name of the particle
     */
    TString GetParticleName(){ return fParticleName;};
    /**
     *
     * @return The nem of the process
     */
    TString GetProcessName(){ return fProcessName;};
    /**
     *
     * @return the variation in energy
     */
    Double_t GetDeltaE(){ return fDeltaE;}
    /**
     *
     * @return the energy deposited in the step
     */
    Double_t GetDepositedEnergy(){ return fDepositedEnergy;}
    //Setters
    /**
     *
     * @param[in] aPosition: the position of the Hit
     */
    void SetPosition(TLorentzVector aPosition){ fPosition = aPosition;}
    /**
     *
     * @param[in] aMomentum: the momentum of the particle after the hit
     */
    void SetMomentum(TLorentzVector aMomentum) {fMomentum = aMomentum;}
    /**
     *
     * @param[in] aHitNo: the hit number
     */
    void SetHitNo(Int_t aHitNo){ fHitNo = aHitNo;}
    /**
     *
     * @param[in] aLayerNo: the layer number
     */
    void SetLayerNo(Int_t aLayerNo){ fLayerNo = aLayerNo;}
    /**
     *
     * @param[in] aTrackID: the tack identifier
     */
    void SetTrackID(Int_t aTrackID){ fTrackID = aTrackID;}
    /**
     *
     * @param[in] pName: the process name
     */
    void SetProcessName(TString pName){ fProcessName = pName;}
    /**
     *
     * @param[in] pName: the particle name
     */
    void SetParticleName(TString pName){ fParticleName = pName;}
    /**
     *
     * @param[in] aDeltaE: the delta Energy
     */
    void SetDeltaE(Double_t aDeltaE){fDeltaE=aDeltaE;}
    /**
     *
     * @param[in] anEnergy: the deposited energy
     */
    void SetDepositedEnergy(Double_t anEnergy){ fDepositedEnergy = anEnergy;}
    /**
     *
     * Prints the information of the hit
     */
    virtual void Print(Option_t *option="")const ;

    /**
     * Resets the Hit information
     */
    void Reset();

    ClassDef(ScintHit,1);
};



#endif //NEXTSIM_SCINTHIT_HH

