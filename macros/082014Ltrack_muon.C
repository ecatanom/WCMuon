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
  
  // Path to WCSim ROOT file
  // ======================= 
  
  // Load Data
  // =========
   TString filename("/lbne/data2/users/txin/Samples/muplus_1200mev_200kton_10inch_13per_hqe_MuSct.root");
 
  WCSimInterface::LoadData(filename);

  // get first entry
  Bool_t truehit = 1; // 1 is to use true hits
  Bool_t Lmu = 0; // 1 is to use LMuon cut
  Double_t sigma0 = 0.1; //sigma0 = 0.1; //1 ns
  if(truehit) {WCSimInterface::SetToUseTrueHits();
    WCSimInterface::Instance()->SetToMCP();//
    WCSimInterface::Instance()->SmearTrueHits(sigma0); //Smear sigma0=1ns, we are talking about MCP
  }
  WCSimDataCleaner::Instance()->SetMinPulseHeight(-1.0);//there's no cut
  WCSimDataCleaner::Instance()->SetNeighbourRadius(300.0); //cm
  WCSimDataCleaner::Instance()->SetNeighbourDigits(50.0);//number of neighb
  WCSimDataCleaner::Instance()->SetClusterRadius(300.0);
  WCSimDataCleaner::Instance()->SetClusterDigits(50.0);//at least 50 clusters
  WCSimDataCleaner::Instance()->SetTimeWindowNeighbours(25.0);//ns window
  WCSimDataCleaner::Instance()->SetTimeWindowClusters(25.0);

  //WCSimInterface::Instance()->SetToGated();//use PMT
  //both commented is using ungated PMT


  Bool_t filtered = 0;
  Bool_t drawd = 1; // 1 is to draw the distance plot at the end
  if(drawd){//dist traveled by photon
    double mind = 0.0;
    double maxd = 900.0;
  }
  else{
    double mind = 1500.0;
    double maxd = 5500.0;
  }
  double mindmu = -200.0;//dist muon
  double maxdmu = 800.0;
  TH1D* hltrackdata = new TH1D("hltrackdata", ";Ltrack [cm]",100,mindmu,maxdmu);
  TH1D* hltrackdataall = new TH1D("hltrackdataall", ";Ltrack [cm]",100,mindmu,maxdmu);  //Ltrack only
  //TH1D* hltrackdataall = new TH1D("hltrackdataall", ";Oangle [deg]",100,0,60); // Oamgle only
 
 TH1D* hltrackmc = new TH1D("hltrackmc", "Ltrack [cm]",100,mindmu,maxdmu);
  Double_t TResid, LPhot, LMuon, Oangle;
  double bdeltaT, rdeltaT;
  
  
  //LOOP OVER EVENTS
  
  for(Int_t ievt=0;ievt<1000;ievt++ ){
    //ievt=16;
    WCSimInterface::LoadEvent(ievt);
    // build event
    WCSimTrueEvent* trueEvent = WCSimInterface::TrueEvent();
    WCSimRecoEvent* recoEvent = WCSimInterface::RecoEvent();
    //
    WCSimRecoAB* haReco = new WCSimRecoAB(); //run filters
    if(filtered) haReco->RunFilter(recoEvent);
    
    int myNdigits = recoEvent->GetNDigits();
    int NFilterdigits = recoEvent->GetNFilterDigits();
  
    // get true quantities
    Double_t trueX = trueEvent->GetVtxX();
    Double_t trueY = trueEvent->GetVtxY();
    Double_t trueZ = trueEvent->GetVtxZ(); 
    if( trueX==0 && trueY==0 && trueZ==0 ) continue;
    Double_t dirX = trueEvent->GetDirX();
    Double_t dirY = trueEvent->GetDirY();
    Double_t dirZ = trueEvent->GetDirZ();
    Double_t trueT = 0.0;
    double theta = (TMath::Pi())/2.0 - atan(dirZ/sqrt(dirX*dirX+dirY*dirY)); //theta = theta + 3.0/41.0;
    double phi = 0.0;
  if( dirX<0.0 ) phi = TMath::Pi() - asin(dirY/sqrt(dirX*dirX+dirY*dirY));
  else if( dirY>0.0 ) phi = asin(dirY/sqrt(dirX*dirX+dirY*dirY));
  else if( dirY<0.0 ) phi = 2.0*TMath::Pi() + asin(dirY/sqrt(dirX*dirX+dirY*dirY));
  //else( dirY=0.0 ) phi = 0.0;
  dirX = cos(phi)*sin(theta);
  dirY = sin(phi)*sin(theta);
  dirZ = cos(theta);
  
  //phenomenology... water model: class that contains index of refraction, attenuation (lambda), initial spectrum, etc. How photon travels through water
  WCSimWaterModel *wm2 = WCSimWaterModel::Instance();
  WCSimTResidPDF *pdf = WCSimTResidPDF::Instance();//dont use this :p
  
  int ifilter = 0;
  for(int i=0; i<myNdigits; i++){
    
   WCSimRecoDigit* adigit = recoEvent->GetDigit(i);
   double hitX = adigit->GetX();
   double hitY = adigit->GetY();
   double hitZ = adigit->GetZ();
   double hitT = adigit->GetTime();
   double qpes = adigit->GetQPEs();//charge
   double res = WCSimParameters::TimeResolution(qpes); 
   
   WCSimVertexGeometry::CalcTResid(trueX, trueY, trueZ, trueT, dirX, dirY, dirZ, hitX, hitY, hitZ, hitT, TResid, LPhot,LMuon, Oangle); 
   //     double Ptemp = pdf->MakeChromPeakPDF(TResid,LPhot,sigma0); 
   if(filtered) hltrackdata->Fill(LMuon); 
    hltrackdataall->Fill(LMuon); //Ltrack only
   // hltrackdataall->Fill(Oangle); //Opening angle only
     ifilter++; 
     //} //loop of the filter
  } //loop over hits
  } // loop over events
  
  //****************************************************************
  /* // PDFC


  Double_t Norm       = 10.0;
  Double_t softcutoff = 120.0;//80 400MeV muon, 500 1.2GeV muon
  Double_t highcut=500;
  Double_t earlysigma = 2.0/sqrt(Norm); // P(l=-20cm)=0.01
  Double_t earlycut   = 0; //2.0*earlysigma; 
  Double_t latesigma  = 200.0;// latesigma = 25.0/(10.0*sqrt(Norm)); // P(l=525cm)=0.01
  Double_t latecut    = softcutoff+25.0;
  Double_t normF      = 1.0/((earlysigma+latesigma)*(TMath::Pi()/2.0)+softcutoff);
  
 Int_t nbin = hltrackdata->GetNbinsX();
  Double_t width = hltrackdata->GetBinWidth(1);
  Double_t minedge = hltrackdata->GetBinLowEdge(1);
  for(int i=1;i<nbin+1;i++){
      Double_t PLmu       = 0.0;
 Double_t distMuon = minedge + (i-0.5)*width; 
   

 //if( distMuon > (highcut) ) PLmu = Norm/(1.0+((distMuon-highcut+earlycut)*(distMuon-highcut+earlycut)/(5*5)));
 // else
 if( distMuon > (softcutoff-earlycut) ) PLmu = Norm/(1.0+((distMuon-softcutoff+earlycut)*(distMuon-softcutoff+earlycut)/(latesigma*latesigma)));
 else if ( distMuon > (-1.0*earlycut)) PLmu = Norm;
 else PLmu = Norm/(1.0+((distMuon+earlycut)*(distMuon+earlycut))/(earlysigma*earlysigma));//-1.0
 //hltrackmc->SetBinContent(i,PLmu);
 //try to introduce the correct bias
 Double_t bias= hltrackdataall->GetBinContent(i);
 hltrackmc->SetBinContent(i,bias*PLmu);
  }

  */
