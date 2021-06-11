./Make.sh Measure_OSSS_TT.cc
./Measure_OSSS_TT.exe /data/ccaillol/smhem2017_svfitted_20nov/DataB.root files_fractions/DataB.root data_obs data_obs 0
./Measure_OSSS_TT.exe /data/ccaillol/smhem2017_svfitted_20nov/DataC.root files_fractions/DataC.root data_obs data_obs 0
./Measure_OSSS_TT.exe /data/ccaillol/smhem2017_svfitted_20nov/DataD.root files_fractions/DataD.root data_obs data_obs 0
./Measure_OSSS_TT.exe /data/ccaillol/smhem2017_svfitted_20nov/DataE.root files_fractions/DataE.root data_obs data_obs 0
./Measure_OSSS_TT.exe /data/ccaillol/smhem2017_svfitted_20nov/DataF.root files_fractions/DataF.root data_obs data_obs 0
./Measure_OSSS_TT.exe /data/ccaillol/smhem2017_svfitted_20nov/TTToSemiLeptonic.root files_fractions/TTToSemiLeptonic.root TTToSemiLeptonic TT 0
./Measure_OSSS_TT.exe /data/ccaillol/smhem2017_svfitted_20nov/TTToHadronic.root files_fractions/TTToHadronic.root TTToHadronic TT 0
./Measure_OSSS_TT.exe /data/ccaillol/smhem2017_svfitted_20nov/Embedded.root files_fractions/embedded.root embedded embedded 0
hadd -f files_fractions/TT.root files_fractions/TTToSemiLeptonic.root files_fractions/TTToHadronic.root
hadd -f files_fractions/Data.root files_fractions/DataB.root files_fractions/DataC.root files_fractions/DataD.root files_fractions/DataE.root files_fractions/DataF.root
#./Measure_OSSS_TT.exe /data/ccaillol/smhem2017_svfitted_20nov/DY.root files_fractions/DYincl.root Z Z 0
#./Measure_OSSS_TT.exe /data/ccaillol/smhem2017_svfitted_20nov/DY1.root files_fractions/DY1.root Z Z 0
#./Measure_OSSS_TT.exe /data/ccaillol/smhem2017_svfitted_20nov/DY2.root files_fractions/DY2.root Z Z 0
#./Measure_OSSS_TT.exe /data/ccaillol/smhem2017_svfitted_20nov/DY3.root files_fractions/DY3.root Z Z 0
#./Measure_OSSS_TT.exe /data/ccaillol/smhem2017_svfitted_20nov/DY4.root files_fractions/DY4.root Z Z 0
#hadd -f files_fractions/DY.root files_fractions/DYincl.root files_fractions/DY1.root files_fractions/DY2.root files_fractions/DY3.root files_fractions/DY4.root 


