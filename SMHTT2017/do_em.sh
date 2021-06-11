./Make.sh FinalSelection_em.cc
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_5mar/DataB.root files_nominal_em/DataB.root data_obs data_obs 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_5mar/DataC.root files_nominal_em/DataC.root data_obs data_obs 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_5mar/DataD.root files_nominal_em/DataD.root data_obs data_obs 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_5mar/DataE.root files_nominal_em/DataE.root data_obs data_obs 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_5mar/DataF.root files_nominal_em/DataF.root data_obs data_obs 0
hadd -f files_nominal_em/Data.root files_nominal_em/DataB.root files_nominal_em/DataC.root files_nominal_em/DataD.root files_nominal_em/DataE.root files_nominal_em/DataF.root
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_5mar/DY.root files_nominal_em/DYincl.root Z Z 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_5mar/DY1.root files_nominal_em/DY1.root Z Z 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_5mar/DY2.root files_nominal_em/DY2.root Z Z 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_5mar/DY3.root files_nominal_em/DY3.root Z Z 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_5mar/DY4.root files_nominal_em/DY4.root Z Z 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_5mar/DY.root files_nominal_em/DYinclFake.root Z W 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_5mar/DY1.root files_nominal_em/DY1Fake.root Z W 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_5mar/DY2.root files_nominal_em/DY2Fake.root Z W 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_5mar/DY3.root files_nominal_em/DY3Fake.root Z W 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_5mar/DY4.root files_nominal_em/DY4Fake.root Z W 0
hadd -f files_nominal_em/DY.root files_nominal_em/DYincl.root files_nominal_em/DY1.root files_nominal_em/DY2.root files_nominal_em/DY3.root files_nominal_em/DY4.root files_nominal_em/DYinclFake.root files_nominal_em/DY1Fake.root files_nominal_em/DY2Fake.root files_nominal_em/DY3Fake.root files_nominal_em/DY4Fake.root
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_5mar/Wall.root files_nominal_em/W.root W W 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_5mar/TTToHadronic.root files_nominal_em/TTToHadronic.root TTToHadronic TT 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_5mar/TTTo2L2Nu.root files_nominal_em/TTTo2L2Nu.root TTTo2L2Nu TT 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_5mar/TTToSemiLeptonic.root files_nominal_em/TTToSemiLeptonic.root TTToSemiLeptonic TT 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_5mar/TTToHadronic.root files_nominal_em/TTToHadronicFake.root TTToHadronic W 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_5mar/TTTo2L2Nu.root files_nominal_em/TTTo2L2NuFake.root TTTo2L2Nu W 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_5mar/TTToSemiLeptonic.root files_nominal_em/TTToSemiLeptonicFake.root TTToSemiLeptonic W 0
hadd -f files_nominal_em/TT.root files_nominal_em/TTToHadronic.root files_nominal_em/TTTo2L2Nu.root files_nominal_em/TTToSemiLeptonic.root files_nominal_em/TTToHadronicFake.root files_nominal_em/TTTo2L2NuFake.root files_nominal_em/TTToSemiLeptonicFake.root 
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_5mar/ST_t_antitop.root files_nominal_em/ST_t_antitop.root ST_t_antitop ST 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_5mar/ST_t_top.root files_nominal_em/ST_t_top.root ST_t_top ST 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_5mar/ST_tW_antitop.root files_nominal_em/ST_tW_antitop.root ST_tW_antitop ST 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_5mar/ST_tW_top.root files_nominal_em/ST_tW_top.root ST_tW_top ST 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_5mar/WZ2L2Q.root files_nominal_em/WZ2L2Q.root WZ2L2Q VV 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_5mar/WZ3L1Nu.root files_nominal_em/WZ3L1Nu.root WZ3L1Nu VV 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_5mar/VV2L2Nu.root files_nominal_em/VV2L2Nu.root VV2L2Nu VV 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_5mar/ZZ2L2Q.root files_nominal_em/ZZ2L2Q.root ZZ2L2Q VV 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_5mar/ZZ4L.root files_nominal_em/ZZ4L.root ZZ4L VV 0
hadd -f files_nominal_em/VV.root files_nominal_em/WZ2L2Q.root files_nominal_em/WZ3L1Nu.root files_nominal_em/VV2L2Nu.root files_nominal_em/ZZ2L2Q.root files_nominal_em/ZZ4L.root files_nominal_em/ST_tW_antitop.root files_nominal_em/ST_tW_top.root

