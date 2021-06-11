if __name__ == "__main__":

    import ROOT
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('--scale', default="nominal", help="Which TES?")
    parser.add_argument('--directory', default="nominal")
    parser.add_argument('--shape', default="nominal")
    options = parser.parse_args()

    nbhist=1
    nbhist=47
    postfix=["","_CMS_rawFF_mt_qcd_0jet_unc1Up","_CMS_rawFF_mt_qcd_0jet_unc2Up","_CMS_rawFF_mt_qcd_0jet_unc1Down","_CMS_rawFF_mt_qcd_0jet_unc2Down","_CMS_rawFF_mt_qcd_1jet_unc1Up","_CMS_rawFF_mt_qcd_1jet_unc2Up","_CMS_rawFF_mt_qcd_1jet_unc1Down","_CMS_rawFF_mt_qcd_1jet_unc2Down","_CMS_rawFF_mt_qcd_2jet_unc1Up","_CMS_rawFF_mt_qcd_2jet_unc2Up","_CMS_rawFF_mt_qcd_2jet_unc1Down","_CMS_rawFF_mt_qcd_2jet_unc2Down","_CMS_rawFF_mt_w_0jet_unc1Up","_CMS_rawFF_mt_w_0jet_unc2Up","_CMS_rawFF_mt_w_0jet_unc1Down","_CMS_rawFF_mt_w_0jet_unc2Down","_CMS_rawFF_mt_w_1jet_unc1Up","_CMS_rawFF_mt_w_1jet_unc2Up","_CMS_rawFF_mt_w_1jet_unc1Down","_CMS_rawFF_mt_w_1jet_unc2Down","_CMS_rawFF_mt_w_2jet_unc1Up","_CMS_rawFF_mt_w_2jet_unc2Up","_CMS_rawFF_mt_w_2jet_unc1Down","_CMS_rawFF_mt_w_2jet_unc2Down","_CMS_rawFF_mt_tt_unc1Up","_CMS_rawFF_mt_tt_unc2Up","_CMS_rawFF_mt_tt_unc1Down","_CMS_rawFF_mt_tt_unc2Down","_CMS_FF_closure_lpt_mt_qcdUp","_CMS_FF_closure_lpt_mt_qcdDown","_CMS_FF_closure_lpt_xtrg_mt_qcdUp","_CMS_FF_closure_lpt_xtrg_mt_qcdDown","_CMS_FF_closure_lpt_mt_wUp","_CMS_FF_closure_lpt_mt_wDown","_CMS_FF_closure_lpt_xtrg_mt_wUp","_CMS_FF_closure_lpt_xtrg_mt_wDown","_CMS_FF_closure_lpt_mt_ttUp","_CMS_FF_closure_lpt_mt_ttDown","_CMS_FF_closure_lpt_xtrg_mt_ttUp","_CMS_FF_closure_lpt_xtrg_mt_ttDown","_CMS_FF_closure_OSSS_mvis_mt_qcdUp","_CMS_FF_closure_OSSS_mvis_mt_qcdDown","_CMS_FF_closure_mt_mt_w_unc1Up","_CMS_FF_closure_mt_mt_w_unc1Down","_CMS_FF_closure_mt_mt_w_unc2Up","_CMS_FF_closure_mt_mt_w_unc2Down"]
    postfix_out=["","_CMS_rawFF_mt_qcd_0jet_unc1Up","_CMS_rawFF_mt_qcd_0jet_unc2Up","_CMS_rawFF_mt_qcd_0jet_unc1Down","_CMS_rawFF_mt_qcd_0jet_unc2Down","_CMS_rawFF_mt_qcd_1jet_unc1Up","_CMS_rawFF_mt_qcd_1jet_unc2Up","_CMS_rawFF_mt_qcd_1jet_unc1Down","_CMS_rawFF_mt_qcd_1jet_unc2Down","_CMS_rawFF_mt_qcd_2jet_unc1Up","_CMS_rawFF_mt_qcd_2jet_unc2Up","_CMS_rawFF_mt_qcd_2jet_unc1Down","_CMS_rawFF_mt_qcd_2jet_unc2Down","_CMS_rawFF_mt_w_0jet_unc1Up","_CMS_rawFF_mt_w_0jet_unc2Up","_CMS_rawFF_mt_w_0jet_unc1Down","_CMS_rawFF_mt_w_0jet_unc2Down","_CMS_rawFF_mt_w_1jet_unc1Up","_CMS_rawFF_mt_w_1jet_unc2Up","_CMS_rawFF_mt_w_1jet_unc1Down","_CMS_rawFF_mt_w_1jet_unc2Down","_CMS_rawFF_mt_w_2jet_unc1Up","_CMS_rawFF_mt_w_2jet_unc2Up","_CMS_rawFF_mt_w_2jet_unc1Down","_CMS_rawFF_mt_w_2jet_unc2Down","_CMS_rawFF_mt_tt_unc1Up","_CMS_rawFF_mt_tt_unc2Up","_CMS_rawFF_mt_tt_unc1Down","_CMS_rawFF_mt_tt_unc2Down","_CMS_FF_closure_lpt_mt_qcdUp","_CMS_FF_closure_lpt_mt_qcdDown","_CMS_FF_closure_lpt_xtrg_mt_qcdUp","_CMS_FF_closure_lpt_xtrg_mt_qcdDown","_CMS_FF_closure_lpt_mt_wUp","_CMS_FF_closure_lpt_mt_wDown","_CMS_FF_closure_lpt_xtrg_mt_wUp","_CMS_FF_closure_lpt_xtrg_mt_wDown","_CMS_FF_closure_lpt_mt_ttUp","_CMS_FF_closure_lpt_mt_ttDown","_CMS_FF_closure_lpt_xtrg_mt_ttUp","_CMS_FF_closure_lpt_xtrg_mt_ttDown","_CMS_FF_closure_OSSS_mvis_mt_qcdUp","_CMS_FF_closure_OSSS_mvis_mt_qcdDown","_CMS_FF_closure_mt_mt_w_unc1Up","_CMS_FF_closure_mt_mt_w_unc1Down","_CMS_FF_closure_mt_mt_w_unc2Up","_CMS_FF_closure_mt_mt_w_unc2Down"]

    fout=ROOT.TFile("files_"+options.directory+"_mt/Fake.root","recreate")

    factorT=1.0
    factorL=1.0

    fData=ROOT.TFile("files_"+options.directory+"_mt/Data.root","r")
    fDY=ROOT.TFile("files_"+options.directory+"_mt/DY.root","r")
    fEmbedded=ROOT.TFile("files_"+options.directory+"_mt/embedded.root","r")
    fTT=ROOT.TFile("files_"+options.directory+"_mt/TT.root","r")
    fVV=ROOT.TFile("files_"+options.directory+"_mt/VV.root","r")

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
      print k
      h_0jet.append(fData.Get("AI0jet/reweighted_data_obs"+postfix[k]))
      h_boosted.append(fData.Get("AIboosted/reweighted_data_obs"+postfix[k]))
      h_vbf.append(fData.Get("AIvbf/reweighted_data_obs"+postfix[k]))
      h_0jetlow.append(fData.Get("AI0jetlow/reweighted_data_obs"+postfix[k]))
      h_0jethigh.append(fData.Get("AI0jethigh/reweighted_data_obs"+postfix[k]))
      h_boosted1.append(fData.Get("AIboosted1/reweighted_data_obs"+postfix[k]))
      h_boosted2.append(fData.Get("AIboosted2/reweighted_data_obs"+postfix[k]))
      h_vbflow.append(fData.Get("AIvbflow/reweighted_data_obs"+postfix[k]))
      h_vbfhigh.append(fData.Get("AIvbfhigh/reweighted_data_obs"+postfix[k]))

      print "AI0jet/reweighted_data_obs"+postfix[k]

      h_0jetDYT.append(fEmbedded.Get("AI0jet/reweighted_data_obs"+postfix[k]))
      h_boostedDYT.append(fEmbedded.Get("AIboosted/reweighted_data_obs"+postfix[k]))
      h_vbfDYT.append(fEmbedded.Get("AIvbf/reweighted_data_obs"+postfix[k]))
      h_0jetlowDYT.append(fEmbedded.Get("AI0jetlow/reweighted_data_obs"+postfix[k]))
      h_0jethighDYT.append(fEmbedded.Get("AI0jethigh/reweighted_data_obs"+postfix[k]))
      h_boosted1DYT.append(fEmbedded.Get("AIboosted1/reweighted_data_obs"+postfix[k]))
      h_boosted2DYT.append(fEmbedded.Get("AIboosted2/reweighted_data_obs"+postfix[k]))
      h_vbflowDYT.append(fEmbedded.Get("AIvbflow/reweighted_data_obs"+postfix[k]))
      h_vbfhighDYT.append(fEmbedded.Get("AIvbfhigh/reweighted_data_obs"+postfix[k]))

      h_0jetDYT[k].Add(fVV.Get("AI0jet/VVT"+postfix[k]))
      h_boostedDYT[k].Add(fVV.Get("AIboosted/VVT"+postfix[k]))
      h_vbfDYT[k].Add(fVV.Get("AIvbf/VVT"+postfix[k]))
      h_0jetlowDYT[k].Add(fVV.Get("AI0jetlow/VVT"+postfix[k]))
      h_0jethighDYT[k].Add(fVV.Get("AI0jethigh/VVT"+postfix[k]))
      h_boosted1DYT[k].Add(fVV.Get("AIboosted1/VVT"+postfix[k]))
      h_boosted2DYT[k].Add(fVV.Get("AIboosted2/VVT"+postfix[k]))
      h_vbflowDYT[k].Add(fVV.Get("AIvbflow/VVT"+postfix[k]))
      h_vbfhighDYT[k].Add(fVV.Get("AIvbfhigh/VVT"+postfix[k]))

      h_0jetDYT[k].Add(fTT.Get("AI0jet/TTT"+postfix[k]))
      h_boostedDYT[k].Add(fTT.Get("AIboosted/TTT"+postfix[k]))
      h_vbfDYT[k].Add(fTT.Get("AIvbf/TTT"+postfix[k]))
      h_0jetlowDYT[k].Add(fTT.Get("AI0jetlow/TTT"+postfix[k]))
      h_0jethighDYT[k].Add(fTT.Get("AI0jethigh/TTT"+postfix[k]))
      h_boosted1DYT[k].Add(fTT.Get("AIboosted1/TTT"+postfix[k]))
      h_boosted2DYT[k].Add(fTT.Get("AIboosted2/TTT"+postfix[k]))
      h_vbflowDYT[k].Add(fTT.Get("AIvbflow/TTT"+postfix[k]))
      h_vbfhighDYT[k].Add(fTT.Get("AIvbfhigh/TTT"+postfix[k]))

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
    dir0jet=fout.mkdir("mt_0jet")
    dir0jet.cd()
    for k in range(0,nbhist):
      #print postfix[k]
      print h_0jet[k].Integral(),h_0jetDYT[k].Integral(),h_0jetDYL[k].Integral()
      h_0jet[k].Add(h_0jetDYT[k],-factorT)
      h_0jet[k].Add(h_0jetDYL[k],-factorL)
      #h_0jet[k].Scale(h_0jet[0].Integral(-1,-1,-1,-1)/h_0jet[k].Integral(-1,-1,-1,-1))
      h_0jet[k].SetName("jetFakes"+postfix_out[k])
      h_0jet[k].Write()

    dir1jet=fout.mkdir("mt_boosted")
    dir1jet.cd()
    for k in range(0,nbhist):
      h_boosted[k].Add(h_boostedDYT[k],-factorT)
      h_boosted[k].Add(h_boostedDYL[k],-factorL)
      #h_boosted[k].Scale(h_boosted[0].Integral(-1,-1,-1,-1)/h_boosted[k].Integral(-1,-1,-1,-1))
      h_boosted[k].SetName("jetFakes"+postfix_out[k])
      h_boosted[k].Write()

    dir2jet=fout.mkdir("mt_vbf")
    dir2jet.cd()
    for k in range(0,nbhist):
      h_vbf[k].Add(h_vbfDYT[k],-factorT)
      h_vbf[k].Add(h_vbfDYL[k],-factorL)
      #h_vbf[k].Scale(h_vbf[0].Integral(-1,-1,-1,-1)/h_vbf[k].Integral(-1,-1,-1,-1))
      h_vbf[k].SetName("jetFakes"+postfix_out[k])
      h_vbf[k].Write()

    dir3jet=fout.mkdir("mt_0jet_PTH_0_10")
    dir3jet.cd()
    for k in range(0,nbhist):
      h_0jetlow[k].Add(h_0jetlowDYT[k],-factorT)
      h_0jetlow[k].Add(h_0jetlowDYL[k],-factorL)
      h_0jetlow[k].SetName("jetFakes"+postfix_out[k])
      print "0jet low ",postfix[k],h_0jetlow[k].Integral()
      print "DYT ",h_0jetlowDYT[k].Integral()
      print "DYL ",h_0jetlowDYL[k].Integral()
      #h_0jetlow[k].Scale(0.96) #FIXME!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      h_0jetlow[k].Write()

    dir4jet=fout.mkdir("mt_0jet_PTH_GE10")
    dir4jet.cd()
    for k in range(0,nbhist):
      h_0jethigh[k].Add(h_0jethighDYT[k],-factorT)
      h_0jethigh[k].Add(h_0jethighDYL[k],-factorL)
      #h_0jethigh[k].Scale(h_0jethigh[0].Integral(-1,-1,-1,-1)/h_0jethigh[k].Integral(-1,-1,-1,-1))
      h_0jethigh[k].SetName("jetFakes"+postfix_out[k])
      print "0jet high ",postfix[k],h_0jethigh[k].Integral()
      #h_0jethigh[k].Scale(1.04)
      h_0jethigh[k].Write()

    dir5jet=fout.mkdir("mt_boosted_1J")
    dir5jet.cd()
    for k in range(0,nbhist):
      h_boosted1[k].Add(h_boosted1DYT[k],-factorT)
      h_boosted1[k].Add(h_boosted1DYL[k],-factorL)
      #h_boosted1[k].Scale(h_boosted1[0].Integral(-1,-1,-1,-1)/h_boosted1[k].Integral(-1,-1,-1,-1))
      h_boosted1[k].SetName("jetFakes"+postfix_out[k])
      print "Boosted1 ",postfix[k],h_boosted1[k].Integral()
      h_boosted1[k].Write()

    dir6jet=fout.mkdir("mt_boosted_GE2J")
    dir6jet.cd()
    for k in range(0,nbhist):
      h_boosted2[k].Add(h_boosted2DYT[k],-factorT)
      h_boosted2[k].Add(h_boosted2DYL[k],-factorL)
      #h_boosted2[k].Scale(h_boosted2[0].Integral(-1,-1,-1,-1)/h_boosted2[k].Integral(-1,-1,-1,-1))
      h_boosted2[k].SetName("jetFakes"+postfix_out[k])
      print "Boosted2 ",postfix[k],h_boosted2[k].Integral()
      h_boosted2[k].Write()

    dir7jet=fout.mkdir("mt_vbf_PTH_0_200")
    dir7jet.cd()
    for k in range(0,nbhist):
      h_vbflow[k].Add(h_vbflowDYT[k],-factorT)
      h_vbflow[k].Add(h_vbflowDYL[k],-factorL)
      #h_vbflow[k].Scale(h_vbflow[0].Integral(-1,-1,-1,-1)/h_vbflow[k].Integral(-1,-1,-1,-1))
      h_vbflow[k].SetName("jetFakes"+postfix_out[k])
      print "VBF low ",postfix[k],h_vbflow[k].Integral()
      h_vbflow[k].Write()

    dir8jet=fout.mkdir("mt_vbf_PTH_GE_200")
    dir8jet.cd()
    for k in range(0,nbhist):
      h_vbfhigh[k].Add(h_vbfhighDYT[k],-factorT)
      h_vbfhigh[k].Add(h_vbfhighDYL[k],-factorL)
      #h_vbfhigh[k].Scale(h_vbfhigh[0].Integral(-1,-1,-1,-1)/h_vbfhigh[k].Integral(-1,-1,-1,-1))
      h_vbfhigh[k].SetName("jetFakes"+postfix_out[k])
      print "VBF high ",postfix[k],h_vbfhigh[k].Integral()
      h_vbfhigh[k].Write()
