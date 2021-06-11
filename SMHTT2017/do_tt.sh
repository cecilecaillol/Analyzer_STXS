./Make.sh FinalSelection_tt.cc
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/DataB.root files_nominal_tt/DataB.root data_obs data_obs 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/DataC.root files_nominal_tt/DataC.root data_obs data_obs 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/DataD.root files_nominal_tt/DataD.root data_obs data_obs 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/DataE.root files_nominal_tt/DataE.root data_obs data_obs 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/DataF.root files_nominal_tt/DataF.root data_obs data_obs 0
hadd -f files_nominal_tt/Data.root files_nominal_tt/DataB.root files_nominal_tt/DataC.root files_nominal_tt/DataD.root files_nominal_tt/DataE.root files_nominal_tt/DataF.root
#./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/Embedded.root files_nominal_tt/Embedded.root embedded embedded 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/EmbeddedB.root files_nominal_tt/EmbeddedB.root embedded embedded 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/EmbeddedC.root files_nominal_tt/EmbeddedC.root embedded embedded 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/EmbeddedD.root files_nominal_tt/EmbeddedD.root embedded embedded 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/EmbeddedE.root files_nominal_tt/EmbeddedE.root embedded embedded 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/EmbeddedF.root files_nominal_tt/EmbeddedF.root embedded embedded 0
hadd -f files_nominal_tt/Embedded.root files_nominal_tt/EmbeddedB.root files_nominal_tt/EmbeddedC.root files_nominal_tt/EmbeddedD.root files_nominal_tt/EmbeddedE.root files_nominal_tt/EmbeddedF.root
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/DY.root files_nominal_tt/DYincl.root DY DY 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/DY1.root files_nominal_tt/DY1.root DY DY 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/DY2.root files_nominal_tt/DY2.root DY DY 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/DY3.root files_nominal_tt/DY3.root DY DY 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/DY4.root files_nominal_tt/DY4.root DY DY 0
hadd -f files_nominal_tt/DY.root files_nominal_tt/DYincl.root files_nominal_tt/DY1.root files_nominal_tt/DY2.root files_nominal_tt/DY3.root files_nominal_tt/DY4.root
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/DYlow.root files_nominal_tt/DYlow.root DYlow DYlow 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/W.root files_nominal_tt/Wincl.root W W 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/W1.root files_nominal_tt/W1.root W W 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/W2.root files_nominal_tt/W2.root W W 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/W3.root files_nominal_tt/W3.root W W 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/W4.root files_nominal_tt/W4.root W W 0
hadd -f files_nominal_tt/W.root files_nominal_tt/Wincl.root files_nominal_tt/W1.root files_nominal_tt/W2.root files_nominal_tt/W3.root files_nominal_tt/W4.root 
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/TTToHadronic.root files_nominal_tt/TTToHadronic.root TTToHadronic TT 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/TTTo2L2Nu.root files_nominal_tt/TTTo2L2Nu.root TTTo2L2Nu TT 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/TTToSemiLeptonic.root files_nominal_tt/TTToSemiLeptonic.root TTToSemiLeptonic TT 0
hadd -f files_nominal_tt/TT.root files_nominal_tt/TTToHadronic.root files_nominal_tt/TTToSemiLeptonic.root files_nominal_tt/TTTo2L2Nu.root
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/WW.root files_nominal_tt/WW.root WW VV 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/WZ.root files_nominal_tt/WZ.root WZ VV 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/ZZ.root files_nominal_tt/ZZ.root ZZ VV 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/ST_t_antitop.root files_nominal_tt/ST_t_antitop.root ST_t_antitop VV 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/ST_t_top.root files_nominal_tt/ST_t_top.root ST_t_top VV 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/ST_tW_antitop.root files_nominal_tt/ST_tW_antitop.root ST_tW_antitop VV 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/ST_tW_top.root files_nominal_tt/ST_tW_top.root ST_tW_top VV 0
hadd -f files_nominal_tt/VV.root files_nominal_tt/WW.root files_nominal_tt/WZ.root files_nominal_tt/ZZ.root files_nominal_tt/ST_t_antitop.root files_nominal_tt/ST_t_top.root files_nominal_tt/ST_tW_antitop.root files_nominal_tt/ST_tW_top.root 
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/ggH125.root files_nominal_tt/ggH_htt125.root ggH_htt125 ggH_htt125 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/VBF125.root files_nominal_tt/qqH_htt125.root qqH_htt125 qqH_htt125 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/WplusH125.root files_nominal_tt/Wplus125.root WplusH125 WH_htt125 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/WminusH125.root files_nominal_tt/WminusH125.root WminusH125 WH_htt125 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/ZH125.root files_nominal_tt/ZH125.root ZH125 ZH_htt125 0
hadd -f files_nominal_tt/signal.root files_nominal_tt/ggH_htt125.root files_nominal_tt/qqH_htt125.root files_nominal_tt/Wplus125.root files_nominal_tt/WminusH125.root files_nominal_tt/ZH125.root
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/EWKZLL.root files_nominal_tt/EWKZLL.root EWKZLL EWKZ 0
./FinalSelection_tt.exe /data/ccaillol/smhtt2017_sv_21feb/EWKZNuNu.root files_nominal_tt/EWKZNuNu.root EWKZNuNu EWKZ 0
hadd -f files_nominal_tt/EWKZ.root files_nominal_tt/EWKZLL.root files_nominal_tt/EWKZNuNu.root
python Create_fake_tt.py
python Create_embeddedUnc_tt.py
#sh do_rivet.sh

hadd -f smh_tt_2D.root files_nominal_tt/Embedded.root files_nominal_tt/EmbeddedUnc.root files_nominal_tt/EWKZ.root files_nominal_tt/Data.root files_nominal_tt/DY.root files_nominal_tt/W.root files_nominal_tt/TT.root files_nominal_tt/VV.root files_nominal_tt/Fake.root files_nominal_tt/DYlow.root files_nominal_tt/signal.root #files_nominal_tt/rivet.root
python Create_1D_tt.py

