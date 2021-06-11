#!/usr/bin/env python
import ROOT
import re
from array import array

def add_lumi():
    lowX=0.68
    lowY=0.835
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.30, lowY+0.16, "NDC")
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.SetTextSize(0.06)
    lumi.SetTextFont (   42 )
    lumi.AddText("2016, 35.9 fb^{-1} (13 TeV)")
    return lumi

def add_CMS():
    lowX=0.21
    lowY=0.70
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(61)
    lumi.SetTextSize(0.08)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("CMS Preliminary")
    return lumi

def add_Preliminary():
    lowX=0.21
    lowY=0.63
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(52)
    lumi.SetTextSize(0.06)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("Preliminary")
    return lumi

def make_legend():
        output = ROOT.TLegend(0.65, 0.64, 0.92, 0.86, "", "brNDC")
        output.SetNColumns(2)
        output.SetLineWidth(0)
        output.SetLineStyle(0)
        output.SetFillStyle(0)
        output.SetBorderSize(0)
        output.SetTextFont(62)
        return output

#ROOT.gStyle.SetFrameLineWidth(3)
#ROOT.gStyle.SetLineWidth(3)
ROOT.gStyle.SetOptStat(0)

c=ROOT.TCanvas("canvas","",0,0,1200,600)
c.cd()

fDY=ROOT.TFile("files_nominal_mt/DY.root","r")
fW=ROOT.TFile("files_nominal_mt/W.root","r")
fTT=ROOT.TFile("files_nominal_mt/TT.root","r")
fVV=ROOT.TFile("files_nominal_mt/VV.root","r")
fData=ROOT.TFile("files_nominal_mt/Data.root","r")
fEmbedded=ROOT.TFile("files_nominal_mt/embedded.root","r")

adapt=ROOT.gROOT.GetColor(12)
new_idx=ROOT.gROOT.GetListOfColors().GetSize() + 1
trans=ROOT.TColor(new_idx, adapt.GetRed(), adapt.GetGreen(),adapt.GetBlue(), "",0.5)

#categories=["mt_0jetlow","mt_0jethigh","mt_boosted1","mt_boosted2","mt_vbflow","mt_vbfhigh"] 
categories=["mt_0jet_PTH_0_10","mt_0jet_PTH_GE10","mt_boosted_1J","mt_boosted_GE2J","mt_vbf_PTH_0_200","mt_vbf_PTH_GE_200"]

ncat=6

freal=["f3real","f4real","f5real","f6real","f7real","f8real"]
fjet=["f3jet","f4jet","f5jet","f6jet","f7jet","f8jet"]