//****************************************************************
  // PDFD
  /*

  Double_t Norm       = 10.0;
  Double_t softcutoff = 200.0;//80 400MeV muon, 500 1.2GeV muon
  Double_t highcut=500;
  Double_t earlysigma = 2.0/sqrt(Norm); // P(l=-20cm)=0.01
  Double_t earlycut   = 0; //2.0*earlysigma; 
  Double_t latesigma  = 200.0;// latesigma = 25.0/(10.0*sqrt(Norm)); // P(l=525cm)=0.01
  Double_t latecut    = softcutoff+25.0;
  Double_t normF      = 1.0/((earlysigma+latesigma)*(TMath::Pi()/2.0)+softcutoff);
  
 Int_t nbin = hltrackdata->GetNbinsX();
  Double_t width = hltrackdata->GetBinWidth(1);
  Double_t minedge = hltrackdata->GetBinLowEdge(1);
  for(int i=1;i<nbin+1;i++){
      Double_t PLmu       = 0.0;
 Double_t distMuon = minedge + (i-0.5)*width; 
   

 //if( distMuon > (highcut) ) PLmu = Norm/(1.0+((distMuon-highcut+earlycut)*(distMuon-highcut+earlycut)/(5*5)));
 // else
 if( distMuon > (softcutoff-earlycut) ) PLmu = Norm/(1.0+((distMuon-softcutoff+earlycut)*(distMuon-softcutoff+earlycut)/(latesigma*latesigma)));
 else if ( distMuon > (-1.0*earlycut)) PLmu = Norm;
 else PLmu = Norm/(1.0+((distMuon+earlycut)*(distMuon+earlycut))/(earlysigma*earlysigma));//-1.0
 //hltrackmc->SetBinContent(i,PLmu);
 //try to introduce the correct bias
 Double_t bias= hltrackdataall->GetBinContent(i);
 hltrackmc->SetBinContent(i,bias*PLmu);
  }
  */
   //****************************************************************
  // PDFA MUON ORIGINAL FUNCTION FROM MY VERTEX FINDER
  //works for 1.2 GeV muon
  
  Double_t Norm       = 10.0;
  Double_t softcutoff = 350.0;//80 400MeV muon, 500 1.2GeV muon 350 
  Double_t earlysigma = 2.0/sqrt(Norm); // P(l=-20cm)=0.01
  Double_t earlycut   = -20; //2.0*earlysigma; 
  Double_t latesigma  = 5.0; latesigma = 25.0/(10.0*sqrt(Norm)); // P(l=525cm)=0.01
  Double_t latecut    = softcutoff+25.0;
  Double_t normF      = 1.0/((earlysigma+latesigma)*(TMath::Pi()/2.0)+softcutoff);
  
 Int_t nbin = hltrackdata->GetNbinsX();
  Double_t width = hltrackdata->GetBinWidth(1);
  Double_t minedge = hltrackdata->GetBinLowEdge(1);
  for(int i=1;i<nbin+1;i++){
      Double_t PLmu       = 0.0;
 Double_t distMuon = minedge + (i-0.5)*width; 
   

 if( distMuon > (softcutoff-earlycut) ) PLmu = Norm/(1.0+((distMuon-softcutoff+earlycut)*(distMuon-softcutoff+earlycut)/(latesigma*latesigma)));
      else if ( distMuon > (-1.0*earlycut)) PLmu = Norm;
      else PLmu = Norm/(1.0+((distMuon+earlycut)*(distMuon+earlycut))/(earlysigma*earlysigma));//-1.0
      // hltrackmc->SetBinContent(i,PLmu);
      //try to introduce the correct bias
      Double_t bias= hltrackdataall->GetBinContent(i);
      hltrackmc->SetBinContent(i,bias*PLmu);
  }
  
  //**************************
  
  hltrackdataall->SetTitle("1200 MeV 200 kton muon");
  hltrackmc->SetTitle("1200 MeV 200 kton muon, PDFA");
  // hltrackdataall->SetTitle("400 MeV 50 kton muon, PDFC, Biased");
  
  //Oangle only
  // hltrackdataall->SetTitle("1200 MeV 200 kton muon, ALL");
  //hltrackdataall->SetTitle("1200 MeV 200 kton muon, ALL");
  
  TCanvas* ca1 = new TCanvas("ca1","ca1",500,300);
  //  hltrackdata->Sumw2();
  hltrackdataall->SetLineWidth(2);
  hltrackdataall->Draw();
  //  hltrackdataall->SetLineColor(kBlue);
   
   hltrackmc->Scale((hltrackdataall->GetMaximum())/(hltrackmc->GetMaximum()));
  hltrackmc->SetLineColor(kRed);
  hltrackmc->SetLineWidth(2);
   hltrackmc->Draw("same");
   /* 
  TFile myFile("muplusLtrackZoom.root","update");
  hltrackdataall->Write("1200MeV200ktonLtrack");
  hltrackmc->Write("1200MeV200ktonLtrackPDFA");*/
  /*
 
  //PDF only
  TCanvas* ca1 = new TCanvas("ca1","ca1",500,300);
  hltrackmc->SetTitle("PDF4");
 hltrackmc->SetLineColor(kRed);
 hltrackmc->SetLineWidth(2);
  hltrackmc->Draw();
  */
  /*
  //Oangle only  
  TLine l(42,-10000,42,1100000);
  l.SetLineColor(kRed);
  l.SetLineWidth(2);
  l.SetLineStyle(2);
  l.Draw("same");
  */
  //TFile myFile("muplusOangle.root","update");
  //hltrackdataall->Write("1200MeV200ktonOangle");
  
  // TString nameImage("400Ltrack");
  /* TString nameImage("400Oangle");
     nameImage+=(ievt-1);
     nameImage+=".pdf";
     ca1.Print(nameImage,"pdf");
  */
  }
