if __name__ == "__main__":

    import ROOT
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('--scale', default="nominal", choices=['nominal', 'up', 'down', 'wup', 'wdown','qcdup','qcddown','JESup','JESdown'], help="Which TES?")
    options = parser.parse_args()

    fEmb=ROOT.TFile("files_nominal_tt/Embedded.root","r")
    fTT=ROOT.TFile("files_nominal_tt/TT.root","r")
    fout=ROOT.TFile("files_nominal_tt/EmbeddedUnc.root","recreate")

    h_0jetU=fEmb.Get("tt_0jet").Get("embedded").Clone()
    h_0jetD=fEmb.Get("tt_0jet").Get("embedded").Clone()
    h_0jetU.Add(fTT.Get("tt_0jet").Get("TTT"),0.1)
    h_0jetD.Add(fTT.Get("tt_0jet").Get("TTT"),-0.1)
    h_0jetU.SetName("embedded_CMS_htt_emb_ttbarUp")
    h_0jetD.SetName("embedded_CMS_htt_emb_ttbarDown")

    h_boostedU=fEmb.Get("tt_boosted").Get("embedded").Clone()
    h_boostedD=fEmb.Get("tt_boosted").Get("embedded").Clone()
    h_boostedU.Add(fTT.Get("tt_boosted").Get("TTT"),0.1)
    h_boostedD.Add(fTT.Get("tt_boosted").Get("TTT"),-0.1)
    h_boostedU.SetName("embedded_CMS_htt_emb_ttbarUp")
    h_boostedD.SetName("embedded_CMS_htt_emb_ttbarDown")

    h_vbfU=fEmb.Get("tt_vbf").Get("embedded").Clone()
    h_vbfD=fEmb.Get("tt_vbf").Get("embedded").Clone()
    h_vbfU.Add(fTT.Get("tt_vbf").Get("TTT"),0.1)
    h_vbfD.Add(fTT.Get("tt_vbf").Get("TTT"),-0.1)
    h_vbfU.SetName("embedded_CMS_htt_emb_ttbarUp")
    h_vbfD.SetName("embedded_CMS_htt_emb_ttbarDown")

    h_1jetU=fEmb.Get("tt_1jet").Get("embedded").Clone()
    h_1jetD=fEmb.Get("tt_1jet").Get("embedded").Clone()
    h_1jetU.Add(fTT.Get("tt_1jet").Get("TTT"),0.1)
    h_1jetD.Add(fTT.Get("tt_1jet").Get("TTT"),-0.1)
    h_1jetU.SetName("embedded_CMS_htt_emb_ttbarUp")
    h_1jetD.SetName("embedded_CMS_htt_emb_ttbarDown")

    h_gg2jetsU=fEmb.Get("tt_gg2jets").Get("embedded").Clone()
    h_gg2jetsD=fEmb.Get("tt_gg2jets").Get("embedded").Clone()
    h_gg2jetsU.Add(fTT.Get("tt_gg2jets").Get("TTT"),0.1)
    h_gg2jetsD.Add(fTT.Get("tt_gg2jets").Get("TTT"),-0.1)
    h_gg2jetsU.SetName("embedded_CMS_htt_emb_ttbarUp")
    h_gg2jetsD.SetName("embedded_CMS_htt_emb_ttbarDown")

    h_vh2jetsU=fEmb.Get("tt_vh2jets").Get("embedded").Clone()
    h_vh2jetsD=fEmb.Get("tt_vh2jets").Get("embedded").Clone()
    h_vh2jetsU.Add(fTT.Get("tt_vh2jets").Get("TTT"),0.1)
    h_vh2jetsD.Add(fTT.Get("tt_vh2jets").Get("TTT"),-0.1)
    h_vh2jetsU.SetName("embedded_CMS_htt_emb_ttbarUp")
    h_vh2jetsD.SetName("embedded_CMS_htt_emb_ttbarDown")

    h_vbf2U=fEmb.Get("tt_vbf2").Get("embedded").Clone()
    h_vbf2D=fEmb.Get("tt_vbf2").Get("embedded").Clone()
    h_vbf2U.Add(fTT.Get("tt_vbf2").Get("TTT"),0.1)
    h_vbf2D.Add(fTT.Get("tt_vbf2").Get("TTT"),-0.1)
    h_vbf2U.SetName("embedded_CMS_htt_emb_ttbarUp")
    h_vbf2D.SetName("embedded_CMS_htt_emb_ttbarDown")
    
    fout.cd()
    dir0jet=fout.mkdir("tt_0jet")
    dir0jet.cd()
    h_0jetU.Write()
    h_0jetD.Write()

    dir1jet=fout.mkdir("tt_boosted")
    dir1jet.cd()
    h_boostedU.Write()
    h_boostedD.Write()

    dir2jet=fout.mkdir("tt_vbf")
    dir2jet.cd()
    h_vbfU.Write()
    h_vbfD.Write()

    dir3jet=fout.mkdir("tt_1jet")
    dir3jet.cd()
    h_1jetU.Write()
    h_1jetD.Write()

    dir4jet=fout.mkdir("tt_gg2jets")
    dir4jet.cd()
    h_gg2jetsU.Write()
    h_gg2jetsD.Write()

    dir5jet=fout.mkdir("tt_vh2jets")
    dir5jet.cd()
    h_vh2jetsU.Write()
    h_vh2jetsD.Write()

    dir6jet=fout.mkdir("tt_vbf2")
    dir6jet.cd()
    h_vbf2U.Write()
    h_vbf2D.Write()

