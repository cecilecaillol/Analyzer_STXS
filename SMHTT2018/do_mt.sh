./Make.sh FinalSelection_mt.cc
./FinalSelection_mt.exe /data/ccaillol/smhmt2018_svfitted_12oct/DataA.root files_nominal_mt/DataA.root data_obs data_obs 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2018_svfitted_12oct/DataB.root files_nominal_mt/DataB.root data_obs data_obs 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2018_svfitted_12oct/DataC.root files_nominal_mt/DataC.root data_obs data_obs 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2018_svfitted_12oct/DataD.root files_nominal_mt/DataD.root data_obs data_obs 0
hadd -f files_nominal_mt/Data.root files_nominal_mt/DataA.root files_nominal_mt/DataB.root files_nominal_mt/DataC.root files_nominal_mt/DataD.root
./FinalSelection_mt.exe /data/ccaillol/smhmt2018_svfitted_12oct/DY.root files_nominal_mt/DYincl.root DY DY 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2018_svfitted_12oct/DY1.root files_nominal_mt/DY1.root DY DY 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2018_svfitted_12oct/DY2.root files_nominal_mt/DY2.root DY DY 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2018_svfitted_12oct/DY3.root files_nominal_mt/DY3.root DY DY 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2018_svfitted_12oct/DY4.root files_nominal_mt/DY4.root DY DY 0
hadd -f files_nominal_mt/DY.root files_nominal_mt/DYincl.root files_nominal_mt/DY1.root files_nominal_mt/DY2.root files_nominal_mt/DY3.root files_nominal_mt/DY4.root
./FinalSelection_mt.exe /data/ccaillol/smhmt2018_svfitted_12oct/Wall.root files_nominal_mt/W.root W W 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2018_svfitted_12oct/TTToHadronic.root files_nominal_mt/TTToHadronic.root TTToHadronic TT 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2018_svfitted_12oct/TTTo2L2Nu.root files_nominal_mt/TTTo2L2Nu.root TTTo2L2Nu TT 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2018_svfitted_12oct/TTToSemiLeptonic.root files_nominal_mt/TTToSemiLeptonic.root TTToSemiLeptonic TT 0
hadd -f files_nominal_mt/TT.root files_nominal_mt/TTToHadronic.root files_nominal_mt/TTTo2L2Nu.root files_nominal_mt/TTToSemiLeptonic.root
./FinalSelection_mt.exe /data/ccaillol/smhmt2018_svfitted_12oct/WW.root files_nominal_mt/WW.root WW VV 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2018_svfitted_12oct/WZ.root files_nominal_mt/WZ.root WZ VV 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2018_svfitted_12oct/ZZ.root files_nominal_mt/ZZ.root ZZ VV 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2018_svfitted_12oct/ST_t_antitop.root files_nominal_mt/ST_t_antitop.root ST_t_antitop ST 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2018_svfitted_12oct/ST_t_top.root files_nominal_mt/ST_t_top.root ST_t_top ST 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2018_svfitted_12oct/ST_tW_antitop.root files_nominal_mt/ST_tW_antitop.root ST_tW_antitop ST 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2018_svfitted_12oct/ST_tW_top.root files_nominal_mt/ST_tW_top.root ST_tW_top ST 0
hadd -f files_nominal_mt/VV.root files_nominal_mt/WW.root files_nominal_mt/WZ.root files_nominal_mt/ZZ.root files_nominal_mt/ST_t_antitop.root files_nominal_mt/ST_t_top.root files_nominal_mt/ST_tW_antitop.root files_nominal_mt/ST_tW_top.root
./FinalSelection_mt.exe /data/ccaillol/smhmt2018_svfitted_12oct/ggH125.root files_nominal_mt/ggH_htt125.root ggH_htt125 ggH_htt125 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2018_svfitted_12oct/VBF125.root files_nominal_mt/qqH_htt125.root qqH_htt125 qqH_htt125 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2018_svfitted_12oct/WplusH125.root files_nominal_mt/Wplus125.root WplusH125 WH_htt125 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2018_svfitted_12oct/WminusH125.root files_nominal_mt/WminusH125.root WminusH125 WH_htt125 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2018_svfitted_12oct/ZH125.root files_nominal_mt/ZH125.root ZH125 ZH_htt125 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2018_svfitted_12oct/GGZHLLTT.root files_nominal_mt/GGZHLLTT125.root GGZHLLTT125 ZH_htt125 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2018_svfitted_12oct/GGZHQQTT.root files_nominal_mt/GGZHQQTT125.root GGZHQQTT125 ZH_htt125 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2018_svfitted_12oct/GGZHNNTT.root files_nominal_mt/GGZHNNTT125.root GGZHNNTT125 ZH_htt125 0
#./FinalSelection_mt.exe /data/ccaillol/smhmt2018_svfitted_12oct/ggHWW.root files_nominal_mt/ggH_hww125.root GGHWW ggH_hww125 0
#./FinalSelection_mt.exe /data/ccaillol/smhmt2018_svfitted_12oct/VBFWW.root files_nominal_mt/qqH_hww125.root VBFHWW qqH_hww125 0
#./FinalSelection_mt.exe /data/ccaillol/smhmt2018_svfitted_12oct/WplusHWW.root files_nominal_mt/WplusWW.root WplusHWW WH_hww125 0
#./FinalSelection_mt.exe /data/ccaillol/smhmt2018_svfitted_12oct/WminusHWW.root files_nominal_mt/WminusHWW.root WminusHWW WH_hww125 0
#./FinalSelection_mt.exe /data/ccaillol/smhmt2018_svfitted_12oct/ZHWW.root files_nominal_mt/ZHWW.root ZHWW ZH_hww125 0
#./FinalSelection_mt.exe /data/ccaillol/smhmt2018_svfitted_12oct/GGZHWW.root files_nominal_mt/GGZHWW.root GGZHWW ZH_hww125 0
hadd -f files_nominal_mt/signal.root files_nominal_mt/ggH_htt125.root files_nominal_mt/qqH_htt125.root files_nominal_mt/Wplus125.root files_nominal_mt/WminusH125.root files_nominal_mt/ZH125.root #files_nominal_mt/ggH_hww125.root files_nominal_mt/qqH_hww125.root files_nominal_mt/WplusWW.root files_nominal_mt/WminusHWW.root files_nominal_mt/ZHWW.root files_nominal_mt/GGZHWW.root files_nominal_mt/GGZHLLTT125.root files_nominal_mt/GGZHNNTT125.root files_nominal_mt/GGZHQQTT125.root
./FinalSelection_mt.exe /data/ccaillol/smhmt2018_svfitted_12oct/EWKZLL.root files_nominal_mt/EWKZLL.root EWKZLL EWKZ 0
./FinalSelection_mt.exe /data/ccaillol/smhmt2018_svfitted_12oct/EWKZNuNu.root files_nominal_mt/EWKZNuNu.root EWKZNuNu EWKZ 0
hadd -f files_nominal_mt/EWKZ.root files_nominal_mt/EWKZLL.root files_nominal_mt/EWKZNuNu.root
#sh do_rivet_mt.sh

./FinalSelection_mt.exe /data/ccaillol/smhmt2018_svfitted_12oct/Embedded.root files_nominal_mt/embedded.root embedded embedded 0
python Create_fake_mt_embedded.py
#python Add_embedded_shape_mt.py
hadd -f smh_mt_2D.root files_nominal_mt/Data.root files_nominal_mt/DY.root files_nominal_mt/W.root files_nominal_mt/TT.root files_nominal_mt/VV.root files_nominal_mt/Fake.root files_nominal_mt/signal.root files_nominal_mt/EWKZ.root files_nominal_mt/embedded.root #files_nominal_mt/qqH_rivet125.root files_nominal_mt/ggH_rivet125.root files_nominal_mt/embeddedShape.root
python Create_1D_mt.py

#python Create_fake_mt.py
#hadd -f smh_mt_2D.root files_nominal_mt/Data.root files_nominal_mt/DY.root files_nominal_mt/W.root files_nominal_mt/TT.root files_nominal_mt/VV.root files_nominal_mt/Fake.root files_nominal_mt/signal.root files_nominal_mt/EWKZ.root #files_nominal_mt/qqH_rivet125.root files_nominal_mt/ggH_rivet125.root
#python Create_1D_mt.py

