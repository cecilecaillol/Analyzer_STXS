./Make.sh FinalSelection_em.cc
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_5mar/DataB.root files_diff_em/DataB.root data_obs data_obs 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_5mar/DataC.root files_diff_em/DataC.root data_obs data_obs 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_5mar/DataD.root files_diff_em/DataD.root data_obs data_obs 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_5mar/DataE.root files_diff_em/DataE.root data_obs data_obs 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_5mar/DataF.root files_diff_em/DataF.root data_obs data_obs 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_5mar/DataG.root files_diff_em/DataG.root data_obs data_obs 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_5mar/DataH.root files_diff_em/DataH.root data_obs data_obs 0
hadd -f files_diff_em/Data.root files_diff_em/DataB.root files_diff_em/DataC.root files_diff_em/DataD.root files_diff_em/DataE.root files_diff_em/DataF.root files_diff_em/DataG.root files_diff_em/DataH.root
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_5mar/DY.root files_diff_em/DYincl.root Z Z 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_5mar/DY1.root files_diff_em/DY1.root Z Z 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_5mar/DY2.root files_diff_em/DY2.root Z Z 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_5mar/DY3.root files_diff_em/DY3.root Z Z 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_5mar/DY4.root files_diff_em/DY4.root Z Z 0
hadd -f files_diff_em/DY.root files_diff_em/DYincl.root files_diff_em/DY1.root files_diff_em/DY2.root files_diff_em/DY3.root files_diff_em/DY4.root
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_5mar/Wall.root files_diff_em/W.root W W 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_5mar/TT.root files_diff_em/TT.root TT TT 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_5mar/WZ2L2Q.root files_diff_em/WZ2L2Q.root WZ2L2Q VV 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_5mar/WZ3L1Nu.root files_diff_em/WZ3L1Nu.root WZ3L1Nu VV 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_5mar/VV2L2Nu.root files_diff_em/VV2L2Nu.root VV2L2Nu VV 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_5mar/ZZ2L2Q.root files_diff_em/ZZ2L2Q.root ZZ2L2Q VV 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_5mar/ZZ4L.root files_diff_em/ZZ4L.root ZZ4L VV 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_5mar/ST_t_antitop.root files_diff_em/ST_t_antitop.root ST_t_antitop ST 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_5mar/ST_t_top.root files_diff_em/ST_t_top.root ST_t_top ST 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_5mar/ST_tW_antitop.root files_diff_em/ST_tW_antitop.root ST_tW_antitop ST 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_5mar/ST_tW_top.root files_diff_em/ST_tW_top.root ST_tW_top ST 0
hadd -f files_diff_em/VV.root files_diff_em/ST_t_antitop.root files_diff_em/ST_t_top.root files_diff_em/ST_tW_antitop.root files_diff_em/ST_tW_top.root files_diff_em/WZ2L2Q.root files_diff_em/WZ3L1Nu.root files_diff_em/VV2L2Nu.root files_diff_em/ZZ2L2Q.root files_diff_em/ZZ4L.root 

./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_11may/ggH125.root files_diff_em/ggH_htt125.root ggH_htt125 ggH_htt125 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_11may/VBF125.root files_diff_em/qqH_htt125.root qqH_htt125 qqH_htt125 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_11may/WplusH125.root files_diff_em/Wplus125.root WplusH125 WH_htt125 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_11may/WminusH125.root files_diff_em/WminusH125.root WminusH125 WH_htt125 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_11may/ZH125.root files_diff_em/ZH125.root ZH125 ZH_htt125 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_11may/GGZHLLTT.root files_diff_em/GGZHLLTT.root GGZHLLTT125 ZH_htt125 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_11may/GGZHQQTT.root files_diff_em/GGZHQQTT.root GGZHQQTT125 ZH_htt125 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_11may/GGHWW.root files_diff_em/GGHWW.root GGHWW ggH_hww125 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_11may/VBFHWW.root files_diff_em/VBFHWW.root VBFHWW qqH_hww125 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_11may/WplusHWW.root files_diff_em/WplusHWW.root WplusHWW WH_hww125 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_11may/WminusHWW.root files_diff_em/WminusHWW.root WminusHWW WH_hww125 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_11may/ZHWW.root files_diff_em/ZHWW.root ZHWW ZH_hww125 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_11may/GGZHWW.root files_diff_em/GGZHWW.root GGZHWW ZH_hww125 0
hadd -f files_diff_em/signal.root files_diff_em/ggH_htt125.root files_diff_em/qqH_htt125.root files_diff_em/Wplus125.root files_diff_em/WminusH125.root files_diff_em/ZH125.root files_diff_em/GGZHLLTT.root files_diff_em/GGZHQQTT.root files_diff_em/GGHWW.root files_diff_em/VBFHWW.root files_diff_em/WplusHWW.root files_diff_em/WminusHWW.root files_diff_em/ZHWW.root files_diff_em/GGZHWW.root 

