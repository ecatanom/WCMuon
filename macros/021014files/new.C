//============ calculate uncertainty =========================
  //Double_t lower = 0.32*ctr_extended_fit_pass;
  //Double_t mid = 0.5*ctr_extended_fit_pass;
  Double_t level = 0.68*ctr_extended_fit_pass;
  Double_t totalcontent = 0.0;
  Double_t totalerr = 0.0;
  Int_t iupper = 0;
  Int_t ilower = 0;
  Int_t imid = 0;

  Double_t content[nbin];
  Double_t binerr[nbin];
  testconh->Sumw2();
  for( Int_t j=0;j<nbin;j++ ){
    content[j] = testconh->GetBinContent(j);
    Double_t ierr = testconh->GetBinError(j);
    binerr[j] = ierr*ierr;
  }
   
  do{
    totalcontent += content[iupper];
    totalerr += binerr[iupper];
    iupper += 1; 
    //cout << iupper << " " << content << " " << binerr << " " << totalerr << endl;
  } while( (totalcontent-sqrt(totalerr)) < level );
  Double_t upper = (iupper - 1.0)*range/nbin + (range/nbin)*(level - totalcontent + sqrt(totalerr) + content[iupper-1])/content[iupper-1];
  
  totalcontent = 0.0;
  totalerr = 0.0;
  do{
    totalcontent += content[imid];
    totalerr += binerr[imid];
    imid += 1; 
    //cout << imid << " " << content << " " << binerr << " " << totalerr << endl;
  } while( (totalcontent) < level );
  Double_t mid = (imid - 1.0)*range/nbin + (range/nbin)*(level - totalcontent + content[imid-1])/content[imid-1];
  //cout << imid << " " << range/nbin << " " << content[imid-1] << " " << (level  - totalcontent + content[imid-1]) << endl;
  
  totalcontent = 0.0;
  totalerr = 0.0;
  do{
    totalcontent += content[ilower];
    totalerr += binerr[ilower];
    ilower += 1; 
    //cout << ilower << " " << content << " " << binerr << " " << totalerr << endl;
  } while( (totalcontent+sqrt(totalerr)) < level );
  Double_t lower = (ilower - 1.0)*range/nbin + (range/nbin)*(level - totalcontent - sqrt(totalerr) + content[ilower-1])/content[ilower-1];

  std::cout << "(" << mid << ", -" << mid-lower << ", +" << upper-mid << ")" << std::endl;

  //================
