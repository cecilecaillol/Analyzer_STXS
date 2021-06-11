#include "TF1.h"
#include "TFile.h"
#include "TString.h"

using namespace std;

TFile frawff("ff_files_mt/uncorrected_fakefactors_mt.root");
TF1* ff_qcd_0jet=(TF1*) frawff.Get("rawFF_mt_qcd_0jet");
TF1* ff_qcd_1jet=(TF1*) frawff.Get("rawFF_mt_qcd_1jet");
TF1* ff_w_0jet=(TF1*) frawff.Get("rawFF_mt_w_0jet");
TF1* ff_w_1jet=(TF1*) frawff.Get("rawFF_mt_w_1jet");
TF1* ff_tt_0jet=(TF1*) frawff.Get("mc_rawFF_mt_tt");

TF1* ff_qcd_0jet_up1=(TF1*) frawff.Get("rawFF_mt_qcd_0jet_unc1_up");
TF1* ff_qcd_1jet_up1=(TF1*) frawff.Get("rawFF_mt_qcd_1jet_unc1_up");
TF1* ff_w_0jet_up1=(TF1*) frawff.Get("rawFF_mt_w_0jet_unc1_up");
TF1* ff_w_1jet_up1=(TF1*) frawff.Get("rawFF_mt_w_1jet_unc1_up");
TF1* ff_tt_0jet_up1=(TF1*) frawff.Get("mc_rawFF_mt_tt_unc1_up");
TF1* ff_qcd_0jet_up2=(TF1*) frawff.Get("rawFF_mt_qcd_0jet_unc2_up");
TF1* ff_qcd_1jet_up2=(TF1*) frawff.Get("rawFF_mt_qcd_1jet_unc2_up");
TF1* ff_w_0jet_up2=(TF1*) frawff.Get("rawFF_mt_w_0jet_unc2_up");
TF1* ff_w_1jet_up2=(TF1*) frawff.Get("rawFF_mt_w_1jet_unc2_up");
TF1* ff_tt_0jet_up2=(TF1*) frawff.Get("mc_rawFF_mt_tt_unc2_up");
TF1* ff_qcd_0jet_down1=(TF1*) frawff.Get("rawFF_mt_qcd_0jet_unc1_down");
TF1* ff_qcd_1jet_down1=(TF1*) frawff.Get("rawFF_mt_qcd_1jet_unc1_down");
TF1* ff_w_0jet_down1=(TF1*) frawff.Get("rawFF_mt_w_0jet_unc1_down");
TF1* ff_w_1jet_down1=(TF1*) frawff.Get("rawFF_mt_w_1jet_unc1_down");
TF1* ff_tt_0jet_down1=(TF1*) frawff.Get("mc_rawFF_mt_tt_unc1_down");
TF1* ff_qcd_0jet_down2=(TF1*) frawff.Get("rawFF_mt_qcd_0jet_unc2_down");
TF1* ff_qcd_1jet_down2=(TF1*) frawff.Get("rawFF_mt_qcd_1jet_unc2_down");
TF1* ff_w_0jet_down2=(TF1*) frawff.Get("rawFF_mt_w_0jet_unc2_down");
TF1* ff_w_1jet_down2=(TF1*) frawff.Get("rawFF_mt_w_1jet_unc2_down");
TF1* ff_tt_0jet_down2=(TF1*) frawff.Get("mc_rawFF_mt_tt_unc2_down");

TFile fmvisclosure ("ff_files_mt/FF_corrections_1.root");
TF1* mvisclosure_qcd=(TF1*) fmvisclosure.Get("closure_mvis_mt_qcd");
TF1* mvisclosure_w=(TF1*) fmvisclosure.Get("closure_mvis_mt_w");
TF1* mvisclosure_tt=(TF1*) fmvisclosure.Get("closure_mvis_mt_ttmc");

TF1* mvisclosure_qcd_up1=(TF1*) fmvisclosure.Get("closure_mvis_mt_qcd_unc1_up");
TF1* mvisclosure_w_up1=(TF1*) fmvisclosure.Get("closure_mvis_mt_tt_unc1_up");
TF1* mvisclosure_tt_up1=(TF1*) fmvisclosure.Get("closure_mvis_mt_ttmc_unc1_up");
TF1* mvisclosure_qcd_up2=(TF1*) fmvisclosure.Get("closure_mvis_mt_qcd_unc2_up");
TF1* mvisclosure_w_up2=(TF1*) fmvisclosure.Get("closure_mvis_mt_tt_unc2_up");
TF1* mvisclosure_tt_up2=(TF1*) fmvisclosure.Get("closure_mvis_mt_ttmc_unc2_up");
TF1* mvisclosure_qcd_down1=(TF1*) fmvisclosure.Get("closure_mvis_mt_qcd_unc1_down");
TF1* mvisclosure_w_down1=(TF1*) fmvisclosure.Get("closure_mvis_mt_tt_unc1_down");
TF1* mvisclosure_tt_down1=(TF1*) fmvisclosure.Get("closure_mvis_mt_ttmc_unc1_down");
TF1* mvisclosure_qcd_down2=(TF1*) fmvisclosure.Get("closure_mvis_mt_qcd_unc2_down");
TF1* mvisclosure_w_down2=(TF1*) fmvisclosure.Get("closure_mvis_mt_tt_unc2_down");
TF1* mvisclosure_tt_down2=(TF1*) fmvisclosure.Get("closure_mvis_mt_ttmc_unc2_down");

