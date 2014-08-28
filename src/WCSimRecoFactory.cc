#include "WCSimRecoFactory.hh"
#include "WCSimReco.hh"
#include "WCSimRecoAB.hh"

#include <string>
#include <iostream>
#include <cassert>

ClassImp(WCSimRecoFactory)

static WCSimRecoFactory* fgRecoFactory = 0;

WCSimRecoFactory* WCSimRecoFactory::Instance()
{
  if(!fgRecoFactory){
    fgRecoFactory = new WCSimRecoFactory();
  }

  // die if finder hasn't actually been created
  if(!fgRecoFactory){
    assert(fgRecoFactory);
  }

  // can do re-setting here
  if(fgRecoFactory){

  }

  return fgRecoFactory;
}

WCSimReco* WCSimRecoFactory::MakeReco()
{
  return this->MakeReco("default");
}

WCSimReco* WCSimRecoFactory::MakeReco(const char *name)
{
  if( strcmp(name,"default")==0 ) {
    WCSimReco* reco = new WCSimRecoAB();
    return reco;
  }

  if( strcmp(name,"AB")==0 ) {
    WCSimReco* reco = new WCSimRecoAB();
    return reco;
  }

  return 0;
}

WCSimRecoFactory::WCSimRecoFactory()
{
  
}

WCSimRecoFactory::~WCSimRecoFactory()
{

}
