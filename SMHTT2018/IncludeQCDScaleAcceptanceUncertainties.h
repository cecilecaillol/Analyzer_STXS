   TFile *f_QCDScaleAcceptance_GGHTT = new TFile("/afs/cern.ch/work/c/ccaillol/public/QCDScaleAcceptance/GGHTT2018.root");
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
   if (sample=="WminusH125") TFile *f_QCDScaleAcceptance_VHTT = new TFile("/afs/cern.ch/work/c/ccaillol/public/QCDScaleAcceptance/WminusHTT2018.root");
   if (sample=="ZH125") TFile *f_QCDScaleAcceptance_VHTT = new TFile("/afs/cern.ch/work/c/ccaillol/public/QCDScaleAcceptance/ZHTT2018.root");
   if (sample=="GGZHLLTT125") TFile *f_QCDScaleAcceptance_VHTT = new TFile("/afs/cern.ch/work/c/ccaillol/public/QCDScaleAcceptance/GGZHLLTT2018.root");
   if (sample=="GGZHNNTT125") TFile *f_QCDScaleAcceptance_VHTT = new TFile("/afs/cern.ch/work/c/ccaillol/public/QCDScaleAcceptance/GGZHNNTT2018.root");
   if (sample=="GGZHQQTT125") TFile *f_QCDScaleAcceptance_VHTT = new TFile("/afs/cern.ch/work/c/ccaillol/public/QCDScaleAcceptance/GGZHQQTT2018.root");
   TH1F *h_QCDScaleAcceptance_VH = (TH1F*) f_QCDScaleAcceptance_VHTT->Get("demo/h_nevents_vbf");
   TH1F *h_QCDScaleAcceptance_VH_scale_0jet = (TH1F*) f_QCDScaleAcceptance_VHTT->Get("demo/h_nevents_vbf_scale_0jet");
   TH1F *h_QCDScaleAcceptance_VH_scale_1jet = (TH1F*) f_QCDScaleAcceptance_VHTT->Get("demo/h_nevents_vbf_scale_1jet");
   TH1F *h_QCDScaleAcceptance_VH_scale_lowmjj = (TH1F*) f_QCDScaleAcceptance_VHTT->Get("demo/h_nevents_vbf_scale_lowmjj");
   TH1F *h_QCDScaleAcceptance_VH_scale_highmjj_lowpt = (TH1F*) f_QCDScaleAcceptance_VHTT->Get("demo/h_nevents_vbf_scale_highmjj_lowpt");
   TH1F *h_QCDScaleAcceptance_VH_scale_highmjj_highpt = (TH1F*) f_QCDScaleAcceptance_VHTT->Get("demo/h_nevents_vbf_scale_highmjj_highpt");
   TH1F *h_QCDScaleAcceptance_WH_scale_lowpt = (TH1F*) f_QCDScaleAcceptance_VHTT->Get("demo/h_nevents_WH_scale_lowpt");
   TH1F *h_QCDScaleAcceptance_WH_scale_highpt = (TH1F*) f_QCDScaleAcceptance_VHTT->Get("demo/h_nevents_WH_scale_highpt");
   TH1F *h_QCDScaleAcceptance_ZH_scale_lowpt = (TH1F*) f_QCDScaleAcceptance_VHTT->Get("demo/h_nevents_ZH_scale_lowpt");
   TH1F *h_QCDScaleAcceptance_ZH_scale_highpt = (TH1F*) f_QCDScaleAcceptance_VHTT->Get("demo/h_nevents_ZH_scale_highpt");

