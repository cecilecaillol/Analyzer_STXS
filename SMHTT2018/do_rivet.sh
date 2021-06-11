./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/ggH125.root files_nominal_et/ggH125_fwd.root ggH125 ggH_fwd_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/ggH125.root files_nominal_et/ggH125_stage0.root ggH125 ggH_stage0_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/ggH125.root files_nominal_et/ggH125_VBFTOPO_JET3VETO.root ggH125 ggH_VBFTOPO_JET3VETO_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/ggH125.root files_nominal_et/ggH125_VBFTOPO_JET3.root ggH125 ggH_VBFTOPO_JET3_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/ggH125.root files_nominal_et/ggH125_0J.root ggH125 ggH_0J_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/ggH125.root files_nominal_et/ggH125_1J_PTH_0_60.root ggH125 ggH_1J_PTH_0_60_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/ggH125.root files_nominal_et/ggH125_1J_PTH_60_120.root ggH125 ggH_1J_PTH_60_120_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/ggH125.root files_nominal_et/ggH125_1J_PTH_120_200.root ggH125 ggH_1J_PTH_120_200_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/ggH125.root files_nominal_et/ggH125_1J_PTH_GT200.root ggH125 ggH_1J_PTH_GT200_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/ggH125.root files_nominal_et/ggH125_GE2J_PTH_0_60.root ggH125 ggH_GE2J_PTH_0_60_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/ggH125.root files_nominal_et/ggH125_GE2J_PTH_60_120.root ggH125 ggH_GE2J_PTH_60_120_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/ggH125.root files_nominal_et/ggH125_GE2J_PTH_120_200.root ggH125 ggH_GE2J_PTH_120_200_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/ggH125.root files_nominal_et/ggH125_GE2J_PTH_GT200.root ggH125 ggH_GE2J_PTH_GT200_htt125 0
hadd -f files_nominal_et/rivet_ggH125.root files_nominal_et/ggH125_fwd.root files_nominal_et/ggH125_stage0.root ggH125 files_nominal_et/ggH125_VBFTOPO_JET3VETO.root files_nominal_et/ggH125_VBFTOPO_JET3.root files_nominal_et/ggH125_0J.root files_nominal_et/ggH125_1J_PTH_0_60.root files_nominal_et/ggH125_1J_PTH_60_120.root files_nominal_et/ggH125_1J_PTH_120_200.root files_nominal_et/ggH125_1J_PTH_GT200.root files_nominal_et/ggH125_GE2J_PTH_0_60.root files_nominal_et/ggH125_GE2J_PTH_60_120.root files_nominal_et/ggH125_GE2J_PTH_120_200.root files_nominal_et/ggH125_GE2J_PTH_GT200.root

./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/VBF125.root files_nominal_et/VBF125_fwd.root VBF125 qqH_fwd_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/VBF125.root files_nominal_et/VBF125_stage0.root VBF125 qqH_stage0_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/VBF125.root files_nominal_et/VBF125_FWDH.root VBF125 qqH_FWDH_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/VBF125.root files_nominal_et/VBF125_VBFTOPO_JET3VETO.root VBF125 qqH_VBFTOPO_JET3VETO_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/VBF125.root files_nominal_et/VBF125_VBFTOPO_JET3.root VBF125 qqH_VBFTOPO_JET3_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/VBF125.root files_nominal_et/VBF125_VH2JET.root VBF125 qqH_VH2JET_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/VBF125.root files_nominal_et/VBF125_REST.root VBF125 qqH_REST_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/VBF125.root files_nominal_et/VBF125_PTJET1_GT200.root VBF125 qqH_PTJET1_GT200_htt125 0
hadd -f files_nominal_et/rivet_VBF125.root files_nominal_et/VBF125_fwd.root files_nominal_et/VBF125_stage0.root files_nominal_et/VBF125_FWDH.root files_nominal_et/VBF125_VBFTOPO_JET3VETO.root files_nominal_et/VBF125_VBFTOPO_JET3.root files_nominal_et/VBF125_VH2JET.root files_nominal_et/VBF125_REST.root files_nominal_et/VBF125_PTJET1_GT200.root

