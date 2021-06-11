#include <TH2.h>
#include <TStyle.h>
#include "PostProcessing.h"
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphAsymmErrors.h>
#include "TMultiGraph.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include <stdio.h>
#include <TF1.h>
#include <TDirectoryFile.h>
#include <TRandom3.h>
#include "TLorentzVector.h"
#include "TString.h"
#include "ScaleFactor.h"
#include "TLegend.h"
#include "TH1F.h"
#include "TKey.h"
#include "THashList.h"
#include "THStack.h"
#include "TPaveLabel.h"
#include "TFile.h"
#include "myHelper.h"
#include "em_Tree.h"
#include "LumiReweightingStandAlone.h"
#include "RooWorkspace.h"
#include "RooRealVar.h"
#include "RooFunctor.h"
#include "ComputeWG1Unc.h"
#include "btagSF.h"

using namespace std;

int main(int argc, char** argv) {

    std::string input = *(argv + 1);
    std::string output = *(argv + 2);
    std::string sample = *(argv + 3);
    std::string name = *(argv + 4);

    float tes=0;
    if (argc > 1) {
        tes = atof(argv[5]);
    }

    TFile *f_Double = new TFile(input.c_str());
    cout<<"XXXXXXXXXXXXX "<<input.c_str()<<" XXXXXXXXXXXX"<<endl;
    TTree *arbre = (TTree*) f_Double->Get("emu_tree");
    TH1F* nbevt = (TH1F*) f_Double->Get("nevents");
    float ngen = nbevt->GetBinContent(2);

    float xs=1.0; float weight=1.0; float luminosity=35922.0;
    if (sample=="DY" or sample=="ZL" or sample=="ZTT" or sample=="ZJ" or sample=="ZLL"){ xs=6225.42; weight=luminosity*xs/ngen;}
    if (sample=="DYlow"){ xs=21658.0; weight=luminosity*xs/ngen;}
    else if (sample=="TT" or sample=="TTT" or sample=="TTJ") {xs=831.76; weight=luminosity*xs/ngen;}
    else if (sample=="TTTo2L2Nu") {xs=88.29; weight=luminosity*xs/ngen;}
    else if (sample=="TTToSemiLeptonic") {xs=365.35; weight=luminosity*xs/ngen;}
    else if (sample=="TTToHadronic") {xs=377.96; weight=luminosity*xs/ngen;}
    else if (sample=="W") {xs=61526.7; weight=luminosity*xs/ngen;}
    else if (sample=="data_obs"){weight=1.0;}
    else if (sample=="embedded"){weight=1.0;}
    else if (sample=="ST_tW_antitop") {xs=35.6; weight=luminosity*xs/ngen;}
    else if (sample=="ST_tW_top") {xs=35.6; weight=luminosity*xs/ngen;}
    else if (sample=="ST_t_antitop") {xs=26.23; weight=luminosity*xs/ngen;}
    else if (sample=="ST_t_top") {xs=44.07; weight=luminosity*xs/ngen;}
    else if (sample=="ggH_htt125") {xs=48.58*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="qqH_htt125") {xs=3.782*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="WplusH125") {xs=0.840*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="WminusH125") {xs=0.5328*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="ZH125") {xs=0.8839*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ") {xs=16.523; weight=luminosity*xs/ngen;}
    else if (sample=="WZ") {xs=47.13; weight=luminosity*xs/ngen;}
    else if (sample=="WW") {xs=118.7; weight=luminosity*xs/ngen;}
    else if (sample=="WZ1L1Nu2Q") {xs=10.71; weight=luminosity*xs/ngen;}
    else if (sample=="WZ1L3Nu") {xs=3.05; weight=luminosity*xs/ngen;}
    else if (sample=="WZJets") {xs=5.26; weight=luminosity*xs/ngen;}
    else if (sample=="WZ3L1Nu") {xs=4.708; weight=luminosity*xs/ngen;}
    else if (sample=="WZ2L2Q") {xs=5.595; weight=luminosity*xs/ngen;}
    else if (sample=="WW1L1Nu2Q") {xs=49.997; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ4L") {xs=1.212; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ2L2Q") {xs=3.22; weight=luminosity*xs/ngen;}
    else if (sample=="VV2L2Nu") {xs=11.95; weight=luminosity*xs/ngen;}
    else if (sample=="WGLNu") {xs=489.0; weight=luminosity*xs/ngen;}
    else if (sample=="WGstarMuMu") {xs=2.793; weight=luminosity*xs/ngen;}
    else if (sample=="WGstarEE") {xs=3.526; weight=luminosity*xs/ngen;}
    else if (sample=="EWKWminus") {xs=23.24; weight=luminosity*xs/ngen;}
    else if (sample=="EWKWplus") {xs=29.59; weight=luminosity*xs/ngen;}
    else if (sample=="EWKZLL" or sample=="EWKZLL_TT" or sample=="EWKZLL_J" or sample=="EWKZLL_L" or sample=="EWKZLL_LL") {xs=4.321; weight=luminosity*xs/ngen;}
    else if (sample=="EWKZNuNu" or sample=="EWKZNuNu_TT" or sample=="EWKZNuNu_J" or sample=="EWKZNuNu_L" or sample=="EWKZNuNu_LL") {xs=10.66; weight=luminosity*xs/ngen;}

    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(10);

    arbre->SetBranchAddress("passMu8E23", &passMu8E23);
    arbre->SetBranchAddress("passMu23E12", &passMu23E12);
    arbre->SetBranchAddress("matchMu8E23_1", &matchMu8E23_1);
    arbre->SetBranchAddress("matchMu23E12_1", &matchMu23E12_1);
    arbre->SetBranchAddress("filterMu8E23_1", &filterMu8E23_1);
    arbre->SetBranchAddress("filterMu23E12_1", &filterMu23E12_1);
    arbre->SetBranchAddress("matchMu8E23_2", &matchMu8E23_2);
    arbre->SetBranchAddress("matchMu23E12_2", &matchMu23E12_2);
    arbre->SetBranchAddress("filterMu8E23_2", &filterMu8E23_2);
    arbre->SetBranchAddress("filterMu23E12_2", &filterMu23E12_2);

    arbre->SetBranchAddress("passMu8E23DZ", &passMu8E23DZ);
    arbre->SetBranchAddress("passMu23E12DZ", &passMu23E12DZ);
    arbre->SetBranchAddress("matchMu8E23DZ_1", &matchMu8E23DZ_1);
    arbre->SetBranchAddress("matchMu23E12DZ_1", &matchMu23E12DZ_1);
    arbre->SetBranchAddress("filterMu8E23DZ_1", &filterMu8E23DZ_1);
    arbre->SetBranchAddress("filterMu23E12DZ_1", &filterMu23E12DZ_1);
    arbre->SetBranchAddress("matchMu8E23DZ_2", &matchMu8E23DZ_2);
    arbre->SetBranchAddress("matchMu23E12DZ_2", &matchMu23E12DZ_2);
    arbre->SetBranchAddress("filterMu8E23DZ_2", &filterMu8E23DZ_2);
    arbre->SetBranchAddress("filterMu23E12DZ_2", &filterMu23E12DZ_2);

    arbre->SetBranchAddress("run", &run);
    arbre->SetBranchAddress("lumi", &lumi);
    arbre->SetBranchAddress("evt", &evt);
    arbre->SetBranchAddress("npv", &npv);
    arbre->SetBranchAddress("pt_1", &pt_1);
    arbre->SetBranchAddress("phi_1", &phi_1);
    arbre->SetBranchAddress("eta_1", &eta_1);
    arbre->SetBranchAddress("iso_1", &iso_1);
    arbre->SetBranchAddress("iso_2", &iso_2);
    arbre->SetBranchAddress("m_1", &m_1);
    arbre->SetBranchAddress("q_1", &q_1);
    arbre->SetBranchAddress("nbtag", &nbtag);
    arbre->SetBranchAddress("nbtagL", &nbtagL);
    arbre->SetBranchAddress("bweight", &bweight);
    arbre->SetBranchAddress("q_2", &q_2);
    arbre->SetBranchAddress("pt_2", &pt_2);
    arbre->SetBranchAddress("eta_2", &eta_2);
    arbre->SetBranchAddress("m_2", &m_2);
    arbre->SetBranchAddress("phi_2", &phi_2);
    arbre->SetBranchAddress("met", &met);
    arbre->SetBranchAddress("m_sv", &m_sv);
    arbre->SetBranchAddress("m_sv_DOWN", &m_sv_DOWN);
    arbre->SetBranchAddress("m_sv_UP", &m_sv_UP);
    arbre->SetBranchAddress("m_sv_UESUp", &m_sv_UESUp);
    arbre->SetBranchAddress("m_sv_UESDown", &m_sv_UESDown);
    arbre->SetBranchAddress("met", &met);
    arbre->SetBranchAddress("metphi", &metphi);
    arbre->SetBranchAddress("met_UESUp", &met_UESUp);
    arbre->SetBranchAddress("metphi_UESDown", &metphi_UESDown);
    arbre->SetBranchAddress("met_UESDown", &met_UESDown);
    arbre->SetBranchAddress("metphi_UESUp", &metphi_UESUp);
    arbre->SetBranchAddress("met_responseUp", &met_responseUp);
    arbre->SetBranchAddress("metphi_responseUp", &metphi_responseUp);
    arbre->SetBranchAddress("met_responseDown", &met_responseDown);
    arbre->SetBranchAddress("metphi_responseDown", &metphi_responseDown);
    arbre->SetBranchAddress("met_resolutionUp", &met_resolutionUp);
    arbre->SetBranchAddress("metphi_resolutionUp", &metphi_resolutionUp);
    arbre->SetBranchAddress("met_resolutionDown", &met_resolutionDown);
    arbre->SetBranchAddress("metphi_resolutionDown", &metphi_resolutionDown);
    arbre->SetBranchAddress("metphi_JetRelativeSampleDown", &metphi_JetRelativeSampleDown);
    arbre->SetBranchAddress("met_JetRelativeSampleDown", &met_JetRelativeSampleDown);
    arbre->SetBranchAddress("metphi_JetRelativeSampleUp", &metphi_JetRelativeSampleUp);
    arbre->SetBranchAddress("met_JetRelativeSampleUp", &met_JetRelativeSampleUp);
    arbre->SetBranchAddress("metphi_JetRelativeBalDown", &metphi_JetRelativeBalDown);
    arbre->SetBranchAddress("met_JetRelativeBalDown", &met_JetRelativeBalDown);
    arbre->SetBranchAddress("metphi_JetRelativeBalUp", &metphi_JetRelativeBalUp);
    arbre->SetBranchAddress("met_JetRelativeBalUp", &met_JetRelativeBalUp);
    arbre->SetBranchAddress("m_sv_ResponseDown", &m_sv_ResponseDown);
    arbre->SetBranchAddress("m_sv_ResponseUp", &m_sv_ResponseUp);
    arbre->SetBranchAddress("m_sv_ResolutionDown", &m_sv_ResolutionDown);
    arbre->SetBranchAddress("m_sv_ResolutionUp", &m_sv_ResolutionUp);
    arbre->SetBranchAddress("m_sv_JetRelativeSampleUp", &m_sv_JetRelativeSampleUp);
    arbre->SetBranchAddress("m_sv_JetRelativeSampleDown", &m_sv_JetRelativeSampleDown);
    arbre->SetBranchAddress("m_sv_JetRelativeBalUp", &m_sv_JetRelativeBalUp);
    arbre->SetBranchAddress("m_sv_JetRelativeBalDown", &m_sv_JetRelativeBalDown);
    arbre->SetBranchAddress("njets", &njets);
    arbre->SetBranchAddress("jpt_1", &jpt_1);
    arbre->SetBranchAddress("jeta_1", &jeta_1);
    arbre->SetBranchAddress("jphi_1", &jphi_1);
    arbre->SetBranchAddress("jpt_2", &jpt_2);
    arbre->SetBranchAddress("jeta_2", &jeta_2);
    arbre->SetBranchAddress("jphi_2", &jphi_2);
    arbre->SetBranchAddress("bpt_1", &bpt_1);
    arbre->SetBranchAddress("beta_1", &beta_1);
    arbre->SetBranchAddress("bphi_1", &bphi_1);
    arbre->SetBranchAddress("bpt_2", &bpt_2);
    arbre->SetBranchAddress("beta_2", &beta_2);
    arbre->SetBranchAddress("bphi_2", &bphi_2);
    arbre->SetBranchAddress("bflavor_1", &bflavor_1);
    arbre->SetBranchAddress("bflavor_2", &bflavor_2);
    arbre->SetBranchAddress("mjj", &mjj);
    arbre->SetBranchAddress("genweight", &genweight);
    arbre->SetBranchAddress("gen_match_1",&gen_match_1);
    arbre->SetBranchAddress("gen_match_2",&gen_match_2);
    arbre->SetBranchAddress("npu",&npu);
    arbre->SetBranchAddress("genpT",&genpT);
    arbre->SetBranchAddress("genM",&genM);
    arbre->SetBranchAddress("pt_top1",&pt_top1);
    arbre->SetBranchAddress("pt_top2",&pt_top2);
    arbre->SetBranchAddress("numGenJets",&numGenJets);
    arbre->SetBranchAddress("Flag_BadChargedCandidateFilter",&Flag_BadChargedCandidateFilter);
    arbre->SetBranchAddress("Flag_BadPFMuonFilter",&Flag_BadPFMuonFilter);
    arbre->SetBranchAddress("Flag_EcalDeadCellTriggerPrimitiveFilter",&Flag_EcalDeadCellTriggerPrimitiveFilter);
    arbre->SetBranchAddress("Flag_HBHENoiseFilter",&Flag_HBHENoiseFilter);
    arbre->SetBranchAddress("Flag_HBHENoiseIsoFilter",&Flag_HBHENoiseIsoFilter);
    arbre->SetBranchAddress("Flag_eeBadScFilter",&Flag_eeBadScFilter);
    arbre->SetBranchAddress("Flag_goodVertices",&Flag_goodVertices);
    arbre->SetBranchAddress("Flag_globalSuperTightHalo2016Filter",&Flag_globalSuperTightHalo2016Filter);
    arbre->SetBranchAddress("Flag_ecalBadCalibFilter",&Flag_ecalBadCalibFilter);
    arbre->SetBranchAddress("Flag_duplicateMuons",&Flag_duplicateMuons);
    arbre->SetBranchAddress("Flag_badMuons",&Flag_badMuons);
    arbre->SetBranchAddress("Flag_ecalBadCalibReducedMINIAODFilter",&Flag_ecalBadCalibReducedMINIAODFilter);
    arbre->SetBranchAddress("pt_1_SigmaUp", &pt_1_SigmaUp);
    arbre->SetBranchAddress("pt_1_SigmaDown", &pt_1_SigmaDown);
    arbre->SetBranchAddress("pt_1_ScaleUp", &pt_1_ScaleUp);
    arbre->SetBranchAddress("pt_1_ScaleDown", &pt_1_ScaleDown);

   bool is_ggh=(name.find("ggH") < 140);
   int nbhist=1;

   std::vector<TH2F*> h_IIOS;
   std::vector<TH2F*> h_IISS;
   std::vector<TH2F*> h_INOS;
   std::vector<TH2F*> h_INSS;
   std::vector<TH2F*> h_NIOS;
   std::vector<TH2F*> h_NISS;
   std::vector<TH2F*> h_NNOS;
   std::vector<TH2F*> h_NNSS;

   std::vector<TH1F*> h0_IIOS;
   std::vector<TH1F*> h0_IISS;
   std::vector<TH1F*> h0_INOS;
   std::vector<TH1F*> h0_INSS;
   std::vector<TH1F*> h0_NIOS;
   std::vector<TH1F*> h0_NISS;
   std::vector<TH1F*> h0_NNOS;
   std::vector<TH1F*> h0_NNSS;

   std::vector<TH1F*> h1_IIOS;
   std::vector<TH1F*> h1_IISS;
   std::vector<TH1F*> h1_INOS;
   std::vector<TH1F*> h1_INSS;
   std::vector<TH1F*> h1_NIOS;
   std::vector<TH1F*> h1_NISS;
   std::vector<TH1F*> h1_NNOS;
   std::vector<TH1F*> h1_NNSS;

   std::vector<TH1F*> h2_IIOS;
   std::vector<TH1F*> h2_IISS;
   std::vector<TH1F*> h2_INOS;
   std::vector<TH1F*> h2_INSS;
   std::vector<TH1F*> h2_NIOS;
   std::vector<TH1F*> h2_NISS;
   std::vector<TH1F*> h2_NNOS;
   std::vector<TH1F*> h2_NNSS;

   float bins_0[] = {0.3,2.5,3,3.5,4,4.5,5,5.5};
   int  binnum_0 = sizeof(bins_0)/sizeof(Float_t) - 1;
   float bins_1[] = {10,15,25,100};
   int  binnum_1 = sizeof(bins_1)/sizeof(Float_t) - 1;
   float bins_2[] = {10,15,25,35,100};
   int  binnum_2 = sizeof(bins_2)/sizeof(Float_t) - 1;


   for (int k=0; k<nbhist; ++k){

        ostringstream NS0IIOS; NS0IIOS << "h_IIOS" << k;
        h_IIOS.push_back(new TH2F (NS0IIOS.str().c_str(),"InvMa",binnum_1,bins_1,binnum_2,bins_2)); h_IIOS[k]->Sumw2();
        ostringstream NS0IISS; NS0IISS << "h_IISS" << k;
        h_IISS.push_back(new TH2F (NS0IISS.str().c_str(),"InvMa",binnum_1,bins_1,binnum_2,bins_2)); h_IISS[k]->Sumw2();
        ostringstream NS0INOS; NS0INOS << "h_INOS" << k;
        h_INOS.push_back(new TH2F (NS0INOS.str().c_str(),"InvMa",binnum_1,bins_1,binnum_2,bins_2)); h_INOS[k]->Sumw2();
        ostringstream NS0INSS; NS0INSS << "h_INSS" << k;
        h_INSS.push_back(new TH2F (NS0INSS.str().c_str(),"InvMa",binnum_1,bins_1,binnum_2,bins_2)); h_INSS[k]->Sumw2();
        ostringstream NS0NIOS; NS0NIOS << "h_NIOS" << k;
        h_NIOS.push_back(new TH2F (NS0NIOS.str().c_str(),"InvMa",binnum_1,bins_1,binnum_2,bins_2)); h_NIOS[k]->Sumw2();
        ostringstream NS0NISS; NS0NISS << "h_NISS" << k;
        h_NISS.push_back(new TH2F (NS0NISS.str().c_str(),"InvMa",binnum_1,bins_1,binnum_2,bins_2)); h_NISS[k]->Sumw2();
        ostringstream NS0NNOS; NS0NNOS << "h_NNOS" << k;
        h_NNOS.push_back(new TH2F (NS0NNOS.str().c_str(),"InvMa",binnum_1,bins_1,binnum_2,bins_2)); h_NNOS[k]->Sumw2();
        ostringstream NS0NNSS; NS0NNSS << "h_NNSS" << k;
        h_NNSS.push_back(new TH2F (NS0NNSS.str().c_str(),"InvMa",binnum_1,bins_1,binnum_2,bins_2)); h_NNSS[k]->Sumw2();

        ostringstream HNS0IIOS; HNS0IIOS << "h0_IIOS" << k;
        h0_IIOS.push_back(new TH1F (HNS0IIOS.str().c_str(),"InvMa",12,2.,6.)); h0_IIOS[k]->Sumw2();
        ostringstream HNS0IISS; HNS0IISS << "h0_IISS" << k;
        h0_IISS.push_back(new TH1F (HNS0IISS.str().c_str(),"InvMa",12,2.,6.)); h0_IISS[k]->Sumw2();
        ostringstream HNS0INOS; HNS0INOS << "h0_INOS" << k;
        h0_INOS.push_back(new TH1F (HNS0INOS.str().c_str(),"InvMa",12,2.,6.)); h0_INOS[k]->Sumw2();
        ostringstream HNS0INSS; HNS0INSS << "h0_INSS" << k;
        h0_INSS.push_back(new TH1F (HNS0INSS.str().c_str(),"InvMa",12,2.,6.)); h0_INSS[k]->Sumw2();
        ostringstream HNS0NIOS; HNS0NIOS << "h0_NIOS" << k;
        h0_NIOS.push_back(new TH1F (HNS0NIOS.str().c_str(),"InvMa",12,2.,6.)); h0_NIOS[k]->Sumw2();
        ostringstream HNS0NISS; HNS0NISS << "h0_NISS" << k;
        h0_NISS.push_back(new TH1F (HNS0NISS.str().c_str(),"InvMa",12,2.,6.)); h0_NISS[k]->Sumw2();
        ostringstream HNS0NNOS; HNS0NNOS << "h0_NNOS" << k;
        h0_NNOS.push_back(new TH1F (HNS0NNOS.str().c_str(),"InvMa",12,2.,6.)); h0_NNOS[k]->Sumw2();
        ostringstream HNS0NNSS; HNS0NNSS << "h0_NNSS" << k;
        h0_NNSS.push_back(new TH1F (HNS0NNSS.str().c_str(),"InvMa",12,2.,6.)); h0_NNSS[k]->Sumw2();

        ostringstream HNS1IIOS; HNS1IIOS << "h1_IIOS" << k;
        h1_IIOS.push_back(new TH1F (HNS1IIOS.str().c_str(),"InvMa",9,0.3,5.5)); h1_IIOS[k]->Sumw2();
        ostringstream HNS1IISS; HNS1IISS << "h1_IISS" << k;
        h1_IISS.push_back(new TH1F (HNS1IISS.str().c_str(),"InvMa",9,0.3,5.5)); h1_IISS[k]->Sumw2();
        ostringstream HNS1INOS; HNS1INOS << "h1_INOS" << k;
        h1_INOS.push_back(new TH1F (HNS1INOS.str().c_str(),"InvMa",9,0.3,5.5)); h1_INOS[k]->Sumw2();
        ostringstream HNS1INSS; HNS1INSS << "h1_INSS" << k;
        h1_INSS.push_back(new TH1F (HNS1INSS.str().c_str(),"InvMa",9,0.3,5.5)); h1_INSS[k]->Sumw2();
        ostringstream HNS1NIOS; HNS1NIOS << "h1_NIOS" << k;
        h1_NIOS.push_back(new TH1F (HNS1NIOS.str().c_str(),"InvMa",9,0.3,5.5)); h1_NIOS[k]->Sumw2();
        ostringstream HNS1NISS; HNS1NISS << "h1_NISS" << k;
        h1_NISS.push_back(new TH1F (HNS1NISS.str().c_str(),"InvMa",9,0.3,5.5)); h1_NISS[k]->Sumw2();
        ostringstream HNS1NNOS; HNS1NNOS << "h1_NNOS" << k;
        h1_NNOS.push_back(new TH1F (HNS1NNOS.str().c_str(),"InvMa",9,0.3,5.5)); h1_NNOS[k]->Sumw2();
        ostringstream HNS1NNSS; HNS1NNSS << "h1_NNSS" << k;
        h1_NNSS.push_back(new TH1F (HNS1NNSS.str().c_str(),"InvMa",9,0.3,5.5)); h1_NNSS[k]->Sumw2();

        ostringstream HNS2IIOS; HNS2IIOS << "h2_IIOS" << k;
        h2_IIOS.push_back(new TH1F (HNS2IIOS.str().c_str(),"InvMa",9,0.3,5.5)); h2_IIOS[k]->Sumw2();
        ostringstream HNS2IISS; HNS2IISS << "h2_IISS" << k;
        h2_IISS.push_back(new TH1F (HNS2IISS.str().c_str(),"InvMa",9,0.3,5.5)); h2_IISS[k]->Sumw2();
        ostringstream HNS2INOS; HNS2INOS << "h2_INOS" << k;
        h2_INOS.push_back(new TH1F (HNS2INOS.str().c_str(),"InvMa",9,0.3,5.5)); h2_INOS[k]->Sumw2();
        ostringstream HNS2INSS; HNS2INSS << "h2_INSS" << k;
        h2_INSS.push_back(new TH1F (HNS2INSS.str().c_str(),"InvMa",9,0.3,5.5)); h2_INSS[k]->Sumw2();
        ostringstream HNS2NIOS; HNS2NIOS << "h2_NIOS" << k;
        h2_NIOS.push_back(new TH1F (HNS2NIOS.str().c_str(),"InvMa",9,0.3,5.5)); h2_NIOS[k]->Sumw2();
        ostringstream HNS2NISS; HNS2NISS << "h2_NISS" << k;
        h2_NISS.push_back(new TH1F (HNS2NISS.str().c_str(),"InvMa",9,0.3,5.5)); h2_NISS[k]->Sumw2();
        ostringstream HNS2NNOS; HNS2NNOS << "h2_NNOS" << k;
        h2_NNOS.push_back(new TH1F (HNS2NNOS.str().c_str(),"InvMa",9,0.3,5.5)); h2_NNOS[k]->Sumw2();
        ostringstream HNS2NNSS; HNS2NNSS << "h2_NNSS" << k;
        h2_NNSS.push_back(new TH1F (HNS2NNSS.str().c_str(),"InvMa",9,0.3,5.5)); h2_NNSS[k]->Sumw2();

     }

   float bins_pte[] = {10,15,25,35,100};
   int  binnum_pte = sizeof(bins_pte)/sizeof(Float_t) - 1;
   float bins_ptm[] = {10,15,25,100};
   int  binnum_ptm = sizeof(bins_ptm)/sizeof(Float_t) - 1;

   TH2F* closureOS0 = new TH2F("closureOS0","closureOS0",binnum_ptm,bins_ptm,binnum_pte,bins_pte); closureOS0->Sumw2();
   TH2F* closureSS0 = new TH2F("closureSS0","closureSS0",binnum_ptm,bins_ptm,binnum_pte,bins_pte); closureSS0->Sumw2();
   TH2F* closureOS1 = new TH2F("closureOS1","closureOS1",binnum_ptm,bins_ptm,binnum_pte,bins_pte); closureOS1->Sumw2();
   TH2F* closureSS1 = new TH2F("closureSS1","closureSS1",binnum_ptm,bins_ptm,binnum_pte,bins_pte); closureSS1->Sumw2();
   TH2F* closureOS2 = new TH2F("closureOS2","closureOS2",binnum_ptm,bins_ptm,binnum_pte,bins_pte); closureOS2->Sumw2();
   TH2F* closureSS2 = new TH2F("closureSS2","closureSS2",binnum_ptm,bins_ptm,binnum_pte,bins_pte); closureSS2->Sumw2();
   TH2F* closureOS = new TH2F("closureOS","closureOS",binnum_ptm,bins_ptm,binnum_pte,bins_pte); closureOS->Sumw2();
   TH2F* closureSS = new TH2F("closureSS","closureSS",binnum_ptm,bins_ptm,binnum_pte,bins_pte); closureSS->Sumw2();

    reweight::LumiReWeighting* LumiWeights_12;
    LumiWeights_12 = new reweight::LumiReWeighting("MC_Moriond17_PU25ns_V1.root", "Data_Pileup_2016_271036-284044_80bins.root", "pileup", "pileup");


    TFile *fZ=new TFile("zpt_weights_2016_BtoH.root");
    TH2F *histZ=(TH2F*) fZ->Get("zptmass_histo");

   TFile fwmc("htt_scalefactors_legacy_2016.root");
   RooWorkspace *wmc = (RooWorkspace*)fwmc.Get("w");
   fwmc.Close();

   ScaleFactor * myScaleFactor_IdIsoEle = new ScaleFactor();
   myScaleFactor_IdIsoEle->init_ScaleFactor("LeptonEfficiencies/Electron/Run2016_legacy/Electron_Run2016_legacy_IdIso.root");
   ScaleFactor * myScaleFactor_IdIsoMu = new ScaleFactor();
   myScaleFactor_IdIsoMu->init_ScaleFactor("LeptonEfficiencies/Muon/Run2016_legacy/Muon_Run2016_legacy_IdIso.root");

   TFile *fosss= new TFile("osss_em_2016.root","r");
   TF1 *osss_0jet=(TF1*) fosss->Get("OSSS_qcd_0jet_2016");
   TF1 *osss_1jet=(TF1*) fosss->Get("OSSS_qcd_1jet_2016");
   TF1 *osss_2jet=(TF1*) fosss->Get("OSSS_qcd_2jet_2016");

   TString postfixMC[63]={"","_CMS_JetEta0to3_2016Down","_CMS_JetEta0to3_2016Up","_CMS_JetEta0to5_2016Down","_CMS_JetEta0to5_2016Up","_CMS_JetEta3to5_2016Down","_CMS_JetEta3to5_2016Up","_CMS_JetRelativeSample_2016Down","_CMS_JetRelativeSample_2016Up","_CMS_JetRelativeBal_2016Down","_CMS_JetRelativeBal_2016Up","_CMS_JetEC2_2016Down","_CMS_JetEC2_2016Up","_CMS_scale_met_unclustered_2016Down","_CMS_scale_met_unclustered_2016Up","_CMS_htt_boson_reso_met_0jet_2016Down","_CMS_htt_boson_reso_met_0jet_2016Up","_CMS_htt_boson_reso_met_1jet_2016Down","_CMS_htt_boson_reso_met_1jet_2016Up","_CMS_htt_boson_reso_met_2jet_2016Down","_CMS_htt_boson_reso_met_2jet_2016Up","_CMS_htt_boson_scale_met_0jet_2016Down","_CMS_htt_boson_scale_met_0jet_2016Up","_CMS_htt_boson_scale_met_1jet_2016Down","_CMS_htt_boson_scale_met_1jet_2016Up","_CMS_htt_boson_scale_met_2jet_2016Down","_CMS_htt_boson_scale_met_2jet_2016Up","_CMS_htt_ttbarShapeDown","_CMS_htt_ttbarShapeUp","_CMS_htt_dyShapeDown","_CMS_htt_dyShapeUp","_CMS_scale_e_2016Down","_CMS_scale_e_2016Up","_CMS_smear_e_2016Down","_CMS_smear_e_2016Up","_CMS_scale_m_etam2p4tom2p1_2016Down","_CMS_scale_m_etam2p4tom2p1_2016Up","_CMS_scale_m_etam2p1tom1p2_2016Down","_CMS_scale_m_etam2p1tom1p2_2016Up","_CMS_scale_m_etam1p2to1p2_2016Down","_CMS_scale_m_etam1p2to1p2_2016Up","_CMS_scale_m_eta1p2to2p1_2016Down","_CMS_scale_m_eta1p2to2p1_2016Up","_CMS_scale_m_eta2p1to2p4_2016Down","_CMS_scale_m_eta2p1to2p4_2016Up","_THU_ggH_MuUp","_THU_ggH_MuDown","_THU_ggH_ResUp","_THU_ggH_ResDown","_THU_ggH_Mig01Up","_THU_ggH_Mig01Down","_THU_ggH_Mig12Up","_THU_ggH_Mig12Down","_THU_ggH_VBF2jUp","_THU_ggH_VBF2jDown","_THU_ggH_VBF3jUp","_THU_ggH_VBF3jDown","_THU_ggH_PT60Up","_THU_ggH_PT60Down","_THU_ggH_PT120Up","_THU_ggH_PT120Down","_THU_ggH_qmtopUp","_THU_ggH_qmtopDown"};

   TString postfixQCD[10]={"_CMS_QCD_njet0_intercept_2016Down","_CMS_QCD_njet0_intercept_2016Up","_CMS_QCD_njet0_slope_2016Down","_CMS_QCD_njet0_slope_2016Up","_CMS_QCD_njet1_intercept_2016Down","_CMS_QCD_njet1_intercept_2016Up","_CMS_QCD_njet1_slope_2016Down","_CMS_QCD_njet1_slope_2016Up","_CMS_QCD_antiiso_2016Down","_CMS_QCD_antiiso_2016Up"};

   Int_t nentries_wtn = (Int_t) arbre->GetEntries();
   for (Int_t i = 0; i < nentries_wtn; i++) {
        arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

	if (fabs(eta_1)>2.5) continue;
        if (fabs(eta_2)>2.4) continue;

        if (Flag_goodVertices) continue;
        if (Flag_globalSuperTightHalo2016Filter) continue;
        if (Flag_HBHENoiseFilter) continue;
        if (Flag_HBHENoiseIsoFilter) continue;
        if (Flag_EcalDeadCellTriggerPrimitiveFilter) continue;
        if (Flag_BadPFMuonFilter) continue;
        if ((sample=="data_obs" or sample=="embedded") && Flag_eeBadScFilter) continue;

        bool triggerMu8E23=(passMu8E23 && matchMu8E23_1 && filterMu8E23_1 && matchMu8E23_2 && pt_1>23.5 && pt_2>9.5);
        bool triggerMu23E12=(passMu23E12 && matchMu23E12_1 && filterMu23E12_1 && matchMu23E12_2 && pt_1>12.5 && pt_2>23.5);
        //bool triggerMu8E23=(passMu8E23 && pt_1>23.5 && pt_2>9.5);
        //bool triggerMu23E12=(passMu23E12 && pt_1>12.5 && pt_2>23.5);
        if (sample=="data_obs" && run>=278820){
           triggerMu8E23=(passMu8E23DZ && matchMu8E23DZ_1 && filterMu8E23DZ_1 && matchMu8E23DZ_2 && filterMu8E23DZ_2 && pt_1>23 && pt_2>9);
           triggerMu23E12=(passMu23E12DZ && matchMu23E12DZ_1 && filterMu23E12DZ_1 && matchMu23E12DZ_2 && filterMu23E12DZ_2 && pt_1>12 && pt_2>23);
        }

        if (!triggerMu8E23 && !triggerMu23E12) continue;

        bool isII=(iso_1<0.15 && iso_2<0.20);
        bool isIN=(iso_1<0.15 && iso_2>0.20 && iso_2<0.50);
        bool isNI=(iso_1>0.15 && iso_1<0.50 && iso_2<0.20);
        bool isNN=(iso_1>0.15 && iso_1<0.50 && iso_2>0.20 && iso_2<0.50);

	TLorentzVector mymu; 
	mymu.SetPtEtaPhiM(pt_2,eta_2,phi_2,m_2);
        TLorentzVector myele;
        myele.SetPtEtaPhiM(pt_1,eta_1,phi_1,m_1);

	if (mymu.DeltaR(myele)<0.3) continue;

        /*if (sample=="W"){
            weight=28.84;
            if (numGenJets==1) weight=6.092;
            else if (numGenJets==2) weight=3.481;
            else if (numGenJets==3) weight=1.067;
            else if (numGenJets==4) weight=2.251;
        }
        if (sample=="DY"){
            weight=1.532;
            if (numGenJets==1)
                weight=0.4805;
            else if (numGenJets==2)
                weight=0.463;
            else if (numGenJets==3)
                weight=0.524;
            else if (numGenJets==4)
                weight=0.341;
        }*/

        if (sample=="W"){ //20nov
            weight=25.42858;
            if (numGenJets==1) weight=5.7747;
            else if (numGenJets==2) weight=1.79323;
            else if (numGenJets==3) weight=0.68005;
            else if (numGenJets==4) weight=0.80296;
        }
        if (sample=="DY" or sample=="Z"){
            weight=1.4953;
            if (numGenJets==1) weight=0.54145;
            else if (numGenJets==2) weight=0.5050;
            else if (numGenJets==3) weight=0.50586;
            else if (numGenJets==4) weight=0.41489;
        }



	float aweight=genweight*weight*LumiWeights_12->weight(npu);
        if (sample=="embedded") aweight=genweight;

	TLorentzVector mymet;
	mymet.SetPtEtaPhiM(met,0,metphi,0);

	if (sample=="data_obs") aweight=1.0;

	// Top pT reweighting
        float topfactor=1.0;
        if (name=="TT"){
           float pttop1=pt_top1;
           if (pttop1>472) pttop1=472;
           float pttop2=pt_top2;
           if (pttop2>472) pttop2=472;
           topfactor=sqrt(exp(0.088-0.00087*pttop1+0.00000092*pttop1*pttop1)*exp(0.088-0.00087*pttop2+0.00000092*pttop2*pttop2));
           aweight*=topfactor;
        }

        float zptweight=1.0;
        if (sample!="embedded" && sample!="data_obs"){
          /*aweight=aweight*myScaleFactor_IdIsoEle->get_ScaleFactor(pt_1,eta_1);
          aweight=aweight*myScaleFactor_IdIsoMu->get_ScaleFactor(pt_2,eta_2);
          aweight=aweight*bweight;
          zptweight=histZ->GetBinContent(histZ->GetXaxis()->FindBin(genM),histZ->GetYaxis()->FindBin(genpT));
          if (sample=="DY") aweight=aweight*zptweight;*/

          wmc->var("z_gen_mass")->setVal(genM);
          wmc->var("z_gen_pt")->setVal(genpT);
          zptweight=wmc->function("zptmass_weight_nom")->getVal();
          if (sample=="DY" or sample=="Z") aweight=aweight*zptweight;

          wmc->var("m_pt")->setVal(mymu.Pt());
          wmc->var("m_eta")->setVal(mymu.Eta());
          wmc->var("m_iso")->setVal(iso_2);
          wmc->var("e_pt")->setVal(myele.Pt());
          wmc->var("e_eta")->setVal(myele.Eta());
          wmc->var("e_iso")->setVal(iso_1);
          //aweight=aweight*myScaleFactor_IdIsoEle->get_ScaleFactor(pt_1,eta_1);
          //aweight=aweight*myScaleFactor_IdIsoMu->get_ScaleFactor(pt_2,eta_2);
          aweight=aweight*wmc->function("m_trk_ratio")->getVal();
          aweight=aweight*wmc->function("e_trk_ratio")->getVal();
          aweight=aweight*wmc->function("m_idiso_ic_ratio")->getVal();
          aweight=aweight*wmc->function("e_idiso_ic_ratio")->getVal();

          aweight=aweight*bweight;

          float probData =wmc->function("m_trg_8_ic_data")->getVal()*wmc->function("e_trg_23_ic_data")->getVal()*int(triggerMu8E23)+wmc->function("m_trg_23_ic_data")->getVal()*wmc->function("e_trg_12_ic_data")->getVal()*int(triggerMu23E12)-wmc->function("e_trg_23_ic_data")->getVal()*wmc->function("m_trg_23_ic_data")->getVal()*int(triggerMu8E23 && triggerMu23E12);
          float probMC =wmc->function("m_trg_8_ic_mc")->getVal()*wmc->function("e_trg_23_ic_mc")->getVal()*int(triggerMu8E23)+wmc->function("m_trg_23_ic_mc")->getVal()*wmc->function("e_trg_12_ic_mc")->getVal()*int(triggerMu23E12)-wmc->function("e_trg_23_ic_mc")->getVal()*wmc->function("m_trg_23_ic_mc")->getVal()*int(triggerMu8E23 && triggerMu23E12);
          float sf_trg=1.0;
          if (probMC==0) sf_trg=1.0;
          else sf_trg=probData/probMC;
          aweight=aweight*sf_trg;

        }

	//************************* Fill histograms **********************
	TLorentzVector myrawele=myele;
        TLorentzVector myrawmu=mymu;
        TLorentzVector myrawmet=mymet;
	for (int k=0; k<nbhist; ++k){

	   float weight2=1.0;

           if (nbtag>0) continue;
           if (nbtagL>1) continue;

	   // reset all variables before any systematic shift
	   myele=myrawele;
           mymu=myrawmu;
	   mymet=myrawmet;

	   if (mymu.Pt()<24 and myele.Pt()<24) continue;
	   if (mymu.Pt()<10) continue;
	   if (myele.Pt()<12) continue;

           float norm_zeta=norm_F(myele.Px()/myele.Pt()+mymu.Px()/mymu.Pt(),myele.Py()/myele.Pt()+mymu.Py()/mymu.Pt());
           float x_zeta= (myele.Px()/myele.Pt()+mymu.Px()/mymu.Pt())/norm_zeta;
           float y_zeta= (myele.Py()/myele.Pt()+mymu.Py()/mymu.Pt())/norm_zeta;
           float p_zeta_mis=mymet.Px()*x_zeta+mymet.Py()*y_zeta;
           float pzeta_vis=(myele.Px()+mymu.Px())*x_zeta+(myele.Py()+mymu.Py())*y_zeta;
	   float dzeta=p_zeta_mis-0.85*pzeta_vis;
	   bool pass_dzeta=dzeta>-30;

           float mt=TMass_F((myele+mymu).Pt(),mymet.Pt(),(myele+mymu).Px(),mymet.Px(),(myele+mymu).Py(),mymet.Py());
	   float pass_mt=(mt<60);

           float sssf=2.5;
           if (njets==0) sssf=osss_0jet->Eval(myele.DeltaR(mymu));
           else if (njets==1) sssf=osss_1jet->Eval(myele.DeltaR(mymu));
           else sssf=sssf=osss_2jet->Eval(myele.DeltaR(mymu));

           if (njets==0){
               if (isII && q_1*q_2<0)
                   h0_IIOS[k]->Fill(myele.DeltaR(mymu),aweight*weight2);
               if (isII && q_1*q_2>0)
                   h0_IISS[k]->Fill(myele.DeltaR(mymu),aweight*weight2);
               if (isIN && q_1*q_2<0)
                   h0_INOS[k]->Fill(myele.DeltaR(mymu),aweight*weight2);
               if (isIN && q_1*q_2>0)
                   h0_INSS[k]->Fill(myele.DeltaR(mymu),aweight*weight2);
               if (isNI && q_1*q_2<0)
                   h0_NIOS[k]->Fill(myele.DeltaR(mymu),aweight*weight2);
               if (isNI && q_1*q_2>0)
                   h0_NISS[k]->Fill(myele.DeltaR(mymu),aweight*weight2);
               if (isNN && q_1*q_2<0)
                   h0_NNOS[k]->Fill(myele.DeltaR(mymu),aweight*weight2);
               if (isNN && q_1*q_2>0)
                   h0_NNSS[k]->Fill(myele.DeltaR(mymu),aweight*weight2);
	       if (isIN && q_1*q_2<0)
		   closureOS0->Fill(mymu.Pt(),myele.Pt(),aweight*weight2);
               if (isIN && q_1*q_2>0)
                   closureSS0->Fill(mymu.Pt(),myele.Pt(),aweight*weight2*sssf);
           }
           if (njets==1){
               if (isII && q_1*q_2<0)
                   h1_IIOS[k]->Fill(myele.DeltaR(mymu),aweight*weight2);
               if (isII && q_1*q_2>0)
                   h1_IISS[k]->Fill(myele.DeltaR(mymu),aweight*weight2);
               if (isIN && q_1*q_2<0)
                   h1_INOS[k]->Fill(myele.DeltaR(mymu),aweight*weight2);
               if (isIN && q_1*q_2>0)
                   h1_INSS[k]->Fill(myele.DeltaR(mymu),aweight*weight2);
               if (isNI && q_1*q_2<0)
                   h1_NIOS[k]->Fill(myele.DeltaR(mymu),aweight*weight2);
               if (isNI && q_1*q_2>0)
                   h1_NISS[k]->Fill(myele.DeltaR(mymu),aweight*weight2);
               if (isNN && q_1*q_2<0)
                   h1_NNOS[k]->Fill(myele.DeltaR(mymu),aweight*weight2);
               if (isNN && q_1*q_2>0)
                   h1_NNSS[k]->Fill(myele.DeltaR(mymu),aweight*weight2);
               if (isIN && q_1*q_2<0)
                   closureOS1->Fill(mymu.Pt(),myele.Pt(),aweight*weight2);
               if (isIN && q_1*q_2>0)
                   closureSS1->Fill(mymu.Pt(),myele.Pt(),aweight*weight2*sssf);
           }
           if (njets>1){
               if (isII && q_1*q_2<0)
                   h2_IIOS[k]->Fill(myele.DeltaR(mymu),aweight*weight2);
               if (isII && q_1*q_2>0)
                   h2_IISS[k]->Fill(myele.DeltaR(mymu),aweight*weight2);
               if (isIN && q_1*q_2<0)
                   h2_INOS[k]->Fill(myele.DeltaR(mymu),aweight*weight2);
               if (isIN && q_1*q_2>0)
                   h2_INSS[k]->Fill(myele.DeltaR(mymu),aweight*weight2);
               if (isNI && q_1*q_2<0)
                   h2_NIOS[k]->Fill(myele.DeltaR(mymu),aweight*weight2);
               if (isNI && q_1*q_2>0)
                   h2_NISS[k]->Fill(myele.DeltaR(mymu),aweight*weight2);
               if (isNN && q_1*q_2<0)
                   h2_NNOS[k]->Fill(myele.DeltaR(mymu),aweight*weight2);
               if (isNN && q_1*q_2>0)
                   h2_NNSS[k]->Fill(myele.DeltaR(mymu),aweight*weight2);
               if (isIN && q_1*q_2<0)
                   closureOS2->Fill(mymu.Pt(),myele.Pt(),aweight*weight2);
               if (isIN && q_1*q_2>0)
                   closureSS2->Fill(mymu.Pt(),myele.Pt(),aweight*weight2*sssf);
           }

           if (njets>-1){
               float mupt=mymu.Pt();
               if (mupt>100) mupt=99;
               float ept=myele.Pt();
               if (ept>100) ept=99;
               if (isII && q_1*q_2<0)
                   h_IIOS[k]->Fill(mupt,ept,aweight*weight2);
               if (isII && q_1*q_2>0)
                   h_IISS[k]->Fill(mupt,ept,aweight*weight2);
               if (isIN && q_1*q_2<0)
                   h_INOS[k]->Fill(mupt,ept,aweight*weight2);
               if (isIN && q_1*q_2>0)
                   h_INSS[k]->Fill(mupt,ept,aweight*weight2);
               if (isNI && q_1*q_2<0)
                   h_NIOS[k]->Fill(mupt,ept,aweight*weight2);
               if (isNI && q_1*q_2>0)
                   h_NISS[k]->Fill(mupt,ept,aweight*weight2);
               if (isNN && q_1*q_2<0)
                   h_NNOS[k]->Fill(mupt,ept,aweight*weight2);
               if (isNN && q_1*q_2>0)
                   h_NNSS[k]->Fill(mupt,ept,aweight*weight2);
               if (isIN && q_1*q_2<0)
                   closureOS->Fill(mupt,ept,aweight*weight2);
               if (isIN && q_1*q_2>0)
                   closureSS->Fill(mupt,ept,aweight*weight2*sssf);
           }

	} // end of loop over nbhist

    } // end of loop over events
    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();

    TString postfix="";

    TDirectory *d_closureOS0 =fout->mkdir("closureOS0");
    d_closureOS0->cd();
    closureOS0->SetName(name.c_str());
    closureOS0->Write();
    TDirectory *d_closureSS0 =fout->mkdir("closureSS0");
    d_closureSS0->cd();
    closureSS0->SetName(name.c_str());
    closureSS0->Write();
    TDirectory *d_closureOS1 =fout->mkdir("closureOS1");
    d_closureOS1->cd();
    closureOS1->SetName(name.c_str());
    closureOS1->Write();
    TDirectory *d_closureSS1 =fout->mkdir("closureSS1");
    d_closureSS1->cd();
    closureSS1->SetName(name.c_str());
    closureSS1->Write();
    TDirectory *d_closureOS2 =fout->mkdir("closureOS2");
    d_closureOS2->cd();
    closureOS2->SetName(name.c_str());
    closureOS2->Write();
    TDirectory *d_closureSS2 =fout->mkdir("closureSS2");
    d_closureSS2->cd();
    closureSS2->SetName(name.c_str());
    closureSS2->Write();
    TDirectory *d_closureOS =fout->mkdir("closureOS");
    d_closureOS->cd();
    closureOS->SetName(name.c_str());
    closureOS->Write();
    TDirectory *d_closureSS =fout->mkdir("closureSS");
    d_closureSS->cd();
    closureSS->SetName(name.c_str());
    closureSS->Write();


    TDirectory *IIOS0 =fout->mkdir("IIOS0");
    IIOS0->cd();
    for (int k=0; k<nbhist; ++k){
       postfix=postfixMC[k];
cout<<h0_IIOS[k]->Integral()<<endl;
       h0_IIOS[k]->SetName(name.c_str()+postfix);
       h0_IIOS[k]->Write();
    }
    TDirectory *IISS0 =fout->mkdir("IISS0");
    IISS0->cd();
    for (int k=0; k<nbhist; ++k){
       postfix=postfixMC[k];
       h0_IISS[k]->SetName(name.c_str()+postfix);
       h0_IISS[k]->Write();
    }
    TDirectory *NIOS0 =fout->mkdir("NIOS0");
    NIOS0->cd();
    for (int k=0; k<nbhist; ++k){
       postfix=postfixMC[k];
       h0_NIOS[k]->SetName(name.c_str()+postfix);
       h0_NIOS[k]->Write();
    }
    TDirectory *NISS0 =fout->mkdir("NISS0");
    NISS0->cd();
    for (int k=0; k<nbhist; ++k){
       postfix=postfixMC[k];
       h0_NISS[k]->SetName(name.c_str()+postfix);
       h0_NISS[k]->Write();
    }
    TDirectory *INOS0 =fout->mkdir("INOS0");
    INOS0->cd();
    for (int k=0; k<nbhist; ++k){
       postfix=postfixMC[k];
       h0_INOS[k]->SetName(name.c_str()+postfix);
       h0_INOS[k]->Write();
    }
    TDirectory *INSS0 =fout->mkdir("INSS0");
    INSS0->cd();
    for (int k=0; k<nbhist; ++k){
       postfix=postfixMC[k];
       h0_INSS[k]->SetName(name.c_str()+postfix);
       h0_INSS[k]->Write();
    }
    TDirectory *NNOS0 =fout->mkdir("NNOS0");
    NNOS0->cd();
    for (int k=0; k<nbhist; ++k){
       postfix=postfixMC[k];
       h0_NNOS[k]->SetName(name.c_str()+postfix);
       h0_NNOS[k]->Write();
    }
    TDirectory *NNSS0 =fout->mkdir("NNSS0");
    NNSS0->cd();
    for (int k=0; k<nbhist; ++k){
       postfix=postfixMC[k];
       h0_NNSS[k]->SetName(name.c_str()+postfix);
       h0_NNSS[k]->Write();
    }

    TDirectory *IIOS1 =fout->mkdir("IIOS1");
    IIOS1->cd();
    for (int k=0; k<nbhist; ++k){
       postfix=postfixMC[k];
       h1_IIOS[k]->SetName(name.c_str()+postfix);
       h1_IIOS[k]->Write();
    }
    TDirectory *IISS1 =fout->mkdir("IISS1");
    IISS1->cd();
    for (int k=0; k<nbhist; ++k){
       postfix=postfixMC[k];
       h1_IISS[k]->SetName(name.c_str()+postfix);
       h1_IISS[k]->Write();
    }
    TDirectory *NIOS1 =fout->mkdir("NIOS1");
    NIOS1->cd();
    for (int k=0; k<nbhist; ++k){
       postfix=postfixMC[k];
       h1_NIOS[k]->SetName(name.c_str()+postfix);
       h1_NIOS[k]->Write();
    }
    TDirectory *NISS1 =fout->mkdir("NISS1");
    NISS1->cd();
    for (int k=0; k<nbhist; ++k){
       postfix=postfixMC[k];
       h1_NISS[k]->SetName(name.c_str()+postfix);
       h1_NISS[k]->Write();
    }
    TDirectory *INOS1 =fout->mkdir("INOS1");
    INOS1->cd();
    for (int k=0; k<nbhist; ++k){
       postfix=postfixMC[k];
       h1_INOS[k]->SetName(name.c_str()+postfix);
       h1_INOS[k]->Write();
    }
    TDirectory *INSS1 =fout->mkdir("INSS1");
    INSS1->cd();
    for (int k=0; k<nbhist; ++k){
       postfix=postfixMC[k];
       h1_INSS[k]->SetName(name.c_str()+postfix);
       h1_INSS[k]->Write();
    }
    TDirectory *NNOS1 =fout->mkdir("NNOS1");
    NNOS1->cd();
    for (int k=0; k<nbhist; ++k){
       postfix=postfixMC[k];
       h1_NNOS[k]->SetName(name.c_str()+postfix);
       h1_NNOS[k]->Write();
    }
    TDirectory *NNSS1 =fout->mkdir("NNSS1");
    NNSS1->cd();
    for (int k=0; k<nbhist; ++k){
       postfix=postfixMC[k];
       h1_NNSS[k]->SetName(name.c_str()+postfix);
       h1_NNSS[k]->Write();
    }

    TDirectory *IIOS2 =fout->mkdir("IIOS2");
    IIOS2->cd();
    for (int k=0; k<nbhist; ++k){
       postfix=postfixMC[k];
       h2_IIOS[k]->SetName(name.c_str()+postfix);
       h2_IIOS[k]->Write();
    }
    TDirectory *IISS2 =fout->mkdir("IISS2");
    IISS2->cd();
    for (int k=0; k<nbhist; ++k){
       postfix=postfixMC[k];
       h2_IISS[k]->SetName(name.c_str()+postfix);
       h2_IISS[k]->Write();
    }
    TDirectory *NIOS2 =fout->mkdir("NIOS2");
    NIOS2->cd();
    for (int k=0; k<nbhist; ++k){
       postfix=postfixMC[k];
       h2_NIOS[k]->SetName(name.c_str()+postfix);
       h2_NIOS[k]->Write();
    }
    TDirectory *NISS2 =fout->mkdir("NISS2");
    NISS2->cd();
    for (int k=0; k<nbhist; ++k){
       postfix=postfixMC[k];
       h2_NISS[k]->SetName(name.c_str()+postfix);
       h2_NISS[k]->Write();
    }
    TDirectory *INOS2 =fout->mkdir("INOS2");
    INOS2->cd();
    for (int k=0; k<nbhist; ++k){
       postfix=postfixMC[k];
       h2_INOS[k]->SetName(name.c_str()+postfix);
       h2_INOS[k]->Write();
    }
    TDirectory *INSS2 =fout->mkdir("INSS2");
    INSS2->cd();
    for (int k=0; k<nbhist; ++k){
       postfix=postfixMC[k];
       h2_INSS[k]->SetName(name.c_str()+postfix);
       h2_INSS[k]->Write();
    }
    TDirectory *NNOS2 =fout->mkdir("NNOS2");
    NNOS2->cd();
    for (int k=0; k<nbhist; ++k){
       postfix=postfixMC[k];
       h2_NNOS[k]->SetName(name.c_str()+postfix);
       h2_NNOS[k]->Write();
    }
    TDirectory *NNSS2 =fout->mkdir("NNSS2");
    NNSS2->cd();
    for (int k=0; k<nbhist; ++k){
       postfix=postfixMC[k];
       h2_NNSS[k]->SetName(name.c_str()+postfix);
       h2_NNSS[k]->Write();
    }

    TDirectory *IIOS =fout->mkdir("IIOS");
    IIOS->cd();
    for (int k=0; k<nbhist; ++k){
       postfix=postfixMC[k];
       h_IIOS[k]->SetName(name.c_str()+postfix);
       h_IIOS[k]->Write();
    }
    TDirectory *IISS =fout->mkdir("IISS");
    IISS->cd();
    for (int k=0; k<nbhist; ++k){
       postfix=postfixMC[k];
       h_IISS[k]->SetName(name.c_str()+postfix);
       h_IISS[k]->Write();
    }
    TDirectory *NIOS =fout->mkdir("NIOS");
    NIOS->cd();
    for (int k=0; k<nbhist; ++k){
       postfix=postfixMC[k];
       h_NIOS[k]->SetName(name.c_str()+postfix);
       h_NIOS[k]->Write();
    }
    TDirectory *NISS =fout->mkdir("NISS");
    NISS->cd();
    for (int k=0; k<nbhist; ++k){
       postfix=postfixMC[k];
       h_NISS[k]->SetName(name.c_str()+postfix);
       h_NISS[k]->Write();
    }
    TDirectory *INOS =fout->mkdir("INOS");
    INOS->cd();
    for (int k=0; k<nbhist; ++k){
       postfix=postfixMC[k];
       h_INOS[k]->SetName(name.c_str()+postfix);
       h_INOS[k]->Write();
    }
    TDirectory *INSS =fout->mkdir("INSS");
    INSS->cd();
    for (int k=0; k<nbhist; ++k){
       postfix=postfixMC[k];
       h_INSS[k]->SetName(name.c_str()+postfix);
       h_INSS[k]->Write();
    }
    TDirectory *NNOS =fout->mkdir("NNOS");
    NNOS->cd();
    for (int k=0; k<nbhist; ++k){
       postfix=postfixMC[k];
       h_NNOS[k]->SetName(name.c_str()+postfix);
       h_NNOS[k]->Write();
    }
    TDirectory *NNSS =fout->mkdir("NNSS");
    NNSS->cd();
    for (int k=0; k<nbhist; ++k){
       postfix=postfixMC[k];
       h_NNSS[k]->SetName(name.c_str()+postfix);
       h_NNSS[k]->Write();
    }


    fout->Close();
} 


