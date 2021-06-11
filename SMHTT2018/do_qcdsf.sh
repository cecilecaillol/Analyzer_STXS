./Make.sh QCDSF_em.cc
./QCDSF_em.exe /data/ccaillol/smhem2018_svfitted_20nov/DataA.root qcdfiles_em/DataA.root data_obs data_obs 0
./QCDSF_em.exe /data/ccaillol/smhem2018_svfitted_20nov/DataB.root qcdfiles_em/DataB.root data_obs data_obs 0
./QCDSF_em.exe /data/ccaillol/smhem2018_svfitted_20nov/DataC.root qcdfiles_em/DataC.root data_obs data_obs 0
./QCDSF_em.exe /data/ccaillol/smhem2018_svfitted_20nov/DataD.root qcdfiles_em/DataD.root data_obs data_obs 0
hadd -f qcdfiles_em/Data.root qcdfiles_em/DataA.root qcdfiles_em/DataB.root qcdfiles_em/DataC.root qcdfiles_em/DataD.root
./QCDSF_em.exe /data/ccaillol/smhem2018_svfitted_20nov/DY.root qcdfiles_em/DYincl.root DY DY 0
./QCDSF_em.exe /data/ccaillol/smhem2018_svfitted_20nov/DY1.root qcdfiles_em/DY1.root DY DY 0
./QCDSF_em.exe /data/ccaillol/smhem2018_svfitted_20nov/DY2.root qcdfiles_em/DY2.root DY DY 0
./QCDSF_em.exe /data/ccaillol/smhem2018_svfitted_20nov/DY3.root qcdfiles_em/DY3.root DY DY 0
./QCDSF_em.exe /data/ccaillol/smhem2018_svfitted_20nov/DY4.root qcdfiles_em/DY4.root DY DY 0
hadd -f qcdfiles_em/DY.root qcdfiles_em/DYincl.root qcdfiles_em/DY1.root qcdfiles_em/DY2.root qcdfiles_em/DY3.root qcdfiles_em/DY4.root
./QCDSF_em.exe /data/ccaillol/smhem2018_svfitted_20nov/Wall.root qcdfiles_em/W.root W W 0
./QCDSF_em.exe /data/ccaillol/smhem2018_svfitted_20nov/TTToHadronic.root qcdfiles_em/TTToHadronic.root TTToHadronic TT 0
./QCDSF_em.exe /data/ccaillol/smhem2018_svfitted_20nov/TTTo2L2Nu.root qcdfiles_em/TTTo2L2Nu.root TTTo2L2Nu TT 0
./QCDSF_em.exe /data/ccaillol/smhem2018_svfitted_20nov/TTToSemiLeptonic.root qcdfiles_em/TTToSemiLeptonic.root TTToSemiLeptonic TT 0
hadd -f qcdfiles_em/TT.root qcdfiles_em/TTToHadronic.root qcdfiles_em/TTTo2L2Nu.root qcdfiles_em/TTToSemiLeptonic.root
#./QCDSF_em.exe /data/ccaillol/smhem2018_svfitted_20nov/WW.root qcdfiles_em/WW.root WW VV 0
#./QCDSF_em.exe /data/ccaillol/smhem2018_svfitted_20nov/WZ.root qcdfiles_em/WZ.root WZ VV 0
#./QCDSF_em.exe /data/ccaillol/smhem2018_svfitted_20nov/ZZ.root qcdfiles_em/ZZ.root ZZ VV 0
./QCDSF_em.exe /data/ccaillol/smhem2018_svfitted_20nov/WZ2L2Q.root qcdfiles_em/WZ2L2Q.root WZ2L2Q VV 0
./QCDSF_em.exe /data/ccaillol/smhem2018_svfitted_20nov/WZ3L1Nu.root qcdfiles_em/WZ3L1Nu.root WZ3L1Nu VV 0
./QCDSF_em.exe /data/ccaillol/smhem2018_svfitted_20nov/VV2L2Nu.root qcdfiles_em/VV2L2Nu.root VV2L2Nu VV 0
./QCDSF_em.exe /data/ccaillol/smhem2018_svfitted_20nov/ZZ2L2Q.root qcdfiles_em/ZZ2L2Q.root ZZ2L2Q VV 0
./QCDSF_em.exe /data/ccaillol/smhem2018_svfitted_20nov/ZZ4L.root qcdfiles_em/ZZ4L.root ZZ4L VV 0
./QCDSF_em.exe /data/ccaillol/smhem2018_svfitted_20nov/ST_t_antitop.root qcdfiles_em/ST_t_antitop.root ST_t_antitop ST 0
./QCDSF_em.exe /data/ccaillol/smhem2018_svfitted_20nov/ST_t_top.root qcdfiles_em/ST_t_top.root ST_t_top ST 0
./QCDSF_em.exe /data/ccaillol/smhem2018_svfitted_20nov/ST_tW_antitop.root qcdfiles_em/ST_tW_antitop.root ST_tW_antitop ST 0
./QCDSF_em.exe /data/ccaillol/smhem2018_svfitted_20nov/ST_tW_top.root qcdfiles_em/ST_tW_top.root ST_tW_top ST 0
#hadd -f qcdfiles_em/VV.root qcdfiles_em/WW.root qcdfiles_em/WZ.root qcdfiles_em/ZZ.root qcdfiles_em/ST_t_antitop.root qcdfiles_em/ST_t_top.root qcdfiles_em/ST_tW_antitop.root qcdfiles_em/ST_tW_top.root
hadd -f qcdfiles_em/VV.root qcdfiles_em/ST_t_antitop.root qcdfiles_em/ST_t_top.root qcdfiles_em/ST_tW_antitop.root qcdfiles_em/ST_tW_top.root qcdfiles_em/WZ2L2Q.root qcdfiles_em/WZ3L1Nu.root qcdfiles_em/VV2L2Nu.root qcdfiles_em/ZZ2L2Q.root qcdfiles_em/ZZ4L.root 

hadd -f qcd_em.root qcdfiles_em/Data.root qcdfiles_em/DY.root qcdfiles_em/W.root qcdfiles_em/TT.root qcdfiles_em/VV.root

python Compute_OSSS.py
rm osss_em_2018.root
root -l -b -q Fit_QCDSF_em.cc
