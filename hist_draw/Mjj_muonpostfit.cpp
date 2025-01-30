#include "TH1.h"
#include "TTree.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TFile.h"

void Mjj_muonpostfit(){
 TFile* dataf = new TFile("../Ntuples/Data_All_Years_muon_v23.5.root", "read");
 TTree* datatree = (TTree*) dataf->Get("CollectionTree_NOM");

 TFile* ewf = new TFile("../Ntuples/EW_Pow_All_Years_muon_v23.5.root", "read");
 TTree* ewtree = (TTree*) ewf->Get("CollectionTree_NOM");

 TFile* qcdf = new TFile("../Ntuples/QCD_Wjets_Powheg_All_Years_muon_v23.5.root", "read");
 TTree* qcdtree = (TTree*) qcdf->Get("CollectionTree_NOM");

 TFile* nonwf = new TFile("../Ntuples/NonW_All_Years_muon_v23.5.root", "read");
 TTree* nonwtree = (TTree*) nonwf->Get("CollectionTree_NOM");

 TFile* multif = new TFile("../Ntuples/Multijet_All_muon_v23.5.root", "read");
 TTree* multitree = (TTree*) multif->Get("CollectionTree_NOM");

 TCanvas *cs;// initialize pdf file
 cs = new TCanvas("cs_total","cs_total", 400,20,1200,800);
 cs -> Print("Mjj_muonpostfit.pdf["); // Make blank page in pdf file

 auto hs = new THStack("hs","Mjj_postfit_Muon"); // Object used to plot histograms stacked on one another

  Double_t edges[6] = {1000,1500, 2250, 3000, 4000, 6000};
  TH1D* h_Data  = new TH1D("h_Data" ,"h_Data", 5, edges);
   h_Data->SetMarkerStyle(8);

  TH1D* h_EW_Wjj = new TH1D("h_EW_Wjj" ,"h_EW_Wjj", 5,edges);
    h_EW_Wjj->SetFillColor(kBlue);
    h_EW_Wjj->SetLineColor(kBlue);

    
  TH1D* h_QCDWjj = new TH1D("h_QCDWjj" ,"h_QCDWjj", 5, edges);
    h_QCDWjj->SetFillColor(kRed+1);
    h_QCDWjj->SetLineColor(kRed+1);

  TH1D* h_NonWjj    = new TH1D("h_NonWjj" ,"h_NonWjj", 5, edges);
    h_NonWjj->SetFillColor(kGreen+1); 
    h_NonWjj->SetLineColor(kGreen+1); 

  TH1D* h_multijj    = new TH1D("h_Multijet" ,"h_Multijet", 5, edges);
    h_multijj -> SetFillColor(kViolet+1); 
    h_multijj -> SetLineColor(kViolet+1); 

  datatree->Draw("Mjj>>h_Data", "(nGapJets == 0)*(cut>=16)*(Mjj>1000)*(passReco==1)", "goff");
  ewtree->Draw("Mjj>>h_EW_Wjj", "(nGapJets == 0)*(cut>=16)*(Mjj>1000)*(passReco==1)*(finalWeight)*(Lumi)*(21824.098/21880.853)", "goff");
  qcdtree->Draw("Mjj>>h_QCDWjj", "(nGapJets == 0)*(cut>=16)*(Mjj>1000)*(passReco==1)*(finalWeight)*(Lumi)*(47020.670/51127.686)", "goff");
  nonwtree->Draw("Mjj>>h_NonWjj", "(nGapJets == 0)*(cut>=16)*(Mjj>1000)*(passReco==1)*(finalWeight)*(Lumi)", "goff");
  multitree->Draw("Mjj>>h_Multijet", "(nGapJets == 0)*(cut>=16)*(Mjj>1000)*(passReco==1)*(prw)*(mc_nFactor)*(recoWeight)*(SfsWeight)*(mc_w_init)*(Lumi)", "goff");

    hs -> Add(h_EW_Wjj);
    hs -> Add(h_QCDWjj);
    hs -> Add(h_NonWjj); 
    hs -> Add(h_multijj);

  // Draw stacked histogram in the pdf file
  hs -> Draw("hist");
  // Draw sdata histogram in the pdf file, but not in stavck, just superemposed on canvas
  h_Data->Draw("Same E1");
  h_Data->Draw("Same P");

  //Axis Titles for Stack
  hs -> GetYaxis() -> SetTitle("N Events");
  hs -> GetXaxis() -> SetTitle("Mjj");

  cs -> Update();
  cs -> Print("Mjj_muonpostfit.pdf");
  cs -> Print("Mjj_muonpostfit.pdf]"); // Need to call this agani to tell the PDF that this was the last page ( thats the "]" )
  cs -> Clear();

  cs -> Close();

}