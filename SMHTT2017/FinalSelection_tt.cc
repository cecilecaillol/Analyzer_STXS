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
#include "TLegend.h"
#include "TH1F.h"
#include "TKey.h"
#include "THashList.h"
#include "THStack.h"
#include "TPaveLabel.h"
#include "TFile.h"
#include "myHelper.h"
#include "tt_Tree.h"
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

    float tes=0;
    if (argc > 1) {
        tes = atof(argv[5]);
    }

    TFile *f_Double = new TFile(input.c_str());
    cout<<"XXXXXXXXXXXXX "<<input.c_str()<<" XXXXXXXXXXXX"<<endl;
    TTree *arbre = (TTree*) f_Double->Get("tautau_tree");
    TH1F* nbevt = (TH1F*) f_Double->Get("nevents");
    float ngen = nbevt->GetBinContent(2);

    float xs=1.0; float weight=1.0; float luminosity=41400;
    if (sample=="DY" or sample=="ZL" or sample=="ZTT" or sample=="ZJ" or sample=="ZLL"){ xs=6225.42; weight=luminosity*xs/ngen;}
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
    arbre->SetBranchAddress("Rivet_stage1_cat_pTjet30GeV", &Rivet_stage1_cat_pTjet30GeV);

    arbre->SetBranchAddress("run", &run);
    arbre->SetBranchAddress("lumi", &lumi);
    arbre->SetBranchAddress("evt", &evt);
    arbre->SetBranchAddress("npv", &npv);
    arbre->SetBranchAddress("pt_1", &pt_1);
    arbre->SetBranchAddress("phi_1", &phi_1);
    arbre->SetBranchAddress("eta_1", &eta_1);
    arbre->SetBranchAddress("m_1", &m_1);
    arbre->SetBranchAddress("q_1", &q_1);
    arbre->SetBranchAddress("nbtag", &nbtag);
    arbre->SetBranchAddress("q_2", &q_2);
    arbre->SetBranchAddress("pt_2", &pt_2);
    arbre->SetBranchAddress("eta_2", &eta_2);
    arbre->SetBranchAddress("m_2", &m_2);
    arbre->SetBranchAddress("phi_2", &phi_2);
    arbre->SetBranchAddress("met", &met);
    arbre->SetBranchAddress("m_sv", &m_sv);
    arbre->SetBranchAddress("m_sv_01DOWN", &m_sv_01DOWN);
    arbre->SetBranchAddress("m_sv_01UP", &m_sv_01UP);
    arbre->SetBranchAddress("m_sv_10DOWN", &m_sv_10DOWN);
    arbre->SetBranchAddress("m_sv_10UP", &m_sv_10UP);
    arbre->SetBranchAddress("m_sv_11DOWN", &m_sv_11DOWN);
    arbre->SetBranchAddress("m_sv_11UP", &m_sv_11UP);
    arbre->SetBranchAddress("m_sv_UESUp", &m_sv_UESUp);
    arbre->SetBranchAddress("m_sv_UESDown", &m_sv_UESDown);
    arbre->SetBranchAddress("m_sv_ResponseUp", &m_sv_ResponseUp);
    arbre->SetBranchAddress("m_sv_ResponseDown", &m_sv_ResponseDown);
    arbre->SetBranchAddress("m_sv_ResolutionUp", &m_sv_ResolutionUp);
    arbre->SetBranchAddress("m_sv_ResolutionDown", &m_sv_ResolutionDown);
    arbre->SetBranchAddress("m_sv_JetEta0to3Up", &m_sv_JetEta0to3Up);
    arbre->SetBranchAddress("m_sv_JetEta0to3Down", &m_sv_JetEta0to3Down);
    arbre->SetBranchAddress("m_sv_JetEta0to5Up", &m_sv_JetEta0to5Up);
    arbre->SetBranchAddress("m_sv_JetEta0to5Down", &m_sv_JetEta0to5Down);
    arbre->SetBranchAddress("m_sv_JetEta3to5Up", &m_sv_JetEta3to5Up);
    arbre->SetBranchAddress("m_sv_JetEta3to5Down", &m_sv_JetEta3to5Down);
    arbre->SetBranchAddress("m_sv_JetRelativeBalUp", &m_sv_JetRelativeBalUp);
    arbre->SetBranchAddress("m_sv_JetRelativeBalDown", &m_sv_JetRelativeBalDown);
    arbre->SetBranchAddress("m_sv_JetRelativeSampleUp", &m_sv_JetRelativeSampleUp);
    arbre->SetBranchAddress("m_sv_JetRelativeSampleDown", &m_sv_JetRelativeSampleDown);

    arbre->SetBranchAddress("metphi", &metphi);
    arbre->SetBranchAddress("met", &met);
    arbre->SetBranchAddress("metphi", &metphi);
    arbre->SetBranchAddress("met_UESUp", &met_UESUp);
    arbre->SetBranchAddress("metphi_UESUp", &metphi_UESUp);
    arbre->SetBranchAddress("met_UESDown", &met_UESDown);
    arbre->SetBranchAddress("metphi_UESDown", &metphi_UESDown);
    arbre->SetBranchAddress("met_resolutionUp", &met_resolutionUp);
    arbre->SetBranchAddress("metphi_resolutionUp", &metphi_resolutionUp);
    arbre->SetBranchAddress("met_responseUp", &met_responseUp);
    arbre->SetBranchAddress("metphi_responseUp", &metphi_responseUp);
    arbre->SetBranchAddress("met_JetEta0to3Up", &met_JetEta0to3Up);
    arbre->SetBranchAddress("metphi_JetEta0to3Up", &metphi_JetEta0to3Up);
    arbre->SetBranchAddress("met_JetEta3to5Up", &met_JetEta3to5Up);
    arbre->SetBranchAddress("metphi_JetEta3to5Up", &metphi_JetEta3to5Up);
    arbre->SetBranchAddress("met_JetEta0to5Up", &met_JetEta0to5Up);
    arbre->SetBranchAddress("metphi_JetEta0to5Up", &metphi_JetEta0to5Up);
    arbre->SetBranchAddress("met_JetRelativeBalUp", &met_JetRelativeBalUp);
    arbre->SetBranchAddress("metphi_JetRelativeBalUp", &metphi_JetRelativeBalUp);
    arbre->SetBranchAddress("met_JetRelativeSampleUp", &met_JetRelativeSampleUp);
    arbre->SetBranchAddress("metphi_JetRelativeSampleUp", &metphi_JetRelativeSampleUp);
    arbre->SetBranchAddress("met_resolutionDown", &met_resolutionDown);
    arbre->SetBranchAddress("metphi_resolutionDown", &metphi_resolutionDown);
    arbre->SetBranchAddress("met_responseDown", &met_responseDown);
    arbre->SetBranchAddress("metphi_responseDown", &metphi_responseDown);
    arbre->SetBranchAddress("met_JetEta0to3Down", &met_JetEta0to3Down);
    arbre->SetBranchAddress("metphi_JetEta0to3Down", &metphi_JetEta0to3Down);
    arbre->SetBranchAddress("met_JetEta3to5Down", &met_JetEta3to5Down);
    arbre->SetBranchAddress("metphi_JetEta3to5Down", &metphi_JetEta3to5Down);
    arbre->SetBranchAddress("met_JetEta0to5Down", &met_JetEta0to5Down);
    arbre->SetBranchAddress("metphi_JetEta0to5Down", &metphi_JetEta0to5Down);
    arbre->SetBranchAddress("met_JetRelativeBalDown", &met_JetRelativeBalDown);
    arbre->SetBranchAddress("metphi_JetRelativeBalDown", &metphi_JetRelativeBalDown);
    arbre->SetBranchAddress("met_JetRelativeSampleDown", &met_JetRelativeSampleDown);
    arbre->SetBranchAddress("metphi_JetRelativeSampleDown", &metphi_JetRelativeSampleDown);

    arbre->SetBranchAddress("njets", &njets);
    arbre->SetBranchAddress("njets_JetEta0to3Down", &njets_JetEta0to3Down);
    arbre->SetBranchAddress("njets_JetEta0to3Up", &njets_JetEta0to3Up);
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
    arbre->SetBranchAddress("byIsolationMVA3oldDMwLTraw_2",&byIsolationMVA3oldDMwLTraw_2);
    arbre->SetBranchAddress("l2_decayMode",&l2_decayMode);
    arbre->SetBranchAddress("againstElectronTightMVA6_2",&againstElectronTightMVA6_2);
    arbre->SetBranchAddress("againstMuonLoose3_2",&againstMuonLoose3_2);
    arbre->SetBranchAddress("againstElectronVLooseMVA6_2",&againstElectronVLooseMVA6_2);
    arbre->SetBranchAddress("againstMuonTight3_2",&againstMuonTight3_2);
    arbre->SetBranchAddress("byVLooseIsolationMVArun2v2DBoldDMwLT_1",&byVLooseIsolationMVArun2v2DBoldDMwLT_1);
    arbre->SetBranchAddress("byLooseIsolationMVArun2v2DBoldDMwLT_1",&byLooseIsolationMVArun2v2DBoldDMwLT_1);
    arbre->SetBranchAddress("byMediumIsolationMVArun2v2DBoldDMwLT_1",&byMediumIsolationMVArun2v2DBoldDMwLT_1);
    arbre->SetBranchAddress("byTightIsolationMVArun2v2DBoldDMwLT_1",&byTightIsolationMVArun2v2DBoldDMwLT_1);
    arbre->SetBranchAddress("byVTightIsolationMVArun2v2DBoldDMwLT_1",&byVTightIsolationMVArun2v2DBoldDMwLT_1);
    arbre->SetBranchAddress("l1_decayMode",&l1_decayMode);
    arbre->SetBranchAddress("againstElectronTightMVA6_1",&againstElectronTightMVA6_1);
    arbre->SetBranchAddress("againstMuonLoose3_1",&againstMuonLoose3_1);
    arbre->SetBranchAddress("againstElectronVLooseMVA6_1",&againstElectronVLooseMVA6_1);
    arbre->SetBranchAddress("againstMuonTight3_1",&againstMuonTight3_1);
    arbre->SetBranchAddress("gen_match_1",&gen_match_1);
    arbre->SetBranchAddress("gen_match_2",&gen_match_2);
    arbre->SetBranchAddress("npu",&npu);
    arbre->SetBranchAddress("genpT",&genpT);
    arbre->SetBranchAddress("genM",&genM);
    arbre->SetBranchAddress("pt_top1",&pt_top1);
    arbre->SetBranchAddress("pt_top2",&pt_top2);
    arbre->SetBranchAddress("numGenJets",&numGenJets);
    arbre->SetBranchAddress("flag_BadChargedCandidate",&flag_BadChargedCandidate);
    arbre->SetBranchAddress("flag_BadPFMuon",&flag_BadPFMuon);
    arbre->SetBranchAddress("flag_EcalDeadCellTriggerPrimitive",&flag_EcalDeadCellTriggerPrimitive);
    arbre->SetBranchAddress("flag_HBHENoise",&flag_HBHENoise);
    arbre->SetBranchAddress("flag_HBHENoiseIso",&flag_HBHENoiseIso);
    arbre->SetBranchAddress("flag_eeBadSc",&flag_eeBadSc);
    arbre->SetBranchAddress("flag_globalTightHalo2016",&flag_globalTightHalo2016);
    arbre->SetBranchAddress("flag_goodVertices",&flag_goodVertices);
    arbre->SetBranchAddress("flag_globalSuperTightHalo2016",&flag_globalSuperTightHalo2016);
    arbre->SetBranchAddress("flag_ecalBadCalib",&flag_ecalBadCalib);
    arbre->SetBranchAddress("flag_duplicateMuons",&flag_duplicateMuons);
    arbre->SetBranchAddress("flag_badMuons",&flag_badMuons);

    arbre->SetBranchAddress("passDoubleTightTau35TightID",&passDoubleTightTau35TightID);
    arbre->SetBranchAddress("passDoubleMediumTau40TightID",&passDoubleMediumTau40TightID);
    arbre->SetBranchAddress("passDoubleTightTau40",&passDoubleTightTau40);

    arbre->SetBranchAddress("matchDoubleTightTau35TightID_1",&matchDoubleTightTau35TightID_1);
    arbre->SetBranchAddress("matchDoubleMediumTau40TightID_1",&matchDoubleMediumTau40TightID_1);
    arbre->SetBranchAddress("matchDoubleTightTau40_1",&matchDoubleTightTau40_1);
    arbre->SetBranchAddress("matchDoubleTightTau35TightID_2",&matchDoubleTightTau35TightID_2);
    arbre->SetBranchAddress("matchDoubleMediumTau40TightID_2",&matchDoubleMediumTau40TightID_2);
    arbre->SetBranchAddress("matchDoubleTightTau40_2",&matchDoubleTightTau40_2);
    arbre->SetBranchAddress("filterDoubleTightTau35TightID_1",&filterDoubleTightTau35TightID_1);
    arbre->SetBranchAddress("filterDoubleMediumTau40TightID_1",&filterDoubleMediumTau40TightID_1);
    arbre->SetBranchAddress("filterDoubleTightTau40_1",&filterDoubleTightTau40_1);
    arbre->SetBranchAddress("filterDoubleTightTau35TightID_2",&filterDoubleTightTau35TightID_2);
    arbre->SetBranchAddress("filterDoubleMediumTau40TightID_2",&filterDoubleMediumTau40TightID_2);
    arbre->SetBranchAddress("filterDoubleTightTau40_2",&filterDoubleTightTau40_2);

   bool is_ggh=(name.find("ggH") < 140);   
   int nbhist=1;
   if (sample=="data_obs") nbhist=15;
   else if (is_ggh) nbhist=49; 
   else nbhist=31;

   std::vector<TH2F*> h0tau_OS;
   std::vector<TH2F*> h1tau_OS;
   std::vector<TH2F*> h2tau_OS;
   std::vector<TH2F*> h0jet_OS;
   std::vector<TH2F*> h1jet_OS;
   std::vector<TH2F*> h2jet_OS;
   std::vector<TH2F*> h0ell_OS;
   std::vector<TH2F*> h1ell_OS;
   std::vector<TH2F*> h2ell_OS;
   std::vector<TH2F*> h0tau_AI;
   std::vector<TH2F*> h1tau_AI;
   std::vector<TH2F*> h2tau_AI;
   std::vector<TH2F*> h0jet_AI;
   std::vector<TH2F*> h1jet_AI;
   std::vector<TH2F*> h2jet_AI;

   std::vector<TH1F*> h3tau_OS;
   std::vector<TH1F*> h4tau_OS;
   std::vector<TH1F*> h5tau_OS;
   std::vector<TH1F*> h6tau_OS;
   std::vector<TH1F*> h3jet_OS;
   std::vector<TH1F*> h4jet_OS;
   std::vector<TH1F*> h5jet_OS;
   std::vector<TH1F*> h6jet_OS;
   std::vector<TH1F*> h3ell_OS;
   std::vector<TH1F*> h4ell_OS;
   std::vector<TH1F*> h5ell_OS;
   std::vector<TH1F*> h6ell_OS;
   std::vector<TH1F*> h3tau_AI;
   std::vector<TH1F*> h4tau_AI;
   std::vector<TH1F*> h5tau_AI;
   std::vector<TH1F*> h6tau_AI;
   std::vector<TH1F*> h3jet_AI;
   std::vector<TH1F*> h4jet_AI;
   std::vector<TH1F*> h5jet_AI;
   std::vector<TH1F*> h6jet_AI;

   float bins_mtt0[] = {0,40,60,80,100,120,140,160,180,200,220,240,260,280,300};
   int  binnum_mtt0 = sizeof(bins_mtt0)/sizeof(Float_t) - 1;
   float bins_mtt1[] = {0,40,60,70,80,90,100,110,120,130,150,200,250};
   int  binnum_mtt1 = sizeof(bins_mtt1)/sizeof(Float_t) - 1;
   float bins_mtt2[] = {0,40,60,70,80,90,100,110,120,130,150,200,250};
   int  binnum_mtt2 = sizeof(bins_mtt2)/sizeof(Float_t) - 1;

   float bins_mtt3[] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200};//{50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,160,170,180,190,200,250};//{0,5,10,15,20,25,30,35,40,45,50,60,70,80,90,100,120,140,160,180,200,250};
   int  binnum_mtt3 = sizeof(bins_mtt3)/sizeof(Float_t) - 1;
   float bins_mtt4[] = {0,0.3,0.6,0.9,1.2,1.5,1.8,2.1,2.4,2.7,3.0,3.3,3.6,3.9,4.2,4.5,4.8,5.1,5.4,5.7,6.0};//{0,5,10,15,20,25,30,35,40,45,50,60,70,80,90,100,120,140,160,180,200};
   int  binnum_mtt4 = sizeof(bins_mtt4)/sizeof(Float_t) - 1;
   float bins_mtt5[] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200};//{0,1,2,3,4,5,6,7};//{-2.4,-2.2,-2.0,-1.8,-1.6,-1.4,-1.2,-1.0,-0.8,-0.6,-0.4,-0.2,0.0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4};
   int  binnum_mtt5 = sizeof(bins_mtt5)/sizeof(Float_t) - 1;
   float bins_mtt6[] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200};//{0,1,2,3,4,5,6,7};//{-2.4,-2.2,-2.0,-1.8,-1.6,-1.4,-1.2,-1.0,-0.8,-0.6,-0.4,-0.2,0.0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4};
   int  binnum_mtt6 = sizeof(bins_mtt6)/sizeof(Float_t) - 1;

   float bins_mtt[] = {0,30,60,90,120,150,180,250};
   int  binnum_mtt = sizeof(bins_mtt)/sizeof(Float_t) - 1;

   float bins_mjj[] = {0,300,500,800,10000};
   int  binnum_mjj = sizeof(bins_mjj)/sizeof(Float_t) - 1;
   float bins_pth[] = {0,100,170,300,10000};
   int  binnum_pth = sizeof(bins_pth)/sizeof(Float_t) - 1;
   float bins_taupt[] = {0,10000};
   int  binnum_taupt = sizeof(bins_taupt)/sizeof(Float_t) - 1;

   for (int k=0; k<nbhist; ++k){
        ostringstream HNS0tauOS; HNS0tauOS << "h0tau_OS" << k;
        ostringstream HNS1tauOS; HNS1tauOS << "h1tau_OS" << k;
        ostringstream HNS2tauOS; HNS2tauOS << "h2tau_OS" << k;
        h0tau_OS.push_back(new TH2F (HNS0tauOS.str().c_str(),"InvMa",binnum_taupt,bins_taupt,binnum_mtt0,bins_mtt0)); h0tau_OS[k]->Sumw2();
        h1tau_OS.push_back(new TH2F (HNS1tauOS.str().c_str(),"InvMa",binnum_pth,bins_pth,binnum_mtt1,bins_mtt1)); h1tau_OS[k]->Sumw2();
        h2tau_OS.push_back(new TH2F (HNS2tauOS.str().c_str(),"InvMa",binnum_mjj,bins_mjj,binnum_mtt2,bins_mtt2)); h2tau_OS[k]->Sumw2();
        ostringstream HNS0jetOS; HNS0jetOS << "h0jet_OS" << k;
        ostringstream HNS1jetOS; HNS1jetOS << "h1jet_OS" << k;
        ostringstream HNS2jetOS; HNS2jetOS << "h2jet_OS" << k;
        h0jet_OS.push_back(new TH2F (HNS0jetOS.str().c_str(),"InvMa",binnum_taupt,bins_taupt,binnum_mtt0,bins_mtt0)); h0jet_OS[k]->Sumw2();
        h1jet_OS.push_back(new TH2F (HNS1jetOS.str().c_str(),"InvMa",binnum_pth,bins_pth,binnum_mtt1,bins_mtt1)); h1jet_OS[k]->Sumw2();
        h2jet_OS.push_back(new TH2F (HNS2jetOS.str().c_str(),"InvMa",binnum_mjj,bins_mjj,binnum_mtt2,bins_mtt2)); h2jet_OS[k]->Sumw2();
        ostringstream HNS0ellOS; HNS0ellOS << "h0ell_OS" << k;
        ostringstream HNS1ellOS; HNS1ellOS << "h1ell_OS" << k;
        ostringstream HNS2ellOS; HNS2ellOS << "h2ell_OS" << k;
        h0ell_OS.push_back(new TH2F (HNS0ellOS.str().c_str(),"InvMa",binnum_taupt,bins_taupt,binnum_mtt0,bins_mtt0)); h0ell_OS[k]->Sumw2();
        h1ell_OS.push_back(new TH2F (HNS1ellOS.str().c_str(),"InvMa",binnum_pth,bins_pth,binnum_mtt1,bins_mtt1)); h1ell_OS[k]->Sumw2();
        h2ell_OS.push_back(new TH2F (HNS2ellOS.str().c_str(),"InvMa",binnum_mjj,bins_mjj,binnum_mtt2,bins_mtt2)); h2ell_OS[k]->Sumw2();

        ostringstream HNS3tauOS; HNS3tauOS << "h3tau_OS" << k;
        ostringstream HNS4tauOS; HNS4tauOS << "h4tau_OS" << k;
        ostringstream HNS5tauOS; HNS5tauOS << "h5tau_OS" << k;
        ostringstream HNS6tauOS; HNS6tauOS << "h6tau_OS" << k;
        h3tau_OS.push_back(new TH1F (HNS3tauOS.str().c_str(),"InvMa",binnum_mtt3,bins_mtt3)); h3tau_OS[k]->Sumw2();
        h4tau_OS.push_back(new TH1F (HNS4tauOS.str().c_str(),"InvMa",binnum_mtt4,bins_mtt4)); h4tau_OS[k]->Sumw2();
        h5tau_OS.push_back(new TH1F (HNS5tauOS.str().c_str(),"InvMa",binnum_mtt5,bins_mtt5)); h5tau_OS[k]->Sumw2();
        h6tau_OS.push_back(new TH1F (HNS6tauOS.str().c_str(),"InvMa",binnum_mtt6,bins_mtt6)); h6tau_OS[k]->Sumw2();
        ostringstream HNS3jetOS; HNS3jetOS << "h3jet_OS" << k;
        ostringstream HNS4jetOS; HNS4jetOS << "h4jet_OS" << k;
        ostringstream HNS5jetOS; HNS5jetOS << "h5jet_OS" << k;
        ostringstream HNS6jetOS; HNS6jetOS << "h6jet_OS" << k;
        h3jet_OS.push_back(new TH1F (HNS3jetOS.str().c_str(),"InvMa",binnum_mtt3,bins_mtt3)); h3jet_OS[k]->Sumw2();
        h4jet_OS.push_back(new TH1F (HNS4jetOS.str().c_str(),"InvMa",binnum_mtt4,bins_mtt4)); h4jet_OS[k]->Sumw2();
        h5jet_OS.push_back(new TH1F (HNS5jetOS.str().c_str(),"InvMa",binnum_mtt5,bins_mtt5)); h5jet_OS[k]->Sumw2();
        h6jet_OS.push_back(new TH1F (HNS6jetOS.str().c_str(),"InvMa",binnum_mtt6,bins_mtt6)); h6jet_OS[k]->Sumw2();
        ostringstream HNS3ellOS; HNS3ellOS << "h3ell_OS" << k;
        ostringstream HNS4ellOS; HNS4ellOS << "h4ell_OS" << k;
        ostringstream HNS5ellOS; HNS5ellOS << "h5ell_OS" << k;
        ostringstream HNS6ellOS; HNS6ellOS << "h6ell_OS" << k;
        h3ell_OS.push_back(new TH1F (HNS3ellOS.str().c_str(),"InvMa",binnum_mtt3,bins_mtt3)); h3ell_OS[k]->Sumw2();
        h4ell_OS.push_back(new TH1F (HNS4ellOS.str().c_str(),"InvMa",binnum_mtt4,bins_mtt4)); h4ell_OS[k]->Sumw2();
        h5ell_OS.push_back(new TH1F (HNS5ellOS.str().c_str(),"InvMa",binnum_mtt5,bins_mtt5)); h5ell_OS[k]->Sumw2();
        h6ell_OS.push_back(new TH1F (HNS6ellOS.str().c_str(),"InvMa",binnum_mtt6,bins_mtt6)); h6ell_OS[k]->Sumw2();

        ostringstream HNS0tauAI; HNS0tauAI << "h0tau_AI" << k;
        ostringstream HNS1tauAI; HNS1tauAI << "h1tau_AI" << k;
        ostringstream HNS2tauAI; HNS2tauAI << "h2tau_AI" << k;
        h0tau_AI.push_back(new TH2F (HNS0tauAI.str().c_str(),"InvMa",binnum_taupt,bins_taupt,binnum_mtt0,bins_mtt0)); h0tau_AI[k]->Sumw2();
        h1tau_AI.push_back(new TH2F (HNS1tauAI.str().c_str(),"InvMa",binnum_pth,bins_pth,binnum_mtt1,bins_mtt1)); h1tau_AI[k]->Sumw2();
        h2tau_AI.push_back(new TH2F (HNS2tauAI.str().c_str(),"InvMa",binnum_mjj,bins_mjj,binnum_mtt2,bins_mtt2)); h2tau_AI[k]->Sumw2();
        ostringstream HNS0jetAI; HNS0jetAI << "h0jet_AI" << k;
        ostringstream HNS1jetAI; HNS1jetAI << "h1jet_AI" << k;
        ostringstream HNS2jetAI; HNS2jetAI << "h2jet_AI" << k;
        h0jet_AI.push_back(new TH2F (HNS0jetAI.str().c_str(),"InvMa",binnum_taupt,bins_taupt,binnum_mtt0,bins_mtt0)); h0jet_AI[k]->Sumw2();
        h1jet_AI.push_back(new TH2F (HNS1jetAI.str().c_str(),"InvMa",binnum_pth,bins_pth,binnum_mtt1,bins_mtt1)); h1jet_AI[k]->Sumw2();
        h2jet_AI.push_back(new TH2F (HNS2jetAI.str().c_str(),"InvMa",binnum_mjj,bins_mjj,binnum_mtt2,bins_mtt2)); h2jet_AI[k]->Sumw2();

        ostringstream HNS3tauAI; HNS3tauAI << "h3tau_AI" << k;
        ostringstream HNS4tauAI; HNS4tauAI << "h4tau_AI" << k;
        ostringstream HNS5tauAI; HNS5tauAI << "h5tau_AI" << k;
        ostringstream HNS6tauAI; HNS6tauAI << "h6tau_AI" << k;
        h3tau_AI.push_back(new TH1F (HNS3tauAI.str().c_str(),"InvMa",binnum_mtt3,bins_mtt3)); h3tau_AI[k]->Sumw2();
        h4tau_AI.push_back(new TH1F (HNS4tauAI.str().c_str(),"InvMa",binnum_mtt4,bins_mtt4)); h4tau_AI[k]->Sumw2();
        h5tau_AI.push_back(new TH1F (HNS5tauAI.str().c_str(),"InvMa",binnum_mtt5,bins_mtt5)); h5tau_AI[k]->Sumw2();
        h6tau_AI.push_back(new TH1F (HNS6tauAI.str().c_str(),"InvMa",binnum_mtt6,bins_mtt6)); h6tau_AI[k]->Sumw2();
        ostringstream HNS3jetAI; HNS3jetAI << "h3jet_AI" << k;
        ostringstream HNS4jetAI; HNS4jetAI << "h4jet_AI" << k;
        ostringstream HNS5jetAI; HNS5jetAI << "h5jet_AI" << k;
        ostringstream HNS6jetAI; HNS6jetAI << "h6jet_AI" << k;
        h3jet_AI.push_back(new TH1F (HNS3jetAI.str().c_str(),"InvMa",binnum_mtt3,bins_mtt3)); h3jet_AI[k]->Sumw2();
        h4jet_AI.push_back(new TH1F (HNS4jetAI.str().c_str(),"InvMa",binnum_mtt4,bins_mtt4)); h4jet_AI[k]->Sumw2();
        h5jet_AI.push_back(new TH1F (HNS5jetAI.str().c_str(),"InvMa",binnum_mtt5,bins_mtt5)); h5jet_AI[k]->Sumw2();
        h6jet_AI.push_back(new TH1F (HNS6jetAI.str().c_str(),"InvMa",binnum_mtt6,bins_mtt6)); h6jet_AI[k]->Sumw2();
     }

   TH1F* h_weight= new TH1F("h_weight","h_weight",100,0,0.8);

   reweight::LumiReWeighting* LumiWeights_12;
   LumiWeights_12 = new reweight::LumiReWeighting(input, "MyDataPileupHistogram.root", "pileup_mc", "pileup");

   TFile* f_btag_eff=new TFile("tagging_efficiencies_march2018_btageff-all_samp-inc-DeepCSV_medium.root","r");
   TH2F* h_btag_eff_b=(TH2F*) f_btag_eff->Get("btag_eff_b");
   TH2F* h_btag_eff_c=(TH2F*) f_btag_eff->Get("btag_eff_c");
   TH2F* h_btag_eff_oth=(TH2F*) f_btag_eff->Get("btag_eff_oth");

   TFile fw("htt_scalefactors_v17_6.root");
   RooWorkspace *w = (RooWorkspace*)fw.Get("w");
   //w->Print();
   fw.Close();

   TFile fw2016("htt_scalefactors_v16_11_embedded.root");
   RooWorkspace *w2016 = (RooWorkspace*)fw2016.Get("w");
   fw2016.Close();

   TFile fwmc("htt_scalefactors_2017_v2.root");
   RooWorkspace *wmc = (RooWorkspace*)fwmc.Get("w");
   fwmc.Close();

   TFile* ff_file = TFile::Open("HTTutilities/Jet2TauFakes/data/SM2017/tight/vloose/tt/fakeFactors.root");
   FakeFactor* ff1 = (FakeFactor*)ff_file->Get("ff_comb");
   const std::vector<std::string>& inputNames1 = ff1->inputs();
   std::vector<double> inputs1(8);
   FakeFactor* ff2 = (FakeFactor*)ff_file->Get("ff_comb");
   const std::vector<std::string>& inputNames2 = ff2->inputs();
   std::vector<double> inputs2(8);

   //TauTriggerSFs2017* ttsf=new TauTriggerSFs2017("ditau", "2017", "tight", "MVAv2");

   TString postfixMC[49]={"","_CMS_scale_t_1prongDown","_CMS_scale_t_1prongUp","_CMS_scale_t_1prong1pizeroDown","_CMS_scale_t_1prong1pizeroUp","_CMS_scale_t_3prongDown","_CMS_scale_t_3prongUp","_CMS_JetEta0to3Down","_CMS_JetEta0to3Up","_CMS_JetEta0to5Down","_CMS_JetEta0to5Up","_CMS_JetEta3to5Down","_CMS_JetEta3to5Up","_CMS_JetRelativeSampleDown","_CMS_JetRelativeSampleUp","_CMS_JetRelativeBalDown","_CMS_JetRelativeBalUp","_CMS_scale_met_unclusteredDown","_CMS_scale_met_unclusteredUp","_CMS_htt_boson_scale_metDown","_CMS_htt_boson_scale_metUp","_CMS_htt_boson_reso_metDown","_CMS_htt_boson_reso_metUp","_CMS_htt_ttbarShapeDown","_CMS_htt_ttbarShapeUp","_CMS_htt_dyShapeDown","_CMS_htt_dyShapeUp","_CMS_1ProngPi0EffDown","_CMS_1ProngPi0EffUp","_CMS_3ProngEffDown","_CMS_3ProngEffUp","_THU_ggH_MuUp","_THU_ggH_MuDown","_THU_ggH_ResUp","_THU_ggH_ResDown","_THU_ggH_Mig01Up","_THU_ggH_Mig01Down","_THU_ggH_Mig12Up","_THU_ggH_Mig12Down","_THU_ggH_VBF2jUp","_THU_ggH_VBF2jDown","_THU_ggH_VBF3jUp","_THU_ggH_VBF3jDown","_THU_ggH_PT60Up","_THU_ggH_PT60Down","_THU_ggH_PT120Up","_THU_ggH_PT120Down","_THU_ggH_qmtopUp","_THU_ggH_qmtopDown"};

   TString postfixEmb[49]={"","_CMS_scale_emb_t_1prongDown","_CMS_scale_emb_t_1prongUp","_CMS_scale_emb_t_1prong1pizeroDown","_CMS_scale_emb_t_1prong1pizeroUp","_CMS_scale_emb_t_3prongDown","_CMS_scale_emb_t_3prongUp","_CMS_JetEta0to3Down","_CMS_JetEta0to3Up","_CMS_JetEta0to5Down","_CMS_JetEta0to5Up","_CMS_JetEta3to5Down","_CMS_JetEta3to5Up","_CMS_JetRelativeSampleDown","_CMS_JetRelativeSampleUp","_CMS_JetRelativeBalDown","_CMS_JetRelativeBalUp","_CMS_scale_met_unclusteredDown","_CMS_scale_met_unclusteredUp","_CMS_htt_boson_scale_metDown","_CMS_htt_boson_scale_metUp","_CMS_htt_boson_reso_metDown","_CMS_htt_boson_reso_metUp","_CMS_htt_ttbarShapeDown","_CMS_htt_ttbarShapeUp","_CMS_htt_dyShapeDown","_CMS_htt_dyShapeUp","_CMS_1ProngPi0EffDown","_CMS_1ProngPi0EffUp","_CMS_3ProngEffDown","_CMS_3ProngEffUp","_THU_ggH_MuUp","_THU_ggH_MuDown","_THU_ggH_ResUp","_THU_ggH_ResDown","_THU_ggH_Mig01Up","_THU_ggH_Mig01Down","_THU_ggH_Mig12Up","_THU_ggH_Mig12Down","_THU_ggH_VBF2jUp","_THU_ggH_VBF2jDown","_THU_ggH_VBF3jUp","_THU_ggH_VBF3jDown","_THU_ggH_PT60Up","_THU_ggH_PT60Down","_THU_ggH_PT120Up","_THU_ggH_PT120Down","_THU_ggH_qmtopUp","_THU_ggH_qmtopDown"};

   TString postfixFF[15]={"","_CMS_ff_qcd_tt_systUp","_CMS_ff_qcd_tt_systDown","_CMS_ff_qcd_njet0_tt_statUp","_CMS_ff_qcd_njet0_tt_statDown","_CMS_ff_qcd_njet1_tt_statUp","_CMS_ff_qcd_njet1_tt_statDown","_CMS_ff_w_tt_systUp","_CMS_ff_w_tt_systDown","_CMS_ff_tt_tt_systUp","_CMS_ff_tt_tt_systDown","_CMS_ff_w_frac_tt_systUp","_CMS_ff_w_frac_tt_systDown","_CMS_ff_tt_frac_tt_systUp","_CMS_ff_tt_frac_tt_systDown"};

   std::string FFsys[14]={"ff_qcd_syst_up","ff_qcd_syst_down","ff_qcd_dm0_njet0_stat_up","ff_qcd_dm0_njet0_stat_down","ff_qcd_dm0_njet1_stat_up","ff_qcd_dm0_njet1_stat_down","ff_w_syst_up","ff_w_syst_down","ff_tt_syst_up","ff_tt_syst_down","ff_w_frac_syst_up","ff_w_frac_syst_down","ff_tt_frac_syst_up","ff_tt_frac_syst_down"};

   TFile * f_NNLOPS = new TFile("NNLOPS_reweight.root");
   TGraph * g_NNLOPS_0jet = (TGraph*) f_NNLOPS-> Get("gr_NNLOPSratio_pt_powheg_0jet");
   TGraph * g_NNLOPS_1jet = (TGraph*) f_NNLOPS-> Get("gr_NNLOPSratio_pt_powheg_1jet");
   TGraph * g_NNLOPS_2jet = (TGraph*) f_NNLOPS-> Get("gr_NNLOPSratio_pt_powheg_2jet");
   TGraph * g_NNLOPS_3jet = (TGraph*) f_NNLOPS-> Get("gr_NNLOPSratio_pt_powheg_3jet");

   bool do_rivet=(name.find("ggH") < 140 or name.find("qqH") < 140 or name.find("VH") < 140 or name.find("WH") < 140 or name.find("ZH") < 140);
   if (sample=="ggH_htt125" or sample=="qqH_htt125" or sample=="WplusH125" or sample=="WminusH125" or sample=="ZH125") do_rivet=false;

   Int_t nentries_wtn = (Int_t) arbre->GetEntries();
   for (Int_t i = 0; i < nentries_wtn; i++) {
        arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

	// Rivet splitting
	if (do_rivet){
           if (name.find("ggH_fwd_htt1") < 140 && Rivet_stage0_cat!=10) continue;
           if (name.find("ggH_stage0_htt1") < 140 && Rivet_stage0_cat!=11) continue;
           if (name.find("qqH_fwd_htt1") < 140 && Rivet_stage0_cat!=20) continue;
           if (name.find("qqH_stage0_htt1") < 140 && Rivet_stage0_cat!=21) continue;
           if ((name.find("VH_had_htt1") < 140 or name.find("WH_had_htt1") < 140 or name.find("ZH_had_htt1") < 140) && Rivet_stage0_cat!=23) continue;
           if (name.find("WH_lep_fwd_htt1") < 140 && Rivet_stage0_cat!=30) continue;
           if (name.find("WH_lep_htt1") < 140 && Rivet_stage0_cat!=31) continue;
           if ((name.find("VH_had_fwd_htt1") < 140 or name.find("WH_had_fwd_htt1") < 140 or name.find("ZH_had_fwd_htt1") < 140) && Rivet_stage0_cat!=22) continue;
           if (name.find("ZH_lep_fwd_htt1") < 140 && Rivet_stage0_cat!=40) continue;
           if (name.find("ZH_lep_htt1") < 140 && Rivet_stage0_cat!=41) continue;
           if (name.find("ggH_VBFTOPO_JET3VETO_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=101) continue;
           if (name.find("ggH_VBFTOPO_JET3_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=102) continue;
           if (name.find("ggH_0J_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=103) continue;
           if (name.find("ggH_1J_PTH_0_60_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=104) continue;
           if (name.find("ggH_1J_PTH_60_120_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=105) continue;
           if (name.find("ggH_1J_PTH_120_200_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=106) continue;
           if (name.find("ggH_1J_PTH_GT200_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=107) continue;
           if (name.find("ggH_GE2J_PTH_0_60_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=108) continue;
           if (name.find("ggH_GE2J_PTH_60_120_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=109) continue;
           if (name.find("ggH_GE2J_PTH_120_200_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=110) continue;
           if (name.find("ggH_GE2J_PTH_GT200_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=111) continue;
           if (name.find("qqH_FWDH_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=200) continue;
           if (name.find("qqH_VBFTOPO_JET3VETO_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=201) continue;
           if (name.find("qqH_VBFTOPO_JET3_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=202) continue;
           if (name.find("qqH_VH2JET_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=203) continue;
           if (name.find("qqH_REST_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=204) continue;
           if (name.find("qqH_PTJET1_GT200_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=205) continue;
           if ((name.find("VH_had_VBFTOPO_JET3VETO_htt1") < 140 or name.find("WH_had_VBFTOPO_JET3VETO_htt1") < 140 or name.find("ZH_had_VBFTOPO_JET3VETO_htt1") < 140) && Rivet_stage1_cat_pTjet30GeV!=201) continue;
           if ((name.find("VH_had_VBFTOPO_JET3_htt1") < 140 or name.find("WH_had_VBFTOPO_JET3_htt1") < 140 or name.find("ZH_had_VBFTOPO_JET3_htt1") < 140) && Rivet_stage1_cat_pTjet30GeV!=202) continue;
           if ((name.find("VH_had_VH2JET_htt1") < 140 or name.find("WH_had_VH2JET_htt1") < 140 or name.find("ZH_had_VH2JET_htt1") < 140) && Rivet_stage1_cat_pTjet30GeV!=203) continue;
           if ((name.find("VH_had_REST_htt1") < 140 or name.find("WH_had_REST_htt1") < 140 or name.find("ZH_had_REST_htt1") < 140) && Rivet_stage1_cat_pTjet30GeV!=204) continue;
           if ((name.find("VH_had_PTJET1_GT200_htt1") < 140 or name.find("WH_had_PTJET1_GT200_htt1") < 140 or name.find("ZH_had_PTJET1_GT200_htt1") < 140) && Rivet_stage1_cat_pTjet30GeV!=205) continue;
           if (name.find("WH_lep_FWDH_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=300) continue;
           if (name.find("WH_lep_PTV_0_150_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=301) continue;
           if (name.find("WH_lep_PTV_150_250_0J_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=302) continue;
           if (name.find("WH_lep_PTV_150_250_GE1J_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=303) continue;
           if (name.find("WH_lep_PTV_GT250_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=304) continue;
           if ((name.find("VH_had_FWDH_htt1") < 140 or name.find("WH_had_FWDH_htt1") < 140 or name.find("ZH_had_FWDH_htt1") < 140) && Rivet_stage1_cat_pTjet30GeV!=200) continue;
           if (name.find("ZH_lep_FWDH_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=400) continue;
           if (name.find("ZH_lep_PTV_0_150_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=401) continue;
           if (name.find("ZH_lep_PTV_150_250_0J_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=402) continue;
           if (name.find("ZH_lep_PTV_150_250_Ge1J_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=403) continue;
           if (name.find("ZH_lep_PTV_GT250_htt1") < 140 && Rivet_stage1_cat_pTjet30GeV!=404) continue;
	}

        bool trigger1_match=(passDoubleTightTau35TightID && pt_1>39.5 && pt_2>39.5 && matchDoubleTightTau35TightID_1 && filterDoubleTightTau35TightID_1 && matchDoubleTightTau35TightID_2 && filterDoubleTightTau35TightID_2);
        bool trigger2_match=(passDoubleMediumTau40TightID && pt_1>44.5 && pt_2>44.5 && matchDoubleMediumTau40TightID_1 && filterDoubleMediumTau40TightID_1 && matchDoubleMediumTau40TightID_2 && filterDoubleMediumTau40TightID_2);
        bool trigger3_match=(passDoubleTightTau40 && pt_1>44.5 && pt_2>44.5 && matchDoubleTightTau40_1 && filterDoubleTightTau40_1 && matchDoubleTightTau40_2 && filterDoubleTightTau40_2);

        bool trigger1=(passDoubleTightTau35TightID && pt_1>39.5 && pt_2>39.5);
        bool trigger2=(passDoubleMediumTau40TightID && pt_1>44.5 && pt_2>44.5);
        bool trigger3=(passDoubleTightTau40 && pt_1>44.5 && pt_2>44.5);

	if (sample!="embedded" && !trigger1_match && !trigger2_match && !trigger3_match) continue;
        if (sample=="embedded" && !trigger1 && !trigger2 && !trigger3) continue;

	if (fabs(eta_1)>2.1) continue;
        if (fabs(eta_2)>2.1) continue;

	if (flag_goodVertices) continue;
	if (flag_globalTightHalo2016) continue;
	if (flag_HBHENoise) continue;
	if (flag_HBHENoiseIso) continue;
	if (flag_EcalDeadCellTriggerPrimitive) continue;
	if (flag_BadPFMuon) continue;
	if (flag_BadChargedCandidate) continue;
	if ((sample=="data_obs" or sample=="embedded") && flag_eeBadSc) continue;
	if (flag_ecalBadCalib) continue;

	float signalRegion=(byTightIsolationMVArun2v2DBoldDMwLT_1 && byTightIsolationMVArun2v2DBoldDMwLT_2);
        float antiisoRegion1=(byVLooseIsolationMVArun2v2DBoldDMwLT_1 && !byTightIsolationMVArun2v2DBoldDMwLT_1 && byTightIsolationMVArun2v2DBoldDMwLT_2);
        float antiisoRegion2=(byVLooseIsolationMVArun2v2DBoldDMwLT_2 && !byTightIsolationMVArun2v2DBoldDMwLT_2 && byTightIsolationMVArun2v2DBoldDMwLT_1);

	TLorentzVector mytau2; 
	mytau2.SetPtEtaPhiM(pt_2,eta_2,phi_2,m_2);
        TLorentzVector mytau1;
        mytau1.SetPtEtaPhiM(pt_1,eta_1,phi_1,m_1);

        if (sample=="W"){
            weight=32.7;
            if (numGenJets==1) weight=5.90;
            else if (numGenJets==2) weight=12.58;
            else if (numGenJets==3) weight=2.26;
            else if (numGenJets==4) weight=1.13;
        }
        if (sample=="DY"){
            weight=2.66;
            if (numGenJets==1)
                weight=0.46;
            else if (numGenJets==2)
                weight=0.958;
            else if (numGenJets==3)
                weight=0.603;
            else if (numGenJets==4)
                weight=0.224;
        }

	//if ((sample=="TTTo2L2Nu" or sample=="TTToHadronic" or sample=="TTToSemiLeptonic") && gen_match_1>2 && gen_match_1<6 && gen_match_2>2 && gen_match_2<6) continue; // remove overlap with embedded samples

	float aweight=genweight*weight*LumiWeights_12->weight(npu);
        if (sample=="embedded") aweight=genweight;
	if (sample!="embedded" && sample!="data_obs" && gen_match_1==5) aweight=aweight*0.89; // Tau ID SF
        if (sample!="embedded" && sample!="data_obs" && gen_match_2==5) aweight=aweight*0.89; // Tau ID SF
        if (sample!="embedded" && sample!="data_obs" && gen_match_1==5) aweight=aweight*0.96; // Tau trigger SF FIXME
        if (sample!="embedded" && sample!="data_obs" && gen_match_2==5) aweight=aweight*0.96; // Tau trigger SF FIXME
        if (sample=="embedded") aweight=aweight*0.97*0.97; // Tau ID SF for embedded
        //if (sample=="embedded") aweight=aweight*2.0;//FIXME!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	if (sample=="qqH_htt125") aweight=aweight*0.95;//Prefiring effect

	if (sample=="embedded"){
	   gen_match_1=5;
	   gen_match_2=5;
	}

	//NNLOPS weights
        if (name.find("ggH")<100 && name.find("NNLOPS")>100 && name.find("hww")>100){
            if (Rivet_nJets30==0) aweight = aweight * g_NNLOPS_0jet->Eval(min(Rivet_higgsPt,float(125.0)));
            if (Rivet_nJets30==1) aweight = aweight * g_NNLOPS_1jet->Eval(min(Rivet_higgsPt,float(625.0)));
            if (Rivet_nJets30==2) aweight = aweight * g_NNLOPS_2jet->Eval(min(Rivet_higgsPt,float(800.0)));
            if (Rivet_nJets30>=3) aweight = aweight * g_NNLOPS_3jet->Eval(min(Rivet_higgsPt,float(925.0)));
        }
	NumV WG1unc = qcd_ggF_uncert_2017(Rivet_nJets30, Rivet_higgsPt, Rivet_stage1_cat_pTjet30GeV);

	TLorentzVector mymet;
	mymet.SetPtEtaPhiM(met,0,metphi,0);

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
	  if (sample=="DY") aweight=aweight*zptweight;
	}

        if (sample=="embedded"){
          if (l2_decayMode==0) aweight=aweight*0.975; // track reconstruction
          else if (l2_decayMode==1) aweight=aweight*0.975*1.051; // track reconstruction
          else if (l2_decayMode==10) aweight=aweight*0.975*0.975*0.975; // track reconstruction
          if (l1_decayMode==0) aweight=aweight*0.975; // track reconstruction
          else if (l1_decayMode==1) aweight=aweight*0.975*1.051; // track reconstruction
          else if (l1_decayMode==10) aweight=aweight*0.975*0.975*0.975; // track reconstruction
          w->var("gt_pt")->setVal(mytau1.Pt());
          w->var("gt_eta")->setVal(mytau1.Eta());
          aweight=aweight*w->function("m_sel_idEmb_ratio")->getVal();
          w->var("gt_pt")->setVal(mytau2.Pt());
          w->var("gt_eta")->setVal(mytau2.Eta());
          aweight=aweight*w->function("m_sel_idEmb_ratio")->getVal();
          w->var("gt1_pt")->setVal(mytau1.Pt());
          w->var("gt1_eta")->setVal(mytau1.Eta());
          w->var("gt2_pt")->setVal(mytau2.Pt());
          w->var("gt2_eta")->setVal(mytau2.Eta());
          aweight=aweight*w->function("m_sel_trg_ratio")->getVal();
	  w->var("t_pt")->setVal(mytau1.Pt());
	  aweight=aweight*w->function("tt_emb_PFTau35OR40_tight_kit_ratio")->getVal();
          w->var("t_pt")->setVal(mytau2.Pt());
          aweight=aweight*w->function("tt_emb_PFTau35OR40_tight_kit_ratio")->getVal();
        }

	//************************ Compute fake factors ******************
	float frac_qcd=1.0;
	float frac_w=0.0;
	float frac_tt=0.0;

        inputs1[0] = mytau1.Pt();
        inputs1[1] = mytau2.Pt();
        inputs1[2] = l1_decayMode;
        inputs1[3] = njets;
        inputs1[4] = (mytau1+mytau2).M();
        inputs1[5] = frac_qcd;
        inputs1[6] = frac_w;
        inputs1[7] = frac_tt;
	double FF1=ff1->value(inputs1);

        inputs2[0] = mytau2.Pt();
        inputs2[1] = mytau1.Pt();
        inputs2[2] = l2_decayMode;
        inputs2[3] = njets;
        inputs2[4] = (mytau1+mytau2).M();
        inputs2[5] = frac_qcd;
        inputs2[6] = frac_w;
        inputs2[7] = frac_tt;
        double FF2=ff2->value(inputs2);

	float myvar=(mytau1+mytau2).M();
	TLorentzVector myrawtau1=mytau1;
        TLorentzVector myrawtau2=mytau2;
        TLorentzVector myrawmet=mymet;
        float massJets=mjj;
        int numberJets=njets;
	int rawnbtag=nbtag;
	float mtt=m_sv;

	bool isJ=false;
	bool isT=false;
	bool isL=false;
	if (sample!="data_obs" && gen_match_1==5 && gen_match_2==5) isT=true;
        if (sample!="data_obs" && gen_match_1<6 && gen_match_2<6 && !(gen_match_1==5 && gen_match_2==5)) isL=true;
	if (sample!="data_obs" && (gen_match_1==6 or gen_match_2==6)) isJ=true;
        if (sample=="embedded") isT=true;
        if (sample=="embedded") isL=false;
        if (sample=="embedded") isJ=false;
	for (int k=0; k<nbhist; ++k){

	   float weight2=1.0;

	   // reset all variables before any systematic shift
	   massJets=mjj;
	   mtt=m_sv;
	   numberJets=njets;
	   mytau1=myrawtau1;
           mytau2=myrawtau2;
	   mymet=myrawmet;
	   massJets=mjj;
           nbtag=rawnbtag;

	   if (sample!="data_obs"){
	      if (k>0 && k<7){ // TES x 6
                if (k==1){
		   if (gen_match_1==5 && gen_match_2==5 && l1_decayMode==0 && l2_decayMode==0){mytau1*=0.992; mymet=mymet+(0.008/0.992)*mytau1; mytau2*=0.992; mymet=mymet+(0.008/0.992)*mytau2; mtt=m_sv_11DOWN;}
                   if (gen_match_1==5 && l1_decayMode==0 && l2_decayMode!=0){mytau1*=0.992; mymet=mymet+(0.008/0.992)*mytau1; mtt=m_sv_10DOWN;}
                   if (gen_match_2==5 && l1_decayMode!=0 && l2_decayMode==0){mytau2*=0.992; mymet=mymet+(0.008/0.992)*mytau2; mtt=m_sv_01DOWN;}
		}
                else if (k==2){
                   if (gen_match_1==5 && gen_match_2==5 && l1_decayMode==0 && l2_decayMode==0){mytau1*=1.008; mymet=mymet-(0.008/1.008)*mytau1; mytau2*=1.008; mymet=mymet-(0.008/1.008)*mytau2; mtt=m_sv_11UP;}
                   if (gen_match_1==5 && l1_decayMode==0 && l2_decayMode!=0){mytau1*=1.008; mymet=mymet-(0.008/1.008)*mytau1; mtt=m_sv_10UP;}
                   if (gen_match_2==5 && l1_decayMode!=0 && l2_decayMode==0){mytau2*=1.008; mymet=mymet-(0.008/1.008)*mytau2; mtt=m_sv_01UP;}
                }
                else if (k==3){
                   if (gen_match_1==5 && gen_match_2==5 && l1_decayMode==1 && l2_decayMode==1){mytau1*=0.992; mymet=mymet+(0.008/0.992)*mytau1; mytau2*=0.992; mymet=mymet+(0.008/0.992)*mytau2; mtt=m_sv_11DOWN;}
                   if (gen_match_1==5 && l1_decayMode==1 && l2_decayMode!=1){mytau1*=0.992; mymet=mymet+(0.008/0.992)*mytau1; mtt=m_sv_10DOWN;}                
                   if (gen_match_2==5 && l1_decayMode!=1 && l2_decayMode==1){mytau2*=0.992; mymet=mymet+(0.008/0.992)*mytau2; mtt=m_sv_01DOWN;}
                }
                else if (k==4){
                   if (gen_match_1==5 && gen_match_2==5 && l1_decayMode==1 && l2_decayMode==1){mytau1*=1.008; mymet=mymet-(0.008/1.008)*mytau1; mytau2*=1.008; mymet=mymet-(0.008/1.008)*mytau2; mtt=m_sv_11UP;}
                   if (gen_match_1==5 && l1_decayMode==1 && l2_decayMode!=1){mytau1*=1.008; mymet=mymet-(0.008/1.008)*mytau1; mtt=m_sv_10UP;}
                   if (gen_match_2==5 && l1_decayMode!=1 && l2_decayMode==1){mytau2*=1.008; mymet=mymet-(0.008/1.008)*mytau2; mtt=m_sv_01UP;}
                }
                else if (k==5){
                   if (gen_match_1==5 && gen_match_2==5 && l1_decayMode==10 && l2_decayMode==10){mytau1*=0.992; mymet=mymet+(0.008/0.992)*mytau1; mytau2*=0.992; mymet=mymet+(0.008/0.992)*mytau2; mtt=m_sv_11DOWN;}
                   if (gen_match_1==5 && l1_decayMode==10 && l2_decayMode!=10){mytau1*=0.992; mymet=mymet+(0.008/0.992)*mytau1; mtt=m_sv_10DOWN;}                
                   if (gen_match_2==5 && l1_decayMode!=10 && l2_decayMode==10){mytau2*=0.992; mymet=mymet+(0.008/0.992)*mytau2; mtt=m_sv_01DOWN;}
                }
                else if (k==6){
                   if (gen_match_1==5 && gen_match_2==5 && l1_decayMode==10 && l2_decayMode==10){mytau1*=1.008; mymet=mymet-(0.008/1.008)*mytau1; mytau2*=1.008; mymet=mymet-(0.008/1.008)*mytau2; mtt=m_sv_11UP;}
                   if (gen_match_1==5 && l1_decayMode==10 && l2_decayMode!=10){mytau1*=1.008; mymet=mymet-(0.008/1.008)*mytau1; mtt=m_sv_10UP;}
                   if (gen_match_2==5 && l1_decayMode!=10 && l2_decayMode==10){mytau2*=1.008; mymet=mymet-(0.008/1.008)*mytau2; mtt=m_sv_01UP;}
                }
              }
              else if (k>6 && k<17){ // JES x 10
                if (k==7){numberJets=njets_JetEta0to3Down; massJets=mjj_JetEta0to3Down; mymet.SetPtEtaPhiM(met_JetEta0to3Down, 0, metphi_JetEta0to3Down, 0); mtt=m_sv_JetEta0to3Down;}
                else if (k==8){numberJets=njets_JetEta0to3Up; massJets=mjj_JetEta0to3Up; mymet.SetPtEtaPhiM(met_JetEta0to3Up, 0, metphi_JetEta0to3Up, 0); mtt=m_sv_JetEta0to3Up;}
                else if (k==9){numberJets=njets_JetEta0to5Down; massJets=mjj_JetEta0to5Down; mymet.SetPtEtaPhiM(met_JetEta0to5Down, 0, metphi_JetEta0to5Down, 0); mtt=m_sv_JetEta0to5Down;}
                else if (k==10){numberJets=njets_JetEta0to5Up; massJets=mjj_JetEta0to5Up; mymet.SetPtEtaPhiM(met_JetEta0to5Up, 0, metphi_JetEta0to5Up, 0); mtt=m_sv_JetEta0to5Up;}
                else if (k==11){numberJets=njets_JetEta3to5Down; massJets=mjj_JetEta3to5Down; mymet.SetPtEtaPhiM(met_JetEta3to5Down, 0, metphi_JetEta3to5Down, 0); mtt=m_sv_JetEta3to5Down;}
                else if (k==12){numberJets=njets_JetEta3to5Up; massJets=mjj_JetEta3to5Up; mymet.SetPtEtaPhiM(met_JetEta3to5Up, 0, metphi_JetEta3to5Up, 0); mtt=m_sv_JetEta3to5Up;}
                else if (k==13){numberJets=njets_JetRelativeSampleDown; massJets=mjj_JetRelativeSampleDown; mymet.SetPtEtaPhiM(met_JetRelativeSampleDown, 0, metphi_JetRelativeSampleDown, 0); mtt=m_sv_JetRelativeSampleDown;}
                else if (k==14){numberJets=njets_JetRelativeSampleUp; massJets=mjj_JetRelativeSampleUp; mymet.SetPtEtaPhiM(met_JetRelativeSampleUp, 0, metphi_JetRelativeSampleUp, 0); mtt=m_sv_JetRelativeSampleUp;}
                else if (k==15){numberJets=njets_JetRelativeBalDown; massJets=mjj_JetRelativeBalDown; mymet.SetPtEtaPhiM(met_JetRelativeBalDown, 0, metphi_JetRelativeBalDown, 0); mtt=m_sv_JetRelativeBalDown;}
                else if (k==16){numberJets=njets_JetRelativeBalUp; massJets=mjj_JetRelativeBalUp; mymet.SetPtEtaPhiM(met_JetRelativeBalUp, 0, metphi_JetRelativeBalUp, 0); mtt=m_sv_JetRelativeBalUp;}
              }
	      else if ((name=="TT" or name=="VV") && k>16 && k<19){ // UES x 2
                if (k==17){mymet=myrawmet; mymet.SetPtEtaPhiM(met_UESDown, 0, metphi_UESDown, 0); mtt=m_sv_UESDown;}
	        else if (k==18){mymet=myrawmet; mymet.SetPtEtaPhiM(met_UESUp, 0, metphi_UESUp, 0); mtt=m_sv_UESUp;}
	      }
              else if (!(name=="embedded" or name=="TT" or name=="VV") && k>18 && k<23){ // Recoil x 4 //FIXME
                if (k==19){mymet=myrawmet; mymet.SetPtEtaPhiM(met_responseDown, 0, metphi_responseDown, 0); mtt=m_sv_ResponseDown;}
                else if (k==20){mymet=myrawmet; mymet.SetPtEtaPhiM(met_responseUp, 0, metphi_responseUp, 0); mtt=m_sv_ResponseUp;}
                else if (k==21){mymet=myrawmet; mymet.SetPtEtaPhiM(met_resolutionDown, 0, metphi_resolutionDown, 0); mtt=m_sv_ResolutionDown;}
                else if (k==22){mymet=myrawmet; mymet.SetPtEtaPhiM(met_resolutionUp, 0, metphi_resolutionUp, 0); mtt=m_sv_ResolutionUp;}
              }
	      else if (k>22 && k<25 && (sample=="TTToHadronic" or sample=="TTTo2L2Nu" or sample=="TTToSemiLeptonic")){ //Top pt reweighting x 2
	        if (k==23) weight2=1.0/topfactor;
                else if (k==24) weight2=topfactor;
	      }
              else if (k>24 && k<27 && (sample=="DY")){ //Z pt reweighting x 2
                if (k==25) weight2=1.0/zptweight;
                else if (k==26) weight2=zptweight;
              }
              else if (k>26 && k<31){ // Embedded CMS_1ProngPi0Eff x 4
                if (k==27) weight2=1.0; //FIXME
                else if (k==28) weight2=1.0; //FIXME
                else if (k==29) weight2=1.0; //FIXME
                else if (k==30) weight2=1.0; //FIXME
              }
	      if (is_ggh && k>30 && k<49){ // WG1 x 18
                if (k==31) weight2=1+WG1unc[0];
                else if (k==32) weight2=1-WG1unc[0];
                else if (k==33) weight2=1+WG1unc[1];
                else if (k==34) weight2=1-WG1unc[1];
                else if (k==35) weight2=1+WG1unc[2];
                else if (k==36) weight2=1-WG1unc[2];
                else if (k==37) weight2=1+WG1unc[3];
                else if (k==38) weight2=1-WG1unc[3];
                else if (k==39) weight2=1+WG1unc[4];
                else if (k==40) weight2=1-WG1unc[4];
                else if (k==41) weight2=1+WG1unc[5];
                else if (k==42) weight2=1-WG1unc[5];
                else if (k==43) weight2=1+WG1unc[6];
                else if (k==44) weight2=1-WG1unc[6];
                else if (k==45) weight2=1+WG1unc[7];
                else if (k==46) weight2=1-WG1unc[7];
                else if (k==47) weight2=1+WG1unc[8];
                else if (k==48) weight2=1-WG1unc[8];
              }
	   }
	   if (sample=="data_obs"){
	      if (k>0 && k<15){ // FF x 14
                FF1=ff1->value(inputs1,FFsys[k-1]);
                FF2=ff2->value(inputs2,FFsys[k-1]);
              }
	   }

           nbtag=rawnbtag;
           if (sample!="data_obs" && sample!="embedded" && nbtag>0) nbtag=PromoteDemote(h_btag_eff_b, h_btag_eff_c, h_btag_eff_oth, nbtag, bpt_1, bflavor_1, beta_1,0);
           if (nbtag>0) continue;

	   // Check again the pT after the shifts
           trigger1_match=(passDoubleTightTau35TightID && mytau1.Pt()>40 && mytau2.Pt()>40 && matchDoubleTightTau35TightID_1 && filterDoubleTightTau35TightID_1 && matchDoubleTightTau35TightID_2 && filterDoubleTightTau35TightID_2);
           trigger2_match=(passDoubleMediumTau40TightID && mytau1.Pt()>45 && mytau2.Pt()>45 && matchDoubleMediumTau40TightID_1 && filterDoubleMediumTau40TightID_1 && matchDoubleMediumTau40TightID_2 && filterDoubleMediumTau40TightID_2);
           trigger3_match=(passDoubleTightTau40 && mytau1.Pt()>45 && mytau2.Pt()>45 && matchDoubleTightTau40_1 && filterDoubleTightTau40_1 && matchDoubleTightTau40_2 && filterDoubleTightTau40_2);
           trigger1=(passDoubleTightTau35TightID && mytau1.Pt()>40 && mytau2.Pt()>40);
           trigger2=(passDoubleMediumTau40TightID && mytau1.Pt()>45 && mytau2.Pt()>45);
           trigger3=(passDoubleTightTau40 && mytau1.Pt()>45 && mytau2.Pt()>45);
           if (sample!="embedded" && !trigger1_match && !trigger2_match && !trigger3_match) continue;
           if (sample=="embedded" && !trigger1 && !trigger2 && !trigger3) continue;

	   if (mytau1.Pt()<50 && mytau2.Pt()<50) continue;
	
	   //myvar=mtt;
	   float myvar0=mytau2.Pt();
	   float myvar1=(mytau1+mytau2+mymet).Pt();
	   float myvar2=massJets;
           if (numberJets==0 && q_1*q_2<0){
               if ((sample=="data_obs" or isT) && signalRegion)
                   h0tau_OS[k]->Fill(myvar0,myvar,aweight*weight2);
               if ((sample!="data_obs" && isJ) && signalRegion)
                   h0jet_OS[k]->Fill(myvar0,myvar,aweight*weight2);
               if ((sample!="data_obs" && isL) && signalRegion)
                   h0ell_OS[k]->Fill(myvar0,myvar,aweight*weight2);
               if (antiisoRegion1 && sample=="data_obs"){
                   h0tau_AI[k]->Fill(myvar0,myvar,FF1*0.5);
                   h0jet_AI[k]->Fill(myvar0,myvar);
	       }
               if (antiisoRegion2 && sample=="data_obs"){
                   h0tau_AI[k]->Fill(myvar0,myvar,FF2*0.5);
                   h0jet_AI[k]->Fill(myvar0,myvar);
               }
               if ((sample!="data_obs" && (isT or isL)) && antiisoRegion1)
                   h0tau_AI[k]->Fill(myvar0,myvar,aweight*weight2*FF1*0.5);
               if ((sample!="data_obs" && isJ) && antiisoRegion1)
                   h0jet_AI[k]->Fill(myvar0,myvar,aweight*weight2);
               if ((sample!="data_obs" && (isT or isL)) && antiisoRegion2)
                   h0tau_AI[k]->Fill(myvar0,myvar,aweight*weight2*FF2*0.5);
               if ((sample!="data_obs" && isJ) && antiisoRegion2)
                   h0jet_AI[k]->Fill(myvar0,myvar,aweight*weight2);
           }
           if ((numberJets==1 or (numberJets>1 && (myvar1<100 or fabs(jeta_1-jeta_2)<2.5))) && q_1*q_2<0){
               if ((sample=="data_obs" or isT) && signalRegion)
                   h1tau_OS[k]->Fill(myvar1,myvar,aweight*weight2);
               if ((sample!="data_obs" && isJ) && signalRegion)
                   h1jet_OS[k]->Fill(myvar1,myvar,aweight*weight2);
               if ((sample!="data_obs" && isL) && signalRegion)
                   h1ell_OS[k]->Fill(myvar1,myvar,aweight*weight2);
               if (antiisoRegion1 && sample=="data_obs"){
                   h1tau_AI[k]->Fill(myvar1,myvar,FF1*0.5);
                   h1jet_AI[k]->Fill(myvar1,myvar);
	       }
               if (antiisoRegion2 && sample=="data_obs"){
                   h1tau_AI[k]->Fill(myvar1,myvar,FF2*0.5);
                   h1jet_AI[k]->Fill(myvar1,myvar);
               }
               if ((sample!="data_obs" && (isT or isL)) && antiisoRegion1)
                   h1tau_AI[k]->Fill(myvar1,myvar,aweight*weight2*FF1*0.5);
               if ((sample!="data_obs" && isJ) && antiisoRegion1)
                   h1jet_AI[k]->Fill(myvar1,myvar,aweight*weight2);
               if ((sample!="data_obs" && (isT or isL)) && antiisoRegion2)
                   h1tau_AI[k]->Fill(myvar1,myvar,aweight*weight2*FF2*0.5);
               if ((sample!="data_obs" && isJ) && antiisoRegion2)
                   h1jet_AI[k]->Fill(myvar1,myvar,aweight*weight2);
           }
if (numberJets==1 && q_1*q_2<0 && signalRegion) h_weight->Fill(aweight);
           if (numberJets>=2 && myvar1>100 && fabs(jeta_1-jeta_2)>2.5 && q_1*q_2<0){
               if ((sample=="data_obs" or isT) && signalRegion){
                   h2tau_OS[k]->Fill(myvar2,myvar,aweight*weight2);
	       }
               if ((sample!="data_obs" && isJ) && signalRegion)
                   h2jet_OS[k]->Fill(myvar2,myvar,aweight*weight2);
               if ((sample!="data_obs" && isL) && signalRegion)
                   h2ell_OS[k]->Fill(myvar2,myvar,aweight*weight2);
               if (antiisoRegion1 && sample=="data_obs"){
                   h2tau_AI[k]->Fill(myvar2,myvar,FF1*0.5);
                   h2jet_AI[k]->Fill(myvar2,myvar);
	       }
               if (antiisoRegion2 && sample=="data_obs"){
                   h2tau_AI[k]->Fill(myvar2,myvar,FF2*0.5);
                   h2jet_AI[k]->Fill(myvar2,myvar);
               }

               if ((sample!="data_obs" && (isT or isL)) && antiisoRegion1)
                   h2tau_AI[k]->Fill(myvar2,myvar,aweight*weight2*FF1*0.5);
               if ((sample!="data_obs" && isJ) && antiisoRegion1)
                   h2jet_AI[k]->Fill(myvar2,myvar,aweight*weight2);
               if ((sample!="data_obs" && (isT or isL)) && antiisoRegion2)
                   h2tau_AI[k]->Fill(myvar2,myvar,aweight*weight2*FF2*0.5);
               if ((sample!="data_obs" && isJ) && antiisoRegion2)
                   h2jet_AI[k]->Fill(myvar2,myvar,aweight*weight2);
           }
	   float mt1=TMass_F(mytau1.Pt(),mymet.Pt(),mytau1.Px(),mymet.Px(),mytau1.Py(),mymet.Py());
           float mt2=TMass_F(mytau2.Pt(),mymet.Pt(),mytau2.Px(),mymet.Px(),mytau2.Py(),mymet.Py());
	   float myvar3=mt1;//(mytau1+mytau2).M();//mytau1.Pt();
           float myvar4=mytau1.DeltaR(mytau2);//mymet.Pt();//mytau2.Pt();
           float myvar5=mt2;//njets;//mytau1.Eta();
           float myvar6=(mytau1+mytau2+mymet).Pt();//nbtag;//mytau2.Eta();
           if (q_1*q_2<0){
               if ((sample=="data_obs" or isT) && signalRegion)
                   h3tau_OS[k]->Fill(myvar3,aweight*weight2);
               if ((sample!="data_obs" && isJ) && signalRegion)
                   h3jet_OS[k]->Fill(myvar3,aweight*weight2);
               if ((sample!="data_obs" && isL) && signalRegion)
                   h3ell_OS[k]->Fill(myvar3,aweight*weight2);
               if (antiisoRegion1 && sample=="data_obs"){
                   h3tau_AI[k]->Fill(myvar3,FF1*0.5);
                   h3jet_AI[k]->Fill(myvar3);
               }
               if (antiisoRegion2 && sample=="data_obs"){
                   h3tau_AI[k]->Fill(myvar3,FF2*0.5);
                   h3jet_AI[k]->Fill(myvar3);
               }

               if ((sample!="data_obs" && (isT or isL)) && antiisoRegion1)
                   h3tau_AI[k]->Fill(myvar3,aweight*weight2*FF1*0.5);
               if ((sample!="data_obs" && isJ) && antiisoRegion1)
                   h3jet_AI[k]->Fill(myvar3,aweight*weight2);
               if ((sample!="data_obs" && (isT or isL)) && antiisoRegion2)
                   h3tau_AI[k]->Fill(myvar3,aweight*weight2*FF2*0.5);
               if ((sample!="data_obs" && isJ) && antiisoRegion2)
                   h3jet_AI[k]->Fill(myvar3,aweight*weight2);
           }
           if (q_1*q_2<0){
               if ((sample=="data_obs" or isT) && signalRegion)
                   h4tau_OS[k]->Fill(myvar4,aweight*weight2);
               if ((sample!="data_obs" && isJ) && signalRegion)
                   h4jet_OS[k]->Fill(myvar4,aweight*weight2);
               if ((sample!="data_obs" && isL) && signalRegion)
                   h4ell_OS[k]->Fill(myvar4,aweight*weight2);
               if (antiisoRegion1 && sample=="data_obs"){
                   h4tau_AI[k]->Fill(myvar4,FF1*0.5);
                   h4jet_AI[k]->Fill(myvar4);
               }
               if (antiisoRegion2 && sample=="data_obs"){
                   h4tau_AI[k]->Fill(myvar4,FF2*0.5);
                   h4jet_AI[k]->Fill(myvar4);
               }

               if ((sample!="data_obs" && (isT or isL)) && antiisoRegion1)
                   h4tau_AI[k]->Fill(myvar4,aweight*weight2*FF1*0.5);
               if ((sample!="data_obs" && isJ) && antiisoRegion1)
                   h4jet_AI[k]->Fill(myvar4,aweight*weight2);
               if ((sample!="data_obs" && (isT or isL)) && antiisoRegion2)
                   h4tau_AI[k]->Fill(myvar4,aweight*weight2*FF2*0.5);
               if ((sample!="data_obs" && isJ) && antiisoRegion2)
                   h4jet_AI[k]->Fill(myvar4,aweight*weight2);
           }
           if (q_1*q_2<0){
               if ((sample=="data_obs" or isT) && signalRegion)
                   h5tau_OS[k]->Fill(myvar5,aweight*weight2);
               if ((sample!="data_obs" && isJ) && signalRegion)
                   h5jet_OS[k]->Fill(myvar5,aweight*weight2);
               if ((sample!="data_obs" && isL) && signalRegion)
                   h5ell_OS[k]->Fill(myvar5,aweight*weight2);
               if (antiisoRegion1 && sample=="data_obs"){
                   h5tau_AI[k]->Fill(myvar5,FF1*0.5);
                   h5jet_AI[k]->Fill(myvar5);
               }
               if (antiisoRegion2 && sample=="data_obs"){
                   h5tau_AI[k]->Fill(myvar5,FF2*0.5);
                   h5jet_AI[k]->Fill(myvar5);
               }

               if ((sample!="data_obs" && (isT or isL)) && antiisoRegion1)
                   h5tau_AI[k]->Fill(myvar5,aweight*weight2*FF1*0.5);
               if ((sample!="data_obs" && isJ) && antiisoRegion1)
                   h5jet_AI[k]->Fill(myvar5,aweight*weight2);
               if ((sample!="data_obs" && (isT or isL)) && antiisoRegion2)
                   h5tau_AI[k]->Fill(myvar5,aweight*weight2*FF2*0.5);
               if ((sample!="data_obs" && isJ) && antiisoRegion2)
                   h5jet_AI[k]->Fill(myvar5,aweight*weight2);
           }
           if (q_1*q_2<0){
               if ((sample=="data_obs" or isT) && signalRegion)
                   h6tau_OS[k]->Fill(myvar6,aweight*weight2);
               if ((sample!="data_obs" && isJ) && signalRegion)
                   h6jet_OS[k]->Fill(myvar6,aweight*weight2);
               if ((sample!="data_obs" && isL) && signalRegion)
                   h6ell_OS[k]->Fill(myvar6,aweight*weight2);
               if (antiisoRegion1 && sample=="data_obs"){
                   h6tau_AI[k]->Fill(myvar6,FF1*0.5);
                   h6jet_AI[k]->Fill(myvar6);
               }
               if (antiisoRegion2 && sample=="data_obs"){
                   h6tau_AI[k]->Fill(myvar6,FF2*0.5);
                   h6jet_AI[k]->Fill(myvar6);
               }

               if ((sample!="data_obs" && (isT or isL)) && antiisoRegion1)
                   h6tau_AI[k]->Fill(myvar6,aweight*weight2*FF1*0.5);
               if ((sample!="data_obs" && isJ) && antiisoRegion1)
                   h6jet_AI[k]->Fill(myvar6,aweight*weight2);
               if ((sample!="data_obs" && (isT or isL)) && antiisoRegion2)
                   h6tau_AI[k]->Fill(myvar6,aweight*weight2*FF2*0.5);
               if ((sample!="data_obs" && isJ) && antiisoRegion2)
                   h6jet_AI[k]->Fill(myvar6,aweight*weight2);
           }
	} // end of loop over nbhist

    } // end of loop over events
    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();
h_weight->Write();

    TString postfix=postfixFF[0];

    TDirectory *OS0jet =fout->mkdir("tt_0jet");
    OS0jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else if (sample=="embedded") postfix=postfixEmb[k];
       else postfix=postfixMC[k];
       if (sample=="data_obs" && k>0) continue;
       if (name=="DY"){
          h0tau_OS[k]->SetName("ZTT"+postfix);
          h0jet_OS[k]->SetName("ZJ"+postfix);
          h0ell_OS[k]->SetName("ZL"+postfix);
          h0tau_OS[k]->Write();
          h0jet_OS[k]->Write();
          h0ell_OS[k]->Write();
       }
       else if (name=="TT"){
          h0tau_OS[k]->SetName("TTT"+postfix);
          h0jet_OS[k]->SetName("TTJ"+postfix);
          h0ell_OS[k]->SetName("TTL"+postfix);
          h0tau_OS[k]->Write();
          h0jet_OS[k]->Write();
          h0ell_OS[k]->Write();
       }
       else if (name=="VV"){
          h0tau_OS[k]->SetName("VVT"+postfix);
          h0jet_OS[k]->SetName("VVJ"+postfix);
          h0ell_OS[k]->SetName("VVL"+postfix);
          h0tau_OS[k]->Write();
          h0jet_OS[k]->Write();
          h0ell_OS[k]->Write();
       }
       else{
          h0tau_OS[k]->SetName(name.c_str()+postfix);
          h0tau_OS[k]->Add(h0jet_OS[k]);
          h0tau_OS[k]->Add(h0ell_OS[k]);
          h0tau_OS[k]->Write();
       }
    }
    TDirectory *AI0jet =fout->mkdir("AI0jet");
    AI0jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else if (sample=="embedded") postfix=postfixEmb[k];
       else postfix=postfixMC[k];
       if (name=="DY"){
          h0tau_AI[k]->SetName("ZTT"+postfix);
          h0jet_AI[k]->SetName("ZJ"+postfix);
          h0tau_AI[k]->Write();
          h0jet_AI[k]->Write();
       }
       else if (name=="TT"){
          h0tau_AI[k]->SetName("TTT"+postfix);
          h0jet_AI[k]->SetName("TTJ"+postfix);
          h0tau_AI[k]->Write();
          h0jet_AI[k]->Write();
       }
       else if (name=="VV"){
          h0tau_AI[k]->SetName("VVT"+postfix);
          h0jet_AI[k]->SetName("VVJ"+postfix);
          h0tau_AI[k]->Write();
          h0jet_AI[k]->Write();
       }
       else if (sample=="data_obs"){
          h0tau_AI[k]->SetName("reweighted_data_obs"+postfix);
          h0jet_AI[k]->SetName("data_obs"+postfix);
          h0tau_AI[k]->Write();
          h0jet_AI[k]->Write();
       }
       else{
          h0tau_AI[k]->SetName(name.c_str()+postfix);
          h0tau_AI[k]->Add(h0jet_AI[k]);
          h0tau_AI[k]->Write();
       }
    }

    TDirectory *OS1jet =fout->mkdir("tt_boosted");
    OS1jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else if (sample=="embedded") postfix=postfixEmb[k];
       else postfix=postfixMC[k];
       if (sample=="data_obs" && k>0) continue;
       if (name=="DY"){
          h1tau_OS[k]->SetName("ZTT"+postfix);
          h1jet_OS[k]->SetName("ZJ"+postfix);
          h1ell_OS[k]->SetName("ZL"+postfix);
          h1tau_OS[k]->Write();
          h1jet_OS[k]->Write();
          h1ell_OS[k]->Write();
       }
       else if (name=="TT"){
          h1tau_OS[k]->SetName("TTT"+postfix);
          h1jet_OS[k]->SetName("TTJ"+postfix);
          h1ell_OS[k]->SetName("TTL"+postfix);
          h1tau_OS[k]->Write();
          h1jet_OS[k]->Write();
          h1ell_OS[k]->Write();
       }
       else if (name=="VV"){
          h1tau_OS[k]->SetName("VVT"+postfix);
          h1jet_OS[k]->SetName("VVJ"+postfix);
          h1ell_OS[k]->SetName("VVL"+postfix);
          h1tau_OS[k]->Write();
          h1jet_OS[k]->Write();
          h1ell_OS[k]->Write();
       }
       else{
          h1tau_OS[k]->SetName(name.c_str()+postfix);
          h1tau_OS[k]->Add(h1jet_OS[k]);
          h1tau_OS[k]->Add(h1ell_OS[k]);
          h1tau_OS[k]->Write();
       }
    }

    TDirectory *AI1jet =fout->mkdir("AIboosted");
    AI1jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else if (sample=="embedded") postfix=postfixEmb[k];
       else postfix=postfixMC[k];
       if (name=="DY"){
          h1tau_AI[k]->SetName("ZTT"+postfix);
          h1jet_AI[k]->SetName("ZJ"+postfix);
          h1tau_AI[k]->Write();
          h1jet_AI[k]->Write();
       }
       else if (name=="TT"){
          h1tau_AI[k]->SetName("TTT"+postfix);
          h1jet_AI[k]->SetName("TTJ"+postfix);
          h1tau_AI[k]->Write();
          h1jet_AI[k]->Write();
       }
       else if (name=="VV"){
          h1tau_AI[k]->SetName("VVT"+postfix);
          h1jet_AI[k]->SetName("VVJ"+postfix);
          h1tau_AI[k]->Write();
          h1jet_AI[k]->Write();
       }
       else if (sample=="data_obs"){
          h1tau_AI[k]->SetName("reweighted_data_obs"+postfix);
          h1jet_AI[k]->SetName("data_obs"+postfix);
          h1tau_AI[k]->Write();
          h1jet_AI[k]->Write();
       }
       else{
          h1tau_AI[k]->SetName(name.c_str()+postfix);
          h1tau_AI[k]->Add(h1jet_AI[k]);
          h1tau_AI[k]->Write();
       }
    }

    TDirectory *OS2jet =fout->mkdir("tt_vbf");
    OS2jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else if (sample=="embedded") postfix=postfixEmb[k];
       else postfix=postfixMC[k];
       if (sample=="data_obs" && k>0 ) continue;
       if (name=="DY"){
          h2tau_OS[k]->SetName("ZTT"+postfix);
          h2jet_OS[k]->SetName("ZJ"+postfix);
          h2ell_OS[k]->SetName("ZL"+postfix);
          h2tau_OS[k]->Write();
          h2jet_OS[k]->Write();
          h2ell_OS[k]->Write();
       }
       else if (name=="TT"){
          h2tau_OS[k]->SetName("TTT"+postfix);
          h2jet_OS[k]->SetName("TTJ"+postfix);
          h2ell_OS[k]->SetName("TTL"+postfix);
          h2tau_OS[k]->Write();
          h2jet_OS[k]->Write();
          h2ell_OS[k]->Write();
       }
       else if (name=="VV"){
          h2tau_OS[k]->SetName("VVT"+postfix);
          h2jet_OS[k]->SetName("VVJ"+postfix);
          h2ell_OS[k]->SetName("VVL"+postfix);
          h2tau_OS[k]->Write();
          h2jet_OS[k]->Write();
          h2ell_OS[k]->Write();
       }
       else{
          h2tau_OS[k]->SetName(name.c_str()+postfix);
          h2tau_OS[k]->Add(h2jet_OS[k]);
          h2tau_OS[k]->Add(h2ell_OS[k]);
          h2tau_OS[k]->Write();
       }
    }

    TDirectory *AI2jet =fout->mkdir("AIvbf");
    AI2jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else if (sample=="embedded") postfix=postfixEmb[k];
       else postfix=postfixMC[k];
       if (name=="DY"){
          h2tau_AI[k]->SetName("ZTT"+postfix);
          h2jet_AI[k]->SetName("ZJ"+postfix);
          h2tau_AI[k]->Write();
          h2jet_AI[k]->Write();
       }
       else if (name=="TT"){
          h2tau_AI[k]->SetName("TTT"+postfix);
          h2jet_AI[k]->SetName("TTJ"+postfix);
          h2tau_AI[k]->Write();
          h2jet_AI[k]->Write();
       }
       else if (name=="VV"){
          h2tau_AI[k]->SetName("VVT"+postfix);
          h2jet_AI[k]->SetName("VVJ"+postfix);
          h2tau_AI[k]->Write();
          h2jet_AI[k]->Write();
       }
       else if (sample=="data_obs"){
          h2tau_AI[k]->SetName("reweighted_data_obs"+postfix);
          h2jet_AI[k]->SetName("data_obs"+postfix);
          h2tau_AI[k]->Write();
          h2jet_AI[k]->Write();
       }
       else{
          h2tau_AI[k]->SetName(name.c_str()+postfix);
          h2tau_AI[k]->Add(h2jet_AI[k]);
          h2tau_AI[k]->Write();
       }
    }

    TDirectory *OS3jet =fout->mkdir("tt_1jet");
    OS3jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else if (sample=="embedded") postfix=postfixEmb[k];
       else postfix=postfixMC[k];
       if (sample=="data_obs" && k>0 ) continue;
       if (name=="DY"){
          h3tau_OS[k]->SetName("ZTT"+postfix);
          h3jet_OS[k]->SetName("ZJ"+postfix);
          h3ell_OS[k]->SetName("ZL"+postfix);
          h3tau_OS[k]->Write();
          h3jet_OS[k]->Write();
          h3ell_OS[k]->Write();
       }
       else if (name=="TT"){
          h3tau_OS[k]->SetName("TTT"+postfix);
          h3jet_OS[k]->SetName("TTJ"+postfix);
          h3ell_OS[k]->SetName("TTL"+postfix);
          h3tau_OS[k]->Write();
          h3jet_OS[k]->Write();
          h3ell_OS[k]->Write();
       }
       else if (name=="VV"){
          h3tau_OS[k]->SetName("VVT"+postfix);
          h3jet_OS[k]->SetName("VVJ"+postfix);
          h3ell_OS[k]->SetName("VVL"+postfix);
          h3tau_OS[k]->Write();
          h3jet_OS[k]->Write();
          h3ell_OS[k]->Write();
       }
       else{
          h3tau_OS[k]->SetName(name.c_str()+postfix);
          h3tau_OS[k]->Add(h3jet_OS[k]);
          h3tau_OS[k]->Add(h3ell_OS[k]);
          h3tau_OS[k]->Write();
       }
    }

    TDirectory *AI3jet =fout->mkdir("AI1jet");
    AI3jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else if (sample=="embedded") postfix=postfixEmb[k];
       else postfix=postfixMC[k];
       if (name=="DY"){
          h3tau_AI[k]->SetName("ZTT"+postfix);
          h3jet_AI[k]->SetName("ZJ"+postfix);
          h3tau_AI[k]->Write();
          h3jet_AI[k]->Write();
       }
       else if (name=="TT"){
          h3tau_AI[k]->SetName("TTT"+postfix);
          h3jet_AI[k]->SetName("TTJ"+postfix);
          h3tau_AI[k]->Write();
          h3jet_AI[k]->Write();
       }
       else if (name=="VV"){
          h3tau_AI[k]->SetName("VVT"+postfix);
          h3jet_AI[k]->SetName("VVJ"+postfix);
          h3tau_AI[k]->Write();
          h3jet_AI[k]->Write();
       }
       else if (sample=="data_obs"){
          h3tau_AI[k]->SetName("reweighted_data_obs"+postfix);
          h3jet_AI[k]->SetName("data_obs"+postfix);
          h3tau_AI[k]->Write();
          h3jet_AI[k]->Write();
       }
       else{
          h3tau_AI[k]->SetName(name.c_str()+postfix);
          h3tau_AI[k]->Add(h3jet_AI[k]);
          h3tau_AI[k]->Write();
       }
    }

    TDirectory *OS4jet =fout->mkdir("tt_gg2jets");
    OS4jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else if (sample=="embedded") postfix=postfixEmb[k];
       else postfix=postfixMC[k];
       if (sample=="data_obs" && k>0 ) continue;
       if (name=="DY"){
          h4tau_OS[k]->SetName("ZTT"+postfix);
          h4jet_OS[k]->SetName("ZJ"+postfix);
          h4ell_OS[k]->SetName("ZL"+postfix);
          h4tau_OS[k]->Write();
          h4jet_OS[k]->Write();
          h4ell_OS[k]->Write();
       }
       else if (name=="TT"){
          h4tau_OS[k]->SetName("TTT"+postfix);
          h4jet_OS[k]->SetName("TTJ"+postfix);
          h4ell_OS[k]->SetName("TTL"+postfix);
          h4tau_OS[k]->Write();
          h4jet_OS[k]->Write();
          h4ell_OS[k]->Write();
       }
       else if (name=="VV"){
          h4tau_OS[k]->SetName("VVT"+postfix);
          h4jet_OS[k]->SetName("VVJ"+postfix);
          h4ell_OS[k]->SetName("VVL"+postfix);
          h4tau_OS[k]->Write();
          h4jet_OS[k]->Write();
          h4ell_OS[k]->Write();
       }
       else{
          h4tau_OS[k]->SetName(name.c_str()+postfix);
          h4tau_OS[k]->Add(h4jet_OS[k]);
          h4tau_OS[k]->Add(h4ell_OS[k]);
          h4tau_OS[k]->Write();
       }
    }

    TDirectory *AI4jet =fout->mkdir("AIgg2jets");
    AI4jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else if (sample=="embedded") postfix=postfixEmb[k];
       else postfix=postfixMC[k];
       if (name=="DY"){
          h4tau_AI[k]->SetName("ZTT"+postfix);
          h4jet_AI[k]->SetName("ZJ"+postfix);
          h4tau_AI[k]->Write();
          h4jet_AI[k]->Write();
       }
       else if (name=="TT"){
          h4tau_AI[k]->SetName("TTT"+postfix);
          h4jet_AI[k]->SetName("TTJ"+postfix);
          h4tau_AI[k]->Write();
          h4jet_AI[k]->Write();
       }
       else if (name=="VV"){
          h4tau_AI[k]->SetName("VVT"+postfix);
          h4jet_AI[k]->SetName("VVJ"+postfix);
          h4tau_AI[k]->Write();
          h4jet_AI[k]->Write();
       }
       else if (sample=="data_obs"){
          h4tau_AI[k]->SetName("reweighted_data_obs"+postfix);
          h4jet_AI[k]->SetName("data_obs"+postfix);
          h4tau_AI[k]->Write();
          h4jet_AI[k]->Write();
       }
       else{
          h4tau_AI[k]->SetName(name.c_str()+postfix);
          h4tau_AI[k]->Add(h4jet_AI[k]);
          h4tau_AI[k]->Write();
       }
    }

    TDirectory *OS5jet =fout->mkdir("tt_vh2jets");
    OS5jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else if (sample=="embedded") postfix=postfixEmb[k];
       else postfix=postfixMC[k];
       if (sample=="data_obs" && k>0 ) continue;
       if (name=="DY"){
          h5tau_OS[k]->SetName("ZTT"+postfix);
          h5jet_OS[k]->SetName("ZJ"+postfix);
          h5ell_OS[k]->SetName("ZL"+postfix);
          h5tau_OS[k]->Write();
          h5jet_OS[k]->Write();
          h5ell_OS[k]->Write();
       }
       else if (name=="TT"){
          h5tau_OS[k]->SetName("TTT"+postfix);
          h5jet_OS[k]->SetName("TTJ"+postfix);
          h5ell_OS[k]->SetName("TTL"+postfix);
          h5tau_OS[k]->Write();
          h5jet_OS[k]->Write();
          h5ell_OS[k]->Write();
       }
       else if (name=="VV"){
          h5tau_OS[k]->SetName("VVT"+postfix);
          h5jet_OS[k]->SetName("VVJ"+postfix);
          h5ell_OS[k]->SetName("VVL"+postfix);
          h5tau_OS[k]->Write();
          h5jet_OS[k]->Write();
          h5ell_OS[k]->Write();
       }
       else{
          h5tau_OS[k]->SetName(name.c_str()+postfix);
          h5tau_OS[k]->Add(h5jet_OS[k]);
          h5tau_OS[k]->Add(h5ell_OS[k]);
          h5tau_OS[k]->Write();
       }
    }

    TDirectory *AI5jet =fout->mkdir("AIvh2jets");
    AI5jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else if (sample=="embedded") postfix=postfixEmb[k];
       else postfix=postfixMC[k];
       if (name=="DY"){
          h5tau_AI[k]->SetName("ZTT"+postfix);
          h5jet_AI[k]->SetName("ZJ"+postfix);
          h5tau_AI[k]->Write();
          h5jet_AI[k]->Write();
       }
       else if (name=="TT"){
          h5tau_AI[k]->SetName("TTT"+postfix);
          h5jet_AI[k]->SetName("TTJ"+postfix);
          h5tau_AI[k]->Write();
          h5jet_AI[k]->Write();
       }
       else if (name=="VV"){
          h5tau_AI[k]->SetName("VVT"+postfix);
          h5jet_AI[k]->SetName("VVJ"+postfix);
          h5tau_AI[k]->Write();
          h5jet_AI[k]->Write();
       }
       else if (sample=="data_obs"){
          h5tau_AI[k]->SetName("reweighted_data_obs"+postfix);
          h5jet_AI[k]->SetName("data_obs"+postfix);
          h5tau_AI[k]->Write();
          h5jet_AI[k]->Write();
       }
       else{
          h5tau_AI[k]->SetName(name.c_str()+postfix);
          h5tau_AI[k]->Add(h5jet_AI[k]);
          h5tau_AI[k]->Write();
       }
    }

    TDirectory *OS6jet =fout->mkdir("tt_vbf2");
    OS6jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else if (sample=="embedded") postfix=postfixEmb[k];
       else postfix=postfixMC[k];
       if (sample=="data_obs" && k>0 ) continue;
       if (name=="DY"){
          h6tau_OS[k]->SetName("ZTT"+postfix);
          h6jet_OS[k]->SetName("ZJ"+postfix);
          h6ell_OS[k]->SetName("ZL"+postfix);
          h6tau_OS[k]->Write();
          h6jet_OS[k]->Write();
          h6ell_OS[k]->Write();
       }
       else if (name=="TT"){
          h6tau_OS[k]->SetName("TTT"+postfix);
          h6jet_OS[k]->SetName("TTJ"+postfix);
          h6ell_OS[k]->SetName("TTL"+postfix);
          h6tau_OS[k]->Write();
          h6jet_OS[k]->Write();
          h6ell_OS[k]->Write();
       }
       else if (name=="VV"){
          h6tau_OS[k]->SetName("VVT"+postfix);
          h6jet_OS[k]->SetName("VVJ"+postfix);
          h6ell_OS[k]->SetName("VVL"+postfix);
          h6tau_OS[k]->Write();
          h6jet_OS[k]->Write();
          h6ell_OS[k]->Write();
       }
       else{
          h6tau_OS[k]->SetName(name.c_str()+postfix);
          h6tau_OS[k]->Add(h6jet_OS[k]);
          h6tau_OS[k]->Add(h6ell_OS[k]);
          h6tau_OS[k]->Write();
       }
    }

    TDirectory *AI6jet =fout->mkdir("AIvbf2");
    AI6jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else if (sample=="embedded") postfix=postfixEmb[k];
       else postfix=postfixMC[k];
       if (name=="DY"){
          h6tau_AI[k]->SetName("ZTT"+postfix);
          h6jet_AI[k]->SetName("ZJ"+postfix);
          h6tau_AI[k]->Write();
          h6jet_AI[k]->Write();
       }
       else if (name=="TT"){
          h6tau_AI[k]->SetName("TTT"+postfix);
          h6jet_AI[k]->SetName("TTJ"+postfix);
          h6tau_AI[k]->Write();
          h6jet_AI[k]->Write();
       }
       else if (name=="VV"){
          h6tau_AI[k]->SetName("VVT"+postfix);
          h6jet_AI[k]->SetName("VVJ"+postfix);
          h6tau_AI[k]->Write();
          h6jet_AI[k]->Write();
       }
       else if (sample=="data_obs"){
          h6tau_AI[k]->SetName("reweighted_data_obs"+postfix);
          h6jet_AI[k]->SetName("data_obs"+postfix);
          h6tau_AI[k]->Write();
          h6jet_AI[k]->Write();
       }
       else{
          h6tau_AI[k]->SetName(name.c_str()+postfix);
          h6tau_AI[k]->Add(h6jet_AI[k]);
          h6tau_AI[k]->Write();
       }
    }

    fout->Close();
    delete ff1;
    delete ff2;
    ff_file->Close();
    delete wmc;
    delete w;
} 


