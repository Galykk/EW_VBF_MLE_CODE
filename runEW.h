#include <cstdio>
#include "Rtypes.h"
#include "TFile.h"
#include "TTree.h"
#include "QHN.h"
#include "QSigExFitMinuit.h"
#include "QArrayProcessor.h"
#include "QHNF.h"
#include "QProcList.h"
#include "QProcObjProcessor.h"
#include "TH1.h"
#include <iostream>



int main(int nargs, char* args[]);
Bool_t Selector(QProcArgs &args);
Bool_t QCD_Selector(QProcArgs &args);
Bool_t Proj(QProcArgs &args);
Bool_t Join(QProcArgs &args);
Bool_t data_fill(QProcArgs &args);
Bool_t MC_fill(QProcArgs &args);
Bool_t LLSum(QProcArgs &args);
Bool_t Multijet_fill(QProcArgs &args);


void ELLFunction(Int_t&, Double_t*, Double_t &f, Double_t *, Int_t);