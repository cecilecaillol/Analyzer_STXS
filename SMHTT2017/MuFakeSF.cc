#include <TH2.h>
#include <TStyle.h>
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
#include "PostProcessing.h"
#include "mt_Tree.h"
#include "LumiReweightingStandAlone.h"
#include "HTTutilities/Jet2TauFakes/interface/FakeFactor.h"
#include "HTTutilities/Jet2TauFakes/interface/WrapperTGraph.h"
#include "HTTutilities/Jet2TauFakes/interface/WrapperTH2F.h"
#include "HTTutilities/Jet2TauFakes/interface/WrapperTH3D.h"
#include "HTTutilities/Jet2TauFakes/interface/WrapperTFormula.h"
#include "HTTutilities/Jet2TauFakes/interface/IFunctionWrapper.h"
#include "TauAnalysisTools/TauTriggerSFs/interface/TauTriggerSFs2017.h"
#include "RooWorkspace.h"
#include "RooRealVar.h"
#include "RooFunctor.h"
#include "ComputeWG1Unc.h"
#include "SFtautrigger.h"
#include "btagSF.h"

using namespace std;

int main(int argc, char** argv) {

    std::string input = *(argv + 1);
    std::string output = *(argv + 2);
    std::string sample = *(argv + 3);
    std::string name = *(argv + 4);
    std::string tauisolation = *(argv + 5);
    std::string antimuon = *(argv + 6);

    float dm=0;
    float minpt=0;
    float maxpt=2000;
    float mineta=0;
    float maxeta=20;
    if (argc > 1) {
        dm = atof(argv[7]);
        minpt = atof(argv[8]);
        maxpt = atof(argv[9]);
        mineta = atof(argv[10]);
        maxeta = atof(argv[11]);
    }

    TFile *f_Double = new TFile(input.c_str());
    cout<<"XXXXXXXXXXXXX "<<input.c_str()<<" XXXXXXXXXXXX"<<endl;
    TTree *arbre = (TTree*) f_Double->Get("mutau_tree");
    TH1F* nbevt = (TH1F*) f_Double->Get("nevents");
    float ngen = nbevt->GetBinContent(2);

    float xs=1.0; float weight=1.0; float luminosity=41522.0;
    if (sample=="DYL" or sample=="DYT" or sample=="DY" or sample=="ZL" or sample=="ZTT" or sample=="ZJ" or sample=="ZLL"){ xs=6225.42; weight=luminosity*xs/ngen;}
    if (sample=="DYlow"){ xs=21658.0; weight=luminosity*xs/ngen;}
    else if (sample=="TT" or sample=="TTT" or sample=="TTJ") {xs=831.76; weight=luminosity*xs/ngen;}
    else if (sample=="TTTo2L2Nu") {xs=88.29; weight=luminosity*xs/ngen;}
    else if (sample=="TTToSemiLeptonic") {xs=365.35; weight=luminosity*xs/ngen;}
    else if (sample=="TTToHadronic") {xs=377.96; weight=luminosity*xs/ngen;}
    else if (sample=="W") {xs=61526.7; weight=luminosity*xs/ngen;}
    else if (sample=="data_obs"){weight=1.0;}
    else if (sample=="embedded"){weight=1.0;}
    else if (sample=="WZ1L1Nu2Q") {xs=11.66; weight=luminosity*xs/ngen;}
    else if (sample=="WZ1L3Nu") {xs=3.293; weight=luminosity*xs/ngen;}
    else if (sample=="WZJets") {xs=5.26; weight=luminosity*xs/ngen;}
    else if (sample=="WZ3LNu") {xs=5.052; weight=luminosity*xs/ngen;}
    else if (sample=="WZ2L2Q") {xs=6.331; weight=luminosity*xs/ngen;}
    else if (sample=="WW1L1Nu2Q") {xs=49.997; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ4L") {xs=1.325; weight=luminosity*xs/ngen;}
    else if (sample=="VV2L2Nu") {xs=13.97; weight=luminosity*xs/ngen;}
    else if (sample=="WW2L2Nu") {xs=11.08; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ2L2Nu") {xs=0.6008; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ2L2Q") {xs=3.688; weight=luminosity*xs/ngen;}
    else if (sample=="WW4Q") {xs=47.73; weight=luminosity*xs/ngen;}
    else if (sample=="WWLNuQQ") {xs=45.99; weight=luminosity*xs/ngen;}
    else if (sample=="ST_tW_antitop") {xs=35.85; weight=luminosity*xs/ngen;}
    else if (sample=="ST_tW_top") {xs=35.85; weight=luminosity*xs/ngen;}
    else if (sample=="ST_t_antitop") {xs=80.95; weight=luminosity*xs/ngen;}
    else if (sample=="ST_t_top") {xs=136.02; weight=luminosity*xs/ngen;}
    else if (sample=="ggH_htt125") {xs=48.58*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="qqH_htt125") {xs=3.782*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="WplusH125") {xs=0.840*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="WminusH125") {xs=0.5328*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="ZH125") {xs=0.8839*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ") {xs=12.14; weight=luminosity*xs/ngen;}
    else if (sample=="WZ") {xs=23.24; weight=luminosity*xs/ngen;}
    else if (sample=="WW") {xs=118.7; weight=luminosity*xs/ngen;}
    else if (sample=="WGLNu") {xs=489.0; weight=luminosity*xs/ngen;}
    else if (sample=="WGstarMuMu") {xs=2.793; weight=luminosity*xs/ngen;}
    else if (sample=="WGstarEE") {xs=3.526; weight=luminosity*xs/ngen;}
    else if (sample=="EWKWminus") {xs=23.24; weight=luminosity*xs/ngen;}
    else if (sample=="EWKWplus") {xs=29.59; weight=luminosity*xs/ngen;}
    else if (sample=="EWKZLL" or sample=="EWKZLL_TT" or sample=="EWKZLL_J" or sample=="EWKZLL_L" or sample=="EWKZLL_LL") {xs=4.321; weight=luminosity*xs/ngen;}
    else if (sample=="EWKZNuNu" or sample=="EWKZNuNu_TT" or sample=="EWKZNuNu_J" or sample=="EWKZNuNu_L" or sample=="EWKZNuNu_LL") {xs=10.66; weight=luminosity*xs/ngen;}

    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(10);

    arbre->SetBranchAddress("Rivet_higgsPt", &Rivet_higgsPt);
    arbre->SetBranchAddress("Rivet_nJets30", &Rivet_nJets30);
    arbre->SetBranchAddress("Rivet_stage0_cat", &Rivet_stage0_cat);
    arbre->SetBranchAddress("Rivet_stage1p1_cat", &Rivet_stage1p1_cat);
    arbre->SetBranchAddress("Rivet_stage1_cat_pTjet30GeV", &Rivet_stage1_cat_pTjet30GeV);

    arbre->SetBranchAddress("passMu27", &passMu27);
    arbre->SetBranchAddress("passMu24", &passMu24);

    arbre->SetBranchAddress("matchMu27_1", &matchMu27_1);
    arbre->SetBranchAddress("matchMu24_1", &matchMu24_1);
    arbre->SetBranchAddress("filterMu27_1", &filterMu27_1);
    arbre->SetBranchAddress("filterMu24_1", &filterMu24_1);

    arbre->SetBranchAddress("run", &run);
    arbre->SetBranchAddress("lumi", &lumi);
    arbre->SetBranchAddress("evt", &evt);
    arbre->SetBranchAddress("npv", &npv);
    arbre->SetBranchAddress("pt_1", &pt_1);
    arbre->SetBranchAddress("phi_1", &phi_1);
    arbre->SetBranchAddress("eta_1", &eta_1);
    arbre->SetBranchAddress("iso_1", &iso_1);
    arbre->SetBranchAddress("m_1", &m_1);
    arbre->SetBranchAddress("q_1", &q_1);
    arbre->SetBranchAddress("nbtag", &nbtag);
    arbre->SetBranchAddress("q_2", &q_2);
    arbre->SetBranchAddress("pt_2", &pt_2);
    arbre->SetBranchAddress("eta_2", &eta_2);
    arbre->SetBranchAddress("m_2", &m_2);
    arbre->SetBranchAddress("phi_2", &phi_2);
    arbre->SetBranchAddress("met", &met);
    arbre->SetBranchAddress("metphi", &metphi);
    arbre->SetBranchAddress("met", &met);
    arbre->SetBranchAddress("met_UESDown", &met_UESDown);
    arbre->SetBranchAddress("met_UESUp", &met_UESUp);
    arbre->SetBranchAddress("metphi_UESDown", &metphi_UESDown);
    arbre->SetBranchAddress("metphi_UESUp", &metphi_UESUp);
    arbre->SetBranchAddress("met_responseUp", &met_responseUp);
    arbre->SetBranchAddress("metphi_responseUp", &metphi_responseUp);
    arbre->SetBranchAddress("met_responseDown", &met_responseDown);
    arbre->SetBranchAddress("metphi_responseDown", &metphi_responseDown);
    arbre->SetBranchAddress("met_resolutionUp", &met_resolutionUp);
    arbre->SetBranchAddress("metphi_resolutionUp", &metphi_resolutionUp);
    arbre->SetBranchAddress("met_resolutionDown", &met_resolutionDown);
    arbre->SetBranchAddress("metphi_resolutionDown", &metphi_resolutionDown);
    arbre->SetBranchAddress("metphi_JetEta0to3Down", &metphi_JetEta0to3Down);
    arbre->SetBranchAddress("met_JetEta0to3Down", &met_JetEta0to3Down);
    arbre->SetBranchAddress("metphi_JetEta0to3Up", &metphi_JetEta0to3Up);
    arbre->SetBranchAddress("met_JetEta0to3Up", &met_JetEta0to3Up);
    arbre->SetBranchAddress("metphi_JetEta0to5Down", &metphi_JetEta0to5Down);
    arbre->SetBranchAddress("met_JetEta0to5Down", &met_JetEta0to5Down);
    arbre->SetBranchAddress("metphi_JetEta0to5Up", &metphi_JetEta0to5Up);
    arbre->SetBranchAddress("met_JetEta0to5Up", &met_JetEta0to5Up);
    arbre->SetBranchAddress("metphi_JetEta3to5Down", &metphi_JetEta3to5Down);
    arbre->SetBranchAddress("met_JetEta3to5Down", &met_JetEta3to5Down);
    arbre->SetBranchAddress("metphi_JetEta3to5Up", &metphi_JetEta3to5Up);
    arbre->SetBranchAddress("met_JetEta3to5Up", &met_JetEta3to5Up);
    arbre->SetBranchAddress("metphi_JetRelativeSampleDown", &metphi_JetRelativeSampleDown);
    arbre->SetBranchAddress("met_JetRelativeSampleDown", &met_JetRelativeSampleDown);
    arbre->SetBranchAddress("metphi_JetRelativeSampleUp", &metphi_JetRelativeSampleUp);
    arbre->SetBranchAddress("met_JetRelativeSampleUp", &met_JetRelativeSampleUp);
    arbre->SetBranchAddress("metphi_JetRelativeBalDown", &metphi_JetRelativeBalDown);
    arbre->SetBranchAddress("met_JetRelativeBalDown", &met_JetRelativeBalDown);
    arbre->SetBranchAddress("metphi_JetRelativeBalUp", &metphi_JetRelativeBalUp);
    arbre->SetBranchAddress("met_JetRelativeBalUp", &met_JetRelativeBalUp);
    arbre->SetBranchAddress("metphi_JetEC2Down", &metphi_JetEC2Down);
    arbre->SetBranchAddress("met_JetEC2Down", &met_JetEC2Down);
    arbre->SetBranchAddress("metphi_JetEC2Up", &metphi_JetEC2Up);
    arbre->SetBranchAddress("met_JetEC2Up", &met_JetEC2Up);
    arbre->SetBranchAddress("njets", &njets);
    arbre->SetBranchAddress("njets_JetEta0to3Down", &njets_JetEta0to3Down);
    arbre->SetBranchAddress("njets_JetEta0to3Up", &njets_JetEta0to3Up);
    arbre->SetBranchAddress("njets_JetEC2Down", &njets_JetEC2Down);
    arbre->SetBranchAddress("njets_JetEC2Up", &njets_JetEC2Up);
    arbre->SetBranchAddress("njets_JetRelativeSampleDown", &njets_JetRelativeSampleDown);
    arbre->SetBranchAddress("njets_JetRelativeSampleUp", &njets_JetRelativeSampleUp);
    arbre->SetBranchAddress("njets_JetRelativeBalDown", &njets_JetRelativeBalDown);
    arbre->SetBranchAddress("njets_JetRelativeBalUp", &njets_JetRelativeBalUp);
    arbre->SetBranchAddress("njets_JetEta0to5Down", &njets_JetEta0to5Down);
    arbre->SetBranchAddress("njets_JetEta0to5Up", &njets_JetEta0to5Up);
    arbre->SetBranchAddress("njets_JetEta3to5Down", &njets_JetEta3to5Down);
    arbre->SetBranchAddress("njets_JetEta3to5Up", &njets_JetEta3to5Up);
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
    arbre->SetBranchAddress("mjj_JetEta0to3Down", &mjj_JetEta0to3Down);
    arbre->SetBranchAddress("mjj_JetEta0to3Up", &mjj_JetEta0to3Up);
    arbre->SetBranchAddress("mjj_JetEC2Down", &mjj_JetEC2Down);
    arbre->SetBranchAddress("mjj_JetEC2Up", &mjj_JetEC2Up);
    arbre->SetBranchAddress("mjj_JetEta3to5Down", &mjj_JetEta3to5Down);
    arbre->SetBranchAddress("mjj_JetEta3to5Up", &mjj_JetEta3to5Up);
    arbre->SetBranchAddress("mjj_JetEta0to5Down", &mjj_JetEta0to5Down);
    arbre->SetBranchAddress("mjj_JetEta0to5Up", &mjj_JetEta0to5Up);
    arbre->SetBranchAddress("mjj_JetRelativeBalDown", &mjj_JetRelativeBalDown);
    arbre->SetBranchAddress("mjj_JetRelativeBalUp", &mjj_JetRelativeBalUp);
    arbre->SetBranchAddress("mjj_JetRelativeSampleDown", &mjj_JetRelativeSampleDown);
    arbre->SetBranchAddress("mjj_JetRelativeSampleUp", &mjj_JetRelativeSampleUp);
    arbre->SetBranchAddress("genweight", &genweight);
    arbre->SetBranchAddress("byVLooseIsolationMVArun2v2DBoldDMwLT_2",&byVLooseIsolationMVArun2v2DBoldDMwLT_2);
    arbre->SetBranchAddress("byLooseIsolationMVArun2v2DBoldDMwLT_2",&byLooseIsolationMVArun2v2DBoldDMwLT_2);
    arbre->SetBranchAddress("byMediumIsolationMVArun2v2DBoldDMwLT_2",&byMediumIsolationMVArun2v2DBoldDMwLT_2);
    arbre->SetBranchAddress("byTightIsolationMVArun2v2DBoldDMwLT_2",&byTightIsolationMVArun2v2DBoldDMwLT_2);
    arbre->SetBranchAddress("byVTightIsolationMVArun2v2DBoldDMwLT_2",&byVTightIsolationMVArun2v2DBoldDMwLT_2);
    //arbre->SetBranchAddress("byLooseDeep_2",&byLooseDeep_2);
    //arbre->SetBranchAddress("byMediumDeep_2",&byMediumDeep_2);
    //arbre->SetBranchAddress("byTightDeep_2",&byTightDeep_2);
    //arbre->SetBranchAddress("byVTightDeep_2",&byVTightDeep_2);
    //arbre->SetBranchAddress("byTightDPF_2",&byTightDPF_2);
    arbre->SetBranchAddress("byVVVLooseDeepVSjet_2",&byVVVLooseDeepVSjet_2);
    arbre->SetBranchAddress("byVVLooseDeepVSjet_2",&byVVLooseDeepVSjet_2);
    arbre->SetBranchAddress("byVLooseDeepVSjet_2",&byVLooseDeepVSjet_2);
    arbre->SetBranchAddress("byLooseDeepVSjet_2",&byLooseDeepVSjet_2);
    arbre->SetBranchAddress("byMediumDeepVSjet_2",&byMediumDeepVSjet_2);
    arbre->SetBranchAddress("byTightDeepVSjet_2",&byTightDeepVSjet_2);
    arbre->SetBranchAddress("byVTightDeepVSjet_2",&byVTightDeepVSjet_2);
    arbre->SetBranchAddress("byVVVLooseDeepVSe_2",&byVVVLooseDeepVSe_2);
    arbre->SetBranchAddress("byVVLooseDeepVSe_2",&byVVLooseDeepVSe_2);
    arbre->SetBranchAddress("byVLooseDeepVSe_2",&byVLooseDeepVSe_2);
    arbre->SetBranchAddress("byLooseDeepVSe_2",&byLooseDeepVSe_2);
    arbre->SetBranchAddress("byMediumDeepVSe_2",&byMediumDeepVSe_2);
    arbre->SetBranchAddress("byTightDeepVSe_2",&byTightDeepVSe_2);
    arbre->SetBranchAddress("byVTightDeepVSe_2",&byVTightDeepVSe_2);
    arbre->SetBranchAddress("byVVVLooseDeepVSmu_2",&byVVVLooseDeepVSmu_2);
    arbre->SetBranchAddress("byVVLooseDeepVSmu_2",&byVVLooseDeepVSmu_2);
    arbre->SetBranchAddress("byVLooseDeepVSmu_2",&byVLooseDeepVSmu_2);
    arbre->SetBranchAddress("byLooseDeepVSmu_2",&byLooseDeepVSmu_2);
    arbre->SetBranchAddress("byMediumDeepVSmu_2",&byMediumDeepVSmu_2);
    arbre->SetBranchAddress("byTightDeepVSmu_2",&byTightDeepVSmu_2);
    arbre->SetBranchAddress("byVTightDeepVSmu_2",&byVTightDeepVSmu_2);
    arbre->SetBranchAddress("byIsolationMVA3oldDMwLTraw_2",&byIsolationMVA3oldDMwLTraw_2);
    arbre->SetBranchAddress("l2_decayMode",&l2_decayMode);
    arbre->SetBranchAddress("againstElectronVLooseMVA6_2",&againstElectronVLooseMVA6_2);
    arbre->SetBranchAddress("againstElectronVTightMVA6_2",&againstElectronVTightMVA6_2);
    arbre->SetBranchAddress("againstMuonTight3_2",&againstMuonTight3_2);
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

   int nbhist=1;
   if (sample=="data_obs") nbhist=1;
   else nbhist=15;

   std::vector<TH1F*> h0T_OS;
   std::vector<TH1F*> h0T_SS;
   std::vector<TH1F*> h0T_SSAI;
   std::vector<TH1F*> h0T_OSAI;
   std::vector<TH1F*> h0T_MTOS;
   std::vector<TH1F*> h0T_MTSS;

   std::vector<TH1F*> h0L_OS;
   std::vector<TH1F*> h0L_SS;
   std::vector<TH1F*> h0L_SSAI;
   std::vector<TH1F*> h0L_OSAI;
   std::vector<TH1F*> h0L_MTOS;
   std::vector<TH1F*> h0L_MTSS;

   std::vector<TH1F*> h0J_OS;
   std::vector<TH1F*> h0J_SS;
   std::vector<TH1F*> h0J_SSAI;
   std::vector<TH1F*> h0J_OSAI;
   std::vector<TH1F*> h0J_MTOS;
   std::vector<TH1F*> h0J_MTSS;

   std::vector<TH1F*> h1T_OS;
   std::vector<TH1F*> h1T_SS;
   std::vector<TH1F*> h1T_SSAI;
   std::vector<TH1F*> h1T_OSAI;
   std::vector<TH1F*> h1T_MTOS;
   std::vector<TH1F*> h1T_MTSS;

   std::vector<TH1F*> h1L_OS;
   std::vector<TH1F*> h1L_SS;
   std::vector<TH1F*> h1L_SSAI;
   std::vector<TH1F*> h1L_OSAI;
   std::vector<TH1F*> h1L_MTOS;
   std::vector<TH1F*> h1L_MTSS;

   std::vector<TH1F*> h1J_OS;
   std::vector<TH1F*> h1J_SS;
   std::vector<TH1F*> h1J_SSAI;
   std::vector<TH1F*> h1J_OSAI;
   std::vector<TH1F*> h1J_MTOS;
   std::vector<TH1F*> h1J_MTSS;

   for (int k=0; k<nbhist; ++k){
        ostringstream HNS0tauOS; HNS0tauOS << "h0T_OS" << k;
        h0T_OS.push_back(new TH1F (HNS0tauOS.str().c_str(),"InvMa",15,80,110)); h0T_OS[k]->Sumw2();
        ostringstream HNS0jetOS; HNS0jetOS << "h0T_SS" << k;
        h0T_SS.push_back(new TH1F (HNS0jetOS.str().c_str(),"InvMa",15,80,110)); h0T_SS[k]->Sumw2();
        ostringstream HNS0ellOS; HNS0ellOS << "h0T_OSAI" << k;
        h0T_OSAI.push_back(new TH1F (HNS0ellOS.str().c_str(),"InvMa",15,80,110)); h0T_OSAI[k]->Sumw2();
        ostringstream HNS0tauAI; HNS0tauAI << "h0T_SSAI" << k;
        h0T_SSAI.push_back(new TH1F (HNS0tauAI.str().c_str(),"InvMa",15,80,110)); h0T_SSAI[k]->Sumw2();
        ostringstream HNS0MTOS; HNS0MTOS << "h0T_MTOS" << k;
        h0T_MTOS.push_back(new TH1F (HNS0MTOS.str().c_str(),"InvMa",16,90,170)); h0T_MTOS[k]->Sumw2();
        ostringstream HNS0MTSS; HNS0MTSS << "h0T_MTSS" << k;
        h0T_MTSS.push_back(new TH1F (HNS0MTSS.str().c_str(),"InvMa",16,90,170)); h0T_MTSS[k]->Sumw2();

        ostringstream HNS0LtauOS; HNS0LtauOS << "h0L_OS" << k;
        h0L_OS.push_back(new TH1F (HNS0LtauOS.str().c_str(),"InvMa",15,80,110)); h0L_OS[k]->Sumw2();
        ostringstream HNS0LjetOS; HNS0LjetOS << "h0L_SS" << k;
        h0L_SS.push_back(new TH1F (HNS0LjetOS.str().c_str(),"InvMa",15,80,110)); h0L_SS[k]->Sumw2();
        ostringstream HNS0LellOS; HNS0LellOS << "h0L_OSAI" << k;
        h0L_OSAI.push_back(new TH1F (HNS0LellOS.str().c_str(),"InvMa",15,80,110)); h0L_OSAI[k]->Sumw2();
        ostringstream HNS0LtauAI; HNS0LtauAI << "h0L_SSAI" << k;
        h0L_SSAI.push_back(new TH1F (HNS0LtauAI.str().c_str(),"InvMa",15,80,110)); h0L_SSAI[k]->Sumw2();
        ostringstream HNS0LMTOS; HNS0LMTOS << "h0L_MTOS" << k;
        h0L_MTOS.push_back(new TH1F (HNS0LMTOS.str().c_str(),"InvMa",16,90,170)); h0L_MTOS[k]->Sumw2();
        ostringstream HNS0LMTSS; HNS0LMTSS << "h0L_MTSS" << k;
        h0L_MTSS.push_back(new TH1F (HNS0LMTSS.str().c_str(),"InvMa",16,90,170)); h0L_MTSS[k]->Sumw2();

        ostringstream HNS0JtauOS; HNS0JtauOS << "h0J_OS" << k;
        h0J_OS.push_back(new TH1F (HNS0JtauOS.str().c_str(),"InvMa",15,80,110)); h0J_OS[k]->Sumw2();
        ostringstream HNS0JjetOS; HNS0JjetOS << "h0J_SS" << k;
        h0J_SS.push_back(new TH1F (HNS0JjetOS.str().c_str(),"InvMa",15,80,110)); h0J_SS[k]->Sumw2();
        ostringstream HNS0JellOS; HNS0JellOS << "h0J_OSAI" << k;
        h0J_OSAI.push_back(new TH1F (HNS0JellOS.str().c_str(),"InvMa",15,80,110)); h0J_OSAI[k]->Sumw2();
        ostringstream HNS0JtauAI; HNS0JtauAI << "h0J_SSAI" << k;
        h0J_SSAI.push_back(new TH1F (HNS0JtauAI.str().c_str(),"InvMa",15,80,110)); h0J_SSAI[k]->Sumw2();
        ostringstream HNS0JMTOS; HNS0JMTOS << "h0J_MTOS" << k;
        h0J_MTOS.push_back(new TH1F (HNS0JMTOS.str().c_str(),"InvMa",16,90,170)); h0J_MTOS[k]->Sumw2();
        ostringstream HNS0JMTSS; HNS0JMTSS << "h0J_MTSS" << k;
        h0J_MTSS.push_back(new TH1F (HNS0JMTSS.str().c_str(),"InvMa",16,90,170)); h0J_MTSS[k]->Sumw2();

        ostringstream HNS1tauOS; HNS1tauOS << "h1T_OS" << k;
        h1T_OS.push_back(new TH1F (HNS1tauOS.str().c_str(),"InvMa",5,85,100)); h1T_OS[k]->Sumw2();
        ostringstream HNS1jetOS; HNS1jetOS << "h1T_SS" << k;
        h1T_SS.push_back(new TH1F (HNS1jetOS.str().c_str(),"InvMa",5,85,100)); h1T_SS[k]->Sumw2();
        ostringstream HNS1ellOS; HNS1ellOS << "h1T_OSAI" << k;
        h1T_OSAI.push_back(new TH1F (HNS1ellOS.str().c_str(),"InvMa",5,85,100)); h1T_OSAI[k]->Sumw2();
        ostringstream HNS1tauAI; HNS1tauAI << "h1T_SSAI" << k;
        h1T_SSAI.push_back(new TH1F (HNS1tauAI.str().c_str(),"InvMa",5,85,100)); h1T_SSAI[k]->Sumw2();
        ostringstream HNS1MTOS; HNS1MTOS << "h1T_MTOS" << k;
        h1T_MTOS.push_back(new TH1F (HNS1MTOS.str().c_str(),"InvMa",16,90,170)); h1T_MTOS[k]->Sumw2();
        ostringstream HNS1MTSS; HNS1MTSS << "h1T_MTSS" << k;
        h1T_MTSS.push_back(new TH1F (HNS1MTSS.str().c_str(),"InvMa",16,90,170)); h1T_MTSS[k]->Sumw2();

        ostringstream HNS1LtauOS; HNS1LtauOS << "h1L_OS" << k;
        h1L_OS.push_back(new TH1F (HNS1LtauOS.str().c_str(),"InvMa",5,85,100)); h1L_OS[k]->Sumw2();
        ostringstream HNS1LjetOS; HNS1LjetOS << "h1L_SS" << k;
        h1L_SS.push_back(new TH1F (HNS1LjetOS.str().c_str(),"InvMa",5,85,100)); h1L_SS[k]->Sumw2();
        ostringstream HNS1LellOS; HNS1LellOS << "h1L_OSAI" << k;
        h1L_OSAI.push_back(new TH1F (HNS1LellOS.str().c_str(),"InvMa",5,85,100)); h1L_OSAI[k]->Sumw2();
        ostringstream HNS1LtauAI; HNS1LtauAI << "h1L_SSAI" << k;
        h1L_SSAI.push_back(new TH1F (HNS1LtauAI.str().c_str(),"InvMa",5,85,100)); h1L_SSAI[k]->Sumw2();
        ostringstream HNS1LMTOS; HNS1LMTOS << "h1L_MTOS" << k;
        h1L_MTOS.push_back(new TH1F (HNS1LMTOS.str().c_str(),"InvMa",16,90,170)); h1L_MTOS[k]->Sumw2();
        ostringstream HNS1LMTSS; HNS1LMTSS << "h1L_MTSS" << k;
        h1L_MTSS.push_back(new TH1F (HNS1LMTSS.str().c_str(),"InvMa",16,90,170)); h1L_MTSS[k]->Sumw2();

        ostringstream HNS1JtauOS; HNS1JtauOS << "h1J_OS" << k;
        h1J_OS.push_back(new TH1F (HNS1JtauOS.str().c_str(),"InvMa",5,85,100)); h1J_OS[k]->Sumw2();
        ostringstream HNS1JjetOS; HNS1JjetOS << "h1J_SS" << k;
        h1J_SS.push_back(new TH1F (HNS1JjetOS.str().c_str(),"InvMa",5,85,100)); h1J_SS[k]->Sumw2();
        ostringstream HNS1JellOS; HNS1JellOS << "h1J_OSAI" << k;
        h1J_OSAI.push_back(new TH1F (HNS1JellOS.str().c_str(),"InvMa",5,85,100)); h1J_OSAI[k]->Sumw2();
        ostringstream HNS1JtauAI; HNS1JtauAI << "h1J_SSAI" << k;
        h1J_SSAI.push_back(new TH1F (HNS1JtauAI.str().c_str(),"InvMa",5,85,100)); h1J_SSAI[k]->Sumw2();
        ostringstream HNS1JMTOS; HNS1JMTOS << "h1J_MTOS" << k;
        h1J_MTOS.push_back(new TH1F (HNS1JMTOS.str().c_str(),"InvMa",16,90,170)); h1J_MTOS[k]->Sumw2();
        ostringstream HNS1JMTSS; HNS1JMTSS << "h1J_MTSS" << k;
        h1J_MTSS.push_back(new TH1F (HNS1JMTSS.str().c_str(),"InvMa",16,90,170)); h1J_MTSS[k]->Sumw2();
     }

   reweight::LumiReWeighting* LumiWeights_12;
   LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#VBFHToTauTau_M125_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
   if (sample=="W1") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3#MINIAODSIM", "pileup");
   else if (sample=="W2") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#W2JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v5#MINIAODSIM", "pileup");
   else if (sample=="ST_t_antitop") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
   else if (sample=="DY4") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_v2_94X_mc2017_realistic_v14-v2#MINIAODSIM", "pileup");
   else if (sample=="W") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3#MINIAODSIM", "pileup");
   else if (sample=="DY") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017RECOSIMstep_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
   else if (sample=="WW") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#WW_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
   else if (sample=="WplusH125") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#WplusHToTauTau_M125_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
   else if (sample=="WZ") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#WZ_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
   else if (sample=="DY4") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
   else if (sample=="ST_tW_top") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2#MINIAODSIM", "pileup");
   else if (sample=="WminusH125") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#WminusHToTauTau_M125_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
   else if (sample=="ST_tW_antitop") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2#MINIAODSIM", "pileup");
   else if (sample=="W3") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
   else if (sample=="ZH125") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#ZHToTauTau_M125_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");


   TFile fw("htt_scalefactors_legacy_2017.root");
   RooWorkspace *w = (RooWorkspace*)fw.Get("w");
   fw.Close();

   TFile fwmc("htt_scalefactors_legacy_2017.root");
   RooWorkspace *wmc = (RooWorkspace*)fwmc.Get("w");
   fwmc.Close();

   ScaleFactor * myScaleFactor_trgMu2735 = new ScaleFactor();
   myScaleFactor_trgMu2735->init_ScaleFactor("LeptonEfficiencies/Muon/Run2017/Muon_IsoMu24orIsoMu27.root");
   ScaleFactor * myScaleFactor_trgEle24 = new ScaleFactor();
   myScaleFactor_trgEle24->init_ScaleFactor("LeptonEfficiencies/Muon/Run2017/Muon_IsoMu24orIsoMu27.root");
   ScaleFactor * myScaleFactor_IdIso = new ScaleFactor();
   myScaleFactor_IdIso->init_ScaleFactor("LeptonEfficiencies/Muon/Run2017/Muon_IdIso_IsoLt0.15_eff_RerecoFall17.root");

   TFile *ftauid = new TFile("TauID_SF_pt_DeepTau2017v2p1VSjet_2017ReReco.root");
   TF1 *fct_tauid= (TF1*) ftauid->Get("Medium_cent");
   TF1 *fct_tauid_up= (TF1*) ftauid->Get("Medium_up");
   TF1 *fct_tauid_down= (TF1*) ftauid->Get("Medium_down");

   TString postfixMC[15]={"","_CMS_scale_t_2017Down","_CMS_scale_t_2017Up","_CMS_scale_efaket_1prong_2017Down","_CMS_scale_efaket_1prong_2017Up","_CMS_scale_efaket_1prong1pizero_2017Down","_CMS_scale_efaket_1prong1pizero_2017Up","_CMS_htt_boson_reso_met_2017Down","_CMS_htt_boson_reso_met_2017Up","_CMS_htt_boson_scale_met_2017Down","_CMS_htt_boson_scale_met_2017Up","_CMS_htt_ttbarShapeDown","_CMS_htt_ttbarShapeUp","_CMS_htt_dyShapeDown","_CMS_htt_dyShapeUp"};

   Int_t nentries_wtn = (Int_t) arbre->GetEntries();
   for (Int_t i = 0; i < nentries_wtn; i++) {
        arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

	if (l2_decayMode!=dm or fabs(eta_2)<mineta or fabs(eta_2)>=maxeta) continue;

	bool isL=(gen_match_2<5);
        bool isT=(gen_match_2==5);
        bool isJ=(gen_match_2>5);
	if (sample=="data_obs"){ isL=false; isJ=false; isT=true;}

        if (l2_decayMode==5 or l2_decayMode==6) continue;

	if (fabs(eta_1)>2.4) continue;
        if (fabs(eta_2)>2.3) continue;

        if (Flag_goodVertices) continue;
        if (Flag_globalSuperTightHalo2016Filter) continue;
        if (Flag_HBHENoiseFilter) continue;
        if (Flag_HBHENoiseIsoFilter) continue;
        if (Flag_EcalDeadCellTriggerPrimitiveFilter) continue;
        if (Flag_BadPFMuonFilter) continue;
        if ((sample=="data_obs" or sample=="embedded") && Flag_eeBadScFilter) continue;
        if (Flag_ecalBadCalibReducedMINIAODFilter) continue;

	// With loose pT cuts to do the shifts after
	bool trigger24=(passMu24 && pt_1>25 && matchMu24_1 && filterMu24_1);
        bool trigger27=(passMu27 && pt_1>28 && matchMu27_1 && filterMu27_1);
        if (!trigger27 && !trigger24) continue;
	if (nbtag>0) continue;

	// Against leptons
	if (!byVVVLooseDeepVSe_2) continue;

	// SR and CR
        float signalRegion=(byMediumDeepVSjet_2 && iso_1<0.15);
        float antiisoRegion=(byMediumDeepVSjet_2 && iso_1<0.15);

	if (tauisolation=="VVVLoose") signalRegion=(byVVVLooseDeepVSjet_2 && iso_1<0.15);
        if (tauisolation=="VVLoose") signalRegion=(byVVLooseDeepVSjet_2 && iso_1<0.15);
        if (tauisolation=="VLoose") signalRegion=(byVLooseDeepVSjet_2 && iso_1<0.15);
        if (tauisolation=="Loose") signalRegion=(byLooseDeepVSjet_2 && iso_1<0.15);
        if (tauisolation=="Medium") signalRegion=(byMediumDeepVSjet_2 && iso_1<0.15);
        if (tauisolation=="Tight") signalRegion=(byTightDeepVSjet_2 && iso_1<0.15);
        if (tauisolation=="VTight") signalRegion=(byVTightDeepVSjet_2 && iso_1<0.15);

	bool pass_antimu=byTightDeepVSmu_2;
  	if (antimuon=="VVVLoose") pass_antimu=byVVVLooseDeepVSmu_2;
        if (antimuon=="VVLoose") pass_antimu=byVVLooseDeepVSmu_2;
        if (antimuon=="VLoose") pass_antimu=byVLooseDeepVSmu_2;
        if (antimuon=="Loose") pass_antimu=byLooseDeepVSmu_2;
        if (antimuon=="Medium") pass_antimu=byMediumDeepVSmu_2;
        if (antimuon=="Tight") pass_antimu=byTightDeepVSmu_2;
        if (antimuon=="VTight") pass_antimu=byVTightDeepVSmu_2;

	// Define leptons
	TLorentzVector mytau; 
	mytau.SetPtEtaPhiM(pt_2,eta_2,phi_2,m_2);
        TLorentzVector mymu;
        mymu.SetPtEtaPhiM(pt_1,eta_1,phi_1,m_1);
	if (mymu.DeltaR(mytau)<0.5) continue;
        TLorentzVector mymet;
        mymet.SetPtEtaPhiM(met,0,metphi,0);

	// Stitching for W and DY
        if (sample=="W"){
            weight=23.8336;
            if (numGenJets==1) weight=3.1468;
            else if (numGenJets==2) weight=4.087;
            else if (numGenJets==3) weight=2.253;
            else if (numGenJets==4) weight=2.1954;
        }
        if (sample=="DY" or sample=="DYT" or sample=="DYL"){
            weight=2.58055;
            if (numGenJets==1) weight=0.71000;
            else if (numGenJets==2) weight=0.9211255;
            else if (numGenJets==3) weight=1.65081;
            else if (numGenJets==4) weight=0.21935;
        }

	// Weights
	float aweight=genweight*weight*LumiWeights_12->weight(npu);
        if (byMediumDeepVSjet_2 && sample!="embedded" && sample!="data_obs" && gen_match_2==5) aweight=aweight*fct_tauid->Eval(mytau.Pt());

	if (sample=="data_obs") aweight=1.0;

	// Top pT reweighting
        float topfactor=1.0;
        if (name=="TT"){
           float pttop1=pt_top1;
           if (pttop1>400) pttop1=400;
           float pttop2=pt_top2;
           if (pttop2>400) pttop2=400;
           topfactor=sqrt(exp(0.0615-0.0005*pttop1)*exp(0.0615-0.0005*pttop2));
           aweight*=topfactor;
        }

        float zptweight=1.0;
        if (sample!="embedded" && sample!="data_obs"){
          wmc->var("z_gen_mass")->setVal(genM);
          wmc->var("z_gen_pt")->setVal(genpT);
          zptweight=wmc->function("zptmass_weight_nom")->getVal();
          if (sample=="DY" or sample=="DYL" or sample=="DYT") aweight=aweight*zptweight;
          aweight=aweight*myScaleFactor_IdIso->get_ScaleFactor(pt_1,eta_1);
          if (trigger27 or trigger24) aweight=aweight*myScaleFactor_trgMu2735->get_ScaleFactor(pt_1,eta_1);
        }

        TLorentzVector myrawmu=mymu;
	TLorentzVector myrawtau=mytau;
        TLorentzVector myrawmet=mymet;

	for (int k=0; k<nbhist; ++k){
	   float weight2=1.0;

	   // reset all variables before any systematic shift
	   mytau=myrawtau;
           mymu=myrawmu;
	   mymet=myrawmet;

           if (sample!="data_obs"){
              if (k>0 && k<3 && gen_match_2==5){ // TES x 2
                if (k==1){mytau*=0.97; mymet=mymet+(0.03/0.97)*mytau; }
                else if (k==2){mytau*=1.03; mymet=mymet-(0.03/1.03)*mytau;}
              }
              else if (k>2 && k<7 && (gen_match_2<5)){ // mu->tau fake ES x 4
                if (k==3 && l2_decayMode==0){mytau*=0.97; mymet=mymet+(0.03/0.97)*mytau; }
                else if (k==4 && l2_decayMode==0){mytau*=1.03; mymet=mymet-(0.03/1.03)*mytau;}
                else if (k==5 && l2_decayMode==1){mytau*=0.97; mymet=mymet+(0.03/0.97)*mytau;}
                else if (k==6 && l2_decayMode==1){mytau*=1.03; mymet=mymet-(0.03/1.03)*mytau; }
              }
              else if (!(name=="ST" or name=="TT" or name=="VV") && k>6 && k<11){ // recoil x 4
                if (k==7){mymet=myrawmet; mymet.SetPtEtaPhiM(met_resolutionDown, 0, metphi_resolutionDown, 0); }
                else if (k==8){mymet=myrawmet; mymet.SetPtEtaPhiM(met_resolutionUp, 0, metphi_resolutionUp, 0);}
                else if (k==9){mymet=myrawmet; mymet.SetPtEtaPhiM(met_responseDown, 0, metphi_responseDown, 0);}
                else if (k==10){mymet=myrawmet; mymet.SetPtEtaPhiM(met_responseUp, 0, metphi_responseUp, 0); }
              }
              else if (k>10 && k<13 && (sample=="TTToHadronic" or sample=="TTTo2L2Nu" or sample=="TTToSemiLeptonic")){ //Top pt reweighting x 2
                if (k==11) weight2=1.0/topfactor;
                else if (k==12) weight2=topfactor;
              }
              else if (k>12 && k<15 && (sample=="DY" or sample=="DYL" or sample=="DYT")){ //Top pt reweighting x 2
                if (k==13) weight2=(1+0.90*(zptweight-1))/zptweight;
                else if (k==14) weight2=(1+1.10*(zptweight-1))/zptweight;
              }
           }

	   // Reapply cuts after shift
           trigger24=(passMu24 && mymu.Pt()>25 && matchMu24_1 && filterMu24_1);
           trigger27=(passMu27 && mymu.Pt()>28 && matchMu27_1 && filterMu27_1);
           if (!trigger27 && !trigger24) continue;
           if (mytau.Pt()<20) continue;
	   if (mytau.Pt()<minpt or mytau.Pt()>=maxpt) continue;

	   // Calculate mT and observables
    	   float mt=TMass_F(mymu.Pt(),mymet.Pt(),mymu.Px(),mymet.Px(),mymu.Py(),mymet.Py());
	   float var=mt;

	   // Fill SR histograms
           if (pass_antimu){
               if (q_1*q_2<0 && mt<50 && signalRegion){
                   if (isT) h0T_OS[k]->Fill((mymu+mytau).M(),aweight*weight2);
                   if (isL) h0L_OS[k]->Fill((mymu+mytau).M(),aweight*weight2);
                   if (isJ) h0J_OS[k]->Fill((mymu+mytau).M(),aweight*weight2);
               }
               if (q_1*q_2>0 && mt<50 && signalRegion){
                   if (isT) h0T_SS[k]->Fill((mymu+mytau).M(),aweight*weight2);
                   if (isL) h0L_SS[k]->Fill((mymu+mytau).M(),aweight*weight2);
                   if (isJ) h0J_SS[k]->Fill((mymu+mytau).M(),aweight*weight2);
               }
               if (q_1*q_2<0 && mt<50 && antiisoRegion){
                   if (isT) h0T_OSAI[k]->Fill((mymu+mytau).M(),aweight*weight2);
                   if (isL) h0L_OSAI[k]->Fill((mymu+mytau).M(),aweight*weight2);
                   if (isJ) h0J_OSAI[k]->Fill((mymu+mytau).M(),aweight*weight2);
               }
               if (q_1*q_2>0 && mt<50 && antiisoRegion){
                   if (isT) h0T_SSAI[k]->Fill((mymu+mytau).M(),aweight*weight2);
                   if (isL) h0L_SSAI[k]->Fill((mymu+mytau).M(),aweight*weight2);
                   if (isJ) h0J_SSAI[k]->Fill((mymu+mytau).M(),aweight*weight2);
               }
               if (q_1*q_2<0 && mt>80 && signalRegion){
                   if (isT) h0T_MTOS[k]->Fill(var,aweight*weight2);
                   if (isL) h0L_MTOS[k]->Fill(var,aweight*weight2);
                   if (isJ) h0J_MTOS[k]->Fill(var,aweight*weight2);
               }
               if (q_1*q_2>0 && mt>80 && signalRegion){
                   if (isT) h0T_MTSS[k]->Fill(var,aweight*weight2);
                   if (isL) h0L_MTSS[k]->Fill(var,aweight*weight2);
                   if (isJ) h0J_MTSS[k]->Fill(var,aweight*weight2);
               }
           }
           if (!pass_antimu){
               if (q_1*q_2<0 && mt<50 && signalRegion){
                   if (isT) h1T_OS[k]->Fill((mymu+mytau).M(),aweight*weight2);
                   if (isL) h1L_OS[k]->Fill((mymu+mytau).M(),aweight*weight2);
                   if (isJ) h1J_OS[k]->Fill((mymu+mytau).M(),aweight*weight2);
               }
               if (q_1*q_2>0 && mt<50 && signalRegion){
                   if (isT) h1T_SS[k]->Fill((mymu+mytau).M(),aweight*weight2);
                   if (isL) h1L_SS[k]->Fill((mymu+mytau).M(),aweight*weight2);
                   if (isJ) h1J_SS[k]->Fill((mymu+mytau).M(),aweight*weight2);
               }
               if (q_1*q_2<0 && mt<50 && antiisoRegion){
                   if (isT) h1T_OSAI[k]->Fill((mymu+mytau).M(),aweight*weight2);
                   if (isL) h1L_OSAI[k]->Fill((mymu+mytau).M(),aweight*weight2);
                   if (isJ) h1J_OSAI[k]->Fill((mymu+mytau).M(),aweight*weight2);
               }
               if (q_1*q_2>0 && mt<50 && antiisoRegion){
                   if (isT) h1T_SSAI[k]->Fill((mymu+mytau).M(),aweight*weight2);
                   if (isL) h1L_SSAI[k]->Fill((mymu+mytau).M(),aweight*weight2);
                   if (isJ) h1J_SSAI[k]->Fill((mymu+mytau).M(),aweight*weight2);
               }
               if (q_1*q_2<0 && mt>80 && signalRegion){
                   if (isT) h1T_MTOS[k]->Fill(var,aweight*weight2);
                   if (isL) h1L_MTOS[k]->Fill(var,aweight*weight2);
                   if (isJ) h1J_MTOS[k]->Fill(var,aweight*weight2);
               }
               if (q_1*q_2>0 && mt>80 && signalRegion){
                   if (isT) h1T_MTSS[k]->Fill(var,aweight*weight2);
                   if (isL) h1L_MTSS[k]->Fill(var,aweight*weight2);
                   if (isJ) h1J_MTSS[k]->Fill(var,aweight*weight2);
	       }
           }

	} // end of loop over nbhist

    } // end of loop over events
    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();
    
    TString postfix=postfixMC[0];
    TDirectory *OS0 =fout->mkdir("ZLmupass");
    OS0->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs" && k>0) continue;
       postfix=postfixMC[k];
       if (sample!="data_obs" && sample!="W"){
         h0T_OS[k]->SetName(name+"T"+postfix);
         h0T_OS[k]->Write();
         h0L_OS[k]->SetName(name+"L"+postfix);
         h0L_OS[k]->Write();
         h0J_OS[k]->SetName(name+"J"+postfix);
         h0J_OS[k]->Write();
       }
       else{
	 h0T_OS[k]->Add(h0L_OS[k]);
         h0T_OS[k]->Add(h0J_OS[k]);
         h0T_OS[k]->SetName(name+postfix);
         h0T_OS[k]->Write();
       }
    }
    TDirectory *SS0 =fout->mkdir("ZLmupassSS");
    SS0->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs" && k>0) continue;
       postfix=postfixMC[k];
       if (sample!="data_obs" && sample!="W"){
         h0T_SS[k]->SetName(name+"T"+postfix);
         h0T_SS[k]->Write();
         h0L_SS[k]->SetName(name+"L"+postfix);
         h0L_SS[k]->Write();
         h0J_SS[k]->SetName(name+"J"+postfix);
         h0J_SS[k]->Write();
       }
       else{
         h0T_SS[k]->Add(h0L_SS[k]);
         h0T_SS[k]->Add(h0J_SS[k]);
         h0T_SS[k]->SetName(name+postfix);
         h0T_SS[k]->Write();
       }
    }
    TDirectory *OSAI0 =fout->mkdir("ZLmupassOSAI");
    OSAI0->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs" && k>0) continue;
       postfix=postfixMC[k];
       if (sample!="data_obs" && sample!="W"){
         h0T_OSAI[k]->SetName(name+"T"+postfix);
         h0T_OSAI[k]->Write();
         h0L_OSAI[k]->SetName(name+"L"+postfix);
         h0L_OSAI[k]->Write();
         h0J_OSAI[k]->SetName(name+"J"+postfix);
         h0J_OSAI[k]->Write();
       }
       else{
         h0T_OSAI[k]->Add(h0L_OSAI[k]);
         h0T_OSAI[k]->Add(h0J_OSAI[k]);
         h0T_OSAI[k]->SetName(name+postfix);
         h0T_OSAI[k]->Write();
       }
    }
    TDirectory *SSAI0 =fout->mkdir("ZLmupassSSAI");
    SSAI0->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs" && k>0) continue;
       postfix=postfixMC[k];
       if (sample!="data_obs" && sample!="W"){
         h0T_SSAI[k]->SetName(name+"T"+postfix);
         h0T_SSAI[k]->Write();
         h0L_SSAI[k]->SetName(name+"L"+postfix);
         h0L_SSAI[k]->Write();
         h0J_SSAI[k]->SetName(name+"J"+postfix);
         h0J_SSAI[k]->Write();
       }
       else{
         h0T_SSAI[k]->Add(h0L_SSAI[k]);
         h0T_SSAI[k]->Add(h0J_SSAI[k]);
         h0T_SSAI[k]->SetName(name+postfix);
         h0T_SSAI[k]->Write();
       }
    }
    TDirectory *MTOS0 =fout->mkdir("ZLmupassMTOS");
    MTOS0->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs" && k>0) continue;
       postfix=postfixMC[k];
       if (sample!="data_obs" && sample!="W"){
         h0T_MTOS[k]->SetName(name+"T"+postfix);
         h0T_MTOS[k]->Write();
         h0L_MTOS[k]->SetName(name+"L"+postfix);
         h0L_MTOS[k]->Write();
         h0J_MTOS[k]->SetName(name+"J"+postfix);
         h0J_MTOS[k]->Write();
       }
       else{
         h0T_MTOS[k]->Add(h0L_MTOS[k]);
         h0T_MTOS[k]->Add(h0J_MTOS[k]);
         h0T_MTOS[k]->SetName(name+postfix);
         h0T_MTOS[k]->Write();
       }
    }
    TDirectory *MTSS0 =fout->mkdir("ZLmupassMTSS");
    MTSS0->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs" && k>0) continue;
       postfix=postfixMC[k];
       if (sample!="data_obs" && sample!="W"){
         h0T_MTSS[k]->SetName(name+"T"+postfix);
         h0T_MTSS[k]->Write();
         h0L_MTSS[k]->SetName(name+"L"+postfix);
         h0L_MTSS[k]->Write();
         h0J_MTSS[k]->SetName(name+"J"+postfix);
         h0J_MTSS[k]->Write();
       }
       else{
         h0T_MTSS[k]->Add(h0L_MTSS[k]);
         h0T_MTSS[k]->Add(h0J_MTSS[k]);
         h0T_MTSS[k]->SetName(name+postfix);
         h0T_MTSS[k]->Write();
       }
    }

    TDirectory *OS1 =fout->mkdir("ZLmufail");
    OS1->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs" && k>0) continue;
       postfix=postfixMC[k];
       if (sample!="data_obs" && sample!="W"){
         h1T_OS[k]->SetName(name+"T"+postfix);
         h1T_OS[k]->Write();
         h1L_OS[k]->SetName(name+"L"+postfix);
         h1L_OS[k]->Write();
         h1J_OS[k]->SetName(name+"J"+postfix);
         h1J_OS[k]->Write();
       }
       else{
         h1T_OS[k]->Add(h1L_OS[k]);
         h1T_OS[k]->Add(h1J_OS[k]);
         h1T_OS[k]->SetName(name+postfix);
         h1T_OS[k]->Write();
       }

    }
    TDirectory *SS1 =fout->mkdir("ZLmufailSS");
    SS1->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs" && k>0) continue;
       postfix=postfixMC[k];
       if (sample!="data_obs" && sample!="W"){
         h1T_SS[k]->SetName(name+"T"+postfix);
         h1T_SS[k]->Write();
         h1L_SS[k]->SetName(name+"L"+postfix);
         h1L_SS[k]->Write();
         h1J_SS[k]->SetName(name+"J"+postfix);
         h1J_SS[k]->Write();
       }
       else{
         h1T_SS[k]->Add(h1L_SS[k]);
         h1T_SS[k]->Add(h1J_SS[k]);
         h1T_SS[k]->SetName(name+postfix);
         h1T_SS[k]->Write();
       }
    }
    TDirectory *OSAI1 =fout->mkdir("ZLmufailOSAI");
    OSAI1->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs" && k>0) continue;
       postfix=postfixMC[k];
       if (sample!="data_obs" && sample!="W"){
         h1T_OSAI[k]->SetName(name+"T"+postfix);
         h1T_OSAI[k]->Write();
         h1L_OSAI[k]->SetName(name+"L"+postfix);
         h1L_OSAI[k]->Write();
         h1J_OSAI[k]->SetName(name+"J"+postfix);
         h1J_OSAI[k]->Write();
       }
       else{
         h1T_OSAI[k]->Add(h1L_OSAI[k]);
         h1T_OSAI[k]->Add(h1J_OSAI[k]);
         h1T_OSAI[k]->SetName(name+postfix);
         h1T_OSAI[k]->Write();
       }
    }
    TDirectory *SSAI1 =fout->mkdir("ZLmufailSSAI");
    SSAI1->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs" && k>0) continue;
       postfix=postfixMC[k];
       if (sample!="data_obs" && sample!="W"){
         h1T_SSAI[k]->SetName(name+"T"+postfix);
         h1T_SSAI[k]->Write();
         h1L_SSAI[k]->SetName(name+"L"+postfix);
         h1L_SSAI[k]->Write();
         h1J_SSAI[k]->SetName(name+"J"+postfix);
         h1J_SSAI[k]->Write();
       }
       else{
         h1T_SSAI[k]->Add(h1L_SSAI[k]);
         h1T_SSAI[k]->Add(h1J_SSAI[k]);
         h1T_SSAI[k]->SetName(name+postfix);
         h1T_SSAI[k]->Write();
       }
    }
    TDirectory *MTOS1 =fout->mkdir("ZLmufailMTOS");
    MTOS1->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs" && k>0) continue;
       postfix=postfixMC[k];
       if (sample!="data_obs" && sample!="W"){
         h1T_MTOS[k]->SetName(name+"T"+postfix);
         h1T_MTOS[k]->Write();
         h1L_MTOS[k]->SetName(name+"L"+postfix);
         h1L_MTOS[k]->Write();
         h1J_MTOS[k]->SetName(name+"J"+postfix);
         h1J_MTOS[k]->Write();
       }
       else{
         h1T_MTOS[k]->Add(h1L_MTOS[k]);
         h1T_MTOS[k]->Add(h1J_MTOS[k]);
         h1T_MTOS[k]->SetName(name+postfix);
         h1T_MTOS[k]->Write();
       }

    }
    TDirectory *MTSS1 =fout->mkdir("ZLmufailMTSS");
    MTSS1->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs" && k>0) continue;
       postfix=postfixMC[k];
       if (sample!="data_obs" && sample!="W"){
         h1T_MTSS[k]->SetName(name+"T"+postfix);
         h1T_MTSS[k]->Write();
         h1L_MTSS[k]->SetName(name+"L"+postfix);
         h1L_MTSS[k]->Write();
         h1J_MTSS[k]->SetName(name+"J"+postfix);
         h1J_MTSS[k]->Write();
       }
       else{
         h1T_MTSS[k]->Add(h1L_MTSS[k]);
         h1T_MTSS[k]->Add(h1J_MTSS[k]);
         h1T_MTSS[k]->SetName(name+postfix);
         h1T_MTSS[k]->Write();
       }
    }

    fout->Close();
    delete wmc;
    delete w;
} 