./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_11may/ggH125.root files_nominal_em/ggH_htt125.root ggH_htt125 ggH_htt125 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_11may/VBF125.root files_nominal_em/qqH_htt125.root qqH_htt125 qqH_htt125 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_11may/WplusH125.root files_nominal_em/Wplus125_had.root WplusH125 WH_had_htt125 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_11may/WplusH125.root files_nominal_em/Wplus125_lep.root WplusH125 WH_lep_htt125 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_11may/WminusH125.root files_nominal_em/WminusH125_had.root WminusH125 WH_had_htt125 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_11may/WminusH125.root files_nominal_em/WminusH125_lep.root WminusH125 WH_lep_htt125 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_11may/ZH125.root files_nominal_em/ZH125_had.root ZH125 ZH_had_htt125 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_11may/ZH125.root files_nominal_em/ZH125_lep.root ZH125 ZH_lep_htt125 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_11may/GGZHLLTT.root files_nominal_em/GGZHLLTT.root GGZHLLTT125 ggZH_lep_htt125 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_11may/GGZHQQTT.root files_nominal_em/GGZHQQTT.root GGZHQQTT125 ggZH_had_htt125 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_11may/GGZHNNTT.root files_nominal_em/GGZHNNTT.root GGZHNNTT125 ggZH_lep_htt125 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_11may/GGHWW.root files_nominal_em/GGHWW.root GGHWW ggH_hww125 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_11may/VBFHWW.root files_nominal_em/VBFHWW.root VBFHWW qqH_hww125 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_11may/WplusHWW.root files_nominal_em/WplusHWW.root WplusHWW WH_hww125 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_11may/WminusHWW.root files_nominal_em/WminusHWW.root WminusHWW WH_hww125 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_11may/ZHWW.root files_nominal_em/ZHWW.root ZHWW ZH_hww125 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_11may/ZHWW.root files_nominal_em/ZHWWlep.root ZHWW ZH_lep_hww125 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_11may/ZHWW.root files_nominal_em/ZHWWhad.root ZHWW ZH_had_hww125 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_11may/GGZHWW.root files_nominal_em/GGZHWW.root GGZHWW ZH_hww125 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_11may/GGZHWW.root files_nominal_em/GGZHWWlep.root GGZHWW ggZH_lep_hww125 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_11may/GGZHWW.root files_nominal_em/GGZHWWhad.root GGZHWW ggZH_had_hww125 0
hadd -f files_nominal_em/signal.root files_nominal_em/ggH_htt125.root files_nominal_em/qqH_htt125.root files_nominal_em/Wplus125_had.root files_nominal_em/Wplus125_lep.root files_nominal_em/WminusH125_had.root files_nominal_em/WminusH125_lep.root files_nominal_em/ZH125_had.root files_nominal_em/ZH125_lep.root files_nominal_em/GGZHLLTT.root files_nominal_em/GGZHQQTT.root files_nominal_em/GGZHNNTT.root files_nominal_em/GGHWW.root files_nominal_em/VBFHWW.root files_nominal_em/WplusHWW.root files_nominal_em/WminusHWW.root files_nominal_em/ZHWW.root files_nominal_em/GGZHWW.root files_nominal_em/ZHWWlep.root files_nominal_em/ZHWWhad.root files_nominal_em/GGZHWWlep.root files_nominal_em/GGZHWWhad.root 

./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_5mar/EWKZLL.root files_nominal_em/EWKZLL.root EWKZLL EWKZ 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_5mar/EWKZNuNu.root files_nominal_em/EWKZNuNu.root EWKZNuNu EWKZ 0
hadd -f files_nominal_em/EWKZ.root files_nominal_em/EWKZLL.root files_nominal_em/EWKZNuNu.root
sh do_rivet_em.sh
sh do_hwwrivet_em.sh

#./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_2mar/Embedded.root files_nominal_em/embeddedNoBBB.root embedded embedded 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_5mar/Embedded.root files_nominal_em/embeddedNoBBB.root embedded embedded 0
python Add_embedded_bbb.py
python Create_fake_em_embedded.py
python Add_embedded_shape_em.py
hadd -f smh_em_2D.root files_nominal_em/Data.root files_nominal_em/embedded.root files_nominal_em/embeddedShape.root files_nominal_em/DY.root files_nominal_em/W.root files_nominal_em/TT.root files_nominal_em/VV.root files_nominal_em/Fake.root files_nominal_em/signal.root files_nominal_em/EWKZ.root files_nominal_em/qqH_rivet125.root files_nominal_em/ggH_rivet125.root files_nominal_em/WminusH_rivet125.root files_nominal_em/WplusH_rivet125.root files_nominal_em/ZH_rivet125.root files_nominal_em/GGZHLLTT_rivet125.root files_nominal_em/GGZHQQTT_rivet125.root files_nominal_em/GGZHNNTT_rivet125.root files_nominal_em/qqHWW_rivet125.root files_nominal_em/ggHWW_rivet125.root files_nominal_em/WminusHWW_rivet125.root files_nominal_em/WplusHWW_rivet125.root files_nominal_em/ZHWW_rivet125.root files_nominal_em/GGZHWWlep_rivet125.root files_nominal_em/GGZHWWhad_rivet125.root 
python Create_1D_em.py

#python Create_fake_em.py
#hadd -f smh_em_2D.root files_nominal_em/Data.root files_nominal_em/DY.root files_nominal_em/W.root files_nominal_em/TT.root files_nominal_em/VV.root files_nominal_em/Fake.root files_nominal_em/signal.root files_nominal_em/EWKZ.root #files_nominal_em/qqH_rivet125.root files_nominal_em/ggH_rivet125.root
#python Create_1D_em.py

