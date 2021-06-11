#!/usr/bin/env python
import ROOT
import re
from array import array

def add_lumi():
    lowX=0.58
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
    lumi.SetTextSize(0.05)
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
        output = ROOT.TLegend(0.45, 0.64, 0.92, 0.86, "", "brNDC")
        output.SetNColumns(2)
        output.SetLineWidth(0)
        output.SetLineStyle(0)
        output.SetFillStyle(0)
        output.SetBorderSize(0)
        output.SetTextFont(62)
        return output

ROOT.gStyle.SetFrameLineWidth(3)
ROOT.gStyle.SetLineWidth(3)
ROOT.gStyle.SetOptStat(0)

c=ROOT.TCanvas("canvas","",0,0,600,600)
c.cd()

file=ROOT.TFile("control_em_embedded_1.root","r")
bins_mtt0 = [10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70];
bins_mtt1 = [10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70];
bins_mtt2 = [0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150];
bins_mtt3 = [0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175,180,185,190,195,200,205,210,215,220,225,230,235,240,245,250];
bins_mtt4 = [35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140];
bins_mtt5 = [60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220];
bins_mtt6 = [0,1,2,3,4,5,6,7];
bins_mtt7 = [-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5];
bins_mtt8 = [-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5];
name=["mupt","ept","met","pth","mvis","msv","njets","eeta","mueta"]
label=["#mu p_{T} (GeV)","e p_{T} (GeV)","MET (GeV)","Higgs p_{T} (GeV)","m_{vis}(e,#mu) (GeV)","m_{#tau#tau}(e,#mu) (GeV)","Jet multiplicity","e #eta","#mu #eta"]

#file=ROOT.TFile("control_em_embedded_2.root","r")
#bins_mtt0 = [-100,-90,-80,-70,-60,-50,-40,-30,-20,-10,0,10,20,30,40,50,60,70,80,90,100];
#bins_mtt1 = [0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,310,320,330,340,350,360,370,380,390,400,410,420,430,440,450,460,470,480,490,500];
#bins_mtt2 =[0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120];
#bins_mtt3 = [30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150];
#bins_mtt4 = [-4.7,-4.5,-4.3,-4.1,-3.9,-3.7,-3.5,-3.3,-3.1,-2.9,-2.7,-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5,2.7,2.9,3.1,3.3,3.5,3.7,3.9,4.1,4.3,4.5,4.7];
#bins_mtt5 = [30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120];
#bins_mtt6 = [-4.7,-4.5,-4.3,-4.1,-3.9,-3.7,-3.5,-3.3,-3.1,-2.9,-2.7,-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5,2.7,2.9,3.1,3.3,3.5,3.7,3.9,4.1,4.3,4.5,4.7];
#bins_mtt7 = [0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4,2.6,2.8,3.0,3.2,3.4,3.6,3.8,4.0,4.2,4.4,4.6,4.8,5.0,5.2,5.4,5.6,5.8,6.0,6.2,6.4,6.6,6.8,7.0];
#bins_mtt8 = [0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4,2.6,2.8,3.0,3.2,3.4,3.6,3.8,4.0,4.2,4.4,4.6,4.8,5.0];
#name=["dzeta","mjj","mt","j1pt","j1eta","j2pt","j2eta","detajj","dr"]
#label=["D_{#zeta} (GeV)","m_{jj} (GeV)","m_{T}(e#mu,MET) (GeV)","Leading jet p_{T} (GeV)","Leading jet #eta","Subleading jet p_{T} (GeV)", "Subleading jet #eta","#Delta#eta_{jj}","#DeltaR(e,#tau_{h})"]

newhist=[ROOT.TH1F("hist","hist",len(bins_mtt0)-1,float(bins_mtt0[0]),float(bins_mtt0[int(len(bins_mtt0)-1)]))]
newhist.append(ROOT.TH1F("hist","hist",len(bins_mtt1)-1,float(bins_mtt1[0]),float(bins_mtt1[int(len(bins_mtt1)-1)])))
newhist.append(ROOT.TH1F("hist","hist",len(bins_mtt2)-1,float(bins_mtt2[0]),float(bins_mtt2[int(len(bins_mtt2)-1)])))
newhist.append(ROOT.TH1F("hist","hist",len(bins_mtt3)-1,float(bins_mtt3[0]),float(bins_mtt3[int(len(bins_mtt3)-1)])))
newhist.append(ROOT.TH1F("hist","hist",len(bins_mtt4)-1,float(bins_mtt4[0]),float(bins_mtt4[int(len(bins_mtt4)-1)])))
newhist.append(ROOT.TH1F("hist","hist",len(bins_mtt5)-1,float(bins_mtt5[0]),float(bins_mtt5[int(len(bins_mtt5)-1)])))
newhist.append(ROOT.TH1F("hist","hist",len(bins_mtt6)-1,float(bins_mtt6[0]),float(bins_mtt6[int(len(bins_mtt6)-1)])))
newhist.append(ROOT.TH1F("hist","hist",len(bins_mtt7)-1,float(bins_mtt7[0]),float(bins_mtt7[int(len(bins_mtt7)-1)])))
newhist.append(ROOT.TH1F("hist","hist",len(bins_mtt8)-1,float(bins_mtt8[0]),float(bins_mtt8[int(len(bins_mtt8)-1)])))

