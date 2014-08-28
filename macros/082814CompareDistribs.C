{
  /*
  //Compare Oangle
  TFile myFile ("muplusOangle.root","read");
  TH1D * h400M50 = (TH1D*) myFile.Get("400MeV50ktonOangle");
  TH1D * h400M200 = (TH1D*) myFile.Get("400MeV200ktonOangle");
  TH1D * h1200M200 = (TH1D*) myFile.Get("1200MeV200ktonOangle");

  h400M50->SetLineColor(kRed);
  h400M200->SetLineColor(kBlue);


 gStyle->SetOptTitle(kFALSE);
  TCanvas c1;
  // h400M50->SetTitle("");
  h400M50->DrawNormalized();
  h400M200->DrawNormalized("same");
 h1200M200->DrawNormalized("same");


 leg = new TLegend(0.15,0.65,0.5,0.85);
 leg->SetHeader("Compare Oangle");
 leg->AddEntry(h400M50,"","l");
 leg->AddEntry(h400M200,"","l");
 leg->AddEntry(h1200M200,"","l");
 leg->Draw("same");
  */

  //Compare Ltrack

TFile myFile ("muplusLtrackZoom.root","read");
  TH1D * h400M50 = (TH1D*) myFile.Get("400MeV50ktonLtrack");
  TH1D * h400M200 = (TH1D*) myFile.Get("400MeV200ktonLtrack");
  TH1D * h1200M200 = (TH1D*) myFile.Get("1200MeV200ktonLtrack");

  TH1D * h400M50B = (TH1D*) myFile.Get("400MeV50ktonLtrackPDFB");
  TH1D * h400M200B = (TH1D*) myFile.Get("400MeV200ktonLtrackPDFB");
  TH1D * h1200M200A = (TH1D*) myFile.Get("1200MeV200ktonLtrackPDFA");

  h400M50B->SetLineColor(kRed);
  h400M200B->SetLineColor(kBlue);
  
  gStyle->SetOptTitle(kFALSE);
  TCanvas c1;
  // h400M50->SetTitle("");
  h400M50B->DrawNormalized();
  h400M200B->DrawNormalized("same");
 h1200M200A->DrawNormalized("same");


 leg = new TLegend(0.55,0.65,0.9,0.85);
 leg->SetHeader("Compare Ltrack");
 leg->AddEntry(h400M50B,"","l");
 leg->AddEntry(h400M200B,"","l");
 leg->AddEntry(h1200M200A,"","l");
 leg->Draw("same");
}
