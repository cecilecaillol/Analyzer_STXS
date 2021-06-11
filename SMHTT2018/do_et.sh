./Make.sh FinalSelection_et.cc
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_31jan/DataA.root files_nominal_et/DataA.root data_obs data_obs 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_31jan/DataB.root files_nominal_et/DataB.root data_obs data_obs 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_31jan/DataC.root files_nominal_et/DataC.root data_obs data_obs 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_31jan/DataD.root files_nominal_et/DataD.root data_obs data_obs 0
hadd -f files_nominal_et/Data.root files_nominal_et/DataA.root files_nominal_et/DataB.root files_nominal_et/DataC.root files_nominal_et/DataD.root
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_31jan/DY.root files_nominal_et/DYincl.root Z Z 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_31jan/DY1.root files_nominal_et/DY1.root Z Z 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_31jan/DY2.root files_nominal_et/DY2.root Z Z 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_31jan/DY3.root files_nominal_et/DY3.root Z Z 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_31jan/DY4.root files_nominal_et/DY4.root Z Z 0
hadd -f files_nominal_et/DY.root files_nominal_et/DYincl.root files_nominal_et/DY1.root files_nominal_et/DY2.root files_nominal_et/DY3.root files_nominal_et/DY4.root
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_31jan/Wall.root files_nominal_et/W.root W W 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_31jan/TTToHadronic.root files_nominal_et/TTToHadronic.root TTToHadronic TT 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_31jan/TTTo2L2Nu.root files_nominal_et/TTTo2L2Nu.root TTTo2L2Nu TT 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_31jan/TTToSemiLeptonic.root files_nominal_et/TTToSemiLeptonic.root TTToSemiLeptonic TT 0
hadd -f files_nominal_et/TT.root files_nominal_et/TTToHadronic.root files_nominal_et/TTTo2L2Nu.root files_nominal_et/TTToSemiLeptonic.root
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_31jan/WZ2L2Q.root files_nominal_et/WZ2L2Q.root WZ2L2Q VV 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_31jan/WZ3L1Nu.root files_nominal_et/WZ3L1Nu.root WZ3L1Nu VV 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_31jan/VV2L2Nu.root files_nominal_et/VV2L2Nu.root VV2L2Nu VV 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_31jan/ZZ2L2Q.root files_nominal_et/ZZ2L2Q.root ZZ2L2Q VV 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_31jan/ZZ4L.root files_nominal_et/ZZ4L.root ZZ4L VV 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_31jan/ST_t_antitop.root files_nominal_et/ST_t_antitop.root ST_t_antitop ST 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_31jan/ST_t_top.root files_nominal_et/ST_t_top.root ST_t_top ST 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_31jan/ST_tW_antitop.root files_nominal_et/ST_tW_antitop.root ST_tW_antitop ST 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_31jan/ST_tW_top.root files_nominal_et/ST_tW_top.root ST_tW_top ST 0
hadd -f files_nominal_et/VV.root  files_nominal_et/ST_t_antitop.root files_nominal_et/ST_t_top.root files_nominal_et/ST_tW_antitop.root files_nominal_et/ST_tW_top.root files_nominal_et/WZ2L2Q.root files_nominal_et/WZ3L1Nu.root files_nominal_et/VV2L2Nu.root files_nominal_et/ZZ2L2Q.root files_nominal_et/ZZ4L.root 
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_11may/ggH125.root files_nominal_et/ggH_htt125.root ggH_htt125 ggH_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_11may/VBF125.root files_nominal_et/qqH_htt125.root qqH_htt125 qqH_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_11may/WplusH125.root files_nominal_et/Wplus125_had.root WplusH125 WH_had_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_11may/WplusH125.root files_nominal_et/Wplus125_lep.root WplusH125 WH_lep_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_11may/WminusH125.root files_nominal_et/WminusH125_had.root WminusH125 WH_had_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_11may/WminusH125.root files_nominal_et/WminusH125_lep.root WminusH125 WH_lep_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_11may/ZH125.root files_nominal_et/ZH125_had.root ZH125 ZH_had_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_11may/ZH125.root files_nominal_et/ZH125_lep.root ZH125 ZH_lep_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_11may/GGZHLLTT.root files_nominal_et/GGZHLLTT125.root GGZHLLTT125 ggZH_lep_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_11may/GGZHQQTT.root files_nominal_et/GGZHQQTT125.root GGZHQQTT125 ggZH_had_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_11may/GGZHNNTT.root files_nominal_et/GGZHNNTT125.root GGZHNNTT125 ggZH_lep_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_11may/ggHWW.root files_nominal_et/ggH_hww125.root GGHWW ggH_hww125 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_11may/VBFWW.root files_nominal_et/qqH_hww125.root VBFHWW qqH_hww125 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_11may/WplusHWW.root files_nominal_et/WplusWW.root WplusHWW WH_hww125 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_11may/WminusHWW.root files_nominal_et/WminusHWW.root WminusHWW WH_hww125 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_11may/ZHWW.root files_nominal_et/ZHWW.root ZHWW ZH_hww125 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_11may/ZHWW.root files_nominal_et/ZHWWhad.root ZHWW ZH_had_hww125 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_11may/ZHWW.root files_nominal_et/ZHWWlep.root ZHWW ZH_lep_hww125 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_11may/GGZHWW.root files_nominal_et/GGZHWW.root GGZHWW ZH_hww125 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_11may/GGZHWW.root files_nominal_et/GGZHWWhad.root GGZHWW ggZH_had_hww125 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_11may/GGZHWW.root files_nominal_et/GGZHWWlep.root GGZHWW ggZH_lep_hww125 0
hadd -f files_nominal_et/signal.root files_nominal_et/ggH_htt125.root files_nominal_et/qqH_htt125.root files_nominal_et/Wplus125_had.root files_nominal_et/Wplus125_lep.root files_nominal_et/WminusH125_had.root files_nominal_et/WminusH125_lep.root files_nominal_et/ZH125_had.root files_nominal_et/ZH125_lep.root files_nominal_et/ggH_hww125.root files_nominal_et/qqH_hww125.root files_nominal_et/WplusWW.root files_nominal_et/WminusHWW.root files_nominal_et/ZHWW.root files_nominal_et/GGZHWW.root files_nominal_et/GGZHLLTT125.root files_nominal_et/GGZHNNTT125.root files_nominal_et/GGZHQQTT125.root files_nominal_et/ZHWWhad.root files_nominal_et/ZHWWlep.root files_nominal_et/GGZHWWhad.root files_nominal_et/GGZHWWlep.root 
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_31jan/EWKZLL.root files_nominal_et/EWKZLL.root EWKZLL EWKZ 0
./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_31jan/EWKZNuNu.root files_nominal_et/EWKZNuNu.root EWKZNuNu EWKZ 0
hadd -f files_nominal_et/EWKZ.root files_nominal_et/EWKZLL.root files_nominal_et/EWKZNuNu.root
sh do_rivet_et.sh
sh do_hwwrivet_et.sh

