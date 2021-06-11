if __name__ == "__main__":

    import ROOT
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('--scale', default="nominal", help="Which TES?")
    parser.add_argument('--directory', default="nominal")
    options = parser.parse_args()

    nslices=int(3)

    fout=ROOT.TFile("files_"+options.directory+"_et/ZLshapes.root","recreate")

    fDY=ROOT.TFile("smh_et.root","r")

    categories=["et_0jet","et_boosted","et_vbf","et_0jetlow","et_0jethigh","et_boosted1","et_boosted2","et_vbflow","et_vbfhigh"]
    ncat=9

    for k in range(0,ncat):
      h_nominal=fDY.Get(categories[k]+"/ZL")
      print categories[k],h_nominal.GetSize()-2
      h_up1=h_nominal.Clone()
      h_down1=h_nominal.Clone()
      h_up2=h_nominal.Clone()
      h_down2=h_nominal.Clone()
      h_up3=h_nominal.Clone()
      h_down3=h_nominal.Clone()

      size_slice=(h_nominal.GetSize()-2)/nslices
      #print size_slice
      for j in range(1,size_slice+1):
	h_up1.SetBinContent(j,1.40*h_up1.GetBinContent(j))
        h_down1.SetBinContent(j,0.60*h_down1.GetBinContent(j))
      if nslices>1:
        for j in range(1+size_slice,2*size_slice+1):
          h_up2.SetBinContent(j,1.40*h_up2.GetBinContent(j))
          h_down2.SetBinContent(j,0.60*h_down2.GetBinContent(j))
      if nslices>2:
        for j in range(1+2*size_slice,3*size_slice+1):
          h_up3.SetBinContent(j,1.40*h_up3.GetBinContent(j))
          h_down3.SetBinContent(j,0.60*h_down3.GetBinContent(j))

      fout.cd()
      dir0jet=fout.mkdir(categories[k])
      dir0jet.cd()
      h_up1.SetName("ZL_CMS_norm_efaket_slice1_2017Up")
      h_up1.Write()
      h_down1.SetName("ZL_CMS_norm_efaket_slice1_2017Down")
      h_down1.Write()
      if nslices>1:
        h_up2.SetName("ZL_CMS_norm_efaket_slice2_2017Up")
        h_up2.Write()
        h_down2.SetName("ZL_CMS_norm_efaket_slice2_2017Down")
        h_down2.Write()
      if nslices>2:
        h_up3.SetName("ZL_CMS_norm_efaket_slice3_2017Up")
        h_up3.Write()
        h_down3.SetName("ZL_CMS_norm_efaket_slice3_2017Down")
        h_down3.Write()