adapt=ROOT.gROOT.GetColor(12)
new_idx=ROOT.gROOT.GetListOfColors().GetSize() + 1
trans=ROOT.TColor(new_idx, adapt.GetRed(), adapt.GetGreen(),adapt.GetBlue(), "",0.5)

categories=["em_0jet","em_boosted","em_vbf","em_0jetlow","em_0jethigh","em_boosted1","em_boosted2","em_vbflow","em_vbfhigh"] 
ncat=9

for i in range (0,ncat):
   Data2=file.Get(categories[i]).Get("data_obs")
   QCD2=file.Get(categories[i]).Get("QCD")
   W2=file.Get(categories[i]).Get("W") 
   TT2=file.Get(categories[i]).Get("TTL")
   VV2=file.Get(categories[i]).Get("VVL")
   VV2.Add(file.Get(categories[i]).Get("STL"))
   VV2.Add(file.Get(categories[i]).Get("ggH_hww125"))
   VV2.Add(file.Get(categories[i]).Get("qqH_hww125"))
   VV2.Add(file.Get(categories[i]).Get("WH_hww125"))
   VV2.Add(file.Get(categories[i]).Get("ZH_hww125"))
   DY2=file.Get(categories[i]).Get("embedded")
   VV2.Add(file.Get(categories[i]).Get("ZL"))
   signal2=file.Get(categories[i]).Get("ggH_htt125")
   signal2.Add(file.Get(categories[i]).Get("qqH_htt125"))
   signal2.Add(file.Get(categories[i]).Get("WH_htt125"))
   signal2.Add(file.Get(categories[i]).Get("ZH_htt125"))
   signal2.Scale(50)

   Data=newhist[i].Clone()
   QCD=newhist[i].Clone()
   W=newhist[i].Clone()
   TT=newhist[i].Clone()
   VV=newhist[i].Clone()
   DY=newhist[i].Clone()
   signal=newhist[i].Clone()

   for j in range(0,Data.GetSize()):
     Data.SetBinContent(j,Data2.GetBinContent(j))
     Data.SetBinError(j,Data2.GetBinError(j))
     QCD.SetBinContent(j,QCD2.GetBinContent(j))
     QCD.SetBinError(j,QCD2.GetBinError(j))
     W.SetBinContent(j,W2.GetBinContent(j))
     W.SetBinError(j,W2.GetBinError(j))
     DY.SetBinContent(j,DY2.GetBinContent(j))
     DY.SetBinError(j,DY2.GetBinError(j))
     VV.SetBinContent(j,VV2.GetBinContent(j))
     VV.SetBinError(j,VV2.GetBinError(j))
     TT.SetBinContent(j,TT2.GetBinContent(j))
     TT.SetBinError(j,TT2.GetBinError(j))
     signal.SetBinContent(j,signal2.GetBinContent(j))
     signal.SetBinError(j,signal2.GetBinError(j))

   Data.GetXaxis().SetTitle("")
   Data.GetXaxis().SetTitleSize(0)
   Data.GetXaxis().SetNdivisions(505)
   Data.GetYaxis().SetLabelFont(42)
   Data.GetYaxis().SetLabelOffset(0.01)
   Data.GetYaxis().SetLabelSize(0.06)
   Data.GetYaxis().SetTitleSize(0.075)
   Data.GetYaxis().SetTitleOffset(1.18)
   Data.SetTitle("")
   Data.GetYaxis().SetTitle("Events/bin")

   QCD.SetFillColor(ROOT.TColor.GetColor("#ffccff"))
   W.SetFillColor(ROOT.TColor.GetColor("#de5a6a"))
   TT.SetFillColor(ROOT.TColor.GetColor("#9999cc"))
   DY.SetFillColor(ROOT.TColor.GetColor("#ffcc66"))
   VV.SetFillColor(ROOT.TColor.GetColor("#12cadd"))

   #for k in range(1,Data.GetSize()-1):
   #   VV.SetBinError(k,(VV.GetBinError(k)*VV.GetBinError(k)+0.10*0.10*VV.GetBinContent(k)*VV.GetBinContent(k))**0.5)
   #   DY.SetBinError(k,(DY.GetBinError(k)*DY.GetBinError(k)+0.10*0.10*DY.GetBinContent(k)*DY.GetBinContent(k))**0.5)
   #   TT.SetBinError(k,(TT.GetBinError(k)*TT.GetBinError(k)+0.10*0.10*TT.GetBinContent(k)*TT.GetBinContent(k))**0.5)
   #   QCD.SetBinError(k,(QCD.GetBinError(k)*QCD.GetBinError(k)+0.20*0.20*QCD.GetBinContent(k)*QCD.GetBinContent(k))**0.5)

   #for k in range(1,Data.GetSize()-1):
   #     s=signal.GetBinContent(k)
   #     b=DYS.GetBinContent(k)+QCD.GetBinContent(k)+DYB.GetBinContent(k)+TT.GetBinContent(k)
   #     if (b<0):
   #         b=0.000001
   #     if (s/(0.00001+s+b)**0.5 > 0.2):
   #         Data.SetBinContent(k,-1)
   #         Data.SetBinError(k,-1)


   Data.SetMarkerStyle(20)
   Data.SetMarkerSize(1)
   QCD.SetLineColor(1)
   W.SetLineColor(1)
   TT.SetLineColor(1)
   DY.SetLineColor(1)
   VV.SetLineColor(1)
   Data.SetLineColor(1)
   Data.SetLineWidth(2)
   signal.SetLineWidth(3)
   signal.SetLineColor(2)
   #signal.SetFillColor(2)
   #signal.Scale(50)

   stack=ROOT.THStack("stack","stack")
   stack.Add(VV)
   stack.Add(QCD)
   stack.Add(W)
   stack.Add(TT)
   stack.Add(DY)
   #stack.Add(signal)

   errorBand = QCD.Clone()
   errorBand.Add(W)
   errorBand.Add(TT)
   errorBand.Add(VV)
   errorBand.Add(DY)
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
   pad1.SetFrameLineWidth(3)
   pad1.SetFrameBorderMode(0)
   pad1.SetFrameBorderSize(10)
   #pad1.SetLogy()

   Data.GetXaxis().SetLabelSize(0)
   Data.SetMaximum(max(Data.GetMaximum()*1.5,errorBand.GetMaximum()*1.5))
   Data.SetMinimum(0.1)
   Data.Draw("e")
   stack.Draw("histsame")
   errorBand.Draw("e2same")
   Data.Draw("esame")
   signal.Draw("histsame")

   legende=make_legend()
   legende.AddEntry(Data,"Observed","elp")
   legende.AddEntry(DY,"Z#rightarrow#tau#tau/ee/#mu#mu","f")
   legende.AddEntry(TT,"t#bar{t}","f")
   legende.AddEntry(W,"W+jets","f")
   legende.AddEntry(QCD,"QCD","f")
   legende.AddEntry(VV,"Others","f")
   legende.AddEntry(errorBand,"Stat. unc.","f")
   legende.AddEntry(signal,"H#rightarrow#tau#tau (x50)","l")
   legende.Draw()

   l1=add_lumi()
   l1.Draw("same")
   l2=add_CMS()
   l2.Draw("same")
   l3=add_Preliminary()
   #l3.Draw("same")
 
   pad1.RedrawAxis()

   c.cd()
   pad2 = ROOT.TPad("pad2","pad2",0,0,1,0.35);
   pad2.SetTopMargin(0.05);
   pad2.SetBottomMargin(0.35);
   pad2.SetLeftMargin(0.18);
   pad2.SetRightMargin(0.05);
   pad2.SetTickx(1)
   pad2.SetTicky(1)
   pad2.SetFrameLineWidth(3)
   pad2.SetGridx()
   pad2.SetGridy()
   pad2.Draw()
   pad2.cd()
   h1=Data.Clone()
   h1.SetMaximum(1.3)#FIXME(1.5)
   h1.SetMinimum(0.7)#FIXME(0.5)
   h1.SetMarkerStyle(20)
   h3=errorBand.Clone()
   hwoE=errorBand.Clone()
   for iii in range (1,hwoE.GetSize()-2):
     hwoE.SetBinError(iii,0)
   h3.Sumw2()
   h1.Sumw2()
   h1.SetStats(0)
   h1.Divide(hwoE)
   h3.Divide(hwoE)
   h1.GetXaxis().SetTitle(label[i])
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
   c.SaveAs("control_em/"+name[i]+"_embedded.pdf")
   c.SaveAs("control_em/"+name[i]+"_embedded.png")

