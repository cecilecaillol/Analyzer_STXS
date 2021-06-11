./Make.sh FinalSelection_em.cc
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/DataB.root files_topcontrol_em/DataB.root data_obs data_obs 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/DataC.root files_topcontrol_em/DataC.root data_obs data_obs 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/DataD.root files_topcontrol_em/DataD.root data_obs data_obs 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/DataE.root files_topcontrol_em/DataE.root data_obs data_obs 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/DataF.root files_topcontrol_em/DataF.root data_obs data_obs 0
hadd -f files_topcontrol_em/Data.root files_topcontrol_em/DataB.root files_topcontrol_em/DataC.root files_topcontrol_em/DataD.root files_topcontrol_em/DataE.root files_topcontrol_em/DataF.root
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/DY.root files_topcontrol_em/DYincl.root Z Z 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/DY1.root files_topcontrol_em/DY1.root Z Z 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/DY2.root files_topcontrol_em/DY2.root Z Z 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/DY3.root files_topcontrol_em/DY3.root Z Z 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/DY4.root files_topcontrol_em/DY4.root Z Z 0
hadd -f files_topcontrol_em/DY.root files_topcontrol_em/DYincl.root files_topcontrol_em/DY1.root files_topcontrol_em/DY2.root files_topcontrol_em/DY3.root files_topcontrol_em/DY4.root
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/Wall.root files_topcontrol_em/W.root W W 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/TTToHadronic.root files_topcontrol_em/TTToHadronic.root TTToHadronic TT 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/TTTo2L2Nu.root files_topcontrol_em/TTTo2L2Nu.root TTTo2L2Nu TT 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/TTToSemiLeptonic.root files_topcontrol_em/TTToSemiLeptonic.root TTToSemiLeptonic TT 0
hadd -f files_topcontrol_em/TT.root files_topcontrol_em/TTToHadronic.root files_topcontrol_em/TTTo2L2Nu.root files_topcontrol_em/TTToSemiLeptonic.root
#./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/WW.root files_topcontrol_em/WW.root WW VV 0
#./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/WZ.root files_topcontrol_em/WZ.root WZ VV 0
#./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/ZZ.root files_topcontrol_em/ZZ.root ZZ VV 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/ST_t_antitop.root files_topcontrol_em/ST_t_antitop.root ST_t_antitop ST 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/ST_t_top.root files_topcontrol_em/ST_t_top.root ST_t_top ST 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/ST_tW_antitop.root files_topcontrol_em/ST_tW_antitop.root ST_tW_antitop ST 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/ST_tW_top.root files_topcontrol_em/ST_tW_top.root ST_tW_top ST 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/WZ2L2Q.root files_topcontrol_em/WZ2L2Q.root WZ2L2Q VV 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/WZ3L1Nu.root files_topcontrol_em/WZ3L1Nu.root WZ3L1Nu VV 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/VV2L2Nu.root files_topcontrol_em/VV2L2Nu.root VV2L2Nu VV 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/ZZ2L2Q.root files_topcontrol_em/ZZ2L2Q.root ZZ2L2Q VV 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/ZZ4L.root files_topcontrol_em/ZZ4L.root ZZ4L VV 0
#hadd -f files_topcontrol_em/VV.root files_topcontrol_em/WW.root files_topcontrol_em/WZ.root files_topcontrol_em/ZZ.root files_topcontrol_em/ST_t_antitop.root files_topcontrol_em/ST_t_top.root files_topcontrol_em/ST_tW_antitop.root files_topcontrol_em/ST_tW_top.root
hadd -f files_topcontrol_em/VV.root files_topcontrol_em/WZ2L2Q.root files_topcontrol_em/WZ3L1Nu.root files_topcontrol_em/VV2L2Nu.root files_topcontrol_em/ZZ2L2Q.root files_topcontrol_em/ZZ4L.root files_topcontrol_em/ST_t_antitop.root files_topcontrol_em/ST_t_top.root files_topcontrol_em/ST_tW_antitop.root files_topcontrol_em/ST_tW_top.root
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/ggH125.root files_topcontrol_em/ggH_htt125.root ggH_htt125 ggH_htt125 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/VBF125.root files_topcontrol_em/qqH_htt125.root qqH_htt125 qqH_htt125 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/WplusH125.root files_topcontrol_em/Wplus125.root WplusH125 WH_htt125 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/WminusH125.root files_topcontrol_em/WminusH125.root WminusH125 WH_htt125 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/ZH125.root files_topcontrol_em/ZH125.root ZH125 ZH_htt125 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/GGZHLLTT.root files_topcontrol_em/GGZHLLTT.root GGZHLLTT125 ZH_htt125 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/GGZHQQTT.root files_topcontrol_em/GGZHQQTT.root GGZHQQTT125 ZH_htt125 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/GGZHNNTT.root files_topcontrol_em/GGZHNNTT.root GGZHNNTT125 ZH_htt125 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/GGHWW.root files_topcontrol_em/GGHWW.root GGHWW ggH_hww125 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/VBFHWW.root files_topcontrol_em/VBFHWW.root VBFHWW qqH_hww125 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/WplusHWW.root files_topcontrol_em/WplusHWW.root WplusHWW WH_hww125 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/WminusHWW.root files_topcontrol_em/WminusHWW.root WminusHWW WH_hww125 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/ZHWW.root files_topcontrol_em/ZHWW.root ZHWW ZH_hww125 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/GGZHWW.root files_topcontrol_em/GGZHWW.root GGZHWW ZH_hww125 0
hadd -f files_topcontrol_em/signal.root files_topcontrol_em/ggH_htt125.root files_topcontrol_em/qqH_htt125.root files_topcontrol_em/Wplus125.root files_topcontrol_em/WminusH125.root files_topcontrol_em/ZH125.root files_topcontrol_em/GGZHLLTT.root files_topcontrol_em/GGZHQQTT.root files_topcontrol_em/GGZHNNTT.root files_topcontrol_em/GGHWW.root files_topcontrol_em/VBFHWW.root files_topcontrol_em/WplusHWW.root files_topcontrol_em/WminusHWW.root files_topcontrol_em/ZHWW.root files_topcontrol_em/GGZHWW.root
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/EWKZLL.root files_topcontrol_em/EWKZLL.root EWKZLL EWKZ 0
./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/EWKZNuNu.root files_topcontrol_em/EWKZNuNu.root EWKZNuNu EWKZ 0
hadd -f files_topcontrol_em/EWKZ.root files_topcontrol_em/EWKZLL.root files_topcontrol_em/EWKZNuNu.root

./FinalSelection_em.exe /data/ccaillol/smhem2017_svfitted_20nov/Embedded.root files_topcontrol_em/embedded.root embedded embedded 0
python Create_fake_em_embedded.py --directory topcontrol
python Add_embedded_shape_em.py
hadd -f smh_em_2D.root files_topcontrol_em/Data.root files_topcontrol_em/embedded.root files_topcontrol_em/DY.root files_topcontrol_em/W.root files_topcontrol_em/TT.root files_topcontrol_em/VV.root files_topcontrol_em/Fake.root files_topcontrol_em/signal.root files_topcontrol_em/EWKZ.root 
python Create_1D_em.py
cp smh_em.root topcontrol_em.root 

