#include <TLatex.h>
#include <TGraph.h>

#include "TGraphAsymmErrors.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH1.h"
#include "TH2.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "math.h"
#include "TGaxis.h"
#include "TLegend.h"
#include "TInterpreter.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TFile.h"
#include "TH2.h"
#include "TNtuple.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include "TFrame.h"
#include "TSystem.h"
#include "TInterpreter.h"
#include "TMatrixD.h"
#include "TMinuit.h"

double square(double x)
{
  return x*x;
}

void makeBinsInteger(TH1* histogram_pass, TH1* histogram_fail)
{
  assert(histogram_pass->GetNbinsX() == histogram_fail->GetNbinsX());
  int numBins = histogram_pass->GetNbinsX();
  for ( int iBin = 1; iBin <= numBins; ++iBin ) {
    if (histogram_pass->GetBinContent(iBin)<0){ histogram_pass->SetBinContent(iBin,0); histogram_pass->SetBinError(iBin,0);}
    if (histogram_fail->GetBinContent(iBin)<0){ histogram_fail->SetBinContent(iBin,0); histogram_fail->SetBinError(iBin,0);}
    double binContent_sum = histogram_pass->GetBinContent(iBin) + histogram_fail->GetBinContent(iBin);
    double binError2_sum = square(histogram_pass->GetBinError(iBin)) + square(histogram_fail->GetBinError(iBin));
    double binError_sum = TMath::Sqrt(binError2_sum);
    if ( binContent_sum > 0. && binError_sum > 0. ) {
      double nEff = square(binContent_sum/binError_sum);
      double avWeight = binContent_sum/nEff;
      double binContent_pass = TMath::Nint(histogram_pass->GetBinContent(iBin)/avWeight);
      double binError_pass = TMath::Sqrt(binContent_pass);
      histogram_pass->SetBinContent(iBin, binContent_pass);
      histogram_pass->SetBinError(iBin, binError_pass);
      double binContent_fail = TMath::Nint(histogram_fail->GetBinContent(iBin)/avWeight);
      double binError_fail = TMath::Sqrt(binContent_fail);
      histogram_fail->SetBinContent(iBin, binContent_fail);
      histogram_fail->SetBinError(iBin, binError_fail);
    }
  }
}

double fitFunction(double x, double par0, double par1) {
    return par0 + par1 *(x-40);
}

Double_t fitFunc_Exp3Par(Double_t *x, Double_t *par) {
    return par[0] + par[1]* (x[0]-3.0);
}

Double_t fitFunc_Line2Par(Double_t *x, Double_t *par) {
    return par[0] + par[1] * (x[0]-2.5) ;
}

Double_t fitFunc_Constant(Double_t *x, Double_t *par) {
    return par[0];
}

Double_t fitFunc_Line2Par2(Double_t *x, Double_t *par) {
    //return par[0] + par[1] * (x[0]-4.) ;//+ par[2] * x[0]* x[0] + par[3] * x[0]* x[0] *x[0];
    //return par[0] + par[1]*(TMath::Exp(par[2] * x[0]-par[3]));
    //return par[0] + par[1]*(TMath::Landau((x[0]-1),par[2],par[3],0));
    return par[0] + par[1]*x[0]+par[2]*x[0]*x[0]+par[3]*x[0]*x[0]*x[0];
}

Double_t fitFunc_Landau(Double_t *x, Double_t *par) {
    return par[0] + par[1]*(TMath::Landau((x[0]-30),par[2],par[3],0));
}

