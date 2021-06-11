./Make.sh FinalSelection_mt.cc
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/DataB.root files_nominal_mt/DataB.root data_obs data_obs 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/DataC.root files_nominal_mt/DataC.root data_obs data_obs 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/DataD.root files_nominal_mt/DataD.root data_obs data_obs 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/DataE.root files_nominal_mt/DataE.root data_obs data_obs 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/DataF.root files_nominal_mt/DataF.root data_obs data_obs 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/DataG.root files_nominal_mt/DataG.root data_obs data_obs 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/DataH.root files_nominal_mt/DataH.root data_obs data_obs 0
hadd -f files_nominal_mt/Data.root files_nominal_mt/DataB.root files_nominal_mt/DataC.root files_nominal_mt/DataD.root files_nominal_mt/DataE.root files_nominal_mt/DataF.root files_nominal_mt/DataG.root files_nominal_mt/DataH.root
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/DY.root files_nominal_mt/DYincl.root Z Z 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/DY1.root files_nominal_mt/DY1.root Z Z 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/DY2.root files_nominal_mt/DY2.root Z Z 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/DY3.root files_nominal_mt/DY3.root Z Z 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/DY4.root files_nominal_mt/DY4.root Z Z 0
hadd -f files_nominal_mt/DY.root files_nominal_mt/DYincl.root files_nominal_mt/DY1.root files_nominal_mt/DY2.root files_nominal_mt/DY3.root files_nominal_mt/DY4.root
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/W.root files_nominal_mt/Wincl.root W W 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/W1.root files_nominal_mt/W1.root W W 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/W2.root files_nominal_mt/W2.root W W 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/W3.root files_nominal_mt/W3.root W W 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/W4.root files_nominal_mt/W4.root W W 0
hadd -f files_nominal_mt/W.root files_nominal_mt/Wincl.root files_nominal_mt/W1.root files_nominal_mt/W2.root files_nominal_mt/W3.root files_nominal_mt/W4.root
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/TT.root files_nominal_mt/TT.root TT TT 0
###./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/WW.root files_nominal_mt/WW.root WW VV 0
###./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/WZ.root files_nominal_mt/WZ.root WZ VV 0
###./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/ZZ.root files_nominal_mt/ZZ.root ZZ VV 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/WZ2L2Q.root files_nominal_mt/WZ2L2Q.root WZ2L2Q VV 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/WZ3L1Nu.root files_nominal_mt/WZ3L1Nu.root WZ3L1Nu VV 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/VV2L2Nu.root files_nominal_mt/VV2L2Nu.root VV2L2Nu VV 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/ZZ2L2Q.root files_nominal_mt/ZZ2L2Q.root ZZ2L2Q VV 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/ZZ4L.root files_nominal_mt/ZZ4L.root ZZ4L VV 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/ST_t_antitop.root files_nominal_mt/ST_t_antitop.root ST_t_antitop ST 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/ST_t_top.root files_nominal_mt/ST_t_top.root ST_t_top ST 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/ST_tW_antitop.root files_nominal_mt/ST_tW_antitop.root ST_tW_antitop ST 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/ST_tW_top.root files_nominal_mt/ST_tW_top.root ST_tW_top ST 0
###hadd -f files_nominal_mt/VV.root files_nominal_mt/ST_t_antitop.root files_nominal_mt/ST_t_top.root files_nominal_mt/ST_tW_antitop.root files_nominal_mt/ST_tW_top.root files_nominal_mt/WW.root files_nominal_mt/WZ.root files_nominal_mt/ZZ.root 
hadd -f files_nominal_mt/VV.root files_nominal_mt/ST_t_antitop.root files_nominal_mt/ST_t_top.root files_nominal_mt/ST_tW_antitop.root files_nominal_mt/ST_tW_top.root files_nominal_mt/WZ2L2Q.root files_nominal_mt/WZ3L1Nu.root files_nominal_mt/VV2L2Nu.root files_nominal_mt/ZZ2L2Q.root files_nominal_mt/ZZ4L.root
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/ggH125.root files_nominal_mt/ggH_htt125.root ggH_htt125 ggH_htt125 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/VBF125.root files_nominal_mt/qqH_htt125.root qqH_htt125 qqH_htt125 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/WplusH125.root files_nominal_mt/Wplus125.root WplusH125 WH_htt125 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/WminusH125.root files_nominal_mt/WminusH125.root WminusH125 WH_htt125 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/ZH125.root files_nominal_mt/ZH125.root ZH125 ZH_htt125 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/GGZHLLTT.root files_nominal_mt/GGZHLLTT.root GGZHLLTT125 ZH_htt125 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/GGZHQQTT.root files_nominal_mt/GGZHQQTT.root GGZHQQTT125 ZH_htt125 0
###./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/GGZHNNTT.root files_nominal_mt/GGZHNNTT.root GGZHNNTT125 ZH_htt125 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/GGHWW.root files_nominal_mt/GGHWW.root GGHWW ggH_hww125 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/VBFHWW.root files_nominal_mt/VBFHWW.root VBFHWW qqH_hww125 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/WplusHWW.root files_nominal_mt/WplusHWW.root WplusHWW WH_hww125 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/WminusHWW.root files_nominal_mt/WminusHWW.root WminusHWW WH_hww125 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/ZHWW.root files_nominal_mt/ZHWW.root ZHWW ZH_hww125 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/GGZHWW.root files_nominal_mt/GGZHWW.root GGZHWW ZH_hww125 0

hadd -f files_nominal_mt/signal.root files_nominal_mt/ggH_htt125.root files_nominal_mt/qqH_htt125.root files_nominal_mt/Wplus125.root files_nominal_mt/WminusH125.root files_nominal_mt/ZH125.root files_nominal_mt/GGZHLLTT.root files_nominal_mt/GGZHQQTT.root files_nominal_mt/GGHWW.root files_nominal_mt/VBFHWW.root files_nominal_mt/WplusHWW.root files_nominal_mt/WminusHWW.root files_nominal_mt/ZHWW.root files_nominal_mt/GGZHWW.root
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/EWKZLL.root files_nominal_mt/EWKZLL.root EWKZLL EWKZ 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_23feb/EWKZNuNu.root files_nominal_mt/EWKZNuNu.root EWKZNuNu EWKZ 0
hadd -f files_nominal_mt/EWKZ.root files_nominal_mt/EWKZLL.root files_nominal_mt/EWKZNuNu.root
#sh do_rivet_mt.sh

######
./FinalSelection_mt.exe /data/ccaillol/smhmt2016_svfitted_2mar/embedded.root files_nominal_mt/embedded.root embedded embedded 0
python Add_embedded_shape_mt.py
python Create_fake_mt_embedded.py
#hadd -f smh_mt_2D.root files_nominal_mt/Data.root files_nominal_mt/embedded.root files_nominal_mt/DY.root files_nominal_mt/W.root files_nominal_mt/TT.root files_nominal_mt/VV.root files_nominal_mt/Fake.root files_nominal_mt/signal.root files_nominal_mt/EWKZ.root files_nominal_mt/qqH_rivet125.root files_nominal_mt/ggH_rivet125.root files_nominal_mt/embeddedShape.root
hadd -f smh_mt_2D.root files_nominal_mt/Data.root files_nominal_mt/embedded.root files_nominal_mt/DY.root files_nominal_mt/W.root files_nominal_mt/TT.root files_nominal_mt/VV.root files_nominal_mt/Fake.root files_nominal_mt/signal.root files_nominal_mt/EWKZ.root files_nominal_mt/embeddedShape.root 
python Create_1D_mt.py
