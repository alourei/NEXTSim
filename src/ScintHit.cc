//
// Created by David Pérez Loureiro on 3/5/18.
//

#include "ScintHit.hh"
#include <iostream>


ScintHit::ScintHit(){

    fPosition = TLorentzVector(-99,-99,-99,-99);
    fMomentum = TLorentzVector(-99,-99,-99,-99);
    fHitNo = -1;
    fLayerNo = -1;
    fTrackID = -1;
    fParticleName = TString("");
    fProcessName = TString("");
    fDeltaE = -1;
    fDepositedEnergy = -1;



}

ScintHit::~ScintHit(){;}

void ScintHit::Print(Option_t *option) const {

    std::cout<<"ScintHit Information Hit #: "<<fHitNo<<std::endl;
    std::cout<<"Particle Name: "<<fParticleName<<std::endl;
    std::cout<<"Process Name: "<<fProcessName<<std::endl;
    std::cout<<"Position: ("<<fPosition.X()<<", "<<fPosition.Y()<<", "<<fPosition.Z()<<")"<<"\n";
    std::cout<<"Time: "<<fPosition.T()<<"\n"
             <<"Momentum: ("<<fMomentum.X()<<", "<<fMomentum.Y()<<", "<<fMomentum.Z()<<")"<<"\n";
    std::cout<<"Energy: "<<fMomentum.E()<<"\n"
            <<"Delta Energy: "<<fDeltaE<<std::endl
            <<"Deposited Energy: "<<fDepositedEnergy<<std::endl
            <<"Module Number: "<<fLayerNo<<std::endl;



}