/*Este programa imprime event displays  
Puede aplicar filtros simples

*/

{

  // Load libraries
  // ==============
  //gROOT->Reset();
  gSystem->Load("libGeom");
  gSystem->Load("libEve");
  gSystem->Load("libMinuit");
  gSystem->Load("libCintex");
  Cintex::Enable();
  gSystem->Load("libWCSimRootDict");
  gSystem->Load("libWCSimRoot.so");
  gSystem->Load("libWCSimAnalysis.so");
  
  // Path to WCSim ROOT file
  // =======================
  //TString filename("/lbne/data/water/sim200kton_20111017/singleparticle/wcsimlc/muon_plus_001200MeV_200kton.0001_13percentbare_DetDev_MuSct_Ion.root");
  string mycoverage ="20";
  TString filename("/lbne/data/users/ecatanom/samples/muplus_1200mev_500kton_10inch_"+mycoverage+"per_hqe_MuSct.root");



  Double_t TResid, LPhot, LMuon, Oangle;
  double bdeltaT, rdeltaT;
  Double_t trueX ;
  Double_t trueY;
  Double_t trueZ ;
  Double_t dirX ;
  Double_t dirY ;
  Double_t dirZ ;
  Double_t trueT ;
  double theta ;
  int myNdigits;
  int NFilterdigits;

  int myeventnumber=0;
  
  // Load Data
  // =========
  WCSimInterface::LoadData(filename);

  // get first entry
  Bool_t truehit = 1; // 1 is to use true hits
  Bool_t filtered = 1; // 1 is to use Andy's cut
  Bool_t Lmu = 0; // 1 is to use LMuon cut
  Double_t sigma0 = 0.1; //sigma0 = 0.1;
  if(truehit) {WCSimInterface::SetToUseTrueHits();
    WCSimInterface::Instance()->SmearTrueHits(sigma0);}

  WCSimDataCleaner::Instance()->SetMinPulseHeight(-1.0);
  WCSimDataCleaner::Instance()->SetNeighbourRadius(350.0); 
  WCSimDataCleaner::Instance()->SetNeighbourDigits(75.0);//a 50 b 70
  WCSimDataCleaner::Instance()->SetClusterRadius(350.0);
  WCSimDataCleaner::Instance()->SetClusterDigits(75.0);
  WCSimDataCleaner::Instance()->SetTimeWindowNeighbours(25.0);
  WCSimDataCleaner::Instance()->SetTimeWindowClusters(25.0);

  WCSimInterface::Instance()->SetToMCP();
  //WCSimInterface::Instance()->SetToGated();

  // =========================

  //WCSimVertexFinder::UseTrueVertex(); // use true vertex
  //WCSimRingFinder::UseRecoVertex();  //comment for better ring 
  // WCSimVertexFinder::LMuonDoubleFilter(300);
  //WCSimVertexFinder::PointFitOnly();

  WCSimDisplayAB* mydisplay=new WCSimDisplayAB();
  mydisplay->PrintGIF();
  
  int thelist[]={1225,1356,1457,1744,26,323};
for(int ecounter=0;ecounter<6;ecounter++){
    myeventnumber=thelist[ecounter];
    WCSimInterface::LoadEvent(myeventnumber);
    
    WCSimRecoEvent* theRecoEvent;
    WCSimTrueEvent* theTrueEvent;
    theRecoEvent = WCSimInterface::RecoEvent();
    theTrueEvent = WCSimInterface::TrueEvent();
    WCSimRecoAB* haReco = new WCSimRecoAB(); //run filters
    haReco->RunFilter(theRecoEvent);

    mydisplay->DrawDisplay(theRecoEvent);
    //myfakedisplay->DrawTrueEvent(theTrueEvent);
    //myfakedisplay->DrawRecoEvent(theRecoEvent);
    mydisplay->PrintDisplay();
    cout <<"============================================="<<ecounter<<endl;
  }
TString mycleaning="mv myCleaningFile.root myCleaningFile"+mycoverage+".root";
gSystem->Exec(mycleaning);
  return;

  
 


  
}