TF1 *M_FR(int WP, std::string type, std::string files, std::string num, std::string denum, std::string name, TH2F * hist2D_lep, Double_t fMin, Double_t fMax) {
    TFile *inputFile = new TFile(files.c_str());

    TH1D *Numerator = (TH1D*) inputFile->Get(num.c_str());
    TH1D *Denumerator = (TH1D*) inputFile->Get(denum.c_str());

    TH1D *histogram_pass = (TH1D*) Numerator->Rebin(1);
    TH1D *histogram_fail = (TH1D*) Denumerator->Rebin(1);

    makeBinsInteger(histogram_pass, histogram_fail);

    TGraphAsymmErrors* TGraph_FR = new TGraphAsymmErrors(26);
    TGraph_FR->Divide(histogram_pass, histogram_fail, "pois");

    Double_t *yg = TGraph_FR->GetY();
    for (int i = 0; i<5; i++) printf("yg[%d] = %g\n", i,yg[i]);

    int nPar = 4; // number of parameters in the fit

    TF1 * theFit2 = new TF1("theFit2", fitFunc_Line2Par, fMin, fMax, 2);

    theFit2->SetParameter(0, 2.0);
    theFit2->SetParameter(1, -0.3);

    float xAxisMax = 500;
    //if (type.find("Line2Par2") < 140) theFit2 = new TF1("theFit2", fitFunc_Line2Par2, fMin, fMax, 2);
    if (type.find("Line2Par2") < 140){ 
       theFit2 = new TF1("theFit2", fitFunc_Line2Par2, fMin, fMax, 4);
       theFit2->SetParameter(0, 2.0);
       theFit2->SetParameter(1, -0.3);
       theFit2->SetParameter(2, -0.3);
       theFit2->SetParameter(3, -0.3);
    }
   if (type.find("Constant") < 140){
       theFit2 = new TF1("theFit2", fitFunc_Line2Par2, fMin, fMax, 1);
       theFit2->SetParameter(0, 2.0);
    }
    TGraph_FR->Fit("theFit2", "R0");

    TCanvas* canvas = new TCanvas("canvas", "", 800, 800);
    canvas->SetTitle("");
    canvas->SetGrid();
    TGraph_FR->GetYaxis()->SetRangeUser(0.,5.);
    TGraph_FR->GetYaxis()->SetTitle("OS-to-SS scale factor");
    TGraph_FR->GetXaxis()->SetRangeUser(0.3, 6.0);
    TGraph_FR->GetXaxis()->SetTitle("#DeltaR(e,#mu)");
    TGraph_FR->SetTitle("");
    TGraph_FR->Draw("PAE");
    TGraph_FR->SetLineWidth(3);
    std::string outNaming = "fit_" + name + ".pdf";
    TLatex t = TLatex();
    t.SetNDC();
    t.SetTextFont(42);
    t.SetTextAlign(12);
    t.SetTextSize(0.04);
    t.DrawLatex(0.55, .96, "35.9 fb^{-1} (2016, 13 TeV)");
    theFit2->Draw("SAME");
    theFit2->SetLineColor(2);

    // Up and down fits
    Double_t TauLegParameters[2];
    theFit2->GetParameters(TauLegParameters);

    Double_t matrix[2][2];
    gMinuit->mnemat(&matrix[0][0],2);
    TMatrixD mat_D(2,2);
     for (int i=0; i<2; ++i){
        for (int j=0; j<2; ++j){
             mat_D[i][j]=matrix[i][j];
        }
    }
    float aup; float adown; float bup; float bdown;

    TMatrixDEigen mat_sym=TMatrixDEigen (mat_D);
    TMatrixD eigenValues=mat_sym.GetEigenValues();
    TMatrixD eigenVectors=mat_sym.GetEigenVectors();
    TMatrixD eigenVectorsInverted=mat_sym.GetEigenVectors();
    aup = TauLegParameters[0]+eigenVectorsInverted[0][0]*sqrt(eigenValues[0][0])+eigenVectorsInverted[0][1]*sqrt(eigenValues[1][1]);
    bup = TauLegParameters[1]+eigenVectorsInverted[0][1]*sqrt(eigenValues[0][0])+eigenVectorsInverted[1][1]*sqrt(eigenValues[1][1]);
    adown = TauLegParameters[0]-eigenVectorsInverted[0][0]*sqrt(eigenValues[0][0])-eigenVectorsInverted[0][1]*sqrt(eigenValues[1][1]);
    bdown = TauLegParameters[1]-eigenVectorsInverted[0][1]*sqrt(eigenValues[0][0])-eigenVectorsInverted[1][1]*sqrt(eigenValues[1][1]);

    float au1=TauLegParameters[0]+eigenVectorsInverted[0][0]*sqrt(eigenValues[0][0]);
    float bu1=TauLegParameters[1]+eigenVectorsInverted[0][1]*sqrt(eigenValues[0][0]);
    float ad1=TauLegParameters[0]-eigenVectorsInverted[0][0]*sqrt(eigenValues[0][0]);
    float bd1=TauLegParameters[1]-eigenVectorsInverted[0][1]*sqrt(eigenValues[0][0]);
    float au2=TauLegParameters[0]+eigenVectorsInverted[0][1]*sqrt(eigenValues[1][1]);
    float bu2=TauLegParameters[1]+eigenVectorsInverted[1][1]*sqrt(eigenValues[1][1]);
    float ad2=TauLegParameters[0]-eigenVectorsInverted[0][1]*sqrt(eigenValues[1][1]);
    float bd2=TauLegParameters[1]-eigenVectorsInverted[1][1]*sqrt(eigenValues[1][1]);

    TF1 * theFitup1 = new TF1("theFit2", fitFunc_Line2Par, fMin, fMax, 2);
    if (type.find("Line2Par2") < 140) theFitup1 = new TF1("theFit2", fitFunc_Line2Par2, fMin, fMax, 2);
    theFitup1->SetParameter(0, au1);
    theFitup1->SetParameter(1, bu1);
    theFitup1->SetLineColor(kViolet+1);
    theFitup1->Draw("same");
    TF1 * theFitup2 = new TF1("theFit2", fitFunc_Line2Par, fMin, fMax, 2);
    if (type.find("Line2Par2") < 140) theFitup2 = new TF1("theFit2", fitFunc_Line2Par2, fMin, fMax, 2);
    theFitup2->SetParameter(0, au2);
    theFitup2->SetParameter(1, bu2);
    theFitup2->SetLineColor(kGreen-3);
    theFitup2->Draw("same");
    TF1 * theFitdown1 = new TF1("theFit2", fitFunc_Line2Par, fMin, fMax, 2);
    if (type.find("Line2Par2") < 140) theFitdown1 = new TF1("theFit2", fitFunc_Line2Par2, fMin, fMax, 2);
    theFitdown1->SetParameter(0, ad1);
    theFitdown1->SetParameter(1, bd1);
    theFitdown1->SetLineColor(kViolet+1);
    theFitdown1->Draw("same");
    TF1 * theFitdown2 = new TF1("theFit2", fitFunc_Line2Par, fMin, fMax, 2);
    if (type.find("Line2Par2") < 140) theFitdown2 = new TF1("theFit2", fitFunc_Line2Par2, fMin, fMax, 2);
    theFitdown2->SetParameter(0, ad2);
    theFitdown2->SetParameter(1, bd2);
    theFitdown2->SetLineColor(kGreen-3);
    theFitdown2->Draw("same");
    TLegend *l = new TLegend(0.15, 0.74, 0.5, 0.89, NULL, "brNDC");
    l->SetBorderSize(0);
    l->SetFillColor(0);
    l->SetTextSize(.03);
    l->SetFillColor(0);
    l->AddEntry(theFit2, "Best fit", "l");
    l->AddEntry(theFitup1, "1st uncertainty #pm 1#sigma", "l");
    l->AddEntry(theFitup2, "2nd uncertainty #pm 1#sigma", "l");
    l->Draw("same");

    canvas->SaveAs(outNaming.c_str());

    TFile *FR_H = new TFile("osss_em_2016.root", "UPDATE");
    FR_H->cd();
    theFit2->SetName(TString(name));
    theFit2->Write();
    theFitup1->SetName(TString(name)+"_unc1_up");
    theFitup1->Write();
    theFitdown1->SetName(TString(name)+"_unc1_down");
    theFitdown1->Write();
    theFitup2->SetName(TString(name)+"_unc2_up");
    theFitup2->Write();
    theFitdown2->SetName(TString(name)+"_unc2_down");
    theFitdown2->Write();
    FR_H->Close();

   return theFit2;
}