TFile fosssclosure ("ff_files_mt/FF_QCDcorrectionOSSS.root");
TF1* osssclosure_qcd=(TF1*) fosssclosure.Get("closure_OSSS_mvis_mt_qcd");
TF1* mtclosure_w=(TF1*) fosssclosure.Get("closure_mt_mt_w");

TF1* osssclosure_qcd_up1=(TF1*) fosssclosure.Get("closure_OSSS_mvis_mt_qcd_unc1_up");
TF1* mtclosure_w_up1=(TF1*) fosssclosure.Get("closure_mt_mt_w_unc1_up");
TF1* osssclosure_qcd_up2=(TF1*) fosssclosure.Get("closure_OSSS_mvis_mt_qcd_unc2_up");
TF1* mtclosure_w_up2=(TF1*) fosssclosure.Get("closure_mt_mt_w_unc2_up");
TF1* osssclosure_qcd_down1=(TF1*) fosssclosure.Get("closure_OSSS_mvis_mt_qcd_unc1_down");
TF1* mtclosure_w_down1=(TF1*) fosssclosure.Get("closure_mt_mt_w_unc1_down");
TF1* osssclosure_qcd_down2=(TF1*) fosssclosure.Get("closure_OSSS_mvis_mt_qcd_unc2_down");
TF1* mtclosure_w_down2=(TF1*) fosssclosure.Get("closure_mt_mt_w_unc2_down");


float get_raw_FF(float pt, TF1* fct){
  float ff=1.0;
  ff=fct->Eval(pt);
  return ff;
}

float get_mvis_closure(float mvis, TF1* fct){
  float corr=1.0;
  corr=fct->Eval(mvis);
  return corr;
}

float get_mt_closure(float mt, TF1* fct){
  float corr=1.0;
  corr=fct->Eval(mt);
  return corr;
}

