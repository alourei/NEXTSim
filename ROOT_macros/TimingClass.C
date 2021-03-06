#define TimingClass_cxx
#include "TimingClass.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include <TH3.h>
#include <TFile.h>

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>



void TimingClass::Loop(const Int_t entries)
{
//   In a ROOT session, you can do:
//      Root > .L TimingClass.C
//      Root > TimingClass t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   if(entries==0)
     nentries = fChain->GetEntriesFast();
   else
   nentries = entries;


   
   Long64_t nbytes = 0, nb = 0;

   TFile *fil=new TFile("Anl_out.root","NEW");
   
   TH1F *h=new TH1F("h1","Time Distribution",2000,-15,15);
   TH1F *h2=new TH1F("h2","Time Distribution2",2000,-15,15);
   TH1F *h3=new TH1F("h3","Time Distribution3",2000,-1,30);
   TH2F *h2D= new TH2F("h2d","time Vs energy deposited",2000,-15,15,2000,0,1500);
   TH2F *h2Dpos= new TH2F("h22pos","time Vs Position",2000,-60,60,2000,-6,6);
   TH2F *h2DposL= new TH2F("h22posL","time Vs Position L",2000,-60,60,2000,-1,25);
   TH2F *h2DposR= new TH2F("h22posR","time Vs Position R",2000,-60,60,2000,-1,25);
   TH3F *h3D= new TH3F("h3d","Energy Vs Position Vs time ",500,0,1100,500,-60,60,500,-15,15);
   TH2F *h2DtrackL= new TH2F("h22tL","time Vs TrackLength L",2000,0,6000,2000,-1,25);
   TH2F *h2DtrackR= new TH2F("h22tR","time Vs TrackLength R",2000,0,6000,2000,-1,25);


   TH1F *htime[2];
   htime[0]=new TH1F("h_time0","Time Distribution in SiPM 0 ",500,0,50);
   htime[1]=new TH1F("h_time1","Time Distribution in SiPM 1",500,0,50);

   TH2F *h_time_photons[2];
   h_time_photons[0]=new TH2F("h2D0","Time Distribution Vs number of photons detected",200,0,50,200,0,500);
   h_time_photons[1]=new TH2F("h2D1","Time Distribution Vs number of photons detected",200,0,50,200,0,500);


   h2->SetLineColor(2);

   
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;


     //Loop over the SiPm entries
     Double_t time_left=999;
     Double_t time_right=999;
     Double_t track_length=-1;
     UInt_t posL=0;
     UInt_t posR=0;
     Int_t TrackID_L;
     Int_t TrackID_R;

     Double_t average[2]={0};
     Int_t hits[2]={0};

     
     Int_t nSciHits=vTimeOfPhotonInEJ200->size();
     Int_t nHits=vSDPhotonTime->size();
     
     if(nSciHits>0){
       //std::cout<<"Event "<<eventNb<<" has "<< nSciHits<<" in the Plastic"<<std::endl;
       //std::cout<<"Event "<<eventNb<<" has "<<NumberofPhotons<<" in the Plastic"<<std::endl;
     }

     if(nHits>0){
       //std::cout<<"Event "<<eventNb<<" has "<< nHits<<" in the SiPM"<<std::endl;
       
       
       for(Int_t i=0;i<nHits;i++){
	 
	 //std::cout<<"Hit # "<<i<<" TrackID "<<vSDTrackID->at(i)<<std::endl;
	 //std::cout<<"Hit # "<<i<<" Detector Number "<<vSDDetectorNumber->at(i)<<std::endl;
	 //std::cout<<"Hit # "<<i<<" Time "<<vSDPhotonTime->at(i)<<std::endl;
	 Int_t DetectorID=vSDDetectorNumber->at(i);
	 switch(DetectorID){
	 case 6:
	     average[0]+=vSDPhotonTime->at(i);
	     hits[0]++;

	   if(vSDPhotonTime->at(i)<time_left){
	     time_left=vSDPhotonTime->at(i);
	     posL=i;
	     TrackID_L=vSDTrackID->at(i);
	   }
	   break;
	 case 7:
	     average[1]+=vSDPhotonTime->at(i);
	     hits[1]++;
	   if(vSDPhotonTime->at(i)<time_right){
	     time_right=vSDPhotonTime->at(i);
	     posR=i;
	     TrackID_R=vSDTrackID->at(i);
	   }
	   break;
	 default:
	   break;
	 }
	 } 
       //Looking for matches in the Scint hits

     
        Double_t Delta_t=(time_left-time_right);
       if(depositedEnergy>250)
	 h->Fill(Delta_t);
       //h2D->Fill(Delta_t, depositedEnergy);
       h2Dpos->Fill(neutronIncidentPositionZ,Delta_t);
       h2DposL->Fill(neutronIncidentPositionZ,time_left);
       h2DposR->Fill(neutronIncidentPositionZ,time_right);
       h2->Fill(Delta_t);
       //h3->Fill((time_left+time_right)/2);
       h3D->Fill(depositedEnergy,neutronIncidentPositionZ,Delta_t);
       //h2DtrackL->Fill(track_length,time_left) ;
       h2DtrackR->Fill(track_length,time_right);
      //else
	     //h2->Fill(Delta_t);
	     //}
	     //else{
       //std::cout << "Element not found in myvector\n";
       //continue;
       //}
       //}
       
     for(Int_t k=0;k<2;k++){
	if(hits[k]>0){
	  average[k]/=hits[k];
	  //std::cout<<average[k]<<" "<<maximum<<" "<<minimum<<std::endl;
	  htime[k]->Fill(average[k]);
	  h_time_photons[k]->Fill(average[k],hits[k]);
	}
       }

      h3->Fill((average[0]+average[1])/2);
       h2D->Fill((average[0]+average[1])/2, depositedEnergy);
 
       
   // if (Cut(ientry) < 0) continue;
     }
     }//end loop

   TH2F *h6=(TH2F*)h3D->Project3D("yx");
   h3->Draw();
   //h2DtrackR->Draw("colz");
   fil->Write();
}



  
