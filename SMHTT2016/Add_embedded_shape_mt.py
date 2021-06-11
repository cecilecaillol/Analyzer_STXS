if __name__ == "__main__":

    import ROOT
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('--scale', default="nominal", choices=['nominal', 'up', 'down', 'wup', 'wdown','qcdup','qcddown','JESup','JESdown'], help="Which TES?")
    parser.add_argument('--directory', default="nominal")
    options = parser.parse_args()

    fEmbedded=ROOT.TFile("files_"+options.directory+"_mt/embedded.root","r")
    fTT=ROOT.TFile("files_"+options.directory+"_mt/TT.root","r")
    fout=ROOT.TFile("files_"+options.directory+"_mt/embeddedShape.root","recreate")


    categories=["mt_0jet","mt_boosted","mt_vbf","mt_0jet_PTH_0_10","mt_0jet_PTH_GE10","mt_boosted_1J","mt_boosted_GE2J","mt_vbf_PTH_0_200","mt_vbf_PTH_GE_200"]
    ncat=9

    for i in range(0,ncat):
       h_nominal=fEmbedded.Get("mt_0jet/embedded").Clone()
       h_tt=fTT.Get("mt_0jet/ttcontamination").Clone()
       if i==1:
          h_nominal=fEmbedded.Get("mt_boosted/embedded").Clone()
          h_tt=fTT.Get("mt_boosted/ttcontamination").Clone()
       if i==2:
          h_nominal=fEmbedded.Get("mt_vbf/embedded").Clone()
          h_tt=fTT.Get("mt_vbf/ttcontamination").Clone()
       if i==3:
          h_nominal=fEmbedded.Get("mt_0jet_PTH_0_10/embedded").Clone()
          h_tt=fTT.Get("mt_0jet_PTH_0_10/ttcontamination").Clone()
       if i==4:
          h_nominal=fEmbedded.Get("mt_0jet_PTH_GE10/embedded").Clone()
          h_tt=fTT.Get("mt_0jet_PTH_GE10/ttcontamination").Clone()
       if i==5:
          h_nominal=fEmbedded.Get("mt_boosted_1J/embedded").Clone()
          h_tt=fTT.Get("mt_boosted_1J/ttcontamination").Clone()
       if i==6:
          h_nominal=fEmbedded.Get("mt_boosted_GE2J/embedded").Clone()
          h_tt=fTT.Get("mt_boosted_GE2J/ttcontamination").Clone()
       if i==7:
          h_nominal=fEmbedded.Get("mt_vbf_PTH_0_200/embedded").Clone()
          h_tt=fTT.Get("mt_vbf_PTH_0_200/ttcontamination").Clone()
       if i==8:
          h_nominal=fEmbedded.Get("mt_vbf_PTH_GE_200/embedded").Clone()
          h_tt=fTT.Get("mt_vbf_PTH_GE_200/ttcontamination").Clone()
       h_up=h_nominal.Clone()
       h_down=h_nominal.Clone()
       print h_tt.Integral()
       h_up.Add(h_tt,0.10)
       h_down.Add(h_tt,-0.10)

       fout.cd()
       mydir=fout.mkdir(categories[i])
       mydir.cd()
       h_up.SetName("embedded_CMS_htt_emb_ttbar_2016Up")
       h_up.Write()
       h_down.SetName("embedded_CMS_htt_emb_ttbar_2016Down")
       h_down.Write()

