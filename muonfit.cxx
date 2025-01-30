#include <typeinfo>

#include "runEW.h"

// If the binning changes, change these values to match and the histograms correspond
 static const Int_t Mjj_nbins = 6;
 static const Double_t Mjj_bins[Mjj_nbins+1] = {500, 1000,1500, 2250, 3000, 4000, 6000};
 static const Int_t Ptjj_nbins = 6;
 static const Double_t Ptjj_bins[Ptjj_nbins+1] = {0, 70, 140, 250, 400, 550, 1050};
 static const Int_t dPhijj_nbins = 12;
 static const Double_t dPhijj_bins[dPhijj_nbins+1] = {-1.0000, -0.9375, -0.8750, -0.7500, -0.500, -0.2500, 0.0, 0.2500, 0.500, 0.7500, 0.8750, 0.9375, 1.0000};
 static const Int_t j1Pt_nbins = 5;
 static const Double_t j1Pt_bins[j1Pt_nbins+1] = {80, 140, 250, 400, 550, 1050};
 static const Int_t dYjj_nbins = 9;
 static const Double_t dYjj_bins[dYjj_nbins+1] = {2.0, 2.6, 3.1, 3.6, 3.9, 4.2, 4.6, 5.0, 6.0, 8.0};
 static const Int_t l1Pt_nbins = 5;
 static const Double_t l1Pt_bins[l1Pt_nbins+1] = {27, 80, 150, 250, 350, 700};
 static const Int_t l1Cent_nbins = 8;
 static const Double_t l1Cent_bins[l1Cent_nbins+1] = {0.0,0.2,0.4,0.6,0.8,1.2,1.6,2.0,2.5};


