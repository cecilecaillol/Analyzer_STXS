if __name__ == "__main__":

    import ROOT
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('--scale', default="nominal", choices=['nominal', 'up', 'down', 'wup', 'wdown','qcdup','qcddown','JESup','JESdown'], help="Which TES?")
    options = parser.parse_args()

    nbhist=1
    #nbhist=19
    #postfix=["","_CMS_ff_qcd_et_syst_2016Up","_CMS_ff_qcd_et_syst_2016Down","_CMS_ff_qcd_njet0_et_stat_2016Up","_CMS_ff_qcd_njet0_et_stat_2016Down","_CMS_ff_qcd_njet1_et_stat_2016Up","_CMS_ff_qcd_njet1_et_stat_2016Down","_CMS_ff_w_et_syst_2016Up","_CMS_ff_w_et_syst_2016Down","_CMS_ff_w_njet0_et_stat_2016Up","_CMS_ff_w_njet0_et_stat_2016Down","_CMS_ff_w_njet1_et_stat_2016Up","_CMS_ff_w_njet1_et_stat_2016Down","_CMS_ff_tt_et_syst_2016Up","_CMS_ff_tt_et_syst_2016Down","_CMS_ff_tt_njet0_et_stat_2016Up","_CMS_ff_tt_njet0_et_stat_2016Down","_CMS_ff_tt_njet1_et_stat_2016Up","_CMS_ff_tt_njet1_et_stat_2016Down"]

    nbhist=47
    postfix=["","_CMS_rawFF_et_qcd_0jet_unc1_2016Up","_CMS_rawFF_et_qcd_0jet_unc2_2016Up","_CMS_rawFF_et_qcd_0jet_unc1_2016Down","_CMS_rawFF_et_qcd_0jet_unc2_2016Down","_CMS_rawFF_et_qcd_1jet_unc1_2016Up","_CMS_rawFF_et_qcd_1jet_unc2_2016Up","_CMS_rawFF_et_qcd_1jet_unc1_2016Down","_CMS_rawFF_et_qcd_1jet_unc2_2016Down","_CMS_rawFF_et_qcd_2jet_unc1_2016Up","_CMS_rawFF_et_qcd_2jet_unc2_2016Up","_CMS_rawFF_et_qcd_2jet_unc1_2016Down","_CMS_rawFF_et_qcd_2jet_unc2_2016Down","_CMS_rawFF_et_w_0jet_unc1_2016Up","_CMS_rawFF_et_w_0jet_unc2_2016Up","_CMS_rawFF_et_w_0jet_unc1_2016Down","_CMS_rawFF_et_w_0jet_unc2_2016Down","_CMS_rawFF_et_w_1jet_unc1_2016Up","_CMS_rawFF_et_w_1jet_unc2_2016Up","_CMS_rawFF_et_w_1jet_unc1_2016Down","_CMS_rawFF_et_w_1jet_unc2_2016Down","_CMS_rawFF_et_w_2jet_unc1_2016Up","_CMS_rawFF_et_w_2jet_unc2_2016Up","_CMS_rawFF_et_w_2jet_unc1_2016Down","_CMS_rawFF_et_w_2jet_unc2_2016Down","_CMS_rawFF_et_tt_unc1_2016Up","_CMS_rawFF_et_tt_unc2_2016Up","_CMS_rawFF_et_tt_unc1_2016Down","_CMS_rawFF_et_tt_unc2_2016Down","_CMS_FF_closure_lpt_et_qcd_2016Up","_CMS_FF_closure_lpt_et_qcd_2016Down","_CMS_FF_closure_lpt_xtrg_et_qcd_2016Up","_CMS_FF_closure_lpt_xtrg_et_qcd_2016Down","_CMS_FF_closure_lpt_et_w_2016Up","_CMS_FF_closure_lpt_et_w_2016Down","_CMS_FF_closure_lpt_xtrg_et_w_2016Up","_CMS_FF_closure_lpt_xtrg_et_w_2016Down","_CMS_FF_closure_lpt_et_tt_2016Up","_CMS_FF_closure_lpt_et_tt_2016Down","_CMS_FF_closure_lpt_xtrg_et_tt_2016Up","_CMS_FF_closure_lpt_xtrg_et_tt_2016Down","_CMS_FF_closure_OSSS_mvis_et_qcd_2016Up","_CMS_FF_closure_OSSS_mvis_et_qcd_2016Down","_CMS_FF_closure_mt_et_w_unc1_2016Up","_CMS_FF_closure_mt_et_w_unc1_2016Down","_CMS_FF_closure_mt_et_w_unc2_2016Up","_CMS_FF_closure_mt_et_w_unc2_2016Down"]

    fData=ROOT.TFile("files_nominal_et/Data.root","r")
    fDY=ROOT.TFile("files_nominal_et/DY.root","r")
    fTT=ROOT.TFile("files_nominal_et/TT.root","r")
    fVV=ROOT.TFile("files_nominal_et/VV.root","r")
    fout=ROOT.TFile("files_nominal_et/Fake.root","recreate")

    h_0jet=[]
    h_boosted=[]
    h_vbf=[]
    h_0jetlow=[]
    h_0jethigh=[]
    h_boosted1=[]
    h_boosted2=[]
    h_vbflow=[]
    h_vbfhigh=[]

    h_0jetDYL=[]
    h_boostedDYL=[]
    h_vbfDYL=[]
    h_0jetlowDYL=[]
    h_0jethighDYL=[]
    h_boosted1DYL=[]
    h_boosted2DYL=[]
    h_vbflowDYL=[]
    h_vbfhighDYL=[]

    h_0jetDYT=[]
    h_boostedDYT=[]
    h_vbfDYT=[]
    h_0jetlowDYT=[]
    h_0jethighDYT=[]
    h_boosted1DYT=[]
    h_boosted2DYT=[]
    h_vbflowDYT=[]
    h_vbfhighDYT=[]

    for k in range(0,nbhist):
      h_0jet.append(fData.Get("AI0jet/reweighted_data_obs"+postfix[k]))
      h_boosted.append(fData.Get("AIboosted/reweighted_data_obs"+postfix[k]))
      h_vbf.append(fData.Get("AIvbf/reweighted_data_obs"+postfix[k]))
      h_0jetlow.append(fData.Get("AI0jetlow/reweighted_data_obs"+postfix[k]))
      h_0jethigh.append(fData.Get("AI0jethigh/reweighted_data_obs"+postfix[k]))
      h_boosted1.append(fData.Get("AIboosted1/reweighted_data_obs"+postfix[k]))
      h_boosted2.append(fData.Get("AIboosted2/reweighted_data_obs"+postfix[k]))
      h_vbflow.append(fData.Get("AIvbflow/reweighted_data_obs"+postfix[k]))
      h_vbfhigh.append(fData.Get("AIvbfhigh/reweighted_data_obs"+postfix[k]))

      h_0jetDYT.append(fDY.Get("AI0jet/ZT"+postfix[k]))
      h_boostedDYT.append(fDY.Get("AIboosted/ZT"+postfix[k]))
      h_vbfDYT.append(fDY.Get("AIvbf/ZT"+postfix[k]))
      h_0jetlowDYT.append(fDY.Get("AI0jetlow/ZT"+postfix[k]))
      h_0jethighDYT.append(fDY.Get("AI0jethigh/ZT"+postfix[k]))
      h_boosted1DYT.append(fDY.Get("AIboosted1/ZT"+postfix[k]))
      h_boosted2DYT.append(fDY.Get("AIboosted2/ZT"+postfix[k]))
      h_vbflowDYT.append(fDY.Get("AIvbflow/ZT"+postfix[k]))
      h_vbfhighDYT.append(fDY.Get("AIvbfhigh/ZT"+postfix[k]))

      print postfix[k]

      h_0jetDYT[k].Add(fTT.Get("AI0jet/TTT"+postfix[k]))
      h_boostedDYT[k].Add(fTT.Get("AIboosted/TTT"+postfix[k]))
      h_vbfDYT[k].Add(fTT.Get("AIvbf/TTT"+postfix[k]))
      h_0jetlowDYT[k].Add(fTT.Get("AI0jetlow/TTT"+postfix[k]))
      h_0jethighDYT[k].Add(fTT.Get("AI0jethigh/TTT"+postfix[k]))
      h_boosted1DYT[k].Add(fTT.Get("AIboosted1/TTT"+postfix[k]))
      h_boosted2DYT[k].Add(fTT.Get("AIboosted2/TTT"+postfix[k]))
      h_vbflowDYT[k].Add(fTT.Get("AIvbflow/TTT"+postfix[k]))
      h_vbfhighDYT[k].Add(fTT.Get("AIvbfhigh/TTT"+postfix[k]))

      h_0jetDYT[k].Add(fVV.Get("AI0jet/VVT"+postfix[k]))
      h_boostedDYT[k].Add(fVV.Get("AIboosted/VVT"+postfix[k]))
      h_vbfDYT[k].Add(fVV.Get("AIvbf/VVT"+postfix[k]))
      h_0jetlowDYT[k].Add(fVV.Get("AI0jetlow/VVT"+postfix[k]))
      h_0jethighDYT[k].Add(fVV.Get("AI0jethigh/VVT"+postfix[k]))
      h_boosted1DYT[k].Add(fVV.Get("AIboosted1/VVT"+postfix[k]))
      h_boosted2DYT[k].Add(fVV.Get("AIboosted2/VVT"+postfix[k]))
      h_vbflowDYT[k].Add(fVV.Get("AIvbflow/VVT"+postfix[k]))
      h_vbfhighDYT[k].Add(fVV.Get("AIvbfhigh/VVT"+postfix[k]))

      h_0jetDYT[k].Add(fVV.Get("AI0jet/STT"+postfix[k]))
      h_boostedDYT[k].Add(fVV.Get("AIboosted/STT"+postfix[k]))
      h_vbfDYT[k].Add(fVV.Get("AIvbf/STT"+postfix[k]))
      h_0jetlowDYT[k].Add(fVV.Get("AI0jetlow/STT"+postfix[k]))
      h_0jethighDYT[k].Add(fVV.Get("AI0jethigh/STT"+postfix[k]))
      h_boosted1DYT[k].Add(fVV.Get("AIboosted1/STT"+postfix[k]))
      h_boosted2DYT[k].Add(fVV.Get("AIboosted2/STT"+postfix[k]))
      h_vbflowDYT[k].Add(fVV.Get("AIvbflow/STT"+postfix[k]))
      h_vbfhighDYT[k].Add(fVV.Get("AIvbfhigh/STT"+postfix[k]))

      h_0jetDYL.append(fDY.Get("AI0jet/ZL"+postfix[k]))
      h_boostedDYL.append(fDY.Get("AIboosted/ZL"+postfix[k]))
      h_vbfDYL.append(fDY.Get("AIvbf/ZL"+postfix[k]))
      h_0jetlowDYL.append(fDY.Get("AI0jetlow/ZL"+postfix[k]))
      h_0jethighDYL.append(fDY.Get("AI0jethigh/ZL"+postfix[k]))
      h_boosted1DYL.append(fDY.Get("AIboosted1/ZL"+postfix[k]))
      h_boosted2DYL.append(fDY.Get("AIboosted2/ZL"+postfix[k]))
      h_vbflowDYL.append(fDY.Get("AIvbflow/ZL"+postfix[k]))
      h_vbfhighDYL.append(fDY.Get("AIvbfhigh/ZL"+postfix[k]))

      h_0jetDYL[k].Add(fTT.Get("AI0jet/TTL"+postfix[k]))
      h_boostedDYL[k].Add(fTT.Get("AIboosted/TTL"+postfix[k]))
      h_vbfDYL[k].Add(fTT.Get("AIvbf/TTL"+postfix[k]))
      h_0jetlowDYL[k].Add(fTT.Get("AI0jetlow/TTL"+postfix[k]))
      h_0jethighDYL[k].Add(fTT.Get("AI0jethigh/TTL"+postfix[k]))
      h_boosted1DYL[k].Add(fTT.Get("AIboosted1/TTL"+postfix[k]))
      h_boosted2DYL[k].Add(fTT.Get("AIboosted2/TTL"+postfix[k]))
      h_vbflowDYL[k].Add(fTT.Get("AIvbflow/TTL"+postfix[k]))
      h_vbfhighDYL[k].Add(fTT.Get("AIvbfhigh/TTL"+postfix[k]))

      h_0jetDYL[k].Add(fVV.Get("AI0jet/VVL"+postfix[k]))
      h_boostedDYL[k].Add(fVV.Get("AIboosted/VVL"+postfix[k]))
      h_vbfDYL[k].Add(fVV.Get("AIvbf/VVL"+postfix[k]))
      h_0jetlowDYL[k].Add(fVV.Get("AI0jetlow/VVL"+postfix[k]))
      h_0jethighDYL[k].Add(fVV.Get("AI0jethigh/VVL"+postfix[k]))
      h_boosted1DYL[k].Add(fVV.Get("AIboosted1/VVL"+postfix[k]))
      h_boosted2DYL[k].Add(fVV.Get("AIboosted2/VVL"+postfix[k]))
      h_vbflowDYL[k].Add(fVV.Get("AIvbflow/VVL"+postfix[k]))
      h_vbfhighDYL[k].Add(fVV.Get("AIvbfhigh/VVL"+postfix[k]))

      h_0jetDYL[k].Add(fVV.Get("AI0jet/STL"+postfix[k]))
      h_boostedDYL[k].Add(fVV.Get("AIboosted/STL"+postfix[k]))
      h_vbfDYL[k].Add(fVV.Get("AIvbf/STL"+postfix[k]))
      h_0jetlowDYL[k].Add(fVV.Get("AI0jetlow/STL"+postfix[k]))
      h_0jethighDYL[k].Add(fVV.Get("AI0jethigh/STL"+postfix[k]))
      h_boosted1DYL[k].Add(fVV.Get("AIboosted1/STL"+postfix[k]))
      h_boosted2DYL[k].Add(fVV.Get("AIboosted2/STL"+postfix[k]))
      h_vbflowDYL[k].Add(fVV.Get("AIvbflow/STL"+postfix[k]))
      h_vbfhighDYL[k].Add(fVV.Get("AIvbfhigh/STL"+postfix[k]))

    fout.cd()
    dir0jet=fout.mkdir("et_0jet")
    dir0jet.cd()
    for k in range(0,nbhist):
      #print postfix[k]
      h_0jet[k].Add(h_0jetDYT[k],-1)
      h_0jet[k].Add(h_0jetDYL[k],-1)
      #h_0jet[k].Scale(h_0jet[0].Integral(-1,-1,-1,-1)/h_0jet[k].Integral(-1,-1,-1,-1))
      h_0jet[k].SetName("jetFakes"+postfix[k])
      print h_0jet[k].Integral()
      h_0jet[k].Write()

    dir1jet=fout.mkdir("et_boosted")
    dir1jet.cd()
    for k in range(0,nbhist):
      h_boosted[k].Add(h_boostedDYT[k],-1)
      h_boosted[k].Add(h_boostedDYL[k],-1)
      #h_boosted[k].Scale(h_boosted[0].Integral(-1,-1,-1,-1)/h_boosted[k].Integral(-1,-1,-1,-1))
      h_boosted[k].SetName("jetFakes"+postfix[k])
      print h_boosted[k].Integral()
      h_boosted[k].Write()

    dir2jet=fout.mkdir("et_vbf")
    dir2jet.cd()
    for k in range(0,nbhist):
      h_vbf[k].Add(h_vbfDYT[k],-1)
      h_vbf[k].Add(h_vbfDYL[k],-1)
      #h_vbf[k].Scale(h_vbf[0].Integral(-1,-1,-1,-1)/h_vbf[k].Integral(-1,-1,-1,-1))
      h_vbf[k].SetName("jetFakes"+postfix[k])
      print h_vbf[k].Integral()
      h_vbf[k].Write()

    dir3jet=fout.mkdir("et_0jetlow")
    dir3jet.cd()
    for k in range(0,nbhist):
      h_0jetlow[k].Add(h_0jetlowDYT[k],-1)
      h_0jetlow[k].Add(h_0jetlowDYL[k],-1)
      #h_0jetlow[k].Scale(h_0jetlow[0].Integral(-1,-1,-1,-1)/h_0jetlow[k].Integral(-1,-1,-1,-1))
      h_0jetlow[k].SetName("jetFakes"+postfix[k])
      print h_0jetlow[k].Integral()
      h_0jetlow[k].Write()

    dir4jet=fout.mkdir("et_0jethigh")
    dir4jet.cd()
    for k in range(0,nbhist):
      h_0jethigh[k].Add(h_0jethighDYT[k],-1)
      h_0jethigh[k].Add(h_0jethighDYL[k],-1)
      #h_0jethigh[k].Scale(h_0jethigh[0].Integral(-1,-1,-1,-1)/h_0jethigh[k].Integral(-1,-1,-1,-1))
      h_0jethigh[k].SetName("jetFakes"+postfix[k])
      h_0jethigh[k].Write()

    dir5jet=fout.mkdir("et_boosted1")
    dir5jet.cd()
    for k in range(0,nbhist):
      h_boosted1[k].Add(h_boosted1DYT[k],-1)
      h_boosted1[k].Add(h_boosted1DYL[k],-1)
      #h_boosted1[k].Scale(h_boosted1[0].Integral(-1,-1,-1,-1)/h_boosted1[k].Integral(-1,-1,-1,-1))
      h_boosted1[k].SetName("jetFakes"+postfix[k])
      h_boosted1[k].Write()

    dir6jet=fout.mkdir("et_boosted2")
    dir6jet.cd()
    for k in range(0,nbhist):
      h_boosted2[k].Add(h_boosted2DYT[k],-1)
      h_boosted2[k].Add(h_boosted2DYL[k],-1)
      #h_boosted2[k].Scale(h_boosted2[0].Integral(-1,-1,-1,-1)/h_boosted2[k].Integral(-1,-1,-1,-1))
      h_boosted2[k].SetName("jetFakes"+postfix[k])
      h_boosted2[k].Write()

    dir7jet=fout.mkdir("et_vbflow")
    dir7jet.cd()
    for k in range(0,nbhist):
      h_vbflow[k].Add(h_vbflowDYT[k],-1)
      h_vbflow[k].Add(h_vbflowDYL[k],-1)
      #h_vbflow[k].Scale(h_vbflow[0].Integral(-1,-1,-1,-1)/h_vbflow[k].Integral(-1,-1,-1,-1))
      h_vbflow[k].SetName("jetFakes"+postfix[k])
      h_vbflow[k].Write()

    dir8jet=fout.mkdir("et_vbfhigh")
    dir8jet.cd()
    for k in range(0,nbhist):
      h_vbfhigh[k].Add(h_vbfhighDYT[k],-1)
      h_vbfhigh[k].Add(h_vbfhighDYL[k],-1)
      #h_vbfhigh[k].Scale(h_vbfhigh[0].Integral(-1,-1,-1,-1)/h_vbfhigh[k].Integral(-1,-1,-1,-1))
      h_vbfhigh[k].SetName("jetFakes"+postfix[k])
      h_vbfhigh[k].Write()