for i in range (0,ncat):
   Data=fData.Get(freal[i])
   TT=fTT.Get(fjet[i])
   W=fW.Get(fjet[i])
   W.Add(fVV.Get(fjet[i]))
   DYS=fDY.Get(freal[i])
   DYS.Add(fTT.Get(freal[i]))
   DYS.Add(fVV.Get(freal[i]))
   DYS.Add(fEmbedded.Get(freal[i]))

   QCD=Data.Clone()
   QCD.Add(TT,-1)
   QCD.Add(W,-1)
   QCD.Add(DYS,-1)
   if QCD.Integral()<0:
     QCD.Scale(0)

   Data.GetXaxis().SetTitle("")
   Data.GetXaxis().SetTitleSize(0)
   Data.GetXaxis().SetNdivisions(505)
   Data.GetYaxis().SetLabelFont(42)
   Data.GetYaxis().SetLabelOffset(0.01)
   Data.GetYaxis().SetLabelSize(0.06)
   Data.GetYaxis().SetTitleSize(0.075)
   Data.GetYaxis().SetTitleOffset(1.04)
   Data.SetTitle("")
   Data.GetYaxis().SetTitle("Events/bin")


   QCD.SetFillColor(ROOT.TColor.GetColor("#ffccff"))
   W.SetFillColor(ROOT.TColor.GetColor("#de5a6a"))
   TT.SetFillColor(ROOT.TColor.GetColor("#9999cc"))
   DYS.SetFillColor(ROOT.TColor.GetColor("#ffcc66"))

   Data.SetMarkerStyle(20)
   Data.SetMarkerSize(1)
   QCD.SetLineColor(1)
   W.SetLineColor(1)
   TT.SetLineColor(1)
   DYS.SetLineColor(1)
   Data.SetLineColor(1)
   Data.SetLineWidth(2)

   stack=ROOT.THStack("stack","stack")
   stack.Add(QCD)
   stack.Add(W)
   stack.Add(TT)
   stack.Add(DYS)

   errorBand = QCD.Clone()
   errorBand.Add(W)
   errorBand.Add(TT)
   errorBand.Add(DYS)
   errorBand.SetMarkerSize(0)
   errorBand.SetFillColor(new_idx)
   errorBand.SetFillStyle(3001)
   errorBand.SetLineWidth(1)

   pad1 = ROOT.TPad("pad1","pad1",0,0.35,1,1)
   pad1.Draw()
   pad1.cd()
   pad1.SetFillColor(0)
   pad1.SetBorderMode(0)
   pad1.SetBorderSize(10)
   pad1.SetTickx(1)
   pad1.SetTicky(1)
   pad1.SetLeftMargin(0.18)
   pad1.SetRightMargin(0.05)
   pad1.SetTopMargin(0.122)
   pad1.SetBottomMargin(0.026)
   pad1.SetFrameFillStyle(0)
   pad1.SetFrameLineStyle(0)
   pad1.SetFrameBorderMode(0)
   pad1.SetFrameBorderSize(10)
   #pad1.SetLogy()

   Data.GetXaxis().SetLabelSize(0)
   #Data.SetMaximum(max(Data.GetMaximum()*4.5,errorBand.GetMaximum()*4.5))
   Data.SetMaximum(max(Data.GetMaximum()*1.5,errorBand.GetMaximum()*1.5))
   #Data.SetMinimum(1.5)
   Data.Draw("e")
   stack.Draw("histsame")
   errorBand.Draw("e2same")
   Data.Draw("esame")

   legende=make_legend()
   legende.AddEntry(Data,"Observed","elp")
   legende.AddEntry(DYS,"Prompt","f")
   legende.AddEntry(TT,"TT fake","f")
   legende.AddEntry(W,"W + VV fake","f")
   legende.AddEntry(QCD,"QCD","f")
   legende.AddEntry(errorBand,"Uncertainty","f")
   legende.Draw()

   l1=add_lumi()
   l1.Draw("same")
   l2=add_CMS()
   l2.Draw("same")
   l3=add_Preliminary()
   #l3.Draw("same")
 
   pad1.RedrawAxis()

   categ  = ROOT.TPaveText(0.45, 0.7+0.013, 0.83, 0.70+0.155, "NDC")
   categ.SetBorderSize(   0 )
   categ.SetFillStyle(    0 )
   categ.SetTextAlign(   12 )
   categ.SetTextSize ( 0.06 )
   categ.SetTextColor(    1 )
   categ.SetTextFont (   41 )
   if i==0:
    categ.AddText("0 jet ptH < 10")
   elif i==1 :
    categ.AddText("0 jet ptH > 10")
   elif i==2:
    categ.AddText("Boosted 1 jet")
   elif i==3 :
    categ.AddText("Boosted >= 2 jets")
   elif i==4:
    categ.AddText("VBF ptH < 200")
   elif i==5 :
    categ.AddText("VBF ptH > 200")
   #categ.Draw("same")

   c.cd()
   pad2 = ROOT.TPad("pad2","pad2",0,0,1,0.35);
   pad2.SetTopMargin(0.05);
   pad2.SetBottomMargin(0.35);
   pad2.SetLeftMargin(0.18);
   pad2.SetRightMargin(0.05);
   pad2.SetTickx(1)
   pad2.SetTicky(1)
   pad2.SetGridx()
   pad2.SetGridy()
   pad2.Draw()
   pad2.cd()
   h1=Data.Clone()
   h1.SetMaximum(1.5)#FIXME(1.5)
   h1.SetMinimum(0.5)#FIXME(0.5)
   h1.SetMarkerStyle(20)
   h3=errorBand.Clone()
   hwoE=errorBand.Clone()
   for iii in range (1,hwoE.GetSize()-1):
     hwoE.SetBinError(iii,0)
   h3.Sumw2()
   h1.Sumw2()
   h1.SetStats(0)
   h1.Divide(hwoE)
   h3.Divide(hwoE)
   #h1.GetXaxis().SetTitle("m_{vis}(#mu,#tau_{h}) (GeV)")
   h1.GetXaxis().SetTitle("Bin number")
   h1.GetXaxis().SetLabelSize(0.08)
   h1.GetYaxis().SetLabelSize(0.08)
   h1.GetYaxis().SetTitle("Obs./Exp.")
   h1.GetXaxis().SetNdivisions(505)
   h1.GetYaxis().SetNdivisions(5)

   h1.GetXaxis().SetTitleSize(0.15)
   h1.GetYaxis().SetTitleSize(0.15)
   h1.GetYaxis().SetTitleOffset(0.56)
   h1.GetXaxis().SetTitleOffset(1.04)
   h1.GetXaxis().SetLabelSize(0.11)
   h1.GetYaxis().SetLabelSize(0.11)
   h1.GetXaxis().SetTitleFont(42)
   h1.GetYaxis().SetTitleFont(42)

   h1.Draw("e0p")
   h3.Draw("e2same")

   c.cd()
   pad1.Draw()

   ROOT.gPad.RedrawAxis()

   c.Modified()
   c.SaveAs("dataMC_fractions_"+categories[i]+".pdf")


