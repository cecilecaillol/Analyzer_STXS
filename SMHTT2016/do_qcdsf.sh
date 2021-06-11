./Make.sh QCDSF_em.cc
./QCDSF_em.exe /data/ccaillol/smhem2016_svfitted_16aug/DataB.root qcdfiles_em/DataB.root data_obs data_obs 0
./QCDSF_em.exe /data/ccaillol/smhem2016_svfitted_16aug/DataC.root qcdfiles_em/DataC.root data_obs data_obs 0
./QCDSF_em.exe /data/ccaillol/smhem2016_svfitted_16aug/DataD.root qcdfiles_em/DataD.root data_obs data_obs 0
./QCDSF_em.exe /data/ccaillol/smhem2016_svfitted_16aug/DataE.root qcdfiles_em/DataE.root data_obs data_obs 0
./QCDSF_em.exe /data/ccaillol/smhem2016_svfitted_16aug/DataF.root qcdfiles_em/DataF.root data_obs data_obs 0
./QCDSF_em.exe /data/ccaillol/smhem2016_svfitted_16aug/DataG.root qcdfiles_em/DataG.root data_obs data_obs 0
./QCDSF_em.exe /data/ccaillol/smhem2016_svfitted_16aug/DataH.root qcdfiles_em/DataH.root data_obs data_obs 0
hadd -f qcdfiles_em/Data.root qcdfiles_em/DataB.root qcdfiles_em/DataC.root qcdfiles_em/DataD.root qcdfiles_em/DataE.root qcdfiles_em/DataF.root qcdfiles_em/DataG.root qcdfiles_em/DataH.root
./QCDSF_em.exe /data/ccaillol/smhem2016_svfitted_16aug/DY.root qcdfiles_em/DYincl.root DY DY 0
./QCDSF_em.exe /data/ccaillol/smhem2016_svfitted_16aug/DY1.root qcdfiles_em/DY1.root DY DY 0
./QCDSF_em.exe /data/ccaillol/smhem2016_svfitted_16aug/DY2.root qcdfiles_em/DY2.root DY DY 0
./QCDSF_em.exe /data/ccaillol/smhem2016_svfitted_16aug/DY3.root qcdfiles_em/DY3.root DY DY 0
./QCDSF_em.exe /data/ccaillol/smhem2016_svfitted_16aug/DY4.root qcdfiles_em/DY4.root DY DY 0
hadd -f qcdfiles_em/DY.root qcdfiles_em/DYincl.root qcdfiles_em/DY1.root qcdfiles_em/DY2.root qcdfiles_em/DY3.root qcdfiles_em/DY4.root
./QCDSF_em.exe /data/ccaillol/smhem2016_svfitted_16aug/Wall.root qcdfiles_em/W.root W W 0
./QCDSF_em.exe /data/ccaillol/smhem2016_svfitted_16aug/TT.root qcdfiles_em/TT.root TT TT 0
#./QCDSF_em.exe /data/ccaillol/smhem2016_svfitted_16aug/WZ2L2Q.root qcdfiles_em/WZ2L2Q.root WZ2L2Q VV 0
#./QCDSF_em.exe /data/ccaillol/smhem2016_svfitted_16aug/WZ3L1Nu.root qcdfiles_em/WZ3L1Nu.root WZ3L1Nu VV 0
#./QCDSF_em.exe /data/ccaillol/smhem2016_svfitted_16aug/VV2L2Nu.root qcdfiles_em/VV2L2Nu.root VV2L2Nu VV 0
#./QCDSF_em.exe /data/ccaillol/smhem2016_svfitted_16aug/ZZ2L2Q.root qcdfiles_em/ZZ2L2Q.root ZZ2L2Q VV 0
#./QCDSF_em.exe /data/ccaillol/smhem2016_svfitted_16aug/ZZ4L.root qcdfiles_em/ZZ4L.root ZZ4L VV 0
./QCDSF_em.exe /data/ccaillol/smhem2016_svfitted_16aug/WW.root qcdfiles_em/WW.root WW VV 0
./QCDSF_em.exe /data/ccaillol/smhem2016_svfitted_16aug/WZ.root qcdfiles_em/WZ.root WZ VV 0
./QCDSF_em.exe /data/ccaillol/smhem2016_svfitted_16aug/ZZ.root qcdfiles_em/ZZ.root ZZ VV 0
./QCDSF_em.exe /data/ccaillol/smhem2016_svfitted_16aug/ST_t_antitop.root qcdfiles_em/ST_t_antitop.root ST_t_antitop ST 0
./QCDSF_em.exe /data/ccaillol/smhem2016_svfitted_16aug/ST_t_top.root qcdfiles_em/ST_t_top.root ST_t_top ST 0
./QCDSF_em.exe /data/ccaillol/smhem2016_svfitted_16aug/ST_tW_antitop.root qcdfiles_em/ST_tW_antitop.root ST_tW_antitop ST 0
./QCDSF_em.exe /data/ccaillol/smhem2016_svfitted_16aug/ST_tW_top.root qcdfiles_em/ST_tW_top.root ST_tW_top ST 0
hadd -f qcdfiles_em/VV.root qcdfiles_em/ST_t_antitop.root qcdfiles_em/ST_t_top.root qcdfiles_em/ST_tW_antitop.root qcdfiles_em/ST_tW_top.root qcdfiles_em/WW.root qcdfiles_em/WZ.root qcdfiles_em/ZZ.root
#hadd -f qcdfiles_em/VV.root qcdfiles_em/ST_t_antitop.root qcdfiles_em/ST_t_top.root qcdfiles_em/ST_tW_antitop.root qcdfiles_em/ST_tW_top.root qcdfiles_em/WZ2L2Q.root qcdfiles_em/WZ3L1Nu.root qcdfiles_em/VV2L2Nu.root qcdfiles_em/ZZ2L2Q.root qcdfiles_em/ZZ4L.root 

hadd -f qcd_em.root qcdfiles_em/Data.root qcdfiles_em/DY.root qcdfiles_em/W.root qcdfiles_em/TT.root qcdfiles_em/VV.root

python Compute_OSSS.py
rm osss_em_2016.root
root -l -b -q Fit_QCDSF_em.cc

