#include "Mjj_muonpostfit.cpp"
#include "Mjj_muonprefit.cpp"
#include "Mjj_elepostfit.cpp"
#include "Mjj_eleprefit.cpp"
#include "dYjj_muonprefit.cpp"
#include "dYjj_muonpostfit.cpp"

void maker(){
Mjj_muonprefit();
Mjj_muonpostfit();
Mjj_eleprefit();
Mjj_elepostfit();
dYjj_muonprefit();
dYjj_muonpostfit();
}