#include "TH1.h"
#include "TTree.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TFile.h"

void dYjj_muonprefit(){
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
 cs -> Print("dYjj_muonprefit.pdf["); // Make blank page in pdf file

 auto hs = new THStack("hs","dYjj_prefit_Muon"); // Object used to plot histograms stacked on one another

  Double_t edges[10] = {2.0, 2.6, 3.1, 3.6, 3.9, 4.2, 4.6, 5.0, 6.0, 8.0};
  TH1D* h_Data  = new TH1D("h_Data" ,"h_Data", 9, edges);
   h_Data->SetMarkerStyle(8);

  TH1D* h_EW_Wjj = new TH1D("h_EW_Wjj" ,"h_EW_Wjj", 9,edges);
    h_EW_Wjj->SetFillColor(kBlue);
    h_EW_Wjj->SetLineColor(kBlue);

    
  TH1D* h_QCDWjj = new TH1D("h_QCDWjj" ,"h_QCDWjj", 9, edges);
    h_QCDWjj->SetFillColor(kRed+1);
    h_QCDWjj->SetLineColor(kRed+1);

  TH1D* h_NonWjj    = new TH1D("h_NonWjj" ,"h_NonWjj", 9, edges);
    h_NonWjj->SetFillColor(kGreen+1); 
    h_NonWjj->SetLineColor(kGreen+1); 

  TH1D* h_multijj    = new TH1D("h_Multijet" ,"h_Multijet", 9, edges);
    h_multijj -> SetFillColor(kViolet+1); 
    h_multijj -> SetLineColor(kViolet+1); 

  datatree->Draw("dYjj>>h_Data", "(nGapJets == 0)*(cut>=16)*(Mjj>1000)*(passReco==1)", "goff");
  ewtree->Draw("dYjj>>h_EW_Wjj", "(nGapJets == 0)*(cut>=16)*(Mjj>1000)*(passReco==1)*(finalWeight)*(Lumi)", "goff");
  qcdtree->Draw("dYjj>>h_QCDWjj", "(nGapJets == 0)*(cut>=16)*(Mjj>1000)*(passReco==1)*(finalWeight)*(Lumi)", "goff");
  nonwtree->Draw("dYjj>>h_NonWjj", "(nGapJets == 0)*(cut>=16)*(Mjj>1000)*(passReco==1)*(finalWeight)*(Lumi)", "goff");
  multitree->Draw("dYjj>>h_Multijet", "(nGapJets == 0)*(cut>=16)*(Mjj>1000)*(passReco==1)*(prw)*(mc_nFactor)*(recoWeight)*(SfsWeight)*(mc_w_init)*(Lumi)", "goff");

    hs -> Add(h_EW_Wjj);
    hs -> Add(h_QCDWjj);
    hs -> Add(h_NonWjj); 
    hs -> Add(h_multijj);

  // Draw stacked histogram in the pdf file
  hs -> Draw("hist");
  // Draw sdata histogram in the pdf file, but not in stavck, just superemposed on canvas
  h_Data->Draw("Same");
  h_Data->Draw("Same P");
  
  
   
  //Axis Titles for Stack
  hs -> GetYaxis() -> SetTitle("N Events");
  hs -> GetXaxis() -> SetTitle("dYjj");

  cs -> Update();
  cs -> Print("dYjj_muonprefit.pdf");
  cs -> Print("dYjj_muonprefit.pdf]"); // Need to call this agani to tell the PDF that this was the last page ( thats the "]" )
  cs -> Clear();

  cs -> Close();

}