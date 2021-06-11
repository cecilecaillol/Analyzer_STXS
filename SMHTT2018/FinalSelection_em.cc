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
#include "qq2Hqq_uncert_scheme.h"

using namespace std;

int main(int argc, char** argv) {

    int do_control_plots=0;
    bool do_differential=false;
    bool do_topcontrol=false;

    if (do_control_plots==0) do_topcontrol=false;
    if (do_differential) do_topcontrol=false;
    if (do_differential) do_control_plots=0;

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

    float xs=1.0; float weight=1.0; float luminosity=59740.0;
    if (sample=="Z" or sample=="DY" or sample=="ZL" or sample=="ZTT" or sample=="ZJ" or sample=="ZLL"){ xs=6225.42; weight=luminosity*xs/ngen;}
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
    else if (sample=="ggH_htt125") {xs=48.30*0.06208; weight=luminosity*xs/ngen;}
    else if (sample=="qqH_htt125") {xs=3.770*0.06208; weight=luminosity*xs/ngen;}
    else if (sample=="WplusH125") {xs=0.8331*0.06208; weight=luminosity*xs/ngen;}
    else if (sample=="WminusH125") {xs=0.5272*0.06208; weight=luminosity*xs/ngen;}
    else if (sample=="ZH125") {xs=0.7544*0.06208; weight=luminosity*xs/ngen;}
    else if (sample=="GGZH125") {xs=0.1223*0.06208; weight=luminosity*xs/ngen;}
    else if (sample=="GGZHLLTT125") {xs=0.1223*0.06208*3*0.033658; weight=luminosity*xs/ngen;}
    else if (sample=="GGZHNNTT125") {xs=0.1223*0.06208*0.2000; weight=luminosity*xs/ngen;}
    else if (sample=="GGZHQQTT125") {xs=0.1223*0.06208*0.6991; weight=luminosity*xs/ngen;}
    else if (sample=="GGHWW") {xs=48.30*0.2203*0.3258*0.3258; weight=luminosity*xs/ngen;}
    else if (sample=="VBFHWW") {xs=3.770*0.2203*0.3258*0.3258; weight=luminosity*xs/ngen;}
    else if (sample=="WplusHWW") {xs=0.8331*0.2203; weight=luminosity*xs/ngen;}
    else if (sample=="WminusHWW") {xs=0.5272*0.2203; weight=luminosity*xs/ngen;}
    else if (sample=="ZHWW") {xs=0.7544*0.2203; weight=luminosity*xs/ngen;}
    else if (sample=="GGZHWW") {xs=0.1223*0.2203; weight=luminosity*xs/ngen;}
    /*else if (sample=="ZZ") {xs=12.14; weight=luminosity*xs/ngen;}
    else if (sample=="WZ") {xs=27.57; weight=luminosity*xs/ngen;}
    else if (sample=="WW") {xs=75.88; weight=luminosity*xs/ngen;}*/
else if (sample=="ZZ") {xs=16.523; weight=luminosity*xs/ngen;}
    else if (sample=="WZ") {xs=47.13; weight=luminosity*xs/ngen;}
    else if (sample=="WW") {xs=118.7; weight=luminosity*xs/ngen;}
    else if (sample=="WZ1L1Nu2Q") {xs=10.71; weight=luminosity*xs/ngen;}
    else if (sample=="WZ1L3Nu") {xs=3.05; weight=luminosity*xs/ngen;}
    else if (sample=="WZJets") {xs=5.26; weight=luminosity*xs/ngen;}
    else if (sample=="WZ3L1Nu") {xs=4.43; weight=luminosity*xs/ngen;}
    else if (sample=="WZ2L2Q") {xs=5.52; weight=luminosity*xs/ngen;}
    else if (sample=="WW1L1Nu2Q") {xs=49.997; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ4L") {xs=1.26; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ2L2Q") {xs=3.38; weight=luminosity*xs/ngen;}
    else if (sample=="VV2L2Nu") {xs=13.84; weight=luminosity*xs/ngen;}
    else if (sample=="WGLNu") {xs=489.0; weight=luminosity*xs/ngen;}
    else if (sample=="EWKWminus") {xs=23.24; weight=luminosity*xs/ngen;}
    else if (sample=="EWKWplus") {xs=29.59; weight=luminosity*xs/ngen;}
    else if (sample=="EWKZLL") {xs=4.321; weight=luminosity*xs/ngen;}
    else if (sample=="EWKZNuNu") {xs=10.66; weight=luminosity*xs/ngen;}

cout<<xs<<" "<<ngen<<" "<<weight<<endl;

    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(10);

    arbre->SetBranchAddress("Rivet_higgsPt", &Rivet_higgsPt);
    arbre->SetBranchAddress("Rivet_nJets30", &Rivet_nJets30);
    arbre->SetBranchAddress("Rivet_stage1_1_fine_cat_pTjet30GeV", & Rivet_stage1_1_fine_cat_pTjet30GeV);
    arbre->SetBranchAddress("Rivet_stage1_1_cat_pTjet30GeV", & Rivet_stage1_1_cat_pTjet30GeV);
    arbre->SetBranchAddress("Rivet_stage1_cat_pTjet30GeV", & Rivet_stage1_cat_pTjet30GeV);
    arbre->SetBranchAddress("Rivet_j1pt", &Rivet_j1pt);
    arbre->SetBranchAddress("Rivet_j2pt", &Rivet_j2pt);
    arbre->SetBranchAddress("Rivet_j1eta", &Rivet_j1eta);
    arbre->SetBranchAddress("Rivet_j2eta", &Rivet_j2eta);
    arbre->SetBranchAddress("Rivet_j1phi", &Rivet_j1phi);
    arbre->SetBranchAddress("Rivet_j2phi", &Rivet_j2phi);
    arbre->SetBranchAddress("Rivet_j1m", &Rivet_j1m);
    arbre->SetBranchAddress("Rivet_j2m", &Rivet_j2m);
    arbre->SetBranchAddress("gentau1_eta", &gentau1_eta);
    arbre->SetBranchAddress("gentau2_eta", &gentau2_eta);
    arbre->SetBranchAddress("gentau1_pt", &gentau1_pt);
    arbre->SetBranchAddress("gentau2_pt", &gentau2_pt);

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
    arbre->SetBranchAddress("q_2", &q_2);
    arbre->SetBranchAddress("pt_2", &pt_2);
    arbre->SetBranchAddress("eta_2", &eta_2);
    arbre->SetBranchAddress("m_2", &m_2);
    arbre->SetBranchAddress("phi_2", &phi_2);

    arbre->SetBranchAddress("m_sv", &m_sv);
    arbre->SetBranchAddress("m_sv_muonESDown", &m_sv_muonESDown);
    arbre->SetBranchAddress("m_sv_muonESUp", &m_sv_muonESUp);
    arbre->SetBranchAddress("m_sv_UESUp", &m_sv_UESUp);
    arbre->SetBranchAddress("m_sv_UESDown", &m_sv_UESDown);
    arbre->SetBranchAddress("m_sv_elescaleESUp", &m_sv_elescaleESUp);
    arbre->SetBranchAddress("m_sv_elescaleESDown", &m_sv_elescaleESDown);
    arbre->SetBranchAddress("m_sv_ResponseDown", &m_sv_ResponseDown);
    arbre->SetBranchAddress("m_sv_ResponseUp", &m_sv_ResponseUp);
    arbre->SetBranchAddress("m_sv_ResolutionDown", &m_sv_ResolutionDown);
    arbre->SetBranchAddress("m_sv_ResolutionUp", &m_sv_ResolutionUp);
    arbre->SetBranchAddress("m_sv_JetAbsoluteUp", &m_sv_JetAbsoluteUp);
    arbre->SetBranchAddress("m_sv_JetAbsoluteDown", &m_sv_JetAbsoluteDown);
    arbre->SetBranchAddress("m_sv_JetAbsoluteyearUp", &m_sv_JetAbsoluteyearUp);
    arbre->SetBranchAddress("m_sv_JetAbsoluteyearDown", &m_sv_JetAbsoluteyearDown);
    arbre->SetBranchAddress("m_sv_JetBBEC1Up", &m_sv_JetBBEC1Up);
    arbre->SetBranchAddress("m_sv_JetBBEC1Down", &m_sv_JetBBEC1Down);
    arbre->SetBranchAddress("m_sv_JetBBEC1yearUp", &m_sv_JetBBEC1yearUp);
    arbre->SetBranchAddress("m_sv_JetBBEC1yearDown", &m_sv_JetBBEC1yearDown);
    arbre->SetBranchAddress("m_sv_JetEC2Up", &m_sv_JetEC2Up);
    arbre->SetBranchAddress("m_sv_JetEC2Down", &m_sv_JetEC2Down);
    arbre->SetBranchAddress("m_sv_JetEC2yearUp", &m_sv_JetEC2yearUp);
    arbre->SetBranchAddress("m_sv_JetEC2yearDown", &m_sv_JetEC2yearDown);
    arbre->SetBranchAddress("m_sv_JetFlavorQCDUp", &m_sv_JetFlavorQCDUp);
    arbre->SetBranchAddress("m_sv_JetFlavorQCDDown", &m_sv_JetFlavorQCDDown);
    arbre->SetBranchAddress("m_sv_JetHFUp", &m_sv_JetHFUp);
    arbre->SetBranchAddress("m_sv_JetHFDown", &m_sv_JetHFDown);
    arbre->SetBranchAddress("m_sv_JetHFyearUp", &m_sv_JetHFyearUp);
    arbre->SetBranchAddress("m_sv_JetHFyearDown", &m_sv_JetHFyearDown);
    arbre->SetBranchAddress("m_sv_JetRelativeBalUp", &m_sv_JetRelativeBalUp);
    arbre->SetBranchAddress("m_sv_JetRelativeBalDown", &m_sv_JetRelativeBalDown);
    arbre->SetBranchAddress("m_sv_JetRelativeSampleUp", &m_sv_JetRelativeSampleUp);
    arbre->SetBranchAddress("m_sv_JetRelativeSampleDown", &m_sv_JetRelativeSampleDown);
    arbre->SetBranchAddress("m_sv_JERUp", &m_sv_JERUp);
    arbre->SetBranchAddress("m_sv_JERDown", &m_sv_JERDown);

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
    arbre->SetBranchAddress("metphi_JetAbsoluteDown", &metphi_JetAbsoluteDown);
    arbre->SetBranchAddress("met_JetAbsoluteDown", &met_JetAbsoluteDown);
    arbre->SetBranchAddress("metphi_JetAbsoluteUp", &metphi_JetAbsoluteUp);
    arbre->SetBranchAddress("met_JetAbsoluteUp", &met_JetAbsoluteUp);
    arbre->SetBranchAddress("metphi_JetAbsoluteyearDown", &metphi_JetAbsoluteyearDown);
    arbre->SetBranchAddress("met_JetAbsoluteyearDown", &met_JetAbsoluteyearDown);
    arbre->SetBranchAddress("metphi_JetAbsoluteyearUp", &metphi_JetAbsoluteyearUp);
    arbre->SetBranchAddress("met_JetAbsoluteyearUp", &met_JetAbsoluteyearUp);
    arbre->SetBranchAddress("metphi_JetBBEC1Down", &metphi_JetBBEC1Down);
    arbre->SetBranchAddress("met_JetBBEC1Down", &met_JetBBEC1Down);
    arbre->SetBranchAddress("metphi_JetBBEC1Up", &metphi_JetBBEC1Up);
    arbre->SetBranchAddress("met_JetBBEC1Up", &met_JetBBEC1Up);
    arbre->SetBranchAddress("metphi_JetBBEC1yearDown", &metphi_JetBBEC1yearDown);
    arbre->SetBranchAddress("met_JetBBEC1yearDown", &met_JetBBEC1yearDown);
    arbre->SetBranchAddress("metphi_JetBBEC1yearUp", &metphi_JetBBEC1yearUp);
    arbre->SetBranchAddress("met_JetBBEC1yearUp", &met_JetBBEC1yearUp);
    arbre->SetBranchAddress("metphi_JetEC2Down", &metphi_JetEC2Down);
    arbre->SetBranchAddress("met_JetEC2Down", &met_JetEC2Down);
    arbre->SetBranchAddress("metphi_JetEC2Up", &metphi_JetEC2Up);
    arbre->SetBranchAddress("met_JetEC2Up", &met_JetEC2Up);
    arbre->SetBranchAddress("metphi_JetEC2yearDown", &metphi_JetEC2yearDown);
    arbre->SetBranchAddress("met_JetEC2yearDown", &met_JetEC2yearDown);
    arbre->SetBranchAddress("metphi_JetEC2yearUp", &metphi_JetEC2yearUp);
    arbre->SetBranchAddress("met_JetEC2yearUp", &met_JetEC2yearUp);
    arbre->SetBranchAddress("metphi_JetFlavorQCDDown", &metphi_JetFlavorQCDDown);
    arbre->SetBranchAddress("met_JetFlavorQCDDown", &met_JetFlavorQCDDown);
    arbre->SetBranchAddress("metphi_JetFlavorQCDUp", &metphi_JetFlavorQCDUp);
    arbre->SetBranchAddress("met_JetFlavorQCDUp", &met_JetFlavorQCDUp);
    arbre->SetBranchAddress("metphi_JetHFDown", &metphi_JetHFDown);
    arbre->SetBranchAddress("met_JetHFDown", &met_JetHFDown);
    arbre->SetBranchAddress("metphi_JetHFUp", &metphi_JetHFUp);
    arbre->SetBranchAddress("met_JetHFUp", &met_JetHFUp);
    arbre->SetBranchAddress("metphi_JetHFyearDown", &metphi_JetHFyearDown);
    arbre->SetBranchAddress("met_JetHFyearDown", &met_JetHFyearDown);
    arbre->SetBranchAddress("metphi_JetHFyearUp", &metphi_JetHFyearUp);
    arbre->SetBranchAddress("met_JetHFyearUp", &met_JetHFyearUp);
    arbre->SetBranchAddress("metphi_JetRelativeBalDown", &metphi_JetRelativeBalDown);
    arbre->SetBranchAddress("met_JetRelativeBalDown", &met_JetRelativeBalDown);
    arbre->SetBranchAddress("metphi_JetRelativeBalUp", &metphi_JetRelativeBalUp);
    arbre->SetBranchAddress("met_JetRelativeBalUp", &met_JetRelativeBalUp);
    arbre->SetBranchAddress("metphi_JetRelativeSampleDown", &metphi_JetRelativeSampleDown);
    arbre->SetBranchAddress("met_JetRelativeSampleDown", &met_JetRelativeSampleDown);
    arbre->SetBranchAddress("metphi_JetRelativeSampleUp", &metphi_JetRelativeSampleUp);
    arbre->SetBranchAddress("met_JetRelativeSampleUp", &met_JetRelativeSampleUp);
    arbre->SetBranchAddress("metphi_JERDown", &metphi_JERDown);
    arbre->SetBranchAddress("met_JERDown", &met_JERDown);
    arbre->SetBranchAddress("metphi_JERUp", &metphi_JERUp);
    arbre->SetBranchAddress("met_JERUp", &met_JERUp);

    arbre->SetBranchAddress("njets", &njets);
    arbre->SetBranchAddress("njets_JetAbsoluteDown", &njets_JetAbsoluteDown);
    arbre->SetBranchAddress("njets_JetAbsoluteUp", &njets_JetAbsoluteUp);
    arbre->SetBranchAddress("njets_JetAbsoluteyearDown", &njets_JetAbsoluteyearDown);
    arbre->SetBranchAddress("njets_JetAbsoluteyearUp", &njets_JetAbsoluteyearUp);
    arbre->SetBranchAddress("njets_JetBBEC1Down", &njets_JetBBEC1Down);
    arbre->SetBranchAddress("njets_JetBBEC1Up", &njets_JetBBEC1Up);
    arbre->SetBranchAddress("njets_JetBBEC1yearDown", &njets_JetBBEC1yearDown);
    arbre->SetBranchAddress("njets_JetBBEC1yearUp", &njets_JetBBEC1yearUp);
    arbre->SetBranchAddress("njets_JetEC2Down", &njets_JetEC2Down);
    arbre->SetBranchAddress("njets_JetEC2Up", &njets_JetEC2Up);
    arbre->SetBranchAddress("njets_JetEC2yearDown", &njets_JetEC2yearDown);
    arbre->SetBranchAddress("njets_JetEC2yearUp", &njets_JetEC2yearUp);
    arbre->SetBranchAddress("njets_JetFlavorQCDDown", &njets_JetFlavorQCDDown);
    arbre->SetBranchAddress("njets_JetFlavorQCDUp", &njets_JetFlavorQCDUp);
    arbre->SetBranchAddress("njets_JetHFDown", &njets_JetHFDown);
    arbre->SetBranchAddress("njets_JetHFUp", &njets_JetHFUp);
    arbre->SetBranchAddress("njets_JetHFyearDown", &njets_JetHFyearDown);
    arbre->SetBranchAddress("njets_JetHFyearUp", &njets_JetHFyearUp);
    arbre->SetBranchAddress("njets_JetRelativeBalDown", &njets_JetRelativeBalDown);
    arbre->SetBranchAddress("njets_JetRelativeBalUp", &njets_JetRelativeBalUp);
    arbre->SetBranchAddress("njets_JetRelativeSampleDown", &njets_JetRelativeSampleDown);
    arbre->SetBranchAddress("njets_JetRelativeSampleUp", &njets_JetRelativeSampleUp);
    arbre->SetBranchAddress("njets_JERDown", &njets_JERDown);
    arbre->SetBranchAddress("njets_JERUp", &njets_JERUp);

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
    arbre->SetBranchAddress("mjj_JetAbsoluteDown", &mjj_JetAbsoluteDown);
    arbre->SetBranchAddress("mjj_JetAbsoluteUp", &mjj_JetAbsoluteUp);
    arbre->SetBranchAddress("mjj_JetAbsoluteyearDown", &mjj_JetAbsoluteyearDown);
    arbre->SetBranchAddress("mjj_JetAbsoluteyearUp", &mjj_JetAbsoluteyearUp);
    arbre->SetBranchAddress("mjj_JetBBEC1Down", &mjj_JetBBEC1Down);
    arbre->SetBranchAddress("mjj_JetBBEC1Up", &mjj_JetBBEC1Up);
    arbre->SetBranchAddress("mjj_JetBBEC1yearDown", &mjj_JetBBEC1yearDown);
    arbre->SetBranchAddress("mjj_JetBBEC1yearUp", &mjj_JetBBEC1yearUp);
    arbre->SetBranchAddress("mjj_JetEC2Down", &mjj_JetEC2Down);
    arbre->SetBranchAddress("mjj_JetEC2Up", &mjj_JetEC2Up);
    arbre->SetBranchAddress("mjj_JetEC2yearDown", &mjj_JetEC2yearDown);
    arbre->SetBranchAddress("mjj_JetEC2yearUp", &mjj_JetEC2yearUp);
    arbre->SetBranchAddress("mjj_JetFlavorQCDDown", &mjj_JetFlavorQCDDown);
    arbre->SetBranchAddress("mjj_JetFlavorQCDUp", &mjj_JetFlavorQCDUp);
    arbre->SetBranchAddress("mjj_JetHFDown", &mjj_JetHFDown);
    arbre->SetBranchAddress("mjj_JetHFUp", &mjj_JetHFUp);
    arbre->SetBranchAddress("mjj_JetHFyearDown", &mjj_JetHFyearDown);
    arbre->SetBranchAddress("mjj_JetHFyearUp", &mjj_JetHFyearUp);
    arbre->SetBranchAddress("mjj_JetRelativeBalDown", &mjj_JetRelativeBalDown);
    arbre->SetBranchAddress("mjj_JetRelativeBalUp", &mjj_JetRelativeBalUp);
    arbre->SetBranchAddress("mjj_JetRelativeSampleDown", &mjj_JetRelativeSampleDown);
    arbre->SetBranchAddress("mjj_JetRelativeSampleUp", &mjj_JetRelativeSampleUp);
    arbre->SetBranchAddress("mjj_JERDown", &mjj_JERDown);
    arbre->SetBranchAddress("mjj_JERUp", &mjj_JERUp);

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

    arbre->SetBranchAddress("pt_1_ScaleUp", &pt_1_ScaleUp);
    arbre->SetBranchAddress("pt_1_ScaleDown", &pt_1_ScaleDown);
    arbre->SetBranchAddress("bweight", &bweight);
    arbre->SetBranchAddress("genpt_1", &genpt_1);
    arbre->SetBranchAddress("geneta_1", &geneta_1);
    arbre->SetBranchAddress("genpt_2", &genpt_2);
    arbre->SetBranchAddress("geneta_2", &geneta_2);

    arbre->SetBranchAddress("lheweight_muR0p5_muF0p5", &lheweight_muR0p5_muF0p5);
    arbre->SetBranchAddress("lheweight_muR2_muF2", &lheweight_muR2_muF2);
    arbre->SetBranchAddress("lheweight_nominal", &lheweight_nominal);

   bool is_ggh=(name.find("ggH") < 140);
   bool is_qqh=(name.find("qqH") < 140);
   int nbhist=1;
   if (sample=="data_obs") nbhist=1+26;
   else if (is_ggh) nbhist=1+60+18; 
   else if (is_qqh) nbhist=1+60+20;
   else if (sample=="embedded") nbhist=1+26+16;
   else nbhist=1+60+26;

   std::vector<TH2F*> h0tau_OS;
   std::vector<TH2F*> h1tau_OS;
   std::vector<TH2F*> h2tau_OS;
   std::vector<TH2F*> h0tau_SS;
   std::vector<TH2F*> h1tau_SS;
   std::vector<TH2F*> h2tau_SS;
   std::vector<TH2F*> h0tau_AI;
   std::vector<TH2F*> h1tau_AI;
   std::vector<TH2F*> h2tau_AI;
   std::vector<TH2F*> h3tau_OS;
   std::vector<TH2F*> h4tau_OS;
   std::vector<TH2F*> h5tau_OS;
   std::vector<TH2F*> h6tau_OS;
   std::vector<TH2F*> h7tau_OS;
   std::vector<TH2F*> h8tau_OS;
   std::vector<TH2F*> h3tau_SS;
   std::vector<TH2F*> h4tau_SS;
   std::vector<TH2F*> h5tau_SS;
   std::vector<TH2F*> h6tau_SS;
   std::vector<TH2F*> h7tau_SS;
   std::vector<TH2F*> h8tau_SS;
   std::vector<TH2F*> h3tau_AI;
   std::vector<TH2F*> h4tau_AI;
   std::vector<TH2F*> h5tau_AI;
   std::vector<TH2F*> h6tau_AI;
   std::vector<TH2F*> h7tau_AI;
   std::vector<TH2F*> h8tau_AI;

   std::vector<TH2F*> h0ell_OS;
   std::vector<TH2F*> h1ell_OS;
   std::vector<TH2F*> h2ell_OS;
   std::vector<TH2F*> h3ell_OS;
   std::vector<TH2F*> h4ell_OS;
   std::vector<TH2F*> h5ell_OS;
   std::vector<TH2F*> h6ell_OS;
   std::vector<TH2F*> h7ell_OS;
   std::vector<TH2F*> h8ell_OS;
   std::vector<TH2F*> h0ell_SS;
   std::vector<TH2F*> h1ell_SS;
   std::vector<TH2F*> h2ell_SS;
   std::vector<TH2F*> h3ell_SS;
   std::vector<TH2F*> h4ell_SS;
   std::vector<TH2F*> h5ell_SS;
   std::vector<TH2F*> h6ell_SS;
   std::vector<TH2F*> h7ell_SS;
   std::vector<TH2F*> h8ell_SS;
   std::vector<TH2F*> h0ell_AI;
   std::vector<TH2F*> h1ell_AI;
   std::vector<TH2F*> h2ell_AI;
   std::vector<TH2F*> h3ell_AI;
   std::vector<TH2F*> h4ell_AI;
   std::vector<TH2F*> h5ell_AI;
   std::vector<TH2F*> h6ell_AI;
   std::vector<TH2F*> h7ell_AI;
   std::vector<TH2F*> h8ell_AI;

   float bins_mtt0[] = {50,70,90,110,130,150,170,210,250,290};
   float bins_mtt1[] = {50,70,90,110,130,150,170,210,250,290};
   float bins_mtt2[] = {50,70,90,110,130,150,170,210,250,290};
   float bins_mtt3[] = {50,70,90,110,130,150,170,210,250,290};
   float bins_mtt4[] = {50,70,90,110,130,150,170,210,250,290};
   float bins_mtt5[] = {50,70,90,110,130,150,170,210,250,290};
   float bins_mtt6[] = {50,70,90,110,130,150,170,210,250,290};
   float bins_mtt7[] = {50,70,90,110,130,150,170,210,250,290};
   float bins_mtt8[] = {50,70,90,110,130,150,170,210,250,290};

   // differential
   /*float bins_mtt0[] = {50,70,90,110,130,150,170,210,250,290}; // 0 jet low
   float bins_mtt1[] = {50,70,90,110,130,150,170,210,250,290}; // 0 jet high
   float bins_mtt2[] = {50,70,90,110,130,150,170,210,250,290}; // 1 jet 
   float bins_mtt3[] = {50,70,90,110,130,150,170,210,250,290}; // 2 jets low
   float bins_mtt4[] = {50,70,90,110,130,150,170,210,250,290}; // 2 jets high
   float bins_mtt5[] = {50,70,90,110,130,150,170,210,250,290}; // 3 jets 
   float bins_mtt6[] = {50,70,90,110,130,150,170,210,250,290}; // 4 jets
   float bins_mtt7[] = {50,70,90,110,130,150,170,210,250,290}; // ge 2jets mjj
   float bins_mtt8[] = {50,70,90,110,130,150,170,210,250,290}; // rien*/

   // Top control 1
   /*float bins_mtt0[] = {15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150};
   float bins_mtt1[] = {15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150};
   float bins_mtt2[] = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175,180,185,190,195,200};
   float bins_mtt3[] = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175,180,185,190,195,200,205,210,215,220,225,230,235,240,245,250,255,260,265,270,275,280,285,290,295,300};
   float bins_mtt4[] = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175,180,185,190,195,200,205,210,215,220,225,230,235,240,245,250};
   float bins_mtt5[] = {50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,310,320,330,340,350,360,370,380,390,400};
   float bins_mtt6[] = {0,1,2,3,4,5};
   float bins_mtt7[] = {-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5};
   float bins_mtt8[] = {-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5};*/
   
   // control 1
   /*float bins_mtt0[] = {10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70};
   float bins_mtt1[] = {10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70};
   float bins_mtt2[] = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100};
   float bins_mtt3[] = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175,180,185,190,195,200,205,210,215,220,225,230,235,240,245,250};
   float bins_mtt4[] = {20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150};
   float bins_mtt5[] = {60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220};
   float bins_mtt6[] = {0,1,2,3,4,5};
   float bins_mtt7[] = {-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5};
   float bins_mtt8[] = {-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5};*/

   // control 2
   /*float bins_mtt0[] = {-100,-90,-80,-70,-60,-50,-40,-30,-20,-10,0,10,20,30,40,50,60,70,80,90,100};
   float bins_mtt1[] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,310,320,330,340,350,360,370,380,390,400,410,420,430,440,450,460,470,480,490,500};
   float bins_mtt2[] ={0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120};
   float bins_mtt3[] = {30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150};
   float bins_mtt4[] = {-4.7,-4.5,-4.3,-4.1,-3.9,-3.7,-3.5,-3.3,-3.1,-2.9,-2.7,-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5,2.7,2.9,3.1,3.3,3.5,3.7,3.9,4.1,4.3,4.5,4.7};
   float bins_mtt5[] = {30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120};
   float bins_mtt6[] = {-4.7,-4.5,-4.3,-4.1,-3.9,-3.7,-3.5,-3.3,-3.1,-2.9,-2.7,-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5,2.7,2.9,3.1,3.3,3.5,3.7,3.9,4.1,4.3,4.5,4.7};
   float bins_mtt7[] = {0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4,2.6,2.8,3.0,3.2,3.4,3.6,3.8,4.0,4.2,4.4,4.6,4.8,5.0,5.2,5.4,5.6,5.8,6.0,6.2,6.4,6.6,6.8,7.0};
   float bins_mtt8[] = {0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4,2.6,2.8,3.0,3.2,3.4,3.6,3.8,4.0,4.2,4.4,4.6,4.8,5.0};*/

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

   float bins_mjj[] = {350,700,1000,1500,10000};
   //float bins_mjj_low[] = {350,700,1000,1500,1800,10000};
   //float bins_mjj_high[] = {350,700,1200,10000};
   float bins_mjj_low[] = {350,700,1000,1500,10000};
   float bins_mjj_high[] = {350,700,1000,10000};
   float bins_pth[] = {0,60,120,200,250,10000};
   float bins_pth_1[] = {0,60,120,200,10000};
   float bins_pth_2[] = {0,60,120,200,10000};
   //float bins_pth_1[] = {0,60,120,200,250,10000};
   //float bins_pth_2[] = {0,60,120,200,250,10000};
   float bins_taupt[] = {0,1000};
   float bins_taupt_low[] = {0,1000};
   float bins_taupt_high[] = {0,1000};
   //float bins_taupt_low[] = {15,1000};
   //float bins_taupt_high[] = {15,1000};

   // differential
   /*float bins_mjj[] = {30,60,120,200,350,10000}; // 1 jet
   float bins_mjj_low[] = {0,150,300,450,600,1000,1400,1800,10000}; // >2jets mjj
   float bins_mjj_high[] = {0,45,80,120,200,350,600,10000}; // rien
   float bins_pth[] = {0,1,2,3,4,10}; // 0jet high
   float bins_pth_1[] = {0,45,80,120,200,350,10000}; // 3 jets
   float bins_pth_2[] = {0,45,80,120,200,350,10000}; // 4 jets
   float bins_taupt[] = {0,45,80,120,200,350,450,10000}; // 0 jet low
   float bins_taupt_low[] = {0,45,80,120,200,350,10000}; // 2 jets low
   float bins_taupt_high[] = {0,45,80,120,200,350,10000}; // 2 jets high*/

   /*float bins_mjj[] = {0,100000};
   float bins_mjj_low[] = {0,100000};
   float bins_mjj_high[] = {0,100000};
   float bins_pth[] = {0,100000};
   float bins_pth_1[] = {0,100000};
   float bins_pth_2[] = {0,100000};
   float bins_taupt[] = {0,100000};
   float bins_taupt_low[] = {0,100000};
   float bins_taupt_high[] = {0,100000};*/

   int  binnum_mjj = sizeof(bins_mjj)/sizeof(Float_t) - 1;
   int  binnum_mjj_low = sizeof(bins_mjj_low)/sizeof(Float_t) - 1;
   int  binnum_mjj_high = sizeof(bins_mjj_high)/sizeof(Float_t) - 1;
   int  binnum_pth = sizeof(bins_pth)/sizeof(Float_t) - 1;
   int  binnum_pth_1 = sizeof(bins_pth_1)/sizeof(Float_t) - 1;
   int  binnum_pth_2 = sizeof(bins_pth_2)/sizeof(Float_t) - 1;
   int  binnum_taupt = sizeof(bins_taupt)/sizeof(Float_t) - 1;
   int  binnum_taupt_low = sizeof(bins_taupt_low)/sizeof(Float_t) - 1;
   int  binnum_taupt_high = sizeof(bins_taupt_high)/sizeof(Float_t) - 1;

   for (int k=0; k<nbhist; ++k){
        ostringstream HNS0tauOS; HNS0tauOS << "h0tau_OS" << k;
        ostringstream HNS1tauOS; HNS1tauOS << "h1tau_OS" << k;
        ostringstream HNS2tauOS; HNS2tauOS << "h2tau_OS" << k;
        h0tau_OS.push_back(new TH2F (HNS0tauOS.str().c_str(),"InvMa",binnum_taupt,bins_taupt,binnum_mtt0,bins_mtt0)); h0tau_OS[k]->Sumw2();
        h1tau_OS.push_back(new TH2F (HNS1tauOS.str().c_str(),"InvMa",binnum_pth,bins_pth,binnum_mtt1,bins_mtt1)); h1tau_OS[k]->Sumw2();
        h2tau_OS.push_back(new TH2F (HNS2tauOS.str().c_str(),"InvMa",binnum_mjj,bins_mjj,binnum_mtt2,bins_mtt2)); h2tau_OS[k]->Sumw2();

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

        ostringstream HNS0tauSS; HNS0tauSS << "h0tau_SS" << k;
        ostringstream HNS1tauSS; HNS1tauSS << "h1tau_SS" << k;
        ostringstream HNS2tauSS; HNS2tauSS << "h2tau_SS" << k;
        h0tau_SS.push_back(new TH2F (HNS0tauSS.str().c_str(),"InvMa",binnum_taupt,bins_taupt,binnum_mtt0,bins_mtt0)); h0tau_SS[k]->Sumw2();
        h1tau_SS.push_back(new TH2F (HNS1tauSS.str().c_str(),"InvMa",binnum_pth,bins_pth,binnum_mtt1,bins_mtt1)); h1tau_SS[k]->Sumw2();
        h2tau_SS.push_back(new TH2F (HNS2tauSS.str().c_str(),"InvMa",binnum_mjj,bins_mjj,binnum_mtt2,bins_mtt2)); h2tau_SS[k]->Sumw2();

        ostringstream HNS0tauAI; HNS0tauAI << "h0tau_AI" << k;
        ostringstream HNS1tauAI; HNS1tauAI << "h1tau_AI" << k;
        ostringstream HNS2tauAI; HNS2tauAI << "h2tau_AI" << k;
        h0tau_AI.push_back(new TH2F (HNS0tauAI.str().c_str(),"InvMa",binnum_taupt,bins_taupt,binnum_mtt0,bins_mtt0)); h0tau_AI[k]->Sumw2();
        h1tau_AI.push_back(new TH2F (HNS1tauAI.str().c_str(),"InvMa",binnum_pth,bins_pth,binnum_mtt1,bins_mtt1)); h1tau_AI[k]->Sumw2();
        h2tau_AI.push_back(new TH2F (HNS2tauAI.str().c_str(),"InvMa",binnum_mjj,bins_mjj,binnum_mtt2,bins_mtt2)); h2tau_AI[k]->Sumw2();

        ostringstream HNS0ellSS; HNS0ellSS << "h0ell_SS" << k;
        ostringstream HNS1ellSS; HNS1ellSS << "h1ell_SS" << k;
        ostringstream HNS2ellSS; HNS2ellSS << "h2ell_SS" << k;
        h0ell_SS.push_back(new TH2F (HNS0ellSS.str().c_str(),"InvMa",binnum_taupt,bins_taupt,binnum_mtt0,bins_mtt0)); h0ell_SS[k]->Sumw2();
        h1ell_SS.push_back(new TH2F (HNS1ellSS.str().c_str(),"InvMa",binnum_pth,bins_pth,binnum_mtt1,bins_mtt1)); h1ell_SS[k]->Sumw2();
        h2ell_SS.push_back(new TH2F (HNS2ellSS.str().c_str(),"InvMa",binnum_mjj,bins_mjj,binnum_mtt2,bins_mtt2)); h2ell_SS[k]->Sumw2();

        ostringstream HNS0ellAI; HNS0ellAI << "h0ell_AI" << k;
        ostringstream HNS1ellAI; HNS1ellAI << "h1ell_AI" << k;
        ostringstream HNS2ellAI; HNS2ellAI << "h2ell_AI" << k;
        h0ell_AI.push_back(new TH2F (HNS0ellAI.str().c_str(),"InvMa",binnum_taupt,bins_taupt,binnum_mtt0,bins_mtt0)); h0ell_AI[k]->Sumw2();
        h1ell_AI.push_back(new TH2F (HNS1ellAI.str().c_str(),"InvMa",binnum_pth,bins_pth,binnum_mtt1,bins_mtt1)); h1ell_AI[k]->Sumw2();
        h2ell_AI.push_back(new TH2F (HNS2ellAI.str().c_str(),"InvMa",binnum_mjj,bins_mjj,binnum_mtt2,bins_mtt2)); h2ell_AI[k]->Sumw2();

        ostringstream HNS3tauSS; HNS3tauSS << "h3tau_SS" << k;
        ostringstream HNS4tauSS; HNS4tauSS << "h4tau_SS" << k;
        ostringstream HNS5tauSS; HNS5tauSS << "h5tau_SS" << k;
        ostringstream HNS6tauSS; HNS6tauSS << "h6tau_SS" << k;
        ostringstream HNS7tauSS; HNS7tauSS << "h7tau_SS" << k;
        ostringstream HNS8tauSS; HNS8tauSS << "h8tau_SS" << k;
        h3tau_SS.push_back(new TH2F (HNS3tauSS.str().c_str(),"InvMa",binnum_taupt_low,bins_taupt_low,binnum_mtt3,bins_mtt3)); h3tau_SS[k]->Sumw2();
        h4tau_SS.push_back(new TH2F (HNS4tauSS.str().c_str(),"InvMa",binnum_taupt_high,bins_taupt_high,binnum_mtt4,bins_mtt4)); h4tau_SS[k]->Sumw2();
        h5tau_SS.push_back(new TH2F (HNS5tauSS.str().c_str(),"InvMa",binnum_pth_1,bins_pth_1,binnum_mtt5,bins_mtt5)); h5tau_SS[k]->Sumw2();
        h6tau_SS.push_back(new TH2F (HNS6tauSS.str().c_str(),"InvMa",binnum_pth_2,bins_pth_2,binnum_mtt6,bins_mtt6)); h6tau_SS[k]->Sumw2();
        h7tau_SS.push_back(new TH2F (HNS7tauSS.str().c_str(),"InvMa",binnum_mjj_low,bins_mjj_low,binnum_mtt7,bins_mtt7)); h7tau_SS[k]->Sumw2();
        h8tau_SS.push_back(new TH2F (HNS8tauSS.str().c_str(),"InvMa",binnum_mjj_high,bins_mjj_high,binnum_mtt8,bins_mtt8)); h8tau_SS[k]->Sumw2();

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

        ostringstream HNS3ellSS; HNS3ellSS << "h3ell_SS" << k;
        ostringstream HNS4ellSS; HNS4ellSS << "h4ell_SS" << k;
        ostringstream HNS5ellSS; HNS5ellSS << "h5ell_SS" << k;
        ostringstream HNS6ellSS; HNS6ellSS << "h6ell_SS" << k;
        ostringstream HNS7ellSS; HNS7ellSS << "h7ell_SS" << k;
        ostringstream HNS8ellSS; HNS8ellSS << "h8ell_SS" << k;
        h3ell_SS.push_back(new TH2F (HNS3ellSS.str().c_str(),"InvMa",binnum_taupt_low,bins_taupt_low,binnum_mtt3,bins_mtt3)); h3ell_SS[k]->Sumw2();
        h4ell_SS.push_back(new TH2F (HNS4ellSS.str().c_str(),"InvMa",binnum_taupt_high,bins_taupt_high,binnum_mtt4,bins_mtt4)); h4ell_SS[k]->Sumw2();
        h5ell_SS.push_back(new TH2F (HNS5ellSS.str().c_str(),"InvMa",binnum_pth_1,bins_pth_1,binnum_mtt5,bins_mtt5)); h5ell_SS[k]->Sumw2();
        h6ell_SS.push_back(new TH2F (HNS6ellSS.str().c_str(),"InvMa",binnum_pth_2,bins_pth_2,binnum_mtt6,bins_mtt6)); h6ell_SS[k]->Sumw2();
        h7ell_SS.push_back(new TH2F (HNS7ellSS.str().c_str(),"InvMa",binnum_mjj_low,bins_mjj_low,binnum_mtt7,bins_mtt7)); h7ell_SS[k]->Sumw2();
        h8ell_SS.push_back(new TH2F (HNS8ellSS.str().c_str(),"InvMa",binnum_mjj_high,bins_mjj_high,binnum_mtt8,bins_mtt8)); h8ell_SS[k]->Sumw2();

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

   TH2F* h0_ttcontamination=new TH2F ("h0_ttcontamination","InvMa",binnum_taupt,bins_taupt,binnum_mtt0,bins_mtt0); h0_ttcontamination->Sumw2();
   TH2F* h1_ttcontamination=new TH2F ("h1_ttcontamination","InvMa",binnum_pth,bins_pth,binnum_mtt1,bins_mtt1); h1_ttcontamination->Sumw2();
   TH2F* h2_ttcontamination=new TH2F ("h2_ttcontamination","InvMa",binnum_mjj,bins_mjj,binnum_mtt2,bins_mtt2); h2_ttcontamination->Sumw2();
   TH2F* h3_ttcontamination=new TH2F ("h3_ttcontamination","InvMa",binnum_taupt_low,bins_taupt_low,binnum_mtt3,bins_mtt3); h3_ttcontamination->Sumw2();
   TH2F* h4_ttcontamination=new TH2F ("h4_ttcontamination","InvMa",binnum_taupt_high,bins_taupt_high,binnum_mtt4,bins_mtt4); h4_ttcontamination->Sumw2();
   TH2F* h5_ttcontamination=new TH2F ("h5_ttcontamination","InvMa",binnum_pth_1,bins_pth_1,binnum_mtt5,bins_mtt5); h5_ttcontamination->Sumw2();
   TH2F* h6_ttcontamination=new TH2F ("h6_ttcontamination","InvMa",binnum_pth_2,bins_pth_2,binnum_mtt6,bins_mtt6); h6_ttcontamination->Sumw2();
   TH2F* h7_ttcontamination=new TH2F ("h7_ttcontamination","InvMa",binnum_mjj_low,bins_mjj_low,binnum_mtt7,bins_mtt7); h7_ttcontamination->Sumw2();
   TH2F* h8_ttcontamination=new TH2F ("h8_ttcontamination","InvMa",binnum_mjj_high,bins_mjj_high,binnum_mtt8,bins_mtt8); h8_ttcontamination->Sumw2();

   reweight::LumiReWeighting* LumiWeights_12;
   LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2018.root", "pu_distributions_data_2018.root", "pileup", "pileup");

   TFile ffrac("fractions_em.root");
   TH1F* hfrac_0jetlow = (TH1F*) ffrac.Get("fraction_qcd_em_0jetlow");
   TH1F* hfrac_0jethigh = (TH1F*) ffrac.Get("fraction_qcd_em_0jethigh");
   TH1F* hfrac_boosted1 = (TH1F*) ffrac.Get("fraction_qcd_em_boosted1");
   TH1F* hfrac_boosted2 = (TH1F*) ffrac.Get("fraction_qcd_em_boosted2");
   TH1F* hfrac_vbflow = (TH1F*) ffrac.Get("fraction_qcd_em_vbflow");
   TH1F* hfrac_vbfhigh = (TH1F*) ffrac.Get("fraction_qcd_em_vbfhigh");

   TFile fwmc("htt_scalefactors_legacy_2018.root");
   RooWorkspace *wmc = (RooWorkspace*)fwmc.Get("w");
   fwmc.Close();


   TFile ftt("toppt_correction_to_2016.root");
   TF1 *fct_tt=(TF1*) ftt.Get("toppt_ratio_to_2016");

   TFile fclosure("qcdfiles_em/closure.root");
   TH2F *closure0=(TH2F*) fclosure.Get("closureOS0");
   TH2F *closure1=(TH2F*) fclosure.Get("closureOS1");
   TH2F *closure2=(TH2F*) fclosure.Get("closureOS2");
   TH2F *closureOS=(TH2F*) fclosure.Get("closureOS");
   TH2F *correction=(TH2F*) fclosure.Get("correction");

   TFile *fosss= new TFile("osss_em_2018.root","r");
   TF1 *osss_0jet=(TF1*) fosss->Get("OSSS_qcd_0jet_2018");
   TF1 *osss_0jet_par0=(TF1*) fosss->Get("OSSS_qcd_0jet_2018_par0");
   TF1 *osss_0jet_par1=(TF1*) fosss->Get("OSSS_qcd_0jet_2018_par1");
   /*TF1 *osss_0jet_unc1_up=(TF1*) fosss->Get("OSSS_qcd_0jet_2018_unc1_up");
   TF1 *osss_0jet_unc1_down=(TF1*) fosss->Get("OSSS_qcd_0jet_2018_unc1_down");
   TF1 *osss_0jet_unc2_up=(TF1*) fosss->Get("OSSS_qcd_0jet_2018_unc2_up");
   TF1 *osss_0jet_unc2_down=(TF1*) fosss->Get("OSSS_qcd_0jet_2018_unc2_down");*/
   TF1 *osss_1jet=(TF1*) fosss->Get("OSSS_qcd_1jet_2018");
   TF1 *osss_1jet_unc1_up=(TF1*) fosss->Get("OSSS_qcd_1jet_2018_unc1_up");
   TF1 *osss_1jet_unc1_down=(TF1*) fosss->Get("OSSS_qcd_1jet_2018_unc1_down");
   TF1 *osss_1jet_unc2_up=(TF1*) fosss->Get("OSSS_qcd_1jet_2018_unc2_up");
   TF1 *osss_1jet_unc2_down=(TF1*) fosss->Get("OSSS_qcd_1jet_2018_unc2_down");
   TF1 *osss_2jet=(TF1*) fosss->Get("OSSS_qcd_2jet_2018");
   TF1 *osss_2jet_unc1_up=(TF1*) fosss->Get("OSSS_qcd_2jet_2018_unc1_up");
   TF1 *osss_2jet_unc1_down=(TF1*) fosss->Get("OSSS_qcd_2jet_2018_unc1_down");
   TF1 *osss_2jet_unc2_up=(TF1*) fosss->Get("OSSS_qcd_2jet_2018_unc2_up");
   TF1 *osss_2jet_unc2_down=(TF1*) fosss->Get("OSSS_qcd_2jet_2018_unc2_down");

   TString postfixMC[61]={"","_CMS_scale_j_AbsoluteDown","_CMS_scale_j_AbsoluteUp","_CMS_scale_j_Absolute_2018Down","_CMS_scale_j_Absolute_2018Up","_CMS_scale_j_BBEC1Down","_CMS_scale_j_BBEC1Up","_CMS_scale_j_BBEC1_2018Down","_CMS_scale_j_BBEC1_2018Up","_CMS_scale_j_EC2Down","_CMS_scale_j_EC2Up","_CMS_scale_j_EC2_2018Down","_CMS_scale_j_EC2_2018Up","_CMS_scale_j_FlavorQCDDown","_CMS_scale_j_FlavorQCDUp","_CMS_scale_j_HFDown","_CMS_scale_j_HFUp","_CMS_scale_j_HF_2018Down","_CMS_scale_j_HF_2018Up","_CMS_scale_j_RelativeBalDown","_CMS_scale_j_RelativeBalUp","_CMS_scale_j_RelativeSample_2018Down","_CMS_scale_j_RelativeSample_2018Up","_CMS_res_j_2018Down","_CMS_res_j_2018Up","_CMS_scale_met_unclustered_2018Down","_CMS_scale_met_unclustered_2018Up","_CMS_htt_boson_reso_met_0jet_2018Down","_CMS_htt_boson_reso_met_0jet_2018Up","_CMS_htt_boson_scale_met_0jet_2018Down","_CMS_htt_boson_scale_met_0jet_2018Up","_CMS_htt_boson_reso_met_1jet_2018Down","_CMS_htt_boson_reso_met_1jet_2018Up","_CMS_htt_boson_scale_met_1jet_2018Down","_CMS_htt_boson_scale_met_1jet_2018Up","_CMS_htt_boson_reso_met_2jet_2018Down","_CMS_htt_boson_reso_met_2jet_2018Up","_CMS_htt_boson_scale_met_2jet_2018Down","_CMS_htt_boson_scale_met_2jet_2018Up","_CMS_htt_ttbarShapeDown","_CMS_htt_ttbarShapeUp","_CMS_htt_dyShapeDown","_CMS_htt_dyShapeUp","_CMS_scale_e_2018Down","_CMS_scale_e_2018Up","_CMS_scale_m_eta2p1to2p4_2018Down","_CMS_scale_m_eta2p1to2p4_2018Up","_CMS_scale_m_eta1p2to2p1_2018Down","_CMS_scale_m_eta1p2to2p1_2018Up","_CMS_scale_m_etalt1p2_2018Down","_CMS_scale_m_etalt1p2_2018Up","_CMS_prefiringDown","_CMS_prefiringUp","_CMS_mu8e23trg_2018Down","_CMS_mu8e23trg_2018Up","_CMS_mu23e12trg_2018Down","_CMS_mu23e12trg_2018Up","_CMS_bothmuetrg_2018Down","_CMS_bothmuetrg_2018Up","_FIXMEscaleDown","_FIXMEscaleUp"};

   TString postfixGGH[18]={"_THU_ggH_MuUp","_THU_ggH_MuDown","_THU_ggH_ResUp","_THU_ggH_ResDown","_THU_ggH_Mig01Up","_THU_ggH_Mig01Down","_THU_ggH_Mig12Up","_THU_ggH_Mig12Down","_THU_ggH_VBF2jUp","_THU_ggH_VBF2jDown","_THU_ggH_VBF3jUp","_THU_ggH_VBF3jDown","_THU_ggH_PT60Up","_THU_ggH_PT60Down","_THU_ggH_PT120Up","_THU_ggH_PT120Down","_THU_ggH_qmtopUp","_THU_ggH_qmtopDown"};

   TString postfixVBF[20]={"_THU_qqH_yieldUp","_THU_qqH_yieldDown","_THU_qqH_PTH200Up","_THU_qqH_PTH200Down","_THU_qqH_Mjj60Up","_THU_qqH_Mjj60Down","_THU_qqH_Mjj120Up","_THU_qqH_Mjj120Down","_THU_qqH_Mjj350Up","_THU_qqH_Mjj350Down","_THU_qqH_Mjj700Up","_THU_qqH_Mjj700Down","_THU_qqH_Mjj1000Up","_THU_qqH_Mjj1000Down","_THU_qqH_Mjj1500Up","_THU_qqH_Mjj1500Down","_THU_qqH_PTH25Up","_THU_qqH_PTH25Down","_THU_qqH_JET01Up","_THU_qqH_JET01Down"};

   TString postfixEmbedded[16]={"_CMS_scale_emb_e_barrel_2018Down","_CMS_scale_emb_e_barrel_2018Up","_CMS_scale_emb_e_endcap_2018Down","_CMS_scale_emb_e_endcap_2018Up","_CMS_scale_emb_m_eta2p1to2p4_2018Down","_CMS_scale_emb_m_eta2p1to2p4_2018Up","_CMS_scale_emb_m_eta1p2to2p1_2018Down","_CMS_scale_emb_m_eta1p2to2p1_2018Up","_CMS_scale_emb_m_etalt1p2_2018Down","_CMS_scale_emb_m_etalt1p2_2018Up","_CMS_mu8e23trg_emb_2018Down","_CMS_mu8e23trg_emb_2018Up","_CMS_mu23e12trg_emb_2018Down","_CMS_mu23e12trg_emb_2018Up","_CMS_bothmuetrg_emb_2018Down","_CMS_bothmuetrg_emb_2018Up"};

   TString postfixQCD[26]={"_CMS_QCD_njet0_intercept_2018Down","_CMS_QCD_njet0_intercept_2018Up","_CMS_QCD_njet0_slope_2018Down","_CMS_QCD_njet0_slope_2018Up","_CMS_QCD_njet1_intercept_2018Down","_CMS_QCD_njet1_intercept_2018Up","_CMS_QCD_njet1_slope_2018Down","_CMS_QCD_njet1_slope_2018Up","_CMS_QCD_njet2_intercept_2018Down","_CMS_QCD_njet2_intercept_2018Up","_CMS_QCD_njet2_slope_2018Down","_CMS_QCD_njet2_slope_2018Up","_CMS_QCD_antiiso_2018Down","_CMS_QCD_antiiso_2018Up","_CMS_QCD_stat_pte15to25_ptmu15to25_2018Down","_CMS_QCD_stat_pte15to25_ptmu15to25_2018Up","_CMS_QCD_stat_pte15to25_ptmugt25_2018Down","_CMS_QCD_stat_pte15to25_ptmugt25_2018Up","_CMS_QCD_stat_pte25to35_ptmu15to25_2018Down","_CMS_QCD_stat_pte25to35_ptmu15to25_2018Up","_CMS_QCD_stat_pte25to35_ptmugt25_2018Down","_CMS_QCD_stat_pte25to35_ptmugt25_2018Up","_CMS_QCD_stat_ptegt35_ptmu15to25_2018Down","_CMS_QCD_stat_ptegt35_ptmu15to25_2018Up","_CMS_QCD_stat_ptegt35_ptmugt25_2018Down","_CMS_QCD_stat_ptegt35_ptmugt25_2018Up"};

   TFile * f_NNLOPS = new TFile("NNLOPS_reweight.root");
   TGraph * g_NNLOPS_0jet = (TGraph*) f_NNLOPS-> Get("gr_NNLOPSratio_pt_powheg_0jet");
   TGraph * g_NNLOPS_1jet = (TGraph*) f_NNLOPS-> Get("gr_NNLOPSratio_pt_powheg_1jet");
   TGraph * g_NNLOPS_2jet = (TGraph*) f_NNLOPS-> Get("gr_NNLOPSratio_pt_powheg_2jet");
   TGraph * g_NNLOPS_3jet = (TGraph*) f_NNLOPS-> Get("gr_NNLOPSratio_pt_powheg_3jet");

   bool do_rivet=(name.find("ggH") < 140 or name.find("qqH") < 140 or name.find("VH") < 140 or name.find("WH") < 140 or name.find("ZH") < 140);

   bool norecoil=(name.find("WH") < 140 or name.find("ZH") < 140 or name=="TT" or name=="VV" or name=="ST");
   bool is_inclusivesignal=false;
   if (name=="ggH_htt125" or name=="qqH_htt125" or name=="WH_htt125" or name=="ZH_htt125" or name=="ggH_hww125" or name=="qqH_hww125" or name=="WH_hww125" or name=="ZH_hww125") is_inclusivesignal=true;

   float lheweight_nominalTo2_average=1.0;
   float lheweight_nominalTo0p5_average=1.0;

   TFile *f_QCDScaleAcceptance_GGHTT = new TFile("/afs/cern.ch/work/c/ccaillol/public/QCDScaleAcceptance/GGHTT2018.root");
   if (sample=="GGZHQQTT125") f_QCDScaleAcceptance_GGHTT = new TFile("/afs/cern.ch/work/c/ccaillol/public/QCDScaleAcceptance/GGZHQQTT2018.root");
   TH1F *h_QCDScaleAcceptance_ggH = (TH1F*) f_QCDScaleAcceptance_GGHTT->Get("demo/h_nevents_ggH");
   TH1F *h_QCDScaleAcceptance_ggH_scale_0jet = (TH1F*) f_QCDScaleAcceptance_GGHTT->Get("demo/h_nevents_ggH_scale_0jet");
   TH1F *h_QCDScaleAcceptance_ggH_scale_1jet_lowpt = (TH1F*) f_QCDScaleAcceptance_GGHTT->Get("demo/h_nevents_ggH_scale_1jet_lowpt");
   TH1F *h_QCDScaleAcceptance_ggH_scale_2jet_lowpt = (TH1F*) f_QCDScaleAcceptance_GGHTT->Get("demo/h_nevents_ggH_scale_2jet_lowpt");
   TH1F *h_QCDScaleAcceptance_ggH_scale_highpt = (TH1F*) f_QCDScaleAcceptance_GGHTT->Get("demo/h_nevents_ggH_scale_highpt");
   TH1F *h_QCDScaleAcceptance_ggH_scale_very_highpt = (TH1F*) f_QCDScaleAcceptance_GGHTT->Get("demo/h_nevents_ggH_scale_very_highpt");
   TH1F *h_QCDScaleAcceptance_ggH_scale_vbf = (TH1F*) f_QCDScaleAcceptance_GGHTT->Get("demo/h_nevents_ggH_scale_vbf");

   TFile *f_QCDScaleAcceptance_VBFHTT = new TFile("/afs/cern.ch/work/c/ccaillol/public/QCDScaleAcceptance/VBFHTT2018.root");
   TH1F *h_QCDScaleAcceptance_vbf = (TH1F*) f_QCDScaleAcceptance_VBFHTT->Get("demo/h_nevents_vbf");
   TH1F *h_QCDScaleAcceptance_vbf_scale_0jet = (TH1F*) f_QCDScaleAcceptance_VBFHTT->Get("demo/h_nevents_vbf_scale_0jet");
   TH1F *h_QCDScaleAcceptance_vbf_scale_1jet = (TH1F*) f_QCDScaleAcceptance_VBFHTT->Get("demo/h_nevents_vbf_scale_1jet");
   TH1F *h_QCDScaleAcceptance_vbf_scale_lowmjj = (TH1F*) f_QCDScaleAcceptance_VBFHTT->Get("demo/h_nevents_vbf_scale_lowmjj");
   TH1F *h_QCDScaleAcceptance_vbf_scale_highmjj_lowpt = (TH1F*) f_QCDScaleAcceptance_VBFHTT->Get("demo/h_nevents_vbf_scale_highmjj_lowpt");
   TH1F *h_QCDScaleAcceptance_vbf_scale_highmjj_highpt = (TH1F*) f_QCDScaleAcceptance_VBFHTT->Get("demo/h_nevents_vbf_scale_highmjj_highpt");

   TFile *f_QCDScaleAcceptance_VHTT = new TFile("/afs/cern.ch/work/c/ccaillol/public/QCDScaleAcceptance/WplusHTT2018.root");
   if (sample=="WminusH125") f_QCDScaleAcceptance_VHTT = new TFile("/afs/cern.ch/work/c/ccaillol/public/QCDScaleAcceptance/WminusHTT2018.root");
   if (sample=="ZH125") f_QCDScaleAcceptance_VHTT = new TFile("/afs/cern.ch/work/c/ccaillol/public/QCDScaleAcceptance/ZHTT2018.root");
   if (sample=="GGZHLLTT125") f_QCDScaleAcceptance_VHTT = new TFile("/afs/cern.ch/work/c/ccaillol/public/QCDScaleAcceptance/GGZHLLTT2018.root");
   if (sample=="GGZHNNTT125") f_QCDScaleAcceptance_VHTT = new TFile("/afs/cern.ch/work/c/ccaillol/public/QCDScaleAcceptance/GGZHNNTT2018.root");
   TH1F *h_QCDScaleAcceptance_VH = (TH1F*) f_QCDScaleAcceptance_VHTT->Get("demo/h_nevents_vbf");
   TH1F *h_QCDScaleAcceptance_VH_scale_0jet = (TH1F*) f_QCDScaleAcceptance_VHTT->Get("demo/h_nevents_vbf_scale_0jet");
   TH1F *h_QCDScaleAcceptance_VH_scale_1jet = (TH1F*) f_QCDScaleAcceptance_VHTT->Get("demo/h_nevents_vbf_scale_1jet");
   TH1F *h_QCDScaleAcceptance_VH_scale_lowmjj = (TH1F*) f_QCDScaleAcceptance_VHTT->Get("demo/h_nevents_vbf_scale_lowmjj");
   TH1F *h_QCDScaleAcceptance_VH_scale_highmjj_lowpt = (TH1F*) f_QCDScaleAcceptance_VHTT->Get("demo/h_nevents_vbf_scale_highmjj_lowpt");
   TH1F *h_QCDScaleAcceptance_VH_scale_highmjj_highpt = (TH1F*) f_QCDScaleAcceptance_VHTT->Get("demo/h_nevents_vbf_scale_highmjj_highpt");
   TH1F *h_QCDScaleAcceptance_WH_lep = (TH1F*) f_QCDScaleAcceptance_VHTT->Get("demo/h_nevents_WH_lep");
   TH1F *h_QCDScaleAcceptance_ZH_lep = (TH1F*) f_QCDScaleAcceptance_VHTT->Get("demo/h_nevents_ZH_lep");
   TH1F *h_QCDScaleAcceptance_WH_scale_lowpt = (TH1F*) f_QCDScaleAcceptance_VHTT->Get("demo/h_nevents_WH_scale_lowpt");
   TH1F *h_QCDScaleAcceptance_WH_scale_highpt = (TH1F*) f_QCDScaleAcceptance_VHTT->Get("demo/h_nevents_WH_scale_highpt");
   TH1F *h_QCDScaleAcceptance_ZH_scale_lowpt = (TH1F*) f_QCDScaleAcceptance_VHTT->Get("demo/h_nevents_ZH_scale_lowpt");
   TH1F *h_QCDScaleAcceptance_ZH_scale_highpt = (TH1F*) f_QCDScaleAcceptance_VHTT->Get("demo/h_nevents_ZH_scale_highpt");

   // GGH scale (for GGH and GGZHQQTT)
   if (name=="ggH_htt125" or name=="ggZH_had_htt125" or name=="ggH_hww125" or name=="ggZH_had_hww125") {lheweight_nominalTo2_average= h_QCDScaleAcceptance_ggH->GetBinContent(1)/h_QCDScaleAcceptance_ggH->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_ggH->GetBinContent(1)/h_QCDScaleAcceptance_ggH->GetBinContent(9); postfixMC[59]="_ggH_scaleDown"; postfixMC[60]="_ggH_scaleUp";}
   if (name.find("H_PTH_0_200_0J_PTH_0_10_h") < 140 or name.find("H_PTH_0_200_0J_PTH_10_200_h") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_ggH_scale_0jet->GetBinContent(1)/h_QCDScaleAcceptance_ggH_scale_0jet->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_ggH_scale_0jet->GetBinContent(1)/h_QCDScaleAcceptance_ggH_scale_0jet->GetBinContent(9); postfixMC[59]="_ggH_scale_0jetDown"; postfixMC[60]="_ggH_scale_0jetUp";}
   if (name.find("H_PTH_0_200_1J_PTH_0_60_h") < 140 or name.find("H_PTH_0_200_1J_PTH_60_120_h") < 140 or name.find("H_PTH_0_200_1J_PTH_120_200_h") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_ggH_scale_1jet_lowpt->GetBinContent(1)/h_QCDScaleAcceptance_ggH_scale_1jet_lowpt->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_ggH_scale_1jet_lowpt->GetBinContent(1)/h_QCDScaleAcceptance_ggH_scale_1jet_lowpt->GetBinContent(9); postfixMC[59]="_ggH_scale_1jet_lowptDown"; postfixMC[60]="_ggH_scale_1jet_lowptUp";}
   if (name.find("H_PTH_0_200_GE2J_MJJ_0_350_PTH_0_60_h") < 140 or name.find("H_PTH_0_200_GE2J_MJJ_0_350_PTH_60_120_h") < 140 or name.find("H_PTH_0_200_GE2J_MJJ_0_350_PTH_120_200_h") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_ggH_scale_2jet_lowpt->GetBinContent(1)/h_QCDScaleAcceptance_ggH_scale_2jet_lowpt->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_ggH_scale_2jet_lowpt->GetBinContent(1)/h_QCDScaleAcceptance_ggH_scale_2jet_lowpt->GetBinContent(9); postfixMC[59]="_ggH_scale_2jet_lowptDown"; postfixMC[60]="_ggH_scale_2jet_lowptUp";}
   if (name.find("H_PTH_200_300_h") < 140 or name.find("H_PTH_300_450_h") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_ggH_scale_highpt->GetBinContent(1)/h_QCDScaleAcceptance_ggH_scale_highpt->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_ggH_scale_highpt->GetBinContent(1)/h_QCDScaleAcceptance_ggH_scale_highpt->GetBinContent(9); postfixMC[59]="_ggH_scale_highptDown"; postfixMC[60]="_ggH_scale_highptUp";}
   if (name.find("H_PTH_450_650_h") < 140 or name.find("H_PTH_GE650_h") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_ggH_scale_very_highpt->GetBinContent(1)/h_QCDScaleAcceptance_ggH_scale_very_highpt->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_ggH_scale_very_highpt->GetBinContent(1)/h_QCDScaleAcceptance_ggH_scale_very_highpt->GetBinContent(9); postfixMC[59]="_ggH_scale_very_highptDown"; postfixMC[60]="_ggH_scale_very_highptUp";}
   if (name.find("H_PTH_0_200_GE2J_MJJ_350_700_PTHJJ_0_25_h") < 140 or name.find("H_PTH_0_200_GE2J_MJJ_350_700_PTHJJ_GE25_h") < 140 or name.find("H_PTH_0_200_GE2J_MJJ_GE700_PTHJJ_0_25_h") < 140 or name.find("H_PTH_0_200_GE2J_MJJ_GE700_PTHJJ_GE25_h") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_ggH_scale_vbf->GetBinContent(1)/h_QCDScaleAcceptance_ggH_scale_vbf->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_ggH_scale_vbf->GetBinContent(1)/h_QCDScaleAcceptance_ggH_scale_vbf->GetBinContent(9); postfixMC[59]="_ggH_scale_vbfDown"; postfixMC[60]="_ggH_scale_vbfUp";}

   // VBF scale
   if (name=="qqH_htt125" or name=="qqH_hww125") {lheweight_nominalTo2_average= h_QCDScaleAcceptance_vbf->GetBinContent(1)/h_QCDScaleAcceptance_vbf->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_vbf->GetBinContent(1)/h_QCDScaleAcceptance_vbf->GetBinContent(9); postfixMC[59]="_vbf_scaleDown"; postfixMC[60]="_vbf_scaleUp";}
   if (name.find("qqH_0J_h") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_vbf_scale_0jet->GetBinContent(1)/h_QCDScaleAcceptance_vbf_scale_0jet->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_vbf_scale_0jet->GetBinContent(1)/h_QCDScaleAcceptance_vbf_scale_0jet->GetBinContent(9); postfixMC[59]="_vbf_scale_0jetDown"; postfixMC[60]="_vbf_scale_0jetUp";}
   if (name.find("qqH_1J_h") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_vbf_scale_1jet->GetBinContent(1)/h_QCDScaleAcceptance_vbf_scale_1jet->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_vbf_scale_1jet->GetBinContent(1)/h_QCDScaleAcceptance_vbf_scale_1jet->GetBinContent(9); postfixMC[59]="_vbf_scale_1jetDown"; postfixMC[60]="_vbf_scale_1jetUp";}
   if (name.find("qqH_GE2J_MJJ_0_60_h") < 140 or name.find("qqH_GE2J_MJJ_60_120_h") < 140 or name.find("qqH_GE2J_MJJ_120_350_h") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_vbf_scale_lowmjj->GetBinContent(1)/h_QCDScaleAcceptance_vbf_scale_lowmjj->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_vbf_scale_lowmjj->GetBinContent(1)/h_QCDScaleAcceptance_vbf_scale_lowmjj->GetBinContent(9); postfixMC[59]="_vbf_scale_lowmjjDown"; postfixMC[60]="_vbf_scale_lowmjjUp";}
   if (name.find("qqH_GE2J_MJJ_GE350_PTH_0_200_MJJ_350_700_PTHJJ_0_25_h") < 140 or name.find("qqH_GE2J_MJJ_GE350_PTH_0_200_MJJ_350_700_PTHJJ_GE25_h") < 140 or name.find("qqH_GE2J_MJJ_GE350_PTH_0_200_MJJ_GE700_PTHJJ_0_25_h") < 140 or name.find("qqH_GE2J_MJJ_GE350_PTH_0_200_MJJ_GE700_PTHJJ_GE25_h") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_vbf_scale_highmjj_lowpt->GetBinContent(1)/h_QCDScaleAcceptance_vbf_scale_highmjj_lowpt->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_vbf_scale_highmjj_lowpt->GetBinContent(1)/h_QCDScaleAcceptance_vbf_scale_highmjj_lowpt->GetBinContent(9); postfixMC[59]="_vbf_scale_highmjj_lowptDown"; postfixMC[60]="_vbf_scale_highmjj_lowptUp";}
   if (name.find("qqH_GE2J_MJJ_GE350_PTH_GE200_h") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_vbf_scale_highmjj_highpt->GetBinContent(1)/h_QCDScaleAcceptance_vbf_scale_highmjj_highpt->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_vbf_scale_highmjj_highpt->GetBinContent(1)/h_QCDScaleAcceptance_vbf_scale_highmjj_highpt->GetBinContent(9); postfixMC[59]="_vbf_scale_highmjj_highptDown"; postfixMC[60]="_vbf_scale_highmjj_highptUp";}


   // VH had scale
   if (sample=="WminusH125" or sample=="WplusH125" or sample=="ZH125" or sample=="WminusHWW" or sample=="WplusHWW" or sample=="ZHWW"){
     if (name=="WH_had_htt125" or name=="ZH_had_htt125" or name=="WH_had_hww125" or name=="ZH_had_hww125") {lheweight_nominalTo2_average= h_QCDScaleAcceptance_vbf->GetBinContent(1)/h_QCDScaleAcceptance_vbf->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_vbf->GetBinContent(1)/h_QCDScaleAcceptance_vbf->GetBinContent(9); postfixMC[59]="_VH_scaleDown"; postfixMC[60]="_VH_scaleUp";}
     if (name.find("H_0J_h") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_VH_scale_0jet->GetBinContent(1)/h_QCDScaleAcceptance_VH_scale_0jet->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_VH_scale_0jet->GetBinContent(1)/h_QCDScaleAcceptance_VH_scale_0jet->GetBinContent(9); postfixMC[59]="_VH_scale_0jetDown"; postfixMC[60]="_VH_scale_0jetUp";}
     if (name.find("H_1J_h") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_VH_scale_1jet->GetBinContent(1)/h_QCDScaleAcceptance_VH_scale_1jet->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_VH_scale_1jet->GetBinContent(1)/h_QCDScaleAcceptance_VH_scale_1jet->GetBinContent(9); postfixMC[59]="_VH_scale_1jetDown"; postfixMC[60]="_VH_scale_1jetUp";}
     if (name.find("H_GE2J_MJJ_0_60_h") < 140 or name.find("H_GE2J_MJJ_60_120_h") < 140 or name.find("H_GE2J_MJJ_120_350_h") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_VH_scale_lowmjj->GetBinContent(1)/h_QCDScaleAcceptance_VH_scale_lowmjj->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_VH_scale_lowmjj->GetBinContent(1)/h_QCDScaleAcceptance_VH_scale_lowmjj->GetBinContent(9); postfixMC[59]="_VH_scale_lowmjjDown"; postfixMC[60]="_VH_scale_lowmjjUp";}
     if (name.find("H_GE2J_MJJ_GE350_PTH_0_200_MJJ_350_700_PTHJJ_0_25_h") < 140 or name.find("H_GE2J_MJJ_GE350_PTH_0_200_MJJ_350_700_PTHJJ_GE25_h") < 140 or name.find("H_GE2J_MJJ_GE350_PTH_0_200_MJJ_GE700_PTHJJ_0_25_h") < 140 or name.find("H_GE2J_MJJ_GE350_PTH_0_200_MJJ_GE700_PTHJJ_GE25_h") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_VH_scale_highmjj_lowpt->GetBinContent(1)/h_QCDScaleAcceptance_VH_scale_highmjj_lowpt->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_VH_scale_highmjj_lowpt->GetBinContent(1)/h_QCDScaleAcceptance_VH_scale_highmjj_lowpt->GetBinContent(9); postfixMC[59]="_VH_scale_highmjj_lowptDown"; postfixMC[60]="_VH_scale_highmjj_lowptUp";}
     if (name.find("H_GE2J_MJJ_GE350_PTH_GE200_h") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_VH_scale_highmjj_highpt->GetBinContent(1)/h_QCDScaleAcceptance_VH_scale_highmjj_highpt->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_VH_scale_highmjj_highpt->GetBinContent(1)/h_QCDScaleAcceptance_VH_scale_highmjj_highpt->GetBinContent(9); postfixMC[59]="_VH_scale_highmjj_highptDown"; postfixMC[60]="_VH_scale_highmjj_highptUp";}
   }

   // VH lep scale
   if (sample=="WminusH125" or sample=="WplusH125" or sample=="ZH125" or sample=="GGZHLLTT125" or sample=="GGZHNNTT125" or sample=="WminusHWW" or sample=="WplusHWW" or sample=="ZHWW" or sample=="GGZHWW"){
      if (name=="WH_lep_htt125" or name=="WH_lep_hww125") {lheweight_nominalTo2_average= h_QCDScaleAcceptance_WH_lep->GetBinContent(1)/h_QCDScaleAcceptance_WH_lep->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_WH_lep->GetBinContent(1)/h_QCDScaleAcceptance_WH_lep->GetBinContent(9); postfixMC[59]="_WHlep_scaleDown"; postfixMC[60]="_WHlep_scaleUp";}
      if (name=="ggZH_lep_htt125" or name=="ZH_lep_htt125" or name=="ggZH_lep_hww125" or name=="ZH_lep_hww125") {lheweight_nominalTo2_average= h_QCDScaleAcceptance_ZH_lep->GetBinContent(1)/h_QCDScaleAcceptance_ZH_lep->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_ZH_lep->GetBinContent(1)/h_QCDScaleAcceptance_ZH_lep->GetBinContent(9); postfixMC[59]="_ZHlep_scaleDown"; postfixMC[60]="_ZHlep_scaleUp";}
      if (name.find("WH_lep_PTV_0_75_h") < 140 or name.find("WH_lep_PTV_75_150_h") < 140 or name.find("WH_lep_PTV_150_250_0J_h") < 140 or name.find("WH_lep_PTV_150_250_GE1J_h") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_WH_scale_lowpt->GetBinContent(1)/h_QCDScaleAcceptance_WH_scale_lowpt->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_WH_scale_lowpt->GetBinContent(1)/h_QCDScaleAcceptance_WH_scale_lowpt->GetBinContent(9); postfixMC[59]="_WH_scale_lowptDown"; postfixMC[60]="_WH_scale_lowptUp";}
      if (name.find("WH_lep_PTV_GT250_h") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_WH_scale_highpt->GetBinContent(1)/h_QCDScaleAcceptance_WH_scale_highpt->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_WH_scale_highpt->GetBinContent(1)/h_QCDScaleAcceptance_WH_scale_highpt->GetBinContent(9); postfixMC[59]="_WH_scale_highptDown"; postfixMC[60]="_WH_scale_highptUp";}
      if (name.find("ZH_lep_PTV_0_75_h") < 140 or name.find("ZH_lep_PTV_75_150_h") < 140 or name.find("ZH_lep_PTV_150_250_0J_h") < 140 or name.find("ZH_lep_PTV_150_250_GE1J_h") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_ZH_scale_lowpt->GetBinContent(1)/h_QCDScaleAcceptance_ZH_scale_lowpt->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_ZH_scale_lowpt->GetBinContent(1)/h_QCDScaleAcceptance_ZH_scale_lowpt->GetBinContent(9); postfixMC[59]="_ZH_scale_lowptDown"; postfixMC[60]="_ZH_scale_lowptUp";}
      if (name.find("ZH_lep_PTV_GT250_h") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_ZH_scale_highpt->GetBinContent(1)/h_QCDScaleAcceptance_ZH_scale_highpt->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_ZH_scale_highpt->GetBinContent(1)/h_QCDScaleAcceptance_ZH_scale_highpt->GetBinContent(9); postfixMC[59]="_ZH_scale_highptDown"; postfixMC[60]="_ZH_scale_highptUp";}
   }

   cout<<postfixMC[59]<<" "<<postfixMC[60]<<endl;

   TH1F* h_msv=new TH1F("h_msv","h_msv",24,50,290);

   Int_t nentries_wtn = (Int_t) arbre->GetEntries();
   for (Int_t i = 0; i < nentries_wtn; i++) {
        arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

lheweight_nominal=1.0;//

	// Rivet splitting
	if (do_rivet && !do_differential){
           if (name.find("ggH_FWDH_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=100) continue;
           if (name.find("H_PTH_200_300_h") < 140 && (Rivet_stage1_1_cat_pTjet30GeV!=101 or (Rivet_higgsPt<200 or Rivet_higgsPt>300))) continue;
           if (name.find("H_PTH_300_450_h") < 140 && (Rivet_stage1_1_cat_pTjet30GeV!=101 or (Rivet_higgsPt<300 or Rivet_higgsPt>450))) continue;
           if (name.find("H_PTH_450_650_h") < 140 && (Rivet_stage1_1_cat_pTjet30GeV!=101 or (Rivet_higgsPt<450 or Rivet_higgsPt>650))) continue;
           if (name.find("H_PTH_GE650_h") < 140 && (Rivet_stage1_1_cat_pTjet30GeV!=101 or Rivet_higgsPt<650)) continue;
           if (name.find("H_PTH_0_200_0J_PTH_0_10_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=102) continue;
           if (name.find("H_PTH_0_200_0J_PTH_10_200_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=103) continue;
           if (name.find("H_PTH_0_200_1J_PTH_0_60_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=104) continue;
           if (name.find("H_PTH_0_200_1J_PTH_60_120_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=105) continue;
           if (name.find("H_PTH_0_200_1J_PTH_120_200_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=106) continue;
           if (name.find("H_PTH_0_200_GE2J_MJJ_0_350_PTH_0_60_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=107) continue;
           if (name.find("H_PTH_0_200_GE2J_MJJ_0_350_PTH_60_120_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=108) continue;
           if (name.find("H_PTH_0_200_GE2J_MJJ_0_350_PTH_120_200_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=109) continue;
           if (name.find("H_PTH_0_200_GE2J_MJJ_350_700_PTHJJ_0_25_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=110) continue;
           if (name.find("H_PTH_0_200_GE2J_MJJ_350_700_PTHJJ_GE25_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=111) continue;
           if (name.find("H_PTH_0_200_GE2J_MJJ_GE700_PTHJJ_0_25_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=112) continue;
           if (name.find("H_PTH_0_200_GE2J_MJJ_GE700_PTHJJ_GE25_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=113) continue;
           if (name.find("H_0J_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=201) continue;
           if (name.find("H_1J_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=202) continue;
           if (name.find("H_GE2J_MJJ_0_60_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=203) continue;
           if (name.find("H_GE2J_MJJ_60_120_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=204) continue;
           if (name.find("H_GE2J_MJJ_120_350_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=205) continue;
           if (name.find("H_GE2J_MJJ_GE350_PTH_0_200_MJJ_350_700_PTHJJ_0_25_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=207) continue;
           if (name.find("H_GE2J_MJJ_GE350_PTH_0_200_MJJ_350_700_PTHJJ_GE25_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=208) continue;
           if (name.find("H_GE2J_MJJ_GE350_PTH_0_200_MJJ_GE700_PTHJJ_0_25_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=209) continue;
           if (name.find("H_GE2J_MJJ_GE350_PTH_0_200_MJJ_GE700_PTHJJ_GE25_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=210) continue;
           if (name.find("H_GE2J_MJJ_GE350_PTH_GE200_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=206) continue;
           if (name.find("WH_lep_FWDH_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=300) continue;
           if (name.find("WH_lep_PTV_0_75_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=301) continue;
           if (name.find("WH_lep_PTV_75_150_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=302) continue;
           if (name.find("WH_lep_PTV_150_250_0J_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=303) continue;
           if (name.find("WH_lep_PTV_150_250_GE1J_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=304) continue;
           if (name.find("WH_lep_PTV_GT250_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=305) continue;
           if ((name=="ZH_lep_FWDH_htt125" or name=="ZH_lep_FWDH_hww125") && Rivet_stage1_1_cat_pTjet30GeV!=400) continue;
           if ((name=="ZH_lep_PTV_0_75_htt125" or name=="ZH_lep_PTV_0_75_hww125") && Rivet_stage1_1_cat_pTjet30GeV!=401) continue;
           if ((name=="ZH_lep_PTV_75_150_htt125" or name=="ZH_lep_PTV_75_150_hww125") && Rivet_stage1_1_cat_pTjet30GeV!=402) continue;
           if ((name=="ZH_lep_PTV_150_250_0J_htt125" or name=="ZH_lep_PTV_150_250_0J_hww125") && Rivet_stage1_1_cat_pTjet30GeV!=403) continue;
           if ((name=="ZH_lep_PTV_150_250_GE1J_htt125" or name=="ZH_lep_PTV_150_250_GE1J_hww125") && Rivet_stage1_1_cat_pTjet30GeV!=404) continue;
           if ((name=="ZH_lep_PTV_GT250_htt125" or name=="ZH_lep_PTV_GT250_hww125") && Rivet_stage1_1_cat_pTjet30GeV!=405) continue;
           if (name.find("ggZH_lep_FWDH_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=500) continue;
           if (name.find("ggZH_lep_PTV_0_75_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=501) continue;
           if (name.find("ggZH_lep_PTV_75_150_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=502) continue;
           if (name.find("ggZH_lep_PTV_150_250_0J_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=503) continue;
           if (name.find("ggZH_lep_PTV_150_250_GE1J_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=504) continue;
           if (name.find("ggZH_lep_PTV_GT250_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=505) continue;
           if (name.find("ttH_FWDH_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=600) continue;
           if (name.find("ttH_stage1p1_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=601) continue;
           if (name.find("bbH_FWDH_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=700) continue;
           if (name.find("bbH_stage1p1_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=701) continue;
           if (name.find("tH_FWDH_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=800) continue;
           if (name.find("tH_stage1p1_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV!=801) continue;
           if ((name=="ZH_lep_htt125" or name=="ZH_lep_hww125") && Rivet_stage1_1_cat_pTjet30GeV<400) continue;
           if ((name=="ZH_had_htt125" or name=="ZH_had_hww125") && Rivet_stage1_1_cat_pTjet30GeV>=400) continue;
           if (name.find("WH_lep_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV<300) continue;
           if (name.find("WH_had_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV>=300) continue;
           if (name.find("ggZH_lep_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV<500) continue;
           if (name.find("ggZH_had_h") < 140 && Rivet_stage1_1_cat_pTjet30GeV>=500) continue;
	}

        TLorentzVector Rivet_jet2;
        TLorentzVector Rivet_jet1;
        float Rivet_mjj=-1;
        if (do_rivet && do_differential && Rivet_nJets30>1){
           Rivet_jet1.SetPtEtaPhiM(Rivet_j1pt,Rivet_j1eta,Rivet_j1phi,Rivet_j1m);
           Rivet_jet2.SetPtEtaPhiM(Rivet_j2pt,Rivet_j2eta,Rivet_j2phi,Rivet_j2m);
           Rivet_mjj=(Rivet_jet1+Rivet_jet2).M();
        }

        if (do_rivet && do_differential && !is_inclusivesignal){

           bool is_fiducial=(fabs(gentau1_eta)<2.5 and fabs(gentau2_eta)<2.5 and gentau1_pt>25 and gentau2_pt>25);
           if (name.find("hww") < 140) is_fiducial=false;
           if (name.find("nonfid") < 140 && is_fiducial) continue;
           if (name.find("nonfid") > 140 && !is_fiducial) continue;

           if (name.find("H_PTH_0_20") < 140 && !(Rivet_higgsPt>=0 && Rivet_higgsPt<20)) continue;
           if (name.find("H_PTH_20_45") < 140 && !(Rivet_higgsPt>=20 && Rivet_higgsPt<45)) continue;
           if (name.find("H_PTH_0_45") < 140 && !(Rivet_higgsPt>=0 && Rivet_higgsPt<45)) continue;
           if (name.find("H_PTH_45_80") < 140 && !(Rivet_higgsPt>=45 && Rivet_higgsPt<80)) continue;
           if (name.find("H_PTH_80_120") < 140 && !(Rivet_higgsPt>=80 && Rivet_higgsPt<120)) continue;
           if (name.find("H_PTH_120_200") < 140 && !(Rivet_higgsPt>=120 && Rivet_higgsPt<200)) continue;
           if (name.find("H_PTH_200_350") < 140 && !(Rivet_higgsPt>=200 && Rivet_higgsPt<350)) continue;
           if (name.find("H_PTH_350_600") < 140 && !(Rivet_higgsPt>=350 && Rivet_higgsPt<600)) continue;
           if (name.find("H_PTH_350_450") < 140 && !(Rivet_higgsPt>=350 && Rivet_higgsPt<450)) continue;
           if (name.find("H_PTH_GE600") < 140 && !(Rivet_higgsPt>=600)) continue;
           if (name.find("H_PTH_GT450") < 140 && !(Rivet_higgsPt>=450)) continue;

           if (name.find("H_NJETS_0") < 140 && !(Rivet_nJets30==0)) continue;
           if (name.find("H_NJETS_1") < 140 && !(Rivet_nJets30==1)) continue;
           if (name.find("H_NJETS_2") < 140 && !(Rivet_nJets30==2)) continue;
           if (name.find("H_NJETS_3") < 140 && !(Rivet_nJets30==3)) continue;
           if (name.find("H_NJETS_GE4") < 140 && !(Rivet_nJets30>=4)) continue;

           if (name.find("H_LJPT_30_60") < 140 && !(Rivet_j1pt>=30 && Rivet_j1pt<60)) continue;
           if (name.find("H_LJPT_60_120") < 140 && !(Rivet_j1pt>=60 && Rivet_j1pt<120)) continue;
           if (name.find("H_LJPT_120_200") < 140 && !(Rivet_j1pt>=120 && Rivet_j1pt<200)) continue;
           if (name.find("H_LJPT_200_350") < 140 && !(Rivet_j1pt>=200 && Rivet_j1pt<350)) continue;
           if (name.find("H_LJPT_GT350") < 140 && !(Rivet_j1pt>=350)) continue;

           if (name.find("H_MJJ_0_150") < 140 && !(Rivet_mjj>=0 && Rivet_mjj<150)) continue;
           if (name.find("H_MJJ_150_300") < 140 && !(Rivet_mjj>=150 && Rivet_mjj<300)) continue;
           if (name.find("H_MJJ_300_450") < 140 && !(Rivet_mjj>=300 && Rivet_mjj<450)) continue;
           if (name.find("H_MJJ_450_600") < 140 && !(Rivet_mjj>=450 && Rivet_mjj<600)) continue;
           if (name.find("H_MJJ_600_1000") < 140 && !(Rivet_mjj>=600 && Rivet_mjj<1000)) continue;
           if (name.find("H_MJJ_1000_1400") < 140 && !(Rivet_mjj>=1000 && Rivet_mjj<1400)) continue;
           if (name.find("H_MJJ_1400_1800") < 140 && !(Rivet_mjj>=1400 && Rivet_mjj<1800)) continue;
           if (name.find("H_MJJ_GE1800") < 140 && !(Rivet_mjj>=1800 && Rivet_mjj<10000000)) continue;
        }

	if (fabs(eta_1)>2.1) continue; //FIXME
        if (fabs(eta_2)>2.4) continue;

        if (Flag_goodVertices) continue;
        if (Flag_globalSuperTightHalo2016Filter) continue;
        if (Flag_HBHENoiseFilter) continue;
        if (Flag_HBHENoiseIsoFilter) continue;
        if (Flag_EcalDeadCellTriggerPrimitiveFilter) continue;
        if (Flag_BadPFMuonFilter) continue;
        if ((sample=="data_obs" or sample=="embedded") && Flag_eeBadScFilter) continue;
	if (Flag_ecalBadCalibReducedMINIAODFilter) continue;

        bool triggerMu8E23=(passMu8E23 && matchMu8E23_1 && filterMu8E23_1 && matchMu8E23_2 && filterMu8E23_2 && pt_1>23 && pt_2>9);
        bool triggerMu23E12=(passMu23E12 && matchMu23E12_1 && filterMu23E12_1 && matchMu23E12_2 && filterMu23E12_2 && pt_1>12 && pt_2>23);

        if (!triggerMu8E23 && !triggerMu23E12) continue;

        if (!do_topcontrol && nbtag>0) continue;
        if (!do_topcontrol && nbtagL>1) continue;
        if (do_topcontrol && nbtag==0) continue;

        bool signalRegion=(iso_1<0.15 && iso_2<0.15);
        //bool antiisoRegion=(iso_1<0.30 && iso_2<0.50);

        float antiisoRegion=(iso_1<0.30 && iso_2>0.10 && iso_2<0.30);
        float antiisoRegionVBF=(iso_1<0.50 && iso_2>0.20 && iso_2<0.50);
	if (!signalRegion && !antiisoRegion && !antiisoRegionVBF) continue;

	TLorentzVector mymu; 
	mymu.SetPtEtaPhiM(pt_2,eta_2,phi_2,m_2);
        TLorentzVector myele;
        myele.SetPtEtaPhiM(pt_1,eta_1,phi_1,m_1);
        TLorentzVector mymet;
        mymet.SetPtEtaPhiM(met,0,metphi,0);


           /*float norm_zeta=norm_F(myele.Px()/myele.Pt()+mymu.Px()/mymu.Pt(),myele.Py()/myele.Pt()+mymu.Py()/mymu.Pt());
           float x_zeta= (myele.Px()/myele.Pt()+mymu.Px()/mymu.Pt())/norm_zeta;
           float y_zeta= (myele.Py()/myele.Pt()+mymu.Py()/mymu.Pt())/norm_zeta;
           float p_zeta_mis=mymet.Px()*x_zeta+mymet.Py()*y_zeta;
           float pzeta_vis=(myele.Px()+mymu.Px())*x_zeta+(myele.Py()+mymu.Py())*y_zeta;
           float dzeta=p_zeta_mis-0.85*pzeta_vis;
	if (dzeta>-30) continue;*/

	if (mymu.DeltaR(myele)<0.3) continue;

        if (sample=="W"){
           weight=51.7495;
           if (numGenJets==1) weight=9.0816;
           else if (numGenJets==2) weight=4.5108;
           else if (numGenJets==3) weight=3.07747;
           else if (numGenJets==4) weight=3.2113;
        }
        if (sample=="DY" or sample=="Z"){
          weight=3.6234;
          if (numGenJets==1) weight=0.62980;
          else if (numGenJets==2) weight=0.55213;
          else if (numGenJets==3) weight=0.5995;
          else if (numGenJets==4) weight=0.82114;
        }

        bool is_includedInEmbedded=false;
        if ((name.find("htt")>100 && sample!="data_obs" && sample!="embedded") && ((gen_match_1==3 && gen_match_2==4) or (gen_match_1==4 && gen_match_2==3))) is_includedInEmbedded=true;
	if (sample!="embedded" && sample!="data_obs" && (gen_match_1==6 or gen_match_2==6)) continue;//FIXME

	float aweight=genweight*weight*LumiWeights_12->weight(npu);
        if (sample=="embedded") aweight=genweight;

	//NNLOPS weights
        if (name.find("ggH")<100){
            if (Rivet_nJets30==0) aweight = aweight * g_NNLOPS_0jet->Eval(min(Rivet_higgsPt,float(125.0)));
            if (Rivet_nJets30==1) aweight = aweight * g_NNLOPS_1jet->Eval(min(Rivet_higgsPt,float(625.0)));
            if (Rivet_nJets30==2) aweight = aweight * g_NNLOPS_2jet->Eval(min(Rivet_higgsPt,float(800.0)));
            if (Rivet_nJets30>=3) aweight = aweight * g_NNLOPS_3jet->Eval(min(Rivet_higgsPt,float(925.0)));
        }
	NumV WG1unc = qcd_ggF_uncert_2017(Rivet_nJets30, Rivet_higgsPt, Rivet_stage1_cat_pTjet30GeV);

	if (sample=="data_obs") aweight=1.0;

	// Top pT reweighting
        float topfactor=1.0;
        if (name=="TT" or sample=="TTToHadronic" or sample=="TTToSemiLeptonic" or sample=="TTToHadronic"){
           float pttop1=pt_top1;
           if (pttop1>472) pttop1=472;
           float pttop2=pt_top2;
           if (pttop2>472) pttop2=472;
           topfactor=sqrt(exp(0.088-0.00087*pttop1+0.00000092*pttop1*pttop1)*exp(0.088-0.00087*pttop2+0.00000092*pttop2*pttop2));
           aweight*=topfactor;
        }

        float zptweight=1.0;
	if (sample!="embedded" && sample!="data_obs"){
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
          aweight=aweight*wmc->function("m_trk_ratio")->getVal();
          aweight=aweight*wmc->function("e_trk_ratio")->getVal();
          aweight=aweight*wmc->function("e_idiso_ic_ratio")->getVal();
          aweight=aweight*wmc->function("m_idiso_ic_ratio")->getVal();

          float probData =wmc->function("m_trg_8_ic_data")->getVal()*wmc->function("e_trg_23_ic_data")->getVal()*int(triggerMu8E23)+wmc->function("m_trg_23_ic_data")->getVal()*wmc->function("e_trg_12_ic_data")->getVal()*int(triggerMu23E12)-wmc->function("e_trg_23_ic_data")->getVal()*wmc->function("m_trg_23_ic_data")->getVal()*int(triggerMu8E23 && triggerMu23E12);
          float probMC =wmc->function("m_trg_8_ic_mc")->getVal()*wmc->function("e_trg_23_ic_mc")->getVal()*int(triggerMu8E23)+wmc->function("m_trg_23_ic_mc")->getVal()*wmc->function("e_trg_12_ic_mc")->getVal()*int(triggerMu23E12)-wmc->function("e_trg_23_ic_mc")->getVal()*wmc->function("m_trg_23_ic_mc")->getVal()*int(triggerMu8E23 && triggerMu23E12);
          float sf_trg=probData/probMC;
          if (probMC==0) sf_trg=1;
          aweight=aweight*sf_trg;
          aweight=aweight*bweight;
	}

        if (sample=="embedded"){
          wmc->var("e_pt")->setVal(myele.Pt());
          wmc->var("e_eta")->setVal(myele.Eta());
          wmc->var("e_iso")->setVal(iso_1);
          wmc->var("m_pt")->setVal(mymu.Pt());
          wmc->var("m_eta")->setVal(mymu.Eta());
          wmc->var("m_iso")->setVal(iso_2);
          wmc->var("gt1_pt")->setVal(genpt_1);
          wmc->var("gt2_pt")->setVal(genpt_2);
          wmc->var("gt1_eta")->setVal(geneta_1);
          wmc->var("gt2_eta")->setVal(geneta_2);
          aweight=aweight*wmc->function("m_sel_trg_ic_ratio")->getVal();
          wmc->var("gt_pt")->setVal(genpt_1);
          wmc->var("gt_eta")->setVal(geneta_1);
          aweight=aweight*wmc->function("m_sel_id_ic_ratio")->getVal();
          wmc->var("gt_pt")->setVal(genpt_2);
          wmc->var("gt_eta")->setVal(geneta_2);
          aweight=aweight*wmc->function("m_sel_id_ic_ratio")->getVal();

          aweight=aweight*wmc->function("e_idiso_ic_embed_ratio")->getVal();
          aweight=aweight*wmc->function("m_idiso_ic_embed_ratio")->getVal();
          aweight=aweight*wmc->function("m_trk_ratio")->getVal();
          aweight=aweight*wmc->function("e_trk_embed_ratio")->getVal();

          //float probData =wmc->function("m_trg_8_ic_data")->getVal()*wmc->function("e_trg_23_ic_data")->getVal()*int(triggerMu8E23)+wmc->function("m_trg_23_ic_data")->getVal()*wmc->function("e_trg_12_ic_data")->getVal()*int(triggerMu23E12)-wmc->function("e_trg_23_ic_data")->getVal()*wmc->function("m_trg_23_ic_data")->getVal()*int(triggerMu8E23 && triggerMu23E12);
          //float probEmbedded =wmc->function("m_trg_8_ic_embed")->getVal()*wmc->function("e_trg_23_ic_embed")->getVal()*int(triggerMu8E23)+wmc->function("m_trg_23_ic_embed")->getVal()*wmc->function("e_trg_12_ic_embed")->getVal()*int(triggerMu23E12)-wmc->function("e_trg_23_ic_embed")->getVal()*wmc->function("m_trg_23_ic_embed")->getVal()*int(triggerMu8E23 && triggerMu23E12);

          float probData =wmc->function("e_trg_23_ic_data")->getVal()*int(triggerMu8E23)+wmc->function("m_trg_23_ic_data")->getVal()*wmc->function("e_trg_12_ic_data")->getVal()*int(triggerMu23E12)-wmc->function("e_trg_23_ic_data")->getVal()*wmc->function("m_trg_23_ic_data")->getVal()*int(triggerMu8E23 && triggerMu23E12);
	  float probEmbedded =wmc->function("e_trg_23_ic_embed")->getVal()*int(triggerMu8E23)+wmc->function("m_trg_23_ic_embed")->getVal()*wmc->function("e_trg_12_ic_embed")->getVal()*int(triggerMu23E12)-wmc->function("e_trg_23_ic_embed")->getVal()*wmc->function("m_trg_23_ic_embed")->getVal()*int(triggerMu8E23 && triggerMu23E12);

          float sf_trg=probData/probEmbedded;
          if (probEmbedded==0) sf_trg=1;
          aweight=aweight*sf_trg;

        }

	bool is_tau=(!is_includedInEmbedded && (sample=="data_obs" or sample=="embedded" or ((gen_match_1==3 or gen_match_1==4) and (gen_match_2==3 or gen_match_2==4))));
	bool is_ell=(!is_includedInEmbedded && !is_tau);

        if (!norecoil){ m_sv_JetAbsoluteUp=m_sv; m_sv_JetAbsoluteyearUp=m_sv; m_sv_JetBBEC1Up=m_sv; m_sv_JetBBEC1yearUp=m_sv; m_sv_JetEC2Up=m_sv; m_sv_JetEC2yearUp=m_sv; m_sv_JetFlavorQCDUp=m_sv; m_sv_JetHFUp=m_sv; m_sv_JetHFyearUp=m_sv; m_sv_JetRelativeBalUp=m_sv; m_sv_JetRelativeSampleUp=m_sv; m_sv_JERUp=m_sv; m_sv_JetAbsoluteDown=m_sv; m_sv_JetAbsoluteyearDown=m_sv; m_sv_JetBBEC1Down=m_sv; m_sv_JetBBEC1yearDown=m_sv; m_sv_JetEC2Down=m_sv; m_sv_JetEC2yearDown=m_sv; m_sv_JetFlavorQCDDown=m_sv; m_sv_JetHFDown=m_sv; m_sv_JetHFyearDown=m_sv; m_sv_JetRelativeBalDown=m_sv; m_sv_JetRelativeSampleDown=m_sv; m_sv_JERDown=m_sv;}


	//************************* Fill histograms **********************
	float myvar=(mymu+myele).M();
	TLorentzVector myrawele=myele;
        TLorentzVector myrawmu=mymu;
        TLorentzVector myrawmet=mymet;
        float massJets=mjj;
        int numberJets=njets;
	int rawnbtag=nbtag;
	float mtt=m_sv;
	for (int k=0; k<nbhist; ++k){

	   float weight2=1.0;

	   nbtag=rawnbtag;
           //if (nbtag>0) continue; //FIXME
           //if (nbtagL>1) continue;

           if (!do_topcontrol && nbtag>0) continue;
           if (!do_topcontrol && nbtagL>1) continue;
           if (do_topcontrol && nbtag==0) continue;

	   // reset all variables before any systematic shift
	   massJets=mjj;
	   mtt=m_sv;
	   numberJets=njets;
	   myele=myrawele;
           mymu=myrawmu;
	   mymet=myrawmet;
	   massJets=mjj;

           if (sample!="data_obs" && sample!="embedded"){
              if (k>0 && k<25){ // JES x 24
                if (k==1){numberJets=njets_JetAbsoluteDown; massJets=mjj_JetAbsoluteDown; mymet.SetPtEtaPhiM(met_JetAbsoluteDown,0,metphi_JetAbsoluteDown,0); mtt=m_sv_JetAbsoluteDown;}
                else if (k==2){numberJets=njets_JetAbsoluteUp; massJets=mjj_JetAbsoluteUp; mymet.SetPtEtaPhiM(met_JetAbsoluteUp,0,metphi_JetAbsoluteUp,0); mtt=m_sv_JetAbsoluteUp;}
                else if (k==3){numberJets=njets_JetAbsoluteyearDown; massJets=mjj_JetAbsoluteyearDown; mymet.SetPtEtaPhiM(met_JetAbsoluteyearDown,0,metphi_JetAbsoluteyearDown,0); mtt=m_sv_JetAbsoluteyearDown;}
                else if (k==4){numberJets=njets_JetAbsoluteyearUp; massJets=mjj_JetAbsoluteyearUp; mymet.SetPtEtaPhiM(met_JetAbsoluteyearUp,0,metphi_JetAbsoluteyearUp,0); mtt=m_sv_JetAbsoluteyearUp;}
                else if (k==5){numberJets=njets_JetBBEC1Down; massJets=mjj_JetBBEC1Down; mymet.SetPtEtaPhiM(met_JetBBEC1Down,0,metphi_JetBBEC1Down,0); mtt=m_sv_JetBBEC1Down;}
                else if (k==6){numberJets=njets_JetBBEC1Up; massJets=mjj_JetBBEC1Up; mymet.SetPtEtaPhiM(met_JetBBEC1Up,0,metphi_JetBBEC1Up,0); mtt=m_sv_JetBBEC1Up;}
                else if (k==7){numberJets=njets_JetBBEC1yearDown; massJets=mjj_JetBBEC1yearDown; mymet.SetPtEtaPhiM(met_JetBBEC1yearDown,0,metphi_JetBBEC1yearDown,0); mtt=m_sv_JetBBEC1yearDown;}
                else if (k==8){numberJets=njets_JetBBEC1yearUp; massJets=mjj_JetBBEC1yearUp; mymet.SetPtEtaPhiM(met_JetBBEC1yearUp,0,metphi_JetBBEC1yearUp,0); mtt=m_sv_JetBBEC1yearUp;}
                else if (k==9){numberJets=njets_JetEC2Down; massJets=mjj_JetEC2Down; mymet.SetPtEtaPhiM(met_JetEC2Down,0,metphi_JetEC2Down,0); mtt=m_sv_JetEC2Down;}
                else if (k==10){numberJets=njets_JetEC2Up; massJets=mjj_JetEC2Up; mymet.SetPtEtaPhiM(met_JetEC2Up,0,metphi_JetEC2Up,0); mtt=m_sv_JetEC2Up;}
                else if (k==11){numberJets=njets_JetEC2yearDown; massJets=mjj_JetEC2yearDown; mymet.SetPtEtaPhiM(met_JetEC2yearDown,0,metphi_JetEC2yearDown,0); mtt=m_sv_JetEC2yearDown;}
                else if (k==12){numberJets=njets_JetEC2yearUp; massJets=mjj_JetEC2yearUp; mymet.SetPtEtaPhiM(met_JetEC2yearUp,0,metphi_JetEC2yearUp,0); mtt=m_sv_JetEC2yearUp;}
                else if (k==13){numberJets=njets_JetFlavorQCDDown; massJets=mjj_JetFlavorQCDDown; mymet.SetPtEtaPhiM(met_JetFlavorQCDDown,0,metphi_JetFlavorQCDDown,0); mtt=m_sv_JetFlavorQCDDown;}
                else if (k==14){numberJets=njets_JetFlavorQCDUp; massJets=mjj_JetFlavorQCDUp; mymet.SetPtEtaPhiM(met_JetFlavorQCDUp,0,metphi_JetFlavorQCDUp,0); mtt=m_sv_JetFlavorQCDUp;}
                else if (k==15){numberJets=njets_JetHFDown; massJets=mjj_JetHFDown; mymet.SetPtEtaPhiM(met_JetHFDown,0,metphi_JetHFDown,0); mtt=m_sv_JetHFDown;}
                else if (k==16){numberJets=njets_JetHFUp; massJets=mjj_JetHFUp; mymet.SetPtEtaPhiM(met_JetHFUp,0,metphi_JetHFUp,0); mtt=m_sv_JetHFUp;}
                else if (k==17){numberJets=njets_JetHFyearDown; massJets=mjj_JetHFyearDown; mymet.SetPtEtaPhiM(met_JetHFyearDown,0,metphi_JetHFyearDown,0); mtt=m_sv_JetHFyearDown;}
                else if (k==18){numberJets=njets_JetHFyearUp; massJets=mjj_JetHFyearUp; mymet.SetPtEtaPhiM(met_JetHFyearUp,0,metphi_JetHFyearUp,0); mtt=m_sv_JetHFyearUp;}
                else if (k==19){numberJets=njets_JetRelativeBalDown; massJets=mjj_JetRelativeBalDown; mymet.SetPtEtaPhiM(met_JetRelativeBalDown,0,metphi_JetRelativeBalDown,0); mtt=m_sv_JetRelativeBalDown;}
                else if (k==20){numberJets=njets_JetRelativeBalUp; massJets=mjj_JetRelativeBalUp; mymet.SetPtEtaPhiM(met_JetRelativeBalUp,0,metphi_JetRelativeBalUp,0); mtt=m_sv_JetRelativeBalUp;}
                else if (k==21){numberJets=njets_JetRelativeSampleDown; massJets=mjj_JetRelativeSampleDown; mymet.SetPtEtaPhiM(met_JetRelativeSampleDown,0,metphi_JetRelativeSampleDown,0); mtt=m_sv_JetRelativeSampleDown;}
                else if (k==22){numberJets=njets_JetRelativeSampleUp; massJets=mjj_JetRelativeSampleUp; mymet.SetPtEtaPhiM(met_JetRelativeSampleUp,0,metphi_JetRelativeSampleUp,0); mtt=m_sv_JetRelativeSampleUp;}
                else if (k==23){numberJets=njets_JERDown; massJets=mjj_JERDown; mymet.SetPtEtaPhiM(met_JERDown,0,metphi_JERDown,0); mtt=m_sv_JERDown;}
                else if (k==24){numberJets=njets_JERUp; massJets=mjj_JERUp; mymet.SetPtEtaPhiM(met_JERUp,0,metphi_JERUp,0); mtt=m_sv_JERUp;}
              }

              else if ((name=="TT" or name=="VV" or name=="ST") && k>24 && k<27){ // UES x 2
                if (k==25){mymet.SetPtEtaPhiM(met_UESDown, 0, metphi_UESDown, 0); mtt=m_sv_UESDown;}
                else if (k==26){mymet.SetPtEtaPhiM(met_UESUp, 0, metphi_UESUp, 0); mtt=m_sv_UESUp;}
	      }

              else if (!(name=="TT" or name=="VV" or name=="ST") && k>26 && k<39){ // recoil x 4
                if (njets==0 and k==27){mymet.SetPtEtaPhiM(met_resolutionDown, 0, metphi_resolutionDown, 0); mtt=m_sv_ResolutionDown;}
                else if (njets==0 and k==28){mymet.SetPtEtaPhiM(met_resolutionUp, 0, metphi_resolutionUp, 0); mtt=m_sv_ResolutionUp;}
                else if (njets==0 and k==29){mymet.SetPtEtaPhiM(met_responseDown, 0, metphi_responseDown, 0); mtt=m_sv_ResponseDown;}
                else if (njets==0 and k==30){mymet.SetPtEtaPhiM(met_responseUp, 0, metphi_responseUp, 0); mtt=m_sv_ResponseUp;}
                else if (njets==1 and k==31){mymet.SetPtEtaPhiM(met_resolutionDown, 0, metphi_resolutionDown, 0); mtt=m_sv_ResolutionDown;}
                else if (njets==1 and k==32){mymet.SetPtEtaPhiM(met_resolutionUp, 0, metphi_resolutionUp, 0); mtt=m_sv_ResolutionUp;}
                else if (njets==1 and k==33){mymet.SetPtEtaPhiM(met_responseDown, 0, metphi_responseDown, 0); mtt=m_sv_ResponseDown;}
                else if (njets==1 and k==34){mymet.SetPtEtaPhiM(met_responseUp, 0, metphi_responseUp, 0); mtt=m_sv_ResponseUp;}
                else if (njets>1 and k==35){mymet.SetPtEtaPhiM(met_resolutionDown, 0, metphi_resolutionDown, 0); mtt=m_sv_ResolutionDown;}
                else if (njets>1 and k==36){mymet.SetPtEtaPhiM(met_resolutionUp, 0, metphi_resolutionUp, 0); mtt=m_sv_ResolutionUp;}
                else if (njets>1 and k==37){mymet.SetPtEtaPhiM(met_responseDown, 0, metphi_responseDown, 0); mtt=m_sv_ResponseDown;}
                else if (njets>1 and k==38){mymet.SetPtEtaPhiM(met_responseUp, 0, metphi_responseUp, 0); mtt=m_sv_ResponseUp;}
              }

              else if (k>38 && k<41 && (name=="TT" or sample=="TTToHadronic" or sample=="TTTo2L2Nu" or sample=="TTToSemiLeptonic")){ //Top pt reweighting x 2
                if (k==39) weight2=1.0/topfactor;
                else if (k==40) weight2=topfactor;
              }

              else if (k>40 && k<43 && (sample=="DY" or sample=="Z")){ //DY pt reweighting x 2
                if (k==41) weight2=(zptweight-0.10*(zptweight-1))/zptweight;
                else if (k==42) weight2=(zptweight+0.10*(zptweight-1))/zptweight;
              }

              if (k>42 && k<45){ // EES x 2
                if (k==43){myele*=(pt_1_ScaleDown/myele.Pt()); mymet=myrawmet; mymet=mymet-myele+myrawele; mtt=m_sv_elescaleESDown;}
                else if (k==44){myele*=(pt_1_ScaleUp/myele.Pt()); mymet=myrawmet; mymet=mymet-myele+myrawele; mtt=m_sv_elescaleESUp;}
              }

              if (k>44 && k<51){ // MES x 6 
                if (k==45 && fabs(mymu.Eta())<2.4 && fabs(mymu.Eta())>=2.1){mymu*=0.973; mymet=myrawmet; mymet=mymet+(0.027/0.973)*mymu; mtt=m_sv_muonESDown;}
                else if (k==46 && fabs(mymu.Eta())<2.4 && fabs(mymu.Eta())>=2.1){mymu*=1.027; mymet=myrawmet; mymet=mymet-(0.027/1.027)*mymu; mtt=m_sv_muonESUp;}
		else if (k==47 && fabs(mymu.Eta())<2.1 && fabs(mymu.Eta())>=1.2){mymu*=0.991; mymet=myrawmet; mymet=mymet+(0.009/0.991)*mymu; mtt=m_sv_muonESDown;}
                else if (k==48 && fabs(mymu.Eta())<2.1 && fabs(mymu.Eta())>=1.2){mymu*=1.009; mymet=myrawmet; mymet=mymet-(0.009/1.009)*mymu; mtt=m_sv_muonESUp;}
                else if (k==49 && fabs(mymu.Eta())<1.2){mymu*=0.996; mymet=myrawmet; mymet=mymet+(0.004/0.996)*mymu; mtt=m_sv_muonESDown;}
                else if (k==50 && fabs(mymu.Eta())<1.2){mymu*=1.004; mymet=myrawmet; mymet=mymet-(0.004/1.004)*mymu; mtt=m_sv_muonESUp;}
              }
              else if (k>50 && k<53){
                if (k==51) {weight2=1.0;}
                else if (k==52) {weight2=1.0;}
   	      }
              else if (k>52 && k<59){
                if (k==53 && mymu.Pt()<=24 && myele.Pt()>24) {weight2=0.96;}
                else if (k==54 && mymu.Pt()<=24 && myele.Pt()>24) {weight2=1.04;}
                else if (k==55 && mymu.Pt()>24 && myele.Pt()<=24) {weight2=0.96;}
                else if (k==56 && mymu.Pt()>24 && myele.Pt()<=24) {weight2=1.04;}
                else if (k==57 && mymu.Pt()>24 && myele.Pt()>24) {weight2=0.96;}
                else if (k==58 && mymu.Pt()>24 && myele.Pt()>24) {weight2=1.04;}
              }
              else if (k>58 && k<61){ // muR muF scale x 2
                if (k==59) weight2=lheweight_nominalTo0p5_average*(lheweight_muR0p5_muF0p5/lheweight_nominal);
                else if (k==60) weight2=lheweight_nominalTo2_average*(lheweight_muR2_muF2/lheweight_nominal);
              }
              else if (is_ggh && k>60 && k<79){ // WG1 x 18
                if (k==61) weight2=1+WG1unc[0];
                else if (k==62) weight2=1-WG1unc[0];
                else if (k==63) weight2=1+WG1unc[1];
                else if (k==64) weight2=1-WG1unc[1];
                else if (k==65) weight2=1+WG1unc[2];
                else if (k==66) weight2=1-WG1unc[2];
                else if (k==67) weight2=1+WG1unc[3];
                else if (k==68) weight2=1-WG1unc[3];
                else if (k==69) weight2=1+WG1unc[4];
                else if (k==70) weight2=1-WG1unc[4];
                else if (k==71) weight2=1+WG1unc[5];
                else if (k==72) weight2=1-WG1unc[5];
                else if (k==73) weight2=1+WG1unc[6];
                else if (k==74) weight2=1-WG1unc[6];
                else if (k==75) weight2=1+WG1unc[7];
                else if (k==76) weight2=1-WG1unc[7];
                else if (k==77) weight2=1+WG1unc[8];
                else if (k==78) weight2=1-WG1unc[8];
              }
              else if (is_qqh && k>60 && k<81){ // WG1 x 20
                if (k==61) weight2=vbf_uncert_stage_1_1(0, int(Rivet_stage1_1_fine_cat_pTjet30GeV), 1.0);
                else if (k==62) weight2=vbf_uncert_stage_1_1(0, int(Rivet_stage1_1_fine_cat_pTjet30GeV), -1.0);
                else if (k==63) weight2=vbf_uncert_stage_1_1(1, int(Rivet_stage1_1_fine_cat_pTjet30GeV), 1.0);
                else if (k==64) weight2=vbf_uncert_stage_1_1(1, int(Rivet_stage1_1_fine_cat_pTjet30GeV), -1.0);
                else if (k==65) weight2=vbf_uncert_stage_1_1(2, int(Rivet_stage1_1_fine_cat_pTjet30GeV), 1.0);
                else if (k==66) weight2=vbf_uncert_stage_1_1(2, int(Rivet_stage1_1_fine_cat_pTjet30GeV), -1.0);
                else if (k==67) weight2=vbf_uncert_stage_1_1(3, int(Rivet_stage1_1_fine_cat_pTjet30GeV), 1.0);
                else if (k==68) weight2=vbf_uncert_stage_1_1(3, int(Rivet_stage1_1_fine_cat_pTjet30GeV), -1.0);
                else if (k==69) weight2=vbf_uncert_stage_1_1(4, int(Rivet_stage1_1_fine_cat_pTjet30GeV), 1.0);
                else if (k==70) weight2=vbf_uncert_stage_1_1(4, int(Rivet_stage1_1_fine_cat_pTjet30GeV), -1.0);
                else if (k==71) weight2=vbf_uncert_stage_1_1(5, int(Rivet_stage1_1_fine_cat_pTjet30GeV), 1.0);
                else if (k==72) weight2=vbf_uncert_stage_1_1(5, int(Rivet_stage1_1_fine_cat_pTjet30GeV), -1.0);
                else if (k==73) weight2=vbf_uncert_stage_1_1(6, int(Rivet_stage1_1_fine_cat_pTjet30GeV), 1.0);
                else if (k==74) weight2=vbf_uncert_stage_1_1(6, int(Rivet_stage1_1_fine_cat_pTjet30GeV), -1.0);
                else if (k==75) weight2=vbf_uncert_stage_1_1(7, int(Rivet_stage1_1_fine_cat_pTjet30GeV), 1.0);
                else if (k==76) weight2=vbf_uncert_stage_1_1(7, int(Rivet_stage1_1_fine_cat_pTjet30GeV), -1.0);
                else if (k==77) weight2=vbf_uncert_stage_1_1(8, int(Rivet_stage1_1_fine_cat_pTjet30GeV), 1.0);
                else if (k==78) weight2=vbf_uncert_stage_1_1(8, int(Rivet_stage1_1_fine_cat_pTjet30GeV), -1.0);
                else if (k==79) weight2=vbf_uncert_stage_1_1(9, int(Rivet_stage1_1_fine_cat_pTjet30GeV), 1.0);
                else if (k==80) weight2=vbf_uncert_stage_1_1(9, int(Rivet_stage1_1_fine_cat_pTjet30GeV), -1.0);
              }

           }

           if (sample=="embedded" && k>26 && k<43){
              if (k>26 && k<31){ // EES x 2 
                if (k==27 && fabs(myele.Eta())<1.479) {myele*=0.9950; mymet=mymet+(0.0050/0.9950)*myele; mtt=m_sv_elescaleESDown;}
                else if (k==28 && fabs(myele.Eta())<1.479) {myele*=1.0050; mymet=mymet-(0.0050/1.0050)*myele; mtt=m_sv_elescaleESUp;}
                else if (k==29 && fabs(myele.Eta())>=1.479) {myele*=0.9875; mymet=mymet+(0.0125/0.9875)*myele; mtt=m_sv_elescaleESDown;}
                else if (k==30 && fabs(myele.Eta())>=1.479) {myele*=1.0125; mymet=mymet-(0.0125/1.0125)*myele; mtt=m_sv_elescaleESUp;}
              }
              if (k>30 && k<37){ // MES x 6 
                if (k==31 && fabs(mymu.Eta())<2.4 && fabs(mymu.Eta())>=2.1){mymu*=0.973; mymet=mymet+(0.027/0.973)*mymu; mtt=m_sv_muonESDown;}
                else if (k==32 && fabs(mymu.Eta())<2.4 && fabs(mymu.Eta())>=2.1){mymu*=1.027; mymet=mymet-(0.027/1.027)*mymu; mtt=m_sv_muonESUp;}
                else if (k==33 && fabs(mymu.Eta())<2.1 && fabs(mymu.Eta())>=1.2){mymu*=0.991; mymet=mymet+(0.009/0.991)*mymu; mtt=m_sv_muonESDown;}
                else if (k==34 && fabs(mymu.Eta())<2.1 && fabs(mymu.Eta())>=1.2){mymu*=1.009; mymet=mymet-(0.009/1.009)*mymu; mtt=m_sv_muonESUp;}
                else if (k==35 && fabs(mymu.Eta())<1.2){mymu*=0.996; mymet=mymet+(0.004/0.996)*mymu; mtt=m_sv_muonESDown;}
                else if (k==36 && fabs(mymu.Eta())<1.2){mymu*=1.004; mymet=mymet-(0.004/1.004)*mymu; mtt=m_sv_muonESUp;}
              }
              if (k>36 && k<43){ //trg 
                if (k==37 && mymu.Pt()<=24 && myele.Pt()>24) {weight2=0.96;}
                else if (k==38 && mymu.Pt()<=24 && myele.Pt()>24) {weight2=1.04;}
                else if (k==39 && mymu.Pt()>24 && myele.Pt()<=24) {weight2=0.96;}
                else if (k==40 && mymu.Pt()>24 && myele.Pt()<=24) {weight2=1.04;}
                else if (k==41 && mymu.Pt()>24 && myele.Pt()>24) {weight2=0.96;}
                else if (k==42 && mymu.Pt()>24 && myele.Pt()>24) {weight2=1.04;}
              }

           }

           triggerMu8E23=(passMu8E23 && matchMu8E23_1 && filterMu8E23_1 && matchMu8E23_2 && filterMu8E23_2 && pt_1>24 && pt_2>10);
           triggerMu23E12=(passMu23E12 && matchMu23E12_1 && filterMu23E12_1 && matchMu23E12_2 && filterMu23E12_2 && pt_1>13 && pt_2>24);
           if (!triggerMu8E23 && !triggerMu23E12) continue;

	   if (mymu.Pt()<24 and myele.Pt()<24) continue;
	   if (mymu.Pt()<15) continue;
	   if (myele.Pt()<15) continue;

           float norm_zeta=norm_F(myele.Px()/myele.Pt()+mymu.Px()/mymu.Pt(),myele.Py()/myele.Pt()+mymu.Py()/mymu.Pt());
           float x_zeta= (myele.Px()/myele.Pt()+mymu.Px()/mymu.Pt())/norm_zeta;
           float y_zeta= (myele.Py()/myele.Pt()+mymu.Py()/mymu.Pt())/norm_zeta;
           float p_zeta_mis=mymet.Px()*x_zeta+mymet.Py()*y_zeta;
           float pzeta_vis=(myele.Px()+mymu.Px())*x_zeta+(myele.Py()+mymu.Py())*y_zeta;
	   float dzeta=p_zeta_mis-0.85*pzeta_vis;
	   bool pass_dzeta=dzeta>-30;//FIXME

           float mt=TMass_F((myele+mymu).Pt(),mymet.Pt(),(myele+mymu).Px(),mymet.Px(),(myele+mymu).Py(),mymet.Py());
	   float pass_mt=(mt<60);
           if (do_topcontrol) pass_mt=true;
           if (do_topcontrol && dzeta>-40) continue;
           if (do_topcontrol) pass_dzeta=true;


	   myvar=mtt;
	   //if (numberJets==0) myvar=(mymu+myele).M();
	   float myvar0=myele.Pt();
	   float myvar1=(mymu+myele+mymet).Pt();
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


           if (do_differential){
              myvar0=1.05*(myele+mymu+mymet).Pt();
              myvar1=numberJets;
              myvar2=jpt_1;
              myvar3=(myele+mymu+mymet).Pt();
              myvar4=(myele+mymu+mymet).Pt();
              myvar5=(myele+mymu+mymet).Pt();
              myvar6=(myele+mymu+mymet).Pt();
              myvar7=massJets;
              myvar8=(myele+mymu+mymet).Pt();
           }

           if (do_control_plots>0){
                myvar0=1;myvar1=1;myvar2=1;myvar3=1;myvar4=1;myvar5=1;myvar6=1;myvar7=1;myvar8=1;
           }
	   if (do_control_plots==1){
	      mass0=mymu.Pt();
              mass1=myele.Pt();
	      mass2=mymet.Pt();
              mass3=(myele+mymu+mymet).Pt();
              mass4=(myele+mymu).M();
              mass5=m_sv;
              mass6=njets;
              mass7=myele.Eta();
              mass8=mymu.Eta();
	   }
           if (do_control_plots==2){
              mass0=dzeta;
              if (numberJets<2) mass1=-1;
              else mass1=mjj;
              mass2=mt;
              if (numberJets<1) mass3=-1;
              else mass3=jpt_1;
              if (numberJets<1) mass4=-10;
              else mass4=jeta_1;
              if (numberJets<2) mass5=-1;
              else mass5=jpt_2;
              if (numberJets<2) mass6=-10;
              else mass6=jeta_2;
	      if (numberJets<2) mass7=-100;
              else mass7=fabs(jeta_1-jeta_2);
              mass8=myele.DeltaR(mymu);
           }

           float ssweight=2.5;
           if (numberJets==0) ssweight=osss_0jet->Eval(myele.DeltaR(mymu));
           else if (numberJets==1) ssweight=osss_1jet->Eval(myele.DeltaR(mymu));
           else ssweight=osss_2jet->Eval(myele.DeltaR(mymu));

           float sscorr=1.0;
	   float mupt=mymu.Pt();
	   float ept=myele.Pt();
	   if (mupt>100) mupt=99;
           if (ept>100) ept=99;
	   sscorr=correction->GetBinContent(correction->GetXaxis()->FindBin(mupt),correction->GetYaxis()->FindBin(ept));

           if (!is_qqh && sample!="embedded" && !is_ggh && sample!="data_obs" && k>60 && k<87){ // QCD x 14
                /*if (k==59 && numberJets==0) ssweight=osss_0jet_unc1_down->Eval(myele.DeltaR(mymu));
                else if (k==60 && numberJets==0) ssweight=osss_0jet_unc1_up->Eval(myele.DeltaR(mymu));
                else if (k==61 && numberJets==0) ssweight=osss_0jet_unc2_down->Eval(myele.DeltaR(mymu));
                else if (k==62 && numberJets==0) ssweight=osss_0jet_unc2_up->Eval(myele.DeltaR(mymu));*/
		if (k==61 && numberJets==0) ssweight=osss_0jet_par0->Eval(myele.DeltaR(mymu));
                else if (k==62 && numberJets==0) ssweight=osss_0jet->Eval(myele.DeltaR(mymu))-(osss_0jet_par0->Eval(myele.DeltaR(mymu))-osss_0jet->Eval(myele.DeltaR(mymu)));
                else if (k==63 && numberJets==0) ssweight=osss_0jet_par1->Eval(myele.DeltaR(mymu));
                else if (k==64 && numberJets==0) ssweight=osss_0jet->Eval(myele.DeltaR(mymu))-(osss_0jet_par1->Eval(myele.DeltaR(mymu))-osss_0jet->Eval(myele.DeltaR(mymu)));
                else if (k==65 && numberJets==1) ssweight=osss_1jet_unc1_down->Eval(myele.DeltaR(mymu));
                else if (k==66 && numberJets==1) ssweight=osss_1jet_unc1_up->Eval(myele.DeltaR(mymu));
                else if (k==67 && numberJets==1) ssweight=osss_1jet_unc2_down->Eval(myele.DeltaR(mymu));
                else if (k==68 && numberJets==1) ssweight=osss_1jet_unc2_up->Eval(myele.DeltaR(mymu));
                else if (k==69 && numberJets>1) ssweight=osss_2jet_unc1_down->Eval(myele.DeltaR(mymu));
                else if (k==70 && numberJets>1) ssweight=osss_2jet_unc1_up->Eval(myele.DeltaR(mymu));
                else if (k==71 && numberJets>1) ssweight=osss_2jet_unc2_down->Eval(myele.DeltaR(mymu));
                else if (k==72 && numberJets>1) ssweight=osss_2jet_unc2_up->Eval(myele.DeltaR(mymu));
                else if (k==73) sscorr=1.0;
                else if (k==74) sscorr=(1+2*(correction->GetBinContent(correction->GetXaxis()->FindBin(mupt),correction->GetYaxis()->FindBin(ept))-1));
                else if (k==75 and myele.Pt()>=15 and myele.Pt()<25 and mymu.Pt()>=15 and mymu.Pt()<25) weight2=1-sqrt(pow(closureOS->GetBinError(closureOS->GetXaxis()->FindBin(20.0),closureOS->GetYaxis()->FindBin(20.0))/closureOS->GetBinContent(closureOS->GetXaxis()->FindBin(20.0),closureOS->GetYaxis()->FindBin(20.0)),2)+pow(correction->GetBinError(correction->GetXaxis()->FindBin(20.0),correction->GetYaxis()->FindBin(20.0))/correction->GetBinContent(correction->GetXaxis()->FindBin(20.0),correction->GetYaxis()->FindBin(20.0)),2));
                else if (k==76 and myele.Pt()>=15 and myele.Pt()<25 and mymu.Pt()>=15 and mymu.Pt()<25) weight2=1+sqrt(pow(closureOS->GetBinError(closureOS->GetXaxis()->FindBin(20.0),closureOS->GetYaxis()->FindBin(20.0))/closureOS->GetBinContent(closureOS->GetXaxis()->FindBin(20.0),closureOS->GetYaxis()->FindBin(20.0)),2)+pow(correction->GetBinError(correction->GetXaxis()->FindBin(20.0),correction->GetYaxis()->FindBin(20.0))/correction->GetBinContent(correction->GetXaxis()->FindBin(20.0),correction->GetYaxis()->FindBin(20.0)),2));
                else if (k==77 and myele.Pt()>=15 and myele.Pt()<25 and mymu.Pt()>=25) weight2=1-sqrt(pow(closureOS->GetBinError(closureOS->GetXaxis()->FindBin(50.0),closureOS->GetYaxis()->FindBin(20.0))/closureOS->GetBinContent(closureOS->GetXaxis()->FindBin(50.0),closureOS->GetYaxis()->FindBin(20.0)),2)+pow(correction->GetBinError(correction->GetXaxis()->FindBin(50.0),correction->GetYaxis()->FindBin(20.0))/correction->GetBinContent(correction->GetXaxis()->FindBin(50.0),correction->GetYaxis()->FindBin(20.0)),2));
                else if (k==78 and myele.Pt()>=15 and myele.Pt()<25 and mymu.Pt()>=25) weight2=1+sqrt(pow(closureOS->GetBinError(closureOS->GetXaxis()->FindBin(50.0),closureOS->GetYaxis()->FindBin(20.0))/closureOS->GetBinContent(closureOS->GetXaxis()->FindBin(50.0),closureOS->GetYaxis()->FindBin(20.0)),2)+pow(correction->GetBinError(correction->GetXaxis()->FindBin(50.0),correction->GetYaxis()->FindBin(20.0))/correction->GetBinContent(correction->GetXaxis()->FindBin(50.0),correction->GetYaxis()->FindBin(20.0)),2));
                else if (k==79 and myele.Pt()>=25 and myele.Pt()<35 and mymu.Pt()>=15 and mymu.Pt()<25) weight2=1-sqrt(pow(closureOS->GetBinError(closureOS->GetXaxis()->FindBin(20.0),closureOS->GetYaxis()->FindBin(30.0))/closureOS->GetBinContent(closureOS->GetXaxis()->FindBin(20.0),closureOS->GetYaxis()->FindBin(30.0)),2)+pow(correction->GetBinError(correction->GetXaxis()->FindBin(20.0),correction->GetYaxis()->FindBin(30.0))/correction->GetBinContent(correction->GetXaxis()->FindBin(20.0),correction->GetYaxis()->FindBin(30.0)),2));
                else if (k==80 and myele.Pt()>=25 and myele.Pt()<35 and mymu.Pt()>=15 and mymu.Pt()<25) weight2=1+sqrt(pow(closureOS->GetBinError(closureOS->GetXaxis()->FindBin(20.0),closureOS->GetYaxis()->FindBin(30.0))/closureOS->GetBinContent(closureOS->GetXaxis()->FindBin(20.0),closureOS->GetYaxis()->FindBin(30.0)),2)+pow(correction->GetBinError(correction->GetXaxis()->FindBin(20.0),correction->GetYaxis()->FindBin(30.0))/correction->GetBinContent(correction->GetXaxis()->FindBin(20.0),correction->GetYaxis()->FindBin(30.0)),2));
                else if (k==81 and myele.Pt()>=25 and myele.Pt()<35 and mymu.Pt()>=25) weight2=1-sqrt(pow(closureOS->GetBinError(closureOS->GetXaxis()->FindBin(50.0),closureOS->GetYaxis()->FindBin(30.0))/closureOS->GetBinContent(closureOS->GetXaxis()->FindBin(50.0),closureOS->GetYaxis()->FindBin(30.0)),2)+pow(correction->GetBinError(correction->GetXaxis()->FindBin(50.0),correction->GetYaxis()->FindBin(30.0))/correction->GetBinContent(correction->GetXaxis()->FindBin(50.0),correction->GetYaxis()->FindBin(30.0)),2));
                else if (k==82 and myele.Pt()>=25 and myele.Pt()<35 and mymu.Pt()>=25) weight2=1+sqrt(pow(closureOS->GetBinError(closureOS->GetXaxis()->FindBin(50.0),closureOS->GetYaxis()->FindBin(30.0))/closureOS->GetBinContent(closureOS->GetXaxis()->FindBin(50.0),closureOS->GetYaxis()->FindBin(30.0)),2)+pow(correction->GetBinError(correction->GetXaxis()->FindBin(50.0),correction->GetYaxis()->FindBin(30.0))/correction->GetBinContent(correction->GetXaxis()->FindBin(50.0),correction->GetYaxis()->FindBin(30.0)),2));
                else if (k==83 and myele.Pt()>=35 and mymu.Pt()>=15 and mymu.Pt()<25) weight2=1-sqrt(pow(closureOS->GetBinError(closureOS->GetXaxis()->FindBin(20.0),closureOS->GetYaxis()->FindBin(50.0))/closureOS->GetBinContent(closureOS->GetXaxis()->FindBin(20.0),closureOS->GetYaxis()->FindBin(50.0)),2)+pow(correction->GetBinError(correction->GetXaxis()->FindBin(20.0),correction->GetYaxis()->FindBin(50.0))/correction->GetBinContent(correction->GetXaxis()->FindBin(20.0),correction->GetYaxis()->FindBin(50.0)),2));
                else if (k==84 and myele.Pt()>=35 and mymu.Pt()>=15 and mymu.Pt()<25) weight2=1+sqrt(pow(closureOS->GetBinError(closureOS->GetXaxis()->FindBin(20.0),closureOS->GetYaxis()->FindBin(50.0))/closureOS->GetBinContent(closureOS->GetXaxis()->FindBin(20.0),closureOS->GetYaxis()->FindBin(50.0)),2)+pow(correction->GetBinError(correction->GetXaxis()->FindBin(20.0),correction->GetYaxis()->FindBin(50.0))/correction->GetBinContent(correction->GetXaxis()->FindBin(20.0),correction->GetYaxis()->FindBin(50.0)),2));
                else if (k==85 and myele.Pt()>=35 and mymu.Pt()>=25) weight2=1-sqrt(pow(closureOS->GetBinError(closureOS->GetXaxis()->FindBin(50.0),closureOS->GetYaxis()->FindBin(50.0))/closureOS->GetBinContent(closureOS->GetXaxis()->FindBin(50.0),closureOS->GetYaxis()->FindBin(50.0)),2)+pow(correction->GetBinError(correction->GetXaxis()->FindBin(50.0),correction->GetYaxis()->FindBin(50.0))/correction->GetBinContent(correction->GetXaxis()->FindBin(50.0),correction->GetYaxis()->FindBin(50.0)),2));
                else if (k==85 and myele.Pt()>=35 and mymu.Pt()>=25) weight2=1+sqrt(pow(closureOS->GetBinError(closureOS->GetXaxis()->FindBin(50.0),closureOS->GetYaxis()->FindBin(50.0))/closureOS->GetBinContent(closureOS->GetXaxis()->FindBin(50.0),closureOS->GetYaxis()->FindBin(50.0)),2)+pow(correction->GetBinError(correction->GetXaxis()->FindBin(50.0),correction->GetYaxis()->FindBin(50.0))/correction->GetBinContent(correction->GetXaxis()->FindBin(50.0),correction->GetYaxis()->FindBin(50.0)),2));
           }
           if ((sample=="data_obs" or sample=="embedded") && k>0 && k<27){
                /*if (k==1 && numberJets==0) ssweight=osss_0jet_unc1_down->Eval(myele.DeltaR(mymu));
                else if (k==2 && numberJets==0) ssweight=osss_0jet_unc1_up->Eval(myele.DeltaR(mymu));
                else if (k==3 && numberJets==0) ssweight=osss_0jet_unc2_down->Eval(myele.DeltaR(mymu));
                else if (k==4 && numberJets==0) ssweight=osss_0jet_unc2_up->Eval(myele.DeltaR(mymu));*/
                if (k==1 && numberJets==0) ssweight=osss_0jet_par0->Eval(myele.DeltaR(mymu));
                else if (k==2 && numberJets==0) ssweight=osss_0jet->Eval(myele.DeltaR(mymu))-(osss_0jet_par0->Eval(myele.DeltaR(mymu))-osss_0jet->Eval(myele.DeltaR(mymu)));
                else if (k==3 && numberJets==0) ssweight=osss_0jet_par1->Eval(myele.DeltaR(mymu));
                else if (k==4 && numberJets==0) ssweight=osss_0jet->Eval(myele.DeltaR(mymu))-(osss_0jet_par1->Eval(myele.DeltaR(mymu))-osss_0jet->Eval(myele.DeltaR(mymu)));
                else if (k==5 && numberJets==1) ssweight=osss_1jet_unc1_down->Eval(myele.DeltaR(mymu));
                else if (k==6 && numberJets==1) ssweight=osss_1jet_unc1_up->Eval(myele.DeltaR(mymu));
                else if (k==7 && numberJets==1) ssweight=osss_1jet_unc2_down->Eval(myele.DeltaR(mymu));
                else if (k==8 && numberJets==1) ssweight=osss_1jet_unc2_up->Eval(myele.DeltaR(mymu));
                else if (k==9 && numberJets>1) ssweight=osss_2jet_unc1_down->Eval(myele.DeltaR(mymu));
                else if (k==10 && numberJets>1) ssweight=osss_2jet_unc1_up->Eval(myele.DeltaR(mymu));
                else if (k==11 && numberJets>1) ssweight=osss_2jet_unc2_down->Eval(myele.DeltaR(mymu));
                else if (k==12 && numberJets>1) ssweight=osss_2jet_unc2_up->Eval(myele.DeltaR(mymu));
                else if (k==13) sscorr=1.0;
                else if (k==14) sscorr=(1+2*(correction->GetBinContent(correction->GetXaxis()->FindBin(mupt),correction->GetYaxis()->FindBin(ept))-1));
                else if (k==15 and myele.Pt()>=15 and myele.Pt()<25 and mymu.Pt()>=15 and mymu.Pt()<25) weight2=1-sqrt(pow(closureOS->GetBinError(closureOS->GetXaxis()->FindBin(20.0),closureOS->GetYaxis()->FindBin(20.0))/closureOS->GetBinContent(closureOS->GetXaxis()->FindBin(20.0),closureOS->GetYaxis()->FindBin(20.0)),2)+pow(correction->GetBinError(correction->GetXaxis()->FindBin(20.0),correction->GetYaxis()->FindBin(20.0))/correction->GetBinContent(correction->GetXaxis()->FindBin(20.0),correction->GetYaxis()->FindBin(20.0)),2));
                else if (k==16 and myele.Pt()>=15 and myele.Pt()<25 and mymu.Pt()>=15 and mymu.Pt()<25) weight2=1+sqrt(pow(closureOS->GetBinError(closureOS->GetXaxis()->FindBin(20.0),closureOS->GetYaxis()->FindBin(20.0))/closureOS->GetBinContent(closureOS->GetXaxis()->FindBin(20.0),closureOS->GetYaxis()->FindBin(20.0)),2)+pow(correction->GetBinError(correction->GetXaxis()->FindBin(20.0),correction->GetYaxis()->FindBin(20.0))/correction->GetBinContent(correction->GetXaxis()->FindBin(20.0),correction->GetYaxis()->FindBin(20.0)),2));
                else if (k==17 and myele.Pt()>=15 and myele.Pt()<25 and mymu.Pt()>=25) weight2=1-sqrt(pow(closureOS->GetBinError(closureOS->GetXaxis()->FindBin(50.0),closureOS->GetYaxis()->FindBin(20.0))/closureOS->GetBinContent(closureOS->GetXaxis()->FindBin(50.0),closureOS->GetYaxis()->FindBin(20.0)),2)+pow(correction->GetBinError(correction->GetXaxis()->FindBin(50.0),correction->GetYaxis()->FindBin(20.0))/correction->GetBinContent(correction->GetXaxis()->FindBin(50.0),correction->GetYaxis()->FindBin(20.0)),2));
                else if (k==18 and myele.Pt()>=15 and myele.Pt()<25 and mymu.Pt()>=25) weight2=1+sqrt(pow(closureOS->GetBinError(closureOS->GetXaxis()->FindBin(50.0),closureOS->GetYaxis()->FindBin(20.0))/closureOS->GetBinContent(closureOS->GetXaxis()->FindBin(50.0),closureOS->GetYaxis()->FindBin(20.0)),2)+pow(correction->GetBinError(correction->GetXaxis()->FindBin(50.0),correction->GetYaxis()->FindBin(20.0))/correction->GetBinContent(correction->GetXaxis()->FindBin(50.0),correction->GetYaxis()->FindBin(20.0)),2));
                else if (k==19 and myele.Pt()>=25 and myele.Pt()<35 and mymu.Pt()>=15 and mymu.Pt()<25) weight2=1-sqrt(pow(closureOS->GetBinError(closureOS->GetXaxis()->FindBin(20.0),closureOS->GetYaxis()->FindBin(30.0))/closureOS->GetBinContent(closureOS->GetXaxis()->FindBin(20.0),closureOS->GetYaxis()->FindBin(30.0)),2)+pow(correction->GetBinError(correction->GetXaxis()->FindBin(20.0),correction->GetYaxis()->FindBin(30.0))/correction->GetBinContent(correction->GetXaxis()->FindBin(20.0),correction->GetYaxis()->FindBin(30.0)),2));
                else if (k==20 and myele.Pt()>=25 and myele.Pt()<35 and mymu.Pt()>=15 and mymu.Pt()<25) weight2=1+sqrt(pow(closureOS->GetBinError(closureOS->GetXaxis()->FindBin(20.0),closureOS->GetYaxis()->FindBin(30.0))/closureOS->GetBinContent(closureOS->GetXaxis()->FindBin(20.0),closureOS->GetYaxis()->FindBin(30.0)),2)+pow(correction->GetBinError(correction->GetXaxis()->FindBin(20.0),correction->GetYaxis()->FindBin(30.0))/correction->GetBinContent(correction->GetXaxis()->FindBin(20.0),correction->GetYaxis()->FindBin(30.0)),2));
                else if (k==21 and myele.Pt()>=25 and myele.Pt()<35 and mymu.Pt()>=25) weight2=1-sqrt(pow(closureOS->GetBinError(closureOS->GetXaxis()->FindBin(50.0),closureOS->GetYaxis()->FindBin(30.0))/closureOS->GetBinContent(closureOS->GetXaxis()->FindBin(50.0),closureOS->GetYaxis()->FindBin(30.0)),2)+pow(correction->GetBinError(correction->GetXaxis()->FindBin(50.0),correction->GetYaxis()->FindBin(30.0))/correction->GetBinContent(correction->GetXaxis()->FindBin(50.0),correction->GetYaxis()->FindBin(30.0)),2));
                else if (k==22 and myele.Pt()>=25 and myele.Pt()<35 and mymu.Pt()>=25) weight2=1+sqrt(pow(closureOS->GetBinError(closureOS->GetXaxis()->FindBin(50.0),closureOS->GetYaxis()->FindBin(30.0))/closureOS->GetBinContent(closureOS->GetXaxis()->FindBin(50.0),closureOS->GetYaxis()->FindBin(30.0)),2)+pow(correction->GetBinError(correction->GetXaxis()->FindBin(50.0),correction->GetYaxis()->FindBin(30.0))/correction->GetBinContent(correction->GetXaxis()->FindBin(50.0),correction->GetYaxis()->FindBin(30.0)),2));
                else if (k==23 and myele.Pt()>=35 and mymu.Pt()>=15 and mymu.Pt()<25) weight2=1-sqrt(pow(closureOS->GetBinError(closureOS->GetXaxis()->FindBin(20.0),closureOS->GetYaxis()->FindBin(50.0))/closureOS->GetBinContent(closureOS->GetXaxis()->FindBin(20.0),closureOS->GetYaxis()->FindBin(50.0)),2)+pow(correction->GetBinError(correction->GetXaxis()->FindBin(20.0),correction->GetYaxis()->FindBin(50.0))/correction->GetBinContent(correction->GetXaxis()->FindBin(20.0),correction->GetYaxis()->FindBin(50.0)),2));
                else if (k==24 and myele.Pt()>=35 and mymu.Pt()>=15 and mymu.Pt()<25) weight2=1+sqrt(pow(closureOS->GetBinError(closureOS->GetXaxis()->FindBin(20.0),closureOS->GetYaxis()->FindBin(50.0))/closureOS->GetBinContent(closureOS->GetXaxis()->FindBin(20.0),closureOS->GetYaxis()->FindBin(50.0)),2)+pow(correction->GetBinError(correction->GetXaxis()->FindBin(20.0),correction->GetYaxis()->FindBin(50.0))/correction->GetBinContent(correction->GetXaxis()->FindBin(20.0),correction->GetYaxis()->FindBin(50.0)),2));
                else if (k==25 and myele.Pt()>=35 and mymu.Pt()>=25) weight2=1-sqrt(pow(closureOS->GetBinError(closureOS->GetXaxis()->FindBin(50.0),closureOS->GetYaxis()->FindBin(50.0))/closureOS->GetBinContent(closureOS->GetXaxis()->FindBin(50.0),closureOS->GetYaxis()->FindBin(50.0)),2)+pow(correction->GetBinError(correction->GetXaxis()->FindBin(50.0),correction->GetYaxis()->FindBin(50.0))/correction->GetBinContent(correction->GetXaxis()->FindBin(50.0),correction->GetYaxis()->FindBin(50.0)),2));
                else if (k==26 and myele.Pt()>=35 and mymu.Pt()>=25) weight2=1+sqrt(pow(closureOS->GetBinError(closureOS->GetXaxis()->FindBin(50.0),closureOS->GetYaxis()->FindBin(50.0))/closureOS->GetBinContent(closureOS->GetXaxis()->FindBin(50.0),closureOS->GetYaxis()->FindBin(50.0)),2)+pow(correction->GetBinError(correction->GetXaxis()->FindBin(50.0),correction->GetYaxis()->FindBin(50.0))/correction->GetBinContent(correction->GetXaxis()->FindBin(50.0),correction->GetYaxis()->FindBin(50.0)),2));
           }
           ssweight=ssweight*closureOS->GetBinContent(closureOS->GetXaxis()->FindBin(mupt),closureOS->GetYaxis()->FindBin(ept));

if (ssweight<0) ssweight=2.5;
float mymsv=m_sv;
if (mymsv<50) mymsv=50;
float frac=hfrac_0jetlow->GetBinContent(hfrac_0jetlow->GetXaxis()->FindBin(mymsv));
if (njets==0 && myele.DeltaR(mymu)>2.0 && myele.DeltaR(mymu)<3.0) hfrac_0jethigh->GetBinContent(hfrac_0jethigh->GetXaxis()->FindBin(mymsv));
else if (njets==1) frac=hfrac_boosted1->GetBinContent(hfrac_boosted1->GetXaxis()->FindBin(mymsv));
else if (njets>1 && mjj<350) frac=hfrac_boosted2->GetBinContent(hfrac_boosted2->GetXaxis()->FindBin(mymsv));
else if (njets>1 && mjj>350 && (myele+mymu+mymet).Pt()<200) frac=hfrac_vbflow->GetBinContent(hfrac_vbflow->GetXaxis()->FindBin(mymsv));
else if (njets>1 && mjj>350 && (myele+mymu+mymet).Pt()>200) frac=hfrac_vbfhigh->GetBinContent(hfrac_vbfhigh->GetXaxis()->FindBin(mymsv));
float dr=myele.DeltaR(mymu);
ssweight=ssweight*sscorr*frac + (1.0-frac)*(0.4888+2.11274*dr-1.4128*dr*dr+0.329987*dr*dr*dr-0.02756*dr*dr*dr*dr);
sscorr=1.0;//FIXME

	   if (k==0 and signalRegion && q_1*q_2<0) h_msv->Fill(m_sv,aweight*weight2);

           bool category_0=false;
           if (!do_differential && do_control_plots==0 && myele.DeltaR(mymu)>2.0 && numberJets==0 && pass_mt && pass_dzeta) category_0=true;
           if (!do_differential && do_control_plots==1 && pass_mt && pass_dzeta) category_0=true;
           if (!do_differential && do_control_plots==2 && pass_mt) category_0=true;
           if (do_differential && pass_mt) category_0=true;
           if (category_0){
               if (k==0 && is_includedInEmbedded && signalRegion && q_1*q_2<0)
                   h0_ttcontamination->Fill(myvar0,mass0,aweight*weight2);
               if (signalRegion && q_1*q_2<0 && is_tau)
                   h0tau_OS[k]->Fill(myvar0,mass0,aweight*weight2);
               if (signalRegion && q_1*q_2>0 && is_tau)
                   h0tau_SS[k]->Fill(myvar0,mass0,aweight*weight2*ssweight*sscorr);
               if (antiisoRegion && is_tau && q_1*q_2>0 )
                   h0tau_AI[k]->Fill(myvar0,mass0,aweight*weight2*ssweight*sscorr);
               if (signalRegion && q_1*q_2<0 && is_ell)
                   h0ell_OS[k]->Fill(myvar0,mass0,aweight*weight2);
               if (signalRegion && q_1*q_2>0 && is_ell)
                   h0ell_SS[k]->Fill(myvar0,mass0,aweight*weight2*ssweight*sscorr);
               if (antiisoRegion && is_ell && q_1*q_2>0 )
                   h0ell_AI[k]->Fill(myvar0,mass0,aweight*weight2*ssweight*sscorr);
           }

           bool category_1=false;
           if (!do_differential && do_control_plots==0 && numberJets==1 && pass_mt && pass_dzeta) category_1=true;
           if (!do_differential && do_control_plots>=1 && pass_mt && pass_dzeta) category_1=true;
           if (do_differential && pass_mt) category_1=true;
           if (category_1){
               if (k==0 && is_includedInEmbedded && signalRegion && q_1*q_2<0)
                   h1_ttcontamination->Fill(myvar1,mass1,aweight*weight2);
               if (signalRegion && q_1*q_2<0 && is_tau)
                   h1tau_OS[k]->Fill(myvar1,mass1,aweight*weight2);
               if (signalRegion && q_1*q_2>0 && is_tau)
                   h1tau_SS[k]->Fill(myvar1,mass1,aweight*weight2*ssweight*sscorr);
               if (antiisoRegion && is_tau && q_1*q_2>0 )
                   h1tau_AI[k]->Fill(myvar1,mass1,aweight*weight2*ssweight*sscorr);
               if (signalRegion && q_1*q_2<0 && is_ell)
                   h1ell_OS[k]->Fill(myvar1,mass1,aweight*weight2);
               if (signalRegion && q_1*q_2>0 && is_ell)
                   h1ell_SS[k]->Fill(myvar1,mass1,aweight*weight2*ssweight*sscorr);
               if (antiisoRegion && is_ell && q_1*q_2>0 )
                   h1ell_AI[k]->Fill(myvar1,mass1,aweight*weight2*ssweight*sscorr);
           }

           bool category_2=false;
           if (!do_differential && do_control_plots==0 && numberJets>1 && pass_mt && pass_dzeta) category_2=true;
           if (!do_differential && do_control_plots==1 && pass_mt && pass_dzeta) category_2=true;
           if (!do_differential && do_control_plots==2 && pass_dzeta) category_2=true;
           if (do_differential && pass_mt) category_2=true;
           if (category_2){
               if (k==0 && is_includedInEmbedded && signalRegion && q_1*q_2<0)
                   h2_ttcontamination->Fill(myvar2,mass2,aweight*weight2);
               if (signalRegion && q_1*q_2<0 && is_tau)
                   h2tau_OS[k]->Fill(myvar2,mass2,aweight*weight2);
               if (signalRegion && q_1*q_2>0 && is_tau)
                   h2tau_SS[k]->Fill(myvar2,mass2,aweight*weight2*ssweight*sscorr);
               if (antiisoRegionVBF && is_tau && q_1*q_2>0 )
                   h2tau_AI[k]->Fill(myvar2,mass2,aweight*weight2*ssweight*sscorr);
               if (signalRegion && q_1*q_2<0 && is_ell)
                   h2ell_OS[k]->Fill(myvar2,mass2,aweight*weight2);
               if (signalRegion && q_1*q_2>0 && is_ell)
                   h2ell_SS[k]->Fill(myvar2,mass2,aweight*weight2*ssweight*sscorr);
               if (antiisoRegionVBF && is_ell && q_1*q_2>0 )
                   h2ell_AI[k]->Fill(myvar2,mass2,aweight*weight2*ssweight*sscorr);
           }

           bool category_3=false;
           if (!do_differential && do_control_plots==0 && numberJets==0 && myele.DeltaR(mymu)>3 && pass_mt && pass_dzeta) category_3=true;
           if (!do_differential && do_control_plots>=1 && pass_mt && pass_dzeta) category_3=true;
           if (do_differential && pass_mt) category_3=true;
           if (category_3){
               if (k==0 && is_includedInEmbedded && signalRegion && q_1*q_2<0)
                   h3_ttcontamination->Fill(myvar3,mass3,aweight*weight2);
               if (signalRegion && q_1*q_2<0 && is_tau)
                   h3tau_OS[k]->Fill(myvar3,mass3,aweight*weight2);
               if (signalRegion && q_1*q_2>0 && is_tau)
                   h3tau_SS[k]->Fill(myvar3,mass3,aweight*weight2*ssweight*sscorr);
               if (antiisoRegion && is_tau && q_1*q_2>0 )
                   h3tau_AI[k]->Fill(myvar3,mass3,aweight*weight2*ssweight*sscorr);
               if (signalRegion && q_1*q_2<0 && is_ell)
                   h3ell_OS[k]->Fill(myvar3,mass3,aweight*weight2);
               if (signalRegion && q_1*q_2>0 && is_ell)
                   h3ell_SS[k]->Fill(myvar3,mass3,aweight*weight2*ssweight*sscorr);
               if (antiisoRegion && is_ell && q_1*q_2>0 )
                   h3ell_AI[k]->Fill(myvar3,mass3,aweight*weight2*ssweight*sscorr);
           }

           bool category_4=false;
           if (!do_differential && do_control_plots==0 && numberJets==0 && myele.DeltaR(mymu)>2.0 && myele.DeltaR(mymu)<=3.0 && pass_mt && pass_dzeta) category_4=true;
           if (!do_differential && do_control_plots>=1 && pass_mt && pass_dzeta) category_4=true;
           if (do_differential && pass_mt) category_4=true;
           if (category_4){
               if (k==0 && is_includedInEmbedded && signalRegion && q_1*q_2<0)
                   h4_ttcontamination->Fill(myvar4,mass4,aweight*weight2);
               if (signalRegion && q_1*q_2<0 && is_tau)
                   h4tau_OS[k]->Fill(myvar4,mass4,aweight*weight2);
               if (signalRegion && q_1*q_2>0 && is_tau)
                   h4tau_SS[k]->Fill(myvar4,mass4,aweight*weight2*ssweight*sscorr);
               if (antiisoRegion && is_tau && q_1*q_2>0 )
                   h4tau_AI[k]->Fill(myvar4,mass4,aweight*weight2*ssweight*sscorr);
               if (signalRegion && q_1*q_2<0 && is_ell)
                   h4ell_OS[k]->Fill(myvar4,mass4,aweight*weight2);
               if (signalRegion && q_1*q_2>0 && is_ell)
                   h4ell_SS[k]->Fill(myvar4,mass4,aweight*weight2*ssweight*sscorr);
               if (antiisoRegion && is_ell && q_1*q_2>0 )
                   h4ell_AI[k]->Fill(myvar4,mass4,aweight*weight2*ssweight*sscorr);
           }

           bool category_5=false;
           if (!do_differential && do_control_plots==0 && numberJets==1 && pass_mt && pass_dzeta) category_5=true;
           if (!do_differential && do_control_plots>=1 && pass_mt && pass_dzeta) category_5=true;
           if (do_differential && pass_mt) category_5=true;
           if (category_5){
               if (k==0 && is_includedInEmbedded && signalRegion && q_1*q_2<0)
                   h5_ttcontamination->Fill(myvar5,mass5,aweight*weight2);
               if (signalRegion && q_1*q_2<0 && is_tau)
                   h5tau_OS[k]->Fill(myvar5,mass5,aweight*weight2);
               if (signalRegion && q_1*q_2>0 && is_tau)
                   h5tau_SS[k]->Fill(myvar5,mass5,aweight*weight2*ssweight*sscorr);
               if (antiisoRegion && is_tau && q_1*q_2>0 )
                   h5tau_AI[k]->Fill(myvar5,mass5,aweight*weight2*ssweight*sscorr);
               if (signalRegion && q_1*q_2<0 && is_ell)
                   h5ell_OS[k]->Fill(myvar5,mass5,aweight*weight2);
               if (signalRegion && q_1*q_2>0 && is_ell)
                   h5ell_SS[k]->Fill(myvar5,mass5,aweight*weight2*ssweight*sscorr);
               if (antiisoRegion && is_ell && q_1*q_2>0 )
                   h5ell_AI[k]->Fill(myvar5,mass5,aweight*weight2*ssweight*sscorr);
           }

           bool category_6=false;
           if (!do_differential && do_control_plots==0 && numberJets>1 && massJets<350 && pass_mt && pass_dzeta) category_6=true;
           if (!do_differential && do_control_plots>=1 && pass_mt && pass_dzeta) category_6=true;
           if (do_differential && pass_mt) category_6=true;
           if (category_6){
               if (signalRegion && q_1*q_2<0 && is_tau)
                   h6tau_OS[k]->Fill(myvar6,mass6,aweight*weight2);
               if (k==0 && is_includedInEmbedded && signalRegion && q_1*q_2<0)
                   h6_ttcontamination->Fill(myvar6,mass6,aweight*weight2);
               if (signalRegion && q_1*q_2>0 && is_tau)
                   h6tau_SS[k]->Fill(myvar6,mass6,aweight*weight2*ssweight*sscorr);
               if (antiisoRegion && is_tau && q_1*q_2>0 )
                   h6tau_AI[k]->Fill(myvar6,mass6,aweight*weight2*ssweight*sscorr);
               if (signalRegion && q_1*q_2<0 && is_ell)
                   h6ell_OS[k]->Fill(myvar6,mass6,aweight*weight2);
               if (signalRegion && q_1*q_2>0 && is_ell)
                   h6ell_SS[k]->Fill(myvar6,mass6,aweight*weight2*ssweight*sscorr);
               if (antiisoRegion && is_ell && q_1*q_2>0 )
                   h6ell_AI[k]->Fill(myvar6,mass6,aweight*weight2*ssweight*sscorr);
           }


           bool category_7=false;
           if (!do_differential && do_control_plots==0 && numberJets>=2 && massJets>=350 && (myele+mymu+mymet).Pt()<200 && pass_mt && pass_dzeta) category_7=true;
           if (!do_differential && do_control_plots>=1 && pass_mt && pass_dzeta) category_7=true;
           if (do_differential && pass_mt) category_7=true;
           if (category_7){
               if (k==0 && is_includedInEmbedded && signalRegion && q_1*q_2<0)
                   h7_ttcontamination->Fill(myvar7,mass7,aweight*weight2);
               if (signalRegion && q_1*q_2<0 && is_tau)
                   h7tau_OS[k]->Fill(myvar7,mass7,aweight*weight2);
               if (signalRegion && q_1*q_2>0 && is_tau)
                   h7tau_SS[k]->Fill(myvar7,mass7,aweight*weight2*ssweight*sscorr);
               if (antiisoRegionVBF && is_tau && q_1*q_2>0 )
                   h7tau_AI[k]->Fill(myvar7,mass7,aweight*weight2*ssweight*sscorr);
               if (signalRegion && q_1*q_2<0 && is_ell)
                   h7ell_OS[k]->Fill(myvar7,mass7,aweight*weight2);
               if (signalRegion && q_1*q_2>0 && is_ell)
                   h7ell_SS[k]->Fill(myvar7,mass7,aweight*weight2*ssweight*sscorr);
               if (antiisoRegionVBF && is_ell && q_1*q_2>0 )
                   h7ell_AI[k]->Fill(myvar7,mass7,aweight*weight2*ssweight*sscorr);
           }

           bool category_8=false;
           if (!do_differential && do_control_plots==0 && numberJets>=2 && massJets>=350 && (myele+mymu+mymet).Pt()>=200 && pass_mt && pass_dzeta) category_8=true;
           if (!do_differential && do_control_plots>=1 && pass_mt && pass_dzeta) category_8=true;
           if (do_differential && pass_mt) category_8=true;
           if (category_8){
               if (!do_differential && do_control_plots==0 && sample=="W") weight2=0;//FIXME
               if (k==0 && is_includedInEmbedded && signalRegion && q_1*q_2<0)
                   h8_ttcontamination->Fill(myvar8,mass8,aweight*weight2);
               if (signalRegion && q_1*q_2<0 && is_tau)
                   h8tau_OS[k]->Fill(myvar8,mass8,aweight*weight2);
               if (signalRegion && q_1*q_2>0 && is_tau)
                   h8tau_SS[k]->Fill(myvar8,mass8,aweight*weight2*ssweight*sscorr);
               if (antiisoRegionVBF && is_tau && q_1*q_2>0 )
                   h8tau_AI[k]->Fill(myvar8,mass8,aweight*weight2*ssweight*sscorr);
               if (signalRegion && q_1*q_2<0 && is_ell)
                   h8ell_OS[k]->Fill(myvar8,mass8,aweight*weight2);
               if (signalRegion && q_1*q_2>0 && is_ell)
                   h8ell_SS[k]->Fill(myvar8,mass8,aweight*weight2*ssweight*sscorr);
               if (antiisoRegionVBF && is_ell && q_1*q_2>0)
                   h8ell_AI[k]->Fill(myvar8,mass8,aweight*weight2*ssweight*sscorr);
           }
	} // end of loop over nbhist

    } // end of loop over events
    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();
    h_msv->Write();

    if (sample!="data_obs"){
       EmptyBins(h0tau_OS[0]); EmptyBins(h0tau_SS[0]); 
       EmptyBins(h1tau_OS[0]); EmptyBins(h1tau_SS[0]);
       EmptyBins(h2tau_OS[0]); EmptyBins(h2tau_SS[0]); 
       EmptyBins(h3tau_OS[0]); EmptyBins(h3tau_SS[0]); 
       EmptyBins(h4tau_OS[0]); EmptyBins(h4tau_SS[0]); 
       EmptyBins(h5tau_OS[0]); EmptyBins(h5tau_SS[0]); 
       EmptyBins(h6tau_OS[0]); EmptyBins(h6tau_SS[0]); 
       EmptyBins(h7tau_OS[0]); EmptyBins(h7tau_SS[0]); 
       EmptyBins(h8tau_OS[0]); EmptyBins(h8tau_SS[0]); 
       EmptyBins(h0ell_OS[0]); EmptyBins(h0ell_SS[0]);
       EmptyBins(h1ell_OS[0]); EmptyBins(h1ell_SS[0]);
       EmptyBins(h2ell_OS[0]); EmptyBins(h2ell_SS[0]);
       EmptyBins(h3ell_OS[0]); EmptyBins(h3ell_SS[0]);
       EmptyBins(h4ell_OS[0]); EmptyBins(h4ell_SS[0]);
       EmptyBins(h5ell_OS[0]); EmptyBins(h5ell_SS[0]);
       EmptyBins(h6ell_OS[0]); EmptyBins(h6ell_SS[0]);
       EmptyBins(h7ell_OS[0]); EmptyBins(h7ell_SS[0]);
       EmptyBins(h8ell_OS[0]); EmptyBins(h8ell_SS[0]);
    }


    TString postfix="";
    TString strL="L";
    TString strT="T";
    TDirectory *OS0jet =fout->mkdir("em_0jet");
    OS0jet->cd();
    h0_ttcontamination->SetName("ttcontamination");
    h0_ttcontamination->Write();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if ((sample=="embedded" or sample=="data_obs") && k>0 && k<27) postfix=postfixQCD[k-1];
       else if (sample=="embedded" && k>26) postfix=postfixEmbedded[k-1-26];
       else if (!is_ggh && !is_qqh && k>60) postfix=postfixQCD[k-60-1];
       else if (is_ggh && k>60) postfix=postfixGGH[k-60-1];
       else if (is_qqh && k>60) postfix=postfixVBF[k-60-1];
       else postfix=postfixMC[k];
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h0tau_OS[k]->SetName(name.c_str()+strT+postfix);
          h0tau_OS[k]->Write();
          h0ell_OS[k]->SetName(name.c_str()+strL+postfix);
          h0ell_OS[k]->Write();
       }
       else{
	  h0tau_OS[k]->Add(h0ell_OS[k]);
          h0tau_OS[k]->SetName(name.c_str()+postfix);
	  h0tau_OS[k]->Write();
       }
    }
    TDirectory *SS0jet =fout->mkdir("SS0jet");
    SS0jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if ((sample=="embedded" or sample=="data_obs") && k>0 && k<27) postfix=postfixQCD[k-1];
       else if (sample=="embedded" && k>26) postfix=postfixEmbedded[k-1-26];
       else if (!is_ggh && !is_qqh && k>60) postfix=postfixQCD[k-60-1];
       else if (is_ggh && k>60) postfix=postfixGGH[k-60-1];
       else if (is_qqh && k>60) postfix=postfixVBF[k-60-1];
       else postfix=postfixMC[k];
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h0tau_SS[k]->SetName(name.c_str()+strT+postfix);
          h0tau_SS[k]->Write();
          h0ell_SS[k]->SetName(name.c_str()+strL+postfix);
          h0ell_SS[k]->Write();
       }
       else{
          h0tau_SS[k]->Add(h0ell_SS[k]);
          h0tau_SS[k]->SetName(name.c_str()+postfix);
          h0tau_SS[k]->Write();
       }
    }

    TDirectory *AI0jet =fout->mkdir("AI0jet");
    AI0jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if ((sample=="embedded" or sample=="data_obs") && k>0 && k<27) postfix=postfixQCD[k-1];
       else if (sample=="embedded" && k>26) postfix=postfixEmbedded[k-1-26];
       else if (!is_ggh && !is_qqh && k>60) postfix=postfixQCD[k-60-1];
       else if (is_ggh && k>60) postfix=postfixGGH[k-60-1];
       else if (is_qqh && k>60) postfix=postfixVBF[k-60-1];
       else postfix=postfixMC[k];
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h0tau_AI[k]->SetName(name.c_str()+strT+postfix);
          h0tau_AI[k]->Write();
          h0ell_AI[k]->SetName(name.c_str()+strL+postfix);
          h0ell_AI[k]->Write();
       }
       else{
          h0tau_AI[k]->Add(h0ell_AI[k]);
          h0tau_AI[k]->SetName(name.c_str()+postfix);
          h0tau_AI[k]->Write();
       }
    }

    TDirectory *OS1jet =fout->mkdir("em_boosted");
    OS1jet->cd();
    h1_ttcontamination->SetName("ttcontamination");
    h1_ttcontamination->Write();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if ((sample=="embedded" or sample=="data_obs") && k>0 && k<27) postfix=postfixQCD[k-1];
       else if (sample=="embedded" && k>26) postfix=postfixEmbedded[k-1-26];
       else if (!is_ggh && !is_qqh && k>60) postfix=postfixQCD[k-60-1];
       else if (is_ggh && k>60) postfix=postfixGGH[k-60-1];
       else if (is_qqh && k>60) postfix=postfixVBF[k-60-1];
       else postfix=postfixMC[k];
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h1tau_OS[k]->SetName(name.c_str()+strT+postfix);
          h1tau_OS[k]->Write();
          h1ell_OS[k]->SetName(name.c_str()+strL+postfix);
          h1ell_OS[k]->Write();
       }
       else{
          h1tau_OS[k]->Add(h1ell_OS[k]);
          h1tau_OS[k]->SetName(name.c_str()+postfix);
          h1tau_OS[k]->Write();
       }
    }

    TDirectory *SS1jet =fout->mkdir("SSboosted");
    SS1jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if ((sample=="embedded" or sample=="data_obs") && k>0 && k<27) postfix=postfixQCD[k-1];
       else if (sample=="embedded" && k>26) postfix=postfixEmbedded[k-1-26];
       else if (!is_ggh && !is_qqh && k>60) postfix=postfixQCD[k-60-1];
       else if (is_ggh && k>60) postfix=postfixGGH[k-60-1];
       else if (is_qqh && k>60) postfix=postfixVBF[k-60-1];
       else postfix=postfixMC[k];
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h1tau_SS[k]->SetName(name.c_str()+strT+postfix);
          h1tau_SS[k]->Write();
          h1ell_SS[k]->SetName(name.c_str()+strL+postfix);
          h1ell_SS[k]->Write();
       }
       else{
          h1tau_SS[k]->Add(h1ell_SS[k]);
          h1tau_SS[k]->SetName(name.c_str()+postfix);
          h1tau_SS[k]->Write();
       }
    }

    TDirectory *AI1jet =fout->mkdir("AIboosted");
    AI1jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if ((sample=="embedded" or sample=="data_obs") && k>0 && k<27) postfix=postfixQCD[k-1];
       else if (sample=="embedded" && k>26) postfix=postfixEmbedded[k-1-26];
       else if (!is_ggh && !is_qqh && k>60) postfix=postfixQCD[k-60-1];
       else if (is_ggh && k>60) postfix=postfixGGH[k-60-1];
       else if (is_qqh && k>60) postfix=postfixVBF[k-60-1];
       else postfix=postfixMC[k];
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h1tau_AI[k]->SetName(name.c_str()+strT+postfix);
          h1tau_AI[k]->Write();
          h1ell_AI[k]->SetName(name.c_str()+strL+postfix);
          h1ell_AI[k]->Write();
       }
       else{
          h1tau_AI[k]->Add(h1ell_AI[k]);
          h1tau_AI[k]->SetName(name.c_str()+postfix);
          h1tau_AI[k]->Write();
       }
    }

    TDirectory *OS2jet =fout->mkdir("em_vbf");
    OS2jet->cd();
    h2_ttcontamination->SetName("ttcontamination");
    h2_ttcontamination->Write();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if ((sample=="embedded" or sample=="data_obs") && k>0 && k<27) postfix=postfixQCD[k-1];
       else if (sample=="embedded" && k>26) postfix=postfixEmbedded[k-1-26];
       else if (!is_ggh && !is_qqh && k>60) postfix=postfixQCD[k-60-1];
       else if (is_ggh && k>60) postfix=postfixGGH[k-60-1];
       else if (is_qqh && k>60) postfix=postfixVBF[k-60-1];
       else postfix=postfixMC[k];
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h2tau_OS[k]->SetName(name.c_str()+strT+postfix);
          h2tau_OS[k]->Write();
          h2ell_OS[k]->SetName(name.c_str()+strL+postfix);
          h2ell_OS[k]->Write();
       }
       else{
          h2tau_OS[k]->Add(h2ell_OS[k]);
          h2tau_OS[k]->SetName(name.c_str()+postfix);
          h2tau_OS[k]->Write();
       }
    }

    TDirectory *SS2jet =fout->mkdir("SSvbf");
    SS2jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if ((sample=="embedded" or sample=="data_obs") && k>0 && k<27) postfix=postfixQCD[k-1];
       else if (sample=="embedded" && k>26) postfix=postfixEmbedded[k-1-26];
       else if (!is_ggh && !is_qqh && k>60) postfix=postfixQCD[k-60-1];
       else if (is_ggh && k>60) postfix=postfixGGH[k-60-1];
       else if (is_qqh && k>60) postfix=postfixVBF[k-60-1];
       else postfix=postfixMC[k];
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h2tau_SS[k]->SetName(name.c_str()+strT+postfix);
          h2tau_SS[k]->Write();
          h2ell_SS[k]->SetName(name.c_str()+strL+postfix);
          h2ell_SS[k]->Write();
       }
       else{
          h2tau_SS[k]->Add(h2ell_SS[k]);
          h2tau_SS[k]->SetName(name.c_str()+postfix);
          h2tau_SS[k]->Write();
       }
    }

    TDirectory *AI2jet =fout->mkdir("AIvbf");
    AI2jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if ((sample=="embedded" or sample=="data_obs") && k>0 && k<27) postfix=postfixQCD[k-1];
       else if (sample=="embedded" && k>26) postfix=postfixEmbedded[k-1-26];
       else if (!is_ggh && !is_qqh && k>60) postfix=postfixQCD[k-60-1];
       else if (is_ggh && k>60) postfix=postfixGGH[k-60-1];
       else if (is_qqh && k>60) postfix=postfixVBF[k-60-1];
       else postfix=postfixMC[k];
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h2tau_AI[k]->SetName(name.c_str()+strT+postfix);
          h2tau_AI[k]->Write();
          h2ell_AI[k]->SetName(name.c_str()+strL+postfix);
          h2ell_AI[k]->Write();
       }
       else{
          h2tau_AI[k]->Add(h2ell_AI[k]);
          h2tau_AI[k]->SetName(name.c_str()+postfix);
          h2tau_AI[k]->Write();
       }
    }

    TDirectory *OS3jet =fout->mkdir("em_0jetlow");
    OS3jet->cd();
    h3_ttcontamination->SetName("ttcontamination");
    h3_ttcontamination->Write();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if ((sample=="embedded" or sample=="data_obs") && k>0 && k<27) postfix=postfixQCD[k-1];
       else if (sample=="embedded" && k>26) postfix=postfixEmbedded[k-1-26];
       else if (!is_ggh && !is_qqh && k>60) postfix=postfixQCD[k-60-1];
       else if (is_ggh && k>60) postfix=postfixGGH[k-60-1];
       else if (is_qqh && k>60) postfix=postfixVBF[k-60-1];
       else postfix=postfixMC[k];
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h3tau_OS[k]->SetName(name.c_str()+strT+postfix);
          h3tau_OS[k]->Write();
          h3ell_OS[k]->SetName(name.c_str()+strL+postfix);
          h3ell_OS[k]->Write();
       }
       else{
          h3tau_OS[k]->Add(h3ell_OS[k]);
          h3tau_OS[k]->SetName(name.c_str()+postfix);
          h3tau_OS[k]->Write();
       }
    }

    TDirectory *SS3jet =fout->mkdir("SS0jetlow");
    SS3jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if ((sample=="embedded" or sample=="data_obs") && k>0 && k<27) postfix=postfixQCD[k-1];
       else if (sample=="embedded" && k>26) postfix=postfixEmbedded[k-1-26];
       else if (!is_ggh && !is_qqh && k>60) postfix=postfixQCD[k-60-1];
       else if (is_ggh && k>60) postfix=postfixGGH[k-60-1];
       else if (is_qqh && k>60) postfix=postfixVBF[k-60-1];
       else postfix=postfixMC[k];
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h3tau_SS[k]->SetName(name.c_str()+strT+postfix);
          h3tau_SS[k]->Write();
          h3ell_SS[k]->SetName(name.c_str()+strL+postfix);
          h3ell_SS[k]->Write();
       }
       else{
          h3tau_SS[k]->Add(h3ell_SS[k]);
          h3tau_SS[k]->SetName(name.c_str()+postfix);
          h3tau_SS[k]->Write();
       }
    }

    TDirectory *AI3jet =fout->mkdir("AI0jetlow");
    AI3jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if ((sample=="embedded" or sample=="data_obs") && k>0 && k<27) postfix=postfixQCD[k-1];
       else if (sample=="embedded" && k>26) postfix=postfixEmbedded[k-1-26];
       else if (!is_ggh && !is_qqh && k>60) postfix=postfixQCD[k-60-1];
       else if (is_ggh && k>60) postfix=postfixGGH[k-60-1];
       else if (is_qqh && k>60) postfix=postfixVBF[k-60-1];
       else postfix=postfixMC[k];
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h3tau_AI[k]->SetName(name.c_str()+strT+postfix);
          h3tau_AI[k]->Write();
          h3ell_AI[k]->SetName(name.c_str()+strL+postfix);
          h3ell_AI[k]->Write();
       }
       else{
          h3tau_AI[k]->Add(h3ell_AI[k]);
          h3tau_AI[k]->SetName(name.c_str()+postfix);
          h3tau_AI[k]->Write();
       }
    }

    TDirectory *OS4jet =fout->mkdir("em_0jethigh");
    OS4jet->cd();
    h4_ttcontamination->SetName("ttcontamination");
    h4_ttcontamination->Write();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if ((sample=="embedded" or sample=="data_obs") && k>0 && k<27) postfix=postfixQCD[k-1];
       else if (sample=="embedded" && k>26) postfix=postfixEmbedded[k-1-26];
       else if (!is_ggh && !is_qqh && k>60) postfix=postfixQCD[k-60-1];
       else if (is_ggh && k>60) postfix=postfixGGH[k-60-1];
       else if (is_qqh && k>60) postfix=postfixVBF[k-60-1];
       else postfix=postfixMC[k];
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h4tau_OS[k]->SetName(name.c_str()+strT+postfix);
          h4tau_OS[k]->Write();
          h4ell_OS[k]->SetName(name.c_str()+strL+postfix);
          h4ell_OS[k]->Write();
       }
       else{
          h4tau_OS[k]->Add(h4ell_OS[k]);
          h4tau_OS[k]->SetName(name.c_str()+postfix);
          h4tau_OS[k]->Write();
       }
    }

    TDirectory *SS4jet =fout->mkdir("SS0jethigh");
    SS4jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if ((sample=="embedded" or sample=="data_obs") && k>0 && k<27) postfix=postfixQCD[k-1];
       else if (sample=="embedded" && k>26) postfix=postfixEmbedded[k-1-26];
       else if (!is_ggh && !is_qqh && k>60) postfix=postfixQCD[k-60-1];
       else if (is_ggh && k>60) postfix=postfixGGH[k-60-1];
       else if (is_qqh && k>60) postfix=postfixVBF[k-60-1];
       else postfix=postfixMC[k];
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h4tau_SS[k]->SetName(name.c_str()+strT+postfix);
          h4tau_SS[k]->Write();
          h4ell_SS[k]->SetName(name.c_str()+strL+postfix);
          h4ell_SS[k]->Write();
       }
       else{
          h4tau_SS[k]->Add(h4ell_SS[k]);
          h4tau_SS[k]->SetName(name.c_str()+postfix);
          h4tau_SS[k]->Write();
       }
    }

    TDirectory *AI4jet =fout->mkdir("AI0jethigh");
    AI4jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if ((sample=="embedded" or sample=="data_obs") && k>0 && k<27) postfix=postfixQCD[k-1];
       else if (sample=="embedded" && k>26) postfix=postfixEmbedded[k-1-26];
       else if (!is_ggh && !is_qqh && k>60) postfix=postfixQCD[k-60-1];
       else if (is_ggh && k>60) postfix=postfixGGH[k-60-1];
       else if (is_qqh && k>60) postfix=postfixVBF[k-60-1];
       else postfix=postfixMC[k];
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h4tau_AI[k]->SetName(name.c_str()+strT+postfix);
          h4tau_AI[k]->Write();
          h4ell_AI[k]->SetName(name.c_str()+strL+postfix);
          h4ell_AI[k]->Write();
       }
       else{
          h4tau_AI[k]->Add(h4ell_AI[k]);
          h4tau_AI[k]->SetName(name.c_str()+postfix);
          h4tau_AI[k]->Write();
       }
    }

    TDirectory *OS5jet =fout->mkdir("em_boosted1");
    OS5jet->cd();
    h5_ttcontamination->SetName("ttcontamination");
    h5_ttcontamination->Write();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if ((sample=="embedded" or sample=="data_obs") && k>0 && k<27) postfix=postfixQCD[k-1];
       else if (sample=="embedded" && k>26) postfix=postfixEmbedded[k-1-26];
       else if (!is_ggh && !is_qqh && k>60) postfix=postfixQCD[k-60-1];
       else if (is_ggh && k>60) postfix=postfixGGH[k-60-1];
       else if (is_qqh && k>60) postfix=postfixVBF[k-60-1];
       else postfix=postfixMC[k];
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h5tau_OS[k]->SetName(name.c_str()+strT+postfix);
          h5tau_OS[k]->Write();
          h5ell_OS[k]->SetName(name.c_str()+strL+postfix);
          h5ell_OS[k]->Write();
       }
       else{
          h5tau_OS[k]->Add(h5ell_OS[k]);
          h5tau_OS[k]->SetName(name.c_str()+postfix);
          h5tau_OS[k]->Write();
       }
    }

    TDirectory *SS5jet =fout->mkdir("SSboosted1");
    SS5jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if ((sample=="embedded" or sample=="data_obs") && k>0 && k<27) postfix=postfixQCD[k-1];
       else if (sample=="embedded" && k>26) postfix=postfixEmbedded[k-1-26];
       else if (!is_ggh && !is_qqh && k>60) postfix=postfixQCD[k-60-1];
       else if (is_ggh && k>60) postfix=postfixGGH[k-60-1];
       else if (is_qqh && k>60) postfix=postfixVBF[k-60-1];
       else postfix=postfixMC[k];
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h5tau_SS[k]->SetName(name.c_str()+strT+postfix);
          h5tau_SS[k]->Write();
          h5ell_SS[k]->SetName(name.c_str()+strL+postfix);
          h5ell_SS[k]->Write();
       }
       else{
          h5tau_SS[k]->Add(h5ell_SS[k]);
          h5tau_SS[k]->SetName(name.c_str()+postfix);
          h5tau_SS[k]->Write();
       }
    }

    TDirectory *AI5jet =fout->mkdir("AIboosted1");
    AI5jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if ((sample=="embedded" or sample=="data_obs") && k>0 && k<27) postfix=postfixQCD[k-1];
       else if (sample=="embedded" && k>26) postfix=postfixEmbedded[k-1-26];
       else if (!is_ggh && !is_qqh && k>60) postfix=postfixQCD[k-60-1];
       else if (is_ggh && k>60) postfix=postfixGGH[k-60-1];
       else if (is_qqh && k>60) postfix=postfixVBF[k-60-1];
       else postfix=postfixMC[k];
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h5tau_AI[k]->SetName(name.c_str()+strT+postfix);
          h5tau_AI[k]->Write();
          h5ell_AI[k]->SetName(name.c_str()+strL+postfix);
          h5ell_AI[k]->Write();
       }
       else{
          h5tau_AI[k]->Add(h5ell_AI[k]);
          h5tau_AI[k]->SetName(name.c_str()+postfix);
          h5tau_AI[k]->Write();
       }
    }

    TDirectory *OS6jet =fout->mkdir("em_boosted2");
    OS6jet->cd();
    h6_ttcontamination->SetName("ttcontamination");
    h6_ttcontamination->Write();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if ((sample=="embedded" or sample=="data_obs") && k>0 && k<27) postfix=postfixQCD[k-1];
       else if (sample=="embedded" && k>26) postfix=postfixEmbedded[k-1-26];
       else if (!is_ggh && !is_qqh && k>60) postfix=postfixQCD[k-60-1];
       else if (is_ggh && k>60) postfix=postfixGGH[k-60-1];
       else if (is_qqh && k>60) postfix=postfixVBF[k-60-1];
       else postfix=postfixMC[k];
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h6tau_OS[k]->SetName(name.c_str()+strT+postfix);
          h6tau_OS[k]->Write();
          h6ell_OS[k]->SetName(name.c_str()+strL+postfix);
          h6ell_OS[k]->Write();
       }
       else{
          h6tau_OS[k]->Add(h6ell_OS[k]);
          h6tau_OS[k]->SetName(name.c_str()+postfix);
          h6tau_OS[k]->Write();
       }
    }

    TDirectory *SS6jet =fout->mkdir("SSboosted2");
    SS6jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if ((sample=="embedded" or sample=="data_obs") && k>0 && k<27) postfix=postfixQCD[k-1];
       else if (sample=="embedded" && k>26) postfix=postfixEmbedded[k-1-26];
       else if (!is_ggh && !is_qqh && k>60) postfix=postfixQCD[k-60-1];
       else if (is_ggh && k>60) postfix=postfixGGH[k-60-1];
       else if (is_qqh && k>60) postfix=postfixVBF[k-60-1];
       else postfix=postfixMC[k];
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h6tau_SS[k]->SetName(name.c_str()+strT+postfix);
          h6tau_SS[k]->Write();
          h6ell_SS[k]->SetName(name.c_str()+strL+postfix);
          h6ell_SS[k]->Write();
       }
       else{
          h6tau_SS[k]->Add(h6ell_SS[k]);
          h6tau_SS[k]->SetName(name.c_str()+postfix);
          h6tau_SS[k]->Write();
       }
    }

    TDirectory *AI6jet =fout->mkdir("AIboosted2");
    AI6jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if ((sample=="embedded" or sample=="data_obs") && k>0 && k<27) postfix=postfixQCD[k-1];
       else if (sample=="embedded" && k>26) postfix=postfixEmbedded[k-1-26];
       else if (!is_ggh && !is_qqh && k>60) postfix=postfixQCD[k-60-1];
       else if (is_ggh && k>60) postfix=postfixGGH[k-60-1];
       else if (is_qqh && k>60) postfix=postfixVBF[k-60-1];
       else postfix=postfixMC[k];
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h6tau_AI[k]->SetName(name.c_str()+strT+postfix);
          h6tau_AI[k]->Write();
          h6ell_AI[k]->SetName(name.c_str()+strL+postfix);
          h6ell_AI[k]->Write();
       }
       else{
          h6tau_AI[k]->Add(h6ell_AI[k]);
          h6tau_AI[k]->SetName(name.c_str()+postfix);
          h6tau_AI[k]->Write();
       }
    }

    TDirectory *OS7jet =fout->mkdir("em_vbflow");
    OS7jet->cd();
    h7_ttcontamination->SetName("ttcontamination");
    h7_ttcontamination->Write();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if ((sample=="embedded" or sample=="data_obs") && k>0 && k<27) postfix=postfixQCD[k-1];
       else if (sample=="embedded" && k>26) postfix=postfixEmbedded[k-1-26];
       else if (!is_ggh && !is_qqh && k>60) postfix=postfixQCD[k-60-1];
       else if (is_ggh && k>60) postfix=postfixGGH[k-60-1];
       else if (is_qqh && k>60) postfix=postfixVBF[k-60-1];
       else postfix=postfixMC[k];
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h7tau_OS[k]->SetName(name.c_str()+strT+postfix);
          h7tau_OS[k]->Write();
          h7ell_OS[k]->SetName(name.c_str()+strL+postfix);
          h7ell_OS[k]->Write();
       }
       else{
          h7tau_OS[k]->Add(h7ell_OS[k]);
          h7tau_OS[k]->SetName(name.c_str()+postfix);
          h7tau_OS[k]->Write();
       }
    }

    TDirectory *SS7jet =fout->mkdir("SSvbflow");
    SS7jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if ((sample=="embedded" or sample=="data_obs") && k>0 && k<27) postfix=postfixQCD[k-1];
       else if (sample=="embedded" && k>26) postfix=postfixEmbedded[k-1-26];
       else if (!is_ggh && !is_qqh && k>60) postfix=postfixQCD[k-60-1];
       else if (is_ggh && k>60) postfix=postfixGGH[k-60-1];
       else if (is_qqh && k>60) postfix=postfixVBF[k-60-1];
       else postfix=postfixMC[k];
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h7tau_SS[k]->SetName(name.c_str()+strT+postfix);
          h7tau_SS[k]->Write();
          h7ell_SS[k]->SetName(name.c_str()+strL+postfix);
          h7ell_SS[k]->Write();
       }
       else{
          h7tau_SS[k]->Add(h7ell_SS[k]);
          h7tau_SS[k]->SetName(name.c_str()+postfix);
          h7tau_SS[k]->Write();
       }
    }

    TDirectory *AI7jet =fout->mkdir("AIvbflow");
    AI7jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if ((sample=="embedded" or sample=="data_obs") && k>0 && k<27) postfix=postfixQCD[k-1];
       else if (sample=="embedded" && k>26) postfix=postfixEmbedded[k-1-26];
       else if (!is_ggh && !is_qqh && k>60) postfix=postfixQCD[k-60-1];
       else if (is_ggh && k>60) postfix=postfixGGH[k-60-1];
       else if (is_qqh && k>60) postfix=postfixVBF[k-60-1];
       else postfix=postfixMC[k];
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h7tau_AI[k]->SetName(name.c_str()+strT+postfix);
          h7tau_AI[k]->Write();
          h7ell_AI[k]->SetName(name.c_str()+strL+postfix);
          h7ell_AI[k]->Write();
       }
       else{
          h7tau_AI[k]->Add(h7ell_AI[k]);
          h7tau_AI[k]->SetName(name.c_str()+postfix);
          h7tau_AI[k]->Write();
       }
    }

    TDirectory *OS8jet =fout->mkdir("em_vbfhigh");
    OS8jet->cd();
    h8_ttcontamination->SetName("ttcontamination");
    h8_ttcontamination->Write();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if ((sample=="embedded" or sample=="data_obs") && k>0 && k<27) postfix=postfixQCD[k-1];
       else if (sample=="embedded" && k>26) postfix=postfixEmbedded[k-1-26];
       else if (!is_ggh && !is_qqh && k>60) postfix=postfixQCD[k-60-1];
       else if (is_ggh && k>60) postfix=postfixGGH[k-60-1];
       else if (is_qqh && k>60) postfix=postfixVBF[k-60-1];
       else postfix=postfixMC[k];
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h8tau_OS[k]->SetName(name.c_str()+strT+postfix);
          h8tau_OS[k]->Write();
          h8ell_OS[k]->SetName(name.c_str()+strL+postfix);
          h8ell_OS[k]->Write();
       }
       else{
          h8tau_OS[k]->Add(h8ell_OS[k]);
          h8tau_OS[k]->SetName(name.c_str()+postfix);
          h8tau_OS[k]->Write();
       }
    }

    TDirectory *SS8jet =fout->mkdir("SSvbfhigh");
    SS8jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if ((sample=="embedded" or sample=="data_obs") && k>0 && k<27) postfix=postfixQCD[k-1];
       else if (sample=="embedded" && k>26) postfix=postfixEmbedded[k-1-26];
       else if (!is_ggh && !is_qqh && k>60) postfix=postfixQCD[k-60-1];
       else if (is_ggh && k>60) postfix=postfixGGH[k-60-1];
       else if (is_qqh && k>60) postfix=postfixVBF[k-60-1];
       else postfix=postfixMC[k];
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h8tau_SS[k]->SetName(name.c_str()+strT+postfix);
          h8tau_SS[k]->Write();
          h8ell_SS[k]->SetName(name.c_str()+strL+postfix);
          h8ell_SS[k]->Write();
       }
       else{
          h8tau_SS[k]->Add(h8ell_SS[k]);
          h8tau_SS[k]->SetName(name.c_str()+postfix);
          h8tau_SS[k]->Write();
       }
    }

    TDirectory *AI8jet =fout->mkdir("AIvbfhigh");
    AI8jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if ((sample=="embedded" or sample=="data_obs") && k>0 && k<27) postfix=postfixQCD[k-1];
       else if (sample=="embedded" && k>26) postfix=postfixEmbedded[k-1-26];
       else if (!is_ggh && !is_qqh && k>60) postfix=postfixQCD[k-60-1];
       else if (is_ggh && k>60) postfix=postfixGGH[k-60-1];
       else if (is_qqh && k>60) postfix=postfixVBF[k-60-1];
       else postfix=postfixMC[k];
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h8tau_AI[k]->SetName(name.c_str()+strT+postfix);
          h8tau_AI[k]->Write();
          h8ell_AI[k]->SetName(name.c_str()+strL+postfix);
          h8ell_AI[k]->Write();
       }
       else{
          h8tau_AI[k]->Add(h8ell_AI[k]);
          h8tau_AI[k]->SetName(name.c_str()+postfix);
          h8tau_AI[k]->Write();
       }
    }

    cout<<h0tau_OS[0]->Integral()<<" "<<h7tau_OS[0]->Integral()<<" "<<h8tau_OS[0]->Integral()<<endl;
    fout->Close();
    delete wmc;
} 


