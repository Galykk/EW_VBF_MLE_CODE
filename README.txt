
Qsigex must be installed
--------------------------------------------------
**The two codes should be almost identical**
- open _Index.html in a browser for Qsigex Documentation

//////////////////////////////////////////////////

> make
#for muon fit
> muonfit muonfit_results.root
#for electron fit
> elefit elefit_results.root

//////////////////////////////////////////////////

If the code doesn't run, make sure the runEW.h file is properly 
created with all functions constructor and include statements

- Ntuples directory contains event level data which is used in the fit
- hist_draw directory contains a few event reconstruction
- root_data contains original histograms provided by Dylan Pizzi which are not used in the fit