float get_ff(float pt, float mt, float mvis, int njets, float frac_tt, float frac_qcd, float frac_w, TString shift){
   float ff_qcd=1.0;
   float ff_w=0;
   float ff_tt=1.0;

   // Raw FF
   if (njets==0){
	ff_qcd=get_raw_FF(pt,ff_qcd_0jet);
	if (shift=="ff_qcd_0jet_up1") ff_qcd=get_raw_FF(pt,ff_qcd_0jet_up1);
        else if (shift=="ff_qcd_0jet_up2") ff_qcd=get_raw_FF(pt,ff_qcd_0jet_up2);
        else if (shift=="ff_qcd_0jet_down1") ff_qcd=get_raw_FF(pt,ff_qcd_0jet_down1);
        else if (shift=="ff_qcd_0jet_down2") ff_qcd=get_raw_FF(pt,ff_qcd_0jet_down2);
	ff_w=get_raw_FF(pt,ff_w_0jet);
        if (shift=="ff_w_0jet_up1") ff_w=get_raw_FF(pt,ff_w_0jet_up1);
        else if (shift=="ff_w_0jet_up2") ff_w=get_raw_FF(pt,ff_w_0jet_up2);
        else if (shift=="ff_w_0jet_down1") ff_w=get_raw_FF(pt,ff_w_0jet_down1);
        else if (shift=="ff_w_0jet_down2") ff_w=get_raw_FF(pt,ff_w_0jet_down2);
   }
   else{
        ff_qcd=get_raw_FF(pt,ff_qcd_1jet);
        if (shift=="ff_qcd_1jet_up1") ff_qcd=get_raw_FF(pt,ff_qcd_1jet_up1);
        else if (shift=="ff_qcd_1jet_up2") ff_qcd=get_raw_FF(pt,ff_qcd_1jet_up2);
        else if (shift=="ff_qcd_1jet_down1") ff_qcd=get_raw_FF(pt,ff_qcd_1jet_down1);
        else if (shift=="ff_qcd_1jet_down2") ff_qcd=get_raw_FF(pt,ff_qcd_1jet_down2);
        ff_w=get_raw_FF(pt,ff_w_1jet);
        if (shift=="ff_w_1jet_up1") ff_w=get_raw_FF(pt,ff_w_1jet_up1);
        else if (shift=="ff_w_1jet_up2") ff_w=get_raw_FF(pt,ff_w_1jet_up2);
        else if (shift=="ff_w_1jet_down1") ff_w=get_raw_FF(pt,ff_w_1jet_down1);
        else if (shift=="ff_w_1jet_down2") ff_w=get_raw_FF(pt,ff_w_1jet_down2);
   }
   ff_tt=get_raw_FF(pt,ff_tt_0jet);
   if (shift=="ff_tt_0jet_up1") ff_tt=get_raw_FF(pt,ff_tt_0jet_up1);
   else if (shift=="ff_tt_0jet_up2") ff_tt=get_raw_FF(pt,ff_tt_0jet_up2);
   else if (shift=="ff_tt_0jet_down1") ff_tt=get_raw_FF(pt,ff_tt_0jet_down1);
   else if (shift=="ff_tt_0jet_down2") ff_tt=get_raw_FF(pt,ff_tt_0jet_down2);

   // Mvis closure
   if (shift=="mvisclosure_qcd_up1") ff_qcd = ff_qcd*get_mvis_closure(mvis, mvisclosure_qcd_up1);
   else if (shift=="mvisclosure_qcd_up2") ff_qcd = ff_qcd*get_mvis_closure(mvis, mvisclosure_qcd_up2);
   else if (shift=="mvisclosure_qcd_down1") ff_qcd = ff_qcd*get_mvis_closure(mvis, mvisclosure_qcd_down1);
   else if (shift=="mvisclosure_qcd_down2") ff_qcd = ff_qcd*get_mvis_closure(mvis, mvisclosure_qcd_down2);
   else ff_qcd = ff_qcd*get_mvis_closure(mvis, mvisclosure_qcd);

   /*if (shift=="mvisclosure_w_up1") ff_w = ff_w*get_mvis_closure(mvis, mvisclosure_w_up1);
   else if (shift=="mvisclosure_w_up2") ff_w = ff_w*get_mvis_closure(mvis, mvisclosure_w_up2);
   else if (shift=="mvisclosure_w_down1") ff_w = ff_w*get_mvis_closure(mvis, mvisclosure_w_down1);
   else if (shift=="mvisclosure_w_down2") ff_w = ff_w*get_mvis_closure(mvis, mvisclosure_w_down2);*/
   if (shift=="mvisclosure_w_up1") ff_w = ff_w*(1+2*(get_mvis_closure(mvis, mvisclosure_w)-1));
   else if (shift=="mvisclosure_w_down1") ff_w = ff_w;
   else ff_w = ff_w*get_mvis_closure(mvis, mvisclosure_w);

   if (shift=="mvisclosure_tt_up1") ff_tt = ff_tt*get_mvis_closure(mvis, mvisclosure_tt_up1);
   else if (shift=="mvisclosure_tt_up2") ff_tt = ff_tt*get_mvis_closure(mvis, mvisclosure_tt_up2);
   else if (shift=="mvisclosure_tt_down1") ff_tt = ff_tt*get_mvis_closure(mvis, mvisclosure_tt_down1);
   else if (shift=="mvisclosure_tt_down2") ff_tt = ff_tt*get_mvis_closure(mvis, mvisclosure_tt_down2);
   else ff_tt = ff_tt*get_mvis_closure(mvis, mvisclosure_tt);

   // MT and OSSS corrections
   if (shift=="mtclosure_w_up1") ff_w = ff_w*get_mt_closure(mt,mtclosure_w_up1);
   else if (shift=="mtclosure_w_up2") ff_w = ff_w*get_mt_closure(mt,mtclosure_w_up2);
   else if (shift=="mtclosure_w_down1") ff_w = ff_w*get_mt_closure(mt,mtclosure_w_down1);
   else if (shift=="mtclosure_w_down2") ff_w = ff_w*get_mt_closure(mt,mtclosure_w_down2);
   else ff_w = ff_w*get_mt_closure(mt,mtclosure_w);

   /*if (shift=="osssclosure_qcd_up1") ff_qcd = ff_qcd*get_mvis_closure(mvis, osssclosure_qcd_up1);
   else if (shift=="osssclosure_qcd_up2") ff_qcd = ff_qcd*get_mvis_closure(mvis, osssclosure_qcd_up2);
   else if (shift=="osssclosure_qcd_down1") ff_qcd = ff_qcd*get_mvis_closure(mvis, osssclosure_qcd_down1);
   else if (shift=="osssclosure_qcd_down2") ff_qcd = ff_qcd*get_mvis_closure(mvis, osssclosure_qcd_down2);*/
   if (shift=="osssclosure_qcd_up1") ff_qcd = ff_qcd*(1+2*(get_mvis_closure(mvis, osssclosure_qcd)-1));
   else if (shift=="osssclosure_qcd_down1") ff_qcd = ff_qcd;
   else ff_qcd = ff_qcd*get_mvis_closure(mvis, osssclosure_qcd);

   if (ff_tt<0 or ff_tt>10) ff_tt=0;
   if (ff_qcd<0 or ff_qcd>10) ff_qcd=0;
   if (ff_w<0 or ff_w>10) ff_w=0;

   float ff_cmb=frac_tt*ff_tt + frac_qcd*ff_qcd + frac_w*ff_w;
   return ff_cmb;
} 

