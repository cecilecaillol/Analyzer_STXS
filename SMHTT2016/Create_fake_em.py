if __name__ == "__main__":

    import ROOT
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('--scale', default="nominal", choices=['nominal', 'up', 'down', 'wup', 'wdown','qcdup','qcddown','JESup','JESdown'], help="Which TES?")
    options = parser.parse_args()

    #nbhist=1
    nbhist=15
    postfix=["","_CMS_QCD_njet0_intercept_2016Down","_CMS_QCD_njet0_intercept_2016Up","_CMS_QCD_njet0_slope_2016Down","_CMS_QCD_njet0_slope_2016Up","_CMS_QCD_njet1_intercept_2016Down","_CMS_QCD_njet1_intercept_2016Up","_CMS_QCD_njet1_slope_2016Down","_CMS_QCD_njet1_slope_2016Up","_CMS_QCD_njet2_intercept_2016Down","_CMS_QCD_njet2_intercept_2016Up","_CMS_QCD_njet2_slope_2016Down","_CMS_QCD_njet2_slope_2016Up","_CMS_QCD_antiiso_2016Down","_CMS_QCD_antiiso_2016Up"]

    fData=ROOT.TFile("files_nominal_em/Data.root","r")
    fDY=ROOT.TFile("files_nominal_em/DY.root","r")
    fTT=ROOT.TFile("files_nominal_em/TT.root","r")
    fW=ROOT.TFile("files_nominal_em/W.root","r")
    fVV=ROOT.TFile("files_nominal_em/VV.root","r")
    fout=ROOT.TFile("files_nominal_em/Fake.root","recreate")

    h_0jet=[]
    h_boosted=[]
    h_vbf=[]
    h_0jetlow=[]
    h_0jethigh=[]
    h_boosted1=[]
    h_boosted2=[]
    h_vbflow=[]
    h_vbfhigh=[]

    h_0jetZL=[]
    h_boostedZL=[]
    h_vbfZL=[]
    h_0jetlowZL=[]
    h_0jethighZL=[]
    h_boosted1ZL=[]
    h_boosted2ZL=[]
    h_vbflowZL=[]
    h_vbfhighZL=[]

    h_0jetZTT=[]
    h_boostedZTT=[]
    h_vbfZTT=[]
    h_0jetlowZTT=[]
    h_0jethighZTT=[]
    h_boosted1ZTT=[]
    h_boosted2ZTT=[]
    h_vbflowZTT=[]
    h_vbfhighZTT=[]

    hAI_0jet=[]
    hAI_boosted=[]
    hAI_vbf=[]
    hAI_0jetlow=[]
    hAI_0jethigh=[]
    hAI_boosted1=[]
    hAI_boosted2=[]
    hAI_vbflow=[]
    hAI_vbfhigh=[]

    hAI_0jetZL=[]
    hAI_boostedZL=[]
    hAI_vbfZL=[]
    hAI_0jetlowZL=[]
    hAI_0jethighZL=[]
    hAI_boosted1ZL=[]
    hAI_boosted2ZL=[]
    hAI_vbflowZL=[]
    hAI_vbfhighZL=[]

    hAI_0jetZTT=[]
    hAI_boostedZTT=[]
    hAI_vbfZTT=[]
    hAI_0jetlowZTT=[]
    hAI_0jethighZTT=[]
    hAI_boosted1ZTT=[]
    hAI_boosted2ZTT=[]
    hAI_vbflowZTT=[]
    hAI_vbfhighZTT=[]

    for k in range(0,nbhist):
      h_0jet.append(fData.Get("SS0jet/data_obs"+postfix[k]))
      h_boosted.append(fData.Get("SSboosted/data_obs"+postfix[k]))
      h_vbf.append(fData.Get("SSvbf/data_obs"+postfix[k]))
      h_0jetlow.append(fData.Get("SS0jetlow/data_obs"+postfix[k]))
      h_0jethigh.append(fData.Get("SS0jethigh/data_obs"+postfix[k]))
      h_boosted1.append(fData.Get("SSboosted1/data_obs"+postfix[k]))
      h_boosted2.append(fData.Get("SSboosted2/data_obs"+postfix[k]))
      h_vbflow.append(fData.Get("SSvbflow/data_obs"+postfix[k]))
      h_vbfhigh.append(fData.Get("SSvbfhigh/data_obs"+postfix[k]))

      hAI_0jet.append(fData.Get("AI0jet/data_obs"+postfix[k]))
      hAI_boosted.append(fData.Get("AIboosted/data_obs"+postfix[k]))
      hAI_vbf.append(fData.Get("AIvbf/data_obs"+postfix[k]))
      hAI_0jetlow.append(fData.Get("AI0jetlow/data_obs"+postfix[k]))
      hAI_0jethigh.append(fData.Get("AI0jethigh/data_obs"+postfix[k]))
      hAI_boosted1.append(fData.Get("AIboosted1/data_obs"+postfix[k]))
      hAI_boosted2.append(fData.Get("AIboosted2/data_obs"+postfix[k]))
      hAI_vbflow.append(fData.Get("AIvbflow/data_obs"+postfix[k]))
      hAI_vbfhigh.append(fData.Get("AIvbfhigh/data_obs"+postfix[k]))

      h_0jetZTT.append(fDY.Get("SS0jet/ZT"+postfix[k]))
      h_boostedZTT.append(fDY.Get("SSboosted/ZT"+postfix[k]))
      h_vbfZTT.append(fDY.Get("SSvbf/ZT"+postfix[k]))
      h_0jetlowZTT.append(fDY.Get("SS0jetlow/ZT"+postfix[k]))
      h_0jethighZTT.append(fDY.Get("SS0jethigh/ZT"+postfix[k]))
      h_boosted1ZTT.append(fDY.Get("SSboosted1/ZT"+postfix[k]))
      h_boosted2ZTT.append(fDY.Get("SSboosted2/ZT"+postfix[k]))
      h_vbflowZTT.append(fDY.Get("SSvbflow/ZT"+postfix[k]))
      h_vbfhighZTT.append(fDY.Get("SSvbfhigh/ZT"+postfix[k]))

      hAI_0jetZTT.append(fDY.Get("AI0jet/ZT"+postfix[k]))
      hAI_boostedZTT.append(fDY.Get("AIboosted/ZT"+postfix[k]))
      hAI_vbfZTT.append(fDY.Get("AIvbf/ZT"+postfix[k]))
      hAI_0jetlowZTT.append(fDY.Get("AI0jetlow/ZT"+postfix[k]))
      hAI_0jethighZTT.append(fDY.Get("AI0jethigh/ZT"+postfix[k]))
      hAI_boosted1ZTT.append(fDY.Get("AIboosted1/ZT"+postfix[k]))
      hAI_boosted2ZTT.append(fDY.Get("AIboosted2/ZT"+postfix[k]))
      hAI_vbflowZTT.append(fDY.Get("AIvbflow/ZT"+postfix[k]))
      hAI_vbfhighZTT.append(fDY.Get("AIvbfhigh/ZT"+postfix[k]))

      h_0jetZTT[k].Add(fTT.Get("SS0jet/TTT"+postfix[k]))
      h_boostedZTT[k].Add(fTT.Get("SSboosted/TTT"+postfix[k]))
      h_vbfZTT[k].Add(fTT.Get("SSvbf/TTT"+postfix[k]))
      h_0jetlowZTT[k].Add(fTT.Get("SS0jetlow/TTT"+postfix[k]))
      h_0jethighZTT[k].Add(fTT.Get("SS0jethigh/TTT"+postfix[k]))
      h_boosted1ZTT[k].Add(fTT.Get("SSboosted1/TTT"+postfix[k]))
      h_boosted2ZTT[k].Add(fTT.Get("SSboosted2/TTT"+postfix[k]))
      h_vbflowZTT[k].Add(fTT.Get("SSvbflow/TTT"+postfix[k]))
      h_vbfhighZTT[k].Add(fTT.Get("SSvbfhigh/TTT"+postfix[k]))

      hAI_0jetZTT[k].Add(fTT.Get("AI0jet/TTT"+postfix[k]))
      hAI_boostedZTT[k].Add(fTT.Get("AIboosted/TTT"+postfix[k]))
      hAI_vbfZTT[k].Add(fTT.Get("AIvbf/TTT"+postfix[k]))
      hAI_0jetlowZTT[k].Add(fTT.Get("AI0jetlow/TTT"+postfix[k]))
      hAI_0jethighZTT[k].Add(fTT.Get("AI0jethigh/TTT"+postfix[k]))
      hAI_boosted1ZTT[k].Add(fTT.Get("AIboosted1/TTT"+postfix[k]))
      hAI_boosted2ZTT[k].Add(fTT.Get("AIboosted2/TTT"+postfix[k]))
      hAI_vbflowZTT[k].Add(fTT.Get("AIvbflow/TTT"+postfix[k]))
      hAI_vbfhighZTT[k].Add(fTT.Get("AIvbfhigh/TTT"+postfix[k]))

      h_0jetZTT[k].Add(fVV.Get("SS0jet/STT"+postfix[k]))
      h_boostedZTT[k].Add(fVV.Get("SSboosted/STT"+postfix[k]))
      h_vbfZTT[k].Add(fVV.Get("SSvbf/STT"+postfix[k]))
      h_0jetlowZTT[k].Add(fVV.Get("SS0jetlow/STT"+postfix[k]))
      h_0jethighZTT[k].Add(fVV.Get("SS0jethigh/STT"+postfix[k]))
      h_boosted1ZTT[k].Add(fVV.Get("SSboosted1/STT"+postfix[k]))
      h_boosted2ZTT[k].Add(fVV.Get("SSboosted2/STT"+postfix[k]))
      h_vbflowZTT[k].Add(fVV.Get("SSvbflow/STT"+postfix[k]))
      h_vbfhighZTT[k].Add(fVV.Get("SSvbfhigh/STT"+postfix[k]))

      hAI_0jetZTT[k].Add(fVV.Get("AI0jet/STT"+postfix[k]))
      hAI_boostedZTT[k].Add(fVV.Get("AIboosted/STT"+postfix[k]))
      hAI_vbfZTT[k].Add(fVV.Get("AIvbf/STT"+postfix[k]))
      hAI_0jetlowZTT[k].Add(fVV.Get("AI0jetlow/STT"+postfix[k]))
      hAI_0jethighZTT[k].Add(fVV.Get("AI0jethigh/STT"+postfix[k]))
      hAI_boosted1ZTT[k].Add(fVV.Get("AIboosted1/STT"+postfix[k]))
      hAI_boosted2ZTT[k].Add(fVV.Get("AIboosted2/STT"+postfix[k]))
      hAI_vbflowZTT[k].Add(fVV.Get("AIvbflow/STT"+postfix[k]))
      hAI_vbfhighZTT[k].Add(fVV.Get("AIvbfhigh/STT"+postfix[k]))

      h_0jetZTT[k].Add(fVV.Get("SS0jet/VVT"+postfix[k]))
      h_boostedZTT[k].Add(fVV.Get("SSboosted/VVT"+postfix[k]))
      h_vbfZTT[k].Add(fVV.Get("SSvbf/VVT"+postfix[k]))
      h_0jetlowZTT[k].Add(fVV.Get("SS0jetlow/VVT"+postfix[k]))
      h_0jethighZTT[k].Add(fVV.Get("SS0jethigh/VVT"+postfix[k]))
      h_boosted1ZTT[k].Add(fVV.Get("SSboosted1/VVT"+postfix[k]))
      h_boosted2ZTT[k].Add(fVV.Get("SSboosted2/VVT"+postfix[k]))
      h_vbflowZTT[k].Add(fVV.Get("SSvbflow/VVT"+postfix[k]))
      h_vbfhighZTT[k].Add(fVV.Get("SSvbfhigh/VVT"+postfix[k]))

      hAI_0jetZTT[k].Add(fVV.Get("AI0jet/VVT"+postfix[k]))
      hAI_boostedZTT[k].Add(fVV.Get("AIboosted/VVT"+postfix[k]))
      hAI_vbfZTT[k].Add(fVV.Get("AIvbf/VVT"+postfix[k]))
      hAI_0jetlowZTT[k].Add(fVV.Get("AI0jetlow/VVT"+postfix[k]))
      hAI_0jethighZTT[k].Add(fVV.Get("AI0jethigh/VVT"+postfix[k]))
      hAI_boosted1ZTT[k].Add(fVV.Get("AIboosted1/VVT"+postfix[k]))
      hAI_boosted2ZTT[k].Add(fVV.Get("AIboosted2/VVT"+postfix[k]))
      hAI_vbflowZTT[k].Add(fVV.Get("AIvbflow/VVT"+postfix[k]))
      hAI_vbfhighZTT[k].Add(fVV.Get("AIvbfhigh/VVT"+postfix[k]))

      h_0jetZL.append(fDY.Get("SS0jet/ZL"+postfix[k]))
      h_boostedZL.append(fDY.Get("SSboosted/ZL"+postfix[k]))
      h_vbfZL.append(fDY.Get("SSvbf/ZL"+postfix[k]))
      h_0jetlowZL.append(fDY.Get("SS0jetlow/ZL"+postfix[k]))
      h_0jethighZL.append(fDY.Get("SS0jethigh/ZL"+postfix[k]))
      h_boosted1ZL.append(fDY.Get("SSboosted1/ZL"+postfix[k]))
      h_boosted2ZL.append(fDY.Get("SSboosted2/ZL"+postfix[k]))
      h_vbflowZL.append(fDY.Get("SSvbflow/ZL"+postfix[k]))
      h_vbfhighZL.append(fDY.Get("SSvbfhigh/ZL"+postfix[k]))

      hAI_0jetZL.append(fDY.Get("AI0jet/ZL"+postfix[k]))
      hAI_boostedZL.append(fDY.Get("AIboosted/ZL"+postfix[k]))
      hAI_vbfZL.append(fDY.Get("AIvbf/ZL"+postfix[k]))
      hAI_0jetlowZL.append(fDY.Get("AI0jetlow/ZL"+postfix[k]))
      hAI_0jethighZL.append(fDY.Get("AI0jethigh/ZL"+postfix[k]))
      hAI_boosted1ZL.append(fDY.Get("AIboosted1/ZL"+postfix[k]))
      hAI_boosted2ZL.append(fDY.Get("AIboosted2/ZL"+postfix[k]))
      hAI_vbflowZL.append(fDY.Get("AIvbflow/ZL"+postfix[k]))
      hAI_vbfhighZL.append(fDY.Get("AIvbfhigh/ZL"+postfix[k]))

      h_0jetZL[k].Add(fTT.Get("SS0jet/TTL"+postfix[k]))
      h_boostedZL[k].Add(fTT.Get("SSboosted/TTL"+postfix[k]))
      h_vbfZL[k].Add(fTT.Get("SSvbf/TTL"+postfix[k]))
      h_0jetlowZL[k].Add(fTT.Get("SS0jetlow/TTL"+postfix[k]))
      h_0jethighZL[k].Add(fTT.Get("SS0jethigh/TTL"+postfix[k]))
      h_boosted1ZL[k].Add(fTT.Get("SSboosted1/TTL"+postfix[k]))
      h_boosted2ZL[k].Add(fTT.Get("SSboosted2/TTL"+postfix[k]))
      h_vbflowZL[k].Add(fTT.Get("SSvbflow/TTL"+postfix[k]))
      h_vbfhighZL[k].Add(fTT.Get("SSvbfhigh/TTL"+postfix[k]))

      hAI_0jetZL[k].Add(fTT.Get("AI0jet/TTL"+postfix[k]))
      hAI_boostedZL[k].Add(fTT.Get("AIboosted/TTL"+postfix[k]))
      hAI_vbfZL[k].Add(fTT.Get("AIvbf/TTL"+postfix[k]))
      hAI_0jetlowZL[k].Add(fTT.Get("AI0jetlow/TTL"+postfix[k]))
      hAI_0jethighZL[k].Add(fTT.Get("AI0jethigh/TTL"+postfix[k]))
      hAI_boosted1ZL[k].Add(fTT.Get("AIboosted1/TTL"+postfix[k]))
      hAI_boosted2ZL[k].Add(fTT.Get("AIboosted2/TTL"+postfix[k]))
      hAI_vbflowZL[k].Add(fTT.Get("AIvbflow/TTL"+postfix[k]))
      hAI_vbfhighZL[k].Add(fTT.Get("AIvbfhigh/TTL"+postfix[k]))

      h_0jetZL[k].Add(fVV.Get("SS0jet/STL"+postfix[k]))
      h_boostedZL[k].Add(fVV.Get("SSboosted/STL"+postfix[k]))
      h_vbfZL[k].Add(fVV.Get("SSvbf/STL"+postfix[k]))
      h_0jetlowZL[k].Add(fVV.Get("SS0jetlow/STL"+postfix[k]))
      h_0jethighZL[k].Add(fVV.Get("SS0jethigh/STL"+postfix[k]))
      h_boosted1ZL[k].Add(fVV.Get("SSboosted1/STL"+postfix[k]))
      h_boosted2ZL[k].Add(fVV.Get("SSboosted2/STL"+postfix[k]))
      h_vbflowZL[k].Add(fVV.Get("SSvbflow/STL"+postfix[k]))
      h_vbfhighZL[k].Add(fVV.Get("SSvbfhigh/STL"+postfix[k]))

      hAI_0jetZL[k].Add(fVV.Get("AI0jet/STL"+postfix[k]))
      hAI_boostedZL[k].Add(fVV.Get("AIboosted/STL"+postfix[k]))
      hAI_vbfZL[k].Add(fVV.Get("AIvbf/STL"+postfix[k]))
      hAI_0jetlowZL[k].Add(fVV.Get("AI0jetlow/STL"+postfix[k]))
      hAI_0jethighZL[k].Add(fVV.Get("AI0jethigh/STL"+postfix[k]))
      hAI_boosted1ZL[k].Add(fVV.Get("AIboosted1/STL"+postfix[k]))
      hAI_boosted2ZL[k].Add(fVV.Get("AIboosted2/STL"+postfix[k]))
      hAI_vbflowZL[k].Add(fVV.Get("AIvbflow/STL"+postfix[k]))
      hAI_vbfhighZL[k].Add(fVV.Get("AIvbfhigh/STL"+postfix[k]))

      h_0jetZL[k].Add(fW.Get("SS0jet/W"+postfix[k]))
      h_boostedZL[k].Add(fW.Get("SSboosted/W"+postfix[k]))
      h_vbfZL[k].Add(fW.Get("SSvbf/W"+postfix[k]))
      h_0jetlowZL[k].Add(fW.Get("SS0jetlow/W"+postfix[k]))
      h_0jethighZL[k].Add(fW.Get("SS0jethigh/W"+postfix[k]))
      h_boosted1ZL[k].Add(fW.Get("SSboosted1/W"+postfix[k]))
      h_boosted2ZL[k].Add(fW.Get("SSboosted2/W"+postfix[k]))
      h_vbflowZL[k].Add(fW.Get("SSvbflow/W"+postfix[k]))
      h_vbfhighZL[k].Add(fW.Get("SSvbfhigh/W"+postfix[k]))

      hAI_0jetZL[k].Add(fW.Get("AI0jet/W"+postfix[k]))
      hAI_boostedZL[k].Add(fW.Get("AIboosted/W"+postfix[k]))
      hAI_vbfZL[k].Add(fW.Get("AIvbf/W"+postfix[k]))
      hAI_0jetlowZL[k].Add(fW.Get("AI0jetlow/W"+postfix[k]))
      hAI_0jethighZL[k].Add(fW.Get("AI0jethigh/W"+postfix[k]))
      hAI_boosted1ZL[k].Add(fW.Get("AIboosted1/W"+postfix[k]))
      hAI_boosted2ZL[k].Add(fW.Get("AIboosted2/W"+postfix[k]))
      hAI_vbflowZL[k].Add(fW.Get("AIvbflow/W"+postfix[k]))
      hAI_vbfhighZL[k].Add(fW.Get("AIvbfhigh/W"+postfix[k]))

      h_0jetZL[k].Add(fVV.Get("SS0jet/VVL"+postfix[k]))
      h_boostedZL[k].Add(fVV.Get("SSboosted/VVL"+postfix[k]))
      h_vbfZL[k].Add(fVV.Get("SSvbf/VVL"+postfix[k]))
      h_0jetlowZL[k].Add(fVV.Get("SS0jetlow/VVL"+postfix[k]))
      h_0jethighZL[k].Add(fVV.Get("SS0jethigh/VVL"+postfix[k]))
      h_boosted1ZL[k].Add(fVV.Get("SSboosted1/VVL"+postfix[k]))
      h_boosted2ZL[k].Add(fVV.Get("SSboosted2/VVL"+postfix[k]))
      h_vbflowZL[k].Add(fVV.Get("SSvbflow/VVL"+postfix[k]))
      h_vbfhighZL[k].Add(fVV.Get("SSvbfhigh/VVL"+postfix[k]))

      hAI_0jetZL[k].Add(fVV.Get("AI0jet/VVL"+postfix[k]))
      hAI_boostedZL[k].Add(fVV.Get("AIboosted/VVL"+postfix[k]))
      hAI_vbfZL[k].Add(fVV.Get("AIvbf/VVL"+postfix[k]))
      hAI_0jetlowZL[k].Add(fVV.Get("AI0jetlow/VVL"+postfix[k]))
      hAI_0jethighZL[k].Add(fVV.Get("AI0jethigh/VVL"+postfix[k]))
      hAI_boosted1ZL[k].Add(fVV.Get("AIboosted1/VVL"+postfix[k]))
      hAI_boosted2ZL[k].Add(fVV.Get("AIboosted2/VVL"+postfix[k]))
      hAI_vbflowZL[k].Add(fVV.Get("AIvbflow/VVL"+postfix[k]))
      hAI_vbfhighZL[k].Add(fVV.Get("AIvbfhigh/VVL"+postfix[k]))

    fout.cd()
    dir0jet=fout.mkdir("em_0jet")
    dir0jet.cd()
    for k in range(0,nbhist):
      h_0jet[k].Add(h_0jetZTT[k],-1)
      h_0jet[k].Add(h_0jetZL[k],-1)
      hAI_0jet[k].Add(hAI_0jetZTT[k],-1)
      hAI_0jet[k].Add(hAI_0jetZL[k],-1)
      hAI_0jet[k].Scale(h_0jet[k].Integral()/hAI_0jet[k].Integral())
      for l in range(0,hAI_0jet[k].GetSize()):
	if (hAI_0jet[k].GetBinContent(l+1)<0):
	   hAI_0jet[k].SetBinContent(l+1,0)
      hAI_0jet[k].SetName("QCD"+postfix[k])
      hAI_0jet[k].Write()

    dir1jet=fout.mkdir("em_boosted")
    dir1jet.cd()
    for k in range(0,nbhist):
      h_boosted[k].Add(h_boostedZTT[k],-1)
      h_boosted[k].Add(h_boostedZL[k],-1)
      hAI_boosted[k].Add(hAI_boostedZTT[k],-1)
      hAI_boosted[k].Add(hAI_boostedZL[k],-1)
      hAI_boosted[k].Scale(h_boosted[k].Integral()/hAI_boosted[k].Integral())
      for l in range(0,hAI_boosted[k].GetSize()):
        if (hAI_boosted[k].GetBinContent(l+1)<0):
           hAI_boosted[k].SetBinContent(l+1,0)
      hAI_boosted[k].SetName("QCD"+postfix[k])
      hAI_boosted[k].Write()


    dir2jet=fout.mkdir("em_vbf")
    dir2jet.cd()
    for k in range(0,nbhist):
      h_vbf[k].Add(h_vbfZTT[k],-1)
      h_vbf[k].Add(h_vbfZL[k],-1)
      hAI_vbf[k].Add(hAI_vbfZTT[k],-1)
      hAI_vbf[k].Add(hAI_vbfZL[k],-1)
      hAI_vbf[k].Scale(h_vbf[k].Integral()/hAI_vbf[k].Integral())
      for l in range(0,hAI_vbf[k].GetSize()):
        if (hAI_vbf[k].GetBinContent(l+1)<0):
           hAI_vbf[k].SetBinContent(l+1,0)
      hAI_vbf[k].SetName("QCD"+postfix[k])
      hAI_vbf[k].Write()


    dir3jet=fout.mkdir("em_0jetlow")
    dir3jet.cd()
    for k in range(0,nbhist):
      h_0jetlow[k].Add(h_0jetlowZTT[k],-1)
      h_0jetlow[k].Add(h_0jetlowZL[k],-1)
      hAI_0jetlow[k].Add(hAI_0jetlowZTT[k],-1)
      hAI_0jetlow[k].Add(hAI_0jetlowZL[k],-1)
      hAI_0jetlow[k].Scale(h_0jetlow[k].Integral()/hAI_0jetlow[k].Integral())
      for l in range(0,hAI_0jetlow[k].GetSize()):
        if (hAI_0jetlow[k].GetBinContent(l+1)<0):
           hAI_0jetlow[k].SetBinContent(l+1,0)
      hAI_0jetlow[k].SetName("QCD"+postfix[k])
      hAI_0jetlow[k].Write()

    dir4jet=fout.mkdir("em_0jethigh")
    dir4jet.cd()
    for k in range(0,nbhist):
      h_0jethigh[k].Add(h_0jethighZTT[k],-1)
      h_0jethigh[k].Add(h_0jethighZL[k],-1)
      hAI_0jethigh[k].Add(hAI_0jethighZTT[k],-1)
      hAI_0jethigh[k].Add(hAI_0jethighZL[k],-1)
      hAI_0jethigh[k].Scale(h_0jethigh[k].Integral()/hAI_0jethigh[k].Integral())
      for l in range(0,hAI_0jethigh[k].GetSize()):
        if (hAI_0jethigh[k].GetBinContent(l+1)<0):
           hAI_0jethigh[k].SetBinContent(l+1,0)
      hAI_0jethigh[k].SetName("QCD"+postfix[k])
      hAI_0jethigh[k].Write()

    dir5jet=fout.mkdir("em_boosted1")
    dir5jet.cd()
    for k in range(0,nbhist):
      h_boosted1[k].Add(h_boosted1ZTT[k],-1)
      h_boosted1[k].Add(h_boosted1ZL[k],-1)
      hAI_boosted1[k].Add(hAI_boosted1ZTT[k],-1)
      hAI_boosted1[k].Add(hAI_boosted1ZL[k],-1)
      hAI_boosted1[k].Scale(h_boosted1[k].Integral()/hAI_boosted1[k].Integral())
      for l in range(0,hAI_boosted1[k].GetSize()):
        if (hAI_boosted1[k].GetBinContent(l+1)<0):
           hAI_boosted1[k].SetBinContent(l+1,0)
      hAI_boosted1[k].SetName("QCD"+postfix[k])
      hAI_boosted1[k].Write()

    dir6jet=fout.mkdir("em_boosted2")
    dir6jet.cd()
    for k in range(0,nbhist):
      h_boosted2[k].Add(h_boosted2ZTT[k],-1)
      h_boosted2[k].Add(h_boosted2ZL[k],-1)
      hAI_boosted2[k].Add(hAI_boosted2ZTT[k],-1)
      hAI_boosted2[k].Add(hAI_boosted2ZL[k],-1)
      hAI_boosted2[k].Scale(h_boosted2[k].Integral()/hAI_boosted2[k].Integral())
      for l in range(0,hAI_boosted2[k].GetSize()):
        if (hAI_boosted2[k].GetBinContent(l+1)<0):
           hAI_boosted2[k].SetBinContent(l+1,0)
      hAI_boosted2[k].SetName("QCD"+postfix[k])
      hAI_boosted2[k].Write()

    dir7jet=fout.mkdir("em_vbflow")
    dir7jet.cd()
    for k in range(0,nbhist):
      h_vbflow[k].Add(h_vbflowZTT[k],-1)
      h_vbflow[k].Add(h_vbflowZL[k],-1)
      hAI_vbflow[k].Add(hAI_vbflowZTT[k],-1)
      hAI_vbflow[k].Add(hAI_vbflowZL[k],-1)
      hAI_vbflow[k].Scale(h_vbflow[k].Integral()/hAI_vbflow[k].Integral())
      for l in range(0,hAI_vbflow[k].GetSize()):
        if (hAI_vbflow[k].GetBinContent(l+1)<0):
           hAI_vbflow[k].SetBinContent(l+1,0)
      hAI_vbflow[k].SetName("QCD"+postfix[k])
      hAI_vbflow[k].Write()

    dir8jet=fout.mkdir("em_vbfhigh")
    dir8jet.cd()
    for k in range(0,nbhist):
      h_vbfhigh[k].Add(h_vbfhighZTT[k],-1)
      h_vbfhigh[k].Add(h_vbfhighZL[k],-1)
      hAI_vbfhigh[k].Add(hAI_vbfhighZTT[k],-1)
      hAI_vbfhigh[k].Add(hAI_vbfhighZL[k],-1)
      print h_vbfhigh[k].Integral(),hAI_vbfhigh[k].Integral()
      hAI_vbfhigh[k].Scale(h_vbfhigh[k].Integral()/hAI_vbfhigh[k].Integral())
      for l in range(0,hAI_vbfhigh[k].GetSize()):
        if (hAI_vbfhigh[k].GetBinContent(l+1)<0):
           hAI_vbfhigh[k].SetBinContent(l+1,0)
      hAI_vbfhigh[k].SetName("QCD"+postfix[k])
      hAI_vbfhigh[k].Write()


