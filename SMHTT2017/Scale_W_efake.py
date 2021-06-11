if __name__ == "__main__":

    import ROOT
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('--scale', default="nominal", choices=['nominal', 'up', 'down', 'wup', 'wdown','qcdup','qcddown','JESup','JESdown'], help="Which TES?")
    options = parser.parse_args()

    nbhist=1

    fData=ROOT.TFile("efakefiles/Data.root","r")
    fDY=ROOT.TFile("efakefiles/DY.root","r")
    fTT=ROOT.TFile("efakefiles/TT.root","r")
    fVV=ROOT.TFile("efakefiles/VV.root","r")
    fW=ROOT.TFile("efakefiles/W.root","r")
    foutW=ROOT.TFile("efakefiles/Wscaled.root","recreate")
    foutTT=ROOT.TFile("efakefiles/TTscaled.root","recreate")

    postfix=[""]

    sf=1.0
    sfpass=1.0
    for k in range(0,nbhist):
      myh=fData.Get("ZLepassMTOS").Get("data_obs").Clone()
      myh.Add(fDY.Get("ZLepassMTOS").Get("DYL").Clone(),-1)
      myh.Add(fDY.Get("ZLepassMTOS").Get("DYT").Clone(),-1)
      myh.Add(fDY.Get("ZLepassMTOS").Get("DYJ").Clone(),-1)
      myh.Add(fTT.Get("ZLepassMTOS").Get("TTT").Clone(),-1)
      myh.Add(fTT.Get("ZLepassMTOS").Get("TTL").Clone(),-1)
      myh.Add(fTT.Get("ZLepassMTOS").Get("TTJ").Clone(),-1)
      myh.Add(fVV.Get("ZLepassMTOS").Get("VVT").Clone(),-1)
      myh.Add(fVV.Get("ZLepassMTOS").Get("VVL").Clone(),-1)
      myh.Add(fVV.Get("ZLepassMTOS").Get("VVJ").Clone(),-1)
      myh.Add(fVV.Get("ZLepassMTOS").Get("STT").Clone(),-1)
      myh.Add(fVV.Get("ZLepassMTOS").Get("STL").Clone(),-1)
      myh.Add(fVV.Get("ZLepassMTOS").Get("STJ").Clone(),-1)
      sf=myh.Integral()/fW.Get("ZLepassMTOS").Get("W").Integral()
      print sf
      sf2=fData.Get("ZLepassMTOS").Get("data_obs").Integral()/(fDY.Get("ZLepassMTOS").Get("DYT").Integral()+fDY.Get("ZLepassMTOS").Get("DYL").Integral()+fDY.Get("ZLepassMTOS").Get("DYJ").Integral()+fTT.Get("ZLepassMTOS").Get("TTT").Integral()+fTT.Get("ZLepassMTOS").Get("TTL").Integral()+fTT.Get("ZLepassMTOS").Get("TTJ").Integral()+fVV.Get("ZLepassMTOS").Get("VVT").Integral()+fVV.Get("ZLepassMTOS").Get("VVL").Integral()+fVV.Get("ZLepassMTOS").Get("VVJ").Integral()+fVV.Get("ZLepassMTOS").Get("STT").Integral()+fVV.Get("ZLepassMTOS").Get("STL").Integral()+fVV.Get("ZLepassMTOS").Get("STJ").Integral()+fW.Get("ZLepassMTOS").Get("W").Integral())
      print sf2
      sfpass=sf2

    sffail=1.0
    for k in range(0,nbhist):
      myh=fData.Get("ZLefailMTOS").Get("data_obs").Clone()
      myh.Add(fDY.Get("ZLefailMTOS").Get("DYL").Clone(),-1)
      myh.Add(fDY.Get("ZLefailMTOS").Get("DYT").Clone(),-1)
      myh.Add(fDY.Get("ZLefailMTOS").Get("DYJ").Clone(),-1)
      myh.Add(fTT.Get("ZLefailMTOS").Get("TTT").Clone(),-1)
      myh.Add(fTT.Get("ZLefailMTOS").Get("TTL").Clone(),-1)
      myh.Add(fTT.Get("ZLefailMTOS").Get("TTJ").Clone(),-1)
      myh.Add(fVV.Get("ZLefailMTOS").Get("VVT").Clone(),-1)
      myh.Add(fVV.Get("ZLefailMTOS").Get("VVL").Clone(),-1)
      myh.Add(fVV.Get("ZLefailMTOS").Get("VVJ").Clone(),-1)
      myh.Add(fVV.Get("ZLefailMTOS").Get("STT").Clone(),-1)
      myh.Add(fVV.Get("ZLefailMTOS").Get("STL").Clone(),-1)
      myh.Add(fVV.Get("ZLefailMTOS").Get("STJ").Clone(),-1)
      sf=myh.Integral()/fW.Get("ZLefailMTOS").Get("W").Integral()
      print sf
      sf2=fData.Get("ZLefailMTOS").Get("data_obs").Integral()/(fDY.Get("ZLefailMTOS").Get("DYT").Integral()+fDY.Get("ZLefailMTOS").Get("DYL").Integral()+fDY.Get("ZLefailMTOS").Get("DYJ").Integral()+fTT.Get("ZLefailMTOS").Get("TTT").Integral()+fTT.Get("ZLefailMTOS").Get("TTL").Integral()+fTT.Get("ZLefailMTOS").Get("TTJ").Integral()+fVV.Get("ZLefailMTOS").Get("VVT").Integral()+fVV.Get("ZLefailMTOS").Get("VVL").Integral()+fVV.Get("ZLefailMTOS").Get("VVJ").Integral()+fVV.Get("ZLefailMTOS").Get("STT").Integral()+fVV.Get("ZLefailMTOS").Get("STL").Integral()+fVV.Get("ZLefailMTOS").Get("STJ").Integral()+fW.Get("ZLefailMTOS").Get("W").Integral())
      print sf2
      #sffail=sf2


    name=["ZLepass","ZLepassMTOS","ZLepassMTSS","ZLepassSSAI","ZLepassSS"]
    namefail=["ZLefail","ZLefailMTOS","ZLefailMTSS","ZLefailSSAI","ZLefailSS"]
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
