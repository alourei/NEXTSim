//
// Created by David Pérez Loureiro on 3/2/18.
//

#ifndef NEXTMULTIPLESCATTERING_OPTPHOTONHIT_HH
#define NEXTMULTIPLESCATTERING_OPTPHOTONHIT_HH

#include "TObject.h"
#include "TROOT.h"
#include "TVector3.h"

/** \file OptPhotonHit.hh
 *  \author D. Perez Loureiro
 *  \date 03/02/2018
 *
 */


/** \class OptPhotonHit
 *  \brief Class to store the SiPM, PMT Hits in the  Output ROOT file
 *
 *  Stores the information of the optical photon hits in the sensitive detector. SiPM or PMT
 */
class OptPhotonHit : public TObject {

private:

    TVector3 fPosition; ///< The Position of the Hit in mm
    Double_t fTime;     ///< The Absolute Time in ns
    Double_t fLocalTime; ///< The Local time in ns
    Double_t fWavelength; ///< The wavelength of the optical photon produced
    Int_t fDetectorID; ///< The SiPM Number
    Int_t fModuleNumber; ///< The Detector Layer
    TString fDetectorName; ///< The Detector Name
public:
    /**
     * Default constructor
     */
    OptPhotonHit();
    /**
     *  Default destructor
     */
    virtual ~OptPhotonHit();
    //Getters
    /**
     *
     * @return The position of the hit
     */
    TVector3 GetPosition(){return fPosition;}
    /**
     *
     * @return The absolute time of the hit
     */
     Double_t GetTime(){ return fTime;}
    /**
     *
     * @return The local time of the hit
     */
    Double_t GetLocalTime(){ return fLocalTime;}
    /**
     *
     * @return the wavelength of the hit
     */
    Double_t GetWaveLength(){return fWavelength;}
    /**
     *
     * @return The detector Identifier
     */
    Int_t GetDetectorID(){ return fDetectorID;}
    /**
     *
     * @return The module number
     */
    Int_t GetModuleNumber(){ return fModuleNumber;}
    /**
     *
     * @return The name of the detector
     */
    TString GetDetectorName(){ return fDetectorName;}
    //Setters
    /**
     *
     * @param[in] aPosition: a vector with the position of the hit
     */

    void SetPosition(TVector3 aPosition){fPosition=aPosition;}
    /**
     *
     * @param[in] aTime: the time of the hit
     */
    void SetTime(Double_t aTime){fTime = aTime;}
    /**
     *
     * @param[in] aTime: the local time of the hit
     */
    void SetLocalTime(Double_t aTime){fLocalTime = aTime;}
    /**
     *
     * @param[in] aWavelength: the wavelength of the detected photon
     */
    void SetWaveLength(Double_t aWavelength){fWavelength=aWavelength;}
    /**
     *
     * @param[in] anID: the detector ID
     */
    void SetDetectorID(Int_t anID){fDetectorID = anID;}
    /**
     *
     * @param[in] aModuleNumber: the module number
     */
    void SetModuleNumber(Int_t aModuleNumber){fModuleNumber = aModuleNumber;}
    /**
     *
     * @param[in] aName: The name to set
     */
    void SetDetectorName(TString aName){ fDetectorName=aName;}
    /**
     * Prints the Hit Information
     */
    virtual void Print(Option_t *option="") const;
    /**
     * Resets the hit information
     */
    void Reset();

    ClassDef(OptPhotonHit,1);
};


#endif //NEXTMULTIPLESCATTERING_OPTPHOTONHIT_HH
