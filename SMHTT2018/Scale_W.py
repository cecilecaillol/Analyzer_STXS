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
    fTT=ROOT.TFile("tauidfiles/TT.root","r")
    fVV=ROOT.TFile("tauidfiles/VV.root","r")
    fW=ROOT.TFile("tauidfiles/W.root","r")
    foutW=ROOT.TFile("tauidfiles/Wscaled.root","recreate")
    foutTT=ROOT.TFile("tauidfiles/TTscaled.root","recreate")

    postfix=[""]

    sf=1.0
    #for k in range(0,nbhist):
    #  myh=fData.Get("ZLmu0MTOS").Get("data_obs").Clone()
    #  myh.Add(fDYL.Get("ZLmu0MTOS").Get("DYL").Clone(),-1)
    #  myh.Add(fembedded.Get("ZLmu0MTOS").Get("embedded").Clone(),-1)
    #  myh.Add(fTT.Get("ZLmu0MTOS").Get("TT").Clone(),-1)
    #  myh.Add(fVV.Get("ZLmu0MTOS").Get("VV").Clone(),-1)
    #  myh.Add(fVV.Get("ZLmu0MTOS").Get("ST").Clone(),-1)
    #  sf=myh.Integral()/fW.Get("ZLmu0MTOS").Get("W").Integral()
    #  print sf
    #  sf2=fData.Get("ZLmu0MTOS").Get("data_obs").Integral()/(fDYL.Get("ZLmu0MTOS").Get("DYL").Integral()+fembedded.Get("ZLmu0MTOS").Get("embedded").Integral()+fTT.Get("ZLmu0MTOS").Get("TT").Integral()+fVV.Get("ZLmu0MTOS").Get("VV").Integral()+fVV.Get("ZLmu0MTOS").Get("ST").Integral()+fW.Get("ZLmu0MTOS").Get("W").Integral())
    #  print sf2
    #  sf=sf2

    dir0=foutW.mkdir("ZLmu0")
    dir0.cd()
    for k in range(0,nbhist):
      myh=fW.Get("ZLmu0").Get("W").Clone()
      myh.SetName("W")
      myh.Scale(sf)
      myh.Write()

    dir1=foutW.mkdir("ZLmu0MTOS")
    dir1.cd()
    for k in range(0,nbhist):
      myh=fW.Get("ZLmu0MTOS").Get("W").Clone()
      myh.SetName("W")
      myh.Scale(sf)
      myh.Write()

    dir11=foutW.mkdir("ZLmu0MTSS")
    dir11.cd()
    for k in range(0,nbhist):
      myh=fW.Get("ZLmu0MTSS").Get("W").Clone()
      myh.SetName("W")
      myh.Scale(sf)
      myh.Write()

    dir2=foutW.mkdir("ZLmu0SSAI")
    dir2.cd()
    for k in range(0,nbhist):
      myh=fW.Get("ZLmu0SSAI").Get("W").Clone()
      myh.SetName("W")
      myh.Scale(sf)
      myh.Write()

    dir3=foutW.mkdir("ZLmu0SS")
    dir3.cd()
    for k in range(0,nbhist):
      myh=fW.Get("ZLmu0SS").Get("W").Clone()
      myh.SetName("W")
      myh.Scale(sf)
      myh.Write()

#####

    dir0=foutTT.mkdir("ZLmu0")
    dir0.cd()
    for k in range(0,nbhist):
      myh=fTT.Get("ZLmu0").Get("TT").Clone()
      myh.SetName("TT")
      myh.Scale(sf)
      myh.Write()

    dir1=foutTT.mkdir("ZLmu0MTOS")
    dir1.cd()
    for k in range(0,nbhist):
      myh=fTT.Get("ZLmu0MTOS").Get("TT").Clone()
      myh.SetName("TT")
      myh.Scale(sf)
      myh.Write()

    dir11=foutTT.mkdir("ZLmu0MTSS")
    dir11.cd()
    for k in range(0,nbhist):
      myh=fTT.Get("ZLmu0MTSS").Get("TT").Clone()
      myh.SetName("TT")
      myh.Scale(sf)
      myh.Write()

    dir2=foutTT.mkdir("ZLmu0SSAI")
    dir2.cd()
    for k in range(0,nbhist):
      myh=fTT.Get("ZLmu0SSAI").Get("TT").Clone()
      myh.SetName("TT")
      myh.Scale(sf)
      myh.Write()

    dir3=foutTT.mkdir("ZLmu0SS")
    dir3.cd()
    for k in range(0,nbhist):
      myh=fTT.Get("ZLmu0SS").Get("TT").Clone()
      myh.SetName("TT")
      myh.Scale(sf)
      myh.Write()
