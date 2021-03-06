void Ioana_wc_eventntuple_MultiJobs(std::string inputFile, std::string type, std::string outFile, int jobs)
{
 
  gSystem->Load("libGeom");
  gSystem->Load("libEve");
  gSystem->Load("libMinuit"); 
  gSystem->Load("libCintex");
  Cintex::Enable();
  gSystem->Load("libWCSimRootDict");
  gSystem->Load("libWCSimRoot.so");
  gSystem->Load("libWCSimAnalysis.so");
  
  //string inputFile = "muon_minus_000400MeV_200kton.0000";
  //string inputFile = "muon_plus_000800MeV_200kton.0000";
  //string inputFile = "muon_plus_001200MeV_200kton.0000";
  //string inputFile = "muon_minus_001600MeV_200kton.0001";
  //string inputFile = "muon_plus_002000MeV_200kton.0000";
  //string inputFile = "muon_plus_002400MeV_200kton.0000";
  //string inputFile = "muon_plus_002800MeV_200kton.0000";
  //string inputFile = "muon_plus_003200MeV_200kton.0000";
  //string inputFile = "muon_plus_003600MeV_200kton.0000";
  //string inputFile = "muon_plus_004000MeV_200kton.0000";
  //string inputFile = "muon_plus_004400MeV_200kton.0000";
  //string inputFile = "muon_plus_004800MeV_200kton.0000";
  

  // Configuration
  // =============
  WCSimRingFinder::UseRecoVertex();      // suppress ring finder

  // Print Parameters
  // ================
  WCSimParameters::PrintParameters();
  WCSimDataCleaner::PrintParameters();
  WCSimVertexFinder::PrintParameters();
  WCSimRingFinder::PrintParameters();

  // Load Data
  // ========= 
  //WCSimInterface::LoadData(("/lbne/data/water/sim200kton_20111017/singleparticle/rootfiles/"+ inputFile +".root").c_str());
  WCSimInterface::LoadData(inputFile.c_str());
  WCSimInterface::SetToUseTrueHits();
  //WCSimInterface::Instance()->UsePMTPosition();
  WCSimInterface::Instance()->SmearTrueHits(0.25);//Erika isChanging this 
  WCSimDataCleaner::Instance()->NeighbourRadius(220.0); // orig 300 c 250
  WCSimDataCleaner::Instance()->NeighbourDigits(10.0);//orig 50 c 40
  //WCSimDataCleaner::Instance()->TimeWindow(25.0);
  WCSimDataCleaner::Instance()->SetMinPulseHeight(-1.0);
  WCSimInterface::Instance()->SetToMCP();
  //WCSimInterface::Instance()->SetToGated();

  WCSimDataCleaner::Instance()->SetClusterRadius(300.0);// orig 300 
  WCSimDataCleaner::Instance()->SetClusterDigits(50.0); //  orig 50 
  WCSimDataCleaner::Instance()->SetTimeWindowNeighbours(25.0);//orig 25 b 15
  WCSimDataCleaner::Instance()->SetTimeWindowClusters(25.0); //orig 25 b 15
  //WCSimVertexFinder::LMuonDoubleFilter(200);


  // Create Ntuple Writer
  // ====================
  WCSimNtupleWriter* ntpwriter = new WCSimNtupleWriter();

  // type of ntuple
  // ==============
  ntpwriter->UseNtuple(type.c_str());
  //ntpwriter->UseNtuple("Reco");
  // ntpwriter->UseNtuple("Vertex");
  // ntpwriter->UseNtuple("VertexSeed");

  // set file name
  // =============
  //outfileName = "ntuple_"+type+"_"+inputFile+"testchrom.root";
  ntpwriter->SetFileName(outFile.c_str());
   //ntpwriter->SetFileName(("ntuple_reco_"+inputFile+".root").c_str());
   //ntpwriter->SetFileName(("ntuple_vertex_"+inputFile+".root").c_str());

  // loop over events
  // =================
  ntpwriter->Run((1*jobs), (jobs*1+1));

  WCSimRecoObjectTable::Instance()->Print();
 
}
