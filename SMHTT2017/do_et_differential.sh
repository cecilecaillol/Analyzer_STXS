./Make.sh FinalSelection_et.cc
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_31jan/DataB.root files_diff_et/DataB.root data_obs data_obs 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_31jan/DataC.root files_diff_et/DataC.root data_obs data_obs 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_31jan/DataD.root files_diff_et/DataD.root data_obs data_obs 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_31jan/DataE.root files_diff_et/DataE.root data_obs data_obs 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_31jan/DataF.root files_diff_et/DataF.root data_obs data_obs 0
hadd -f files_diff_et/Data.root files_diff_et/DataB.root files_diff_et/DataC.root files_diff_et/DataD.root files_diff_et/DataE.root files_diff_et/DataF.root 
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_31jan/DY.root files_diff_et/DYincl.root Z Z 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_31jan/DY1.root files_diff_et/DY1.root Z Z 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_31jan/DY2.root files_diff_et/DY2.root Z Z 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_31jan/DY3.root files_diff_et/DY3.root Z Z 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_31jan/DY4.root files_diff_et/DY4.root Z Z 0
hadd -f files_diff_et/DY.root files_diff_et/DYincl.root files_diff_et/DY1.root files_diff_et/DY2.root files_diff_et/DY3.root files_diff_et/DY4.root #files_diff_et/DYlow.root
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_31jan/Wall.root files_diff_et/W.root W W 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_31jan/TTToHadronic.root files_diff_et/TTToHadronic.root TTToHadronic TT 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_31jan/TTTo2L2Nu.root files_diff_et/TTTo2L2Nu.root TTTo2L2Nu TT 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_31jan/TTToSemiLeptonic.root files_diff_et/TTToSemiLeptonic.root TTToSemiLeptonic TT 0
hadd -f files_diff_et/TT.root files_diff_et/TTToHadronic.root files_diff_et/TTTo2L2Nu.root files_diff_et/TTToSemiLeptonic.root
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_31jan/WZ2L2Q.root files_diff_et/WZ2L2Q.root WZ2L2Q VV 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_31jan/WZ3L1Nu.root files_diff_et/WZ3L1Nu.root WZ3L1Nu VV 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_31jan/VV2L2Nu.root files_diff_et/VV2L2Nu.root VV2L2Nu VV 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_31jan/ZZ2L2Q.root files_diff_et/ZZ2L2Q.root ZZ2L2Q VV 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_31jan/ZZ4L.root files_diff_et/ZZ4L.root ZZ4L VV 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_31jan/ST_t_antitop.root files_diff_et/ST_t_antitop.root ST_t_antitop ST 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_31jan/ST_t_top.root files_diff_et/ST_t_top.root ST_t_top ST 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_31jan/ST_tW_antitop.root files_diff_et/ST_tW_antitop.root ST_tW_antitop ST 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_31jan/ST_tW_top.root files_diff_et/ST_tW_top.root ST_tW_top ST 0
hadd -f files_diff_et/VV.root files_diff_et/ST_t_antitop.root files_diff_et/ST_t_top.root files_diff_et/ST_tW_antitop.root files_diff_et/ST_tW_top.root files_diff_et/WZ2L2Q.root files_diff_et/WZ3L1Nu.root files_diff_et/VV2L2Nu.root files_diff_et/ZZ2L2Q.root files_diff_et/ZZ4L.root 