./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/WplusH125.root files_nominal_et/WplusH_VH_had_125.root WplusH125 VH_had_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/WplusH125.root files_nominal_et/WplusH_WH_lep_fwd_125.root WplusH125 WH_lep_fwd_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/WplusH125.root files_nominal_et/WplusH_WH_lep_125.root WplusH125 WH_lep_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/WplusH125.root files_nominal_et/WplusH_VH_had_VBFTOPO_JET3VETO_125.root WplusH125 VH_had_VBFTOPO_JET3VETO_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/WplusH125.root files_nominal_et/WplusH_VH_had_VBFTOPO_JET3_125.root WplusH125 VH_had_VBFTOPO_JET3_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/WplusH125.root files_nominal_et/WplusH_VH_had_VH2JET_125.root WplusH125 VH_had_VH2JET_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/WplusH125.root files_nominal_et/WplusH_VH_had_REST_125.root WplusH125 VH_had_REST_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/WplusH125.root files_nominal_et/WplusH_VH_had_PTJET1_GT200_125.root WplusH125 VH_had_PTJET1_GT200_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/WplusH125.root files_nominal_et/WplusH_WH_lep_FWDH_125.root WplusH125 WH_lep_FWDH_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/WplusH125.root files_nominal_et/WplusH_WH_lep_PTV_0_150_125.root WplusH125 WH_lep_PTV_0_150_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/WplusH125.root files_nominal_et/WplusH_WH_lep_PTV_150_250_0J_125.root WplusH125 WH_lep_PTV_150_250_0J_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/WplusH125.root files_nominal_et/WplusH_WH_lep_PTV_150_250_GE1J_125.root WplusH125 WH_lep_PTV_150_250_GE1J_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/WplusH125.root files_nominal_et/WplusH_WH_lep_PTV_GT250_125.root WplusH125 WH_lep_PTV_GT250_htt125 0
hadd -f files_nominal_et/rivet_WplusH125.root files_nominal_et/WplusH_VH_had_125.root files_nominal_et/WplusH_WH_lep_fwd_125.root files_nominal_et/WplusH_WH_lep_125.root files_nominal_et/WplusH_VH_had_VBFTOPO_JET3VETO_125.root files_nominal_et/WplusH_VH_had_VBFTOPO_JET3_125.root files_nominal_et/WplusH_VH_had_VH2JET_125.root files_nominal_et/WplusH_VH_had_REST_125.root files_nominal_et/WplusH_VH_had_PTJET1_GT200_125.root files_nominal_et/WplusH_WH_lep_FWDH_125.root files_nominal_et/WplusH_WH_lep_PTV_0_150_125.root files_nominal_et/WplusH_WH_lep_PTV_150_250_0J_125.root files_nominal_et/WplusH_WH_lep_PTV_150_250_GE1J_125.root files_nominal_et/WplusH_WH_lep_PTV_GT250_125.root

./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/WminusH125.root files_nominal_et/WminusH_VH_had_125.root WminusH125 VH_had_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/WminusH125.root files_nominal_et/WminusH_WH_lep_125.root WminusH125 WH_lep_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/WminusH125.root files_nominal_et/WminusH_VH_had_VBFTOPO_JET3VETO_125.root WminusH125 VH_had_VBFTOPO_JET3VETO_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/WminusH125.root files_nominal_et/WminusH_VH_had_VBFTOPO_JET3_125.root WminusH125 VH_had_VBFTOPO_JET3_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/WminusH125.root files_nominal_et/WminusH_VH_had_VH2JET_125.root WminusH125 VH_had_VH2JET_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/WminusH125.root files_nominal_et/WminusH_VH_had_REST_125.root WminusH125 VH_had_REST_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/WminusH125.root files_nominal_et/WminusH_VH_had_PTJET1_GT200_125.root WminusH125 VH_had_PTJET1_GT200_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/WminusH125.root files_nominal_et/WminusH_WH_lep_FWDH_125.root WminusH125 WH_lep_FWDH_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/WminusH125.root files_nominal_et/WminusH_WH_lep_PTV_0_150_125.root WminusH125 WH_lep_PTV_0_150_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/WminusH125.root files_nominal_et/WminusH_WH_lep_PTV_150_250_0J_125.root WminusH125 WH_lep_PTV_150_250_0J_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/WminusH125.root files_nominal_et/WminusH_WH_lep_PTV_150_250_GE1J_125.root WminusH125 WH_lep_PTV_150_250_GE1J_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/WminusH125.root files_nominal_et/WminusH_WH_lep_PTV_GT250_125.root WminusH125 WH_lep_PTV_GT250_htt125 0
hadd -f files_nominal_et/rivet_WminusH125.root files_nominal_et/WminusH_VH_had_125.root files_nominal_et/WminusH_WH_lep_fwd_125.root files_nominal_et/WminusH_WH_lep_125.root files_nominal_et/WminusH_VH_had_VBFTOPO_JET3VETO_125.root files_nominal_et/WminusH_VH_had_VBFTOPO_JET3_125.root files_nominal_et/WminusH_VH_had_VH2JET_125.root files_nominal_et/WminusH_VH_had_REST_125.root files_nominal_et/WminusH_VH_had_PTJET1_GT200_125.root files_nominal_et/WminusH_WH_lep_FWDH_125.root files_nominal_et/WminusH_WH_lep_PTV_0_150_125.root files_nominal_et/WminusH_WH_lep_PTV_150_250_0J_125.root files_nominal_et/WminusH_WH_lep_PTV_150_250_GE1J_125.root files_nominal_et/WminusH_WH_lep_PTV_GT250_125.root