./FinalSelection_et.exe /data/ccaillol/smhet2018_svfitted_2mar/Embedded.root files_nominal_et/embedded.root embedded embedded 0
python Create_fake_et_embedded.py
python Add_embedded_shape_et.py
hadd -f smh_et_2D.root files_nominal_et/Data.root files_nominal_et/DY.root files_nominal_et/W.root files_nominal_et/TT.root files_nominal_et/VV.root files_nominal_et/Fake.root files_nominal_et/signal.root files_nominal_et/EWKZ.root files_nominal_et/embedded.root files_nominal_et/embeddedShape.root files_nominal_et/qqH_rivet125.root files_nominal_et/ggH_rivet125.root files_nominal_et/WminusH_rivet125.root files_nominal_et/WplusH_rivet125.root files_nominal_et/ZH_rivet125.root files_nominal_et/GGZHLLTT_rivet125.root files_nominal_et/GGZHQQTT_rivet125.root files_nominal_et/GGZHNNTT_rivet125.root files_nominal_et/ggHWW_rivet125.root files_nominal_et/qqHWW_rivet125.root files_nominal_et/WplusHWW_rivet125.root files_nominal_et/WminusHWW_rivet125.root files_nominal_et/ZHWW_rivet125.root files_nominal_et/GGZHWWlep_rivet125.root files_nominal_et/GGZHWWhad_rivet125.root 
python Create_1D_et.py



#python Create_fake_et.py
#hadd -f smh_et_2D.root files_nominal_et/Data.root files_nominal_et/DY.root files_nominal_et/W.root files_nominal_et/TT.root files_nominal_et/VV.root files_nominal_et/Fake.root files_nominal_et/signal.root files_nominal_et/EWKZ.root #files_nominal_et/qqH_rivet125.root files_nominal_et/ggH_rivet125.root
#python Create_1D_et.py