./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_11may/ggH125.root files_diff_em/ggH_htt125_nonfid.root ggH_htt125 ggH_htt_nonfid125 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_11may/VBF125.root files_diff_em/qqH_htt125_nonfid.root qqH_htt125 qqH_htt_nonfid125 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_11may/WplusH125.root files_diff_em/Wplus125_nonfid.root WplusH125 WH_htt_nonfid125 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_11may/WminusH125.root files_diff_em/WminusH125_nonfid.root WminusH125 WH_htt_nonfid125 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_11may/ZH125.root files_diff_em/ZH125_nonfid.root ZH125 ZH_htt_nonfid125 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_11may/GGZHLLTT.root files_diff_em/GGZHLLTT_nonfid.root GGZHLLTT125 ZH_htt_nonfid125 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_11may/GGZHQQTT.root files_diff_em/GGZHQQTT_nonfid.root GGZHQQTT125 ZH_htt_nonfid125 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_11may/GGHWW.root files_diff_em/GGHWW_nonfid.root GGHWW ggH_hww125 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_11may/VBFHWW.root files_diff_em/VBFHWW_nonfid.root VBFHWW qqH_hww125 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_11may/WplusHWW.root files_diff_em/WplusHWW_nonfid.root WplusHWW WH_hww125 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_11may/WminusHWW.root files_diff_em/WminusHWW_nonfid.root WminusHWW WH_hww125 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_11may/ZHWW.root files_diff_em/ZHWW_nonfid.root ZHWW ZH_hww125 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_11may/GGZHWW.root files_diff_em/GGZHWW_nonfid.root GGZHWW ZH_hww125 0
hadd -f files_diff_em/signal_nonfid.root files_diff_em/ggH_htt125_nonfid.root files_diff_em/qqH_htt125_nonfid.root files_diff_em/Wplus125_nonfid.root files_diff_em/WminusH125_nonfid.root files_diff_em/ZH125_nonfid.root files_diff_em/GGZHLLTT_nonfid.root files_diff_em/GGZHQQTT_nonfid.root files_diff_em/GGHWW_nonfid.root files_diff_em/VBFHWW_nonfid.root files_diff_em/WplusHWW_nonfid.root files_diff_em/WminusHWW_nonfid.root files_diff_em/ZHWW_nonfid.root files_diff_em/GGZHWW_nonfid.root

./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_5mar/EWKZLL.root files_diff_em/EWKZLL.root EWKZLL EWKZ 0
./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_5mar/EWKZNuNu.root files_diff_em/EWKZNuNu.root EWKZNuNu EWKZ 0
hadd -f files_diff_em/EWKZ.root files_diff_em/EWKZLL.root files_diff_em/EWKZNuNu.root

./FinalSelection_em.exe /data/ccaillol/smhem2016_svfitted_5mar/embedded.root files_diff_em/embedded.root embedded embedded 0

sh signal_differential_ggH_htt_em.sh
sh signal_differential_qqH_htt_em.sh
sh signal_differential_WplusH_htt_em.sh
sh signal_differential_WminusH_htt_em.sh
sh signal_differential_ZH_htt_em.sh

python Create_fake_em_embedded.py --directory diff 
python Add_embedded_shape_em.py --directory diff 
hadd -f smh_em_diff_2D.root files_diff_em/Data.root files_diff_em/embedded.root files_diff_em/DY.root files_diff_em/W.root files_diff_em/TT.root files_diff_em/VV.root files_diff_em/Fake.root files_diff_em/signal.root files_diff_em/signal_nonfid.root files_diff_em/EWKZ.root files_diff_em/embeddedShape.root files_diff_em/diff_ggH.root files_diff_em/diff_qqH.root files_diff_em/diff_WplusH.root files_diff_em/diff_WminusH.root files_diff_em/diff_ZH.root
python Create_1D_em_differential.py


