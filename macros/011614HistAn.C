{

#include<TFile.h>;
  TFile *cleaning5 = new TFile ("/lbne/app/users/ecatanom/WCSimAnalysis/macros/myCleaningFile5.root");
  TFile * cleaning8= new TFile ("/lbne/app/users/ecatanom/WCSimAnalysis/macros/myCleaningFile8.root");
  TFile * cleaning13 = new TFile ("/lbne/app/users/ecatanom/WCSimAnalysis/macros/myCleaningFile13.root");
  TFile * cleaning20= new TFile ("/lbne/app/users/ecatanom/WCSimAnalysis/macros/myCleaningFile20.root");


// TH1D * h51 = (TH1D* )cleaning5.Get("histDrsq;1");
// TH1D * h81 = (TH1D* )cleaning8.Get("histDrsq;1");
// TH1D * h131 = (TH1D* )cleaning13.Get("histDrsq;1");
// TH1D * h201 = (TH1D* )cleaning20.Get("histDrsq;1");

// TH1D * h52 = (TH1D* )cleaning5.Get("histDrsq;2");
// TH1D * h82 = (TH1D* )cleaning8.Get("histDrsq;2");
// TH1D * h132 = (TH1D* )cleaning13.Get("histDrsq;2");
// TH1D * h202 = (TH1D* )cleaning20.Get("histDrsq;2");

// TH1D * h53 = (TH1D* )cleaning5.Get("histDrsq;3");
// TH1D * h83 = (TH1D* )cleaning8.Get("histDrsq;3");
// TH1D * h133 = (TH1D* )cleaning13.Get("histDrsq;3");
// TH1D * h203 = (TH1D* )cleaning20.Get("histDrsq;3");

// TH1D * h54 = (TH1D* )cleaning5.Get("histDrsq;4");
// TH1D * h84 = (TH1D* )cleaning8.Get("histDrsq;4");
// TH1D * h134 = (TH1D* )cleaning13.Get("histDrsq;4");
// TH1D * h204 = (TH1D* )cleaning20.Get("histDrsq;4");

// TH1D * h55 = (TH1D* )cleaning5.Get("histDrsq;5");
// TH1D * h85 = (TH1D* )cleaning8.Get("histDrsq;5");
// TH1D * h135 = (TH1D* )cleaning13.Get("histDrsq;5");
// TH1D * h205 = (TH1D* )cleaning20.Get("histDrsq;5");

// TH1D * h56 = (TH1D* )cleaning5.Get("histDrsq;6");
// TH1D * h86 = (TH1D* )cleaning8.Get("histDrsq;6");
// TH1D * h136 = (TH1D* )cleaning13.Get("histDrsq;6");
// TH1D * h206 = (TH1D* )cleaning20.Get("histDrsq;6");
 
 gStyle->SetTitleFontSize(0.07);

TCanvas *ca1 = new TCanvas("ca1","dR",400,300);
//ca1->Divide(3,2);
 
// //  ca1->cd(1);
//  gPad->SetLogy(); 
//  h201->SetTitle("1225");
//  h201->GetYaxis()->SetTitle("dR");
//  h201->Draw();
//  h51->SetLineColor(kGreen);
//  h81->SetLineColor(kBlue);
//  h131->SetLineColor(kRed);
//  h51->Draw("same");
//  h81->Draw("same");
//  h131->Draw("same");

// ca1->cd(2);
// gPad->SetLogy(); 
//  h202->SetTitle("1356");
//  h202->GetYaxis()->SetTitle("dR");
//  h202->Draw();
//  h52->SetLineColor(kGreen);
//  h82->SetLineColor(kBlue);
//  h132->SetLineColor(kRed);
//  h52->Draw("same");
//  h82->Draw("same");
//  h132->Draw("same");


// ca1->cd(3);
// gPad->SetLogy(); 
//  h203->SetTitle("1457");
//  h203->GetYaxis()->SetTitle("dR");
//  h203->Draw();
//  h53->SetLineColor(kGreen);
//  h83->SetLineColor(kBlue);
//  h133->SetLineColor(kRed);
//  h53->Draw("same");
//  h83->Draw("same");
//  h133->Draw("same");


// ca1->cd(4);
//  gPad->SetLogy(); 
//  h204->SetTitle("1744");
//  h204->GetYaxis()->SetTitle("dR");
//  h204->Draw();
//  h54->SetLineColor(kGreen);
//  h84->SetLineColor(kBlue);
//  h134->SetLineColor(kRed);
//  h54->Draw("same");
//  h84->Draw("same");
//  h134->Draw("same");

// ca1->cd(5);
//  gPad->SetLogy(); 
//  h205->SetTitle("26");
//  h205->GetYaxis()->SetTitle("dR");
//  h205->Draw();
//  h55->SetLineColor(kGreen);
//  h85->SetLineColor(kBlue);
//  h135->SetLineColor(kRed);
//  h55->Draw("same");
//  h85->Draw("same");
//  h135->Draw("same");

// ca1->cd(6);
 // gPad->SetLogy(); 
//  h206->SetTitle("323");
//  h206->GetYaxis()->SetTitle("dR");
//  h206->Draw();
//  h56->SetLineColor(kGreen);
//  h86->SetLineColor(kBlue);
//  h136->SetLineColor(kRed);
//  h56->Draw("same");
//  h86->Draw("same");
//  h136->Draw("same");


//  TImage *img1 = TImage::Create();
//  img1->FromPad(ca1);
//  img1->  WriteImage("/lbne/data2/users/ecatanom/011614files/dR6.png");
 

//  TH1D * h51 = (TH1D* )cleaning5.Get("histDt;6");
//  TH1D * h81 = (TH1D* )cleaning8.Get("histDt;6");
//  TH1D * h131 = (TH1D* )cleaning13.Get("histDt;6");
//  TH1D * h201 = (TH1D* )cleaning20.Get("histDt;6");

 TH1D * h51 = (TH1D* )cleaning5.Get("histNeighb;5");
 TH1D * h81 = (TH1D* )cleaning8.Get("histNeighb;5");
 TH1D * h131 = (TH1D* )cleaning13.Get("histNeighb;5");
 TH1D * h201 = (TH1D* )cleaning20.Get("histNeighb;5");
 gPad->SetLogy(); 
 //h201->Rebin(2);
  //h131->Rebin(2);
  //h81->Rebin(2);
 //h51->Rebin(2);
 h201->SetTitle("2");
 h201->GetYaxis()->SetTitle("NNeighb");
 //h201->SetMinimum(10);
 h201->GetXaxis()->SetRangeUser(0,1000);
h201->Draw();
 h51->SetLineColor(kGreen);
 h81->SetLineColor(kBlue);
 h131->SetLineColor(kRed);
 h51->Draw("same");
 h81->Draw("same");
 h131->Draw("same");

TImage *img1 = TImage::Create();
  img1->FromPad(ca1);
  //img1->  WriteImage("/lbne/data2/users/ecatanom/011614files/Neighb6b.png");
 
}
