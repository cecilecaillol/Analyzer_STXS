double GetSF(int WP, float x, int flavour, int syst){

   if (WP==1){
      if (fabs(flavour)==4 or fabs(flavour)==5){
        if (syst==0){
           return  2.22144*((1.+(0.540134*x))/(1.+(1.30246*x))) ;
        }
	if (syst==-1){
	   if (x<30) return (2.22144*((1.+(0.540134*x))/(1.+(1.30246*x))))-0.038731977343559265;
	   else if (x<50) return (2.22144*((1.+(0.540134*x))/(1.+(1.30246*x))))-0.015137125737965107;
           else if (x<70) return (2.22144*((1.+(0.540134*x))/(1.+(1.30246*x))))-0.013977443799376488;
           else if (x<100) return (2.22144*((1.+(0.540134*x))/(1.+(1.30246*x))))-0.012607076205313206;
           else if (x<140) return (2.22144*((1.+(0.540134*x))/(1.+(1.30246*x))))-0.013979751616716385;
           else if (x<200) return (2.22144*((1.+(0.540134*x))/(1.+(1.30246*x))))-0.015011214651167393;
           else if (x<300) return (2.22144*((1.+(0.540134*x))/(1.+(1.30246*x))))-0.034551065415143967;
           else if (x<600) return (2.22144*((1.+(0.540134*x))/(1.+(1.30246*x))))-0.040168888866901398;
	   else return (2.22144*((1.+(0.540134*x))/(1.+(1.30246*x))))-0.054684814065694809;
	}
	else if (syst==1){
           if (x<30) return (2.22144*((1.+(0.540134*x))/(1.+(1.30246*x))))+0.038731977343559265;
           else if (x<50) return (2.22144*((1.+(0.540134*x))/(1.+(1.30246*x))))+0.015137125737965107;
           else if (x<70) return (2.22144*((1.+(0.540134*x))/(1.+(1.30246*x))))+0.013977443799376488;
           else if (x<100) return (2.22144*((1.+(0.540134*x))/(1.+(1.30246*x))))+0.012607076205313206;
           else if (x<140) return (2.22144*((1.+(0.540134*x))/(1.+(1.30246*x))))+0.013979751616716385;
           else if (x<200) return (2.22144*((1.+(0.540134*x))/(1.+(1.30246*x))))+0.015011214651167393;
           else if (x<300) return (2.22144*((1.+(0.540134*x))/(1.+(1.30246*x))))+0.034551065415143967;
           else if (x<600) return (2.22144*((1.+(0.540134*x))/(1.+(1.30246*x))))+0.040168888866901398;
           else return (2.22144*((1.+(0.540134*x))/(1.+(1.30246*x))))+0.054684814065694809;
	}
      }
      else {
        if (syst==0)  return 0.972902+0.000201811*x+3.96396e-08*x*x+-4.53965e-10*x*x*x ;
	if (syst==-1) return  (0.972902+0.000201811*x+3.96396e-08*x*x+-4.53965e-10*x*x*x)*(1-(0.101236+0.000212696*x+-1.71672e-07*x*x));
	if (syst==1) return  (0.972902+0.000201811*x+3.96396e-08*x*x+-4.53965e-10*x*x*x)*(1+(0.101236+0.000212696*x+-1.71672e-07*x*x));
     }
   }
   else return 0;
}


double bTagEventWeight(int nBtaggedJets, float bjetpt_1, int bjetflavour_1, float bjetpt_2, int bjetflavour_2, int WP, int syst, int nBTags)
{
  if (nBtaggedJets > 2) return -10000;
  if( nBTags > 2 ) return -10000;

  /*
    ##################################################################
    Event weight matrix:
    ------------------------------------------------------------------
    nBTags\b-tagged jets  |    0        1             2
    ------------------------------------------------------------------
      0                   |    1      1-SF      (1-SF1)(1-SF2)
                          |
      1                   |    0       SF    SF1(1-SF2)+(1-SF1)SF2
                          |
      2                   |    0        0           SF1SF2
    ##################################################################
  */
  
  if( nBTags > nBtaggedJets) return 0;
  if( nBTags==0 && nBtaggedJets==0) return 1;

  double weight = 0;
  if(nBtaggedJets==1){
    double SF = GetSF(WP,bjetpt_1,bjetflavour_1,syst);
    for( unsigned int i=0; i<=1; ++i ){
      if( i != nBTags ) continue;
      weight += pow(SF,i)*pow(1-SF,1-i);
    }
  }
  else if(nBtaggedJets==2 ){
    double SF1 = GetSF(WP,bjetpt_1,bjetflavour_1,syst);
    double SF2 = GetSF(WP,bjetpt_2,bjetflavour_2,syst);
    
    for( unsigned int i=0; i<=1; ++i ){
      for( unsigned int j=0; j<=1; ++j ){
        if( (i+j) != nBTags ) continue;
        weight += pow(SF1,i)*pow(1-SF1,1-i)*pow(SF2,j)*pow(1-SF2,1-j);
      }
    }
  }
  return weight;
}

int PromoteDemote(TH2F* h_btag_eff_b, TH2F* h_btag_eff_c, TH2F* h_btag_eff_oth, int nbtag, float bpt_1, float bflavor_1, float beta_1, int syst){
        float SF=GetSF(1,bpt_1,bflavor_1,syst);
        float beff=1.0;
        if (bflavor_1==5){
           if(bpt_1>h_btag_eff_b->GetXaxis()->GetBinLowEdge(h_btag_eff_b->GetNbinsX()+1))
               beff = h_btag_eff_b->GetBinContent(h_btag_eff_b->GetNbinsX(),h_btag_eff_b->GetYaxis()->FindBin(fabs(beta_1)));
           else
               beff = h_btag_eff_b->GetBinContent(h_btag_eff_b->GetXaxis()->FindBin(bpt_1),h_btag_eff_b->GetYaxis()->FindBin(fabs(beta_1)));
        }
        else if (bflavor_1==4){
           if(bpt_1>h_btag_eff_c->GetXaxis()->GetBinLowEdge(h_btag_eff_c->GetNbinsX()+1))
               beff = h_btag_eff_c->GetBinContent(h_btag_eff_c->GetNbinsX(),h_btag_eff_c->GetYaxis()->FindBin(fabs(beta_1)));
           else
               beff = h_btag_eff_c->GetBinContent(h_btag_eff_c->GetXaxis()->FindBin(bpt_1),h_btag_eff_c->GetYaxis()->FindBin(fabs(beta_1)));
        }
        else {
           if(bpt_1>h_btag_eff_oth->GetXaxis()->GetBinLowEdge(h_btag_eff_oth->GetNbinsX()+1))
               beff = h_btag_eff_oth->GetBinContent(h_btag_eff_oth->GetNbinsX(),h_btag_eff_oth->GetYaxis()->FindBin(fabs(beta_1)));
           else
               beff = h_btag_eff_oth->GetBinContent(h_btag_eff_oth->GetXaxis()->FindBin(bpt_1),h_btag_eff_oth->GetYaxis()->FindBin(fabs(beta_1)));
        }
        TRandom3* rand=new TRandom3();
        rand->SetSeed((int)((beta_1+5)*100000));
        float myrand=rand->Rndm();
        if (SF<1 && myrand<(1-SF)) nbtag=nbtag-1;
        if (SF>1 && myrand<((1-SF)/(1-1.0/beff))) nbtag=nbtag+1;

        return nbtag;

}

