#include <TH2.h>
#include "ApplyFF_mt.h"
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

using namespace std;

int main(int argc, char** argv) {

    int do_control_plots=1;

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
    TTree *arbre = (TTree*) f_Double->Get("mutau_tree");
    TH1F* nbevt = (TH1F*) f_Double->Get("nevents");
    float ngen = nbevt->GetBinContent(2);

    float xs=1.0; float weight=1.0; float luminosity=59740.0;
    if (sample=="DY" or sample=="ZL" or sample=="ZTT" or sample=="ZJ" or sample=="ZLL"){ xs=6225.42; weight=luminosity*xs/ngen;}
    if (sample=="DYlow"){ xs=21658.0; weight=luminosity*xs/ngen;}
    else if (sample=="TT" or sample=="TTT" or sample=="TTJ") {xs=831.76; weight=luminosity*xs/ngen;}
    else if (sample=="TTTo2L2Nu") {xs=88.29; weight=luminosity*xs/ngen;}
    else if (sample=="TTToSemiLeptonic") {xs=365.35; weight=luminosity*xs/ngen;}
    else if (sample=="TTToHadronic") {xs=377.96; weight=luminosity*xs/ngen;}
    else if (sample=="W") {xs=61526.7; weight=luminosity*xs/ngen;}
    else if (sample=="data_obs"){weight=1.0;}
    else if (sample=="embedded"){weight=1.0;}
    else if (sample=="ST_tW_antitop") {xs=35.85; weight=luminosity*xs/ngen;}
    else if (sample=="ST_tW_top") {xs=35.85; weight=luminosity*xs/ngen;}
    else if (sample=="ST_t_antitop") {xs=80.94; weight=luminosity*xs/ngen;}
    else if (sample=="ST_t_top") {xs=136.02; weight=luminosity*xs/ngen;}
    else if (sample=="ggH_htt125") {xs=48.58*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="qqH_htt125") {xs=3.782*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="WplusH125") {xs=0.840*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="WminusH125") {xs=0.5328*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="ZH125") {xs=0.7612*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="GGZH125") {xs=0.1227*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="GGZHLLTT125") {xs=0.1227*0.0627*3*0.033658; weight=luminosity*xs/ngen;}
    else if (sample=="GGZHNNTT125") {xs=0.1227*0.0627*0.2000; weight=luminosity*xs/ngen;}
    else if (sample=="GGZHQQTT125") {xs=0.1227*0.0627*0.6991; weight=luminosity*xs/ngen;}
    else if (sample=="GGHWW") {xs=48.58*0.2137*0.3258*0.3258; weight=luminosity*xs/ngen;}
    else if (sample=="VBFHWW") {xs=3.782*0.2137*0.3258*0.3258; weight=luminosity*xs/ngen;}
    else if (sample=="WplusHWW") {xs=0.840*0.2137; weight=luminosity*xs/ngen;}
    else if (sample=="WminusHWW") {xs=0.5328*0.2137; weight=luminosity*xs/ngen;}
    else if (sample=="ZHWW") {xs=0.7612*0.2137; weight=luminosity*xs/ngen;}
    else if (sample=="GGZHWW") {xs=0.1227*0.2137; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ") {xs=16.523; weight=luminosity*xs/ngen;}
    else if (sample=="WZ") {xs=47.13; weight=luminosity*xs/ngen;}
    else if (sample=="WW") {xs=118.7; weight=luminosity*xs/ngen;}
    else if (sample=="WGLNu") {xs=489.0; weight=luminosity*xs/ngen;}
    else if (sample=="EWKWminus") {xs=23.24; weight=luminosity*xs/ngen;}
    else if (sample=="EWKWplus") {xs=29.59; weight=luminosity*xs/ngen;}
    else if (sample=="EWKZLL") {xs=4.321; weight=luminosity*xs/ngen;}
    else if (sample=="EWKZNuNu") {xs=10.66; weight=luminosity*xs/ngen;}

    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(10);

    arbre->SetBranchAddress("Rivet_higgsPt", &Rivet_higgsPt);
    arbre->SetBranchAddress("Rivet_nJets30", &Rivet_nJets30);
    arbre->SetBranchAddress("Rivet_stage0_cat", &Rivet_stage0_cat);
    arbre->SetBranchAddress("Rivet_stage1p1_cat", &Rivet_stage1p1_cat);
    arbre->SetBranchAddress("Rivet_stage1_cat_pTjet30GeV", &Rivet_stage1_cat_pTjet30GeV);

    arbre->SetBranchAddress("passMu24", &passMu24);
    arbre->SetBranchAddress("passMu27", &passMu27);
    arbre->SetBranchAddress("passMu20Tau27", &passMu20Tau27);
    arbre->SetBranchAddress("passMu20HPSTau27", &passMu20HPSTau27);

    arbre->SetBranchAddress("matchEmbFilter_Mu20Tau27_1", &matchEmbFilter_Mu20Tau27_1);
    arbre->SetBranchAddress("matchEmbFilter_Mu24_1", &matchEmbFilter_Mu24_1);
    arbre->SetBranchAddress("matchEmbFilter_Mu27_1", &matchEmbFilter_Mu27_1);
    arbre->SetBranchAddress("matchEmbFilter_Mu20Tau27_2", &matchEmbFilter_Mu20Tau27_2);
    arbre->SetBranchAddress("matchEmbFilter_Mu20HPSTau27_2", &matchEmbFilter_Mu20HPSTau27_2);

    arbre->SetBranchAddress("matchMu24_1", &matchMu24_1);
    arbre->SetBranchAddress("matchMu27_1", &matchMu27_1);
    arbre->SetBranchAddress("matchMu20Tau27_1", &matchMu20Tau27_1);
    arbre->SetBranchAddress("matchMu20Tau27_2", &matchMu20Tau27_2);
    arbre->SetBranchAddress("matchMu20HPSTau27_1", &matchMu20HPSTau27_1);
    arbre->SetBranchAddress("matchMu20HPSTau27_2", &matchMu20HPSTau27_2);
    arbre->SetBranchAddress("filterMu24_1", &filterMu24_1);
    arbre->SetBranchAddress("filterMu27_1", &filterMu27_1);
    arbre->SetBranchAddress("filterMu20Tau27_1", &filterMu20Tau27_1);
    arbre->SetBranchAddress("filterMu20Tau27_2", &filterMu20Tau27_2);
    arbre->SetBranchAddress("filterMu20HPSTau27_1", &filterMu20HPSTau27_1);
    arbre->SetBranchAddress("filterMu20HPSTau27_2", &filterMu20HPSTau27_2);

    arbre->SetBranchAddress("genpt_1", &genpt_1);
    arbre->SetBranchAddress("geneta_1", &geneta_1);
    arbre->SetBranchAddress("genpt_2", &genpt_2);
    arbre->SetBranchAddress("geneta_2", &geneta_2);

    arbre->SetBranchAddress("run", &run);
    arbre->SetBranchAddress("lumi", &lumi);
    arbre->SetBranchAddress("evt", &evt);
    arbre->SetBranchAddress("npv", &npv);
    arbre->SetBranchAddress("pt_1", &pt_1);
    arbre->SetBranchAddress("phi_1", &phi_1);
    arbre->SetBranchAddress("eta_1", &eta_1);
    arbre->SetBranchAddress("iso_1", &iso_1);
    arbre->SetBranchAddress("isoDB_1", &isoDB_1);
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
    arbre->SetBranchAddress("njets_JetEC2Down", &njets_JetEC2Down);
    arbre->SetBranchAddress("njets_JetEC2Up", &njets_JetEC2Up);
    arbre->SetBranchAddress("mjj_JetEC2Down", &mjj_JetEC2Down);
    arbre->SetBranchAddress("mjj_JetEC2Up", &mjj_JetEC2Up);
    arbre->SetBranchAddress("m_sv_ResponseDown", &m_sv_ResponseDown);
    arbre->SetBranchAddress("m_sv_ResponseUp", &m_sv_ResponseUp);
    arbre->SetBranchAddress("m_sv_ResolutionDown", &m_sv_ResolutionDown);
    arbre->SetBranchAddress("m_sv_ResolutionUp", &m_sv_ResolutionUp);
    arbre->SetBranchAddress("m_sv_JetRelativeSampleUp", &m_sv_JetRelativeSampleUp);
    arbre->SetBranchAddress("m_sv_JetRelativeSampleDown", &m_sv_JetRelativeSampleDown);
    arbre->SetBranchAddress("m_sv_JetRelativeBalUp", &m_sv_JetRelativeBalUp);
    arbre->SetBranchAddress("m_sv_JetRelativeBalDown", &m_sv_JetRelativeBalDown);
    arbre->SetBranchAddress("m_sv_JetEta3to5Up", &m_sv_JetEta3to5Up);
    arbre->SetBranchAddress("m_sv_JetEta3to5Down", &m_sv_JetEta3to5Down);
    arbre->SetBranchAddress("m_sv_JetEta0to3Up", &m_sv_JetEta0to3Up);
    arbre->SetBranchAddress("m_sv_JetEta0to3Down", &m_sv_JetEta0to3Down);
    arbre->SetBranchAddress("m_sv_JetEta0to5Up", &m_sv_JetEta0to5Up);
    arbre->SetBranchAddress("m_sv_JetEta0to5Down", &m_sv_JetEta0to5Down);
    arbre->SetBranchAddress("m_sv_JetEC2Up", &m_sv_JetEC2Up);
    arbre->SetBranchAddress("m_sv_JetEC2Down", &m_sv_JetEC2Down);
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
    arbre->SetBranchAddress("againstElectronVTightMVA6_2",&againstElectronVTightMVA6_2);
    arbre->SetBranchAddress("againstElectronTightMVA62018_2",&againstElectronTightMVA62018_2);
    arbre->SetBranchAddress("againstElectronVTightMVA62018_2",&againstElectronVTightMVA62018_2);
    arbre->SetBranchAddress("againstMuonLoose3_2",&againstMuonLoose3_2);
    arbre->SetBranchAddress("byVVVLooseDeepVSjet_2",&byVVVLooseDeepVSjet_2);
    arbre->SetBranchAddress("byVVLooseDeepVSjet_2",&byVVLooseDeepVSjet_2);
    arbre->SetBranchAddress("byVLooseDeepVSjet_2",&byVLooseDeepVSjet_2);
    arbre->SetBranchAddress("byLooseDeepVSjet_2",&byLooseDeepVSjet_2);
    arbre->SetBranchAddress("byMediumDeepVSjet_2",&byMediumDeepVSjet_2);
    arbre->SetBranchAddress("byTightDeepVSjet_2",&byTightDeepVSjet_2);
    arbre->SetBranchAddress("byVTightDeepVSjet_2",&byVTightDeepVSjet_2);
    arbre->SetBranchAddress("byVVVLooseDeepVSmu_2",&byVVVLooseDeepVSmu_2);
    arbre->SetBranchAddress("byVVLooseDeepVSmu_2",&byVVLooseDeepVSmu_2);
    arbre->SetBranchAddress("byVLooseDeepVSmu_2",&byVLooseDeepVSmu_2);
    arbre->SetBranchAddress("byLooseDeepVSmu_2",&byLooseDeepVSmu_2);
    arbre->SetBranchAddress("byMediumDeepVSmu_2",&byMediumDeepVSmu_2);
    arbre->SetBranchAddress("byTightDeepVSmu_2",&byTightDeepVSmu_2);
    arbre->SetBranchAddress("byVTightDeepVSmu_2",&byVTightDeepVSmu_2);
    arbre->SetBranchAddress("byVVVLooseDeepVSe_2",&byVVVLooseDeepVSe_2);
    arbre->SetBranchAddress("byVVLooseDeepVSe_2",&byVVLooseDeepVSe_2);
    arbre->SetBranchAddress("byVLooseDeepVSe_2",&byVLooseDeepVSe_2);
    arbre->SetBranchAddress("byLooseDeepVSe_2",&byLooseDeepVSe_2);
    arbre->SetBranchAddress("byMediumDeepVSe_2",&byMediumDeepVSe_2);
    arbre->SetBranchAddress("byTightDeepVSe_2",&byTightDeepVSe_2);
    arbre->SetBranchAddress("byVTightDeepVSe_2",&byVTightDeepVSe_2);
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

   bool is_ggh=(name.find("ggH") < 140);
   int nbhist=1;
   /*if (sample=="data_obs") nbhist=1+40;
   else if (is_ggh) nbhist=73; 
   else if (name=="embedded") nbhist=7;
   else nbhist=55;
   if (name=="embedded" or name=="ST" or name=="TT" or name=="DY" or name=="VV") nbhist=nbhist+40;//add FF*/

   std::vector<TH2F*> h0tau_OS;
   std::vector<TH2F*> h1tau_OS;
   std::vector<TH2F*> h2tau_OS;
   std::vector<TH2F*> h0ell_OS;
   std::vector<TH2F*> h1ell_OS;
   std::vector<TH2F*> h2ell_OS;
   std::vector<TH2F*> h0jet_OS;
   std::vector<TH2F*> h1jet_OS;
   std::vector<TH2F*> h2jet_OS;

   std::vector<TH2F*> h0tau_AI;
   std::vector<TH2F*> h1tau_AI;
   std::vector<TH2F*> h2tau_AI;
   std::vector<TH2F*> h0ell_AI;
   std::vector<TH2F*> h1ell_AI;
   std::vector<TH2F*> h2ell_AI;
   std::vector<TH2F*> h0jet_AI;
   std::vector<TH2F*> h1jet_AI;
   std::vector<TH2F*> h2jet_AI;

   std::vector<TH2F*> h3tau_OS;
   std::vector<TH2F*> h4tau_OS;
   std::vector<TH2F*> h5tau_OS;
   std::vector<TH2F*> h6tau_OS;
   std::vector<TH2F*> h7tau_OS;
   std::vector<TH2F*> h8tau_OS;
   std::vector<TH2F*> h3ell_OS;
   std::vector<TH2F*> h4ell_OS;
   std::vector<TH2F*> h5ell_OS;
   std::vector<TH2F*> h6ell_OS;
   std::vector<TH2F*> h7ell_OS;
   std::vector<TH2F*> h8ell_OS;
   std::vector<TH2F*> h3jet_OS;
   std::vector<TH2F*> h4jet_OS;
   std::vector<TH2F*> h5jet_OS;
   std::vector<TH2F*> h6jet_OS;
   std::vector<TH2F*> h7jet_OS;
   std::vector<TH2F*> h8jet_OS;
   std::vector<TH2F*> h3tau_AI;
   std::vector<TH2F*> h4tau_AI;
   std::vector<TH2F*> h5tau_AI;
   std::vector<TH2F*> h6tau_AI;
   std::vector<TH2F*> h7tau_AI;
   std::vector<TH2F*> h8tau_AI;
   std::vector<TH2F*> h3ell_AI;
   std::vector<TH2F*> h4ell_AI;
   std::vector<TH2F*> h5ell_AI;
   std::vector<TH2F*> h6ell_AI;
   std::vector<TH2F*> h7ell_AI;
   std::vector<TH2F*> h8ell_AI;
   std::vector<TH2F*> h3jet_AI;
   std::vector<TH2F*> h4jet_AI;
   std::vector<TH2F*> h5jet_AI;
   std::vector<TH2F*> h6jet_AI;
   std::vector<TH2F*> h7jet_AI;
   std::vector<TH2F*> h8jet_AI;

   /*float bins_mtt0[] = {0,45,65,75,85,95,105,115,155,405};
   float bins_mtt1[] = {0,40,80,90,100,110,120,130,140,150,160,180,200,250};
   float bins_mtt2[] = {0,50,95,115,135,155,200,400};
   float bins_mtt3[] = {50,60,70,80,90,100,110,120,130,140,150,9000}; // 0 jet ptH < 10
   float bins_mtt4[] = {50,60,70,80,90,100,110,120,130,140,150,9000}; // 0 jet ptH > 10
   float bins_mtt5[] = {50,70,90,110,130,150,170,210,250,9000}; // Boosted 1 jet
   float bins_mtt6[] = {50,70,90,110,130,150,170,210,250,9000}; // Boosted > 1 jet
   float bins_mtt7[] = {50,70,90,110,130,150,170,210,250,9000}; // VBF ptH < 200
   float bins_mtt8[] = {50,70,90,110,130,150,170,210,250,9000}; // VBF ptH > 200*/

   // control 1
   float bins_mtt0[] = {20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100};
   float bins_mtt1[] = {30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80};
   float bins_mtt2[] = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100};
   float bins_mtt3[] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250};
   float bins_mtt4[] = {50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175,180,185,190,195,200};
   float bins_mtt5[] = {60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175,180,185,190,195,200,205,210,215,220,225,230,235,240,245,250};
   float bins_mtt6[] = {0,1,2,3,4,5,6,7,8};
   float bins_mtt7[] = {-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5};
   float bins_mtt8[] = {-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5};

   // control 2
   /*float bins_mtt0[] = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140};
   float bins_mtt1[] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,310,320,330,340,350,360,370,380,390,400,410,420,430,440,450,460,470,480,490,500};
   float bins_mtt2[] = {0,0.005,0.01,0.015,0.02,0.025,0.03,0.035,0.04,0.045,0.05,0.055,0.06,0.065,0.07,0.075,0.08,0.085,0.09,0.095,0.10};
   float bins_mtt3[] = {30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150};
   float bins_mtt4[] = {-4.7,-4.5,-4.3,-4.1,-3.9,-3.7,-3.5,-3.3,-3.1,-2.9,-2.7,-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5,2.7,2.9,3.1,3.3,3.5,3.7,3.9,4.1,4.3,4.5,4.7};
   float bins_mtt5[] = {30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120};
   float bins_mtt6[] = {-4.7,-4.5,-4.3,-4.1,-3.9,-3.7,-3.5,-3.3,-3.1,-2.9,-2.7,-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5,2.7,2.9,3.1,3.3,3.5,3.7,3.9,4.1,4.3,4.5,4.7};
   float bins_mtt7[] = {0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4,2.6,2.8,3.0,3.2,3.4,3.6,3.8,4.0,4.2,4.4,4.6,4.8,5.0,5.2,5.4,5.6,5.8,6.0,6.2,6.4,6.6,6.8,7.0};
   float bins_mtt8[] = {0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4,2.6,2.8,3.0,3.2,3.4,3.6,3.8,4.0,4.2,4.4,4.6,4.8,5.0,5.2,5.4,5.6,5.8,6.0,6.2,6.4,6.6,6.8,7.0};*/

   int  binnum_mtt0 = sizeof(bins_mtt0)/sizeof(Float_t) - 1;
   int  binnum_mtt1 = sizeof(bins_mtt1)/sizeof(Float_t) - 1;
   int  binnum_mtt2 = sizeof(bins_mtt2)/sizeof(Float_t) - 1;
   int  binnum_mtt3 = sizeof(bins_mtt3)/sizeof(Float_t) - 1;
   int  binnum_mtt4 = sizeof(bins_mtt4)/sizeof(Float_t) - 1;
   int  binnum_mtt5 = sizeof(bins_mtt5)/sizeof(Float_t) - 1;
   int  binnum_mtt6 = sizeof(bins_mtt6)/sizeof(Float_t) - 1;
   int  binnum_mtt7 = sizeof(bins_mtt7)/sizeof(Float_t) - 1;
   int  binnum_mtt8 = sizeof(bins_mtt8)/sizeof(Float_t) - 1;

   float bins_mtt[] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250};
   int  binnum_mtt = sizeof(bins_mtt)/sizeof(Float_t) - 1;

   /*float bins_mjj[] = {350,700,1000,1500,9000};
   float bins_mjj_low[] = {350,700,1000,1500,9000}; // VBF ptH < 200
   float bins_mjj_high[] = {350,700,1000,1500,9000}; // VBF ptH > 200
   float bins_pth[] = {0,60,120,200,250,300,9000};
   float bins_pth_1[] = {0,60,120,200,250,300,9000}; // Boosted 1
   float bins_pth_2[] = {0,60,120,200,250,300,9000}; // Boosted 2
   float bins_taupt[] = {30,40,50,60,1000};
   float bins_taupt_low[] = {30,40,50,9000}; // 0 jet ptH < 10
   float bins_taupt_high[] = {30,40,50,60,70,9000}; // 0 jet ptH > 10*/

   float bins_mjj[] = {0,100000};
   float bins_mjj_low[] = {0,100000};
   float bins_mjj_high[] = {0,100000};
   float bins_pth[] = {0,100000};
   float bins_pth_1[] = {0,100000};
   float bins_pth_2[] = {0,100000};
   float bins_taupt[] = {0,100000};
   float bins_taupt_low[] = {0,100000};
   float bins_taupt_high[] = {0,100000};

   int  binnum_mjj = sizeof(bins_mjj)/sizeof(Float_t) - 1;
   int  binnum_mjj_low = sizeof(bins_mjj_low)/sizeof(Float_t) - 1;
   int  binnum_mjj_high = sizeof(bins_mjj_high)/sizeof(Float_t) - 1;
   int  binnum_pth = sizeof(bins_pth)/sizeof(Float_t) - 1;
   int  binnum_pth_1 = sizeof(bins_pth_1)/sizeof(Float_t) - 1;
   int  binnum_pth_2 = sizeof(bins_pth_2)/sizeof(Float_t) - 1;
   int  binnum_taupt = sizeof(bins_taupt)/sizeof(Float_t) - 1;
   int  binnum_taupt_low = sizeof(bins_taupt_low)/sizeof(Float_t) - 1;
   int  binnum_taupt_high = sizeof(bins_taupt_high)/sizeof(Float_t) - 1;


   /*float bins_mtt3[] = {0,5,10,15,20,25,30,35,40,45,50,60,70,80,90,100,120,140,160,180,200};
   int  binnum_mtt3 = sizeof(bins_mtt3)/sizeof(Float_t) - 1;
   float bins_mtt4[] = {0,5,10,15,20,25,30,35,40,45,50,60,70,80,90,100,120,140,160,180,200};
   int  binnum_mtt4 = sizeof(bins_mtt4)/sizeof(Float_t) - 1;
   float bins_mtt5[] = {-2.4,-2.2,-2.0,-1.8,-1.6,-1.4,-1.2,-1.0,-0.8,-0.6,-0.4,-0.2,0.0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4};
   int  binnum_mtt5 = sizeof(bins_mtt5)/sizeof(Float_t) - 1;
   float bins_mtt6[] = {-2.4,-2.2,-2.0,-1.8,-1.6,-1.4,-1.2,-1.0,-0.8,-0.6,-0.4,-0.2,0.0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4};
   int  binnum_mtt6 = sizeof(bins_mtt6)/sizeof(Float_t) - 1;*/

   /*float bins_mtt3[] = {0,5,10,15,20,25,30,35,40,45,50,60,70,80,90,100,120,140,160,180,200,250};
   int  binnum_mtt3 = sizeof(bins_mtt3)/sizeof(Float_t) - 1;
   //float bins_mtt4[] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200};
   float bins_mtt4[] = {-4.0,-3.8,-3.6,-3.4,-3.2,-3.0,-2.8,-2.6,-2.4,-2.2,-2.0,-1.8,-1.6,-1.4,-1.2,-1.0,-0.8,-0.6,-0.4,-0.2,0.0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4,2.6,2.8,3.0,3.2,3.4,3.6,3.8,4.0};
   int  binnum_mtt4 = sizeof(bins_mtt4)/sizeof(Float_t) - 1;
   //float bins_mtt5[] = {-2.4,-2.2,-2.0,-1.8,-1.6,-1.4,-1.2,-1.0,-0.8,-0.6,-0.4,-0.2,0.0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4};
   float bins_mtt5[] = {-200,-180,-160,-140,-120,-100,-80,-60,-40,-20,0,20,40,60,80};
   int  binnum_mtt5 = sizeof(bins_mtt5)/sizeof(Float_t) - 1;
   //float bins_mtt6[] = {-2.4,-2.2,-2.0,-1.8,-1.6,-1.4,-1.2,-1.0,-0.8,-0.6,-0.4,-0.2,0.0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4};
   float bins_mtt6[] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200};
   int  binnum_mtt6 = sizeof(bins_mtt6)/sizeof(Float_t) - 1;*/


   TH1F* f0real=new TH1F ("f0real","f0real",binnum_mtt0,bins_mtt0); f0real->Sumw2();
   TH1F* f0jet=new TH1F ("f0jet","f0jet",binnum_mtt0,bins_mtt0); f0jet->Sumw2();
   TH1F* f1real=new TH1F ("f1real","f1real",binnum_mtt1,bins_mtt1); f1real->Sumw2();
   TH1F* f1jet=new TH1F ("f1jet","f1jet",binnum_mtt1,bins_mtt1); f1jet->Sumw2();
   TH1F* f2real=new TH1F ("f2real","f2real",binnum_mtt2,bins_mtt2); f2real->Sumw2();
   TH1F* f2jet=new TH1F ("f2jet","f2jet",binnum_mtt2,bins_mtt2); f2jet->Sumw2();
   TH1F* f3real=new TH1F ("f3real","f3real",binnum_mtt3,bins_mtt3); f3real->Sumw2();
   TH1F* f3jet=new TH1F ("f3jet","f3jet",binnum_mtt3,bins_mtt3); f3jet->Sumw2();
   TH1F* f4real=new TH1F ("f4real","f4real",binnum_mtt4,bins_mtt4); f4real->Sumw2();
   TH1F* f4jet=new TH1F ("f4jet","f4jet",binnum_mtt4,bins_mtt4); f4jet->Sumw2();
   TH1F* f5real=new TH1F ("f5real","f5real",binnum_mtt5,bins_mtt5); f5real->Sumw2();
   TH1F* f5jet=new TH1F ("f5jet","f5jet",binnum_mtt5,bins_mtt5); f5jet->Sumw2();
   TH1F* f6real=new TH1F ("f6real","f6real",binnum_mtt6,bins_mtt6); f6real->Sumw2();
   TH1F* f6jet=new TH1F ("f6jet","f6jet",binnum_mtt6,bins_mtt6); f6jet->Sumw2();
   TH1F* f7real=new TH1F ("f7real","f7real",binnum_mtt7,bins_mtt7); f7real->Sumw2();
   TH1F* f7jet=new TH1F ("f7jet","f7jet",binnum_mtt7,bins_mtt7); f7jet->Sumw2();
   TH1F* f8real=new TH1F ("f8real","f8real",binnum_mtt8,bins_mtt8); f8real->Sumw2();
   TH1F* f8jet=new TH1F ("f8jet","f8jet",binnum_mtt8,bins_mtt8); f8jet->Sumw2();

   TH2F* h0_ttcontamination=new TH2F ("h0_ttcontamination","InvMa",binnum_taupt,bins_taupt,binnum_mtt0,bins_mtt0); h0_ttcontamination->Sumw2();
   TH2F* h1_ttcontamination=new TH2F ("h1_ttcontamination","InvMa",binnum_pth,bins_pth,binnum_mtt1,bins_mtt1); h1_ttcontamination->Sumw2();
   TH2F* h2_ttcontamination=new TH2F ("h2_ttcontamination","InvMa",binnum_mjj,bins_mjj,binnum_mtt2,bins_mtt2); h2_ttcontamination->Sumw2();
   TH2F* h3_ttcontamination=new TH2F ("h3_ttcontamination","InvMa",binnum_taupt_low,bins_taupt_low,binnum_mtt3,bins_mtt3); h3_ttcontamination->Sumw2();
   TH2F* h4_ttcontamination=new TH2F ("h4_ttcontamination","InvMa",binnum_taupt_high,bins_taupt_high,binnum_mtt4,bins_mtt4); h4_ttcontamination->Sumw2();
   TH2F* h5_ttcontamination=new TH2F ("h5_ttcontamination","InvMa",binnum_pth_1,bins_pth_1,binnum_mtt5,bins_mtt5); h5_ttcontamination->Sumw2();
   TH2F* h6_ttcontamination=new TH2F ("h6_ttcontamination","InvMa",binnum_pth_2,bins_pth_2,binnum_mtt6,bins_mtt6); h6_ttcontamination->Sumw2();
   TH2F* h7_ttcontamination=new TH2F ("h7_ttcontamination","InvMa",binnum_mjj_low,bins_mjj_low,binnum_mtt7,bins_mtt7); h7_ttcontamination->Sumw2();
   TH2F* h8_ttcontamination=new TH2F ("h8_ttcontamination","InvMa",binnum_mjj_high,bins_mjj_high,binnum_mtt8,bins_mtt8); h8_ttcontamination->Sumw2();

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
        ostringstream HNS7tauOS; HNS7tauOS << "h7tau_OS" << k;
        ostringstream HNS8tauOS; HNS8tauOS << "h8tau_OS" << k;
        h3tau_OS.push_back(new TH2F (HNS3tauOS.str().c_str(),"InvMa",binnum_taupt_low,bins_taupt_low,binnum_mtt3,bins_mtt3)); h3tau_OS[k]->Sumw2();
        h4tau_OS.push_back(new TH2F (HNS4tauOS.str().c_str(),"InvMa",binnum_taupt_high,bins_taupt_high,binnum_mtt4,bins_mtt4)); h4tau_OS[k]->Sumw2();
        h5tau_OS.push_back(new TH2F (HNS5tauOS.str().c_str(),"InvMa",binnum_pth_1,bins_pth_1,binnum_mtt5,bins_mtt5)); h5tau_OS[k]->Sumw2();
        h6tau_OS.push_back(new TH2F (HNS6tauOS.str().c_str(),"InvMa",binnum_pth_2,bins_pth_2,binnum_mtt6,bins_mtt6)); h6tau_OS[k]->Sumw2();
        h7tau_OS.push_back(new TH2F (HNS7tauOS.str().c_str(),"InvMa",binnum_mjj_low,bins_mjj_low,binnum_mtt7,bins_mtt7)); h7tau_OS[k]->Sumw2();
        h8tau_OS.push_back(new TH2F (HNS8tauOS.str().c_str(),"InvMa",binnum_mjj_high,bins_mjj_high,binnum_mtt8,bins_mtt8)); h8tau_OS[k]->Sumw2();
        ostringstream HNS3jetOS; HNS3jetOS << "h3jet_OS" << k;
        ostringstream HNS4jetOS; HNS4jetOS << "h4jet_OS" << k;
        ostringstream HNS5jetOS; HNS5jetOS << "h5jet_OS" << k;
        ostringstream HNS6jetOS; HNS6jetOS << "h6jet_OS" << k;
        ostringstream HNS7jetOS; HNS7jetOS << "h7jet_OS" << k;
        ostringstream HNS8jetOS; HNS8jetOS << "h8jet_OS" << k;
        h3jet_OS.push_back(new TH2F (HNS3jetOS.str().c_str(),"InvMa",binnum_taupt_low,bins_taupt_low,binnum_mtt3,bins_mtt3)); h3jet_OS[k]->Sumw2();
        h4jet_OS.push_back(new TH2F (HNS4jetOS.str().c_str(),"InvMa",binnum_taupt_high,bins_taupt_high,binnum_mtt4,bins_mtt4)); h4jet_OS[k]->Sumw2();
        h5jet_OS.push_back(new TH2F (HNS5jetOS.str().c_str(),"InvMa",binnum_pth_1,bins_pth_1,binnum_mtt5,bins_mtt5)); h5jet_OS[k]->Sumw2();
        h6jet_OS.push_back(new TH2F (HNS6jetOS.str().c_str(),"InvMa",binnum_pth_2,bins_pth_2,binnum_mtt6,bins_mtt6)); h6jet_OS[k]->Sumw2();
        h7jet_OS.push_back(new TH2F (HNS7jetOS.str().c_str(),"InvMa",binnum_mjj_low,bins_mjj_low,binnum_mtt7,bins_mtt7)); h7jet_OS[k]->Sumw2();
        h8jet_OS.push_back(new TH2F (HNS8jetOS.str().c_str(),"InvMa",binnum_mjj_high,bins_mjj_high,binnum_mtt8,bins_mtt8)); h8jet_OS[k]->Sumw2();
        ostringstream HNS3ellOS; HNS3ellOS << "h3ell_OS" << k;
        ostringstream HNS4ellOS; HNS4ellOS << "h4ell_OS" << k;
        ostringstream HNS5ellOS; HNS5ellOS << "h5ell_OS" << k;
        ostringstream HNS6ellOS; HNS6ellOS << "h6ell_OS" << k;
        ostringstream HNS7ellOS; HNS7ellOS << "h7ell_OS" << k;
        ostringstream HNS8ellOS; HNS8ellOS << "h8ell_OS" << k;
        h3ell_OS.push_back(new TH2F (HNS3ellOS.str().c_str(),"InvMa",binnum_taupt_low,bins_taupt_low,binnum_mtt3,bins_mtt3)); h3ell_OS[k]->Sumw2();
        h4ell_OS.push_back(new TH2F (HNS4ellOS.str().c_str(),"InvMa",binnum_taupt_high,bins_taupt_high,binnum_mtt4,bins_mtt4)); h4ell_OS[k]->Sumw2();
        h5ell_OS.push_back(new TH2F (HNS5ellOS.str().c_str(),"InvMa",binnum_pth_1,bins_pth_1,binnum_mtt5,bins_mtt5)); h5ell_OS[k]->Sumw2();
        h6ell_OS.push_back(new TH2F (HNS6ellOS.str().c_str(),"InvMa",binnum_pth_2,bins_pth_2,binnum_mtt6,bins_mtt6)); h6ell_OS[k]->Sumw2();
        h7ell_OS.push_back(new TH2F (HNS7ellOS.str().c_str(),"InvMa",binnum_mjj_low,bins_mjj_low,binnum_mtt7,bins_mtt7)); h7ell_OS[k]->Sumw2();
        h8ell_OS.push_back(new TH2F (HNS8ellOS.str().c_str(),"InvMa",binnum_mjj_high,bins_mjj_high,binnum_mtt8,bins_mtt8)); h8ell_OS[k]->Sumw2();

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
        ostringstream HNS0ellAI; HNS0ellAI << "h0ell_AI" << k;
        ostringstream HNS1ellAI; HNS1ellAI << "h1ell_AI" << k;
        ostringstream HNS2ellAI; HNS2ellAI << "h2ell_AI" << k;
        h0ell_AI.push_back(new TH2F (HNS0ellAI.str().c_str(),"InvMa",binnum_taupt,bins_taupt,binnum_mtt0,bins_mtt0)); h0ell_AI[k]->Sumw2();
        h1ell_AI.push_back(new TH2F (HNS1ellAI.str().c_str(),"InvMa",binnum_pth,bins_pth,binnum_mtt1,bins_mtt1)); h1ell_AI[k]->Sumw2();
        h2ell_AI.push_back(new TH2F (HNS2ellAI.str().c_str(),"InvMa",binnum_mjj,bins_mjj,binnum_mtt2,bins_mtt2)); h2ell_AI[k]->Sumw2();

        ostringstream HNS3tauAI; HNS3tauAI << "h3tau_AI" << k;
        ostringstream HNS4tauAI; HNS4tauAI << "h4tau_AI" << k;
        ostringstream HNS5tauAI; HNS5tauAI << "h5tau_AI" << k;
        ostringstream HNS6tauAI; HNS6tauAI << "h6tau_AI" << k;
        ostringstream HNS7tauAI; HNS7tauAI << "h7tau_AI" << k;
        ostringstream HNS8tauAI; HNS8tauAI << "h8tau_AI" << k;
        h3tau_AI.push_back(new TH2F (HNS3tauAI.str().c_str(),"InvMa",binnum_taupt_low,bins_taupt_low,binnum_mtt3,bins_mtt3)); h3tau_AI[k]->Sumw2();
        h4tau_AI.push_back(new TH2F (HNS4tauAI.str().c_str(),"InvMa",binnum_taupt_high,bins_taupt_high,binnum_mtt4,bins_mtt4)); h4tau_AI[k]->Sumw2();
        h5tau_AI.push_back(new TH2F (HNS5tauAI.str().c_str(),"InvMa",binnum_pth_1,bins_pth_1,binnum_mtt5,bins_mtt5)); h5tau_AI[k]->Sumw2();
        h6tau_AI.push_back(new TH2F (HNS6tauAI.str().c_str(),"InvMa",binnum_pth_2,bins_pth_2,binnum_mtt6,bins_mtt6)); h6tau_AI[k]->Sumw2();
        h7tau_AI.push_back(new TH2F (HNS7tauAI.str().c_str(),"InvMa",binnum_mjj_low,bins_mjj_low,binnum_mtt7,bins_mtt7)); h7tau_AI[k]->Sumw2();
        h8tau_AI.push_back(new TH2F (HNS8tauAI.str().c_str(),"InvMa",binnum_mjj_high,bins_mjj_high,binnum_mtt8,bins_mtt8)); h8tau_AI[k]->Sumw2();
        ostringstream HNS3jetAI; HNS3jetAI << "h3jet_AI" << k;
        ostringstream HNS4jetAI; HNS4jetAI << "h4jet_AI" << k;
        ostringstream HNS5jetAI; HNS5jetAI << "h5jet_AI" << k;
        ostringstream HNS6jetAI; HNS6jetAI << "h6jet_AI" << k;
        ostringstream HNS7jetAI; HNS7jetAI << "h7jet_AI" << k;
        ostringstream HNS8jetAI; HNS8jetAI << "h8jet_AI" << k;
        h3jet_AI.push_back(new TH2F (HNS3jetAI.str().c_str(),"InvMa",binnum_taupt_low,bins_taupt_low,binnum_mtt3,bins_mtt3)); h3jet_AI[k]->Sumw2();
        h4jet_AI.push_back(new TH2F (HNS4jetAI.str().c_str(),"InvMa",binnum_taupt_high,bins_taupt_high,binnum_mtt4,bins_mtt4)); h4jet_AI[k]->Sumw2();
        h5jet_AI.push_back(new TH2F (HNS5jetAI.str().c_str(),"InvMa",binnum_pth_1,bins_pth_1,binnum_mtt5,bins_mtt5)); h5jet_AI[k]->Sumw2();
        h6jet_AI.push_back(new TH2F (HNS6jetAI.str().c_str(),"InvMa",binnum_pth_2,bins_pth_2,binnum_mtt6,bins_mtt6)); h6jet_AI[k]->Sumw2();
        h7jet_AI.push_back(new TH2F (HNS7jetAI.str().c_str(),"InvMa",binnum_mjj_low,bins_mjj_low,binnum_mtt7,bins_mtt7)); h7jet_AI[k]->Sumw2();
        h8jet_AI.push_back(new TH2F (HNS8jetAI.str().c_str(),"InvMa",binnum_mjj_high,bins_mjj_high,binnum_mtt8,bins_mtt8)); h8jet_AI[k]->Sumw2();
        ostringstream HNS3ellAI; HNS3ellAI << "h3ell_AI" << k;
        ostringstream HNS4ellAI; HNS4ellAI << "h4ell_AI" << k;
        ostringstream HNS5ellAI; HNS5ellAI << "h5ell_AI" << k;
        ostringstream HNS6ellAI; HNS6ellAI << "h6ell_AI" << k;
        ostringstream HNS7ellAI; HNS7ellAI << "h7ell_AI" << k;
        ostringstream HNS8ellAI; HNS8ellAI << "h8ell_AI" << k;
        h3ell_AI.push_back(new TH2F (HNS3ellAI.str().c_str(),"InvMa",binnum_taupt_low,bins_taupt_low,binnum_mtt3,bins_mtt3)); h3ell_AI[k]->Sumw2();
        h4ell_AI.push_back(new TH2F (HNS4ellAI.str().c_str(),"InvMa",binnum_taupt_high,bins_taupt_high,binnum_mtt4,bins_mtt4)); h4ell_AI[k]->Sumw2();
        h5ell_AI.push_back(new TH2F (HNS5ellAI.str().c_str(),"InvMa",binnum_pth_1,bins_pth_1,binnum_mtt5,bins_mtt5)); h5ell_AI[k]->Sumw2();
        h6ell_AI.push_back(new TH2F (HNS6ellAI.str().c_str(),"InvMa",binnum_pth_2,bins_pth_2,binnum_mtt6,bins_mtt6)); h6ell_AI[k]->Sumw2();
        h7ell_AI.push_back(new TH2F (HNS7ellAI.str().c_str(),"InvMa",binnum_mjj_low,bins_mjj_low,binnum_mtt7,bins_mtt7)); h7ell_AI[k]->Sumw2();
        h8ell_AI.push_back(new TH2F (HNS8ellAI.str().c_str(),"InvMa",binnum_mjj_high,bins_mjj_high,binnum_mtt8,bins_mtt8)); h8ell_AI[k]->Sumw2();
     }

   reweight::LumiReWeighting* LumiWeights_12;
   LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2018.root", "pu_distributions_data_2018.root", "pileup", "pileup");

   TFile *ftauid = new TFile("TauID_SF_pt_DeepTau2017v2p1VSjet_2018ReReco.root");
   TF1 *fct_tauid= (TF1*) ftauid->Get("Medium_cent");
   TF1 *fct_tauid_up= (TF1*) ftauid->Get("Medium_up");
   TF1 *fct_tauid_down= (TF1*) ftauid->Get("Medium_down");

   TFile *ffrac=new TFile("files_nominal_et/fractions.root");
   TH1F* frac_w_0jet=(TH1F*) ffrac->Get("frac_w_0jet");
   TH1F* frac_tt_0jet=(TH1F*) ffrac->Get("frac_tt_0jet");
   TH1F* frac_qcd_0jet=(TH1F*) ffrac->Get("frac_qcd_0jet");
   TH1F* frac_data_0jet=(TH1F*) ffrac->Get("frac_data_0jet");
   TH1F* frac_w_boosted=(TH1F*) ffrac->Get("frac_w_boosted");
   TH1F* frac_tt_boosted=(TH1F*) ffrac->Get("frac_tt_boosted");
   TH1F* frac_qcd_boosted=(TH1F*) ffrac->Get("frac_qcd_boosted");
   TH1F* frac_data_boosted=(TH1F*) ffrac->Get("frac_data_boosted");
   TH1F* frac_w_vbf=(TH1F*) ffrac->Get("frac_w_vbf");
   TH1F* frac_tt_vbf=(TH1F*) ffrac->Get("frac_tt_vbf");
   TH1F* frac_qcd_vbf=(TH1F*) ffrac->Get("frac_qcd_vbf");
   TH1F* frac_data_vbf=(TH1F*) ffrac->Get("frac_data_vbf");
   TH1F* frac_w_0jetlow=(TH1F*) ffrac->Get("frac_w_0jetlow");
   TH1F* frac_tt_0jetlow=(TH1F*) ffrac->Get("frac_tt_0jetlow");
   TH1F* frac_qcd_0jetlow=(TH1F*) ffrac->Get("frac_qcd_0jetlow");
   TH1F* frac_data_0jetlow=(TH1F*) ffrac->Get("frac_data_0jetlow");
   TH1F* frac_w_0jethigh=(TH1F*) ffrac->Get("frac_w_0jethigh");
   TH1F* frac_tt_0jethigh=(TH1F*) ffrac->Get("frac_tt_0jethigh");
   TH1F* frac_qcd_0jethigh=(TH1F*) ffrac->Get("frac_qcd_0jethigh");
   TH1F* frac_data_0jethigh=(TH1F*) ffrac->Get("frac_data_0jethigh");
   TH1F* frac_w_boosted1=(TH1F*) ffrac->Get("frac_w_boosted1");
   TH1F* frac_tt_boosted1=(TH1F*) ffrac->Get("frac_tt_boosted1");
   TH1F* frac_qcd_boosted1=(TH1F*) ffrac->Get("frac_qcd_boosted1");
   TH1F* frac_data_boosted1=(TH1F*) ffrac->Get("frac_data_boosted1");
   TH1F* frac_w_boosted2=(TH1F*) ffrac->Get("frac_w_boosted2");
   TH1F* frac_tt_boosted2=(TH1F*) ffrac->Get("frac_tt_boosted2");
   TH1F* frac_qcd_boosted2=(TH1F*) ffrac->Get("frac_qcd_boosted2");
   TH1F* frac_data_boosted2=(TH1F*) ffrac->Get("frac_data_boosted2");
   TH1F* frac_w_vbflow=(TH1F*) ffrac->Get("frac_w_vbflow");
   TH1F* frac_tt_vbflow=(TH1F*) ffrac->Get("frac_tt_vbflow");
   TH1F* frac_qcd_vbflow=(TH1F*) ffrac->Get("frac_qcd_vbflow");
   TH1F* frac_data_vbflow=(TH1F*) ffrac->Get("frac_data_vbflow");
   TH1F* frac_w_vbfhigh=(TH1F*) ffrac->Get("frac_w_vbfhigh");
   TH1F* frac_tt_vbfhigh=(TH1F*) ffrac->Get("frac_tt_vbfhigh");
   TH1F* frac_qcd_vbfhigh=(TH1F*) ffrac->Get("frac_qcd_vbfhigh");
   TH1F* frac_data_vbfhigh=(TH1F*) ffrac->Get("frac_data_vbfhigh");

   TFile fw("htt_scalefactors_legacy_2018.root");
   RooWorkspace *w = (RooWorkspace*)fw.Get("w");
   fw.Close();

   TFile fwmc("htt_scalefactors_legacy_2018.root");
   RooWorkspace *wmc = (RooWorkspace*)fwmc.Get("w");
   fwmc.Close();

   ScaleFactor * myScaleFactor_trg2427 = new ScaleFactor();
   myScaleFactor_trg2427->init_ScaleFactor("LeptonEfficiencies/Muon/Run2018/Muon_Run2018_IsoMu24orIsoMu27.root");
   ScaleFactor * myScaleFactor_trg20 = new ScaleFactor();
   myScaleFactor_trg20->init_ScaleFactor("LeptonEfficiencies/Muon/Run2018/Muon_Run2018_IsoMu20.root");
   ScaleFactor * myScaleFactor_IdIso = new ScaleFactor();
   myScaleFactor_IdIso->init_ScaleFactor("LeptonEfficiencies/Muon/Run2018/Muon_Run2018_IdIso.root");

   TFile* ff_file = TFile::Open("HTTutilities/Jet2TauFakes/data/SM2018/tight/vloose/et/fakeFactors.root");
   FakeFactor* ff = (FakeFactor*)ff_file->Get("ff_comb");
   const std::vector<std::string>& inputNames = ff->inputs();
   std::vector<double> inputs(9);

   TString postfixMC[73]={"","_CMS_scale_t_1prong_2018Down","_CMS_scale_t_1prong_2018Up","_CMS_scale_t_1prong1pizero_2018Down","_CMS_scale_t_1prong1pizero_2018Up","_CMS_scale_t_3prong_2018Down","_CMS_scale_t_3prong_2018Up","_CMS_tauideff_pt30to35_2018Down","_CMS_tauideff_pt30to35_2018Up","_CMS_tauideff_pt35to40_2018Down","_CMS_tauideff_pt35to40_2018Up","_CMS_tauideff_ptgt40_2018Down","_CMS_tauideff_ptgt40_2018Up","_CMS_JetEta0to3_2018Down","_CMS_JetEta0to3_2018Up","_CMS_JetEta0to5_2018Down","_CMS_JetEta0to5_2018Up","_CMS_JetEta3to5_2018Down","_CMS_JetEta3to5_2018Up","_CMS_JetRelativeSample_2018Down","_CMS_JetRelativeSample_2018Up","_CMS_JetRelativeBal_2018Down","_CMS_JetRelativeBal_2018Up","_CMS_JetEC2_2018Down","_CMS_JetEC2_2018Up","_CMS_scale_efaket_1prong_2018Down","_CMS_scale_efaket_1prong_2018Up","_CMS_scale_efaket_1prong1pizero_2018Down","_CMS_scale_efaket_1prong1pizero_2018Up","_CMS_scale_met_unclustered_2018Down","_CMS_scale_met_unclustered_2018Up","_CMS_htt_boson_reso_met_0jet_2018Down","_CMS_htt_boson_reso_met_0jet_2018Up","_CMS_htt_boson_reso_met_1jet_2018Down","_CMS_htt_boson_reso_met_1jet_2018Up","_CMS_htt_boson_reso_met_2jet_2018Down","_CMS_htt_boson_reso_met_2jet_2018Up","_CMS_htt_boson_scale_met_0jet_2018Down","_CMS_htt_boson_scale_met_0jet_2018Up","_CMS_htt_boson_scale_met_1jet_2018Down","_CMS_htt_boson_scale_met_1jet_2018Up","_CMS_htt_boson_scale_met_2jet_2018Down","_CMS_htt_boson_scale_met_2jet_2018Up","_CMS_htt_ttbarShapeDown","_CMS_htt_ttbarShapeUp","_CMS_htt_dyShapeDown","_CMS_htt_dyShapeUp","_CMS_scale_e_2018Down","_CMS_scale_e_2018Up","_CMS_smear_e_2018Down","_CMS_smear_e_2018Up","_CMS_singleeletrg_2018Down","_CMS_singleeletrg_2018Down","_CMS_eletautrg_2018Down","_CMS_eletautrg_2018Up","_THU_ggH_MuUp","_THU_ggH_MuDown","_THU_ggH_ResUp","_THU_ggH_ResDown","_THU_ggH_Mig01Up","_THU_ggH_Mig01Down","_THU_ggH_Mig12Up","_THU_ggH_Mig12Down","_THU_ggH_VBF2jUp","_THU_ggH_VBF2jDown","_THU_ggH_VBF3jUp","_THU_ggH_VBF3jDown","_THU_ggH_PT60Up","_THU_ggH_PT60Down","_THU_ggH_PT120Up","_THU_ggH_PT120Down","_THU_ggH_qmtopUp","_THU_ggH_qmtopDown"};

   TString postfixEmbedded[7]={"","_CMS_scale_emb_t_1prong_2018Down","_CMS_scale_emb_t_1prong_2018Up","_CMS_scale_emb_t_1prong1pizero_2018Down","_CMS_scale_emb_t_1prong1pizero_2018Up","_CMS_scale_emb_t_3prong_2018Down","_CMS_scale_emb_t_3prong_2018Up"};

   //std::string FFsys[18]={"ff_qcd_syst_up","ff_qcd_syst_down","ff_qcd_dm0_njet0_stat_up","ff_qcd_dm0_njet0_stat_down","ff_qcd_dm0_njet1_stat_up","ff_qcd_dm0_njet1_stat_down","ff_w_syst_up","ff_w_syst_down","ff_w_dm0_njet0_stat_up","ff_w_dm0_njet0_stat_down","ff_w_dm0_njet1_stat_up","ff_w_dm0_njet1_stat_down","ff_tt_syst_up","ff_tt_syst_down","ff_tt_dm0_njet0_stat_up","ff_tt_dm0_njet0_stat_down","ff_tt_dm0_njet1_stat_up","ff_tt_dm0_njet1_stat_down"};
   //TString postfixFF[19]={"","_CMS_ff_qcd_et_syst_2018Up","_CMS_ff_qcd_et_syst_2018Down","_CMS_ff_qcd_njet0_et_stat_2018Up","_CMS_ff_qcd_njet0_et_stat_2018Down","_CMS_ff_qcd_njet1_et_stat_2018Up","_CMS_ff_qcd_njet1_et_stat_2018Down","_CMS_ff_w_et_syst_2018Up","_CMS_ff_w_et_syst_2018Down","_CMS_ff_w_njet0_et_stat_2018Up","_CMS_ff_w_njet0_et_stat_2018Down","_CMS_ff_w_njet1_et_stat_2018Up","_CMS_ff_w_njet1_et_stat_2018Down","_CMS_ff_tt_et_syst_2018Up","_CMS_ff_tt_et_syst_2018Down","_CMS_ff_tt_njet0_et_stat_2018Up","_CMS_ff_tt_njet0_et_stat_2018Down","_CMS_ff_tt_njet1_et_stat_2018Up","_CMS_ff_tt_njet1_et_stat_2018Down"};

   TString FFsys[40]={"ff_qcd_0jet_up1","ff_qcd_0jet_up2","ff_qcd_0jet_down1","ff_qcd_0jet_down2","ff_qcd_1jet_up1","ff_qcd_1jet_up2","ff_qcd_1jet_down1","ff_qcd_1jet_down2","ff_w_0jet_up1","ff_w_0jet_up2","ff_w_0jet_down1","ff_w_0jet_down2","ff_w_1jet_up1","ff_w_1jet_up2","ff_w_1jet_down1","ff_w_1jet_down2","ff_tt_0jet_up1","ff_tt_0jet_up2","ff_tt_0jet_down1","ff_tt_0jet_down2","mvisclosure_qcd_up1","mvisclosure_qcd_up2","mvisclosure_qcd_down1","mvisclosure_qcd_down2","mvisclosure_w_up1","mvisclosure_w_up2","mvisclosure_w_down1","mvisclosure_w_down2","mvisclosure_tt_up1","mvisclosure_tt_up2","mvisclosure_tt_down1","mvisclosure_tt_down2","osssclosure_qcd_up1","osssclosure_qcd_up2","osssclosure_qcd_down1","osssclosure_qcd_down2","mtclosure_w_up1","mtclosure_w_up2","mtclosure_w_down1","mtclosure_w_down2"};
   TString postfixFF[41]={"","_CMS_rawFF_et_qcd_0jet_unc1_2018Up","_CMS_rawFF_et_qcd_0jet_unc2_2018Up","_CMS_rawFF_et_qcd_0jet_unc1_2018Down","_CMS_rawFF_et_qcd_0jet_unc2_2018Down","_CMS_rawFF_et_qcd_1jet_unc1_2018Up","_CMS_rawFF_et_qcd_1jet_unc2_2018Up","_CMS_rawFF_et_qcd_1jet_unc1_2018Down","_CMS_rawFF_et_qcd_1jet_unc2_2018Down","_CMS_rawFF_et_w_0jet_unc1_2018Up","_CMS_rawFF_et_w_0jet_unc2_2018Up","_CMS_rawFF_et_w_0jet_unc1_2018Down","_CMS_rawFF_et_w_0jet_unc2_2018Down","_CMS_rawFF_et_w_1jet_unc1_2018Up","_CMS_rawFF_et_w_1jet_unc2_2018Up","_CMS_rawFF_et_w_1jet_unc1_2018Down","_CMS_rawFF_et_w_1jet_unc2_2018Down","_CMS_rawFF_et_tt_unc1_2018Up","_CMS_rawFF_et_tt_unc2_2018Up","_CMS_rawFF_et_tt_unc1_2018Down","_CMS_rawFF_et_tt_unc2_2018Down","_CMS_FF_closure_mvis_et_qcd_unc1_2018Up","_CMS_FF_closure_mvis_et_qcd_unc2_2018Up","_CMS_FF_closure_mvis_et_qcd_unc1_2018Down","_CMS_FF_closure_mvis_et_qcd_unc2_2018Down","_CMS_FF_closure_mvis_et_w_unc1_2018Up","_CMS_FF_closure_mvis_et_w_unc2_2018Up","_CMS_FF_closure_mvis_et_w_unc1_2018Down","_CMS_FF_closure_mvis_et_w_unc2_2018Down","_CMS_FF_closure_mvis_et_tt_unc1_2018Up","_CMS_FF_closure_mvis_et_tt_unc2_2018Up","_CMS_FF_closure_mvis_et_tt_unc1_2018Down","_CMS_FF_closure_mvis_et_tt_unc2_2018Down","_CMS_FF_closure_OSSS_mvis_et_qcd_unc1_2018Up","_CMS_FF_closure_OSSS_mvis_et_qcd_unc2_2018Up","_CMS_FF_closure_OSSS_mvis_et_qcd_unc1_2018Down","_CMS_FF_closure_OSSS_mvis_et_qcd_unc2_2018Down","_CMS_FF_closure_mt_et_w_unc1_2018Up","_CMS_FF_closure_mt_et_w_unc1_2018Down","_CMS_FF_closure_mt_et_w_unc2_2018Up","_CMS_FF_closure_mt_et_w_unc2_2018Down"};

   TauTriggerSFs2017* etsf=new TauTriggerSFs2017("TauAnalysisTools/TauTriggerSFs/data/tauTriggerEfficiencies2018.root","mutau", "2018", "tight", "MVAv2");

   TFile * f_NNLOPS = new TFile("NNLOPS_reweight.root");
   TGraph * g_NNLOPS_0jet = (TGraph*) f_NNLOPS-> Get("gr_NNLOPSratio_pt_powheg_0jet");
   TGraph * g_NNLOPS_1jet = (TGraph*) f_NNLOPS-> Get("gr_NNLOPSratio_pt_powheg_1jet");
   TGraph * g_NNLOPS_2jet = (TGraph*) f_NNLOPS-> Get("gr_NNLOPSratio_pt_powheg_2jet");
   TGraph * g_NNLOPS_3jet = (TGraph*) f_NNLOPS-> Get("gr_NNLOPSratio_pt_powheg_3jet");

   bool do_rivet=(name.find("ggH") < 140 or name.find("qqH") < 140 or name.find("VH") < 140 or name.find("WH") < 140 or name.find("ZH") < 140);

   Int_t nentries_wtn = (Int_t) arbre->GetEntries();
   for (Int_t i = 0; i < nentries_wtn; i++) {
        arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

//byMediumDeepVSjet_2=byTightIsolationMVArun2v2DBoldDMwLT_2;

	// Rivet splitting
	if (do_rivet){
           if (name.find("ggH_FWDH_htt1") < 140 && Rivet_stage1p1_cat!=100) continue;
           if (name.find("ggH_PTH_GE200_htt1") < 140 && Rivet_stage1p1_cat!=150) continue;
           if (name.find("ggH_PTH_0_200_0J_PTH_0_10_htt1") < 140 && Rivet_stage1p1_cat!=102) continue;
           if (name.find("ggH_PTH_0_200_0J_PTH_10_200_htt1") < 140 && Rivet_stage1p1_cat!=103) continue;
           if (name.find("ggH_PTH_0_200_1J_PTH_0_60_htt1") < 140 && Rivet_stage1p1_cat!=111) continue;
           if (name.find("ggH_PTH_0_200_1J_PTH_60_120_htt1") < 140 && Rivet_stage1p1_cat!=112) continue;
           if (name.find("ggH_PTH_0_200_1J_PTH_120_200_htt1") < 140 && Rivet_stage1p1_cat!=113) continue;
           if (name.find("ggH_PTH_0_200_GE2J_MJJ_0_350_PTH_0_60_htt1") < 140 && Rivet_stage1p1_cat!=121) continue;
           if (name.find("ggH_PTH_0_200_GE2J_MJJ_0_350_PTH_60_120_htt1") < 140 && Rivet_stage1p1_cat!=122) continue;
           if (name.find("ggH_PTH_0_200_GE2J_MJJ_0_350_PTH_120_200_htt1") < 140 && Rivet_stage1p1_cat!=123) continue;
           if (name.find("ggH_PTH_0_200_GE2J_MJJ_350_700_PTHJJ_0_25_htt1") < 140 && Rivet_stage1p1_cat!=131) continue;
           if (name.find("ggH_PTH_0_200_GE2J_MJJ_350_700_PTHJJ_GE25_htt1") < 140 && Rivet_stage1p1_cat!=132) continue;
           if (name.find("ggH_PTH_0_200_GE2J_MJJ_GE700_PTHJJ_0_25_htt1") < 140 && Rivet_stage1p1_cat!=141) continue;
           if (name.find("ggH_PTH_0_200_GE2J_MJJ_GE700_PTHJJ_GE25_htt1") < 140 && Rivet_stage1p1_cat!=142) continue;
           if ((name.find("qqH_FWDH_htt1") < 140 or name.find("WH_had_FWDH_htt1") < 140 or name.find("ZH_had_FWDH_htt1") < 140 or name.find("VH_had_FWDH_htt1") < 140) && Rivet_stage1p1_cat!=200) continue;
           if ((name.find("qqH_0J_htt1") < 140 or name.find("WH_had_0J_htt1") < 140 or name.find("ZH_had_0J_htt1") < 140 or name.find("VH_had_0J_htt1") < 140) && Rivet_stage1p1_cat!=201) continue;
           if ((name.find("qqH_1J_htt1") < 140 or name.find("WH_had_1J_htt1") < 140 or name.find("ZH_had_1J_htt1") < 140 or name.find("VH_had_1J_htt1") < 140) && Rivet_stage1p1_cat!=202) continue;
           if ((name.find("qqH_GE2J_MJJ_0_60_htt1") < 140 or name.find("ZH_had_GE2J_MJJ_0_60_htt1") < 140 or name.find("WH_had_GE2J_MJJ_0_60_htt1") < 140 or name.find("VH_had_GE2J_MJJ_0_60_htt1") < 140) && Rivet_stage1p1_cat!=211) continue;
           if ((name.find("qqH_GE2J_MJJ_60_120_htt1") < 140 or name.find("ZH_had_GE2J_MJJ_60_120_htt1") < 140 or name.find("WH_had_GE2J_MJJ_60_120_htt1") < 140 or name.find("VH_had_GE2J_MJJ_60_120_htt1") < 140) && Rivet_stage1p1_cat!=212) continue;
           if ((name.find("qqH_GE2J_MJJ_120_350_htt1") < 140 or name.find("ZH_had_GE2J_MJJ_120_350_htt1") < 140 or name.find("WH_had_GE2J_MJJ_120_350_htt1") < 140 or name.find("VH_had_GE2J_MJJ_120_350_htt1") < 140) && Rivet_stage1p1_cat!=213) continue;
           if ((name.find("qqH_GE2J_MJJ_GE350_PTH_0_200_MJJ_350_700_PTHJJ_0_25_htt1") < 140 or name.find("ZH_had_GE2J_MJJ_GE350_PTH_0_200_MJJ_350_700_PTHJJ_0_25_htt1") < 140 or name.find("WH_had_GE2J_MJJ_GE350_PTH_0_200_MJJ_350_700_PTHJJ_0_25_htt1") < 140 or name.find("VH_had_GE2J_MJJ_GE350_PTH_0_200_MJJ_350_700_PTHJJ_0_25_htt1") < 140) && Rivet_stage1p1_cat!=251) continue;
           if ((name.find("qqH_GE2J_MJJ_GE350_PTH_0_200_MJJ_350_700_PTHJJ_GE25_htt1") < 140 or name.find("ZH_had_GE2J_MJJ_GE350_PTH_0_200_MJJ_350_700_PTHJJ_GE25_htt1") < 140 or name.find("WH_had_GE2J_MJJ_GE350_PTH_0_200_MJJ_350_700_PTHJJ_GE25_htt1") < 140 or name.find("VH_had_GE2J_MJJ_GE350_PTH_0_200_MJJ_350_700_PTHJJ_GE25_htt1") < 140) && Rivet_stage1p1_cat!=261) continue;
           if ((name.find("qqH_GE2J_MJJ_GE350_PTH_0_200_MJJ_GE700_PTHJJ_0_25_htt1") < 140 or name.find("ZH_had_GE2J_MJJ_GE350_PTH_0_200_MJJ_GE700_PTHJJ_0_25_htt1") < 140 or name.find("WH_had_GE2J_MJJ_GE350_PTH_0_200_MJJ_GE700_PTHJJ_0_25_htt1") < 140 or name.find("VH_had_GE2J_MJJ_GE350_PTH_0_200_MJJ_GE700_PTHJJ_0_25_htt1") < 140)&& Rivet_stage1p1_cat!=252) continue;
           if ((name.find("qqH_GE2J_MJJ_GE350_PTH_0_200_MJJ_GE700_PTHJJ_GE25_htt1") < 140 or name.find("ZH_had_GE2J_MJJ_GE350_PTH_0_200_MJJ_GE700_PTHJJ_GE25_htt1") < 140 or name.find("WH_had_GE2J_MJJ_GE350_PTH_0_200_MJJ_GE700_PTHJJ_GE25_htt1") < 140 or name.find("VH_had_GE2J_MJJ_GE350_PTH_0_200_MJJ_GE700_PTHJJ_GE25_htt1") < 140) && Rivet_stage1p1_cat!=262) continue;
           if ((name.find("qqH_GE2J_MJJ_GE350_PTH_GE200_htt1") < 140 or name.find("ZH_had_GE2J_MJJ_GE350_PTH_GE200_htt1") < 140 or name.find("WH_had_GE2J_MJJ_GE350_PTH_GE200_htt1") < 140 or name.find("VH_had_GE2J_MJJ_GE350_PTH_GE200_htt1") < 140) && Rivet_stage1p1_cat!=271) continue;
           if (name.find("WH_lep_FWDH_htt1") < 140 && Rivet_stage1p1_cat!=300) continue;
           if (name.find("WH_lep_PTV_0_75_htt1") < 140 && Rivet_stage1p1_cat!=301) continue;
           if (name.find("WH_lep_PTV_75_150_htt1") < 140 && Rivet_stage1p1_cat!=302) continue;
           if (name.find("WH_lep_PTV_150_250_0J_htt1") < 140 && Rivet_stage1p1_cat!=303) continue;
           if (name.find("WH_lep_PTV_150_250_GE1J_htt1") < 140 && Rivet_stage1p1_cat!=304) continue;
           if (name.find("WH_lep_PTV_GT250_htt1") < 140 && Rivet_stage1p1_cat!=305) continue;
           if (name.find("ZH_lep_FWDH_htt1") < 140 && Rivet_stage1p1_cat!=400) continue;
           if (name.find("ZH_lep_PTV_0_75_htt1") < 140 && Rivet_stage1p1_cat!=401) continue;
           if (name.find("ZH_lep_PTV_75_150_htt1") < 140 && Rivet_stage1p1_cat!=402) continue;
           if (name.find("ZH_lep_PTV_150_250_0J_htt1") < 140 && Rivet_stage1p1_cat!=403) continue;
           if (name.find("ZH_lep_PTV_150_250_GE1J_htt1") < 140 && Rivet_stage1p1_cat!=404) continue;
           if (name.find("ZH_lep_PTV_GT250_htt1") < 140 && Rivet_stage1p1_cat!=405) continue;
           if (name.find("ggZH_lep_FWDH_htt1") < 140 && Rivet_stage1p1_cat!=500) continue;
           if (name.find("ggZH_lep_PTV_0_75_htt1") < 140 && Rivet_stage1p1_cat!=502) continue;
           if (name.find("ggZH_lep_PTV_75_150_htt1") < 140 && Rivet_stage1p1_cat!=503) continue;
           if (name.find("ggZH_lep_PTV_GT150_0J_htt1") < 140 && Rivet_stage1p1_cat!=504) continue;
           if (name.find("ggZH_lep_PTV_GT140_GE1J_htt1") < 140 && Rivet_stage1p1_cat!=505) continue;
           if (name.find("ttH_FWDH_htt1") < 140 && Rivet_stage1p1_cat!=600) continue;
           if (name.find("ttH_stage1p1_htt1") < 140 && Rivet_stage1p1_cat!=601) continue;
           if (name.find("bbH_FWDH_htt1") < 140 && Rivet_stage1p1_cat!=700) continue;
           if (name.find("bbH_stage1p1_htt1") < 140 && Rivet_stage1p1_cat!=701) continue;
           if (name.find("tH_FWDH_htt1") < 140 && Rivet_stage1p1_cat!=800) continue;
           if (name.find("tH_stage1p1_htt1") < 140 && Rivet_stage1p1_cat!=801) continue;
	}

	if (fabs(eta_1)>2.1) continue;
        if (fabs(eta_2)>2.3) continue;

        if (Flag_goodVertices) continue;
        if (Flag_globalSuperTightHalo2016Filter) continue;
        if (Flag_HBHENoiseFilter) continue;
        if (Flag_HBHENoiseIsoFilter) continue;
        if (Flag_EcalDeadCellTriggerPrimitiveFilter) continue;
        if (Flag_BadPFMuonFilter) continue;
        if ((sample=="data_obs" or sample=="embedded") && Flag_eeBadScFilter) continue;
        if (Flag_ecalBadCalibReducedMINIAODFilter) continue;

        bool trigger24=(passMu24 && matchMu24_1 && filterMu24_1 && pt_1>25);
        bool trigger27=(passMu27 && matchMu27_1 && filterMu27_1 && pt_1>25);
        bool trigger2027=(passMu20Tau27 && matchMu20Tau27_1 && matchMu20Tau27_2 && filterMu20Tau27_1 && filterMu20Tau27_2 && pt_1>21 && pt_1<25 && fabs(eta_2)<2.1 && pt_2>32);
        bool triggerHPS2027=(passMu20HPSTau27 && matchMu20HPSTau27_1 && matchMu20HPSTau27_2 && filterMu20HPSTau27_1 && filterMu20HPSTau27_2 && pt_1>21 && pt_1<25 && fabs(eta_2)<2.1 && pt_2>32);

        if (sample=="embedded"){
           trigger24=(pt_1>25 && matchEmbFilter_Mu24_1);
           trigger27=(pt_1>25 && matchEmbFilter_Mu27_1);
           //trigger2027=(pt_1>21 && pt_1<25 && fabs(eta_2)<2.1 && matchEmbFilter_Mu20Tau27_1 && matchEmbFilter_Mu20Tau27_2 && pt_2>32);
           trigger2027=(pt_1>21 && pt_1<25 && fabs(eta_2)<2.1 && matchEmbFilter_Mu20Tau27_1 && matchEmbFilter_Mu20HPSTau27_2 && pt_2>32);
           triggerHPS2027=(pt_1>21 && pt_1<25 && fabs(eta_2)<2.1 && matchEmbFilter_Mu20Tau27_1 && matchEmbFilter_Mu20HPSTau27_2 && pt_2>32);
	   triggerHPS2027=(pt_1>21 && pt_1<25 && fabs(eta_2)<2.1 && pt_2>32);
        }

//if (run<317509 && pt_1>21 && pt_1<25 && fabs(eta_2)<2.1 && pt_2>32) cout<<matchEmbFilter_Mu20Tau27_1<<" "<<matchEmbFilter_Mu20Tau27_2<<" "<<matchEmbFilter_Mu20HPSTau27_2<<endl;

        if (sample=="data_obs" && run<317509 && !trigger2027 && !trigger24 && !trigger27) continue;
        if (sample=="data_obs" && run>=317509 && !triggerHPS2027 && !trigger24 && !trigger27) continue;
        if (sample!="data_obs" & !trigger24 && !trigger27 && !triggerHPS2027) continue;

        if (!byTightDeepVSmu_2 or !byVVVLooseDeepVSe_2) continue;
        float signalRegion=(byMediumDeepVSjet_2 && iso_1<0.15);
        float antiisoRegion=(byVVVLooseDeepVSjet_2 && !byMediumDeepVSjet_2 && iso_1<0.15);

	TLorentzVector mytau; 
	mytau.SetPtEtaPhiM(pt_2,eta_2,phi_2,m_2);
        TLorentzVector mymu;
        mymu.SetPtEtaPhiM(pt_1,eta_1,phi_1,m_1);

	if (mymu.DeltaR(mytau)<0.5) continue;

        if (sample=="W"){
            weight=51.749;
            if (numGenJets==1) weight=10.170;
            else if (numGenJets==2) weight=4.51855;
            else if (numGenJets==3) weight=3.07747;
            else if (numGenJets==4) weight=3.2113;
        }

        if (sample=="DY"){
            weight=3.6234;
            if (numGenJets==1) weight=0.6298;
            else if (numGenJets==2) weight=0.5521;
            else if (numGenJets==3) weight=0.5995;
            else if (numGenJets==4) weight=0.8211;
        }

	if (sample=="embedded" && gen_match_2==6) continue;
        bool is_includedInEmbedded=false;
        if ((name.find("125")>100 && sample!="data_obs" && sample!="embedded") && gen_match_1>2 && gen_match_1<6 && gen_match_2>2 && gen_match_2<6) is_includedInEmbedded=true; // remove overlap with embedded samples
        bool isT=(!is_includedInEmbedded && gen_match_2==5);
        bool isL=(!is_includedInEmbedded && gen_match_2<5);

	float aweight=genweight*weight*LumiWeights_12->weight(npu);
        if (sample=="embedded") aweight=genweight;
	if (sample=="data_obs") aweight=1.0;

	if (byMediumDeepVSjet_2 && sample!="embedded" && sample!="data_obs" && gen_match_2==5) aweight=aweight*fct_tauid->Eval(mytau.Pt());
	//if (byMediumDeepVSjet_2 && sample=="embedded") aweight=aweight*0.95;
        if (byMediumDeepVSjet_2 && sample=="embedded"){
           if (pt_2>=30 && pt_2<35) aweight=aweight*1.006;
           else if (pt_2>=35 && pt_2<40) aweight=aweight*1.001;
           else if (pt_2>=40) aweight=aweight*1.025;
        }


        if (sample!="embedded" && sample!="data_obs" && gen_match_2<5){
            if (fabs(eta_2)>=0.0 && fabs(eta_2)<0.4 && l2_decayMode==0) aweight=aweight*1.11*1.08;
            if (fabs(eta_2)>=0.4 && fabs(eta_2)<0.8 && l2_decayMode==0) aweight=aweight*1.05*0.78;
            if (fabs(eta_2)>=0.8 && fabs(eta_2)<1.2 && l2_decayMode==0) aweight=aweight*1.18*0.77;
            if (fabs(eta_2)>=1.2 && fabs(eta_2)<1.7 && l2_decayMode==0) aweight=aweight*1.06*0.75;
            if (fabs(eta_2)>=1.7 && fabs(eta_2)<2.3 && l2_decayMode==0) aweight=aweight*1.79*2.02;
            if (l2_decayMode==1) aweight=aweight*0.79*0.55;
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
	if (sample=="embedded"){
          w->var("m_pt")->setVal(mymu.Pt());
          w->var("m_eta")->setVal(mymu.Eta());
          w->var("m_iso")->setVal(iso_1);
          w->var("t_pt")->setVal(mytau.Pt());
          w->var("gt1_pt")->setVal(genpt_1);
          w->var("gt2_pt")->setVal(mytau.Pt());
          w->var("gt1_eta")->setVal(geneta_1);
          w->var("gt2_eta")->setVal(mytau.Eta());
          if (l2_decayMode==0) aweight=aweight*0.975;
          else if (l2_decayMode==1 or l2_decayMode==2) aweight=aweight*0.975*1.051;
          else if (l2_decayMode>=10) aweight=aweight*0.975*0.975*0.975;
          aweight=aweight*w->function("m_sel_trg_ic_ratio")->getVal();
          w->var("gt_pt")->setVal(genpt_1);
          w->var("gt_eta")->setVal(geneta_1);
          aweight=aweight*w->function("m_sel_id_ic_ratio")->getVal();
          w->var("gt_pt")->setVal(mytau.Pt());
          w->var("gt_eta")->setVal(mytau.Eta());
          aweight=aweight*w->function("m_sel_id_ic_ratio")->getVal();

          /*aweight=aweight*w->function("m_iso_binned_embed_kit_ratio")->getVal();
          aweight=aweight*w->function("m_id_embed_kit_ratio")->getVal();
	  if (trigger24 or trigger27) aweight=aweight*(w->function("m_trg24_27_embed_kit_ratio")->getVal());
          else aweight=aweight*(w->function("m_trg_MuTau_Mu20Leg_embed_kit_ratio")->getVal())*(w->function("mt_emb_LooseChargedIsoPFTau27_tight_kit_ratio")->getVal());*/

          aweight=aweight*w->function("m_idiso_ic_embed_ratio")->getVal();
          if (trigger24 or trigger27) aweight=aweight*w->function("m_trg_ic_embed_ratio")->getVal();
          else aweight=aweight*w->function("m_trg_20_ic_embed_ratio")->getVal()*w->function("t_trg_mediumDeepTau_mutau_embed_ratio")->getVal();

	}

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
          wmc->var("m_pt")->setVal(mymu.Pt());
          wmc->var("m_eta")->setVal(mymu.Eta());
          wmc->var("m_iso")->setVal(iso_1);
	  //aweight=aweight*myScaleFactor_IdIso->get_ScaleFactor(pt_1,eta_1);
	  int dm=l2_decayMode;
	  if(dm>10) dm=10;
          //if (trigger24 or trigger27) aweight=aweight*myScaleFactor_trg2427->get_ScaleFactor(pt_1,eta_1);
          //else aweight=aweight*myScaleFactor_trg20->get_ScaleFactor(pt_1,eta_1)*etsf->getTriggerScaleFactor(mytau.Pt(), mytau.Eta(), mytau.Phi(), dm);
          aweight=aweight*wmc->function("m_trk_ratio")->getVal();
          aweight=aweight*bweight;

          aweight=aweight*wmc->function("m_idiso_ic_ratio")->getVal();
          if (trigger24 or trigger27) aweight=aweight*wmc->function("m_trg_ic_ratio")->getVal();
	  else aweight=aweight*wmc->function("m_trg_20_ic_ratio")->getVal()*etsf->getTriggerScaleFactor(mytau.Pt(), mytau.Eta(), mytau.Phi(), dm);
          //else aweight=aweight*myScaleFactor_trg20->get_ScaleFactor(pt_1,eta_1)*etsf->getTriggerScaleFactor(mytau.Pt(), mytau.Eta(), mytau.Phi(), dm);
	}

	//************************ Compute fake factors ******************
	float frac_qcd=0.2;
	float frac_w=0.7;
	float frac_tt=0.1;

        if (njets==0 && (mymu+mytau+mymet).Pt()<10){
            frac_qcd=frac_qcd_0jetlow->GetBinContent(frac_qcd_0jetlow->GetXaxis()->FindBin((mymu+mytau).M()))/frac_data_0jetlow->GetBinContent(frac_data_0jetlow->GetXaxis()->FindBin((mymu+mytau).M()));
            frac_w=frac_w_0jetlow->GetBinContent(frac_w_0jetlow->GetXaxis()->FindBin((mymu+mytau).M()))/frac_data_0jetlow->GetBinContent(frac_data_0jetlow->GetXaxis()->FindBin((mymu+mytau).M()));
            frac_tt=frac_tt_0jetlow->GetBinContent(frac_tt_0jetlow->GetXaxis()->FindBin((mymu+mytau).M()))/frac_data_0jetlow->GetBinContent(frac_data_0jetlow->GetXaxis()->FindBin((mymu+mytau).M()));
        }
        else if (njets==0){
            frac_qcd=frac_qcd_0jethigh->GetBinContent(frac_qcd_0jethigh->GetXaxis()->FindBin((mymu+mytau).M()))/frac_data_0jethigh->GetBinContent(frac_data_0jethigh->GetXaxis()->FindBin((mymu+mytau).M()));
            frac_w=frac_w_0jethigh->GetBinContent(frac_w_0jethigh->GetXaxis()->FindBin((mymu+mytau).M()))/frac_data_0jethigh->GetBinContent(frac_data_0jethigh->GetXaxis()->FindBin((mymu+mytau).M()));
            frac_tt=frac_tt_0jethigh->GetBinContent(frac_tt_0jethigh->GetXaxis()->FindBin((mymu+mytau).M()))/frac_data_0jethigh->GetBinContent(frac_data_0jethigh->GetXaxis()->FindBin((mymu+mytau).M()));
        }
        else if (njets==1){
            frac_qcd=frac_qcd_boosted1->GetBinContent(frac_qcd_boosted1->GetXaxis()->FindBin(m_sv))/frac_data_boosted1->GetBinContent(frac_data_boosted1->GetXaxis()->FindBin(m_sv));
            frac_w=frac_w_boosted1->GetBinContent(frac_w_boosted1->GetXaxis()->FindBin(m_sv))/frac_data_boosted1->GetBinContent(frac_data_boosted1->GetXaxis()->FindBin(m_sv));
            frac_tt=frac_tt_boosted1->GetBinContent(frac_tt_boosted1->GetXaxis()->FindBin(m_sv))/frac_data_boosted1->GetBinContent(frac_data_boosted1->GetXaxis()->FindBin(m_sv));
        }
        else if (njets>1 && mjj<350){
            frac_qcd=frac_qcd_boosted2->GetBinContent(frac_qcd_boosted2->GetXaxis()->FindBin(m_sv))/frac_data_boosted2->GetBinContent(frac_data_boosted2->GetXaxis()->FindBin(m_sv));
            frac_w=frac_w_boosted2->GetBinContent(frac_w_boosted2->GetXaxis()->FindBin(m_sv))/frac_data_boosted2->GetBinContent(frac_data_boosted2->GetXaxis()->FindBin(m_sv));
            frac_tt=frac_tt_boosted2->GetBinContent(frac_tt_boosted2->GetXaxis()->FindBin(m_sv))/frac_data_boosted2->GetBinContent(frac_data_boosted2->GetXaxis()->FindBin(m_sv));
        }
        else if (njets>1 && mjj>=350 && (mymu+mytau+mymet).Pt()<200){
            frac_qcd=frac_qcd_vbflow->GetBinContent(frac_qcd_vbflow->GetXaxis()->FindBin(m_sv))/frac_data_vbflow->GetBinContent(frac_data_vbflow->GetXaxis()->FindBin(m_sv));
            frac_w=frac_w_vbflow->GetBinContent(frac_w_vbflow->GetXaxis()->FindBin(m_sv))/frac_data_vbflow->GetBinContent(frac_data_vbflow->GetXaxis()->FindBin(m_sv));
            frac_tt=frac_tt_vbflow->GetBinContent(frac_tt_vbflow->GetXaxis()->FindBin(m_sv))/frac_data_vbflow->GetBinContent(frac_data_vbflow->GetXaxis()->FindBin(m_sv));
        }
        else if (njets>1 && mjj>=350 && (mymu+mytau+mymet).Pt()>=200){
            frac_qcd=frac_qcd_vbfhigh->GetBinContent(frac_qcd_vbfhigh->GetXaxis()->FindBin(m_sv))/frac_data_vbfhigh->GetBinContent(frac_data_vbfhigh->GetXaxis()->FindBin(m_sv));
            frac_w=frac_w_vbfhigh->GetBinContent(frac_w_vbfhigh->GetXaxis()->FindBin(m_sv))/frac_data_vbfhigh->GetBinContent(frac_data_vbfhigh->GetXaxis()->FindBin(m_sv));
            frac_tt=frac_tt_vbfhigh->GetBinContent(frac_tt_vbfhigh->GetXaxis()->FindBin(m_sv))/frac_data_vbfhigh->GetBinContent(frac_data_vbfhigh->GetXaxis()->FindBin(m_sv));
        }

	float total=frac_qcd+frac_w+frac_tt;
	frac_qcd=frac_qcd/total;
        frac_w=frac_w/total;
        frac_tt=frac_tt/total;

	float mt=TMass_F(mymu.Pt(),mymet.Pt(),mymu.Px(),mymet.Px(),mymu.Py(),mymet.Py());

        inputs[0] = mytau.Pt();
        inputs[1] = l2_decayMode;
        inputs[2] = njets;
        inputs[3] = (mymu+mytau).M();
        inputs[4] = mt;
        inputs[5] = iso_1;
        inputs[6] = frac_qcd;
        inputs[7] = frac_w;
        inputs[8] = frac_tt;

	//************************* Fill histograms **********************
	//double FF=1.0*ff->value(inputs); // Vienna's FF
	double FF=1.0*get_ff(mytau.Pt(), mt, (mymu+mytau).M(), njets, frac_tt, frac_qcd, frac_w, ""); // Our FF
	float myvar=(mymu+mytau).M();
	TLorentzVector myrawtau=mytau;
        TLorentzVector myrawele=mymu;
        TLorentzVector myrawmet=mymet;
        float massJets=mjj;
        int numberJets=njets;
	int rawnbtag=nbtag;
	float mtt=m_sv;
	float rawtaupt=mytau.Pt();
	float rawmt=mt;
	float rawmvis=(mymu+mytau).M();
	float rawnjets=njets;

	for (int k=0; k<nbhist; ++k){

	   float weight2=1.0;

	   nbtag=rawnbtag;
           if (nbtag>0) continue;
           if (nbtagL>1) continue;

	   // reset all variables before any systematic shift
	   massJets=mjj;
	   mtt=m_sv;
	   numberJets=njets;
	   mytau=myrawtau;
           mymu=myrawele;
	   mymet=myrawmet;
	   massJets=mjj;

           if (sample!="data_obs" && !(sample=="embedded" && k>6)){
              if (k>0 && k<7 && gen_match_2==5){ // TES x 6
                if (k==1 && l2_decayMode==0){mytau*=0.989; mymet=mymet+(0.011/0.989)*mytau; mtt=m_sv_DOWN;}
                else if (k==2 && l2_decayMode==0){mytau*=1.011; mymet=mymet-(0.011/1.011)*mytau; mtt=m_sv_UP;}
                else if (k==3 && l2_decayMode==1){mytau*=0.992; mymet=mymet+(0.008/0.992)*mytau; mtt=m_sv_DOWN;}
                else if (k==4 && l2_decayMode==1){mytau*=1.008; mymet=mymet-(0.008/1.008)*mytau; mtt=m_sv_UP;}
                else if (k==5 && l2_decayMode==10){mytau*=0.991; mymet=mymet+(0.009/0.991)*mytau; mtt=m_sv_DOWN;}
                else if (k==6 && l2_decayMode==10){mytau*=1.009; mymet=mymet-(0.009/1.009)*mytau; mtt=m_sv_UP;}
              }
	      else if (k>6 && k<13 && byMediumDeepVSjet_2 && gen_match_2==5){
		if (k==7 && mytau.Pt()>=30 && mytau.Pt()<35) weight2=fct_tauid_down->Eval(mytau.Pt())/fct_tauid->Eval(mytau.Pt());
                else if (k==8 && mytau.Pt()>=30 && mytau.Pt()<35) weight2=fct_tauid_up->Eval(mytau.Pt())/fct_tauid->Eval(mytau.Pt());
                else if (k==9 && mytau.Pt()>=35 && mytau.Pt()<40) weight2=fct_tauid_down->Eval(mytau.Pt())/fct_tauid->Eval(mytau.Pt());
                else if (k==10 && mytau.Pt()>=35 && mytau.Pt()<40) weight2=fct_tauid_up->Eval(mytau.Pt())/fct_tauid->Eval(mytau.Pt());
                else if (k==11 && mytau.Pt()>=40) weight2=fct_tauid_down->Eval(mytau.Pt())/fct_tauid->Eval(mytau.Pt());
                else if (k==12 && mytau.Pt()>=40) weight2=fct_tauid_up->Eval(mytau.Pt())/fct_tauid->Eval(mytau.Pt());
	      }
              else if (k>12 && k<25){ // JES x 12
                if (k==13){numberJets=njets_JetEta0to3Down; massJets=mjj_JetEta0to3Down; mymet=myrawmet; mymet.SetPtEtaPhiM(met_JetEta0to3Down,0,metphi_JetEta0to3Down,0); mtt=m_sv_JetEta0to3Down;}
                else if (k==14){numberJets=njets_JetEta0to3Up; massJets=mjj_JetEta0to3Up; mymet=myrawmet; mymet.SetPtEtaPhiM(met_JetEta0to3Up,0,metphi_JetEta0to3Up,0); mtt=m_sv_JetEta0to3Up;}
                else if (k==15){numberJets=njets_JetEta0to5Down; massJets=mjj_JetEta0to5Down; mymet=myrawmet; mymet.SetPtEtaPhiM(met_JetEta0to5Down,0,metphi_JetEta0to5Down,0); mtt=m_sv_JetEta0to5Down;}
                else if (k==16){numberJets=njets_JetEta0to5Up; massJets=mjj_JetEta0to5Up; mymet=myrawmet; mymet.SetPtEtaPhiM(met_JetEta0to5Up,0,metphi_JetEta0to5Up,0); mtt=m_sv_JetEta0to5Up;}
                else if (k==17){numberJets=njets_JetEta3to5Down; massJets=mjj_JetEta3to5Down; mymet=myrawmet; mymet.SetPtEtaPhiM(met_JetEta3to5Down,0,metphi_JetEta3to5Down,0); mtt=m_sv_JetEta3to5Down;}
                else if (k==18){numberJets=njets_JetEta3to5Up; massJets=mjj_JetEta3to5Up; mymet=myrawmet; mymet.SetPtEtaPhiM(met_JetEta3to5Up,0,metphi_JetEta3to5Up,0); mtt=m_sv_JetEta3to5Up;}
                else if (k==19){numberJets=njets_JetRelativeSampleDown; massJets=mjj_JetRelativeSampleDown; mymet=myrawmet; mymet.SetPtEtaPhiM(met_JetRelativeSampleDown,0,metphi_JetRelativeSampleDown,0); mtt=m_sv_JetRelativeSampleDown;}
                else if (k==20){numberJets=njets_JetRelativeSampleUp; massJets=mjj_JetRelativeSampleUp; mymet=myrawmet; mymet.SetPtEtaPhiM(met_JetRelativeSampleUp,0,metphi_JetRelativeSampleUp,0); mtt=m_sv_JetRelativeSampleUp;}
                else if (k==21){numberJets=njets_JetRelativeBalDown; massJets=mjj_JetRelativeBalDown; mymet=myrawmet; mymet.SetPtEtaPhiM(met_JetRelativeBalDown,0,metphi_JetRelativeBalDown,0); mtt=m_sv_JetRelativeBalDown;}
                else if (k==22){numberJets=njets_JetRelativeBalUp; massJets=mjj_JetRelativeBalUp; mymet=myrawmet; mymet.SetPtEtaPhiM(met_JetRelativeBalUp,0,metphi_JetRelativeBalUp,0); mtt=m_sv_JetRelativeBalUp;}
                else if (k==23){numberJets=njets_JetEC2Down; massJets=mjj_JetEC2Down; mymet=myrawmet; mymet.SetPtEtaPhiM(met_JetEC2Down,0,metphi_JetEC2Down,0); mtt=m_sv_JetEC2Down;}
                else if (k==24){numberJets=njets_JetEC2Up; massJets=mjj_JetEC2Up; mymet=myrawmet; mymet.SetPtEtaPhiM(met_JetEC2Up,0,metphi_JetEC2Up,0); mtt=m_sv_JetEC2Up;}
              }
              else if (k>24 && k<29 && (gen_match_2<5)){ // e->tau fake ES x 4
                if (k==25 && l2_decayMode==0){mytau*=0.97; mymet=mymet+(0.03/0.97)*mytau; mtt=m_sv_DOWN;}
                else if (k==26 && l2_decayMode==0){mytau*=1.03; mymet=mymet-(0.03/1.03)*mytau; mtt=m_sv_UP;}
                else if (k==27 && l2_decayMode==1){mytau*=0.97; mymet=mymet+(0.03/0.97)*mytau; mtt=m_sv_DOWN;}
                else if (k==28 && l2_decayMode==1){mytau*=1.03; mymet=mymet-(0.03/1.03)*mytau; mtt=m_sv_UP;}
              }
              else if ((name=="TT" or name=="VV" or name=="ST") && k>28 && k<31){ // UES x 2
                if (k==29){mymet=myrawmet; mymet.SetPtEtaPhiM(met_UESDown, 0, metphi_UESDown, 0); mtt=m_sv_UESDown;}
                else if (k==30){mymet=myrawmet; mymet.SetPtEtaPhiM(met_UESUp, 0, metphi_UESUp, 0); mtt=m_sv_UESUp;}
	      }
              else if (!(name=="TT" or name=="VV" or name=="ST") && k>30 && k<43){ // recoil x 12
                if (numberJets==0 && k==31){mymet=myrawmet; mymet.SetPtEtaPhiM(met_resolutionDown, 0, metphi_resolutionDown, 0); mtt=m_sv_ResolutionDown;}
                else if (numberJets==0 && k==32){mymet=myrawmet; mymet.SetPtEtaPhiM(met_resolutionUp, 0, metphi_resolutionUp, 0); mtt=m_sv_ResolutionUp;}
                else if (numberJets==1 && k==33){mymet=myrawmet; mymet.SetPtEtaPhiM(met_resolutionDown, 0, metphi_resolutionDown, 0); mtt=m_sv_ResolutionDown;}
                else if (numberJets==1 && k==34){mymet=myrawmet; mymet.SetPtEtaPhiM(met_resolutionUp, 0, metphi_resolutionUp, 0); mtt=m_sv_ResolutionUp;}
                else if (numberJets>1 && k==35){mymet=myrawmet; mymet.SetPtEtaPhiM(met_resolutionDown, 0, metphi_resolutionDown, 0); mtt=m_sv_ResolutionDown;}
                else if (numberJets>1 && k==36){mymet=myrawmet; mymet.SetPtEtaPhiM(met_resolutionUp, 0, metphi_resolutionUp, 0); mtt=m_sv_ResolutionUp;}
                else if (numberJets==0 && k==37){mymet=myrawmet; mymet.SetPtEtaPhiM(met_responseDown, 0, metphi_responseDown, 0); mtt=m_sv_ResponseDown;}
                else if (numberJets==0 && k==38){mymet=myrawmet; mymet.SetPtEtaPhiM(met_responseUp, 0, metphi_responseUp, 0); mtt=m_sv_ResponseUp;}
                else if (numberJets==1 && k==39){mymet=myrawmet; mymet.SetPtEtaPhiM(met_responseDown, 0, metphi_responseDown, 0); mtt=m_sv_ResponseDown;}
                else if (numberJets==1 && k==40){mymet=myrawmet; mymet.SetPtEtaPhiM(met_responseUp, 0, metphi_responseUp, 0); mtt=m_sv_ResponseUp;}
                else if (numberJets>1 && k==41){mymet=myrawmet; mymet.SetPtEtaPhiM(met_responseDown, 0, metphi_responseDown, 0); mtt=m_sv_ResponseDown;}
                else if (numberJets>1 && k==42){mymet=myrawmet; mymet.SetPtEtaPhiM(met_responseUp, 0, metphi_responseUp, 0); mtt=m_sv_ResponseUp;}
              }
              else if (k>42 && k<45 && (sample=="TTToHadronic" or sample=="TTTo2L2Nu" or sample=="TTToSemiLeptonic")){ //Top pt reweighting x 2
                if (k==43) weight2=1.0/topfactor;
                else if (k==44) weight2=topfactor;
              }
              else if (k>44 && k<47 && (sample=="DY")){ //Z pt reweighting x 2
                if (k==45) weight2=(1+0.90*(zptweight-1))/zptweight;
                else if (k==46) weight2=(1+1.10*(zptweight-1))/zptweight;
              }
              else if (k>46 && k<51){ // EES x 4 
                if (k==47){mymu*=(pt_1_ScaleDown/mymu.Pt()); mymet=mymet-mymu+myrawele; mtt=m_sv_ESCALEDOWN;}
                else if (k==48){mymu*=(pt_1_ScaleUp/mymu.Pt()); mymet=mymet-mymu+myrawele; mtt=m_sv_ESCALEUP;}
                else if (k==49){mymu*=(pt_1_SigmaDown/mymu.Pt()); mymet=mymet-mymu+myrawele; mtt=m_sv_ESMEARDOWN;}
                else if (k==50){mymu*=(pt_1_SigmaUp/mymu.Pt()); mymet=mymet-mymu+myrawele; mtt=m_sv_ESMEARUP;}
              }
              else if (k>50 && k<55){ // TRG x 4 
                if (k==51 && mymu.Pt()>33){weight2=0.98;}
                else if (k==52 && mymu.Pt()>33){weight2=1.02;}
                else if (k==53 && mymu.Pt()<33){weight2=0.98;}
                else if (k==54 && mymu.Pt()<33){weight2=1.02;}
              }
              else if (is_ggh && k>54 && k<73){ // WG1 x 18
                if (k==55) weight2=1+WG1unc[0];
                else if (k==56) weight2=1-WG1unc[0];
                else if (k==57) weight2=1+WG1unc[1];
                else if (k==58) weight2=1-WG1unc[1];
                else if (k==59) weight2=1+WG1unc[2];
                else if (k==60) weight2=1-WG1unc[2];
                else if (k==61) weight2=1+WG1unc[3];
                else if (k==62) weight2=1-WG1unc[3];
                else if (k==63) weight2=1+WG1unc[4];
                else if (k==64) weight2=1-WG1unc[4];
                else if (k==65) weight2=1+WG1unc[5];
                else if (k==66) weight2=1-WG1unc[5];
                else if (k==67) weight2=1+WG1unc[6];
                else if (k==68) weight2=1-WG1unc[6];
                else if (k==69) weight2=1+WG1unc[7];
                else if (k==70) weight2=1-WG1unc[7];
                else if (k==71) weight2=1+WG1unc[8];
                else if (k==72) weight2=1-WG1unc[8];
              }
           }

           /*if (name=="ST" or name=="VV" or name=="DY" or name=="TT"){
              if (k>50 && k<69){ // FF x 18
                FF=ff->value(inputs,FFsys[k-1-50]);
              }
           }
           if (sample=="data_obs"){
              if (k>0 && k<19){ // FF x 18
                FF=ff->value(inputs,FFsys[k-1]);
              }
           }*/

	   if (name=="ST" or name=="VV" or name=="DY" or name=="TT"){
              if (k>54 && k<96){ // FF 
	   	FF=1.0*get_ff(rawtaupt, rawmt, rawmvis, rawnjets, frac_tt, frac_qcd, frac_w,FFsys[k-1-54]);
              }
           }
           if (sample=="data_obs"){
              if (k>0 && k<41){ // FF 
		FF=1.0*get_ff(rawtaupt, rawmt, rawmvis, rawnjets, frac_tt, frac_qcd, frac_w,FFsys[k-1]);
              }
           }
	   if (sample=="embedded"){
              if (k>6 && k<47){ // FF 
                FF=1.0*get_ff(rawtaupt, rawmt, rawmvis, rawnjets, frac_tt, frac_qcd, frac_w,FFsys[k-7]);
              }
           }

           if (!(FF>0 && FF<1)) FF=0; //FIXME

           if (mytau.Pt()<30) continue;
           if ((mymu+mytau).M()<50) continue;

    	   mt=TMass_F(mymu.Pt(),mymet.Pt(),mymu.Px(),mymet.Px(),mymu.Py(),mymet.Py());
	   myvar=mtt;
	   if (numberJets==0) myvar=(mymu+mytau).M();
	   float myvar0=mytau.Pt();
	   float myvar1=(mymu+mytau+mymet).Pt();
	   float myvar2=massJets;
           float myvar3=myvar0;
           float myvar4=myvar0;
           float myvar5=myvar1;
           float myvar6=myvar1;
           float myvar7=myvar2;
           float myvar8=myvar2;

           float mass0=myvar;
           float mass1=myvar;
           float mass2=myvar;
           float mass3=myvar;
           float mass4=myvar;
           float mass5=myvar;
           float mass6=myvar;
           float mass7=myvar;
           float mass8=myvar;
           if (do_control_plots>0){
                myvar0=1;myvar1=1;myvar2=1;myvar3=1;myvar4=1;myvar5=1;myvar6=1;myvar7=1;myvar8=1;
           }
           if (do_control_plots==1){
              mass0=mymu.Pt();
              mass1=mytau.Pt();
              mass2=mymet.Pt();
              mass3=(mymu+mytau+mymet).Pt();
              mass4=(mymu+mytau).M();
              mass5=m_sv;
              mass6=njets;
              mass7=mymu.Eta();
              mass8=mytau.Eta();
           }
           if (do_control_plots==2){
              mass0=mt;
              if (numberJets<2) mass1=-1;
              else mass1=mjj;
              mass2=iso_1;
              if (numberJets<1) mass3=-1;
              else mass3=jpt_1;
              if (numberJets<1) mass4=-10;
              else mass4=jeta_1;
              if (numberJets<2) mass5=-1;
              else mass5=jpt_2;
              if (numberJets<2) mass6=-10;
              else mass6=jeta_2;
              if (numberJets<2) mass7=-10;
              else mass7=fabs(jeta_1-jeta_2);
              mass8=mymu.DeltaR(mytau);
           }

           if ((do_control_plots>0 or numberJets==0) && (do_control_plots==2 or mt<50) && q_1*q_2<0){
               if (k==0 && is_includedInEmbedded && signalRegion)
                   h0_ttcontamination->Fill(myvar0,mass0,aweight*weight2);
               if ((sample=="data_obs" or isT) && signalRegion){
                   h0tau_OS[k]->Fill(myvar0,mass0,aweight*weight2);
	       }
               if ((sample!="data_obs" && isL) && signalRegion)
                   h0ell_OS[k]->Fill(myvar0,mass0,aweight*weight2);
               if ((sample!="data_obs" && gen_match_2==6) && signalRegion)
                   h0jet_OS[k]->Fill(myvar0,mass0,aweight*weight2);
               if (antiisoRegion && sample=="data_obs"){
                   h0tau_AI[k]->Fill(myvar0,mass0,FF);
                   h0jet_AI[k]->Fill(myvar0,mass0);
	       }
               if ((sample!="data_obs" && (sample=="embedded" or isT)) && antiisoRegion)
                   h0tau_AI[k]->Fill(myvar0,mass0,aweight*weight2*FF);
               if ((sample!="data_obs" && sample!="embedded" && isL) && antiisoRegion)
                   h0ell_AI[k]->Fill(myvar0,mass0,aweight*weight2*FF);
               if ((sample!="data_obs" && sample!="embedded" && gen_match_2==6) && antiisoRegion)
                   h0jet_AI[k]->Fill(myvar0,mass0,aweight*weight2);

               if (k==0){ // fractions
                  if ((sample=="data_obs" or (sample=="embedded" or isT or isL)) && antiisoRegion)
                      f0real->Fill(mass0,aweight*weight2);
                  if ((sample!="data_obs" && sample!="embedded" && gen_match_2==6) && antiisoRegion)
                      f0jet->Fill(mass0,aweight*weight2);
               }
           }
           if ((do_control_plots>0 or (numberJets==1 or ((myvar1<50 or massJets<350) && numberJets>1))) && mt<50 && q_1*q_2<0){
               if (k==0 && is_includedInEmbedded && signalRegion)
                   h1_ttcontamination->Fill(myvar1,mass1,aweight*weight2);
               if ((sample=="data_obs" or isT) && signalRegion)
                   h1tau_OS[k]->Fill(myvar1,mass1,aweight*weight2);
               if ((sample!="data_obs" && isL) && signalRegion)
                   h1ell_OS[k]->Fill(myvar1,mass1,aweight*weight2);
               if ((sample!="data_obs" && gen_match_2==6) && signalRegion)
                   h1jet_OS[k]->Fill(myvar1,mass1,aweight*weight2);
               if (antiisoRegion && sample=="data_obs"){
                   h1tau_AI[k]->Fill(myvar1,mass1,FF);
                   h1jet_AI[k]->Fill(myvar1,mass1);
	       }
               if ((sample!="data_obs" && (sample=="embedded" or isT)) && antiisoRegion)
                   h1tau_AI[k]->Fill(myvar1,mass1,aweight*weight2*FF);
               if ((sample!="data_obs" && sample!="embedded" && isL) && antiisoRegion)
                   h1ell_AI[k]->Fill(myvar1,mass1,aweight*weight2*FF);
               if ((sample!="data_obs" && sample!="embedded" && gen_match_2==6) && antiisoRegion)
                   h1jet_AI[k]->Fill(myvar1,mass1,aweight*weight2);

               if (k==0){ // fractions
                  if ((sample=="data_obs" or (sample=="embedded" or isT or isL)) && antiisoRegion)
                      f1real->Fill(mass1,aweight*weight2);
                  if ((sample!="data_obs" && sample!="embedded" && gen_match_2==6) && antiisoRegion)
                      f1jet->Fill(mass1,aweight*weight2);
               }
           }
           if ((do_control_plots>0 or (numberJets>=2 && massJets>350 && myvar1>50)) && mt<50 && q_1*q_2<0){
               if (k==0 && is_includedInEmbedded && signalRegion)
                   h2_ttcontamination->Fill(myvar2,mass2,aweight*weight2);
               if ((sample=="data_obs" or isT) && signalRegion)
                   h2tau_OS[k]->Fill(myvar2,mass2,aweight*weight2);
               if ((sample!="data_obs" && isL) && signalRegion)
                   h2ell_OS[k]->Fill(myvar2,mass2,aweight*weight2);
               if ((sample!="data_obs" && gen_match_2==6) && signalRegion)
                   h2jet_OS[k]->Fill(myvar2,mass2,aweight*weight2);
               if (antiisoRegion && sample=="data_obs"){
                   h2tau_AI[k]->Fill(myvar2,mass2,FF);
                   h2jet_AI[k]->Fill(myvar2,mass2);
	       }
               if ((sample!="data_obs" && (sample=="embedded" or isT)) && antiisoRegion)
                   h2tau_AI[k]->Fill(myvar2,mass2,aweight*weight2*FF);
               if ((sample!="data_obs" && sample!="embedded" && isL) && antiisoRegion)
                   h2ell_AI[k]->Fill(myvar2,mass2,aweight*weight2*FF);
               if ((sample!="data_obs" && sample!="embedded" && gen_match_2==6) && antiisoRegion)
                   h2jet_AI[k]->Fill(myvar2,mass2,aweight*weight2);

               if (k==0){ // fractions
                  if ((sample=="data_obs" or (sample=="embedded" or isT or isL)) && antiisoRegion)
                      f2real->Fill(mass2,aweight*weight2);
                  if ((sample!="data_obs" && sample!="embedded" && gen_match_2==6) && antiisoRegion)
                      f2jet->Fill(mass2,aweight*weight2);
               }
           }

           if ((do_control_plots>0 or (numberJets==0 && (mymu+mytau+mymet).Pt()<10)) && mt<50 && q_1*q_2<0){
               if (k==0 && is_includedInEmbedded && signalRegion)
                   h3_ttcontamination->Fill(myvar3,mass3,aweight*weight2);
               if ((sample=="data_obs" or isT) && signalRegion)
                   h3tau_OS[k]->Fill(myvar3,mass3,aweight*weight2);
               if ((sample!="data_obs" && isL) && signalRegion)
                   h3ell_OS[k]->Fill(myvar3,mass3,aweight*weight2);
               if ((sample!="data_obs" && gen_match_2==6) && signalRegion)
                   h3jet_OS[k]->Fill(myvar3,mass3,aweight*weight2);
               if (antiisoRegion && sample=="data_obs"){
                   h3tau_AI[k]->Fill(myvar3,mass3,FF);
                   h3jet_AI[k]->Fill(myvar3,mass3);
               }
               if ((sample!="data_obs" && (sample=="embedded" or isT)) && antiisoRegion)
                   h3tau_AI[k]->Fill(myvar3,mass3,aweight*weight2*FF);
               if ((sample!="data_obs" && sample!="embedded" && isL) && antiisoRegion)
                   h3ell_AI[k]->Fill(myvar3,mass3,aweight*weight2*FF);
               if ((sample!="data_obs" && sample!="embedded" && gen_match_2==6) && antiisoRegion)
                   h3jet_AI[k]->Fill(myvar3,mass3,aweight*weight2);

               if (k==0){ // fractions
                  if ((sample=="data_obs" or (sample=="embedded" or isT or isL)) && antiisoRegion)
                      f3real->Fill(mass3,aweight*weight2);
                  if ((sample!="data_obs" && sample!="embedded" && gen_match_2==6) && antiisoRegion)
                      f3jet->Fill(mass3,aweight*weight2);
               }
           }
           if ((do_control_plots>0 or (numberJets==0 && (mymu+mytau+mymet).Pt()>=10)) && mt<50 && q_1*q_2<0){
               if (k==0 && is_includedInEmbedded && signalRegion)
                   h4_ttcontamination->Fill(myvar4,mass4,aweight*weight2);
               if ((sample=="data_obs" or isT) && signalRegion)
                   h4tau_OS[k]->Fill(myvar4,mass4,aweight*weight2);
               if ((sample!="data_obs" && isL) && signalRegion)
                   h4ell_OS[k]->Fill(myvar4,mass4,aweight*weight2);
               if ((sample!="data_obs" && gen_match_2==6) && signalRegion)
                   h4jet_OS[k]->Fill(myvar4,mass4,aweight*weight2);
               if (antiisoRegion && sample=="data_obs"){
                   h4tau_AI[k]->Fill(myvar4,mass4,FF);
                   h4jet_AI[k]->Fill(myvar4,mass4);
               }
               if ((sample!="data_obs" && (sample=="embedded" or isT)) && antiisoRegion)
                   h4tau_AI[k]->Fill(myvar4,mass4,aweight*weight2*FF);
               if ((sample!="data_obs" && sample!="embedded" && isL) && antiisoRegion)
                   h4ell_AI[k]->Fill(myvar4,mass4,aweight*weight2*FF);
               if ((sample!="data_obs" && sample!="embedded" && gen_match_2==6) && antiisoRegion)
                   h4jet_AI[k]->Fill(myvar4,mass4,aweight*weight2);

               if (k==0){ // fractions
                  if ((sample=="data_obs" or (sample=="embedded" or isT or isL)) && antiisoRegion)
                      f4real->Fill(mass4,aweight*weight2);
                  if ((sample!="data_obs" && sample!="embedded" && gen_match_2==6) && antiisoRegion)
                      f4jet->Fill(mass4,aweight*weight2);
               }
           }
           if ((do_control_plots>0 or numberJets==1) && mt<50 && q_1*q_2<0){
               if (k==0 && is_includedInEmbedded && signalRegion)
                   h5_ttcontamination->Fill(myvar5,mass5,aweight*weight2);
               if ((sample=="data_obs" or isT) && signalRegion)
                   h5tau_OS[k]->Fill(myvar5,mass5,aweight*weight2);
               if ((sample!="data_obs" && isL) && signalRegion)
                   h5ell_OS[k]->Fill(myvar5,mass5,aweight*weight2);
               if ((sample!="data_obs" && gen_match_2==6) && signalRegion)
                   h5jet_OS[k]->Fill(myvar5,mass5,aweight*weight2);
               if (antiisoRegion && sample=="data_obs"){
                   h5tau_AI[k]->Fill(myvar5,mass5,FF);
                   h5jet_AI[k]->Fill(myvar5,mass5);
               }
               if ((sample!="data_obs" && (sample=="embedded" or isT)) && antiisoRegion){
                   h5tau_AI[k]->Fill(myvar5,mass5,aweight*weight2*FF);
	       }
               if ((sample!="data_obs" && sample!="embedded" && isL) && antiisoRegion)
                   h5ell_AI[k]->Fill(myvar5,mass5,aweight*weight2*FF);
               if ((sample!="data_obs" && sample!="embedded" && gen_match_2==6) && antiisoRegion)
                   h5jet_AI[k]->Fill(myvar5,mass5,aweight*weight2);

               if (k==0){ // fractions
                  if ((sample=="data_obs" or (sample=="embedded" or isT or isL)) && antiisoRegion)
                      f5real->Fill(mass5,aweight*weight2);
                  if ((sample!="data_obs" && sample!="embedded" && gen_match_2==6) && antiisoRegion)
                      f5jet->Fill(mass5,aweight*weight2);
               }
           }
           if ((do_control_plots>0 or (numberJets>1 && massJets<350)) && mt<50 && q_1*q_2<0){
               if (k==0 && is_includedInEmbedded && signalRegion)
                   h6_ttcontamination->Fill(myvar6,mass6,aweight*weight2);
               if ((sample=="data_obs" or isT) && signalRegion)
                   h6tau_OS[k]->Fill(myvar6,mass6,aweight*weight2);
               if ((sample!="data_obs" && isL) && signalRegion)
                   h6ell_OS[k]->Fill(myvar6,mass6,aweight*weight2);
               if ((sample!="data_obs" && gen_match_2==6) && signalRegion)
                   h6jet_OS[k]->Fill(myvar6,mass6,aweight*weight2);
               if (antiisoRegion && sample=="data_obs"){
                   h6tau_AI[k]->Fill(myvar6,mass6,FF);
                   h6jet_AI[k]->Fill(myvar6,mass6);
               }
               if ((sample!="data_obs" && (sample=="embedded" or isT)) && antiisoRegion)
                   h6tau_AI[k]->Fill(myvar6,mass6,aweight*weight2*FF);
               if ((sample!="data_obs" && sample!="embedded" && isL) && antiisoRegion)
                   h6ell_AI[k]->Fill(myvar6,mass6,aweight*weight2*FF);
               if ((sample!="data_obs" && sample!="embedded" && gen_match_2==6) && antiisoRegion)
                   h6jet_AI[k]->Fill(myvar6,mass6,aweight*weight2);

               if (k==0){ // fractions
                  if ((sample=="data_obs" or (sample=="embedded" or isL or isT)) && antiisoRegion)
                      f6real->Fill(mass6,aweight*weight2);
                  if ((sample!="data_obs" && sample!="embedded" && gen_match_2==6) && antiisoRegion)
                      f6jet->Fill(mass6,aweight*weight2);
               }
           }
           if ((do_control_plots>0 or (numberJets>=2 && massJets>=350 && (mymu+mytau+mymet).Pt()<200)) && mt<50 && q_1*q_2<0){
               if (k==0 && is_includedInEmbedded && signalRegion)
                   h7_ttcontamination->Fill(myvar7,mass7,aweight*weight2);
               if ((sample=="data_obs" or isT) && signalRegion)
                   h7tau_OS[k]->Fill(myvar7,mass7,aweight*weight2);
               if ((sample!="data_obs" && isL) && signalRegion)
                   h7ell_OS[k]->Fill(myvar7,mass7,aweight*weight2);
               if ((sample!="data_obs" && gen_match_2==6) && signalRegion)
                   h7jet_OS[k]->Fill(myvar7,mass7,aweight*weight2);
               if (antiisoRegion && sample=="data_obs"){
                   h7tau_AI[k]->Fill(myvar7,mass7,FF);
                   h7jet_AI[k]->Fill(myvar7,mass7);
               }
               if ((sample!="data_obs" && (sample=="embedded" or isT)) && antiisoRegion)
                   h7tau_AI[k]->Fill(myvar7,mass7,aweight*weight2*FF);
               if ((sample!="data_obs" && sample!="embedded" && isL) && antiisoRegion)
                   h7ell_AI[k]->Fill(myvar7,mass7,aweight*weight2*FF);
               if ((sample!="data_obs" && sample!="embedded" && gen_match_2==6) && antiisoRegion)
                   h7jet_AI[k]->Fill(myvar7,mass7,aweight*weight2);

               if (k==0){ // fractions
                  if ((sample=="data_obs" or (sample=="embedded" or isL or isT)) && antiisoRegion)
                      f7real->Fill(mass7,aweight*weight2);
                  if ((sample!="data_obs" && sample!="embedded" && gen_match_2==6) && antiisoRegion)
                      f7jet->Fill(mass7,aweight*weight2);
               }
           }
           if ((do_control_plots>0 or (numberJets>=2 && massJets>=350 && (mymu+mytau+mymet).Pt()>=200)) && mt<50 && q_1*q_2<0){
               if (k==0 && is_includedInEmbedded && signalRegion)
                   h8_ttcontamination->Fill(myvar8,mass8,aweight*weight2);
               if ((sample=="data_obs" or isT) && signalRegion)
                   h8tau_OS[k]->Fill(myvar8,mass8,aweight*weight2);
               if ((sample!="data_obs" && isL) && signalRegion)
                   h8ell_OS[k]->Fill(myvar8,mass8,aweight*weight2);
               if ((sample!="data_obs" && gen_match_2==6) && signalRegion)
                   h8jet_OS[k]->Fill(myvar8,mass8,aweight*weight2);
               if (antiisoRegion && sample=="data_obs"){
                   h8tau_AI[k]->Fill(myvar8,mass8,FF);
                   h8jet_AI[k]->Fill(myvar8,mass8);
               }
               if ((sample!="data_obs" && (sample=="embedded" or isT)) && antiisoRegion)
                   h8tau_AI[k]->Fill(myvar8,mass8,aweight*weight2*FF);
               if ((sample!="data_obs" && sample!="embedded" && isL) && antiisoRegion)
                   h8ell_AI[k]->Fill(myvar8,mass8,aweight*weight2*FF);
               if ((sample!="data_obs" && sample!="embedded" && gen_match_2==6) && antiisoRegion)
                   h8jet_AI[k]->Fill(myvar8,mass8,aweight*weight2);

               if (k==0){ // fractions
                  if ((sample=="data_obs" or (sample=="embedded" or isT or isL)) && antiisoRegion)
                      f8real->Fill(myvar8,aweight*weight2);
                  if ((sample!="data_obs" && sample!="embedded" && gen_match_2==6) && antiisoRegion)
                      f8jet->Fill(myvar8,aweight*weight2);
               }

           }
	} // end of loop over nbhist

    } // end of loop over events
    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();

    if (sample!="data_obs"){
       EmptyBins(h0tau_OS[0]); EmptyBins(h0ell_OS[0]); EmptyBins(h0jet_OS[0]); EmptyBins(h0tau_AI[0]); EmptyBins(h0ell_AI[0]); EmptyBins(h0jet_AI[0]);
       EmptyBins(h1tau_OS[0]); EmptyBins(h1ell_OS[0]); EmptyBins(h1jet_OS[0]); EmptyBins(h1tau_AI[0]); EmptyBins(h1ell_AI[0]); EmptyBins(h1jet_AI[0]);
       EmptyBins(h2tau_OS[0]); EmptyBins(h2ell_OS[0]); EmptyBins(h2jet_OS[0]); EmptyBins(h2tau_AI[0]); EmptyBins(h2ell_AI[0]); EmptyBins(h2jet_AI[0]);
       EmptyBins(h3tau_OS[0]); EmptyBins(h3ell_OS[0]); EmptyBins(h3jet_OS[0]); EmptyBins(h3tau_AI[0]); EmptyBins(h3ell_AI[0]); EmptyBins(h3jet_AI[0]);
       EmptyBins(h4tau_OS[0]); EmptyBins(h4ell_OS[0]); EmptyBins(h4jet_OS[0]); EmptyBins(h4tau_AI[0]); EmptyBins(h4ell_AI[0]); EmptyBins(h4jet_AI[0]);
       EmptyBins(h5tau_OS[0]); EmptyBins(h5ell_OS[0]); EmptyBins(h5jet_OS[0]); EmptyBins(h5tau_AI[0]); EmptyBins(h5ell_AI[0]); EmptyBins(h5jet_AI[0]);
       EmptyBins(h6tau_OS[0]); EmptyBins(h6ell_OS[0]); EmptyBins(h6jet_OS[0]); EmptyBins(h6tau_AI[0]); EmptyBins(h6ell_AI[0]); EmptyBins(h6jet_AI[0]);
       EmptyBins(h7tau_OS[0]); EmptyBins(h7ell_OS[0]); EmptyBins(h7jet_OS[0]); EmptyBins(h7tau_AI[0]); EmptyBins(h7ell_AI[0]); EmptyBins(h7jet_AI[0]);
       EmptyBins(h8tau_OS[0]); EmptyBins(h8ell_OS[0]); EmptyBins(h8jet_OS[0]); EmptyBins(h8tau_AI[0]); EmptyBins(h8ell_AI[0]); EmptyBins(h8jet_AI[0]);
    }

    f0real->Write();
    f0jet->Write();
    f1real->Write();
    f1jet->Write();
    f2real->Write();
    f2jet->Write();
    f3real->Write();
    f3jet->Write();
    f4real->Write();
    f4jet->Write();
    f5real->Write();
    f5jet->Write();
    f6real->Write();
    f6jet->Write();
    f7real->Write();
    f7jet->Write();
    f8real->Write();
    f8jet->Write();


    TString postfix=postfixFF[0];

    TDirectory *OS0jet =fout->mkdir("mt_0jet");
    OS0jet->cd();
    h0_ttcontamination->SetName("ttcontamination");
    h0_ttcontamination->Write();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs" && k>0) continue;
       if (sample=="data_obs") postfix=postfixFF[k];
       else if ((name=="ST" or name=="VV" or name=="DY" or name=="TT") and k>54) postfix=postfixFF[k-54];
       else if ((name=="embedded") and k>6) postfix=postfixFF[k-6];
       else if (name=="embedded" and k<7) postfix=postfixEmbedded[k];
       else postfix=postfixMC[k];
       if (name!="embedded" && name!="data_obs" and name.find("125")>140){
          h0tau_OS[k]->SetName(name+"T"+postfix);
          h0ell_OS[k]->SetName(name+"L"+postfix);
          h0jet_OS[k]->SetName(name+"J"+postfix);
          h0tau_OS[k]->Write();
          h0ell_OS[k]->Write();
          h0jet_OS[k]->Write();
       }
       else{
          h0tau_OS[k]->SetName(name.c_str()+postfix);
          h0tau_OS[k]->Add(h0ell_OS[k]);
          h0tau_OS[k]->Add(h0jet_OS[k]);
          h0tau_OS[k]->Write();
       }
    }
    TDirectory *AI0jet =fout->mkdir("AI0jet");
    AI0jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else if ((name=="VV" or name=="ST" or name=="DY" or name=="TT") and k>54) postfix=postfixFF[k-54];
       else if ((name=="embedded") and k>6) postfix=postfixFF[k-6];
       else if (name=="embedded" and k<7) postfix=postfixEmbedded[k];
       else postfix=postfixMC[k];
       if (name!="embedded" && name!="data_obs"){
          h0tau_AI[k]->SetName(name+"T"+postfix);
          h0ell_AI[k]->SetName(name+"L"+postfix);
          h0jet_AI[k]->SetName(name+"J"+postfix);
          h0tau_AI[k]->Write();
          h0ell_AI[k]->Write();
          h0jet_AI[k]->Write();
       }
       else {
          h0tau_AI[k]->SetName("reweighted_data_obs"+postfix);
cout<<h0tau_AI[k]->Integral()<<endl;
          h0jet_AI[k]->SetName("data_obs"+postfix);
          h0tau_AI[k]->Write();
          h0jet_AI[k]->Write();
       }
    }

    TDirectory *OS1jet =fout->mkdir("mt_boosted");
    OS1jet->cd();
    h1_ttcontamination->SetName("ttcontamination");
    h1_ttcontamination->Write();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs" && k>0) continue;
       if (sample=="data_obs") postfix=postfixFF[k];
       else if ((name=="ST" or name=="VV" or name=="DY" or name=="TT") and k>54) postfix=postfixFF[k-54];
       else if ((name=="embedded") and k>6) postfix=postfixFF[k-6];
       else if (name=="embedded" and k<7) postfix=postfixEmbedded[k];
       else postfix=postfixMC[k];
       if (name!="embedded" && name!="data_obs" and name.find("125")>140){
          h1tau_OS[k]->SetName(name+"T"+postfix);
          h1ell_OS[k]->SetName(name+"L"+postfix);
          h1jet_OS[k]->SetName(name+"J"+postfix);
          h1tau_OS[k]->Write();
          h1ell_OS[k]->Write();
          h1jet_OS[k]->Write();
       }
       else{
          h1tau_OS[k]->SetName(name.c_str()+postfix);
          h1tau_OS[k]->Add(h1ell_OS[k]);
          h1tau_OS[k]->Add(h1jet_OS[k]);
          h1tau_OS[k]->Write();
       }
    }

    TDirectory *AI1jet =fout->mkdir("AIboosted");
    AI1jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else if ((name=="ST" or name=="VV" or name=="DY" or name=="TT") and k>54) postfix=postfixFF[k-54];
       else if ((name=="embedded") and k>6) postfix=postfixFF[k-6];
       else if (name=="embedded" and k<7) postfix=postfixEmbedded[k];
       else postfix=postfixMC[k];
       if (name!="embedded" && name!="data_obs"){
          h1tau_AI[k]->SetName(name+"T"+postfix);
          h1ell_AI[k]->SetName(name+"L"+postfix);
          h1jet_AI[k]->SetName(name+"J"+postfix);
          h1tau_AI[k]->Write();
          h1ell_AI[k]->Write();
          h1jet_AI[k]->Write();
       }
       else {
          h1tau_AI[k]->SetName("reweighted_data_obs"+postfix);
          h1jet_AI[k]->SetName("data_obs"+postfix);
          h1tau_AI[k]->Write();
          h1jet_AI[k]->Write();
       }
    }

    TDirectory *OS2jet =fout->mkdir("mt_vbf");
    OS2jet->cd();
    h2_ttcontamination->SetName("ttcontamination");
    h2_ttcontamination->Write();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs" && k>0 ) continue;
       if (sample=="data_obs") postfix=postfixFF[k];
       else if ((name=="ST" or name=="VV" or name=="DY" or name=="TT") and k>54) postfix=postfixFF[k-54];
       else if ((name=="embedded") and k>6) postfix=postfixFF[k-6];
       else if (name=="embedded" and k<7) postfix=postfixEmbedded[k];
       else postfix=postfixMC[k];
       if (name!="embedded" && name!="data_obs" and name.find("125")>140){
          h2tau_OS[k]->SetName(name+"T"+postfix);
          h2ell_OS[k]->SetName(name+"L"+postfix);
          h2jet_OS[k]->SetName(name+"J"+postfix);
          h2tau_OS[k]->Write();
          h2ell_OS[k]->Write();
          h2jet_OS[k]->Write();
       }
       else{
          h2tau_OS[k]->SetName(name.c_str()+postfix);
          h2tau_OS[k]->Add(h2ell_OS[k]);
          h2tau_OS[k]->Add(h2jet_OS[k]);
          h2tau_OS[k]->Write();
       }
    }

    TDirectory *AI2jet =fout->mkdir("AIvbf");
    AI2jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else if ((name=="ST" or name=="VV" or name=="DY" or name=="TT") and k>54) postfix=postfixFF[k-54];
       else if ((name=="embedded") and k>6) postfix=postfixFF[k-6];
       else if (name=="embedded" and k<7) postfix=postfixEmbedded[k];
       else postfix=postfixMC[k];
       if (name!="embedded" && name!="data_obs"){
          h2tau_AI[k]->SetName(name+"T"+postfix);
          h2ell_AI[k]->SetName(name+"L"+postfix);
          h2jet_AI[k]->SetName(name+"J"+postfix);
          h2tau_AI[k]->Write();
          h2ell_AI[k]->Write();
          h2jet_AI[k]->Write();
       }
       else {
          h2tau_AI[k]->SetName("reweighted_data_obs"+postfix);
          h2jet_AI[k]->SetName("data_obs"+postfix);
          h2tau_AI[k]->Write();
          h2jet_AI[k]->Write();
       }
    }

    TDirectory *OS3jet =fout->mkdir("mt_0jetlow");
    OS3jet->cd();
    h3_ttcontamination->SetName("ttcontamination");
    h3_ttcontamination->Write();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs" && k>0 ) continue;
       if (sample=="data_obs") postfix=postfixFF[k];
       else if ((name=="ST" or name=="VV" or name=="DY" or name=="TT") and k>54) postfix=postfixFF[k-54];
       else if ((name=="embedded") and k>6) postfix=postfixFF[k-6];
       else if (name=="embedded" and k<7) postfix=postfixEmbedded[k];
       else postfix=postfixMC[k];
       if (name!="embedded" && name!="data_obs" and name.find("125")>140){
          h3tau_OS[k]->SetName(name+"T"+postfix);
          h3ell_OS[k]->SetName(name+"L"+postfix);
          h3jet_OS[k]->SetName(name+"J"+postfix);
          h3tau_OS[k]->Write();
          h3ell_OS[k]->Write();
          h3jet_OS[k]->Write();
       }
       else{
          h3tau_OS[k]->SetName(name.c_str()+postfix);
          h3tau_OS[k]->Add(h3ell_OS[k]);
          h3tau_OS[k]->Add(h3jet_OS[k]);
          h3tau_OS[k]->Write();
       }
    }

    TDirectory *AI3jet =fout->mkdir("AI0jetlow");
    AI3jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else if ((name=="ST" or name=="VV" or name=="DY" or name=="TT") and k>54) postfix=postfixFF[k-54];
       else if ((name=="embedded") and k>6) postfix=postfixFF[k-6];
       else if (name=="embedded" and k<7) postfix=postfixEmbedded[k];
       else postfix=postfixMC[k];
       if (name!="embedded" && name!="data_obs"){
          h3tau_AI[k]->SetName(name+"T"+postfix);
          h3ell_AI[k]->SetName(name+"L"+postfix);
          h3jet_AI[k]->SetName(name+"J"+postfix);
          h3tau_AI[k]->Write();
          h3ell_AI[k]->Write();
          h3jet_AI[k]->Write();
       }
       else {
          h3tau_AI[k]->SetName("reweighted_data_obs"+postfix);
          h3jet_AI[k]->SetName("data_obs"+postfix);
          h3tau_AI[k]->Write();
          h3jet_AI[k]->Write();
       }
    }

    TDirectory *OS4jet =fout->mkdir("mt_0jethigh");
    OS4jet->cd();
    h4_ttcontamination->SetName("ttcontamination");
    h4_ttcontamination->Write();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs" && k>0 ) continue;
       if (sample=="data_obs") postfix=postfixFF[k];
       else if ((name=="VV" or name=="DY" or name=="TT" or name=="ST") and k>54) postfix=postfixFF[k-54];
       else if ((name=="embedded") and k>6) postfix=postfixFF[k-6];
       else if (name=="embedded" and k<7) postfix=postfixEmbedded[k];
       else postfix=postfixMC[k];
       if (name!="embedded" && name!="data_obs" and name.find("125")>140){
          h4tau_OS[k]->SetName(name+"T"+postfix);
          h4ell_OS[k]->SetName(name+"L"+postfix);
          h4jet_OS[k]->SetName(name+"J"+postfix);
          h4tau_OS[k]->Write();
          h4ell_OS[k]->Write();
          h4jet_OS[k]->Write();
       }
       else{
          h4tau_OS[k]->SetName(name.c_str()+postfix);
          h4tau_OS[k]->Add(h4ell_OS[k]);
          h4tau_OS[k]->Add(h4jet_OS[k]);
          h4tau_OS[k]->Write();
       }
    }

    TDirectory *AI4jet =fout->mkdir("AI0jethigh");
    AI4jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else if ((name=="VV" or name=="DY" or name=="TT" or name=="ST") and k>54) postfix=postfixFF[k-54];
       else if ((name=="embedded") and k>6) postfix=postfixFF[k-6];
       else if (name=="embedded" and k<7) postfix=postfixEmbedded[k];
       else postfix=postfixMC[k];
       if (name!="embedded" && name!="data_obs"){
          h4tau_AI[k]->SetName(name+"T"+postfix);
          h4ell_AI[k]->SetName(name+"L"+postfix);
          h4jet_AI[k]->SetName(name+"J"+postfix);
          h4tau_AI[k]->Write();
          h4ell_AI[k]->Write();
          h4jet_AI[k]->Write();
       }
       else {
          h4tau_AI[k]->SetName("reweighted_data_obs"+postfix);
          h4jet_AI[k]->SetName("data_obs"+postfix);
          h4tau_AI[k]->Write();
          h4jet_AI[k]->Write();
       }
    }

    TDirectory *OS5jet =fout->mkdir("mt_boosted1");
    OS5jet->cd();
    h5_ttcontamination->SetName("ttcontamination");
    h5_ttcontamination->Write();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs" && k>0 ) continue;
       if (sample=="data_obs") postfix=postfixFF[k];
       else if ((name=="VV" or name=="DY" or name=="TT" or name=="ST") and k>54) postfix=postfixFF[k-54];
       else if ((name=="embedded") and k>6) postfix=postfixFF[k-6];
       else if (name=="embedded" and k<7) postfix=postfixEmbedded[k];
       else postfix=postfixMC[k];
       if (name!="embedded" && name!="data_obs" and name.find("125")>140){
          h5tau_OS[k]->SetName(name+"T"+postfix);
          h5ell_OS[k]->SetName(name+"L"+postfix);
          h5jet_OS[k]->SetName(name+"J"+postfix);
          h5tau_OS[k]->Write();
          h5ell_OS[k]->Write();
          h5jet_OS[k]->Write();
       }
       else{
          h5tau_OS[k]->SetName(name.c_str()+postfix);
          h5tau_OS[k]->Add(h5ell_OS[k]);
          h5tau_OS[k]->Add(h5jet_OS[k]);
          h5tau_OS[k]->Write();
       }
    }

    TDirectory *AI5jet =fout->mkdir("AIboosted1");
    AI5jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else if ((name=="VV" or name=="DY" or name=="TT" or name=="ST") and k>54) postfix=postfixFF[k-54];
       else if ((name=="embedded") and k>6) postfix=postfixFF[k-6];
       else if (name=="embedded" and k<7) postfix=postfixEmbedded[k];
       else postfix=postfixMC[k];
       if (name!="embedded" && name!="data_obs"){
          h5tau_AI[k]->SetName(name+"T"+postfix);
          h5ell_AI[k]->SetName(name+"L"+postfix);
          h5jet_AI[k]->SetName(name+"J"+postfix);
          h5tau_AI[k]->Write();
          h5ell_AI[k]->Write();
          h5jet_AI[k]->Write();
       }
       else {
          h5tau_AI[k]->SetName("reweighted_data_obs"+postfix);
          h5jet_AI[k]->SetName("data_obs"+postfix);
          h5tau_AI[k]->Write();
          h5jet_AI[k]->Write();
       }
    }

    TDirectory *OS6jet =fout->mkdir("mt_boosted2");
    OS6jet->cd();
    h6_ttcontamination->SetName("ttcontamination");
    h6_ttcontamination->Write();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs" && k>0 ) continue;
       if (sample=="data_obs") postfix=postfixFF[k];
       else if ((name=="VV" or name=="DY" or name=="TT" or name=="ST") and k>54) postfix=postfixFF[k-54];
       else if ((name=="embedded") and k>6) postfix=postfixFF[k-6];
       else if (name=="embedded" and k<7) postfix=postfixEmbedded[k];
       else postfix=postfixMC[k];
       if (name!="embedded" && name!="data_obs" and name.find("125")>140){
          h6tau_OS[k]->SetName(name+"T"+postfix);
          h6ell_OS[k]->SetName(name+"L"+postfix);
          h6jet_OS[k]->SetName(name+"J"+postfix);
          h6tau_OS[k]->Write();
          h6ell_OS[k]->Write();
          h6jet_OS[k]->Write();
       }
       else{
          h6tau_OS[k]->SetName(name.c_str()+postfix);
          h6tau_OS[k]->Add(h6ell_OS[k]);
          h6tau_OS[k]->Add(h6jet_OS[k]);
          h6tau_OS[k]->Write();
       }
    }

    TDirectory *AI6jet =fout->mkdir("AIboosted2");
    AI6jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else if ((name=="VV" or name=="DY" or name=="TT" or name=="ST") and k>54) postfix=postfixFF[k-54];
       else if ((name=="embedded") and k>6) postfix=postfixFF[k-6];
       else if (name=="embedded" and k<7) postfix=postfixEmbedded[k];
       else postfix=postfixMC[k];
       if (name!="embedded" && name!="data_obs"){
          h6tau_AI[k]->SetName(name+"T"+postfix);
          h6ell_AI[k]->SetName(name+"L"+postfix);
          h6jet_AI[k]->SetName(name+"J"+postfix);
          h6tau_AI[k]->Write();
          h6ell_AI[k]->Write();
          h6jet_AI[k]->Write();
       }
       else {
          h6tau_AI[k]->SetName("reweighted_data_obs"+postfix);
          h6jet_AI[k]->SetName("data_obs"+postfix);
          h6tau_AI[k]->Write();
          h6jet_AI[k]->Write();
       }
    }

    TDirectory *OS7jet =fout->mkdir("mt_vbflow");
    OS7jet->cd();
    h7_ttcontamination->SetName("ttcontamination");
    h7_ttcontamination->Write();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs" && k>0 ) continue;
       if (sample=="data_obs") postfix=postfixFF[k];
       else if ((name=="VV" or name=="DY" or name=="TT" or name=="ST") and k>54) postfix=postfixFF[k-54];
       else if ((name=="embedded") and k>6) postfix=postfixFF[k-6];
       else if (name=="embedded" and k<7) postfix=postfixEmbedded[k];
       else postfix=postfixMC[k];
       if (name!="embedded" && name!="data_obs" and name.find("125")>140){
          h7tau_OS[k]->SetName(name+"T"+postfix);
          h7ell_OS[k]->SetName(name+"L"+postfix);
          h7jet_OS[k]->SetName(name+"J"+postfix);
          h7tau_OS[k]->Write();
          h7ell_OS[k]->Write();
          h7jet_OS[k]->Write();
       }
       else{
          h7tau_OS[k]->SetName(name.c_str()+postfix);
          h7tau_OS[k]->Add(h7ell_OS[k]);
          h7tau_OS[k]->Add(h7jet_OS[k]);
          h7tau_OS[k]->Write();
       }
    }

    TDirectory *AI7jet =fout->mkdir("AIvbflow");
    AI7jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else if ((name=="VV" or name=="DY" or name=="TT" or name=="ST") and k>54) postfix=postfixFF[k-54];
       else if ((name=="embedded") and k>6) postfix=postfixFF[k-6];
       else if (name=="embedded" and k<7) postfix=postfixEmbedded[k];
       else postfix=postfixMC[k];
       if (name!="embedded" && name!="data_obs"){
          h7tau_AI[k]->SetName(name+"T"+postfix);
          h7ell_AI[k]->SetName(name+"L"+postfix);
          h7jet_AI[k]->SetName(name+"J"+postfix);
          h7tau_AI[k]->Write();
          h7ell_AI[k]->Write();
          h7jet_AI[k]->Write();
       }
       else {
          h7tau_AI[k]->SetName("reweighted_data_obs"+postfix);
          h7jet_AI[k]->SetName("data_obs"+postfix);
          h7tau_AI[k]->Write();
          h7jet_AI[k]->Write();
       }
    }

    TDirectory *OS8jet =fout->mkdir("mt_vbfhigh");
    OS8jet->cd();
    h8_ttcontamination->SetName("ttcontamination");
    h8_ttcontamination->Write();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs" && k>0 ) continue;
       if (sample=="data_obs") postfix=postfixFF[k];
       else if ((name=="VV" or name=="DY" or name=="TT" or name=="ST") and k>54) postfix=postfixFF[k-54];
       else if ((name=="embedded") and k>6) postfix=postfixFF[k-6];
       else if (name=="embedded" and k<7) postfix=postfixEmbedded[k];
       else postfix=postfixMC[k];
       if (name!="embedded" && name!="data_obs" and name.find("125")>140){
          h8tau_OS[k]->SetName(name+"T"+postfix);
          h8ell_OS[k]->SetName(name+"L"+postfix);
          h8jet_OS[k]->SetName(name+"J"+postfix);
          h8tau_OS[k]->Write();
          h8ell_OS[k]->Write();
          h8jet_OS[k]->Write();
       }
       else{
          h8tau_OS[k]->SetName(name.c_str()+postfix);
cout<<h8tau_OS[k]->GetEntries()/nbevt->GetBinContent(1)<<endl;
          h8tau_OS[k]->Add(h8ell_OS[k]);
cout<<h8tau_OS[k]->GetEntries()/nbevt->GetBinContent(1)<<endl;
          h8tau_OS[k]->Add(h8jet_OS[k]);
cout<<h8tau_OS[k]->GetEntries()<<" "<<nbevt->GetBinContent(1)<<" "<<h8tau_OS[k]->GetEntries()/nbevt->GetBinContent(1)<<endl;
          h8tau_OS[k]->Write();
       }
    }

    TDirectory *AI8jet =fout->mkdir("AIvbfhigh");
    AI8jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else if ((name=="VV" or name=="DY" or name=="TT" or name=="ST") and k>54) postfix=postfixFF[k-54];
       else if ((name=="embedded") and k>6) postfix=postfixFF[k-6];
       else if (name=="embedded" and k<7) postfix=postfixEmbedded[k];
       else postfix=postfixMC[k];
       if (name!="embedded" && name!="data_obs"){
          h8tau_AI[k]->SetName(name+"T"+postfix);
          h8ell_AI[k]->SetName(name+"L"+postfix);
          h8jet_AI[k]->SetName(name+"J"+postfix);
          h8tau_AI[k]->Write();
          h8ell_AI[k]->Write();
          h8jet_AI[k]->Write();
       }
       else {
          h8tau_AI[k]->SetName("reweighted_data_obs"+postfix);
          h8jet_AI[k]->SetName("data_obs"+postfix);
          h8tau_AI[k]->Write();
          h8jet_AI[k]->Write();
       }
    }


    fout->Close();
    delete ff;
    ff_file->Close();
    delete wmc;
    delete w;
} 


