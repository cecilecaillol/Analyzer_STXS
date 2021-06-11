if __name__ == "__main__":

    import ROOT
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('--scale', default="nominal", choices=['nominal', 'up', 'down', 'wup', 'wdown','qcdup','qcddown','JESup','JESdown'], help="Which TES?")
    options = parser.parse_args()

    nbhist=1

    fData=ROOT.TFile("ZLefiles/Data.root","r")
    fDYL=ROOT.TFile("ZLefiles/DYL.root","r")
    fDYT=ROOT.TFile("ZLefiles/DYT.root","r")
    fTT=ROOT.TFile("ZLefiles/TT.root","r")
    fVV=ROOT.TFile("ZLefiles/VV.root","r")
    fW=ROOT.TFile("ZLefiles/W.root","r")
    fout=ROOT.TFile("ZLefiles/Fake.root","recreate")

    postfix=[""]

    fout.cd()
    dir0=fout.mkdir("ZLe0")
    dir0.cd()
    for k in range(0,nbhist):
      myh=fData.Get("ZLe0SSAI").Get("data_obs").Clone()
      myh.Add(fDYL.Get("ZLe0SSAI").Get("DYL").Clone(),-1)
      myh.Add(fDYT.Get("ZLe0SSAI").Get("DYT").Clone(),-1)
      myh.Add(fTT.Get("ZLe0SSAI").Get("TT").Clone(),-1)
      myh.Add(fVV.Get("ZLe0SSAI").Get("VV").Clone(),-1)
      myh.Add(fVV.Get("ZLe0SSAI").Get("ST").Clone(),-1)
      myh.Add(fW.Get("ZLe0SSAI").Get("W").Clone(),-1)
      myh2=fData.Get("ZLe0SS").Get("data_obs").Clone()
      myh2.Add(fDYL.Get("ZLe0SS").Get("DYL").Clone(),-1)
      myh2.Add(fDYT.Get("ZLe0SS").Get("DYT").Clone(),-1)
      myh2.Add(fTT.Get("ZLe0SS").Get("TT").Clone(),-1)
      myh2.Add(fVV.Get("ZLe0SS").Get("VV").Clone(),-1)
      myh2.Add(fVV.Get("ZLe0SS").Get("ST").Clone(),-1)
      myh2.Add(fW.Get("ZLe0SS").Get("W").Clone(),-1)
      myh.Scale(myh2.Integral()/myh.Integral())
      myh.SetName("QCD"+postfix[k])
      myh.Write()

    dir1=fout.mkdir("ZLe1")
    dir1.cd()
    for k in range(0,nbhist):
      myh=fData.Get("ZLe1SSAI").Get("data_obs").Clone()
      myh.Add(fDYL.Get("ZLe1SSAI").Get("DYL").Clone(),-1)
      myh.Add(fDYT.Get("ZLe1SSAI").Get("DYT").Clone(),-1)
      myh.Add(fTT.Get("ZLe1SSAI").Get("TT").Clone(),-1)
      myh.Add(fVV.Get("ZLe1SSAI").Get("VV").Clone(),-1)
      myh.Add(fVV.Get("ZLe1SSAI").Get("ST").Clone(),-1)
      myh.Add(fW.Get("ZLe1SSAI").Get("W").Clone(),-1)
      myh2=fData.Get("ZLe0SSAI").Get("data_obs").Clone()
      myh2.Add(fDYL.Get("ZLe0SS").Get("DYL").Clone(),-1)
      myh2.Add(fDYT.Get("ZLe0SS").Get("DYT").Clone(),-1)
      myh2.Add(fTT.Get("ZLe0SS").Get("TT").Clone(),-1)
      myh2.Add(fVV.Get("ZLe0SS").Get("VV").Clone(),-1)
      myh2.Add(fVV.Get("ZLe0SS").Get("ST").Clone(),-1)
      myh2.Add(fW.Get("ZLe0SS").Get("W").Clone(),-1)
      myh.Scale(myh2.Integral()/myh.Integral())
      myh.SetName("QCD"+postfix[k])
      myh.Write()

    dir2=fout.mkdir("ZLe0MTOS")
    dir2.cd()
    for k in range(0,nbhist):
      myh=fData.Get("ZLe0MTSS").Get("data_obs").Clone()
      myh.Add(fDYL.Get("ZLe0MTSS").Get("DYL").Clone(),-1)
      myh.Add(fDYT.Get("ZLe0MTSS").Get("DYT").Clone(),-1)
      myh.Add(fTT.Get("ZLe0MTSS").Get("TT").Clone(),-1)
      myh.Add(fVV.Get("ZLe0MTSS").Get("VV").Clone(),-1)
      myh.Add(fVV.Get("ZLe0MTSS").Get("ST").Clone(),-1)
      myh.Add(fW.Get("ZLe0MTSS").Get("W").Clone(),-1)
      myh.SetName("QCD"+postfix[k])
      myh.Write()

    dir3=fout.mkdir("ZLe1MTOS")
    dir3.cd()
    for k in range(0,nbhist):
      myh=fData.Get("ZLe1MTSS").Get("data_obs").Clone()
      myh.Add(fDYL.Get("ZLe1MTSS").Get("DYL").Clone(),-1)
      myh.Add(fDYT.Get("ZLe1MTSS").Get("DYT").Clone(),-1)
      myh.Add(fTT.Get("ZLe1MTSS").Get("TT").Clone(),-1)
      myh.Add(fVV.Get("ZLe1MTSS").Get("VV").Clone(),-1)
      myh.Add(fVV.Get("ZLe1MTSS").Get("ST").Clone(),-1)
      myh.Add(fW.Get("ZLe1MTSS").Get("W").Clone(),-1)
      myh.SetName("QCD"+postfix[k])
      myh.Write()