int main(int nargs, char* args[])
{

  if(nargs>2){
    cout <<
      "Error: Wrong arguments format\nShould be: runme [rootfile]\nwhere rootfile is the optional\nargument that specifies the file that will be created to put the results\n(default is results.root)\n";
    exit(1);
  }
  const Char_t* outfile;
  if(nargs==1){
    outfile="results.root";
  }else{
    outfile=args[1];
  }

TFile f1(outfile,"RECREATE");
  //A list processors, can append processors to it and will excecute all of them if you run the list
  QProcList l_arrayproc("Array Processor List", "Array Processor List");

  //Data Selector
 QArrayProcessor dataproc("Data Processor","Data Processor");
  //Adding processor to the list
  l_arrayproc.AddQProc(&dataproc);
  dataproc.AddProc("Selector", "Selector", Selector, NULL,kTRUE);
  //All branchs of TTree that will be used in selection
  //.AddIVar("Branch Name", "tree://PATHtoFile")
  dataproc.GetProc("Selector").AddIVar("dPhijj","tree://Ntuples/Data_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc.GetProc("Selector").AddIVar("dYjj","tree://Ntuples/Data_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc.GetProc("Selector").AddIVar("j1Pt","tree://Ntuples/Data_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc.GetProc("Selector").AddIVar("l1Pt","tree://Ntuples/Data_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc.GetProc("Selector").AddIVar("Mjj","tree://Ntuples/Data_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc.GetProc("Selector").AddIVar("Ptjj","tree://Ntuples/Data_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc.GetProc("Selector").AddIVar("passReco","tree://Ntuples/Data_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc.GetProc("Selector").AddIVar("cut","tree://Ntuples/Data_All_Years_muon_v23.5.root:CollectionTree_NOM");
  //dataproc.GetProc("Selector").AddIVar("passSR","tree://Ntuples/Data_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc.GetProc("Selector").AddIVar("nGapJets","tree://Ntuples/Data_All_Years_muon_v23.5.root:CollectionTree_NOM");

  //.AddPSProc means Add Post Selection Processor, will only run on selected events
  dataproc.AddPSProc("Data Fill","Data Fill", data_fill, NULL,kTRUE);
  //Get the TTree Branches
  dataproc.GetProc("Data Fill").AddIVar("dPhijj","tree://Ntuples/Data_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc.GetProc("Data Fill").AddIVar("dYjj","tree://Ntuples/Data_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc.GetProc("Data Fill").AddIVar("j1Pt","tree://Ntuples/Data_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc.GetProc("Data Fill").AddIVar("l1Pt","tree://Ntuples/Data_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc.GetProc("Data Fill").AddIVar("Mjj","tree://Ntuples/Data_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc.GetProc("Data Fill").AddIVar("Ptjj","tree://Ntuples/Data_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc.GetProc("Data Fill").AddIVar("l1Cent","tree://Ntuples/Data_All_Years_muon_v23.5.root:CollectionTree_NOM");
  
  //load 7D histogrma
  QHNF_I* data6d = new QHNF_I("Data_7D", "Data_7D", 7);
  gDirectory->Add(data6d);
  //Define axis characteristics 
  //SetAxis(axis, numberofbins, edges)
  data6d->SetAxis(0,dPhijj_nbins, dPhijj_bins);
  data6d->SetAxis(1,dYjj_nbins,dYjj_bins);
  data6d->SetAxis(2,j1Pt_nbins, j1Pt_bins);
  data6d->SetAxis(3,l1Pt_nbins,l1Pt_bins);
  data6d->SetAxis(4,Mjj_nbins, Mjj_bins);
  data6d->SetAxis(5,Ptjj_nbins,Ptjj_bins);
  data6d->SetAxis(6,l1Cent_nbins,l1Cent_bins);
  //Do not Normalize
  data6d->SetNormFlags(QDis::kNoNorm);

  dataproc.GetProc("Data Fill").AddOObj(data6d);

 
  //Add other Selectors for Monte Carlo Selector Observables
  //EW
  QArrayProcessor dataproc2("Data Processor 2","Data Processor 2");
  l_arrayproc.AddQProc(&dataproc2);
  dataproc2.AddProc("EW_Selector", "EW_Selector", Selector, NULL,kTRUE);
  dataproc2.GetProc("EW_Selector").AddIVar("dPhijj","tree://Ntuples/EW_Pow_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc2.GetProc("EW_Selector").AddIVar("dYjj","tree://Ntuples/EW_Pow_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc2.GetProc("EW_Selector").AddIVar("j1Pt","tree://Ntuples/EW_Pow_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc2.GetProc("EW_Selector").AddIVar("l1Pt","tree://Ntuples/EW_Pow_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc2.GetProc("EW_Selector").AddIVar("Mjj","tree://Ntuples/EW_Pow_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc2.GetProc("EW_Selector").AddIVar("Ptjj","tree://Ntuples/EW_Pow_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc2.GetProc("EW_Selector").AddIVar("passReco","tree://Ntuples/EW_Pow_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc2.GetProc("EW_Selector").AddIVar("cut","tree://Ntuples/EW_Pow_All_Years_muon_v23.5.root:CollectionTree_NOM");
  //dataproc2.GetProc("EW_Selector").AddIVar("passSR","tree://Ntuples/EW_Pow_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc2.GetProc("EW_Selector").AddIVar("nGapJets","tree://Ntuples/EW_Pow_All_Years_muon_v23.5.root:CollectionTree_NOM");


  dataproc2.AddPSProc("EW Fill","EW Fill", MC_fill, NULL,kTRUE);
  //Get the TTree Branches
  dataproc2.GetProc("EW Fill").AddIVar("dPhijj","tree://Ntuples/EW_Pow_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc2.GetProc("EW Fill").AddIVar("dYjj","tree://Ntuples/EW_Pow_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc2.GetProc("EW Fill").AddIVar("j1Pt","tree://Ntuples/EW_Pow_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc2.GetProc("EW Fill").AddIVar("l1Pt","tree://Ntuples/EW_Pow_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc2.GetProc("EW Fill").AddIVar("Mjj","tree://Ntuples/EW_Pow_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc2.GetProc("EW Fill").AddIVar("Ptjj","tree://Ntuples/EW_Pow_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc2.GetProc("EW Fill").AddIVar("l1Cent","tree://Ntuples/EW_Pow_All_Years_muon_v23.5.root:CollectionTree_NOM"); 
  dataproc2.GetProc("EW Fill").AddIVar("Lumi","tree://Ntuples/EW_Pow_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc2.GetProc("EW Fill").AddIVar("finalWeight","tree://Ntuples/EW_Pow_All_Years_muon_v23.5.root:CollectionTree_NOM");
  //dataproc2.GetProc("EW Fill").AddIVar("passSR","tree://Ntuples/EW_Pow_All_Years_muon_v23.5.root:CollectionTree_NOM");

QHNF_D* sr_ew6d = new QHNF_D("EW_7D", "EW_7D", 7);
  //gDirectory adds to the output file
  gDirectory->Add(sr_ew6d);
  //Define axis characteristics 
  sr_ew6d->SetAxis(0,dPhijj_nbins, dPhijj_bins);
  sr_ew6d->SetAxis(1,dYjj_nbins,dYjj_bins);
  sr_ew6d->SetAxis(2,j1Pt_nbins, j1Pt_bins);
  sr_ew6d->SetAxis(3,l1Pt_nbins,l1Pt_bins);
  sr_ew6d->SetAxis(4,Mjj_nbins, Mjj_bins);
  sr_ew6d->SetAxis(5,Ptjj_nbins,Ptjj_bins);
  sr_ew6d->SetAxis(6,l1Cent_nbins, l1Cent_bins);

  sr_ew6d->SetNormFlags(QDis::kNoNorm);

  dataproc2.GetProc("EW Fill").AddOObj(sr_ew6d);



  //QCD
  QArrayProcessor dataproc3("Data Processor 3","Data Processor 3");
  l_arrayproc.AddQProc(&dataproc3);
  dataproc3.AddProc("QCD_Selector", "QCD_Selector", QCD_Selector, NULL,kTRUE);
  dataproc3.GetProc("QCD_Selector").AddIVar("dPhijj","tree://Ntuples/QCD_Wjets_Powheg_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc3.GetProc("QCD_Selector").AddIVar("dYjj","tree://Ntuples/QCD_Wjets_Powheg_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc3.GetProc("QCD_Selector").AddIVar("j1Pt","tree://Ntuples/QCD_Wjets_Powheg_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc3.GetProc("QCD_Selector").AddIVar("l1Pt","tree://Ntuples/QCD_Wjets_Powheg_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc3.GetProc("QCD_Selector").AddIVar("Mjj","tree://Ntuples/QCD_Wjets_Powheg_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc3.GetProc("QCD_Selector").AddIVar("Ptjj","tree://Ntuples/QCD_Wjets_Powheg_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc3.GetProc("QCD_Selector").AddIVar("passReco","tree://Ntuples/QCD_Wjets_Powheg_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc3.GetProc("QCD_Selector").AddIVar("cut","tree://Ntuples/QCD_Wjets_Powheg_All_Years_muon_v23.5.root:CollectionTree_NOM");
  //dataproc3.GetProc("QCD_Selector").AddIVar("passSR","tree://Ntuples/QCD_Wjets_Powheg_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc3.GetProc("QCD_Selector").AddIVar("nGapJets","tree://Ntuples/QCD_Wjets_Powheg_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc3.GetProc("QCD_Selector").AddIVar("finalWeight","tree://Ntuples/QCD_Wjets_Powheg_All_Years_muon_v23.5.root:CollectionTree_NOM");

  dataproc3.AddPSProc("QCD Fill","QCD Fill", MC_fill, NULL,kTRUE);
  //Get the TTree Branches
  dataproc3.GetProc("QCD Fill").AddIVar("dPhijj","tree://Ntuples/QCD_Wjets_Powheg_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc3.GetProc("QCD Fill").AddIVar("dYjj","tree://Ntuples/QCD_Wjets_Powheg_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc3.GetProc("QCD Fill").AddIVar("j1Pt","tree://Ntuples/QCD_Wjets_Powheg_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc3.GetProc("QCD Fill").AddIVar("l1Pt","tree://Ntuples/QCD_Wjets_Powheg_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc3.GetProc("QCD Fill").AddIVar("Mjj","tree://Ntuples/QCD_Wjets_Powheg_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc3.GetProc("QCD Fill").AddIVar("Ptjj","tree://Ntuples/QCD_Wjets_Powheg_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc3.GetProc("QCD Fill").AddIVar("l1Cent","tree://Ntuples/QCD_Wjets_Powheg_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc3.GetProc("QCD Fill").AddIVar("Lumi","tree://Ntuples/QCD_Wjets_Powheg_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc3.GetProc("QCD Fill").AddIVar("finalWeight","tree://Ntuples/QCD_Wjets_Powheg_All_Years_muon_v23.5.root:CollectionTree_NOM");
  //dataproc3.GetProc("QCD Fill").AddIVar("passSR","tree://Ntuples/QCD_Wjets_Powheg_All_Years_muon_v23.5.root:CollectionTree_NOM");

QHNF_D* sr_qcd6d = new QHNF_D("QCD_7D", "QCD_7D", 7);
  gDirectory->Add(sr_qcd6d);
  //Define axis characteristics 
  sr_qcd6d->SetAxis(0,dPhijj_nbins, dPhijj_bins);
  sr_qcd6d->SetAxis(1,dYjj_nbins,dYjj_bins);
  sr_qcd6d->SetAxis(2,j1Pt_nbins, j1Pt_bins);
  sr_qcd6d->SetAxis(3,l1Pt_nbins,l1Pt_bins);
  sr_qcd6d->SetAxis(4,Mjj_nbins, Mjj_bins);
  sr_qcd6d->SetAxis(5,Ptjj_nbins,Ptjj_bins);
  sr_qcd6d->SetAxis(6,l1Cent_nbins,l1Cent_bins);

  sr_qcd6d->SetNormFlags(QDis::kNoNorm);

  dataproc3.GetProc("QCD Fill").AddOObj(sr_qcd6d);


 QArrayProcessor dataproc4("Data Processor 4","Data Processor 4");
 l_arrayproc.AddQProc(&dataproc4);
  dataproc4.AddProc("NonW_Selector", "NonW_Selector", Selector, NULL,kTRUE);
  dataproc4.GetProc("NonW_Selector").AddIVar("dPhijj","tree://Ntuples/NonW_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc4.GetProc("NonW_Selector").AddIVar("dYjj","tree://Ntuples/NonW_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc4.GetProc("NonW_Selector").AddIVar("j1Pt","tree://Ntuples/NonW_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc4.GetProc("NonW_Selector").AddIVar("l1Pt","tree://Ntuples/NonW_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc4.GetProc("NonW_Selector").AddIVar("Mjj","tree://Ntuples/NonW_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc4.GetProc("NonW_Selector").AddIVar("Ptjj","tree://Ntuples/NonW_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc4.GetProc("NonW_Selector").AddIVar("passReco","tree://Ntuples/NonW_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc4.GetProc("NonW_Selector").AddIVar("cut","tree://Ntuples/NonW_All_Years_muon_v23.5.root:CollectionTree_NOM");
  //dataproc4.GetProc("NonW_Selector").AddIVar("passSR","tree://Ntuples/NonW_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc4.GetProc("NonW_Selector").AddIVar("nGapJets","tree://Ntuples/NonW_All_Years_muon_v23.5.root:CollectionTree_NOM");

  dataproc4.AddPSProc("NonW Fill","NonW Fill", MC_fill, NULL,kTRUE);
  //Get the TTree Branches
  dataproc4.GetProc("NonW Fill").AddIVar("dPhijj","tree://Ntuples/NonW_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc4.GetProc("NonW Fill").AddIVar("dYjj","tree://Ntuples/NonW_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc4.GetProc("NonW Fill").AddIVar("j1Pt","tree://Ntuples/NonW_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc4.GetProc("NonW Fill").AddIVar("l1Pt","tree://Ntuples/NonW_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc4.GetProc("NonW Fill").AddIVar("Mjj","tree://Ntuples/NonW_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc4.GetProc("NonW Fill").AddIVar("Ptjj","tree://Ntuples/NonW_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc4.GetProc("NonW Fill").AddIVar("l1Cent","tree://Ntuples/NonW_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc4.GetProc("NonW Fill").AddIVar("Lumi","tree://Ntuples/NonW_All_Years_muon_v23.5.root:CollectionTree_NOM");
  dataproc4.GetProc("NonW Fill").AddIVar("finalWeight","tree://Ntuples/NonW_All_Years_muon_v23.5.root:CollectionTree_NOM");
 // dataproc4.GetProc("NonW Fill").AddIVar("passSR","tree://Ntuples/NonW_All_Years_muon_v23.5.root:CollectionTree_NOM");

QHNF_D* sr_nonw6d = new QHNF_D("NonW_7D", "NonW_7D", 7);
  gDirectory->Add(sr_nonw6d);
  //Define axis characteristics 
 sr_nonw6d->SetAxis(0,dPhijj_nbins, dPhijj_bins);
  sr_nonw6d->SetAxis(1,dYjj_nbins,dYjj_bins);
  sr_nonw6d->SetAxis(2,j1Pt_nbins, j1Pt_bins);
  sr_nonw6d->SetAxis(3,l1Pt_nbins,l1Pt_bins);
  sr_nonw6d->SetAxis(4,Mjj_nbins, Mjj_bins);
  sr_nonw6d->SetAxis(5,Ptjj_nbins,Ptjj_bins);
  sr_nonw6d->SetAxis(6,l1Cent_nbins, l1Cent_bins);

  sr_nonw6d->SetNormFlags(QDis::kNoNorm);

  dataproc4.GetProc("NonW Fill").AddOObj(sr_nonw6d);


 QArrayProcessor dataproc5("Data Processor 5","Data Processor 5");
 l_arrayproc.AddQProc(&dataproc5);
  dataproc5.AddProc("Multijet_Selector", "Multijet_Selector", Selector, NULL,kTRUE);
  dataproc5.GetProc("Multijet_Selector").AddIVar("dPhijj","tree://Ntuples/Multijet_All_muon_v23.5.root:CollectionTree_NOM");
  dataproc5.GetProc("Multijet_Selector").AddIVar("dYjj","tree://Ntuples/Multijet_All_muon_v23.5.root:CollectionTree_NOM");
  dataproc5.GetProc("Multijet_Selector").AddIVar("j1Pt","tree://Ntuples/Multijet_All_muon_v23.5.root:CollectionTree_NOM");
  dataproc5.GetProc("Multijet_Selector").AddIVar("l1Pt","tree://Ntuples/Multijet_All_muon_v23.5.root:CollectionTree_NOM");
  dataproc5.GetProc("Multijet_Selector").AddIVar("Mjj","tree://Ntuples/Multijet_All_muon_v23.5.root:CollectionTree_NOM");
  dataproc5.GetProc("Multijet_Selector").AddIVar("Ptjj","tree://Ntuples/Multijet_All_muon_v23.5.root:CollectionTree_NOM");
  dataproc5.GetProc("Multijet_Selector").AddIVar("passReco","tree://Ntuples/Multijet_All_muon_v23.5.root:CollectionTree_NOM");
  dataproc5.GetProc("Multijet_Selector").AddIVar("cut","tree://Ntuples/Multijet_All_muon_v23.5.root:CollectionTree_NOM");
  //dataproc5.GetProc("Multijet_Selector").AddIVar("passSR","tree://Ntuples/Multijet_All_muon_v23.5.root:CollectionTree_NOM");
  dataproc5.GetProc("Multijet_Selector").AddIVar("nGapJets","tree://Ntuples/Multijet_All_muon_v23.5.root:CollectionTree_NOM");

  dataproc5.AddPSProc("Multijet Fill","Multijet Fill", Multijet_fill, NULL,kTRUE);
  //Get the TTree Branches
  dataproc5.GetProc("Multijet Fill").AddIVar("dPhijj","tree://Ntuples/Multijet_All_muon_v23.5.root:CollectionTree_NOM");
  dataproc5.GetProc("Multijet Fill").AddIVar("dYjj","tree://Ntuples/Multijet_All_muon_v23.5.root:CollectionTree_NOM");
  dataproc5.GetProc("Multijet Fill").AddIVar("j1Pt","tree://Ntuples/Multijet_All_muon_v23.5.root:CollectionTree_NOM");
  dataproc5.GetProc("Multijet Fill").AddIVar("l1Pt","tree://Ntuples/Multijet_All_muon_v23.5.root:CollectionTree_NOM");
  dataproc5.GetProc("Multijet Fill").AddIVar("Mjj","tree://Ntuples/Multijet_All_muon_v23.5.root:CollectionTree_NOM");
  dataproc5.GetProc("Multijet Fill").AddIVar("Ptjj","tree://Ntuples/Multijet_All_muon_v23.5.root:CollectionTree_NOM");
  dataproc5.GetProc("Multijet Fill").AddIVar("l1Cent","tree://Ntuples/Multijet_All_muon_v23.5.root:CollectionTree_NOM");
  dataproc5.GetProc("Multijet Fill").AddIVar("Lumi","tree://Ntuples/Multijet_All_muon_v23.5.root:CollectionTree_NOM");
  dataproc5.GetProc("Multijet Fill").AddIVar("prw","tree://Ntuples/Multijet_All_muon_v23.5.root:CollectionTree_NOM");
  dataproc5.GetProc("Multijet Fill").AddIVar("mc_nFactor","tree://Ntuples/Multijet_All_muon_v23.5.root:CollectionTree_NOM");
  dataproc5.GetProc("Multijet Fill").AddIVar("recoWeight","tree://Ntuples/Multijet_All_muon_v23.5.root:CollectionTree_NOM");
  dataproc5.GetProc("Multijet Fill").AddIVar("SfsWeight","tree://Ntuples/Multijet_All_muon_v23.5.root:CollectionTree_NOM");
  dataproc5.GetProc("Multijet Fill").AddIVar("mc_w_init","tree://Ntuples/Multijet_All_muon_v23.5.root:CollectionTree_NOM");
 // dataproc5.GetProc("Multijet Fill").AddIVar("passSR","tree://Ntuples/Multijet_All_muon_v23.5.root:CollectionTree_NOM");



QHNF_D* sr_multijet6d = new QHNF_D("Multijet_7D", "Multijet_7D", 7);
  gDirectory->Add(sr_multijet6d);
  //Define axis characteristics 
 sr_multijet6d->SetAxis(0,dPhijj_nbins, dPhijj_bins);
  sr_multijet6d->SetAxis(1,dYjj_nbins,dYjj_bins);
  sr_multijet6d->SetAxis(2,j1Pt_nbins, j1Pt_bins);
  sr_multijet6d->SetAxis(3,l1Pt_nbins,l1Pt_bins);
  sr_multijet6d->SetAxis(4,Mjj_nbins, Mjj_bins);
  sr_multijet6d->SetAxis(5,Ptjj_nbins,Ptjj_bins);
  sr_multijet6d->SetAxis(6,l1Cent_nbins, l1Cent_bins);

  sr_multijet6d->SetNormFlags(QDis::kNoNorm);
  dataproc5.GetProc("Multijet Fill").AddOObj(sr_multijet6d);
  
  //Run the l_arrayproc list containing all QArrayProcessors
  l_arrayproc.Analyze();
  l_arrayproc.InitProcess();
  l_arrayproc.Exec();
  //Terminating the process will remove all information of the selection, however,
  //everything we need is already in the 7D histograms
  l_arrayproc.TerminateProcess();



  QProcList l_proc("Processor List","Processor List");
  //these processors are good at handling objects like histograms
  QProcObjProcessor ew_pdf("EW_1D", "EW_1D");
  l_proc.AddQProc(&ew_pdf);
  ew_pdf.AddProc("1D PDF","1D PDF", Proj);
  ew_pdf.GetProc("1D PDF").AddIObj(sr_ew6d);

  //Load a 1D histogram
  QHN_D* ew_1d_dPhijj = new QHN_D("EW_1D_dPhijj", "EW_1D_dPhijj",1); 
  //These histograms can be loaded this way because the QArrayProcessors are excecuted already meaning that the 7D histograms exist
  //sr_ew6d->GetAxis(0), copies the axis of the sr_ew6d graph to this 1D pdf
  ew_1d_dPhijj->SetAxis(0,sr_ew6d->GetAxis(0));
  QHN_D* ew_1d_dYjj = new QHN_D("EW_1D_dYjj", "EW_1D_dYjj",1); 
  ew_1d_dYjj->SetAxis(0,sr_ew6d->GetAxis(1));
  QHN_D* ew_1d_j1Pt = new QHN_D("EW_1D_j1Pt", "EW_1D_j1Pt",1);
  ew_1d_j1Pt->SetAxis(0,sr_ew6d->GetAxis(2));
  QHN_D* ew_1d_l1Pt = new QHN_D("EW_1D_l1Pt", "EW_1D_l1Pt",1);
  ew_1d_l1Pt->SetAxis(0,sr_ew6d->GetAxis(3));
  QHN_D* ew_1d_Mjj = new QHN_D("EW_1D_Mjj", "EW_1D_Mjj",1);
  ew_1d_Mjj->SetAxis(0,sr_ew6d->GetAxis(4));
  QHN_D* ew_1d_Ptjj = new QHN_D("EW_1D_Ptjj", "EW_1D_Ptjj",1);
  ew_1d_Ptjj->SetAxis(0,sr_ew6d->GetAxis(5));
  QHN_D* ew_1d_l1Cent = new QHN_D("EW_1D_l1Cent", "EW_1D_l1Cent",1);
  ew_1d_l1Cent->SetAxis(0,sr_ew6d->GetAxis(6));

  //Do not take binwidth into consideration for normalization
  ew_1d_dPhijj->SetNormFlags(QDis::kNoBinWidthNorm);
  ew_1d_dYjj->SetNormFlags(QDis::kNoBinWidthNorm);
  ew_1d_j1Pt->SetNormFlags(QDis::kNoBinWidthNorm);
  ew_1d_l1Pt->SetNormFlags(QDis::kNoBinWidthNorm);
  ew_1d_Mjj->SetNormFlags(QDis::kNoBinWidthNorm);
  ew_1d_Ptjj->SetNormFlags(QDis::kNoBinWidthNorm);
  ew_1d_l1Cent->SetNormFlags(QDis::kNoBinWidthNorm);

  gDirectory->Add(ew_1d_dPhijj);
  gDirectory->Add(ew_1d_dYjj);
  gDirectory->Add(ew_1d_j1Pt);
  gDirectory->Add(ew_1d_l1Pt);
  gDirectory->Add(ew_1d_Mjj);
  gDirectory->Add(ew_1d_Ptjj);
  gDirectory->Add(ew_1d_l1Cent);

  ew_pdf.GetProc("1D PDF").AddOObj(ew_1d_dPhijj);
  ew_pdf.GetProc("1D PDF").AddOObj(ew_1d_dYjj);
  ew_pdf.GetProc("1D PDF").AddOObj(ew_1d_j1Pt);
  ew_pdf.GetProc("1D PDF").AddOObj(ew_1d_l1Pt);
  ew_pdf.GetProc("1D PDF").AddOObj(ew_1d_Mjj);
  ew_pdf.GetProc("1D PDF").AddOObj(ew_1d_Ptjj);
  ew_pdf.GetProc("1D PDF").AddOObj(ew_1d_l1Cent);

  QProcObjProcessor qcd_pdf("QCD_1D", "QCD_1D");
  l_proc.AddQProc(&qcd_pdf);
  qcd_pdf.AddProc("1D PDF","1D PDF", Proj);
  qcd_pdf.GetProc("1D PDF").AddIObj(sr_qcd6d);
  
  QHN_D* qcd_1d_dPhijj = new QHN_D("QCD_1D_dPhijj", "QCD_1D_dPhijj",1); 
  qcd_1d_dPhijj->SetAxis(0,sr_qcd6d->GetAxis(0));
  QHN_D* qcd_1d_dYjj = new QHN_D("QCD_1D_dYjj", "QCD_1D_dYjj",1); 
  qcd_1d_dYjj->SetAxis(0,sr_qcd6d->GetAxis(1));
  QHN_D* qcd_1d_j1Pt = new QHN_D("QCD_1D_j1Pt", "QCD_1D_j1Pt",1);
  qcd_1d_j1Pt->SetAxis(0,sr_qcd6d->GetAxis(2));
  QHN_D* qcd_1d_l1Pt = new QHN_D("QCD_1D_l1Pt", "QCD_1D_l1Pt",1);
  qcd_1d_l1Pt->SetAxis(0,sr_qcd6d->GetAxis(3));
  QHN_D* qcd_1d_Mjj = new QHN_D("QCD_1D_Mjj", "QCD_1D_Mjj",1);
  qcd_1d_Mjj->SetAxis(0,sr_qcd6d->GetAxis(4));
  QHN_D* qcd_1d_Ptjj = new QHN_D("QCD_1D_Ptjj", "QCD_1D_Ptjj",1);
  qcd_1d_Ptjj->SetAxis(0,sr_qcd6d->GetAxis(5));
  QHN_D* qcd_1d_l1Cent = new QHN_D("QCD_1D_l1Cent", "QCD_1D_l1Cent",1);
  qcd_1d_l1Cent->SetAxis(0,sr_qcd6d->GetAxis(6));

  qcd_1d_dPhijj->SetNormFlags(QDis::kNoBinWidthNorm);
  qcd_1d_dYjj->SetNormFlags(QDis::kNoBinWidthNorm);
  qcd_1d_j1Pt->SetNormFlags(QDis::kNoBinWidthNorm);
  qcd_1d_l1Pt->SetNormFlags(QDis::kNoBinWidthNorm);
  qcd_1d_Mjj->SetNormFlags(QDis::kNoBinWidthNorm);
  qcd_1d_Ptjj->SetNormFlags(QDis::kNoBinWidthNorm);
  qcd_1d_l1Cent->SetNormFlags(QDis::kNoBinWidthNorm);

  gDirectory->Add(qcd_1d_dPhijj);
  gDirectory->Add(qcd_1d_dYjj);
  gDirectory->Add(qcd_1d_j1Pt);
  gDirectory->Add(qcd_1d_l1Pt);
  gDirectory->Add(qcd_1d_Mjj);
  gDirectory->Add(qcd_1d_Ptjj);
  gDirectory->Add(qcd_1d_l1Cent);

  qcd_pdf.GetProc("1D PDF").AddOObj(qcd_1d_dPhijj);
  qcd_pdf.GetProc("1D PDF").AddOObj(qcd_1d_dYjj);
  qcd_pdf.GetProc("1D PDF").AddOObj(qcd_1d_j1Pt);
  qcd_pdf.GetProc("1D PDF").AddOObj(qcd_1d_l1Pt);
  qcd_pdf.GetProc("1D PDF").AddOObj(qcd_1d_Mjj);
  qcd_pdf.GetProc("1D PDF").AddOObj(qcd_1d_Ptjj);
  qcd_pdf.GetProc("1D PDF").AddOObj(qcd_1d_l1Cent);

  QProcObjProcessor nonw_pdf("NonW_1D", "NonW_1D");
  l_proc.AddQProc(&nonw_pdf);
  nonw_pdf.AddProc("1D PDF","1D PDF", Proj);
  nonw_pdf.GetProc("1D PDF").AddIObj(sr_nonw6d);

  
  QHN_D* nonw_1d_dPhijj = new QHN_D("NonW_1D_dPhijj", "NonW_1D_dPhijj",1); 
  nonw_1d_dPhijj->SetAxis(0,sr_nonw6d->GetAxis(0));
  QHN_D* nonw_1d_dYjj = new QHN_D("NonW_1D_dYjj", "NonW_1D_dYjj",1); 
  nonw_1d_dYjj->SetAxis(0,sr_nonw6d->GetAxis(1));
  QHN_D* nonw_1d_j1Pt = new QHN_D("NonW_1D_j1Pt", "NonW_1D_j1Pt",1);
  nonw_1d_j1Pt->SetAxis(0,sr_nonw6d->GetAxis(2));
  QHN_D* nonw_1d_l1Pt = new QHN_D("NonW_1D_l1Pt", "NonW_1D_l1Pt",1);
  nonw_1d_l1Pt->SetAxis(0,sr_nonw6d->GetAxis(3));
  QHN_D* nonw_1d_Mjj = new QHN_D("NonW_1D_Mjj", "NonW_1D_Mjj",1);
  nonw_1d_Mjj->SetAxis(0,sr_nonw6d->GetAxis(4));
  QHN_D* nonw_1d_Ptjj = new QHN_D("NonW_1D_Ptjj", "NonW_1D_Ptjj",1);
  nonw_1d_Ptjj->SetAxis(0,sr_nonw6d->GetAxis(5));
  QHN_D* nonw_1d_l1Cent = new QHN_D("NonW_1D_l1Cent", "NonW_1D_l1Cent",1);
  nonw_1d_l1Cent->SetAxis(0,sr_nonw6d->GetAxis(6));

  nonw_1d_dPhijj->SetNormFlags(QDis::kNoBinWidthNorm);
  nonw_1d_dYjj->SetNormFlags(QDis::kNoBinWidthNorm);
  nonw_1d_j1Pt->SetNormFlags(QDis::kNoBinWidthNorm);
  nonw_1d_l1Pt->SetNormFlags(QDis::kNoBinWidthNorm);
  nonw_1d_Mjj->SetNormFlags(QDis::kNoBinWidthNorm);
  nonw_1d_Ptjj->SetNormFlags(QDis::kNoBinWidthNorm);
  nonw_1d_l1Cent->SetNormFlags(QDis::kNoBinWidthNorm);

  gDirectory->Add(nonw_1d_dPhijj);
  gDirectory->Add(nonw_1d_dYjj);
  gDirectory->Add(nonw_1d_j1Pt);
  gDirectory->Add(nonw_1d_l1Pt);
  gDirectory->Add(nonw_1d_Mjj);
  gDirectory->Add(nonw_1d_Ptjj);
  gDirectory->Add(nonw_1d_l1Cent);
  
  nonw_pdf.GetProc("1D PDF").AddOObj(nonw_1d_dPhijj);
  nonw_pdf.GetProc("1D PDF").AddOObj(nonw_1d_dYjj);
  nonw_pdf.GetProc("1D PDF").AddOObj(nonw_1d_j1Pt);
  nonw_pdf.GetProc("1D PDF").AddOObj(nonw_1d_l1Pt);
  nonw_pdf.GetProc("1D PDF").AddOObj(nonw_1d_Mjj);
  nonw_pdf.GetProc("1D PDF").AddOObj(nonw_1d_Ptjj); 
  nonw_pdf.GetProc("1D PDF").AddOObj(nonw_1d_l1Cent);


//Multijet
 QProcObjProcessor multijet_pdf("Multijet_1D", "Multijet_1D");
  l_proc.AddQProc(&multijet_pdf);
  multijet_pdf.AddProc("1D PDF","1D PDF", Proj);
  multijet_pdf.GetProc("1D PDF").AddIObj(sr_multijet6d);

  
  QHN_D* multijet_1d_dPhijj = new QHN_D("Multijet_1D_dPhijj", "Multijet_1D_dPhijj",1); 
  multijet_1d_dPhijj->SetAxis(0,sr_multijet6d->GetAxis(0));
  QHN_D* multijet_1d_dYjj = new QHN_D("Multijet_1D_dYjj", "Multijet_1D_dYjj",1); 
  multijet_1d_dYjj->SetAxis(0,sr_multijet6d->GetAxis(1));
  QHN_D* multijet_1d_j1Pt = new QHN_D("Multijet_1D_j1Pt", "Multijet_1D_j1Pt",1);
  multijet_1d_j1Pt->SetAxis(0,sr_multijet6d->GetAxis(2));
  QHN_D* multijet_1d_l1Pt = new QHN_D("Multijet_1D_l1Pt", "Multijet_1D_l1Pt",1);
  multijet_1d_l1Pt->SetAxis(0,sr_multijet6d->GetAxis(3));
  QHN_D* multijet_1d_Mjj = new QHN_D("Multijet_1D_Mjj", "Multijet_1D_Mjj",1);
  multijet_1d_Mjj->SetAxis(0,sr_multijet6d->GetAxis(4));
  QHN_D* multijet_1d_Ptjj = new QHN_D("Multijet_1D_Ptjj", "Multijet_1D_Ptjj",1);
  multijet_1d_Ptjj->SetAxis(0,sr_multijet6d->GetAxis(5));
  QHN_D* multijet_1d_l1Cent = new QHN_D("Multijet_1D_l1Cent", "Multijet_1D_l1Cent",1);
  multijet_1d_l1Cent->SetAxis(0,sr_multijet6d->GetAxis(6));

  multijet_1d_dPhijj->SetNormFlags(QDis::kNoBinWidthNorm);
  multijet_1d_dYjj->SetNormFlags(QDis::kNoBinWidthNorm);
  multijet_1d_j1Pt->SetNormFlags(QDis::kNoBinWidthNorm);
  multijet_1d_l1Pt->SetNormFlags(QDis::kNoBinWidthNorm);
  multijet_1d_Mjj->SetNormFlags(QDis::kNoBinWidthNorm);
  multijet_1d_Ptjj->SetNormFlags(QDis::kNoBinWidthNorm);
  multijet_1d_l1Cent->SetNormFlags(QDis::kNoBinWidthNorm);

  gDirectory->Add(multijet_1d_dPhijj);
  gDirectory->Add(multijet_1d_dYjj);
  gDirectory->Add(multijet_1d_j1Pt);
  gDirectory->Add(multijet_1d_l1Pt);
  gDirectory->Add(multijet_1d_Mjj);
  gDirectory->Add(multijet_1d_Ptjj);
  gDirectory->Add(multijet_1d_l1Cent);
  
  multijet_pdf.GetProc("1D PDF").AddOObj(multijet_1d_dPhijj);
  multijet_pdf.GetProc("1D PDF").AddOObj(multijet_1d_dYjj);
  multijet_pdf.GetProc("1D PDF").AddOObj(multijet_1d_j1Pt);
  multijet_pdf.GetProc("1D PDF").AddOObj(multijet_1d_l1Pt);
  multijet_pdf.GetProc("1D PDF").AddOObj(multijet_1d_Mjj);
  multijet_pdf.GetProc("1D PDF").AddOObj(multijet_1d_Ptjj); 
  multijet_pdf.GetProc("1D PDF").AddOObj(multijet_1d_l1Cent);



    //Creating Joint PDFS
  QProcObjProcessor ew_joining("EW_Joint", "EW_Joint");
    l_proc.AddQProc(&ew_joining);
    ew_joining.AddProc("Joint", "Joint", Join);
    ew_joining.GetProc("Joint").AddIObj(ew_1d_dPhijj);
    ew_joining.GetProc("Joint").AddIObj(ew_1d_dYjj);
    ew_joining.GetProc("Joint").AddIObj(ew_1d_j1Pt);
    ew_joining.GetProc("Joint").AddIObj(ew_1d_l1Pt);
    ew_joining.GetProc("Joint").AddIObj(ew_1d_Mjj);
    ew_joining.GetProc("Joint").AddIObj(ew_1d_Ptjj);
    ew_joining.GetProc("Joint").AddIObj(ew_1d_l1Cent);
    ew_joining.GetProc("Joint").AddIObj(data6d);

  QHN_D* ew_joint = new QHN_D("EW_jointProb", "EW_jointProb", data6d->GetNFbins(),0.,1.); 
   ew_joint->SetNormFlags(QDis::kNoNorm);

   ew_joining.GetProc("Joint").AddOObj(ew_joint);
   gDirectory->Add(ew_joint);


  QProcObjProcessor qcd_joining("QCD_Joint", "QCD_Joint");
    l_proc.AddQProc(&qcd_joining);
    qcd_joining.AddProc("Joint", "Joint", Join);
    qcd_joining.GetProc("Joint").AddIObj(qcd_1d_dPhijj);
    qcd_joining.GetProc("Joint").AddIObj(qcd_1d_dYjj);
    qcd_joining.GetProc("Joint").AddIObj(qcd_1d_j1Pt);
    qcd_joining.GetProc("Joint").AddIObj(qcd_1d_l1Pt);
    qcd_joining.GetProc("Joint").AddIObj(qcd_1d_Mjj);
    qcd_joining.GetProc("Joint").AddIObj(qcd_1d_Ptjj);
    qcd_joining.GetProc("Joint").AddIObj(qcd_1d_l1Cent);
    qcd_joining.GetProc("Joint").AddIObj(data6d);

  QHN_D* qcd_joint = new QHN_D("QCD_jointProb", "QCD_jointProb", data6d->GetNFbins(),0.,1.); 
   qcd_joint->SetNormFlags(QDis::kNoNorm);

   qcd_joining.GetProc("Joint").AddOObj(qcd_joint);
   gDirectory->Add(qcd_joint);


  QProcObjProcessor nonw_joining("NonW_Joint", "NonW_Joint");
    l_proc.AddQProc(&nonw_joining);
    nonw_joining.AddProc("Joint", "Joint", Join);
    nonw_joining.GetProc("Joint").AddIObj(nonw_1d_dPhijj);
    nonw_joining.GetProc("Joint").AddIObj(nonw_1d_dYjj);
    nonw_joining.GetProc("Joint").AddIObj(nonw_1d_j1Pt);
    nonw_joining.GetProc("Joint").AddIObj(nonw_1d_l1Pt);
    nonw_joining.GetProc("Joint").AddIObj(nonw_1d_Mjj);
    nonw_joining.GetProc("Joint").AddIObj(nonw_1d_Ptjj);
    nonw_joining.GetProc("Joint").AddIObj(nonw_1d_l1Cent);
    nonw_joining.GetProc("Joint").AddIObj(data6d);

  QHN_D* nonw_joint = new QHN_D("NonW_jointProb", "NonW_jointProb", data6d->GetNFbins(),0.,1.); 
   nonw_joint->SetNormFlags(QDis::kNoNorm);

   nonw_joining.GetProc("Joint").AddOObj(nonw_joint);
   gDirectory->Add(nonw_joint);

//Multijet

 QProcObjProcessor multijet_joining("Multijet_Joint", "Multijet_Joint");
    l_proc.AddQProc(&multijet_joining);
    multijet_joining.AddProc("Joint", "Joint", Join);
    multijet_joining.GetProc("Joint").AddIObj(multijet_1d_dPhijj);
    multijet_joining.GetProc("Joint").AddIObj(multijet_1d_dYjj);
    multijet_joining.GetProc("Joint").AddIObj(multijet_1d_j1Pt);
    multijet_joining.GetProc("Joint").AddIObj(multijet_1d_l1Pt);
    multijet_joining.GetProc("Joint").AddIObj(multijet_1d_Mjj);
    multijet_joining.GetProc("Joint").AddIObj(multijet_1d_Ptjj);
    multijet_joining.GetProc("Joint").AddIObj(multijet_1d_l1Cent);
    multijet_joining.GetProc("Joint").AddIObj(data6d);

  QHN_D* multijet_joint = new QHN_D("Multijet_jointProb", "Multijet_jointProb", data6d->GetNFbins(),0.,1.); 
   multijet_joint->SetNormFlags(QDis::kNoNorm);

   multijet_joining.GetProc("Joint").AddOObj(multijet_joint);
   gDirectory->Add(multijet_joint);




  //Process for LL
  QProcDouble llsum;

  QProcObjProcessor LLproc("LLproc", "LLproc");
  l_proc.AddQProc(&LLproc);
  //Add a Post Selection process to compute the likelihood sum over the classes for the current event. The process will use the function LLSum
  LLproc.AddProc("LLSum","LLSum",LLSum);
  //Add the fit parameters to the process
  LLproc.GetProc("LLSum").AddParam("EW");
  LLproc.GetProc("LLSum").AddParam("QCD");
  LLproc.GetProc("LLSum").AddParam("NonW");
  LLproc.GetProc("LLSum").AddParam("Multijet"); 
  //Add the joint probability branches to the process
  LLproc.GetProc("LLSum").AddIObj(ew_joint);
  LLproc.GetProc("LLSum").AddIObj(qcd_joint);
  LLproc.GetProc("LLSum").AddIObj(nonw_joint);
  LLproc.GetProc("LLSum").AddIObj(multijet_joint); 
  LLproc.GetProc("LLSum").AddIObj(data6d);
  //Add llsum as the output of the function
  LLproc.GetProc("LLSum").AddOObj(&llsum);


  //Analyze the processes
  l_proc.Analyze();
  //Print some info about the structure
  l_proc.PrintProcesses(0,kTRUE);
  //dataproc.PrintAnalysisResults();
  //Initialize the processes
  l_proc.InitProcess();

  //Create a QSigExFitMinuit instance
  QSigExFitMinuit* fitter = new QSigExFitMinuit;
  //Attach the processor to the fitter
  fitter->SetProcessor(&l_proc);
  //Add llsum as an output to the minimizing function
  fitter->AddProcOutput(&llsum);

  //Set the fit parameters
  //.SetUp(initialvalue, stepsize,lowerbound,upperbound)
  fitter->Param("EW").Setup(sr_ew6d->GetEntries(),1,0,1000000);
  fitter->Param("QCD").Setup(sr_qcd6d->GetEntries(),1,0,1000000);
  fitter->Param("NonW").Setup(sr_nonw6d->GetEntries(), 0.0, sr_nonw6d->GetEntries(), sr_nonw6d->GetEntries(), kTRUE);
  fitter->Param("Multijet").Setup(sr_multijet6d->GetEntries(),0.00,sr_nonw6d->GetEntries(),sr_nonw6d->GetEntries(), kTRUE);

  //Set the minimizing function
  fitter->SetFCN(ELLFunction);

  //Set Minuit verbosity
  fitter->SetVerbose(0);
  //Initialize the fit
  fitter->InitFit();
  //fitter->PrintParams();
  //Perform the fit
  
  fitter->Fit();
 
  cout << fitter->EvalFCN() << endl;
  //Print the results
  fitter->PrintParams();
  //Print the covariance matrix
  fitter->GetCovMatrix().Print();
  //Print the correlation matrix
  fitter->GetCorMatrix().Print();
  //Terminate the processes

  l_proc.TerminateProcess();

  //Add the fitter to the output file
  f1.Add(fitter);

  f1.Write();
  f1.Close();

}
/***************************************************************************************************************
Make sure to include a constructor for all functions and included classes into the runEW.h file
***************************************************************************************************************/


//This is the general selector for the data, these cuts are applied to most of the Event classes, if any class needs a different cut a new selector
//must be made, look at QCD_Selector

//Comments are original selections that have been removed to match another fit
Bool_t Selector(QProcArgs &args){
 //Data Conditions
 //if (args.IVarF(0)<-M_PI  || args.IVarF(0)>=M_PI) return kFALSE;
 //if (args.IVarF(1)<dYjj_bins[0] || args.IVarF(1)>=dYjj_bins[dYjj_nbins]) return kFALSE;
 //if (args.IVarF(2)<j1Pt_bins[0]  || args.IVarF(2)>=j1Pt_bins[j1Pt_nbins]) return kFALSE;
 //if (args.IVarF(3)<l1Pt_bins[0]  || args.IVarF(3)>=l1Pt_bins[l1Pt_nbins]) return kFALSE;
 if (args.IVarF(4)<=Mjj_bins[1] /* || args.IVarF(4)>=Mjj_bins[Mjj_nbins]*/) return kFALSE;
 //if (args.IVarF(5)<Ptjj_bins[0]  || args.IVarF(5)>=Ptjj_bins[Ptjj_nbins]) return kFALSE;

  //passReco Condition 
 if (args.IVarI(6) != 1) return kFALSE;
   //cut
 if (args.IVarI(7) <16) return kFALSE;
 //SR condition (Probably make another function if you dont care about just one cntrol region)
 //if (args.IVarI(8) != 1) return kFALSE;
 // nGapJets Condition
 if (args.IVarI(8) != 0) return kFALSE;

return kTRUE;
}


//Selector for QCD because needs special cuts to finalWeight
Bool_t QCD_Selector(QProcArgs &args){
  //Data Conditions
 //if (args.IVarF(0)<-M_PI  || args.IVarF(0)>=M_PI) return kFALSE;
 //if (args.IVarF(1)<dYjj_bins[0] || args.IVarF(1)>=dYjj_bins[dYjj_nbins]) return kFALSE;
 //if (args.IVarF(2)<j1Pt_bins[0]  || args.IVarF(2)>=j1Pt_bins[j1Pt_nbins]) return kFALSE;
 //if (args.IVarF(3)<l1Pt_bins[0]  || args.IVarF(3)>=l1Pt_bins[l1Pt_nbins]) return kFALSE;
 if (args.IVarF(4)<Mjj_bins[1] /* || args.IVarF(4)>=Mjj_bins[Mjj_nbins]*/) return kFALSE;
 //if (args.IVarF(5)<Ptjj_bins[0]  || args.IVarF(5)>=Ptjj_bins[Ptjj_nbins]) return kFALSE;

  //passReco Condition 
 if (args.IVarI(6) != 1) return kFALSE;
   //cut
 if (args.IVarI(7) <=16) return kFALSE;
 //SR condition (Probably make another function if you dont care about just one cntrol region)
 //if (args.IVarI(8) != 1) return kFALSE;
 // nGapJets Condition
 if (args.IVarI(8) != 0) return kFALSE;

 //finalWeight cuts
 if (args.IVarF(9) > 0.02) return kFALSE;

return kTRUE;
}


//This is specifically for filling data
Bool_t data_fill(QProcArgs &args){
  //The data 3D Histogram is filled with the branches of the TTree 
  QHNF_D* data = ((QHNF_D*)args.OObj(0));
  //Fill fills with weight 1
  data->Fill((Float_t)(args.IVarF(0)/M_PI), args.IVarF(1),args.IVarF(2), args.IVarF(3), args.IVarF(4),args.IVarF(5),fabs(args.IVarF(6)));
 
  return kTRUE;
}

Bool_t MC_fill(QProcArgs &args){
  QHNF_D* sr = ((QHNF_D*)args.OObj(0));
  //Add the weigted amount to all of the bins in the first argument
  //Findbin provides the 7D coordinates, second argument provides the weight
  sr->AddBinContent((sr->FindBin((Float_t)(args.IVarF(0)/M_PI),args.IVarF(1),args.IVarF(2),args.IVarF(3),args.IVarF(4),args.IVarF(5),fabs(args.IVarF(6)))),
  (Double_t)(args.IVarF(7)*args.IVarF(8)));

return kTRUE;
}

//Like MC fill, finalWeight is calculated from scratch because of issues with the original values assigned 
Bool_t Multijet_fill(QProcArgs &args){

QHNF_D* sr = ((QHNF_D*)args.OObj(0));

  sr->AddBinContent((sr->FindBin((Float_t)(args.IVarF(0)/M_PI),args.IVarF(1),args.IVarF(2),args.IVarF(3),args.IVarF(4),args.IVarF(5),fabs(args.IVarF(6)))),
  args.IVarF(7)*args.IVarF(8)*args.IVarF(9)*args.IVarF(10)*args.IVarF(11)*args.IVarF(12));

return kTRUE;
}


Bool_t Proj(QProcArgs &args){
//create variable so that the coding is simpler
const QHNF_D& class6d = *((QHNF_D*)args.IObj(0));
QHN_D& pdf1 = *((QHN_D*)args.OObj(0));
QHN_D& pdf2 = *((QHN_D*)args.OObj(1));
QHN_D& pdf3 = *((QHN_D*)args.OObj(2));
QHN_D& pdf4 = *((QHN_D*)args.OObj(3));
QHN_D& pdf5 = *((QHN_D*)args.OObj(4));
QHN_D& pdf6 = *((QHN_D*)args.OObj(5));
QHN_D& pdf7 = *((QHN_D*)args.OObj(6));

//must be 7, because 7D
Int_t coords[7];

//for all filled bins
for(int i=0; i<class6d.GetNFbins();i++){
//Get coords and content of the ith filled bin
class6d.GetFBinCoords(i, coords);
Double_t content= class6d.GetFBinContent(i);
//the content can't be negative but could be because of how the Multijet MC was created
if(content < 0.0){
  content =0.0;
}
//Fill the values to 1D PMF
pdf1.AddBinContent(coords[0], content);
pdf2.AddBinContent(coords[1], content);
pdf3.AddBinContent(coords[2], content);
pdf4.AddBinContent(coords[3], content);
pdf5.AddBinContent(coords[4], content);
pdf6.AddBinContent(coords[5], content);
pdf7.AddBinContent(coords[6], content);
}

return kTRUE;
}



Bool_t Join(QProcArgs &args){
//create variable so that the coding is simpler
const QHNF_I& data = *((QHNF_I*)args.IObj(7));
const QHN_D& dPhijj = *((QHN_D*)args.IObj(0));
const QHN_D& dYjj = *((QHN_D*)args.IObj(1));
const QHN_D& j1Pt = *((QHN_D*)args.IObj(2));
const QHN_D& l1Pt = *((QHN_D*)args.IObj(3));
const QHN_D& Mjj = *((QHN_D*)args.IObj(4));
const QHN_D& Ptjj = *((QHN_D*)args.IObj(5));
const QHN_D& l1Cent = *((QHN_D*)args.IObj(6));

QHN_D& joint = *((QHN_D*)args.OObj(0));

//There are 7 axes so an array with 7 entries
Int_t coords[7];
Double_t cur;

//GetNFbins goes over all filld bins
for(int i=0; i<data.GetNFbins();i++){
  //Gets coordinates from filled binned x=coords[0], y=coords[1], z=coords[2]
  // remember in this scenario x=energy, y=radius, z=cthsun
  data.GetFBinCoords(i, coords);

  //Use these coords on the PDFs of the observables then assume indepence to get the joint PDFs
 cur = dPhijj.GetBinContent(coords[0]) *dYjj.GetBinContent(coords[1])*j1Pt.GetBinContent(coords[2])
 *l1Pt.GetBinContent(coords[3])*Mjj.GetBinContent(coords[4])*Ptjj.GetBinContent(coords[5])*l1Cent.GetBinContent(coords[6]);
 //set the bin value of the joint pdf
 joint.SetBinContent(i,cur);
}
return kTRUE;
}



//Calculates likelihood sum
Bool_t LLSum(QProcArgs &args)
{
  static Double_t P;
  //this total acts as a referencet o llsum, so anything done to it will be assigned back to llsum
  Double_t& total=(Double_t&) (*(QProcDouble*)args.OObj(0));
  //Loading the data histogram
  const QHNF_I& data = *((QHNF_I*)args.IObj(4));
  //Compute the likelihood sum for the current event

  for(int j=0; j<data.GetNFbins(); j++) {
    P=0;

    for(int i=0;i<args.GetNParams();i++){
      //can do this because there should be the same number of Paramameters as there are jointPDFs
      //This assumes that the joint PDFs are defined first, if data is defined before this will not work(define data as the last IObj)
      const QHN_D& joint = *((QHN_D*)args.IObj(i)); 
      P+=args.Param(i)*joint.GetBinContent(j);

    }
    if(P>0){
      total += data.GetFBinContent(j)*log(P);
    }
  }
  return kTRUE;
}


//Final Step of the LL
void ELLFunction(Int_t&, Double_t*, Double_t &f, Double_t *, Int_t)
{
  static Int_t i;
  static Double_t const* const* pars;
  //Get a pointer to the array of parameters from the current processor
  pars=QSigExFit::GetCurInstance().GetProcessor()->GetParams();
  //Update the processor output depending on the updated inputs
  QSigExFit::GetCurInstance().ExecProc();
  //Compute the total number of events
  f=0;
  for(i=0; i<QSigExFit::GetCurInstance().GetNParams(); i++) f+=*(pars[i]);
  //Finish to compute the extended log-likelihood
  f=2*(f-(QProcDouble&)QSigExFit::GetCurInstance().GetProcOutput(0));
}