void Fit_QCDSF_em() {

    gStyle->SetOptFit(1111);

    TH2F * Fit_Value_tau = new TH2F("Fit_Value_tau", "Fit_Value_tau", 40, 0, 40, 40, 0, 40);

    Double_t fMin = 0.3;
    Double_t fMax = 10.0;

    TF1* m11 = M_FR(1, "Line2Par2", "qcdfiles_em/Sub.root", "INOS0", "INSS0", "OSSS_qcd_0jet_2016", Fit_Value_tau, fMin, fMax);
    TF1* m111 = M_FR(11, "Line2Par", "qcdfiles_em/Sub.root", "INOS0", "INSS0", "OSSS_qcd_0jet_2016_par1", Fit_Value_tau, fMin, fMax);
    TF1* m112 = M_FR(12, "Constant", "qcdfiles_em/Sub.root", "INOS0", "INSS0", "OSSS_qcd_0jet_2016_par0", Fit_Value_tau, fMin, fMax);
    TF1* m12 = M_FR(2, "Line2Par", "qcdfiles_em/Sub.root", "INOS1", "INSS1", "OSSS_qcd_1jet_2016", Fit_Value_tau, fMin, fMax);
    TF1* m13 = M_FR(3, "Line2Par", "qcdfiles_em/Sub.root", "INOS2", "INSS2", "OSSS_qcd_2jet_2016", Fit_Value_tau, fMin, fMax);
    
}