/*   // VH had scale
   if (sample=="GGZHLLTT125" or sample=="GGZHNNTT125" or sample=="GGZHQQTT125" or sample=="WminusH125" or sample=="WplusH125" or sample=="ZH125"){
     if (name.find("H_0J_htt1") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_VH_scale_0jet->GetBinContent(1)/h_QCDScaleAcceptance_VH_scale_0jet->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_VH_scale_0jet->GetBinContent(1)/h_QCDScaleAcceptance_VH_scale_0jet->GetBinContent(9); postfixMC[81]="_VH_scale_0jetDown"; postfixMC[82]="_VH_scale_0jetUp";}
     if (name.find("H_1J_htt1") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_VH_scale_1jet->GetBinContent(1)/h_QCDScaleAcceptance_VH_scale_1jet->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_VH_scale_1jet->GetBinContent(1)/h_QCDScaleAcceptance_VH_scale_1jet->GetBinContent(9); postfixMC[81]="_VH_scale_1jetDown"; postfixMC[82]="_VH_scale_1jetUp";}
     if (name.find("H_GE2J_MJJ_0_60_htt1") < 140 or name.find("H_GE2J_MJJ_60_120_htt1") < 140 or name.find("H_GE2J_MJJ_120_350_htt1") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_VH_scale_lowmjj->GetBinContent(1)/h_QCDScaleAcceptance_VH_scale_lowmjj->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_VH_scale_lowmjj->GetBinContent(1)/h_QCDScaleAcceptance_VH_scale_lowmjj->GetBinContent(9); postfixMC[81]="_VH_scale_lowmjjDown"; postfixMC[82]="_VH_scale_lowmjjUp";}
     if (name.find("H_GE2J_MJJ_350_700_PTH_0_200_PTHJJ_0_25_htt1") < 140 or name.find("H_GE2J_MJJ_350_700_PTH_0_200_PTHJJ_GT25_htt1") < 140 or name.find("H_GE2J_MJJ_GT700_PTH_0_200_PTHJJ_0_25_htt1") < 140 or name.find("H_GE2J_MJJ_GT700_PTH_0_200_PTHJJ_GT25_htt1") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_VH_scale_highmjj_lowpt->GetBinContent(1)/h_QCDScaleAcceptance_VH_scale_highmjj_lowpt->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_VH_scale_highmjj_lowpt->GetBinContent(1)/h_QCDScaleAcceptance_VH_scale_highmjj_lowpt->GetBinContent(9); postfixMC[81]="_VH_scale_highmjj_lowptDown"; postfixMC[82]="_VH_scale_highmjj_lowptUp";}
     if (name.find("H_GE2J_MJJ_GT350_PTH_GT200_htt1") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_VH_scale_highmjj_highpt->GetBinContent(1)/h_QCDScaleAcceptance_VH_scale_highmjj_highpt->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_VH_scale_highmjj_highpt->GetBinContent(1)/h_QCDScaleAcceptance_VH_scale_highmjj_highpt->GetBinContent(9); postfixMC[81]="_VH_scale_highmjj_highptDown"; postfixMC[82]="_VH_scale_highmjj_highptUp";}
   }

   // VH lep scale
   if (sample=="WminusH125" or sample=="WplusH125" or sample=="ZH125"){
      if (name.find("WH_PTV_0_75_htt1") < 140 or name.find("WH_PTV_75_150_htt1") < 140 or name.find("WH_PTV_150_250_0J_htt1") < 140 or name.find("WH_PTV_150_250_GE1J_htt1") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_WH_scale_lowpt->GetBinContent(1)/h_QCDScaleAcceptance_WH_scale_lowpt->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_WH_scale_lowpt->GetBinContent(1)/h_QCDScaleAcceptance_WH_scale_lowpt->GetBinContent(9); postfixMC[81]="_WH_scale_lowptDown"; postfixMC[82]="_WH_scale_lowptUp";}
      if (name.find("WH_PTV_GT250_htt1") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_WH_scale_highpt->GetBinContent(1)/h_QCDScaleAcceptance_WH_scale_highpt->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_WH_scale_highpt->GetBinContent(1)/h_QCDScaleAcceptance_WH_scale_highpt->GetBinContent(9); postfixMC[81]="_WH_scale_highptDown"; postfixMC[82]="_WH_scale_highptUp";}
      if (name.find("ZH_PTV_0_75_htt1") < 140 or name.find("ZH_PTV_75_150_htt1") < 140 or name.find("ZH_PTV_150_250_0J_htt1") < 140 or name.find("ZH_PTV_150_250_GE1J_htt1") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_ZH_scale_lowpt->GetBinContent(1)/h_QCDScaleAcceptance_ZH_scale_lowpt->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_ZH_scale_lowpt->GetBinContent(1)/h_QCDScaleAcceptance_ZH_scale_lowpt->GetBinContent(9); postfixMC[81]="_ZH_scale_lowptDown"; postfixMC[82]="_ZH_scale_lowptUp";}
      if (name.find("ZH_PTV_GT250_htt1") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_ZH_scale_highpt->GetBinContent(1)/h_QCDScaleAcceptance_ZH_scale_highpt->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_ZH_scale_highpt->GetBinContent(1)/h_QCDScaleAcceptance_ZH_scale_highpt->GetBinContent(9); postfixMC[81]="_ZH_scale_highptDown"; postfixMC[82]="_ZH_scale_highptUp";}
   }
*/
