if __name__ == "__main__":

    import ROOT
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('--scale', default="nominal", choices=['nominal', 'up', 'down', 'wup', 'wdown','qcdup','qcddown','JESup','JESdown'], help="Which TES?")
    options = parser.parse_args()

    nbhist=1

    fData=ROOT.TFile("mufakefiles/Data.root","r")
    fDY=ROOT.TFile("mufakefiles/DY.root","r")
    fTT=ROOT.TFile("mufakefiles/TT.root","r")
    fVV=ROOT.TFile("mufakefiles/VV.root","r")
    fW=ROOT.TFile("mufakefiles/W.root","r")
    foutW=ROOT.TFile("mufakefiles/Wscaled.root","recreate")
    foutTT=ROOT.TFile("mufakefiles/TTscaled.root","recreate")

    postfix=[""]

    sf=1.0
    sfpass=1.0
    for k in range(0,nbhist):
      myh=fData.Get("ZLmupassMTOS").Get("data_obs").Clone()
      myh.Add(fDY.Get("ZLmupassMTOS").Get("DYL").Clone(),-1)
      myh.Add(fDY.Get("ZLmupassMTOS").Get("DYT").Clone(),-1)
      myh.Add(fDY.Get("ZLmupassMTOS").Get("DYJ").Clone(),-1)
      myh.Add(fTT.Get("ZLmupassMTOS").Get("TTT").Clone(),-1)
      myh.Add(fTT.Get("ZLmupassMTOS").Get("TTL").Clone(),-1)
      myh.Add(fTT.Get("ZLmupassMTOS").Get("TTJ").Clone(),-1)
      myh.Add(fVV.Get("ZLmupassMTOS").Get("VVT").Clone(),-1)
      myh.Add(fVV.Get("ZLmupassMTOS").Get("VVL").Clone(),-1)
      myh.Add(fVV.Get("ZLmupassMTOS").Get("VVJ").Clone(),-1)
      myh.Add(fVV.Get("ZLmupassMTOS").Get("STT").Clone(),-1)
      myh.Add(fVV.Get("ZLmupassMTOS").Get("STL").Clone(),-1)
      myh.Add(fVV.Get("ZLmupassMTOS").Get("STJ").Clone(),-1)
      sf=myh.Integral()/fW.Get("ZLmupassMTOS").Get("W").Integral()
      print sf
      sf2=fData.Get("ZLmupassMTOS").Get("data_obs").Integral()/(fDY.Get("ZLmupassMTOS").Get("DYT").Integral()+fDY.Get("ZLmupassMTOS").Get("DYL").Integral()+fDY.Get("ZLmupassMTOS").Get("DYJ").Integral()+fTT.Get("ZLmupassMTOS").Get("TTT").Integral()+fTT.Get("ZLmupassMTOS").Get("TTL").Integral()+fTT.Get("ZLmupassMTOS").Get("TTJ").Integral()+fVV.Get("ZLmupassMTOS").Get("VVT").Integral()+fVV.Get("ZLmupassMTOS").Get("VVL").Integral()+fVV.Get("ZLmupassMTOS").Get("VVJ").Integral()+fVV.Get("ZLmupassMTOS").Get("STT").Integral()+fVV.Get("ZLmupassMTOS").Get("STL").Integral()+fVV.Get("ZLmupassMTOS").Get("STJ").Integral()+fW.Get("ZLmupassMTOS").Get("W").Integral())
      print sf2
      sfpass=sf2

    sffail=1.0
    for k in range(0,nbhist):
      myh=fData.Get("ZLmufailMTOS").Get("data_obs").Clone()
      myh.Add(fDY.Get("ZLmufailMTOS").Get("DYL").Clone(),-1)
      myh.Add(fDY.Get("ZLmufailMTOS").Get("DYT").Clone(),-1)
      myh.Add(fDY.Get("ZLmufailMTOS").Get("DYJ").Clone(),-1)
      myh.Add(fTT.Get("ZLmufailMTOS").Get("TTT").Clone(),-1)
      myh.Add(fTT.Get("ZLmufailMTOS").Get("TTL").Clone(),-1)
      myh.Add(fTT.Get("ZLmufailMTOS").Get("TTJ").Clone(),-1)
      myh.Add(fVV.Get("ZLmufailMTOS").Get("VVT").Clone(),-1)
      myh.Add(fVV.Get("ZLmufailMTOS").Get("VVL").Clone(),-1)
      myh.Add(fVV.Get("ZLmufailMTOS").Get("VVJ").Clone(),-1)
      myh.Add(fVV.Get("ZLmufailMTOS").Get("STT").Clone(),-1)
      myh.Add(fVV.Get("ZLmufailMTOS").Get("STL").Clone(),-1)
      myh.Add(fVV.Get("ZLmufailMTOS").Get("STJ").Clone(),-1)
      sf=myh.Integral()/fW.Get("ZLmufailMTOS").Get("W").Integral()
      print sf
      sf2=fData.Get("ZLmufailMTOS").Get("data_obs").Integral()/(fDY.Get("ZLmufailMTOS").Get("DYT").Integral()+fDY.Get("ZLmufailMTOS").Get("DYL").Integral()+fDY.Get("ZLmufailMTOS").Get("DYJ").Integral()+fTT.Get("ZLmufailMTOS").Get("TTT").Integral()+fTT.Get("ZLmufailMTOS").Get("TTL").Integral()+fTT.Get("ZLmufailMTOS").Get("TTJ").Integral()+fVV.Get("ZLmufailMTOS").Get("VVT").Integral()+fVV.Get("ZLmufailMTOS").Get("VVL").Integral()+fVV.Get("ZLmufailMTOS").Get("VVJ").Integral()+fVV.Get("ZLmufailMTOS").Get("STT").Integral()+fVV.Get("ZLmufailMTOS").Get("STL").Integral()+fVV.Get("ZLmufailMTOS").Get("STJ").Integral()+fW.Get("ZLmufailMTOS").Get("W").Integral())
      print sf2
      #sffail=sf2


    name=["ZLmupass","ZLmupassMTOS","ZLmupassMTSS","ZLmupassSSAI","ZLmupassSS"]
    namefail=["ZLmufail","ZLmufailMTOS","ZLmufailMTSS","ZLmufailSSAI","ZLmufailSS"]
    ncat=5

    for l in range(0,ncat):
      dir0=foutW.mkdir(name[l])
      dir0.cd()
      for k in range(0,nbhist):
        myh=fW.Get(name[l]).Get("W").Clone()
        myh.SetName("W")
        myh.Scale(sfpass)
        myh.Write()

    for l in range(0,ncat):
      dir0=foutTT.mkdir(name[l])
      dir0.cd()
      for k in range(0,nbhist):
        myh=fTT.Get(name[l]).Get("TTJ").Clone()
        myh.SetName("TTJ")
        myh.Scale(sfpass)
        myh.Write()
        myh=fTT.Get(name[l]).Get("TTL").Clone()
        myh.SetName("TTL")
        myh.Write()
        myh=fTT.Get(name[l]).Get("TTT").Clone()
        myh.SetName("TTT")
        myh.Write()

    for l in range(0,ncat):
      dir0=foutW.mkdir(namefail[l])
      dir0.cd()
      for k in range(0,nbhist):
        myh=fW.Get(namefail[l]).Get("W").Clone()
        myh.SetName("W")
        myh.Scale(sffail)
        myh.Write()

    for l in range(0,ncat):
      dir0=foutTT.mkdir(namefail[l])
      dir0.cd()
      for k in range(0,nbhist):
        myh=fTT.Get(namefail[l]).Get("TTJ").Clone()
        myh.SetName("TTJ")
        myh.Scale(sffail)
        myh.Write()
        myh=fTT.Get(namefail[l]).Get("TTL").Clone()
        myh.SetName("TTL")
        myh.Write()
        myh=fTT.Get(namefail[l]).Get("TTT").Clone()
        myh.SetName("TTT")
        myh.Write()