./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_11may/ggH125.root files_diff_et/ggH_htt125.root ggH_htt125 ggH_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_11may/VBF125.root files_diff_et/qqH_htt125.root qqH_htt125 qqH_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_11may/WplusH125.root files_diff_et/Wplus125.root WplusH125 WH_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_11may/WminusH125.root files_diff_et/WminusH125.root WminusH125 WH_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_11may/ZH125.root files_diff_et/ZH125.root ZH125 ZH_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_11may/GGZHLLTT.root files_diff_et/GGZHLLTT.root GGZHLLTT125 ZH_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_11may/GGZHQQTT.root files_diff_et/GGZHQQTT.root GGZHQQTT125 ZH_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_11may/GGZHNNTT.root files_diff_et/GGZHNNTT.root GGZHNNTT125 ZH_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_11may/GGHWW.root files_diff_et/GGHWW.root GGHWW ggH_hww125 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_11may/VBFHWW.root files_diff_et/VBFHWW.root VBFHWW qqH_hww125 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_11may/WplusHWW.root files_diff_et/WplusHWW.root WplusHWW WH_hww125 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_11may/WminusHWW.root files_diff_et/WminusHWW.root WminusHWW WH_hww125 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_11may/ZHWW.root files_diff_et/ZHWW.root ZHWW ZH_hww125 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_11may/GGZHWW.root files_diff_et/GGZHWW.root GGZHWW ZH_hww125 0
hadd -f files_diff_et/signal.root files_diff_et/ggH_htt125.root files_diff_et/qqH_htt125.root files_diff_et/Wplus125.root files_diff_et/WminusH125.root files_diff_et/ZH125.root files_diff_et/GGZHLLTT.root files_diff_et/GGZHQQTT.root files_diff_et/GGZHNNTT.root files_diff_et/GGHWW.root files_diff_et/VBFHWW.root files_diff_et/WplusHWW.root files_diff_et/WminusHWW.root files_diff_et/ZHWW.root files_diff_et/GGZHWW.root

./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_11may/ggH125.root files_diff_et/ggH_htt125_nonfid.root ggH_htt125 ggH_htt_nonfid125 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_11may/VBF125.root files_diff_et/qqH_htt125_nonfid.root qqH_htt125 qqH_htt_nonfid125 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_11may/WplusH125.root files_diff_et/Wplus125_nonfid.root WplusH125 WH_htt_nonfid125 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_11may/WminusH125.root files_diff_et/WminusH125_nonfid.root WminusH125 WH_htt_nonfid125 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_11may/ZH125.root files_diff_et/ZH125_nonfid.root ZH125 ZH_htt_nonfid125 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_11may/GGZHLLTT.root files_diff_et/GGZHLLTT_nonfid.root GGZHLLTT125 ZH_htt_nonfid125 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_11may/GGZHQQTT.root files_diff_et/GGZHQQTT_nonfid.root GGZHQQTT125 ZH_htt_nonfid125 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_11may/GGZHNNTT.root files_diff_et/GGZHNNTT_nonfid.root GGZHNNTT125 ZH_htt_nonfid125 0
hadd -f files_diff_et/signal_nonfid.root files_diff_et/ggH_htt125_nonfid.root files_diff_et/qqH_htt125_nonfid.root files_diff_et/Wplus125_nonfid.root files_diff_et/WminusH125_nonfid.root files_diff_et/ZH125_nonfid.root files_diff_et/GGZHLLTT_nonfid.root files_diff_et/GGZHQQTT_nonfid.root files_diff_et/GGZHNNTT_nonfid.root 

./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_31jan/EWKZLL.root files_diff_et/EWKZLL.root EWKZLL EWKZ 0
./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_31jan/EWKZNuNu.root files_diff_et/EWKZNuNu.root EWKZNuNu EWKZ 0
hadd -f files_diff_et/EWKZ.root files_diff_et/EWKZLL.root files_diff_et/EWKZNuNu.root

./FinalSelection_et.exe /data/ccaillol/smhet2017_svfitted_2mar/Embedded.root files_diff_et/embedded.root embedded embedded 0

sh signal_differential_ggH_htt_et.sh
sh signal_differential_qqH_htt_et.sh
sh signal_differential_WplusH_htt_et.sh
sh signal_differential_WminusH_htt_et.sh
sh signal_differential_ZH_htt_et.sh

python Add_embedded_shape_et.py --directory diff
python Create_fake_et_embedded.py --directory diff
hadd -f smh_et_diff_2D.root files_diff_et/Data.root files_diff_et/embedded.root files_diff_et/embeddedShape.root files_diff_et/DY.root files_diff_et/W.root files_diff_et/TT.root files_diff_et/VV.root files_diff_et/Fake.root files_diff_et/signal.root files_diff_et/EWKZ.root files_diff_et/diff_ggH.root files_diff_et/diff_qqH.root files_diff_et/diff_WplusH.root files_diff_et/diff_WminusH.root files_diff_et/diff_ZH.root files_diff_et/signal_nonfid.root 
python Create_1D_et_differential.py