./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/ZH125.root files_nominal_et/ZH_VH_had_fwd_125.root ZH125 VH_had_fwd_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/ZH125.root files_nominal_et/ZH_VH_had_125.root ZH125 VH_had_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/ZH125.root files_nominal_et/ZH_ZH_lep_fwd_125.root ZH125 ZH_lep_fwd_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/ZH125.root files_nominal_et/ZH_ZH_lep_125.root ZH125 ZH_lep_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/ZH125.root files_nominal_et/ZH_VH_had_FWDH_125.root ZH125 VH_had_FWDH_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/ZH125.root files_nominal_et/ZH_VH_had_VBFTOPO_JET3VETO_125.root ZH125 VH_had_VBFTOPO_JET3VETO_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/ZH125.root files_nominal_et/ZH_VH_had_VBFTOPO_JET3_125.root ZH125 VH_had_VBFTOPO_JET3_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/ZH125.root files_nominal_et/ZH_VH_had_VH2JET_125.root ZH125 VH_had_VH2JET_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/ZH125.root files_nominal_et/ZH_VH_had_REST_125.root ZH125 VH_had_REST_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/ZH125.root files_nominal_et/ZH_VH_had_PTJET1_GT200_125.root ZH125 VH_had_PTJET1_GT200_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/ZH125.root files_nominal_et/ZH_ZH_lep_FWDH_125.root ZH125 ZH_lep_FWDH_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/ZH125.root files_nominal_et/ZH_ZH_lep_PTV_0_150_125.root ZH125 ZH_lep_PTV_0_150_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/ZH125.root files_nominal_et/ZH_ZH_lep_PTV_150_250_0J_125.root ZH125 ZH_lep_PTV_150_250_0J_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/ZH125.root files_nominal_et/ZH_ZH_lep_PTV_150_250_GE1J_125.root ZH125 ZH_lep_PTV_150_250_GE1J_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/ZH125.root files_nominal_et/ZH_ZH_lep_PTV_GT250_125.root ZH125 ZH_lep_PTV_GT250_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/ZH125.root files_nominal_et/ZH_VH_had_fwd_125.root ZH125 VH_had_fwd_htt125 0
./FinalSelection_et.exe /data/ccaillol/smhet_9nov_v2/ZH125.root files_nominal_et/ZH_VH_had_fwd_125.root ZH125 VH_had_fwd_htt125 0
hadd -f files_nominal_et/rivet_ZH125.root files_nominal_et/ZH_VH_had_fwd_125.root files_nominal_et/ZH_VH_had_125.root files_nominal_et/ZH_ZH_lep_fwd_125.root files_nominal_et/ZH_ZH_lep_125.root files_nominal_et/ZH_VH_had_FWDH_125.root files_nominal_et/ZH_VH_had_VBFTOPO_JET3VETO_125.root files_nominal_et/ZH_VH_had_VBFTOPO_JET3_125.root files_nominal_et/ZH_VH_had_VH2JET_125.root files_nominal_et/ZH_VH_had_REST_125.root files_nominal_et/ZH_VH_had_PTJET1_GT200_125.root files_nominal_et/ZH_ZH_lep_FWDH_125.root files_nominal_et/ZH_ZH_lep_PTV_0_150_125.root files_nominal_et/ZH_ZH_lep_PTV_150_250_0J_125.root files_nominal_et/ZH_ZH_lep_PTV_150_250_GE1J_125.root files_nominal_et/ZH_ZH_lep_PTV_GT250_125.root files_nominal_et/ZH_VH_had_fwd_125.root files_nominal_et/ZH_VH_had_fwd_125.root 
hadd -f files_nominal_et/rivet.root files_nominal_et/rivet_ZH125.root files_nominal_et/rivet_WplusH125.root files_nominal_et/rivet_WminusH125.root files_nominal_et/rivet_VBF125.root files_nominal_et/rivet_ggH125.root
