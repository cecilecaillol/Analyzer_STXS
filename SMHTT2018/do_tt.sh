./Make.sh FinalSelection_tt.cc
./FinalSelection_tt.exe /data/ccaillol/smhtt2018_svfitted_23feb_svfit/DataA.root files_nominal_tt/DataA.root data_obs data_obs 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2018_svfitted_23feb_svfit/DataB.root files_nominal_tt/DataB.root data_obs data_obs 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2018_svfitted_23feb_svfit/DataC.root files_nominal_tt/DataC.root data_obs data_obs 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2018_svfitted_23feb_svfit/DataD.root files_nominal_tt/DataD.root data_obs data_obs 0
hadd -f files_nominal_tt/Data.root files_nominal_tt/DataA.root files_nominal_tt/DataB.root files_nominal_tt/DataC.root files_nominal_tt/DataD.root
#./FinalSelection_tt.exe /data/ccaillol/smhtt2018_svfitted_23feb_svfit/Embedded.root files_nominal_tt/Embedded.root embedded embedded 0
#./FinalSelection_tt.exe /data/ccaillol/smhtt2018_svfitted_23feb_svfit/DYall.root files_nominal_tt/DY.root DY DY 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2018_svfitted_23feb_svfit/DY.root files_nominal_tt/DYincl.root DY DY 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2018_svfitted_23feb_svfit/DY1.root files_nominal_tt/DY1.root DY DY 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2018_svfitted_23feb_svfit/DY2.root files_nominal_tt/DY2.root DY DY 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2018_svfitted_23feb_svfit/DY3.root files_nominal_tt/DY3.root DY DY 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2018_svfitted_23feb_svfit/DY4.root files_nominal_tt/DY4.root DY DY 0
hadd -f files_nominal_tt/DY.root files_nominal_tt/DYincl.root files_nominal_tt/DY1.root files_nominal_tt/DY2.root files_nominal_tt/DY3.root files_nominal_tt/DY4.root
./FinalSelection_tt.exe /data/ccaillol/smhtt2018_svfitted_23feb_svfit/DYlow.root files_nominal_tt/DYlow.root DYlow DYlow 0
##./FinalSelection_tt.exe /data/ccaillol/smhtt2018_svfitted_23feb_svfit/DY.root files_nominal_tt/DY.root DY DY 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2018_svfitted_23feb_svfit/Wall.root files_nominal_tt/W.root W W 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2018_svfitted_23feb_svfit/TTToHadronic.root files_nominal_tt/TTToHadronic.root TTToHadronic TT 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2018_svfitted_23feb_svfit/TTTo2L2Nu.root files_nominal_tt/TTTo2L2Nu.root TTTo2L2Nu TT 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2018_svfitted_23feb_svfit/TTToSemiLeptonic.root files_nominal_tt/TTToSemiLeptonic.root TTToSemiLeptonic TT 0
hadd -f files_nominal_tt/TT.root files_nominal_tt/TTToHadronic.root files_nominal_tt/TTTo2L2Nu.root files_nominal_tt/TTToSemiLeptonic.root
./FinalSelection_tt.exe /data/ccaillol/smhtt2018_svfitted_23feb_svfit/WW.root files_nominal_tt/WW.root WW VV 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2018_svfitted_23feb_svfit/WZ.root files_nominal_tt/WZ.root WZ VV 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2018_svfitted_23feb_svfit/ZZ.root files_nominal_tt/ZZ.root ZZ VV 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2018_svfitted_23feb_svfit/ST_t_antitop.root files_nominal_tt/ST_t_antitop.root ST_t_antitop VV 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2018_svfitted_23feb_svfit/ST_t_top.root files_nominal_tt/ST_t_top.root ST_t_top VV 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2018_svfitted_23feb_svfit/ST_tW_antitop.root files_nominal_tt/ST_tW_antitop.root ST_tW_antitop VV 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2018_svfitted_23feb_svfit/ST_tW_top.root files_nominal_tt/ST_tW_top.root ST_tW_top VV 0
hadd -f files_nominal_tt/VV.root files_nominal_tt/WW.root files_nominal_tt/WZ.root files_nominal_tt/ZZ.root files_nominal_tt/ST_t_antitop.root files_nominal_tt/ST_t_top.root files_nominal_tt/ST_tW_antitop.root files_nominal_tt/ST_tW_top.root 
./FinalSelection_tt.exe /data/ccaillol/smhtt2018_svfitted_23feb_svfit/ggH125.root files_nominal_tt/ggH_htt125.root ggH_htt125 ggH_htt125 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2018_svfitted_23feb_svfit/VBF125.root files_nominal_tt/qqH_htt125.root qqH_htt125 qqH_htt125 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2018_svfitted_23feb_svfit/WplusH125.root files_nominal_tt/Wplus125.root WplusH125 WH_htt125 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2018_svfitted_23feb_svfit/WminusH125.root files_nominal_tt/WminusH125.root WminusH125 WH_htt125 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2018_svfitted_23feb_svfit/ZH125.root files_nominal_tt/ZH125.root ZH125 ZH_htt125 0
hadd -f files_nominal_tt/signal.root files_nominal_tt/ggH_htt125.root files_nominal_tt/qqH_htt125.root files_nominal_tt/Wplus125.root files_nominal_tt/WminusH125.root files_nominal_tt/ZH125.root
./FinalSelection_tt.exe /data/ccaillol/smhtt2018_svfitted_23feb_svfit/EWKZLL.root files_nominal_tt/EWKZLL.root EWKZLL DY 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2018_svfitted_23feb_svfit/EWKZNuNu.root files_nominal_tt/EWKZNuNu.root EWKZNuNu DY 0
hadd -f files_nominal_tt/EWKZ.root files_nominal_tt/EWKZLL.root files_nominal_tt/EWKZNuNu.root
python Create_fake_tt.py
#sh do_rivet.sh

hadd -f smh_tt_2D.root files_nominal_tt/Data.root files_nominal_tt/DY.root files_nominal_tt/W.root files_nominal_tt/TT.root files_nominal_tt/VV.root files_nominal_tt/Fake.root files_nominal_tt/DYlow.root files_nominal_tt/signal.root files_nominal_tt/EWKZ.root #files_nominal_tt/rivet.root files_nominal_tt/Embedded.root 
python Create_1D_tt.py

