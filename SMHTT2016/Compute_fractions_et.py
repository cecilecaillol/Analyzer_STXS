if __name__ == "__main__":

    import ROOT
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('--scale', default="nominal", choices=['nominal', 'up', 'down', 'wup', 'wdown','qcdup','qcddown','JESup','JESdown'], help="Which TES?")
    options = parser.parse_args()

    fDY=ROOT.TFile("files_nominal_et/DY.root","r")
    fEmbedded=ROOT.TFile("files_nominal_et/embedded.root","r")
    fW=ROOT.TFile("files_nominal_et/W.root","r")
    fTT=ROOT.TFile("files_nominal_et/TT.root","r")
    fVV=ROOT.TFile("files_nominal_et/VV.root","r")
    fData=ROOT.TFile("files_nominal_et/Data.root","r")
    fout=ROOT.TFile("files_nominal_et/fractions.root","recreate")

    h_0jet_w=fW.Get("f0jet")
    h_0jet_w.Add(fDY.Get("f0jet"))
    h_0jet_w.Add(fVV.Get("f0jet"))
    h_0jet_tt=fTT.Get("f0jet")
    h_0jet_data=fData.Get("f0real")
    h_0jet_real=fDY.Get("f0real")
    h_0jet_real.Add(fEmbedded.Get("f0real"))
    h_0jet_real.Add(fTT.Get("f0real"))
    h_0jet_real.Add(fVV.Get("f0real"))
    h_0jet_qcd=h_0jet_data.Clone()
    h_0jet_qcd.Add(h_0jet_real,-1)
    h_0jet_qcd.Add(h_0jet_tt,-1)
    h_0jet_qcd.Add(h_0jet_w,-1)
    h_0jet_w.SetName("frac_w_0jet")
    h_0jet_qcd.SetName("frac_qcd_0jet")
    h_0jet_tt.SetName("frac_tt_0jet")
    h_0jet_data.SetName("frac_data_0jet")

    h_boosted_w=fW.Get("f1jet")
    h_boosted_w.Add(fDY.Get("f1jet"))
    h_boosted_w.Add(fVV.Get("f1jet"))
    h_boosted_tt=fTT.Get("f1jet")
    h_boosted_data=fData.Get("f1real")
    h_boosted_real=fDY.Get("f1real")
    h_boosted_real.Add(fEmbedded.Get("f1real"))
    h_boosted_real.Add(fTT.Get("f1real"))
    h_boosted_real.Add(fVV.Get("f1real"))
    h_boosted_qcd=h_boosted_data.Clone()
    h_boosted_qcd.Add(h_boosted_real,-1)
    h_boosted_qcd.Add(h_boosted_tt,-1)
    h_boosted_qcd.Add(h_boosted_w,-1)
    h_boosted_w.SetName("frac_w_boosted")
    h_boosted_qcd.SetName("frac_qcd_boosted")
    h_boosted_tt.SetName("frac_tt_boosted")
    h_boosted_data.SetName("frac_data_boosted")

    h_vbf_w=fW.Get("f2jet")
    h_vbf_w.Add(fDY.Get("f2jet"))
    h_vbf_w.Add(fVV.Get("f2jet"))
    h_vbf_tt=fTT.Get("f2jet")
    h_vbf_data=fData.Get("f2real")
    h_vbf_real=fDY.Get("f2real")
    h_vbf_real.Add(fEmbedded.Get("f2real"))
    h_vbf_real.Add(fTT.Get("f2real"))
    h_vbf_real.Add(fVV.Get("f2real"))
    h_vbf_qcd=h_vbf_data.Clone()
    h_vbf_qcd.Add(h_vbf_real,-1)
    h_vbf_qcd.Add(h_vbf_tt,-1)
    h_vbf_qcd.Add(h_vbf_w,-1)
    h_vbf_w.SetName("frac_w_vbf")
    h_vbf_qcd.SetName("frac_qcd_vbf")
    h_vbf_tt.SetName("frac_tt_vbf")
    h_vbf_data.SetName("frac_data_vbf")

    h_0jetlow_w=fW.Get("f3jet")
    h_0jetlow_w.Add(fDY.Get("f3jet"))
    h_0jetlow_w.Add(fVV.Get("f3jet"))
    h_0jetlow_tt=fTT.Get("f3jet")
    h_0jetlow_data=fData.Get("f3real")
    h_0jetlow_real=fDY.Get("f3real")
    h_0jetlow_real.Add(fEmbedded.Get("f3real"))
    h_0jetlow_real.Add(fTT.Get("f3real"))
    h_0jetlow_real.Add(fVV.Get("f3real"))
    h_0jetlow_qcd=h_0jetlow_data.Clone()
    h_0jetlow_qcd.Add(h_0jetlow_real,-1)
    h_0jetlow_qcd.Add(h_0jetlow_tt,-1)
    h_0jetlow_qcd.Add(h_0jetlow_w,-1)
    h_0jetlow_w.SetName("frac_w_0jetlow")
    h_0jetlow_qcd.SetName("frac_qcd_0jetlow")
    h_0jetlow_tt.SetName("frac_tt_0jetlow")
    h_0jetlow_data.SetName("frac_data_0jetlow")

    h_0jethigh_w=fW.Get("f4jet")
    h_0jethigh_w.Add(fDY.Get("f4jet"))
    h_0jethigh_w.Add(fVV.Get("f4jet"))
    h_0jethigh_tt=fTT.Get("f4jet")
    h_0jethigh_data=fData.Get("f4real")
    h_0jethigh_real=fDY.Get("f4real")
    h_0jethigh_real.Add(fEmbedded.Get("f4real"))
    h_0jethigh_real.Add(fTT.Get("f4real"))
    h_0jethigh_real.Add(fVV.Get("f4real"))
    h_0jethigh_qcd=h_0jethigh_data.Clone()
    h_0jethigh_qcd.Add(h_0jethigh_real,-1)
    h_0jethigh_qcd.Add(h_0jethigh_tt,-1)
    h_0jethigh_qcd.Add(h_0jethigh_w,-1)
    h_0jethigh_w.SetName("frac_w_0jethigh")
    h_0jethigh_qcd.SetName("frac_qcd_0jethigh")
    h_0jethigh_tt.SetName("frac_tt_0jethigh")
    h_0jethigh_data.SetName("frac_data_0jethigh")

    h_boosted1_w=fW.Get("f5jet")
    h_boosted1_w.Add(fDY.Get("f5jet"))
    h_boosted1_w.Add(fVV.Get("f5jet"))
    h_boosted1_tt=fTT.Get("f5jet")
    h_boosted1_data=fData.Get("f5real")
    h_boosted1_real=fDY.Get("f5real")
    h_boosted1_real.Add(fEmbedded.Get("f5real"))
    h_boosted1_real.Add(fTT.Get("f5real"))
    h_boosted1_real.Add(fVV.Get("f5real"))
    h_boosted1_qcd=h_boosted1_data.Clone()
    h_boosted1_qcd.Add(h_boosted1_real,-1)
    h_boosted1_qcd.Add(h_boosted1_tt,-1)
    h_boosted1_qcd.Add(h_boosted1_w,-1)
    h_boosted1_w.SetName("frac_w_boosted1")
    h_boosted1_qcd.SetName("frac_qcd_boosted1")
    h_boosted1_tt.SetName("frac_tt_boosted1")
    h_boosted1_data.SetName("frac_data_boosted1")

    h_boosted2_w=fW.Get("f6jet")
    h_boosted2_w.Add(fDY.Get("f6jet"))
    h_boosted2_w.Add(fVV.Get("f6jet"))
    h_boosted2_tt=fTT.Get("f6jet")
    h_boosted2_data=fData.Get("f6real")
    h_boosted2_real=fDY.Get("f6real")
    h_boosted2_real.Add(fEmbedded.Get("f6real"))
    h_boosted2_real.Add(fTT.Get("f6real"))
    h_boosted2_real.Add(fVV.Get("f6real"))
    h_boosted2_qcd=h_boosted2_data.Clone()
    h_boosted2_qcd.Add(h_boosted2_real,-1)
    h_boosted2_qcd.Add(h_boosted2_tt,-1)
    h_boosted2_qcd.Add(h_boosted2_w,-1)
    h_boosted2_w.SetName("frac_w_boosted2")
    h_boosted2_qcd.SetName("frac_qcd_boosted2")
    h_boosted2_tt.SetName("frac_tt_boosted2")
    h_boosted2_data.SetName("frac_data_boosted2")

    h_vbflow_w=fW.Get("f7jet")
    h_vbflow_w.Add(fDY.Get("f7jet"))
    h_vbflow_w.Add(fVV.Get("f7jet"))
    h_vbflow_tt=fTT.Get("f7jet")
    h_vbflow_data=fData.Get("f7real")
    h_vbflow_real=fDY.Get("f7real")
    h_vbflow_real.Add(fEmbedded.Get("f7real"))
    h_vbflow_real.Add(fTT.Get("f7real"))
    h_vbflow_real.Add(fVV.Get("f7real"))
    h_vbflow_qcd=h_vbflow_data.Clone()
    h_vbflow_qcd.Add(h_vbflow_real,-1)
    h_vbflow_qcd.Add(h_vbflow_tt,-1)
    h_vbflow_qcd.Add(h_vbflow_w,-1)
    h_vbflow_w.SetName("frac_w_vbflow")
    h_vbflow_qcd.SetName("frac_qcd_vbflow")
    h_vbflow_tt.SetName("frac_tt_vbflow")
    h_vbflow_data.SetName("frac_data_vbflow")

    h_vbfhigh_w=fW.Get("f8jet")
    h_vbfhigh_w.Add(fDY.Get("f8jet"))
    h_vbfhigh_w.Add(fVV.Get("f8jet"))
    h_vbfhigh_tt=fTT.Get("f8jet")
    h_vbfhigh_data=fData.Get("f8real")
    h_vbfhigh_real=fDY.Get("f8real")
    h_vbfhigh_real.Add(fEmbedded.Get("f8real"))
    h_vbfhigh_real.Add(fTT.Get("f8real"))
    h_vbfhigh_real.Add(fVV.Get("f8real"))
    h_vbfhigh_qcd=h_vbfhigh_data.Clone()
    h_vbfhigh_qcd.Add(h_vbfhigh_real,-1)
    h_vbfhigh_qcd.Add(h_vbfhigh_tt,-1)
    h_vbfhigh_qcd.Add(h_vbfhigh_w,-1)
    h_vbfhigh_w.SetName("frac_w_vbfhigh")
    h_vbfhigh_qcd.SetName("frac_qcd_vbfhigh")
    h_vbfhigh_tt.SetName("frac_tt_vbfhigh")
    h_vbfhigh_data.SetName("frac_data_vbfhigh")

    fout.cd()
    h_0jet_w.Write()
    h_0jet_tt.Write()
    h_0jet_qcd.Write()
    h_0jet_data.Write()

    h_boosted_w.Write()
    h_boosted_tt.Write()
    h_boosted_qcd.Write()
    h_boosted_data.Write()

    h_vbf_w.Write()
    h_vbf_tt.Write()
    h_vbf_qcd.Write()
    h_vbf_data.Write()

    h_0jetlow_w.Write()
    h_0jetlow_tt.Write()
    h_0jetlow_qcd.Write()
    h_0jetlow_data.Write()

    h_0jethigh_w.Write()
    h_0jethigh_tt.Write()
    h_0jethigh_qcd.Write()
    h_0jethigh_data.Write()

    h_boosted1_w.Write()
    h_boosted1_tt.Write()
    h_boosted1_qcd.Write()
    h_boosted1_data.Write()

    h_boosted2_w.Write()
    h_boosted2_tt.Write()
    h_boosted2_qcd.Write()
    h_boosted2_data.Write()

    h_vbflow_w.Write()
    h_vbflow_tt.Write()
    h_vbflow_qcd.Write()
    h_vbflow_data.Write()

    h_vbfhigh_w.Write()
    h_vbfhigh_tt.Write()
    h_vbfhigh_qcd.Write()
    h_vbfhigh_data.Write()
