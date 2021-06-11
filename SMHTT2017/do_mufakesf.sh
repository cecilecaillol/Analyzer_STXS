./Make.sh MuFakeSF.cc
./MuFakeSF.exe /data/ccaillol/smhmt2017_26jul/DataB.root mufakefiles/DataB.root data_obs data_obs 0
./MuFakeSF.exe /data/ccaillol/smhmt2017_26jul/DataC.root mufakefiles/DataC.root data_obs data_obs 0
./MuFakeSF.exe /data/ccaillol/smhmt2017_26jul/DataD.root mufakefiles/DataD.root data_obs data_obs 0
./MuFakeSF.exe /data/ccaillol/smhmt2017_26jul/DataE.root mufakefiles/DataE.root data_obs data_obs 0
./MuFakeSF.exe /data/ccaillol/smhmt2017_26jul/DataF.root mufakefiles/DataF.root data_obs data_obs 0
hadd -f mufakefiles/Data.root mufakefiles/DataB.root mufakefiles/DataC.root mufakefiles/DataD.root mufakefiles/DataE.root mufakefiles/DataF.root
./MuFakeSF.exe /data/ccaillol/smhmt2017_26jul/DY.root mufakefiles/DYincl.root DY DY 0
./MuFakeSF.exe /data/ccaillol/smhmt2017_26jul/DY1.root mufakefiles/DY1.root DY DY 0
./MuFakeSF.exe /data/ccaillol/smhmt2017_26jul/DY2.root mufakefiles/DY2.root DY DY 0
./MuFakeSF.exe /data/ccaillol/smhmt2017_26jul/DY3.root mufakefiles/DY3.root DY DY 0
./MuFakeSF.exe /data/ccaillol/smhmt2017_26jul/DY4.root mufakefiles/DY4.root DY DY 0
hadd -f mufakefiles/DY.root mufakefiles/DYincl.root mufakefiles/DY1.root mufakefiles/DY2.root mufakefiles/DY3.root mufakefiles/DY4.root
./MuFakeSF.exe /data/ccaillol/smhmt2017_26jul/W.root mufakefiles/Wincl.root W W 0
./MuFakeSF.exe /data/ccaillol/smhmt2017_26jul/W1.root mufakefiles/W1.root W W 0
./MuFakeSF.exe /data/ccaillol/smhmt2017_26jul/W2.root mufakefiles/W2.root W W 0
./MuFakeSF.exe /data/ccaillol/smhmt2017_26jul/W3.root mufakefiles/W3.root W W 0
./MuFakeSF.exe /data/ccaillol/smhmt2017_26jul/W4.root mufakefiles/W4.root W W 0
hadd -f mufakefiles/W.root mufakefiles/Wincl.root mufakefiles/W1.root mufakefiles/W2.root mufakefiles/W3.root mufakefiles/W4.root
./MuFakeSF.exe /data/ccaillol/smhmt2017_26jul/TTToHadronic.root mufakefiles/TTToHadronic.root TTToHadronic TT 0
./MuFakeSF.exe /data/ccaillol/smhmt2017_26jul/TTTo2L2Nu.root mufakefiles/TTTo2L2Nu.root TTTo2L2Nu TT 0
./MuFakeSF.exe /data/ccaillol/smhmt2017_26jul/TTToSemiLeptonic.root mufakefiles/TTToSemiLeptonic.root TTToSemiLeptonic TT 0
hadd -f mufakefiles/TT.root mufakefiles/TTToHadronic.root mufakefiles/TTTo2L2Nu.root mufakefiles/TTToSemiLeptonic.root
./MuFakeSF.exe /data/ccaillol/smhmt2017_26jul/WW.root mufakefiles/WW.root WW VV 0
./MuFakeSF.exe /data/ccaillol/smhmt2017_26jul/WZ.root mufakefiles/WZ.root WZ VV 0
./MuFakeSF.exe /data/ccaillol/smhmt2017_26jul/ZZ.root mufakefiles/ZZ.root ZZ VV 0
./MuFakeSF.exe /data/ccaillol/smhmt2017_26jul/ST_t_antitop.root mufakefiles/ST_t_antitop.root ST_t_antitop ST 0
./MuFakeSF.exe /data/ccaillol/smhmt2017_26jul/ST_t_top.root mufakefiles/ST_t_top.root ST_t_top ST 0
./MuFakeSF.exe /data/ccaillol/smhmt2017_26jul/ST_tW_antitop.root mufakefiles/ST_tW_antitop.root ST_tW_antitop ST 0
./MuFakeSF.exe /data/ccaillol/smhmt2017_26jul/ST_tW_top.root mufakefiles/ST_tW_top.root ST_tW_top ST 0
hadd -f mufakefiles/VV.root mufakefiles/WW.root mufakefiles/WZ.root mufakefiles/ZZ.root mufakefiles/ST_t_antitop.root mufakefiles/ST_t_top.root mufakefiles/ST_tW_antitop.root mufakefiles/ST_tW_top.root
python Scale_W_mufake.py
python Create_mufake.py

hadd -f mufakesf.root mufakefiles/Data.root mufakefiles/DY.root mufakefiles/Wscaled.root mufakefiles/TTscaled.root mufakefiles/VV.root mufakefiles/Fake.root

