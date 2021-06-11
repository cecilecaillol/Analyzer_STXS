#!/usr/bin/env python
import ROOT
from ROOT import *
import re
from array import array

islog=1
unrollSV=1

file=ROOT.TFile("smh_em_diff_2D.root","r")
file1=ROOT.TFile("smh_em_diff.root","recreate")


file.cd()
dirList = gDirectory.GetListOfKeys()
for k1 in dirList:
      if k1.GetName()=="em_0jet" or k1.GetName()=="em_boosted" or k1.GetName()=="em_vbf" or k1.GetName()=="em_0jethigh" or k1.GetName()=="em_0jetlow" or k1.GetName()=="em_boosted1" or k1.GetName()=="em_boosted2" or k1.GetName()=="em_vbflow" or k1.GetName()=="em_vbfhigh":
         h1 = k1.ReadObj()
	 name_newdir="em_0jet"
         if k1.GetName()=="em_0jet":
	    name_newdir="em_HiggsPt"
         if k1.GetName()=="em_boosted":
            name_newdir="em_njets"
         if k1.GetName()=="em_vbf":
            name_newdir="em_j1pt"
         if k1.GetName()=="em_0jetlow":
            name_newdir="em_2jet_low"
         if k1.GetName()=="em_0jethigh":
            name_newdir="em_2jet_high"
         if k1.GetName()=="em_boosted1":
            name_newdir="em_3jet"
         if k1.GetName()=="em_boosted2":
            name_newdir="em_4jet"
         if k1.GetName()=="em_vbflow":
            name_newdir="em_2jet"
         if k1.GetName()=="em_vbfhigh":
            name_newdir="em_control2"
         file1.mkdir(name_newdir)
         h1.cd()
         dirList2 = gDirectory.GetListOfKeys()
         for k2 in dirList2:
            h2 = k2.ReadObj()
            h3=h2.Clone()
            nn=h3.GetSize()
            nx=h3.GetXaxis().GetNbins()
   	    ny=h3.GetYaxis().GetNbins()
   	    h1d=ROOT.TH1F("h1d","h1d",nx*ny,0,nx*ny)
            dir1=nx
            dir2=ny
	    l=0
            for j in range(1,dir1+1):
      		for k in range(1,dir2+1):
        	   l=l+1
        	   n = h3.GetBin(j,k);
        	   h1d.SetBinContent(l,h3.GetBinContent(n))
        	   h1d.SetBinError(l,h3.GetBinError(n))
            file1.cd(name_newdir)
            h1d.SetName(k2.GetName())
	    h1d.Write()

