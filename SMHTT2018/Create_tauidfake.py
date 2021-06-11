if __name__ == "__main__":

    import ROOT
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('--scale', default="nominal", choices=['nominal', 'up', 'down', 'wup', 'wdown','qcdup','qcddown','JESup','JESdown'], help="Which TES?")
    options = parser.parse_args()

    nbhist=1

    fData=ROOT.TFile("tauidfiles/Data.root","r")
    fDYL=ROOT.TFile("tauidfiles/DYL.root","r")
    fembedded=ROOT.TFile("tauidfiles/embedded.root","r")
    fTT=ROOT.TFile("tauidfiles/TTscaled.root","r")
    fVV=ROOT.TFile("tauidfiles/VV.root","r")
    fW=ROOT.TFile("tauidfiles/Wscaled.root","r")
    fout=ROOT.TFile("tauidfiles/Fake.root","recreate")

    postfix=[""]

    fout.cd()
    dir0=fout.mkdir("ZLmu0")
    dir0.cd()
    for k in range(0,nbhist):
      myh=fData.Get("ZLmu0SSAI").Get("data_obs").Clone()
      myh.Add(fDYL.Get("ZLmu0SSAI").Get("DYL").Clone(),-1)
      myh.Add(fembedded.Get("ZLmu0SSAI").Get("embedded").Clone(),-1)
      myh.Add(fTT.Get("ZLmu0SSAI").Get("TT").Clone(),-1)
      myh.Add(fVV.Get("ZLmu0SSAI").Get("VV").Clone(),-1)
      myh.Add(fVV.Get("ZLmu0SSAI").Get("ST").Clone(),-1)
      myh.Add(fW.Get("ZLmu0SSAI").Get("W").Clone(),-1)
      myh2=fData.Get("ZLmu0SS").Get("data_obs").Clone()
      myh2.Add(fDYL.Get("ZLmu0SS").Get("DYL").Clone(),-1)
      myh2.Add(fembedded.Get("ZLmu0SS").Get("embedded").Clone(),-1)
      myh2.Add(fTT.Get("ZLmu0SS").Get("TT").Clone(),-1)
      myh2.Add(fVV.Get("ZLmu0SS").Get("VV").Clone(),-1)
      myh2.Add(fVV.Get("ZLmu0SS").Get("ST").Clone(),-1)
      myh2.Add(fW.Get("ZLmu0SS").Get("W").Clone(),-1)
      myh.Scale(myh2.Integral()/myh.Integral())
      myh.Scale(1.06)
      myh.SetName("QCD"+postfix[k])
      myh.Write()

    #dir1=fout.mkdir("ZLmu1")
    #dir1.cd()
    #for k in range(0,nbhist):
    #  myh=fData.Get("ZLmu1SSAI").Get("data_obs").Clone()
    #  myh.Add(fDYL.Get("ZLmu1SSAI").Get("DYL").Clone(),-1)
    #  myh.Add(fembedded.Get("ZLmu1SSAI").Get("embedded").Clone(),-1)
    #  myh.Add(fTT.Get("ZLmu1SSAI").Get("TT").Clone(),-1)
    #  myh.Add(fVV.Get("ZLmu1SSAI").Get("VV").Clone(),-1)
    #  myh.Add(fVV.Get("ZLmu1SSAI").Get("ST").Clone(),-1)
    #  myh.Add(fW.Get("ZLmu1SSAI").Get("W").Clone(),-1)
    #  myh2=fData.Get("ZLmu0SSAI").Get("data_obs").Clone()
    #  myh2.Add(fDYL.Get("ZLmu0SS").Get("DYL").Clone(),-1)
    #  myh2.Add(fembedded.Get("ZLmu0SS").Get("embedded").Clone(),-1)
    #  myh2.Add(fTT.Get("ZLmu0SS").Get("TT").Clone(),-1)
    #  myh2.Add(fVV.Get("ZLmu0SS").Get("VV").Clone(),-1)
    #  myh2.Add(fVV.Get("ZLmu0SS").Get("ST").Clone(),-1)
    #  myh2.Add(fW.Get("ZLmu0SS").Get("W").Clone(),-1)
    #  myh.Scale(myh2.Integral()/myh.Integral())
    #  myh.SetName("QCD"+postfix[k])
    #  myh.Write()

    dir2=fout.mkdir("ZLmu0MTOS")
    dir2.cd()
    for k in range(0,nbhist):
      myh=fData.Get("ZLmu0MTSS").Get("data_obs").Clone()
      myh.Add(fDYL.Get("ZLmu0MTSS").Get("DYL").Clone(),-1)
      myh.Add(fembedded.Get("ZLmu0MTSS").Get("embedded").Clone(),-1)
      myh.Add(fTT.Get("ZLmu0MTSS").Get("TT").Clone(),-1)
      myh.Add(fVV.Get("ZLmu0MTSS").Get("VV").Clone(),-1)
      myh.Add(fVV.Get("ZLmu0MTSS").Get("ST").Clone(),-1)
      myh.Add(fW.Get("ZLmu0MTSS").Get("W").Clone(),-1)
      myh.SetName("QCD"+postfix[k])
      myh.Scale(1.06)
      myh.Write()

    #dir3=fout.mkdir("ZLmu1MTOS")
    #dir3.cd()
    #for k in range(0,nbhist):
    #  myh=fData.Get("ZLmu1MTSS").Get("data_obs").Clone()
    #  myh.Add(fDYL.Get("ZLmu1MTSS").Get("DYL").Clone(),-1)
    #  myh.Add(fembedded.Get("ZLmu1MTSS").Get("embedded").Clone(),-1)
    #  myh.Add(fTT.Get("ZLmu1MTSS").Get("TT").Clone(),-1)
    #  myh.Add(fVV.Get("ZLmu1MTSS").Get("VV").Clone(),-1)
    #  myh.Add(fVV.Get("ZLmu1MTSS").Get("ST").Clone(),-1)
    #  myh.Add(fW.Get("ZLmu1MTSS").Get("W").Clone(),-1)
    #  myh.SetName("QCD"+postfix[k])
    #  myh.Write()

