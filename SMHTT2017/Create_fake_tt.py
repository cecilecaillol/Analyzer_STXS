if __name__ == "__main__":

    import ROOT
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('--scale', default="nominal", choices=['nominal', 'up', 'down', 'wup', 'wdown','qcdup','qcddown','JESup','JESdown'], help="Which TES?")
    options = parser.parse_args()

    #nbhist=1
    nbhist=15
    postfix=["","_CMS_ff_qcd_tt_systUp","_CMS_ff_qcd_tt_systDown","_CMS_ff_qcd_njet0_tt_statUp","_CMS_ff_qcd_njet0_tt_statDown","_CMS_ff_qcd_njet1_tt_statUp","_CMS_ff_qcd_njet1_tt_statDown","_CMS_ff_w_tt_systUp","_CMS_ff_w_tt_systDown","_CMS_ff_tt_tt_systUp","_CMS_ff_tt_tt_systDown","_CMS_ff_w_frac_tt_systUp","_CMS_ff_w_frac_tt_systDown","_CMS_ff_tt_frac_tt_systUp","_CMS_ff_tt_frac_tt_systDown"]

    fData=ROOT.TFile("files_nominal_tt/Data.root","r")
    fDY=ROOT.TFile("files_nominal_tt/DY.root","r")
    fout=ROOT.TFile("files_nominal_tt/Fake.root","recreate")

    h_0jet=[]
    h_boosted=[]
    h_vbf=[]
    h_1jet=[]
    h_gg2jets=[]
    h_vh2jets=[]
    h_vbf2=[]

    h_0jetZTT=[]
    h_boostedZTT=[]
    h_vbfZTT=[]
    h_1jetZTT=[]
    h_gg2jetsZTT=[]
    h_vh2jetsZTT=[]
    h_vbf2ZTT=[]

    for k in range(0,nbhist):
      h_0jet.append(fData.Get("AI0jet/reweighted_data_obs"+postfix[k]))
      h_boosted.append(fData.Get("AIboosted/reweighted_data_obs"+postfix[k]))
      h_vbf.append(fData.Get("AIvbf/reweighted_data_obs"+postfix[k]))
      h_1jet.append(fData.Get("AI1jet/reweighted_data_obs"+postfix[k]))
      h_gg2jets.append(fData.Get("AIgg2jets/reweighted_data_obs"+postfix[k]))
      h_vh2jets.append(fData.Get("AIvh2jets/reweighted_data_obs"+postfix[k]))
      h_vbf2.append(fData.Get("AIvbf2/reweighted_data_obs"+postfix[k]))

      h_0jetZTT.append(fDY.Get("AI0jet/ZTT"+postfix[k]))
      h_boostedZTT.append(fDY.Get("AIboosted/ZTT"+postfix[k]))
      h_vbfZTT.append(fDY.Get("AIvbf/ZTT"+postfix[k]))
      h_1jetZTT.append(fDY.Get("AI1jet/ZTT"+postfix[k]))
      h_gg2jetsZTT.append(fDY.Get("AIgg2jets/ZTT"+postfix[k]))
      h_vh2jetsZTT.append(fDY.Get("AIvh2jets/ZTT"+postfix[k]))
      h_vbf2ZTT.append(fDY.Get("AIvbf2/ZTT"+postfix[k]))

    fout.cd()
    dir0jet=fout.mkdir("tt_0jet")
    dir0jet.cd()
    for k in range(0,nbhist):
      h_0jet[k].Add(h_0jetZTT[0],-1)
      h_0jet[k].Scale(h_0jet[0].Integral(-1,-1,-1,-1)/h_0jet[k].Integral(-1,-1,-1,-1))
      h_0jet[k].SetName("jetFakes"+postfix[k])
      h_0jet[k].Write()

    dir1jet=fout.mkdir("tt_boosted")
    dir1jet.cd()
    for k in range(0,nbhist):
      h_boosted[k].Add(h_boostedZTT[0],-1)
      h_boosted[k].Scale(h_boosted[0].Integral(-1,-1,-1,-1)/h_boosted[k].Integral(-1,-1,-1,-1))
      h_boosted[k].SetName("jetFakes"+postfix[k])
      h_boosted[k].Write()

    dir2jet=fout.mkdir("tt_vbf")
    dir2jet.cd()
    for k in range(0,nbhist):
      h_vbf[k].Add(h_vbfZTT[0],-1)
      h_vbf[k].Scale(h_vbf[0].Integral(-1,-1,-1,-1)/h_vbf[k].Integral(-1,-1,-1,-1))
      h_vbf[k].SetName("jetFakes"+postfix[k])
      h_vbf[k].Write()

    dir3jet=fout.mkdir("tt_1jet")
    dir3jet.cd()
    for k in range(0,nbhist):
      h_1jet[k].Add(h_1jetZTT[0],-1)
      h_1jet[k].Scale(h_1jet[0].Integral(-1,-1)/h_1jet[k].Integral(-1,-1))
      h_1jet[k].SetName("jetFakes"+postfix[k])
      h_1jet[k].Write()

    dir4jet=fout.mkdir("tt_gg2jets")
    dir4jet.cd()
    for k in range(0,nbhist):
      h_gg2jets[k].Add(h_gg2jetsZTT[0],-1)
      h_gg2jets[k].Scale(h_gg2jets[0].Integral(-1,-1)/h_gg2jets[k].Integral(-1,-1))
      h_gg2jets[k].SetName("jetFakes"+postfix[k])
      h_gg2jets[k].Write()

    dir5jet=fout.mkdir("tt_vh2jets")
    dir5jet.cd()
    for k in range(0,nbhist):
      h_vh2jets[k].Add(h_vh2jetsZTT[0],-1)
      h_vh2jets[k].Scale(h_vh2jets[0].Integral(-1,-1)/h_vh2jets[k].Integral(-1,-1))
      h_vh2jets[k].SetName("jetFakes"+postfix[k])
      h_vh2jets[k].Write()

    dir6jet=fout.mkdir("tt_vbf2")
    dir6jet.cd()
    for k in range(0,nbhist):
      h_vbf2[k].Add(h_vbf2ZTT[0],-1)
      h_vbf2[k].Scale(h_vbf2[0].Integral(-1,-1)/h_vbf2[k].Integral(-1,-1))
      h_vbf2[k].SetName("jetFakes"+postfix[k])
      h_vbf2[k].Write()

