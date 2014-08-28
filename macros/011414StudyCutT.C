{
  // Load libraries
  // ==============
  gSystem->Load("libGeom");
  gSystem->Load("libEve");
  gSystem->Load("libMinuit");
  gSystem->Load("libCintex");
  
  gSystem->Load("libWCSimRootDict");
  gSystem->Load("libWCSimRoot.so");
  gSystem->Load("libWCSimAnalysis.so");

  #include "TRandom3.h"
  #include <sstream>
  #include <string>

  gStyle->SetOptStat(1111);

  char* csize = gApplication->Argv(4);
  std::string strsize = "200";
  //std::string strsize = "500";
  int Ncut = 50;
  double Rcut = 300.0;
  double Tcut = 25.0;
  if(!strcmp(csize,"500")){
    strsize = "500";
    Ncut = 60;
    Rcut = 400.0;
    Tcut = 40.0;
  }
  char* ccoverage = gApplication->Argv(5);
  std::string strcoverage = "13";
  if(!strcmp(ccoverage,"20")){
    strcoverage = "20";
  }
  char* crange = gApplication->Argv(6);
  std::string strrange = "5to10"; strrange = "";
  double lowd = 500.0; lowd = 0.0;
  double highd = 1000.0; highd = 999999.9;
  if(!strcmp(crange,"30to35")){
    strrange = "30to35";
    lowd = 3000.0;
    highd = 3500.0;
  }
  else if(!strcmp(crange,"65to70")){
    strrange = "65to70";
    lowd = 6500.0;
    highd = 7000.0;
  }

  TString filename("/lbne/app/users/txin/WCSim/branches/dev/DetectorDevelopment/muplus_1200mev_"+size+"_10inch_"+coverage+"_hqe.root"); 
//  TString filename("/lbne/app/users/txin/WCSim/branches/dev/DetectorDevelopment/muplus_1200mev_"+strsize+"kton_10inch_"+strcoverage+"per_hqe_MuSct"+strrange+".root"); 
  // Path to WCSim ROOT file
  // =======================
//  TString filename("/lbne/app/users/txin/WCSim/branches/dev/DetectorDevelopment/muplus_1200mev_200kton_10inch_13per_hqe.root");  
//  TString filename("/lbne/app/users/txin/WCSim/branches/dev/DetectorDevelopment/muplus_1200mev_200kton_10inch_20per_hqe_MuSct.root");

  // Load Data
  // =========
  WCSimInterface::LoadData(filename);

  // get first entry
  Double_t sigma0 = 0.0; //sigma0 = 0.1;
  WCSimInterface::SetToUseTrueHits();
  WCSimInterface::Instance()->SetToMCP();
  //WCSimInterface::Instance()->SetToGated();
  WCSimInterface::Instance()->SmearTrueHits(sigma0);

  WCSimDataCleaner::Instance()->SetMinPulseHeight(-1.0);
  WCSimDataCleaner::Instance()->SetNeighbourRadius(300.0); 
  WCSimDataCleaner::Instance()->SetNeighbourDigits(50.0);
  WCSimDataCleaner::Instance()->SetClusterRadius(300.0);
  WCSimDataCleaner::Instance()->SetClusterDigits(50.0);
  WCSimDataCleaner::Instance()->SetTimeWindowNeighbours(25.0);
  WCSimDataCleaner::Instance()->SetTimeWindowClusters(25.0);

  double min = 0.0;
  double max = 1000.0;
  double width = 1;
  int nbin = (int)((max-min)/width);
  TH1D* h0 = new TH1D("h0",";time residual [ns]",nbin,min,max);

//  for(int ievent=0;ievent<1;ievent++){
  int ievent[6] = {1225,1356,1457,1744,26,323};
  for(int i=0;i<6;i++){
  WCSimInterface::LoadEvent(ievent[i]);
  WCSimTrueEvent* trueEvent = WCSimInterface::TrueEvent();
  WCSimRecoEvent* recoEvent = WCSimInterface::RecoEvent();

  WCSimRecoAB* haReco = new WCSimRecoAB(); //run filters
  haReco->RunFilter(recoEvent);
  }
/*
  int myNdigits = recoEvent->GetNDigits();
  int NFilterdigits = recoEvent->GetNFilterDigits();
  if( NFilterdigits != 0 ){

  // get true quantities
  Double_t trueX = trueEvent->GetVtxX();
  Double_t trueY = trueEvent->GetVtxY();
  Double_t trueZ = trueEvent->GetVtxZ(); 
  Double_t dirX = trueEvent->GetDirX();
  Double_t dirY = trueEvent->GetDirY();
  Double_t dirZ = trueEvent->GetDirZ();
  Double_t trueT = 0.0;
  double theta = (TMath::Pi())/2.0 - atan(dirZ/sqrt(dirX*dirX+dirY*dirY)); 
  double phi = 0.0;
  if( dirX<0.0 ) phi = TMath::Pi() - asin(dirY/sqrt(dirX*dirX+dirY*dirY));
  else if( dirY>0.0 ) phi = asin(dirY/sqrt(dirX*dirX+dirY*dirY));
  else if( dirY<0.0 ) phi = 2.0*TMath::Pi() + asin(dirY/sqrt(dirX*dirX+dirY*dirY));
  //else( dirY=0.0 ) phi = 0.0;
  dirX = cos(phi)*sin(theta);
  dirY = sin(phi)*sin(theta);
  dirZ = cos(theta);

  for(int i=0; i<myNdigits; i++){

   WCSimRecoDigit* adigit = recoEvent->GetDigit(i);
   if( adigit->IsFiltered() ){ //if the hit passed the filter
    double hitX = adigit->GetX();
    double hitY = adigit->GetY();
    double hitZ = adigit->GetZ();
    double hitT = adigit->GetTime();
    double qpes = adigit->GetQPEs();
    double res = WCSimParameters::TimeResolution(qpes); 

    h0->Fill(hitT);

    } //loop of the filter
  } //loop over hits
  } //nhits > 0
  } // loop over event

//===============================================================================
  TCanvas *ca3 = new TCanvas("ca3","",400,300);
  ca3->cd();
  h0->Draw();

  TLegend *mylegend2 = new TLegend(0.6,0.4,0.9,0.75,"");
  mylegend2->Draw("Same");
*/
}


