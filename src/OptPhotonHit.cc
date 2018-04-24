//
// Created by David Pérez Loureiro on 3/2/18.
// modified on 3/5/18.
//

#include "OptPhotonHit.hh"
#include <iostream>


/**
 *  \file  OptPhotonHit.cc
 *  \author D. Perez Loureiro
 *  \date 03/02/2018
 */

/**
 *  \class OptPhotonHit
 *  \brief Class to store the SiPM hits into the Output ROOT tree
 */

/**
 * Default constructor
 */
OptPhotonHit::OptPhotonHit()
{

    fPosition=TVector3(-99,-99,-99);
    fTime = -1;
    fLocalTime = -1;
    fDetectorID = -1;
    fModuleNumber = -1;
    fWavelength = 0;

}
/**
 * Default destructor
 */
OptPhotonHit::~OptPhotonHit()
{
}


void OptPhotonHit::Print(Option_t *option) const{

    std::cout<<"OptPhotonHit Information"<<std::endl;
    std::cout<<"Position: ("<<fPosition.X()<<", "<<fPosition.Y()<<", "<<fPosition.Z()<<")"<<"\n";
    std::cout<<"Time: "<<fTime<<"\n"
             <<"Wavelength: "<<fWavelength<<"\n"
             <<"Local time: "<<fLocalTime<<"\n"
             <<"Detector Name: "<< fDetectorName<<" ID: "<<fDetectorID<<"\n"
             <<"Module Number: "<<fModuleNumber<<std::endl;


}