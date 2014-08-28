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

  #include <iostream>
  #include <fstream>
  #include "TLegend.h"

  gStyle->SetEndErrorSize(5);

  TFile ffile1("Result_RiseT/hadd_dphot.root");
  TH1D* hmean1 = (TH1D*)dphotmean_200_13->Clone();
  TH1D* hrms1 = (TH1D*)dphotRMS_200_13->Clone();
  TH1D* hmean2 = (TH1D*)dphotmean_500_13->Clone();
  TH1D* hrms2 = (TH1D*)dphotRMS_500_13->Clone();
 
  int nbin = 20;
  double minx = 0.0;
  double maxx = 10000.0;
  float dphot[5] = {750.0,2250.0,3750.0,5250.0,6750.0};
//================= mean of vtxres for 200kton ======
  float mean1[5] = {0.118,0.145,0.182,0.22,0.261};
  float mean2[5] = {0.431,0.447,0.478,0.51,0.548};
  float rms1[5] = {0.118,0.145,0.182,0.22,0.261};
  float rms2[5] = {0.431,0.447,0.478,0.51,0.548};
  float rmsx[5] = {0.118,0.145,0.182,0.22,0.261};
  for(int j=0;j<5;j++){
     mean1[j] = hmean1->GetBinContent(j+1);
     mean2[j] = hmean2->GetBinContent(j+1);  
     rms1[j] = hrms1->GetBinContent(j+1);
     rms2[j] = hrms2->GetBinContent(j+1); 
     rmsx[j] = 0.0; 
  }

  TGraphErrors* g1 = new TGraphErrors(5, dphot, mean1,rmsx,rms1);
  TGraphErrors* g2 = new TGraphErrors(5, dphot, mean2,rmsx,rms2);
 
  cout << "i am good!!!!" << endl;
  g1->SetMarkerStyle(20);
  g1->SetMarkerColor(kRed);
  g1->SetMarkerSize(2.5);
  g1->SetLineWidth(2.0);
  g2->SetMarkerStyle(23);
  g2->SetMarkerColor(kBlue);
  g2->SetMarkerSize(2.5);
  g2->SetLineWidth(2.0);

  
  TLegend *leg2 = new TLegend(0.55,0.65,0.95,0.85);
  leg2->AddEntry(g1,"200kton","p");
  leg2->AddEntry(g2,"500kton","p");

  TCanvas *ca2 = new TCanvas("ca2","ca2",500,400);
  ca2->cd();
  ca2->SetGrid();
  TMultiGraph *mg = new TMultiGraph();
  mg->SetTitle("dphoton vs dvtx");
  mg->Add(g1);
  mg->Add(g2);
  mg->Draw("ALP");
  leg2->Draw("Same");
  
 
}
