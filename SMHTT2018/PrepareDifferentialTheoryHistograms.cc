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
#include "LumiReweightingStandAlone.h"
#include "tr_Tree.h"
#include "ComputeWG1Unc.h"
#include "qq2Hqq_uncert_scheme.h"

using namespace std;

int main(int argc, char** argv) {

    std::string input = *(argv + 1);
    std::string output = *(argv + 2);
    std::string sample = *(argv + 3);
    std::string name = *(argv + 4);

    TFile *f_Double = new TFile(input.c_str());
    cout<<"XXXXXXXXXXXXX "<<input.c_str()<<" XXXXXXXXXXXX"<<endl;
    TTree *arbre = (TTree*) f_Double->Get("demo/tr_tree");
    arbre->SetBranchAddress("Rivet_higgsPt", &Rivet_higgsPt);
    arbre->SetBranchAddress("Rivet_njets", &Rivet_njets);
    arbre->SetBranchAddress("Rivet_stage1cat", &Rivet_stage1cat);
    arbre->SetBranchAddress("Rivet_stage1cat_fine", &Rivet_stage1cat_fine);
    arbre->SetBranchAddress("Rivet_jetPt", &Rivet_jetPt);
    arbre->SetBranchAddress("Rivet_mjj", &Rivet_mjj);
    arbre->SetBranchAddress("muR1muF1", &muR1muF1);
    arbre->SetBranchAddress("muR0p5muF0p5", &muR0p5muF0p5);
    arbre->SetBranchAddress("muR2muF2", &muR2muF2);
    arbre->SetBranchAddress("fulltau1phi", &fulltau1phi);
    arbre->SetBranchAddress("fulltau1eta", &fulltau1eta);
    arbre->SetBranchAddress("fulltau1pt", &fulltau1pt);
    arbre->SetBranchAddress("fulltau2phi", &fulltau2phi);
    arbre->SetBranchAddress("fulltau2eta", &fulltau2eta);
    arbre->SetBranchAddress("fulltau2pt", &fulltau2pt);
    arbre->SetBranchAddress("vistau1_phi", &vistau1_phi);
    arbre->SetBranchAddress("vistau1_eta", &vistau1_eta);
    arbre->SetBranchAddress("vistau1_pt", &vistau1_pt);
    arbre->SetBranchAddress("vistau2_phi", &vistau2_phi);
    arbre->SetBranchAddress("vistau2_eta", &vistau2_eta);
    arbre->SetBranchAddress("vistau2_pt", &vistau2_pt);
    arbre->SetBranchAddress("finalstate", &finalstate);
    arbre->SetBranchAddress("dressedElectron_pt", &dressedElectron_pt);
    arbre->SetBranchAddress("dressedElectron_eta", &dressedElectron_eta);
    arbre->SetBranchAddress("dressedElectron_phi", &dressedElectron_phi);
    arbre->SetBranchAddress("dressedMuon_pt", &dressedMuon_pt);
    arbre->SetBranchAddress("dressedMuon_eta", &dressedMuon_eta);
    arbre->SetBranchAddress("dressedMuon_phi", &dressedMuon_phi);
    arbre->SetBranchAddress("genMetPt", &genMetPt);
    arbre->SetBranchAddress("genMetPhi", &genMetPhi);

    TH1D* nbevt = (TH1D*) f_Double->Get("demo/h_count_powheg");
    float ngen = nbevt->GetBinContent(1);
    float xs=1.0; float weight=1.0; float luminosity=1.0;
    if (sample=="ggH_htt125") {xs=48.3138*0.0621104; weight=luminosity*xs/ngen;}
    else if (sample=="ggH") {xs=48.3138*0.0621104; weight=luminosity*xs/ngen;}
    else if (sample=="qqH_htt125") {xs=3.77061*0.0621104; weight=luminosity*xs/ngen;}
    else if (sample=="qqH") {xs=3.77061*0.0621104; weight=luminosity*xs/ngen;}
    else if (sample=="WplusH125") {xs=0.83173*0.0621104; weight=luminosity*xs/ngen;}
    else if (sample=="WminusH125") {xs=0.527404*0.0621104; weight=luminosity*xs/ngen;}
    else if (sample=="ZH125") {xs=0.754723*0.0621104; weight=luminosity*xs/ngen;}
    else if (sample=="ttHTT") {xs=0.503472*0.0621104; weight=luminosity*xs/ngen;}
    else if (sample=="ttHTT125") {xs=0.503472*0.0621104; weight=luminosity*xs/ngen;}
    else if (sample=="GGZH125") {xs=0.122349*0.0621104; weight=luminosity*xs/ngen;}
    else if (sample=="GGZHLLTT125") {xs=0.122349*0.0621104*3*0.033658; weight=luminosity*xs/ngen;}
    else if (sample=="GGZHNNTT125") {xs=0.122349*0.0621104*0.2000; weight=luminosity*xs/ngen;}
    else if (sample=="GGZHQQTT125") {xs=0.122349*0.0621104*0.6991; weight=luminosity*xs/ngen;}


    TFile * f_NNLOPS = new TFile("NNLOPS_reweight.root");
    TGraph * g_NNLOPS_0jet = (TGraph*) f_NNLOPS-> Get("gr_NNLOPSratio_pt_powheg_0jet");
    TGraph * g_NNLOPS_1jet = (TGraph*) f_NNLOPS-> Get("gr_NNLOPSratio_pt_powheg_1jet");
    TGraph * g_NNLOPS_2jet = (TGraph*) f_NNLOPS-> Get("gr_NNLOPSratio_pt_powheg_2jet");
    TGraph * g_NNLOPS_3jet = (TGraph*) f_NNLOPS-> Get("gr_NNLOPSratio_pt_powheg_3jet");

    float bins_mjj[] = {0,150,300,450,600,1000,1400,1800,2000};
    int  binnum_mjj = sizeof(bins_mjj)/sizeof(Float_t) - 1;
    float bins_jpt[] = {0,30,60,120,200,350,400};
    int  binnum_jpt = sizeof(bins_jpt)/sizeof(Float_t) - 1;
    float bins_fs[] = {1,2,3,4,5};
    int  binnum_fs = sizeof(bins_fs)/sizeof(Float_t) - 1;
    float bins_hpt[] = {0,45,80,120,200,350,450,550};
    int  binnum_hpt = sizeof(bins_hpt)/sizeof(Float_t) - 1;
    float bins_njets[] = {0,1,2,3,4,5};
    int  binnum_njets = sizeof(bins_njets)/sizeof(Float_t) - 1;

    std::vector<TH1F*> h_mjj_powheg;
    std::vector<TH1F*> h_hpt_powheg;
    std::vector<TH1F*> h_njets_powheg;
    std::vector<TH1F*> h_njets_powheg_em;
    std::vector<TH1F*> h_njets_powheg_et;
    std::vector<TH1F*> h_njets_powheg_mt;
    std::vector<TH1F*> h_njets_powheg_tt;
    std::vector<TH1F*> h_jpt_powheg;
    std::vector<TH1F*> h_fs_powheg;

    std::vector<TH1F*> h_mjj_powheg_nnlops;
    std::vector<TH1F*> h_hpt_powheg_nnlops;
    std::vector<TH1F*> h_njets_powheg_nnlops;
    std::vector<TH1F*> h_njets_powheg_nnlops_em;
    std::vector<TH1F*> h_njets_powheg_nnlops_et;
    std::vector<TH1F*> h_njets_powheg_nnlops_mt;
    std::vector<TH1F*> h_njets_powheg_nnlops_tt;
    std::vector<TH1F*> h_jpt_powheg_nnlops;
    std::vector<TH1F*> h_fs_powheg_nnlops;

    int nbhist=11;

    for (int k=0; k<nbhist; ++k){
        ostringstream HNS0tauOS; HNS0tauOS << "h0tau_OS" << k;
        h_mjj_powheg.push_back(new TH1F (HNS0tauOS.str().c_str(),"InvMa",binnum_mjj,bins_mjj)); h_mjj_powheg[k]->Sumw2();
        ostringstream HNS1tauOS; HNS1tauOS << "h1tau_OS" << k;
        h_hpt_powheg.push_back(new TH1F (HNS1tauOS.str().c_str(),"InvMa",binnum_hpt,bins_hpt)); h_hpt_powheg[k]->Sumw2();
        ostringstream HNS2tauOS; HNS2tauOS << "h2tau_OS" << k;
        h_njets_powheg.push_back(new TH1F (HNS2tauOS.str().c_str(),"InvMa",binnum_njets,bins_njets)); h_njets_powheg[k]->Sumw2();
        ostringstream HNS2tauOS_em; HNS2tauOS_em << "h2tau_OS_em" << k;
        h_njets_powheg_em.push_back(new TH1F (HNS2tauOS_em.str().c_str(),"InvMa",binnum_njets,bins_njets)); h_njets_powheg_em[k]->Sumw2();
        ostringstream HNS2tauOS_et; HNS2tauOS_et << "h2tau_OS_et" << k;
        h_njets_powheg_et.push_back(new TH1F (HNS2tauOS_et.str().c_str(),"InvMa",binnum_njets,bins_njets)); h_njets_powheg_et[k]->Sumw2();
        ostringstream HNS2tauOS_mt; HNS2tauOS_mt << "h2tau_OS_mt" << k;
        h_njets_powheg_mt.push_back(new TH1F (HNS2tauOS_mt.str().c_str(),"InvMa",binnum_njets,bins_njets)); h_njets_powheg_mt[k]->Sumw2();
        ostringstream HNS2tauOS_tt; HNS2tauOS_tt << "h2tau_OS_tt" << k;
        h_njets_powheg_tt.push_back(new TH1F (HNS2tauOS_tt.str().c_str(),"InvMa",binnum_njets,bins_njets)); h_njets_powheg_tt[k]->Sumw2();
        ostringstream HNS3tauOS; HNS3tauOS << "h3tau_OS" << k;
        h_jpt_powheg.push_back(new TH1F (HNS3tauOS.str().c_str(),"InvMa",binnum_jpt,bins_jpt)); h_jpt_powheg[k]->Sumw2();
        ostringstream HNS4tauOS; HNS4tauOS << "h4tau_OS" << k;
        h_fs_powheg.push_back(new TH1F (HNS4tauOS.str().c_str(),"InvMa",binnum_fs,bins_fs)); h_fs_powheg[k]->Sumw2();

        ostringstream HNS5tauOS; HNS5tauOS << "h5tau_OS" << k;
        h_mjj_powheg_nnlops.push_back(new TH1F (HNS5tauOS.str().c_str(),"InvMa",binnum_mjj,bins_mjj)); h_mjj_powheg_nnlops[k]->Sumw2();
        ostringstream HNS6tauOS; HNS6tauOS << "h6tau_OS" << k;
        h_hpt_powheg_nnlops.push_back(new TH1F (HNS6tauOS.str().c_str(),"InvMa",binnum_hpt,bins_hpt)); h_hpt_powheg_nnlops[k]->Sumw2();
        ostringstream HNS7tauOS; HNS7tauOS << "h7tau_OS" << k;
        h_njets_powheg_nnlops.push_back(new TH1F (HNS7tauOS.str().c_str(),"InvMa",binnum_njets,bins_njets)); h_njets_powheg_nnlops[k]->Sumw2();
        ostringstream HNS7tauOS_em; HNS7tauOS_em << "h7tau_OS_em" << k;
        h_njets_powheg_nnlops_em.push_back(new TH1F (HNS7tauOS_em.str().c_str(),"InvMa",binnum_njets,bins_njets)); h_njets_powheg_nnlops_em[k]->Sumw2();
        ostringstream HNS7tauOS_et; HNS7tauOS_et << "h7tau_OS_et" << k;
        h_njets_powheg_nnlops_et.push_back(new TH1F (HNS7tauOS_et.str().c_str(),"InvMa",binnum_njets,bins_njets)); h_njets_powheg_nnlops_et[k]->Sumw2();
        ostringstream HNS7tauOS_mt; HNS7tauOS_mt << "h7tau_OS_mt" << k;
        h_njets_powheg_nnlops_mt.push_back(new TH1F (HNS7tauOS_mt.str().c_str(),"InvMa",binnum_njets,bins_njets)); h_njets_powheg_nnlops_mt[k]->Sumw2();
        ostringstream HNS7tauOS_tt; HNS7tauOS_tt << "h7tau_OS_tt" << k;
        h_njets_powheg_nnlops_tt.push_back(new TH1F (HNS7tauOS_tt.str().c_str(),"InvMa",binnum_njets,bins_njets)); h_njets_powheg_nnlops_tt[k]->Sumw2();
        ostringstream HNS8tauOS; HNS8tauOS << "h8tau_OS" << k;
        h_jpt_powheg_nnlops.push_back(new TH1F (HNS8tauOS.str().c_str(),"InvMa",binnum_jpt,bins_jpt)); h_jpt_powheg_nnlops[k]->Sumw2();
        ostringstream HNS9tauOS; HNS9tauOS << "h9tau_OS" << k;
        h_fs_powheg_nnlops.push_back(new TH1F (HNS9tauOS.str().c_str(),"InvMa",binnum_fs,bins_fs)); h_fs_powheg_nnlops[k]->Sumw2();
    }
   TString postfix[11]={"","_THU_ggH_Mu","_THU_ggH_Res","_THU_ggH_Mig01","_THU_ggH_Mig12","_THU_ggH_VBF2j","_THU_ggH_VBF3j","_THU_ggH_PT60","_THU_ggH_PT120","_THU_ggH_qmtop","_scale"};


    TH1F* h_stage1cat=new TH1F("h_stage1cat","h_stage1cat",800,1,801);

    TH1F* h_THUggH = new TH1F("h_THUggH","h_THUggH",20,0,20);
    TH1F* h_THUqqH = new TH1F("h_THUqqH","h_THUqqH",22,0,22);

    // THU ggH stage-1
    TH1F* h_THUggH_r_ggH_PTH_0_200_GE2J = new TH1F("h_THUggH_r_ggH_PTH_0_200_GE2J","h_THUggH_r_ggH_PTH_0_200_GE2J",20,0,20);
    TH1F* h_THUggH_r_ggH_PTH_200_300 = new TH1F("h_THUggH_r_ggH_PTH_200_300","h_THUggH_r_ggH_PTH_200_300",20,0,20);
    TH1F* h_THUggH_r_ggH_PTH_GE300 = new TH1F("h_THUggH_r_ggH_PTH_GE300","h_THUggH_r_ggH_PTH_GE300",20,0,20);
    TH1F* h_THUggH_r_ggH_0J = new TH1F("h_THUggH_r_ggH_0J","h_THUggH_r_ggH_0J",20,0,20);
    TH1F* h_THUggH_r_ggH_1J_PTH_0_60 = new TH1F("h_THUggH_r_ggH_1J_PTH_0_60","h_THUggH_r_ggH_1J_PTH_0_60",20,0,20);
    TH1F* h_THUggH_r_ggH_1J_PTH_60_120 = new TH1F("h_THUggH_r_ggH_1J_PTH_60_120","h_THUggH_r_ggH_1J_PTH_60_120",20,0,20);
    TH1F* h_THUggH_r_ggH_1J_PTH_120_200 = new TH1F("h_THUggH_r_ggH_1J_PTH_120_200","h_THUggH_r_ggH_1J_PTH_120_200",20,0,20);
    TH1F* h_THUggH_r_VBFTOPO_MJJ_350_700 = new TH1F("h_THUggH_r_VBFTOPO_MJJ_350_700","h_THUggH_r_VBFTOPO_MJJ_350_700",20,0,20);
    TH1F* h_THUggH_r_VBFTOPO_MJJ_GE700 = new TH1F("h_THUggH_r_VBFTOPO_MJJ_GE700","h_THUggH_r_VBFTOPO_MJJ_GE700",20,0,20);
    TH1F* h_THUggH_r_ggH_PTH_0_200_GE2J_MJJ_0_350 = new TH1F("h_THUggH_r_ggH_PTH_0_200_GE2J_MJJ_0_350","h_THUggH_r_ggH_PTH_0_200_GE2J_MJJ_0_350",20,0,20);

    TH1F* h_THUqqH_r_qqH_NONVBFTOPO = new TH1F("h_THUqqH_r_qqH_NONVBFTOPO","h_THUqqH_r_qqH_NONVBFTOPO",22,0,22);
    TH1F* h_THUqqH_r_qqH_GE2J_MJJ_350_700_PTH_0_200 = new TH1F("h_THUqqH_r_qqH_GE2J_MJJ_350_700_PTH_0_200","h_THUqqH_r_qqH_GE2J_MJJ_350_700_PTH_0_200",22,0,22);
    TH1F* h_THUqqH_r_qqH_GE2J_MJJ_GE700_PTH_0_200 = new TH1F("h_THUqqH_r_qqH_GE2J_MJJ_GE700_PTH_0_200","h_THUqqH_r_qqH_GE2J_MJJ_GE700_PTH_0_200",22,0,22);
    TH1F* h_THUqqH_r_qqH_BSM = new TH1F("h_THUqqH_r_qqH_BSM","h_THUqqH_r_qqH_BSM",22,0,22);

    Int_t nentries_wtn = (Int_t) arbre->GetEntries();
    for (Int_t i = 0; i < nentries_wtn; i++) {
        arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);
Rivet_stage1cat_fine=200; //FIXME

	float nnlops_weight=1.0;
        if (name=="ggH_htt125"){
          if (Rivet_njets==0) nnlops_weight= g_NNLOPS_0jet->Eval(min(Rivet_higgsPt,float(125.0)));
          if (Rivet_njets==1) nnlops_weight= g_NNLOPS_1jet->Eval(min(Rivet_higgsPt,float(625.0)));
          if (Rivet_njets==2) nnlops_weight= g_NNLOPS_2jet->Eval(min(Rivet_higgsPt,float(800.0)));
          if (Rivet_njets>=3) nnlops_weight= g_NNLOPS_3jet->Eval(min(Rivet_higgsPt,float(925.0)));
	}
        NumV WG1unc = qcd_ggF_uncert_2017(Rivet_njets, Rivet_higgsPt, Rivet_stage1cat);

   	if (Rivet_njets>4) Rivet_njets=4;
   	if (Rivet_mjj>2000) Rivet_mjj=1999;
   	if (Rivet_higgsPt>550) Rivet_higgsPt=549;
   	if (Rivet_jetPt>400) Rivet_jetPt=399;
        if (Rivet_jetPt<30) Rivet_jetPt=15;

	int cat=Rivet_stage1cat;
	if (Rivet_stage1cat<200){
	   if (Rivet_stage1cat==100) cat=100;
	   if (Rivet_stage1cat==101 and Rivet_higgsPt>=200 and Rivet_higgsPt<300) cat=101;
           if (Rivet_stage1cat==101 and Rivet_higgsPt>=300 and Rivet_higgsPt<450) cat=102;
           if (Rivet_stage1cat==101 and Rivet_higgsPt>=450 and Rivet_higgsPt<650) cat=103;
           if (Rivet_stage1cat==101 and Rivet_higgsPt>=650) cat=104;
	   if (Rivet_stage1cat==102) cat=105;
           if (Rivet_stage1cat==103) cat=106;
           if (Rivet_stage1cat==104) cat=107;
           if (Rivet_stage1cat==105) cat=108;
           if (Rivet_stage1cat==106) cat=109;
           if (Rivet_stage1cat==107) cat=110;
           if (Rivet_stage1cat==108) cat=111;
           if (Rivet_stage1cat==109) cat=112;
           if (Rivet_stage1cat==110) cat=113;
           if (Rivet_stage1cat==111) cat=114;
           if (Rivet_stage1cat==112) cat=115;
           if (Rivet_stage1cat==113) cat=116;
	}
	Rivet_stage1cat = cat;

	TLorentzVector mymet;
	TLorentzVector myelectron;
	TLorentzVector mymuon;
	TLorentzVector mytau;
        TLorentzVector mytau1;
        TLorentzVector mytau2;
	mymet.SetPtEtaPhiM(genMetPt,0,genMetPhi,0);
	myelectron.SetPtEtaPhiM(dressedElectron_pt,dressedElectron_eta,dressedElectron_phi,0);
        mymuon.SetPtEtaPhiM(dressedMuon_pt,dressedMuon_eta,dressedMuon_phi,0);
        mytau.SetPtEtaPhiM(vistau1_pt,vistau1_eta,vistau1_phi,0);
        mytau1.SetPtEtaPhiM(vistau1_pt,vistau1_eta,vistau1_phi,0);
        mytau2.SetPtEtaPhiM(vistau2_pt,vistau2_eta,vistau2_phi,0);
	if (finalstate==2 and myelectron.DeltaR(mytau1)<myelectron.DeltaR(mytau2)) mytau=mytau2;
        if (finalstate==2 and myelectron.DeltaR(mytau1)>myelectron.DeltaR(mytau2)) mytau=mytau1;
        if (finalstate==3 and mymuon.DeltaR(mytau1)<mymuon.DeltaR(mytau2)) mytau=mytau2;
        if (finalstate==3 and mymuon.DeltaR(mytau1)>mymuon.DeltaR(mytau2)) mytau=mytau1;

	float mt_emu=-1;
	float mt_etau=-1;
	float mt_mutau=-1;
	if (finalstate==1) mt_emu=TMass_F((myelectron+mymuon).Pt(),mymet.Pt(),(myelectron+mymuon).Px(),mymet.Px(),(myelectron+mymuon).Py(),mymet.Py());
        if (finalstate==2) mt_etau=TMass_F(myelectron.Pt(),mymet.Pt(),myelectron.Px(),mymet.Px(),myelectron.Py(),mymet.Py());
        if (finalstate==3) mt_etau=TMass_F(mymuon.Pt(),mymet.Pt(),mymuon.Px(),mymet.Px(),mymuon.Py(),mymet.Py());

	bool is_fiducial=false; 
	//is_fiducial=(tau1pt>25 && tau2pt>25 && fabs(tau1eta)<2.5 && fabs(tau2eta)<2.5);
	if (finalstate==1 and myelectron.DeltaR(mymuon)>0.3 and mt_emu<60 and (dressedElectron_pt>24 or dressedMuon_pt>24) and dressedElectron_pt>15 and dressedMuon_pt>25 and fabs(dressedElectron_eta)<2.4 and fabs(dressedMuon_eta)<2.4) is_fiducial=true; //emu
        if (finalstate==2 and myelectron.DeltaR(mytau)>0.5 and mt_etau<50 and dressedElectron_pt>25 and vistau1_pt>30 and fabs(dressedElectron_eta)<2.1 and fabs(vistau1_eta)<2.3) is_fiducial=true; //etau
        if (finalstate==3 and mymuon.DeltaR(mytau)>0.5 and mt_mutau<50 and dressedMuon_pt>20 and vistau1_pt>30 and fabs(dressedMuon_eta)<2.1 and fabs(vistau1_eta)<2.3) is_fiducial=true; //mutau
        if (finalstate==4 and mytau1.DeltaR(mytau2)>0.5 and vistau1_pt>40 and vistau2_pt>40 and fabs(vistau1_eta)<2.1 and fabs(vistau2_eta)<2.1 and Rivet_njets>0) is_fiducial=true; //tautau

	if (is_fiducial){
	   h_njets_powheg[0]->Fill(Rivet_njets,weight);
	   if (finalstate==1) h_njets_powheg_em[0]->Fill(Rivet_njets,weight);
           if (finalstate==2) h_njets_powheg_et[0]->Fill(Rivet_njets,weight);
           if (finalstate==3) h_njets_powheg_mt[0]->Fill(Rivet_njets,weight);
           if (finalstate==4) h_njets_powheg_tt[0]->Fill(Rivet_njets,weight);
           h_hpt_powheg[0]->Fill(Rivet_higgsPt,weight);
           h_jpt_powheg[0]->Fill(Rivet_jetPt,weight);
           h_mjj_powheg[0]->Fill(Rivet_mjj,weight);
           h_fs_powheg[0]->Fill(finalstate,weight);

           h_njets_powheg_nnlops[0]->Fill(Rivet_njets,weight*nnlops_weight);
	   if (finalstate==1) h_njets_powheg_nnlops_em[0]->Fill(Rivet_njets,weight*nnlops_weight);
           if (finalstate==2) h_njets_powheg_nnlops_et[0]->Fill(Rivet_njets,weight*nnlops_weight);
           if (finalstate==3) h_njets_powheg_nnlops_mt[0]->Fill(Rivet_njets,weight*nnlops_weight);
           if (finalstate==4) h_njets_powheg_nnlops_tt[0]->Fill(Rivet_njets,weight*nnlops_weight);
           h_hpt_powheg_nnlops[0]->Fill(Rivet_higgsPt,weight*nnlops_weight);
           h_jpt_powheg_nnlops[0]->Fill(Rivet_jetPt,weight*nnlops_weight);
           h_mjj_powheg_nnlops[0]->Fill(Rivet_mjj,weight*nnlops_weight);
           h_fs_powheg_nnlops[0]->Fill(finalstate,weight*nnlops_weight);

           for (int j=0; j<9; ++j){
	      float thuweight=(1+WG1unc[j]);
              h_njets_powheg[j+1]->Fill(Rivet_njets,weight*thuweight);
	      if (finalstate==1) h_njets_powheg_em[j+1]->Fill(Rivet_njets,weight*thuweight);
              if (finalstate==2) h_njets_powheg_et[j+1]->Fill(Rivet_njets,weight*thuweight);
              if (finalstate==3) h_njets_powheg_mt[j+1]->Fill(Rivet_njets,weight*thuweight);
              if (finalstate==4) h_njets_powheg_tt[j+1]->Fill(Rivet_njets,weight*thuweight);
              h_hpt_powheg[j+1]->Fill(Rivet_higgsPt,weight*thuweight);
              h_jpt_powheg[j+1]->Fill(Rivet_jetPt,weight*thuweight);
              h_mjj_powheg[j+1]->Fill(Rivet_mjj,weight*thuweight);
              h_fs_powheg[j+1]->Fill(finalstate,weight*thuweight);

              h_njets_powheg_nnlops[j+1]->Fill(Rivet_njets,weight*nnlops_weight*thuweight);
	      if (finalstate==1) h_njets_powheg_nnlops_em[j+1]->Fill(Rivet_njets,weight*nnlops_weight*thuweight);
              if (finalstate==2) h_njets_powheg_nnlops_et[j+1]->Fill(Rivet_njets,weight*nnlops_weight*thuweight);
              if (finalstate==3) h_njets_powheg_nnlops_mt[j+1]->Fill(Rivet_njets,weight*nnlops_weight*thuweight);
              if (finalstate==4) h_njets_powheg_nnlops_tt[j+1]->Fill(Rivet_njets,weight*nnlops_weight*thuweight);
              h_hpt_powheg_nnlops[j+1]->Fill(Rivet_higgsPt,weight*nnlops_weight*thuweight);
              h_jpt_powheg_nnlops[j+1]->Fill(Rivet_jetPt,weight*nnlops_weight*thuweight);
              h_mjj_powheg_nnlops[j+1]->Fill(Rivet_mjj,weight*nnlops_weight*thuweight);
              h_fs_powheg_nnlops[j+1]->Fill(finalstate,weight*nnlops_weight*thuweight);
           }
           h_njets_powheg[10]->Fill(Rivet_njets,weight*muR0p5muF0p5);
	   if (finalstate==1) h_njets_powheg_em[10]->Fill(Rivet_njets,weight*muR0p5muF0p5);
           if (finalstate==2) h_njets_powheg_et[10]->Fill(Rivet_njets,weight*muR0p5muF0p5);
           if (finalstate==3) h_njets_powheg_mt[10]->Fill(Rivet_njets,weight*muR0p5muF0p5);
           if (finalstate==4) h_njets_powheg_tt[10]->Fill(Rivet_njets,weight*muR0p5muF0p5);
           h_hpt_powheg[10]->Fill(Rivet_higgsPt,weight*muR0p5muF0p5);
           h_jpt_powheg[10]->Fill(Rivet_jetPt,weight*muR0p5muF0p5);
           h_mjj_powheg[10]->Fill(Rivet_mjj,weight*muR0p5muF0p5);
           h_fs_powheg[10]->Fill(finalstate,weight*muR0p5muF0p5);
           h_njets_powheg_nnlops[10]->Fill(Rivet_njets,weight*nnlops_weight*muR0p5muF0p5);
	   if (finalstate==1) h_njets_powheg_nnlops_em[10]->Fill(Rivet_njets,weight*nnlops_weight*muR0p5muF0p5);
           if (finalstate==2) h_njets_powheg_nnlops_et[10]->Fill(Rivet_njets,weight*nnlops_weight*muR0p5muF0p5);
           if (finalstate==3) h_njets_powheg_nnlops_mt[10]->Fill(Rivet_njets,weight*nnlops_weight*muR0p5muF0p5);
           if (finalstate==4) h_njets_powheg_nnlops_tt[10]->Fill(Rivet_njets,weight*nnlops_weight*muR0p5muF0p5);
           h_hpt_powheg_nnlops[10]->Fill(Rivet_higgsPt,weight*nnlops_weight*muR0p5muF0p5);
           h_jpt_powheg_nnlops[10]->Fill(Rivet_jetPt,weight*nnlops_weight*muR0p5muF0p5);
           h_mjj_powheg_nnlops[10]->Fill(Rivet_mjj,weight*nnlops_weight*muR0p5muF0p5);
           h_fs_powheg_nnlops[10]->Fill(finalstate,weight*nnlops_weight*muR0p5muF0p5);
	}
	h_stage1cat->Fill(Rivet_stage1cat,weight*nnlops_weight);

	h_THUggH->Fill(0.,nnlops_weight);
	for (int j=0; j<9; ++j){
	   h_THUggH->Fill(2*j+1.,nnlops_weight*(1+WG1unc[j]));
           h_THUggH->Fill(2*j+2.,nnlops_weight*(1-WG1unc[j]));
	}
        h_THUqqH->Fill(0.,1.0);
        for (int j=0; j<10; ++j){
           h_THUqqH->Fill(2*j+1.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), 1.0));
           h_THUqqH->Fill(2*j+2.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), -1.0));
        }


	if (cat>=110 && cat<=116){
           h_THUggH_r_ggH_PTH_0_200_GE2J->Fill(0.,nnlops_weight);
           for (int j=0; j<9; ++j){
              h_THUggH_r_ggH_PTH_0_200_GE2J->Fill(2*j+1.,nnlops_weight*(1+WG1unc[j]));
              h_THUggH_r_ggH_PTH_0_200_GE2J->Fill(2*j+2.,nnlops_weight*(1-WG1unc[j]));
           }
	}
        if (cat==101){
           h_THUggH_r_ggH_PTH_200_300->Fill(0.,nnlops_weight);
           for (int j=0; j<9; ++j){
              h_THUggH_r_ggH_PTH_200_300->Fill(2*j+1.,nnlops_weight*(1+WG1unc[j]));
              h_THUggH_r_ggH_PTH_200_300->Fill(2*j+2.,nnlops_weight*(1-WG1unc[j]));
           }
        }
        if (cat==102 or cat==103 or cat==104){
           h_THUggH_r_ggH_PTH_GE300->Fill(0.,nnlops_weight);
           for (int j=0; j<9; ++j){
              h_THUggH_r_ggH_PTH_GE300->Fill(2*j+1.,nnlops_weight*(1+WG1unc[j]));
              h_THUggH_r_ggH_PTH_GE300->Fill(2*j+2.,nnlops_weight*(1-WG1unc[j]));
           }
        }
        if (cat==105 or cat==106){
           h_THUggH_r_ggH_0J->Fill(0.,nnlops_weight);
           for (int j=0; j<9; ++j){
              h_THUggH_r_ggH_0J->Fill(2*j+1.,nnlops_weight*(1+WG1unc[j]));
              h_THUggH_r_ggH_0J->Fill(2*j+2.,nnlops_weight*(1-WG1unc[j]));
           }
        }
        if (cat==107){
           h_THUggH_r_ggH_1J_PTH_0_60->Fill(0.,nnlops_weight);
           for (int j=0; j<9; ++j){
              h_THUggH_r_ggH_1J_PTH_0_60->Fill(2*j+1.,nnlops_weight*(1+WG1unc[j]));
              h_THUggH_r_ggH_1J_PTH_0_60->Fill(2*j+2.,nnlops_weight*(1-WG1unc[j]));
           }
        }
        if (cat==108){
           h_THUggH_r_ggH_1J_PTH_60_120->Fill(0.,nnlops_weight);
           for (int j=0; j<9; ++j){
              h_THUggH_r_ggH_1J_PTH_60_120->Fill(2*j+1.,nnlops_weight*(1+WG1unc[j]));
              h_THUggH_r_ggH_1J_PTH_60_120->Fill(2*j+2.,nnlops_weight*(1-WG1unc[j]));
           }
        }
        if (cat==109){
           h_THUggH_r_ggH_1J_PTH_120_200->Fill(0.,nnlops_weight);
           for (int j=0; j<9; ++j){
              h_THUggH_r_ggH_1J_PTH_120_200->Fill(2*j+1.,nnlops_weight*(1+WG1unc[j]));
              h_THUggH_r_ggH_1J_PTH_120_200->Fill(2*j+2.,nnlops_weight*(1-WG1unc[j]));
           }
        }
        if (cat==113 or cat==114){
           h_THUggH_r_VBFTOPO_MJJ_350_700->Fill(0.,nnlops_weight);
           for (int j=0; j<9; ++j){
              h_THUggH_r_VBFTOPO_MJJ_350_700->Fill(2*j+1.,nnlops_weight*(1+WG1unc[j]));
              h_THUggH_r_VBFTOPO_MJJ_350_700->Fill(2*j+2.,nnlops_weight*(1-WG1unc[j]));
           }
        }
        if (cat==115 or cat==116){
           h_THUggH_r_VBFTOPO_MJJ_GE700->Fill(0.,nnlops_weight);
           for (int j=0; j<9; ++j){
              h_THUggH_r_VBFTOPO_MJJ_GE700->Fill(2*j+1.,nnlops_weight*(1+WG1unc[j]));
              h_THUggH_r_VBFTOPO_MJJ_GE700->Fill(2*j+2.,nnlops_weight*(1-WG1unc[j]));
           }
        }
        if (cat==110 or cat==111 or cat==112){
           h_THUggH_r_ggH_PTH_0_200_GE2J_MJJ_0_350->Fill(0.,nnlops_weight);
           for (int j=0; j<9; ++j){
              h_THUggH_r_ggH_PTH_0_200_GE2J_MJJ_0_350->Fill(2*j+1.,nnlops_weight*(1+WG1unc[j]));
              h_THUggH_r_ggH_PTH_0_200_GE2J_MJJ_0_350->Fill(2*j+2.,nnlops_weight*(1-WG1unc[j]));
           }
        }

	if (cat>=201 && cat<=205){
           h_THUqqH_r_qqH_NONVBFTOPO->Fill(0.,1.0);
           for (int j=0; j<10; ++j){
              h_THUqqH_r_qqH_NONVBFTOPO->Fill(2*j+1.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), 1.0));
              h_THUqqH_r_qqH_NONVBFTOPO->Fill(2*j+2.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), -1.0));
           }
	}
        if (cat==207 or cat==208){
           h_THUqqH_r_qqH_GE2J_MJJ_350_700_PTH_0_200->Fill(0.,1.0);
           for (int j=0; j<10; ++j){
              h_THUqqH_r_qqH_GE2J_MJJ_350_700_PTH_0_200->Fill(2*j+1.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), 1.0));
              h_THUqqH_r_qqH_GE2J_MJJ_350_700_PTH_0_200->Fill(2*j+2.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), -1.0));
           }
        }
        if (cat==209 or cat==210){
           h_THUqqH_r_qqH_GE2J_MJJ_GE700_PTH_0_200->Fill(0.,1.0);
           for (int j=0; j<10; ++j){
              h_THUqqH_r_qqH_GE2J_MJJ_GE700_PTH_0_200->Fill(2*j+1.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), 1.0));
              h_THUqqH_r_qqH_GE2J_MJJ_GE700_PTH_0_200->Fill(2*j+2.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), -1.0));
           }
        }
        if (cat==206){
           h_THUqqH_r_qqH_BSM->Fill(0.,1.0);
           for (int j=0; j<10; ++j){
              h_THUqqH_r_qqH_BSM->Fill(2*j+1.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), 1.0));
              h_THUqqH_r_qqH_BSM->Fill(2*j+2.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), -1.0));
           }
        }


    }
    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();
    h_THUggH->Write();
    h_THUggH_r_ggH_PTH_0_200_GE2J->Write();
    h_THUggH_r_ggH_PTH_200_300->Write();
    h_THUggH_r_ggH_PTH_GE300->Write();
    h_THUggH_r_ggH_0J->Write();
    h_THUggH_r_ggH_1J_PTH_0_60->Write();
    h_THUggH_r_ggH_1J_PTH_60_120->Write();
    h_THUggH_r_ggH_1J_PTH_120_200->Write();
    h_THUggH_r_VBFTOPO_MJJ_350_700->Write();
    h_THUggH_r_VBFTOPO_MJJ_GE700->Write();
    h_THUggH_r_ggH_PTH_0_200_GE2J_MJJ_0_350->Write();

    h_THUqqH->Write();
    h_THUqqH_r_qqH_NONVBFTOPO->Write();
    h_THUqqH_r_qqH_GE2J_MJJ_350_700_PTH_0_200->Write();
    h_THUqqH_r_qqH_GE2J_MJJ_GE700_PTH_0_200->Write();
    h_THUqqH_r_qqH_BSM->Write();

    TDirectory* d_njets_powheg=fout->mkdir("njets_powheg");
    d_njets_powheg->cd();
    for (int k=0; k<nbhist; ++k){
      h_njets_powheg[k]->SetName(name.c_str()+postfix[k]);
      h_njets_powheg[k]->Write();
    }
    TDirectory* d_njets_powheg_em=fout->mkdir("njets_powheg_em");
    d_njets_powheg_em->cd();
    for (int k=0; k<nbhist; ++k){
      h_njets_powheg_em[k]->SetName(name.c_str()+postfix[k]);
      h_njets_powheg_em[k]->Write();
    }
    TDirectory* d_njets_powheg_et=fout->mkdir("njets_powheg_et");
    d_njets_powheg_et->cd();
    for (int k=0; k<nbhist; ++k){
      h_njets_powheg_et[k]->SetName(name.c_str()+postfix[k]);
      h_njets_powheg_et[k]->Write();
    }
    TDirectory* d_njets_powheg_mt=fout->mkdir("njets_powheg_mt");
    d_njets_powheg_mt->cd();
    for (int k=0; k<nbhist; ++k){
      h_njets_powheg_mt[k]->SetName(name.c_str()+postfix[k]);
      h_njets_powheg_mt[k]->Write();
    }
    TDirectory* d_njets_powheg_tt=fout->mkdir("njets_powheg_tt");
    d_njets_powheg_tt->cd();
    for (int k=0; k<nbhist; ++k){
      h_njets_powheg_tt[k]->SetName(name.c_str()+postfix[k]);
      h_njets_powheg_tt[k]->Write();
    }

    TDirectory* d_mjj_powheg=fout->mkdir("mjj_powheg");
    d_mjj_powheg->cd();
    for (int k=0; k<nbhist; ++k){
      h_mjj_powheg[k]->SetName(name.c_str()+postfix[k]);
      h_mjj_powheg[k]->Write();
    }
    TDirectory* d_jpt_powheg=fout->mkdir("jpt_powheg");
    d_jpt_powheg->cd();
    for (int k=0; k<nbhist; ++k){
      h_jpt_powheg[k]->SetName(name.c_str()+postfix[k]);
      h_jpt_powheg[k]->Write();
    }
    TDirectory* d_fs_powheg=fout->mkdir("fs_powheg");
    d_fs_powheg->cd();
    for (int k=0; k<nbhist; ++k){
      h_fs_powheg[k]->SetName(name.c_str()+postfix[k]);
      h_fs_powheg[k]->Write();
    }
    TDirectory* d_hpt_powheg=fout->mkdir("hpt_powheg");
    d_hpt_powheg->cd();
    for (int k=0; k<nbhist; ++k){
      h_hpt_powheg[k]->SetName(name.c_str()+postfix[k]);
      h_hpt_powheg[k]->Write();
    }

    TDirectory* d_njets_nnlops=fout->mkdir("njets_nnlops");
    d_njets_nnlops->cd();
    for (int k=0; k<nbhist; ++k){
      h_njets_powheg_nnlops[k]->SetName(name.c_str()+postfix[k]);
      h_njets_powheg_nnlops[k]->Write();
    }
    TDirectory* d_njets_nnlops_em=fout->mkdir("njets_nnlops_em");
    d_njets_nnlops_em->cd();
    for (int k=0; k<nbhist; ++k){
      h_njets_powheg_nnlops_em[k]->SetName(name.c_str()+postfix[k]);
      h_njets_powheg_nnlops_em[k]->Write();
    }
    TDirectory* d_njets_nnlops_et=fout->mkdir("njets_nnlops_et");
    d_njets_nnlops_et->cd();
    for (int k=0; k<nbhist; ++k){
      h_njets_powheg_nnlops_et[k]->SetName(name.c_str()+postfix[k]);
      h_njets_powheg_nnlops_et[k]->Write();
    }
    TDirectory* d_njets_nnlops_mt=fout->mkdir("njets_nnlops_mt");
    d_njets_nnlops_mt->cd();
    for (int k=0; k<nbhist; ++k){
      h_njets_powheg_nnlops_mt[k]->SetName(name.c_str()+postfix[k]);
      h_njets_powheg_nnlops_mt[k]->Write();
    }
    TDirectory* d_njets_nnlops_tt=fout->mkdir("njets_nnlops_tt");
    d_njets_nnlops_tt->cd();
    for (int k=0; k<nbhist; ++k){
      h_njets_powheg_nnlops_tt[k]->SetName(name.c_str()+postfix[k]);
      h_njets_powheg_nnlops_tt[k]->Write();
    }

    TDirectory* d_mjj_nnlops=fout->mkdir("mjj_nnlops");
    d_mjj_nnlops->cd();
    for (int k=0; k<nbhist; ++k){
      h_mjj_powheg_nnlops[k]->SetName(name.c_str()+postfix[k]);
      h_mjj_powheg_nnlops[k]->Write();
    }
    TDirectory* d_jpt_nnlops=fout->mkdir("jpt_nnlops");
    d_jpt_nnlops->cd();
    for (int k=0; k<nbhist; ++k){
      h_jpt_powheg_nnlops[k]->SetName(name.c_str()+postfix[k]);
      h_jpt_powheg_nnlops[k]->Write();
    }
    TDirectory* d_fs_nnlops=fout->mkdir("fs_nnlops");
    d_fs_nnlops->cd();
    for (int k=0; k<nbhist; ++k){
      h_fs_powheg_nnlops[k]->SetName(name.c_str()+postfix[k]);
      h_fs_powheg_nnlops[k]->Write();
    }
    TDirectory* d_hpt_nnlops=fout->mkdir("hpt_nnlops");
    d_hpt_nnlops->cd();
    for (int k=0; k<nbhist; ++k){
      h_hpt_powheg_nnlops[k]->SetName(name.c_str()+postfix[k]);
      h_hpt_powheg_nnlops[k]->Write();
    }

    TDirectory* d_stage1cat=fout->mkdir("stage1cat");
    d_stage1cat->cd();
    h_stage1cat->SetName(name.c_str());
    h_stage1cat->Write();

    fout->Close();
}
