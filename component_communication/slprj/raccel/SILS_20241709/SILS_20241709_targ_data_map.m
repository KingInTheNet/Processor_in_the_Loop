    function targMap = targDataMap(),

    ;%***********************
    ;% Create Parameter Map *
    ;%***********************
    
        nTotData      = 0; %add to this count as we go
        nTotSects     = 1;
        sectIdxOffset = 0;

        ;%
        ;% Define dummy sections & preallocate arrays
        ;%
        dumSection.nData = -1;
        dumSection.data  = [];

        dumData.logicalSrcIdx = -1;
        dumData.dtTransOffset = -1;

        ;%
        ;% Init/prealloc paramMap
        ;%
        paramMap.nSections           = nTotSects;
        paramMap.sectIdxOffset       = sectIdxOffset;
            paramMap.sections(nTotSects) = dumSection; %prealloc
        paramMap.nTotData            = -1;

        ;%
        ;% Auto data (rtP)
        ;%
            section.nData     = 396;
            section.data(396)  = dumData; %prealloc

                    ;% rtP.ADSW
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

                    ;% rtP.CD
                    section.data(2).logicalSrcIdx = 1;
                    section.data(2).dtTransOffset = 1;

                    ;% rtP.CR
                    section.data(3).logicalSrcIdx = 2;
                    section.data(3).dtTransOffset = 2;

                    ;% rtP.GAS_Vref
                    section.data(4).logicalSrcIdx = 3;
                    section.data(4).dtTransOffset = 3;

                    ;% rtP.GAS_b2c
                    section.data(5).logicalSrcIdx = 4;
                    section.data(5).dtTransOffset = 4;

                    ;% rtP.GAS_seed1
                    section.data(6).logicalSrcIdx = 5;
                    section.data(6).dtTransOffset = 13;

                    ;% rtP.GE
                    section.data(7).logicalSrcIdx = 6;
                    section.data(7).dtTransOffset = 16;

                    ;% rtP.GGSW
                    section.data(8).logicalSrcIdx = 7;
                    section.data(8).dtTransOffset = 17;

                    ;% rtP.GPS_position_seed
                    section.data(9).logicalSrcIdx = 8;
                    section.data(9).dtTransOffset = 18;

                    ;% rtP.GPS_time_noise
                    section.data(10).logicalSrcIdx = 9;
                    section.data(10).dtTransOffset = 21;

                    ;% rtP.GPS_time_seed
                    section.data(11).logicalSrcIdx = 10;
                    section.data(11).dtTransOffset = 22;

                    ;% rtP.GPperturbationSW
                    section.data(12).logicalSrcIdx = 11;
                    section.data(12).dtTransOffset = 23;

                    ;% rtP.GYRO_b2c
                    section.data(13).logicalSrcIdx = 12;
                    section.data(13).dtTransOffset = 24;

                    ;% rtP.GYRO_seed1
                    section.data(14).logicalSrcIdx = 13;
                    section.data(14).dtTransOffset = 33;

                    ;% rtP.GYRO_seed2
                    section.data(15).logicalSrcIdx = 14;
                    section.data(15).dtTransOffset = 36;

                    ;% rtP.I
                    section.data(16).logicalSrcIdx = 15;
                    section.data(16).dtTransOffset = 39;

                    ;% rtP.J2
                    section.data(17).logicalSrcIdx = 16;
                    section.data(17).dtTransOffset = 48;

                    ;% rtP.MTQ_c2b
                    section.data(18).logicalSrcIdx = 17;
                    section.data(18).dtTransOffset = 49;

                    ;% rtP.NSAS1_b2c
                    section.data(19).logicalSrcIdx = 18;
                    section.data(19).dtTransOffset = 52;

                    ;% rtP.NSAS2_b2c
                    section.data(20).logicalSrcIdx = 19;
                    section.data(20).dtTransOffset = 61;

                    ;% rtP.NSAS3_b2c
                    section.data(21).logicalSrcIdx = 20;
                    section.data(21).dtTransOffset = 70;

                    ;% rtP.NSAS4_b2c
                    section.data(22).logicalSrcIdx = 21;
                    section.data(22).dtTransOffset = 79;

                    ;% rtP.NSAS5_b2c
                    section.data(23).logicalSrcIdx = 22;
                    section.data(23).dtTransOffset = 88;

                    ;% rtP.NSAS6_b2c
                    section.data(24).logicalSrcIdx = 23;
                    section.data(24).dtTransOffset = 97;

                    ;% rtP.NSAS_ang_limit
                    section.data(25).logicalSrcIdx = 24;
                    section.data(25).dtTransOffset = 106;

                    ;% rtP.NSAS_seed1
                    section.data(26).logicalSrcIdx = 25;
                    section.data(26).dtTransOffset = 107;

                    ;% rtP.NSAS_seed2
                    section.data(27).logicalSrcIdx = 26;
                    section.data(27).dtTransOffset = 108;

                    ;% rtP.NSAS_x_noise
                    section.data(28).logicalSrcIdx = 27;
                    section.data(28).dtTransOffset = 109;

                    ;% rtP.NSAS_y_noise
                    section.data(29).logicalSrcIdx = 28;
                    section.data(29).dtTransOffset = 110;

                    ;% rtP.RW_Gamp
                    section.data(30).logicalSrcIdx = 29;
                    section.data(30).dtTransOffset = 111;

                    ;% rtP.RW_J
                    section.data(31).logicalSrcIdx = 30;
                    section.data(31).dtTransOffset = 112;

                    ;% rtP.RW_Rsc
                    section.data(32).logicalSrcIdx = 31;
                    section.data(32).dtTransOffset = 113;

                    ;% rtP.RW_kE
                    section.data(33).logicalSrcIdx = 32;
                    section.data(33).dtTransOffset = 114;

                    ;% rtP.RW_kT
                    section.data(34).logicalSrcIdx = 33;
                    section.data(34).dtTransOffset = 115;

                    ;% rtP.SRPSW
                    section.data(35).logicalSrcIdx = 34;
                    section.data(35).dtTransOffset = 116;

                    ;% rtP.STT1_b2c_quat
                    section.data(36).logicalSrcIdx = 35;
                    section.data(36).dtTransOffset = 117;

                    ;% rtP.STT_AD_prob
                    section.data(37).logicalSrcIdx = 36;
                    section.data(37).dtTransOffset = 121;

                    ;% rtP.STT_FOV
                    section.data(38).logicalSrcIdx = 37;
                    section.data(38).dtTransOffset = 122;

                    ;% rtP.STT_moon_ang_limit
                    section.data(39).logicalSrcIdx = 38;
                    section.data(39).dtTransOffset = 123;

                    ;% rtP.STT_seed1
                    section.data(40).logicalSrcIdx = 39;
                    section.data(40).dtTransOffset = 124;

                    ;% rtP.STT_sun_ang_limit
                    section.data(41).logicalSrcIdx = 40;
                    section.data(41).dtTransOffset = 127;

                    ;% rtP.TOLERANCE
                    section.data(42).logicalSrcIdx = 41;
                    section.data(42).dtTransOffset = 128;

                    ;% rtP.UT1_UTC
                    section.data(43).logicalSrcIdx = 42;
                    section.data(43).dtTransOffset = 129;

                    ;% rtP.area
                    section.data(44).logicalSrcIdx = 43;
                    section.data(44).dtTransOffset = 130;

                    ;% rtP.arm
                    section.data(45).logicalSrcIdx = 44;
                    section.data(45).dtTransOffset = 131;

                    ;% rtP.earth_radius
                    section.data(46).logicalSrcIdx = 45;
                    section.data(46).dtTransOffset = 134;

                    ;% rtP.ele
                    section.data(47).logicalSrcIdx = 46;
                    section.data(47).dtTransOffset = 135;

                    ;% rtP.jd
                    section.data(48).logicalSrcIdx = 47;
                    section.data(48).dtTransOffset = 141;

                    ;% rtP.pSR
                    section.data(49).logicalSrcIdx = 48;
                    section.data(49).dtTransOffset = 142;

                    ;% rtP.q_ini
                    section.data(50).logicalSrcIdx = 49;
                    section.data(50).dtTransOffset = 143;

                    ;% rtP.rem_mag
                    section.data(51).logicalSrcIdx = 50;
                    section.data(51).dtTransOffset = 147;

                    ;% rtP.rem_magSW
                    section.data(52).logicalSrcIdx = 51;
                    section.data(52).dtTransOffset = 150;

                    ;% rtP.three_one_skew_matrix
                    section.data(53).logicalSrcIdx = 52;
                    section.data(53).dtTransOffset = 151;

                    ;% rtP.wE
                    section.data(54).logicalSrcIdx = 53;
                    section.data(54).dtTransOffset = 163;

                    ;% rtP.w_ini
                    section.data(55).logicalSrcIdx = 54;
                    section.data(55).dtTransOffset = 166;

                    ;% rtP.z0_const
                    section.data(56).logicalSrcIdx = 55;
                    section.data(56).dtTransOffset = 169;

                    ;% rtP.z0_const_m1oeisvxny
                    section.data(57).logicalSrcIdx = 56;
                    section.data(57).dtTransOffset = 170;

                    ;% rtP.z0_const_gejhxxdnvf
                    section.data(58).logicalSrcIdx = 57;
                    section.data(58).dtTransOffset = 171;

                    ;% rtP.z0_const_otzh2whnvs
                    section.data(59).logicalSrcIdx = 58;
                    section.data(59).dtTransOffset = 172;

                    ;% rtP.z0_const_h3tpk4wmcz
                    section.data(60).logicalSrcIdx = 59;
                    section.data(60).dtTransOffset = 173;

                    ;% rtP.z0_const_pdn2lzrjdp
                    section.data(61).logicalSrcIdx = 60;
                    section.data(61).dtTransOffset = 174;

                    ;% rtP.NormalizeVector_maxzero
                    section.data(62).logicalSrcIdx = 61;
                    section.data(62).dtTransOffset = 175;

                    ;% rtP.NormalizeVector_maxzero_lpqo5h1ax3
                    section.data(63).logicalSrcIdx = 62;
                    section.data(63).dtTransOffset = 176;

                    ;% rtP.NormalizeVector_maxzero_p5fqgxj0sr
                    section.data(64).logicalSrcIdx = 63;
                    section.data(64).dtTransOffset = 177;

                    ;% rtP.NormalizeVector_maxzero_jad2sd3ugf
                    section.data(65).logicalSrcIdx = 64;
                    section.data(65).dtTransOffset = 178;

                    ;% rtP.NormalizeVector_maxzero_pk2yr3b0h2
                    section.data(66).logicalSrcIdx = 65;
                    section.data(66).dtTransOffset = 179;

                    ;% rtP.NormalizeVector_maxzero_mjhj4dvvo1
                    section.data(67).logicalSrcIdx = 66;
                    section.data(67).dtTransOffset = 180;

                    ;% rtP.NormalizeVector_maxzero_hdshd0fhdt
                    section.data(68).logicalSrcIdx = 67;
                    section.data(68).dtTransOffset = 181;

                    ;% rtP.NormalizeVector_maxzero_ngb4rhu5uq
                    section.data(69).logicalSrcIdx = 68;
                    section.data(69).dtTransOffset = 182;

                    ;% rtP.NormalizeVector_maxzero_lt2ddtxhuf
                    section.data(70).logicalSrcIdx = 69;
                    section.data(70).dtTransOffset = 183;

                    ;% rtP.NormalizeVector_maxzero_bj3cfn3har
                    section.data(71).logicalSrcIdx = 70;
                    section.data(71).dtTransOffset = 184;

                    ;% rtP.hour2sec_Gain
                    section.data(72).logicalSrcIdx = 71;
                    section.data(72).dtTransOffset = 185;

                    ;% rtP.min2sec_Gain
                    section.data(73).logicalSrcIdx = 72;
                    section.data(73).dtTransOffset = 186;

                    ;% rtP.gcm3kgm3_Gain
                    section.data(74).logicalSrcIdx = 73;
                    section.data(74).dtTransOffset = 187;

                    ;% rtP.Gain_Gain
                    section.data(75).logicalSrcIdx = 74;
                    section.data(75).dtTransOffset = 188;

                    ;% rtP.Gain1_Gain
                    section.data(76).logicalSrcIdx = 75;
                    section.data(76).dtTransOffset = 189;

                    ;% rtP.Gain2_Gain
                    section.data(77).logicalSrcIdx = 76;
                    section.data(77).dtTransOffset = 190;

                    ;% rtP.Gain_Gain_dkxjnn2goq
                    section.data(78).logicalSrcIdx = 77;
                    section.data(78).dtTransOffset = 191;

                    ;% rtP.Gain1_Gain_ewxpcgxoho
                    section.data(79).logicalSrcIdx = 78;
                    section.data(79).dtTransOffset = 192;

                    ;% rtP.Gain2_Gain_lev0onxthq
                    section.data(80).logicalSrcIdx = 79;
                    section.data(80).dtTransOffset = 193;

                    ;% rtP.Gain_Gain_kwo0jnespy
                    section.data(81).logicalSrcIdx = 80;
                    section.data(81).dtTransOffset = 194;

                    ;% rtP.Gain1_Gain_oz4csetmxu
                    section.data(82).logicalSrcIdx = 81;
                    section.data(82).dtTransOffset = 195;

                    ;% rtP.Gain2_Gain_ekmxnyjdgq
                    section.data(83).logicalSrcIdx = 82;
                    section.data(83).dtTransOffset = 196;

                    ;% rtP.Constant_Value
                    section.data(84).logicalSrcIdx = 83;
                    section.data(84).dtTransOffset = 197;

                    ;% rtP.Constant_Value_kjzrxx2pwp
                    section.data(85).logicalSrcIdx = 84;
                    section.data(85).dtTransOffset = 198;

                    ;% rtP.Constant_Value_a2453xvslr
                    section.data(86).logicalSrcIdx = 85;
                    section.data(86).dtTransOffset = 199;

                    ;% rtP.F107_Value
                    section.data(87).logicalSrcIdx = 86;
                    section.data(87).dtTransOffset = 200;

                    ;% rtP.aph_Value
                    section.data(88).logicalSrcIdx = 87;
                    section.data(88).dtTransOffset = 201;

                    ;% rtP.flag_Value
                    section.data(89).logicalSrcIdx = 88;
                    section.data(89).dtTransOffset = 208;

                    ;% rtP.GPperturbation_RSW_kms2_3_Y0
                    section.data(90).logicalSrcIdx = 89;
                    section.data(90).dtTransOffset = 231;

                    ;% rtP.deg2rad_Gain
                    section.data(91).logicalSrcIdx = 90;
                    section.data(91).dtTransOffset = 234;

                    ;% rtP.GG_b_Nm_3_Y0
                    section.data(92).logicalSrcIdx = 91;
                    section.data(92).dtTransOffset = 235;

                    ;% rtP.Gain2_Gain_nbadgk3cn2
                    section.data(93).logicalSrcIdx = 92;
                    section.data(93).dtTransOffset = 238;

                    ;% rtP.Gain_Gain_eirpwpy25e
                    section.data(94).logicalSrcIdx = 93;
                    section.data(94).dtTransOffset = 239;

                    ;% rtP.Gain1_Gain_o0zodm4wod
                    section.data(95).logicalSrcIdx = 94;
                    section.data(95).dtTransOffset = 240;

                    ;% rtP.Gain_Gain_cng034c550
                    section.data(96).logicalSrcIdx = 95;
                    section.data(96).dtTransOffset = 241;

                    ;% rtP.Gain2_Gain_jw4ny4s1oi
                    section.data(97).logicalSrcIdx = 96;
                    section.data(97).dtTransOffset = 242;

                    ;% rtP.Gain1_Gain_kzqbx21odb
                    section.data(98).logicalSrcIdx = 97;
                    section.data(98).dtTransOffset = 243;

                    ;% rtP.Gain_Gain_lv4xtg4q1g
                    section.data(99).logicalSrcIdx = 98;
                    section.data(99).dtTransOffset = 244;

                    ;% rtP.Gain1_Gain_pmepj0f34k
                    section.data(100).logicalSrcIdx = 99;
                    section.data(100).dtTransOffset = 245;

                    ;% rtP.Gain2_Gain_nafalxbj3s
                    section.data(101).logicalSrcIdx = 100;
                    section.data(101).dtTransOffset = 246;

                    ;% rtP.Constant_Value_p1jiuwoh41
                    section.data(102).logicalSrcIdx = 101;
                    section.data(102).dtTransOffset = 247;

                    ;% rtP.Constant_Value_boboxxtlqz
                    section.data(103).logicalSrcIdx = 102;
                    section.data(103).dtTransOffset = 248;

                    ;% rtP.Constant_Value_gtgl4kppkk
                    section.data(104).logicalSrcIdx = 103;
                    section.data(104).dtTransOffset = 249;

                    ;% rtP.remmag_b_Nm_3_Y0
                    section.data(105).logicalSrcIdx = 104;
                    section.data(105).dtTransOffset = 250;

                    ;% rtP.nT2T_Gain
                    section.data(106).logicalSrcIdx = 105;
                    section.data(106).dtTransOffset = 253;

                    ;% rtP.SRP_b_Nm_3_Y0
                    section.data(107).logicalSrcIdx = 106;
                    section.data(107).dtTransOffset = 254;

                    ;% rtP.Gain_Gain_kpmqxdzy5m
                    section.data(108).logicalSrcIdx = 107;
                    section.data(108).dtTransOffset = 257;

                    ;% rtP.Gain1_Gain_k3bjbhd2mm
                    section.data(109).logicalSrcIdx = 108;
                    section.data(109).dtTransOffset = 258;

                    ;% rtP.Gain2_Gain_pyvsmmmr0o
                    section.data(110).logicalSrcIdx = 109;
                    section.data(110).dtTransOffset = 259;

                    ;% rtP.Gain_Gain_bsruw13utp
                    section.data(111).logicalSrcIdx = 110;
                    section.data(111).dtTransOffset = 260;

                    ;% rtP.Gain1_Gain_gox4r1jkwy
                    section.data(112).logicalSrcIdx = 111;
                    section.data(112).dtTransOffset = 261;

                    ;% rtP.Gain2_Gain_gvo2u1fvu1
                    section.data(113).logicalSrcIdx = 112;
                    section.data(113).dtTransOffset = 262;

                    ;% rtP.Gain_Gain_b0hzjatx0r
                    section.data(114).logicalSrcIdx = 113;
                    section.data(114).dtTransOffset = 263;

                    ;% rtP.Gain1_Gain_i30g2qbzrq
                    section.data(115).logicalSrcIdx = 114;
                    section.data(115).dtTransOffset = 264;

                    ;% rtP.Gain2_Gain_p5meiylvde
                    section.data(116).logicalSrcIdx = 115;
                    section.data(116).dtTransOffset = 265;

                    ;% rtP.Constant_Value_n0n1a4zdn2
                    section.data(117).logicalSrcIdx = 116;
                    section.data(117).dtTransOffset = 266;

                    ;% rtP.Constant_Value_ckovqqesxd
                    section.data(118).logicalSrcIdx = 117;
                    section.data(118).dtTransOffset = 267;

                    ;% rtP.Constant_Value_og0eeytiqd
                    section.data(119).logicalSrcIdx = 118;
                    section.data(119).dtTransOffset = 268;

                    ;% rtP.Constant_Value_dxdbvme4z2
                    section.data(120).logicalSrcIdx = 119;
                    section.data(120).dtTransOffset = 269;

                    ;% rtP.rad2deg_Gain
                    section.data(121).logicalSrcIdx = 120;
                    section.data(121).dtTransOffset = 270;

                    ;% rtP.rad2deg_Gain_lqcbchbdpx
                    section.data(122).logicalSrcIdx = 121;
                    section.data(122).dtTransOffset = 271;

                    ;% rtP.rad2deg_Gain_asjrxybn0x
                    section.data(123).logicalSrcIdx = 122;
                    section.data(123).dtTransOffset = 272;

                    ;% rtP.rad2deg_Gain_okxkrd2arw
                    section.data(124).logicalSrcIdx = 123;
                    section.data(124).dtTransOffset = 273;

                    ;% rtP.rad2deg_Gain_cmtkrwe5gj
                    section.data(125).logicalSrcIdx = 124;
                    section.data(125).dtTransOffset = 274;

                    ;% rtP.rad2deg_Gain_ncnor3j1vi
                    section.data(126).logicalSrcIdx = 125;
                    section.data(126).dtTransOffset = 275;

                    ;% rtP.sec_per_day_Gain
                    section.data(127).logicalSrcIdx = 126;
                    section.data(127).dtTransOffset = 276;

                    ;% rtP.Gain_Gain_itrtl3m3mg
                    section.data(128).logicalSrcIdx = 127;
                    section.data(128).dtTransOffset = 277;

                    ;% rtP.Gain2_Gain_ckacseigw1
                    section.data(129).logicalSrcIdx = 128;
                    section.data(129).dtTransOffset = 278;

                    ;% rtP.Gain_Gain_l1oovl4sve
                    section.data(130).logicalSrcIdx = 129;
                    section.data(130).dtTransOffset = 279;

                    ;% rtP.Gain1_Gain_bysm1h5wxu
                    section.data(131).logicalSrcIdx = 130;
                    section.data(131).dtTransOffset = 280;

                    ;% rtP.Gain_Gain_iduukqmyr5
                    section.data(132).logicalSrcIdx = 131;
                    section.data(132).dtTransOffset = 281;

                    ;% rtP.Gain2_Gain_kdxyjqh15k
                    section.data(133).logicalSrcIdx = 132;
                    section.data(133).dtTransOffset = 282;

                    ;% rtP.Gain1_Gain_bv1sce1ofn
                    section.data(134).logicalSrcIdx = 133;
                    section.data(134).dtTransOffset = 283;

                    ;% rtP.Gain_Gain_py1ocxtdbg
                    section.data(135).logicalSrcIdx = 134;
                    section.data(135).dtTransOffset = 284;

                    ;% rtP.Gain1_Gain_jhnqeojsbu
                    section.data(136).logicalSrcIdx = 135;
                    section.data(136).dtTransOffset = 285;

                    ;% rtP.Gain2_Gain_dmh23oivep
                    section.data(137).logicalSrcIdx = 136;
                    section.data(137).dtTransOffset = 286;

                    ;% rtP.TransferFcn1_A
                    section.data(138).logicalSrcIdx = 137;
                    section.data(138).dtTransOffset = 287;

                    ;% rtP.TransferFcn1_C
                    section.data(139).logicalSrcIdx = 138;
                    section.data(139).dtTransOffset = 288;

                    ;% rtP.Integrator_IC
                    section.data(140).logicalSrcIdx = 139;
                    section.data(140).dtTransOffset = 289;

                    ;% rtP.motor_D
                    section.data(141).logicalSrcIdx = 140;
                    section.data(141).dtTransOffset = 290;

                    ;% rtP.Switch1_Threshold
                    section.data(142).logicalSrcIdx = 141;
                    section.data(142).dtTransOffset = 291;

                    ;% rtP.rad2rpm_Gain
                    section.data(143).logicalSrcIdx = 142;
                    section.data(143).dtTransOffset = 292;

                    ;% rtP.SFunction2_P1_Size
                    section.data(144).logicalSrcIdx = 143;
                    section.data(144).dtTransOffset = 293;

                    ;% rtP.SFunction2_P1
                    section.data(145).logicalSrcIdx = 144;
                    section.data(145).dtTransOffset = 295;

                    ;% rtP.TransferFcn1_A_dpe12qdgeu
                    section.data(146).logicalSrcIdx = 145;
                    section.data(146).dtTransOffset = 296;

                    ;% rtP.TransferFcn1_C_mq40l21bd4
                    section.data(147).logicalSrcIdx = 146;
                    section.data(147).dtTransOffset = 297;

                    ;% rtP.Integrator_IC_mzfuiafljt
                    section.data(148).logicalSrcIdx = 147;
                    section.data(148).dtTransOffset = 298;

                    ;% rtP.motor_D_c2y52zc0tt
                    section.data(149).logicalSrcIdx = 148;
                    section.data(149).dtTransOffset = 299;

                    ;% rtP.Switch1_Threshold_gkzjd52v3i
                    section.data(150).logicalSrcIdx = 149;
                    section.data(150).dtTransOffset = 300;

                    ;% rtP.rad2rpm_Gain_l4jmsoyq2v
                    section.data(151).logicalSrcIdx = 150;
                    section.data(151).dtTransOffset = 301;

                    ;% rtP.SFunction7_P1_Size
                    section.data(152).logicalSrcIdx = 151;
                    section.data(152).dtTransOffset = 302;

                    ;% rtP.SFunction7_P1
                    section.data(153).logicalSrcIdx = 152;
                    section.data(153).dtTransOffset = 304;

                    ;% rtP.TransferFcn1_A_iljtckl0vf
                    section.data(154).logicalSrcIdx = 153;
                    section.data(154).dtTransOffset = 305;

                    ;% rtP.TransferFcn1_C_e5t3t2za0w
                    section.data(155).logicalSrcIdx = 154;
                    section.data(155).dtTransOffset = 306;

                    ;% rtP.Integrator_IC_hzjgu55ip5
                    section.data(156).logicalSrcIdx = 155;
                    section.data(156).dtTransOffset = 307;

                    ;% rtP.motor_D_p4qvhshwgu
                    section.data(157).logicalSrcIdx = 156;
                    section.data(157).dtTransOffset = 308;

                    ;% rtP.Switch1_Threshold_lagl2moogx
                    section.data(158).logicalSrcIdx = 157;
                    section.data(158).dtTransOffset = 309;

                    ;% rtP.rad2rpm_Gain_nwcckeryhk
                    section.data(159).logicalSrcIdx = 158;
                    section.data(159).dtTransOffset = 310;

                    ;% rtP.SFunction8_P1_Size
                    section.data(160).logicalSrcIdx = 159;
                    section.data(160).dtTransOffset = 311;

                    ;% rtP.SFunction8_P1
                    section.data(161).logicalSrcIdx = 160;
                    section.data(161).dtTransOffset = 313;

                    ;% rtP.TransferFcn1_A_bf2c2hk3jc
                    section.data(162).logicalSrcIdx = 161;
                    section.data(162).dtTransOffset = 314;

                    ;% rtP.TransferFcn1_C_exc4t4wdx0
                    section.data(163).logicalSrcIdx = 162;
                    section.data(163).dtTransOffset = 315;

                    ;% rtP.Integrator_IC_ly1tqocwk2
                    section.data(164).logicalSrcIdx = 163;
                    section.data(164).dtTransOffset = 316;

                    ;% rtP.motor_D_ngzzpzruyi
                    section.data(165).logicalSrcIdx = 164;
                    section.data(165).dtTransOffset = 317;

                    ;% rtP.Switch1_Threshold_nalfp5zuzj
                    section.data(166).logicalSrcIdx = 165;
                    section.data(166).dtTransOffset = 318;

                    ;% rtP.rad2rpm_Gain_pceq0ixqio
                    section.data(167).logicalSrcIdx = 166;
                    section.data(167).dtTransOffset = 319;

                    ;% rtP.SFunction9_P1_Size
                    section.data(168).logicalSrcIdx = 167;
                    section.data(168).dtTransOffset = 320;

                    ;% rtP.SFunction9_P1
                    section.data(169).logicalSrcIdx = 168;
                    section.data(169).dtTransOffset = 322;

                    ;% rtP.noise1_Mean
                    section.data(170).logicalSrcIdx = 169;
                    section.data(170).dtTransOffset = 323;

                    ;% rtP.noise1_StdDev
                    section.data(171).logicalSrcIdx = 170;
                    section.data(171).dtTransOffset = 326;

                    ;% rtP.UniformRandomNumber_Minimum
                    section.data(172).logicalSrcIdx = 171;
                    section.data(172).dtTransOffset = 329;

                    ;% rtP.UniformRandomNumber_Maximum
                    section.data(173).logicalSrcIdx = 172;
                    section.data(173).dtTransOffset = 330;

                    ;% rtP.UniformRandomNumber_Seed
                    section.data(174).logicalSrcIdx = 173;
                    section.data(174).dtTransOffset = 331;

                    ;% rtP.Gain_Gain_c5svou2zai
                    section.data(175).logicalSrcIdx = 174;
                    section.data(175).dtTransOffset = 332;

                    ;% rtP.Gain2_Gain_fbbevcwdu4
                    section.data(176).logicalSrcIdx = 175;
                    section.data(176).dtTransOffset = 333;

                    ;% rtP.Gain_Gain_fso4j4ph32
                    section.data(177).logicalSrcIdx = 176;
                    section.data(177).dtTransOffset = 334;

                    ;% rtP.Gain1_Gain_c2qfvofd2q
                    section.data(178).logicalSrcIdx = 177;
                    section.data(178).dtTransOffset = 335;

                    ;% rtP.Gain_Gain_cuyfsgurxk
                    section.data(179).logicalSrcIdx = 178;
                    section.data(179).dtTransOffset = 336;

                    ;% rtP.Gain2_Gain_o2m2nfo04s
                    section.data(180).logicalSrcIdx = 179;
                    section.data(180).dtTransOffset = 337;

                    ;% rtP.Gain1_Gain_p0weipavif
                    section.data(181).logicalSrcIdx = 180;
                    section.data(181).dtTransOffset = 338;

                    ;% rtP.Gain_Gain_mtzedpzgxf
                    section.data(182).logicalSrcIdx = 181;
                    section.data(182).dtTransOffset = 339;

                    ;% rtP.Gain1_Gain_fpivyqdmyd
                    section.data(183).logicalSrcIdx = 182;
                    section.data(183).dtTransOffset = 340;

                    ;% rtP.Gain2_Gain_eknqknt03s
                    section.data(184).logicalSrcIdx = 183;
                    section.data(184).dtTransOffset = 341;

                    ;% rtP.km2m_Gain
                    section.data(185).logicalSrcIdx = 184;
                    section.data(185).dtTransOffset = 342;

                    ;% rtP.ECEFPositiontoLLA_F
                    section.data(186).logicalSrcIdx = 185;
                    section.data(186).dtTransOffset = 343;

                    ;% rtP.ECEFPositiontoLLA_R
                    section.data(187).logicalSrcIdx = 186;
                    section.data(187).dtTransOffset = 344;

                    ;% rtP.m2km_Gain
                    section.data(188).logicalSrcIdx = 187;
                    section.data(188).dtTransOffset = 345;

                    ;% rtP.Gain2_Gain_bprrd5rgzt
                    section.data(189).logicalSrcIdx = 188;
                    section.data(189).dtTransOffset = 346;

                    ;% rtP.Gain_Gain_p0g5ioz0tt
                    section.data(190).logicalSrcIdx = 189;
                    section.data(190).dtTransOffset = 347;

                    ;% rtP.Gain1_Gain_l1syl1i1nc
                    section.data(191).logicalSrcIdx = 190;
                    section.data(191).dtTransOffset = 348;

                    ;% rtP.Gain_Gain_cdekolw0kh
                    section.data(192).logicalSrcIdx = 191;
                    section.data(192).dtTransOffset = 349;

                    ;% rtP.Gain2_Gain_inxlw0u2vd
                    section.data(193).logicalSrcIdx = 192;
                    section.data(193).dtTransOffset = 350;

                    ;% rtP.Gain1_Gain_mbywpxkyv2
                    section.data(194).logicalSrcIdx = 193;
                    section.data(194).dtTransOffset = 351;

                    ;% rtP.Gain_Gain_gnbof3p2ih
                    section.data(195).logicalSrcIdx = 194;
                    section.data(195).dtTransOffset = 352;

                    ;% rtP.Gain1_Gain_ai10xj1huz
                    section.data(196).logicalSrcIdx = 195;
                    section.data(196).dtTransOffset = 353;

                    ;% rtP.Gain2_Gain_aryjtg3qqc
                    section.data(197).logicalSrcIdx = 196;
                    section.data(197).dtTransOffset = 354;

                    ;% rtP.Constant_Value_i11k1gefwq
                    section.data(198).logicalSrcIdx = 197;
                    section.data(198).dtTransOffset = 355;

                    ;% rtP.SFunction6_P1_Size
                    section.data(199).logicalSrcIdx = 198;
                    section.data(199).dtTransOffset = 358;

                    ;% rtP.SFunction6_P1
                    section.data(200).logicalSrcIdx = 199;
                    section.data(200).dtTransOffset = 360;

                    ;% rtP.SFunction6_P2_Size
                    section.data(201).logicalSrcIdx = 200;
                    section.data(201).dtTransOffset = 361;

                    ;% rtP.SFunction6_P2
                    section.data(202).logicalSrcIdx = 201;
                    section.data(202).dtTransOffset = 363;

                    ;% rtP.TransferFcn_A
                    section.data(203).logicalSrcIdx = 202;
                    section.data(203).dtTransOffset = 364;

                    ;% rtP.TransferFcn_C
                    section.data(204).logicalSrcIdx = 203;
                    section.data(204).dtTransOffset = 366;

                    ;% rtP.TransferFcn1_A_if5catdafx
                    section.data(205).logicalSrcIdx = 204;
                    section.data(205).dtTransOffset = 368;

                    ;% rtP.TransferFcn1_C_dr34rukazf
                    section.data(206).logicalSrcIdx = 205;
                    section.data(206).dtTransOffset = 370;

                    ;% rtP.TransferFcn2_A
                    section.data(207).logicalSrcIdx = 206;
                    section.data(207).dtTransOffset = 372;

                    ;% rtP.TransferFcn2_C
                    section.data(208).logicalSrcIdx = 207;
                    section.data(208).dtTransOffset = 374;

                    ;% rtP.Constant5_Value
                    section.data(209).logicalSrcIdx = 208;
                    section.data(209).dtTransOffset = 376;

                    ;% rtP.SFunction_P1_Size
                    section.data(210).logicalSrcIdx = 209;
                    section.data(210).dtTransOffset = 377;

                    ;% rtP.SFunction_P1
                    section.data(211).logicalSrcIdx = 210;
                    section.data(211).dtTransOffset = 379;

                    ;% rtP.SFunction_P2_Size
                    section.data(212).logicalSrcIdx = 211;
                    section.data(212).dtTransOffset = 380;

                    ;% rtP.SFunction_P2
                    section.data(213).logicalSrcIdx = 212;
                    section.data(213).dtTransOffset = 382;

                    ;% rtP.noise_Mean
                    section.data(214).logicalSrcIdx = 213;
                    section.data(214).dtTransOffset = 383;

                    ;% rtP.noise1_Mean_gvm1mdzxhn
                    section.data(215).logicalSrcIdx = 214;
                    section.data(215).dtTransOffset = 384;

                    ;% rtP.SFunction2_P1_Size_aqgqx4ctqe
                    section.data(216).logicalSrcIdx = 215;
                    section.data(216).dtTransOffset = 385;

                    ;% rtP.SFunction2_P1_psdu2cwwwx
                    section.data(217).logicalSrcIdx = 216;
                    section.data(217).dtTransOffset = 387;

                    ;% rtP.SFunction2_P2_Size
                    section.data(218).logicalSrcIdx = 217;
                    section.data(218).dtTransOffset = 388;

                    ;% rtP.SFunction2_P2
                    section.data(219).logicalSrcIdx = 218;
                    section.data(219).dtTransOffset = 390;

                    ;% rtP.noise_Mean_ieihuy3dfl
                    section.data(220).logicalSrcIdx = 219;
                    section.data(220).dtTransOffset = 391;

                    ;% rtP.noise1_Mean_dss5wuzq4c
                    section.data(221).logicalSrcIdx = 220;
                    section.data(221).dtTransOffset = 392;

                    ;% rtP.SFunction3_P1_Size
                    section.data(222).logicalSrcIdx = 221;
                    section.data(222).dtTransOffset = 393;

                    ;% rtP.SFunction3_P1
                    section.data(223).logicalSrcIdx = 222;
                    section.data(223).dtTransOffset = 395;

                    ;% rtP.SFunction3_P2_Size
                    section.data(224).logicalSrcIdx = 223;
                    section.data(224).dtTransOffset = 396;

                    ;% rtP.SFunction3_P2
                    section.data(225).logicalSrcIdx = 224;
                    section.data(225).dtTransOffset = 398;

                    ;% rtP.noise_Mean_frav3j55dx
                    section.data(226).logicalSrcIdx = 225;
                    section.data(226).dtTransOffset = 399;

                    ;% rtP.noise1_Mean_mtptilkq10
                    section.data(227).logicalSrcIdx = 226;
                    section.data(227).dtTransOffset = 400;

                    ;% rtP.SFunction4_P1_Size
                    section.data(228).logicalSrcIdx = 227;
                    section.data(228).dtTransOffset = 401;

                    ;% rtP.SFunction4_P1
                    section.data(229).logicalSrcIdx = 228;
                    section.data(229).dtTransOffset = 403;

                    ;% rtP.SFunction4_P2_Size
                    section.data(230).logicalSrcIdx = 229;
                    section.data(230).dtTransOffset = 404;

                    ;% rtP.SFunction4_P2
                    section.data(231).logicalSrcIdx = 230;
                    section.data(231).dtTransOffset = 406;

                    ;% rtP.noise_Mean_gbwkny3l3m
                    section.data(232).logicalSrcIdx = 231;
                    section.data(232).dtTransOffset = 407;

                    ;% rtP.noise1_Mean_k2frfueqdx
                    section.data(233).logicalSrcIdx = 232;
                    section.data(233).dtTransOffset = 408;

                    ;% rtP.SFunction7_P1_Size_buxc0ymhsr
                    section.data(234).logicalSrcIdx = 233;
                    section.data(234).dtTransOffset = 409;

                    ;% rtP.SFunction7_P1_c0oipohs5p
                    section.data(235).logicalSrcIdx = 234;
                    section.data(235).dtTransOffset = 411;

                    ;% rtP.SFunction7_P2_Size
                    section.data(236).logicalSrcIdx = 235;
                    section.data(236).dtTransOffset = 412;

                    ;% rtP.SFunction7_P2
                    section.data(237).logicalSrcIdx = 236;
                    section.data(237).dtTransOffset = 414;

                    ;% rtP.noise_Mean_fjgbzgisby
                    section.data(238).logicalSrcIdx = 237;
                    section.data(238).dtTransOffset = 415;

                    ;% rtP.noise1_Mean_jkwutj3nv4
                    section.data(239).logicalSrcIdx = 238;
                    section.data(239).dtTransOffset = 416;

                    ;% rtP.SFunction8_P1_Size_otc42vq3fz
                    section.data(240).logicalSrcIdx = 239;
                    section.data(240).dtTransOffset = 417;

                    ;% rtP.SFunction8_P1_ddvmotdhun
                    section.data(241).logicalSrcIdx = 240;
                    section.data(241).dtTransOffset = 419;

                    ;% rtP.SFunction8_P2_Size
                    section.data(242).logicalSrcIdx = 241;
                    section.data(242).dtTransOffset = 420;

                    ;% rtP.SFunction8_P2
                    section.data(243).logicalSrcIdx = 242;
                    section.data(243).dtTransOffset = 422;

                    ;% rtP.noise_Mean_hueo1gemyg
                    section.data(244).logicalSrcIdx = 243;
                    section.data(244).dtTransOffset = 423;

                    ;% rtP.noise1_Mean_m2yixhjiff
                    section.data(245).logicalSrcIdx = 244;
                    section.data(245).dtTransOffset = 424;

                    ;% rtP.SFunction9_P1_Size_ncpscvdwkx
                    section.data(246).logicalSrcIdx = 245;
                    section.data(246).dtTransOffset = 425;

                    ;% rtP.SFunction9_P1_nunfwxzwxg
                    section.data(247).logicalSrcIdx = 246;
                    section.data(247).dtTransOffset = 427;

                    ;% rtP.SFunction9_P2_Size
                    section.data(248).logicalSrcIdx = 247;
                    section.data(248).dtTransOffset = 428;

                    ;% rtP.SFunction9_P2
                    section.data(249).logicalSrcIdx = 248;
                    section.data(249).dtTransOffset = 430;

                    ;% rtP.noise_Mean_m211emgdl3
                    section.data(250).logicalSrcIdx = 249;
                    section.data(250).dtTransOffset = 431;

                    ;% rtP.noise_StdDev
                    section.data(251).logicalSrcIdx = 250;
                    section.data(251).dtTransOffset = 434;

                    ;% rtP.TransferFcn_A_c34clvpx4a
                    section.data(252).logicalSrcIdx = 251;
                    section.data(252).dtTransOffset = 437;

                    ;% rtP.TransferFcn_C_ciybxys4sn
                    section.data(253).logicalSrcIdx = 252;
                    section.data(253).dtTransOffset = 438;

                    ;% rtP.TransferFcn1_A_lrz1uxhxld
                    section.data(254).logicalSrcIdx = 253;
                    section.data(254).dtTransOffset = 439;

                    ;% rtP.TransferFcn1_C_b2uz52ggce
                    section.data(255).logicalSrcIdx = 254;
                    section.data(255).dtTransOffset = 440;

                    ;% rtP.TransferFcn2_A_pnihap0iyy
                    section.data(256).logicalSrcIdx = 255;
                    section.data(256).dtTransOffset = 441;

                    ;% rtP.TransferFcn2_C_f5zsdduuzq
                    section.data(257).logicalSrcIdx = 256;
                    section.data(257).dtTransOffset = 442;

                    ;% rtP.SFunction1_P1_Size
                    section.data(258).logicalSrcIdx = 257;
                    section.data(258).dtTransOffset = 443;

                    ;% rtP.SFunction1_P1
                    section.data(259).logicalSrcIdx = 258;
                    section.data(259).dtTransOffset = 445;

                    ;% rtP.km2m_Gain_c3udq35tim
                    section.data(260).logicalSrcIdx = 259;
                    section.data(260).dtTransOffset = 446;

                    ;% rtP.RandomNumber_Mean
                    section.data(261).logicalSrcIdx = 260;
                    section.data(261).dtTransOffset = 447;

                    ;% rtP.RandomNumber_StdDev
                    section.data(262).logicalSrcIdx = 261;
                    section.data(262).dtTransOffset = 450;

                    ;% rtP.ECEFPositiontoLLA_F_h5d2qe30it
                    section.data(263).logicalSrcIdx = 262;
                    section.data(263).dtTransOffset = 453;

                    ;% rtP.ECEFPositiontoLLA_R_dv1fhj4bwm
                    section.data(264).logicalSrcIdx = 263;
                    section.data(264).dtTransOffset = 454;

                    ;% rtP.noise3_Minimum
                    section.data(265).logicalSrcIdx = 264;
                    section.data(265).dtTransOffset = 455;

                    ;% rtP.SFunction5_P1_Size
                    section.data(266).logicalSrcIdx = 265;
                    section.data(266).dtTransOffset = 456;

                    ;% rtP.SFunction5_P1
                    section.data(267).logicalSrcIdx = 266;
                    section.data(267).dtTransOffset = 458;

                    ;% rtP.rpm2rad_Gain
                    section.data(268).logicalSrcIdx = 267;
                    section.data(268).dtTransOffset = 459;

                    ;% rtP.rpm2rad1_Gain
                    section.data(269).logicalSrcIdx = 268;
                    section.data(269).dtTransOffset = 460;

                    ;% rtP.rpm2rad2_Gain
                    section.data(270).logicalSrcIdx = 269;
                    section.data(270).dtTransOffset = 461;

                    ;% rtP.rpm2rad3_Gain
                    section.data(271).logicalSrcIdx = 270;
                    section.data(271).dtTransOffset = 462;

                    ;% rtP.Gain_Gain_kyqyxgfjjc
                    section.data(272).logicalSrcIdx = 271;
                    section.data(272).dtTransOffset = 463;

                    ;% rtP.Gain1_Gain_jdzh1vayht
                    section.data(273).logicalSrcIdx = 272;
                    section.data(273).dtTransOffset = 464;

                    ;% rtP.Gain2_Gain_mjvcbm4pqd
                    section.data(274).logicalSrcIdx = 273;
                    section.data(274).dtTransOffset = 465;

                    ;% rtP.Gain_Gain_ag50armt4q
                    section.data(275).logicalSrcIdx = 274;
                    section.data(275).dtTransOffset = 466;

                    ;% rtP.Gain1_Gain_hahbyfhvn1
                    section.data(276).logicalSrcIdx = 275;
                    section.data(276).dtTransOffset = 467;

                    ;% rtP.Gain2_Gain_bob4otocpt
                    section.data(277).logicalSrcIdx = 276;
                    section.data(277).dtTransOffset = 468;

                    ;% rtP.Gain_Gain_du1axyb1td
                    section.data(278).logicalSrcIdx = 277;
                    section.data(278).dtTransOffset = 469;

                    ;% rtP.Gain1_Gain_cjxo0bvxyl
                    section.data(279).logicalSrcIdx = 278;
                    section.data(279).dtTransOffset = 470;

                    ;% rtP.Gain2_Gain_cyuruau31y
                    section.data(280).logicalSrcIdx = 279;
                    section.data(280).dtTransOffset = 471;

                    ;% rtP.IC_Value
                    section.data(281).logicalSrcIdx = 280;
                    section.data(281).dtTransOffset = 472;

                    ;% rtP.IC1_Value
                    section.data(282).logicalSrcIdx = 281;
                    section.data(282).dtTransOffset = 476;

                    ;% rtP.losstorquepropotionto_Gain
                    section.data(283).logicalSrcIdx = 282;
                    section.data(283).dtTransOffset = 479;

                    ;% rtP.losstorquepropotionto_Gain_hahtzed0yk
                    section.data(284).logicalSrcIdx = 283;
                    section.data(284).dtTransOffset = 480;

                    ;% rtP.losstorquepropotionto_Gain_ftpubwm50g
                    section.data(285).logicalSrcIdx = 284;
                    section.data(285).dtTransOffset = 481;

                    ;% rtP.losstorquepropotionto_Gain_k3z3t2gd1a
                    section.data(286).logicalSrcIdx = 285;
                    section.data(286).dtTransOffset = 482;

                    ;% rtP.reactiontorque_Gain
                    section.data(287).logicalSrcIdx = 286;
                    section.data(287).dtTransOffset = 483;

                    ;% rtP.TransferFcn_A_aashwww0mz
                    section.data(288).logicalSrcIdx = 287;
                    section.data(288).dtTransOffset = 484;

                    ;% rtP.TransferFcn_C_kwbfsnl1hg
                    section.data(289).logicalSrcIdx = 288;
                    section.data(289).dtTransOffset = 485;

                    ;% rtP.TransferFcn_A_gmkfu1bp5e
                    section.data(290).logicalSrcIdx = 289;
                    section.data(290).dtTransOffset = 486;

                    ;% rtP.TransferFcn_C_n45ccaftaw
                    section.data(291).logicalSrcIdx = 290;
                    section.data(291).dtTransOffset = 487;

                    ;% rtP.TransferFcn_A_axh3uxseti
                    section.data(292).logicalSrcIdx = 291;
                    section.data(292).dtTransOffset = 488;

                    ;% rtP.TransferFcn_C_c3yi1bxnht
                    section.data(293).logicalSrcIdx = 292;
                    section.data(293).dtTransOffset = 489;

                    ;% rtP.nT_2_T_Gain
                    section.data(294).logicalSrcIdx = 293;
                    section.data(294).dtTransOffset = 490;

                    ;% rtP.Integrator_IC_fuz2mronvk
                    section.data(295).logicalSrcIdx = 294;
                    section.data(295).dtTransOffset = 491;

                    ;% rtP.rad2deg_Gain_i0zxrskrml
                    section.data(296).logicalSrcIdx = 295;
                    section.data(296).dtTransOffset = 492;

                    ;% rtP.nvdegsec_Mean
                    section.data(297).logicalSrcIdx = 296;
                    section.data(297).dtTransOffset = 493;

                    ;% rtP.nvdegsec_StdDev
                    section.data(298).logicalSrcIdx = 297;
                    section.data(298).dtTransOffset = 496;

                    ;% rtP.nudegsec2_Mean
                    section.data(299).logicalSrcIdx = 298;
                    section.data(299).dtTransOffset = 499;

                    ;% rtP.nudegsec2_StdDev
                    section.data(300).logicalSrcIdx = 299;
                    section.data(300).dtTransOffset = 502;

                    ;% rtP.Switch_Threshold
                    section.data(301).logicalSrcIdx = 300;
                    section.data(301).dtTransOffset = 505;

                    ;% rtP.Switch_Threshold_a5rkjww04l
                    section.data(302).logicalSrcIdx = 301;
                    section.data(302).dtTransOffset = 506;

                    ;% rtP.Switch_Threshold_eczahcudx1
                    section.data(303).logicalSrcIdx = 302;
                    section.data(303).dtTransOffset = 507;

                    ;% rtP.Switch_Threshold_mxo352pg2c
                    section.data(304).logicalSrcIdx = 303;
                    section.data(304).dtTransOffset = 508;

                    ;% rtP.Constant6_Value
                    section.data(305).logicalSrcIdx = 304;
                    section.data(305).dtTransOffset = 509;

                    ;% rtP.Constant2_Value
                    section.data(306).logicalSrcIdx = 305;
                    section.data(306).dtTransOffset = 510;

                    ;% rtP.Constant12_Value
                    section.data(307).logicalSrcIdx = 306;
                    section.data(307).dtTransOffset = 511;

                    ;% rtP.Constant15_Value
                    section.data(308).logicalSrcIdx = 307;
                    section.data(308).dtTransOffset = 512;

                    ;% rtP.Constant4_Value
                    section.data(309).logicalSrcIdx = 308;
                    section.data(309).dtTransOffset = 513;

                    ;% rtP.Constant1_Value
                    section.data(310).logicalSrcIdx = 309;
                    section.data(310).dtTransOffset = 514;

                    ;% rtP.Constant3_Value
                    section.data(311).logicalSrcIdx = 310;
                    section.data(311).dtTransOffset = 515;

                    ;% rtP.Constant1_Value_iq2e102mi0
                    section.data(312).logicalSrcIdx = 311;
                    section.data(312).dtTransOffset = 516;

                    ;% rtP.Constant2_Value_fgyxvvitry
                    section.data(313).logicalSrcIdx = 312;
                    section.data(313).dtTransOffset = 517;

                    ;% rtP.Constant3_Value_mtqeqchjq3
                    section.data(314).logicalSrcIdx = 313;
                    section.data(314).dtTransOffset = 518;

                    ;% rtP.Constant6_Value_oipnu5fd53
                    section.data(315).logicalSrcIdx = 314;
                    section.data(315).dtTransOffset = 519;

                    ;% rtP.Constant_Value_ns0uhctphf
                    section.data(316).logicalSrcIdx = 315;
                    section.data(316).dtTransOffset = 520;

                    ;% rtP.Constant_Value_icfwmptllg
                    section.data(317).logicalSrcIdx = 316;
                    section.data(317).dtTransOffset = 521;

                    ;% rtP.Constant1_Value_oqvdx5zpsu
                    section.data(318).logicalSrcIdx = 317;
                    section.data(318).dtTransOffset = 522;

                    ;% rtP.Constant2_Value_e1f4g20e1v
                    section.data(319).logicalSrcIdx = 318;
                    section.data(319).dtTransOffset = 523;

                    ;% rtP.Constant_Value_amoommf0mg
                    section.data(320).logicalSrcIdx = 319;
                    section.data(320).dtTransOffset = 524;

                    ;% rtP.Constant_Value_mq4m5be1k3
                    section.data(321).logicalSrcIdx = 320;
                    section.data(321).dtTransOffset = 525;

                    ;% rtP.Constant_Value_kcvsynl3gu
                    section.data(322).logicalSrcIdx = 321;
                    section.data(322).dtTransOffset = 526;

                    ;% rtP.Constant_Value_ggebjt2fys
                    section.data(323).logicalSrcIdx = 322;
                    section.data(323).dtTransOffset = 527;

                    ;% rtP.Constant_Value_kblt0a3uql
                    section.data(324).logicalSrcIdx = 323;
                    section.data(324).dtTransOffset = 528;

                    ;% rtP.Constant_Value_hgvjimspu2
                    section.data(325).logicalSrcIdx = 324;
                    section.data(325).dtTransOffset = 529;

                    ;% rtP.Constant_Value_jyoylqpxtd
                    section.data(326).logicalSrcIdx = 325;
                    section.data(326).dtTransOffset = 530;

                    ;% rtP.Constant_Value_kxh4uvpty4
                    section.data(327).logicalSrcIdx = 326;
                    section.data(327).dtTransOffset = 531;

                    ;% rtP.Constant_Value_czynuf313b
                    section.data(328).logicalSrcIdx = 327;
                    section.data(328).dtTransOffset = 532;

                    ;% rtP.Constant_Value_h4xungkdn0
                    section.data(329).logicalSrcIdx = 328;
                    section.data(329).dtTransOffset = 533;

                    ;% rtP.Constant_Value_but5tairxf
                    section.data(330).logicalSrcIdx = 329;
                    section.data(330).dtTransOffset = 534;

                    ;% rtP.Constant_Value_kg1gkk2nel
                    section.data(331).logicalSrcIdx = 330;
                    section.data(331).dtTransOffset = 535;

                    ;% rtP.Constant_Value_ckqmocsjmk
                    section.data(332).logicalSrcIdx = 331;
                    section.data(332).dtTransOffset = 536;

                    ;% rtP.Constant_Value_jdq04jy3wj
                    section.data(333).logicalSrcIdx = 332;
                    section.data(333).dtTransOffset = 537;

                    ;% rtP.Constant_Value_mydahigf2l
                    section.data(334).logicalSrcIdx = 333;
                    section.data(334).dtTransOffset = 538;

                    ;% rtP.SFunction1_P1_Size_oju10to1ph
                    section.data(335).logicalSrcIdx = 334;
                    section.data(335).dtTransOffset = 539;

                    ;% rtP.SFunction1_P1_ku32nmmjfh
                    section.data(336).logicalSrcIdx = 335;
                    section.data(336).dtTransOffset = 541;

                    ;% rtP.SFunction3_P1_Size_esjea1ngwl
                    section.data(337).logicalSrcIdx = 336;
                    section.data(337).dtTransOffset = 542;

                    ;% rtP.SFunction3_P1_jzwtpm1uma
                    section.data(338).logicalSrcIdx = 337;
                    section.data(338).dtTransOffset = 544;

                    ;% rtP.SFunction4_P1_Size_odtljxchme
                    section.data(339).logicalSrcIdx = 338;
                    section.data(339).dtTransOffset = 545;

                    ;% rtP.SFunction4_P1_edpc41wy4o
                    section.data(340).logicalSrcIdx = 339;
                    section.data(340).dtTransOffset = 547;

                    ;% rtP.SFunction5_P1_Size_fiagzwfsx1
                    section.data(341).logicalSrcIdx = 340;
                    section.data(341).dtTransOffset = 548;

                    ;% rtP.SFunction5_P1_brpnppqifr
                    section.data(342).logicalSrcIdx = 341;
                    section.data(342).dtTransOffset = 550;

                    ;% rtP.SFunction6_P1_Size_nugnt25utq
                    section.data(343).logicalSrcIdx = 342;
                    section.data(343).dtTransOffset = 551;

                    ;% rtP.SFunction6_P1_edgmn5fq4g
                    section.data(344).logicalSrcIdx = 343;
                    section.data(344).dtTransOffset = 553;

                    ;% rtP.Constant_Value_hmchyhprrs
                    section.data(345).logicalSrcIdx = 344;
                    section.data(345).dtTransOffset = 554;

                    ;% rtP.Constant1_Value_abguselunm
                    section.data(346).logicalSrcIdx = 345;
                    section.data(346).dtTransOffset = 555;

                    ;% rtP.Constant2_Value_gegmpg2rvu
                    section.data(347).logicalSrcIdx = 346;
                    section.data(347).dtTransOffset = 558;

                    ;% rtP.Constant_Value_lxzojy1yts
                    section.data(348).logicalSrcIdx = 347;
                    section.data(348).dtTransOffset = 560;

                    ;% rtP.Constant_Value_hupkchseos
                    section.data(349).logicalSrcIdx = 348;
                    section.data(349).dtTransOffset = 561;

                    ;% rtP.Constant1_Value_ej0jppt02k
                    section.data(350).logicalSrcIdx = 349;
                    section.data(350).dtTransOffset = 562;

                    ;% rtP.Constant2_Value_cthnum5wwf
                    section.data(351).logicalSrcIdx = 350;
                    section.data(351).dtTransOffset = 565;

                    ;% rtP.Constant_Value_m2hdvkft2v
                    section.data(352).logicalSrcIdx = 351;
                    section.data(352).dtTransOffset = 567;

                    ;% rtP.Constant_Value_ndyne2tsni
                    section.data(353).logicalSrcIdx = 352;
                    section.data(353).dtTransOffset = 568;

                    ;% rtP.Constant1_Value_la1yhx1hao
                    section.data(354).logicalSrcIdx = 353;
                    section.data(354).dtTransOffset = 569;

                    ;% rtP.Constant2_Value_gn4fk3d1lp
                    section.data(355).logicalSrcIdx = 354;
                    section.data(355).dtTransOffset = 572;

                    ;% rtP.Constant_Value_iqckjhnrkz
                    section.data(356).logicalSrcIdx = 355;
                    section.data(356).dtTransOffset = 574;

                    ;% rtP.Constant_Value_ghgnj1qkgx
                    section.data(357).logicalSrcIdx = 356;
                    section.data(357).dtTransOffset = 575;

                    ;% rtP.Constant1_Value_j0a4ub2khm
                    section.data(358).logicalSrcIdx = 357;
                    section.data(358).dtTransOffset = 576;

                    ;% rtP.Constant2_Value_aeurx5t4ck
                    section.data(359).logicalSrcIdx = 358;
                    section.data(359).dtTransOffset = 579;

                    ;% rtP.Constant_Value_fvwnrwg2d1
                    section.data(360).logicalSrcIdx = 359;
                    section.data(360).dtTransOffset = 581;

                    ;% rtP.Constant_Value_ejbbt4py2k
                    section.data(361).logicalSrcIdx = 360;
                    section.data(361).dtTransOffset = 582;

                    ;% rtP.Constant1_Value_g3xactptzz
                    section.data(362).logicalSrcIdx = 361;
                    section.data(362).dtTransOffset = 583;

                    ;% rtP.Constant2_Value_kj0dkshoay
                    section.data(363).logicalSrcIdx = 362;
                    section.data(363).dtTransOffset = 586;

                    ;% rtP.Constant_Value_fnhawrwcfw
                    section.data(364).logicalSrcIdx = 363;
                    section.data(364).dtTransOffset = 588;

                    ;% rtP.Constant_Value_iba131uo1r
                    section.data(365).logicalSrcIdx = 364;
                    section.data(365).dtTransOffset = 589;

                    ;% rtP.Constant1_Value_nc5rt4jowx
                    section.data(366).logicalSrcIdx = 365;
                    section.data(366).dtTransOffset = 590;

                    ;% rtP.Constant2_Value_nqgiw5gjgz
                    section.data(367).logicalSrcIdx = 366;
                    section.data(367).dtTransOffset = 593;

                    ;% rtP.Constant_Value_k3ehwbv3db
                    section.data(368).logicalSrcIdx = 367;
                    section.data(368).dtTransOffset = 595;

                    ;% rtP.Gain_Gain_jiwysirinb
                    section.data(369).logicalSrcIdx = 368;
                    section.data(369).dtTransOffset = 596;

                    ;% rtP.Gain_Gain_gueaxs1w4d
                    section.data(370).logicalSrcIdx = 369;
                    section.data(370).dtTransOffset = 597;

                    ;% rtP.Gain_Gain_o54eldgojd
                    section.data(371).logicalSrcIdx = 370;
                    section.data(371).dtTransOffset = 598;

                    ;% rtP.Gain_Gain_gdjmrybomw
                    section.data(372).logicalSrcIdx = 371;
                    section.data(372).dtTransOffset = 599;

                    ;% rtP.Gain_Gain_jzbglr3iwn
                    section.data(373).logicalSrcIdx = 372;
                    section.data(373).dtTransOffset = 600;

                    ;% rtP.Gain_Gain_ijnc3iled3
                    section.data(374).logicalSrcIdx = 373;
                    section.data(374).dtTransOffset = 601;

                    ;% rtP.Constant2_Value_gqzethcbdt
                    section.data(375).logicalSrcIdx = 374;
                    section.data(375).dtTransOffset = 602;

                    ;% rtP.b0degsec_Value
                    section.data(376).logicalSrcIdx = 375;
                    section.data(376).dtTransOffset = 605;

                    ;% rtP.Constant_Value_g3sjkewgl1
                    section.data(377).logicalSrcIdx = 376;
                    section.data(377).dtTransOffset = 608;

                    ;% rtP.Constant1_Value_hlcqpzkeg5
                    section.data(378).logicalSrcIdx = 377;
                    section.data(378).dtTransOffset = 609;

                    ;% rtP.Constant2_Value_jyuv2gy0ao
                    section.data(379).logicalSrcIdx = 378;
                    section.data(379).dtTransOffset = 610;

                    ;% rtP.Constant3_Value_axvubao2wd
                    section.data(380).logicalSrcIdx = 379;
                    section.data(380).dtTransOffset = 611;

                    ;% rtP.Switch2_Threshold
                    section.data(381).logicalSrcIdx = 380;
                    section.data(381).dtTransOffset = 612;

                    ;% rtP.Constant_Value_ovuyhiuyim
                    section.data(382).logicalSrcIdx = 381;
                    section.data(382).dtTransOffset = 613;

                    ;% rtP.Constant1_Value_oxbz4wjuse
                    section.data(383).logicalSrcIdx = 382;
                    section.data(383).dtTransOffset = 614;

                    ;% rtP.Constant2_Value_pdtexc4kgl
                    section.data(384).logicalSrcIdx = 383;
                    section.data(384).dtTransOffset = 615;

                    ;% rtP.Constant3_Value_ds1jzpwkjt
                    section.data(385).logicalSrcIdx = 384;
                    section.data(385).dtTransOffset = 616;

                    ;% rtP.Switch2_Threshold_hj15nt1i3x
                    section.data(386).logicalSrcIdx = 385;
                    section.data(386).dtTransOffset = 617;

                    ;% rtP.Constant_Value_br1klnkrdq
                    section.data(387).logicalSrcIdx = 386;
                    section.data(387).dtTransOffset = 618;

                    ;% rtP.Constant1_Value_jbsud0br1l
                    section.data(388).logicalSrcIdx = 387;
                    section.data(388).dtTransOffset = 619;

                    ;% rtP.Constant2_Value_lepgnru1ev
                    section.data(389).logicalSrcIdx = 388;
                    section.data(389).dtTransOffset = 620;

                    ;% rtP.Constant3_Value_pq0io1rx2d
                    section.data(390).logicalSrcIdx = 389;
                    section.data(390).dtTransOffset = 621;

                    ;% rtP.Switch2_Threshold_f3oy1s34eo
                    section.data(391).logicalSrcIdx = 390;
                    section.data(391).dtTransOffset = 622;

                    ;% rtP.Constant_Value_kibc2xmwm0
                    section.data(392).logicalSrcIdx = 391;
                    section.data(392).dtTransOffset = 623;

                    ;% rtP.Constant1_Value_bvl32d0cmp
                    section.data(393).logicalSrcIdx = 392;
                    section.data(393).dtTransOffset = 624;

                    ;% rtP.Constant2_Value_oaj3bo5322
                    section.data(394).logicalSrcIdx = 393;
                    section.data(394).dtTransOffset = 625;

                    ;% rtP.Constant3_Value_ihqrcdemxt
                    section.data(395).logicalSrcIdx = 394;
                    section.data(395).dtTransOffset = 626;

                    ;% rtP.Switch2_Threshold_fnlhdgazir
                    section.data(396).logicalSrcIdx = 395;
                    section.data(396).dtTransOffset = 627;

            nTotData = nTotData + section.nData;
            paramMap.sections(1) = section;
            clear section


            ;%
            ;% Non-auto Data (parameter)
            ;%


        ;%
        ;% Add final counts to struct.
        ;%
        paramMap.nTotData = nTotData;



    ;%**************************
    ;% Create Block Output Map *
    ;%**************************
    
        nTotData      = 0; %add to this count as we go
        nTotSects     = 50;
        sectIdxOffset = 0;

        ;%
        ;% Define dummy sections & preallocate arrays
        ;%
        dumSection.nData = -1;
        dumSection.data  = [];

        dumData.logicalSrcIdx = -1;
        dumData.dtTransOffset = -1;

        ;%
        ;% Init/prealloc sigMap
        ;%
        sigMap.nSections           = nTotSects;
        sigMap.sectIdxOffset       = sectIdxOffset;
            sigMap.sections(nTotSects) = dumSection; %prealloc
        sigMap.nTotData            = -1;

        ;%
        ;% Auto data (rtB)
        ;%
            section.nData     = 90;
            section.data(90)  = dumData; %prealloc

                    ;% rtB.gv3z4rzpl5
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

                    ;% rtB.pmkqoqavmi
                    section.data(2).logicalSrcIdx = 1;
                    section.data(2).dtTransOffset = 3;

                    ;% rtB.fdbl5l21n4
                    section.data(3).logicalSrcIdx = 2;
                    section.data(3).dtTransOffset = 4;

                    ;% rtB.chofn13vqp
                    section.data(4).logicalSrcIdx = 3;
                    section.data(4).dtTransOffset = 12;

                    ;% rtB.oucj4k4y2q
                    section.data(5).logicalSrcIdx = 4;
                    section.data(5).dtTransOffset = 13;

                    ;% rtB.c5lfdegv0p
                    section.data(6).logicalSrcIdx = 5;
                    section.data(6).dtTransOffset = 21;

                    ;% rtB.ktlu1ekw1m
                    section.data(7).logicalSrcIdx = 6;
                    section.data(7).dtTransOffset = 22;

                    ;% rtB.ju0zmrtbs0
                    section.data(8).logicalSrcIdx = 7;
                    section.data(8).dtTransOffset = 30;

                    ;% rtB.innw5sywzg
                    section.data(9).logicalSrcIdx = 8;
                    section.data(9).dtTransOffset = 31;

                    ;% rtB.a5ald3g22i
                    section.data(10).logicalSrcIdx = 9;
                    section.data(10).dtTransOffset = 39;

                    ;% rtB.mpca01r2m2
                    section.data(11).logicalSrcIdx = 10;
                    section.data(11).dtTransOffset = 41;

                    ;% rtB.asykhtld2n
                    section.data(12).logicalSrcIdx = 11;
                    section.data(12).dtTransOffset = 42;

                    ;% rtB.ilq2khdcgh
                    section.data(13).logicalSrcIdx = 12;
                    section.data(13).dtTransOffset = 54;

                    ;% rtB.lizdm2xqna
                    section.data(14).logicalSrcIdx = 13;
                    section.data(14).dtTransOffset = 58;

                    ;% rtB.laz0gn3eus
                    section.data(15).logicalSrcIdx = 14;
                    section.data(15).dtTransOffset = 59;

                    ;% rtB.fdbl5l21n42
                    section.data(16).logicalSrcIdx = 15;
                    section.data(16).dtTransOffset = 60;

                    ;% rtB.ggo5omtwrw
                    section.data(17).logicalSrcIdx = 16;
                    section.data(17).dtTransOffset = 64;

                    ;% rtB.gu0xyts5qt
                    section.data(18).logicalSrcIdx = 17;
                    section.data(18).dtTransOffset = 65;

                    ;% rtB.pktfet50kq
                    section.data(19).logicalSrcIdx = 18;
                    section.data(19).dtTransOffset = 66;

                    ;% rtB.cpp1cmyksa
                    section.data(20).logicalSrcIdx = 19;
                    section.data(20).dtTransOffset = 70;

                    ;% rtB.necosqfbva
                    section.data(21).logicalSrcIdx = 20;
                    section.data(21).dtTransOffset = 71;

                    ;% rtB.cyayszgojz
                    section.data(22).logicalSrcIdx = 21;
                    section.data(22).dtTransOffset = 72;

                    ;% rtB.mo4pqo22zy
                    section.data(23).logicalSrcIdx = 22;
                    section.data(23).dtTransOffset = 76;

                    ;% rtB.ooktctrg5d
                    section.data(24).logicalSrcIdx = 23;
                    section.data(24).dtTransOffset = 77;

                    ;% rtB.oucj4k4y2qy
                    section.data(25).logicalSrcIdx = 24;
                    section.data(25).dtTransOffset = 78;

                    ;% rtB.onbsvxszlu
                    section.data(26).logicalSrcIdx = 25;
                    section.data(26).dtTransOffset = 82;

                    ;% rtB.ljv1mgpbcd
                    section.data(27).logicalSrcIdx = 26;
                    section.data(27).dtTransOffset = 83;

                    ;% rtB.ktlu1ekw1mg
                    section.data(28).logicalSrcIdx = 27;
                    section.data(28).dtTransOffset = 84;

                    ;% rtB.lfncg5pvng
                    section.data(29).logicalSrcIdx = 28;
                    section.data(29).dtTransOffset = 88;

                    ;% rtB.kfpd0jse5u
                    section.data(30).logicalSrcIdx = 29;
                    section.data(30).dtTransOffset = 89;

                    ;% rtB.innw5sywzgy
                    section.data(31).logicalSrcIdx = 30;
                    section.data(31).dtTransOffset = 90;

                    ;% rtB.hcpvpoawqx
                    section.data(32).logicalSrcIdx = 31;
                    section.data(32).dtTransOffset = 94;

                    ;% rtB.jihpm3q5gs
                    section.data(33).logicalSrcIdx = 32;
                    section.data(33).dtTransOffset = 97;

                    ;% rtB.gs0kzoznkl
                    section.data(34).logicalSrcIdx = 33;
                    section.data(34).dtTransOffset = 101;

                    ;% rtB.jkg4capamp
                    section.data(35).logicalSrcIdx = 34;
                    section.data(35).dtTransOffset = 104;

                    ;% rtB.cbjdhhra0o
                    section.data(36).logicalSrcIdx = 35;
                    section.data(36).dtTransOffset = 105;

                    ;% rtB.mmxfckfrxp
                    section.data(37).logicalSrcIdx = 36;
                    section.data(37).dtTransOffset = 117;

                    ;% rtB.ovvyrfj4qq
                    section.data(38).logicalSrcIdx = 37;
                    section.data(38).dtTransOffset = 118;

                    ;% rtB.jr21nlhhbn
                    section.data(39).logicalSrcIdx = 38;
                    section.data(39).dtTransOffset = 119;

                    ;% rtB.gyoxzzwqiz
                    section.data(40).logicalSrcIdx = 39;
                    section.data(40).dtTransOffset = 123;

                    ;% rtB.nljkudwtrt
                    section.data(41).logicalSrcIdx = 40;
                    section.data(41).dtTransOffset = 126;

                    ;% rtB.ht411kslhv
                    section.data(42).logicalSrcIdx = 41;
                    section.data(42).dtTransOffset = 129;

                    ;% rtB.ikgewnxpow
                    section.data(43).logicalSrcIdx = 42;
                    section.data(43).dtTransOffset = 132;

                    ;% rtB.geuyf21jdw
                    section.data(44).logicalSrcIdx = 43;
                    section.data(44).dtTransOffset = 135;

                    ;% rtB.hfnierhiih
                    section.data(45).logicalSrcIdx = 44;
                    section.data(45).dtTransOffset = 136;

                    ;% rtB.ahgjrqaame
                    section.data(46).logicalSrcIdx = 45;
                    section.data(46).dtTransOffset = 137;

                    ;% rtB.e3dq3kgfi1
                    section.data(47).logicalSrcIdx = 46;
                    section.data(47).dtTransOffset = 138;

                    ;% rtB.lyqxqxi2xc
                    section.data(48).logicalSrcIdx = 47;
                    section.data(48).dtTransOffset = 139;

                    ;% rtB.jbyqlkik0e
                    section.data(49).logicalSrcIdx = 48;
                    section.data(49).dtTransOffset = 140;

                    ;% rtB.owuvzpfz25
                    section.data(50).logicalSrcIdx = 49;
                    section.data(50).dtTransOffset = 141;

                    ;% rtB.ddje2kvmhp
                    section.data(51).logicalSrcIdx = 50;
                    section.data(51).dtTransOffset = 142;

                    ;% rtB.gsio300bjg
                    section.data(52).logicalSrcIdx = 51;
                    section.data(52).dtTransOffset = 143;

                    ;% rtB.i34t1ktiub
                    section.data(53).logicalSrcIdx = 52;
                    section.data(53).dtTransOffset = 144;

                    ;% rtB.ozbqnpwmeu
                    section.data(54).logicalSrcIdx = 53;
                    section.data(54).dtTransOffset = 145;

                    ;% rtB.gbjcwtpbjf
                    section.data(55).logicalSrcIdx = 54;
                    section.data(55).dtTransOffset = 146;

                    ;% rtB.ogbf133q1z
                    section.data(56).logicalSrcIdx = 55;
                    section.data(56).dtTransOffset = 147;

                    ;% rtB.ocfpzffbzh
                    section.data(57).logicalSrcIdx = 56;
                    section.data(57).dtTransOffset = 148;

                    ;% rtB.pzuqvdky0w
                    section.data(58).logicalSrcIdx = 57;
                    section.data(58).dtTransOffset = 149;

                    ;% rtB.lzmaq0diab
                    section.data(59).logicalSrcIdx = 58;
                    section.data(59).dtTransOffset = 150;

                    ;% rtB.j3kezx3yvk
                    section.data(60).logicalSrcIdx = 59;
                    section.data(60).dtTransOffset = 156;

                    ;% rtB.jg4a0jn2o1
                    section.data(61).logicalSrcIdx = 60;
                    section.data(61).dtTransOffset = 159;

                    ;% rtB.lrdfz5anhg
                    section.data(62).logicalSrcIdx = 61;
                    section.data(62).dtTransOffset = 162;

                    ;% rtB.d2nlp5u0iz
                    section.data(63).logicalSrcIdx = 62;
                    section.data(63).dtTransOffset = 166;

                    ;% rtB.cvndu2lgp0
                    section.data(64).logicalSrcIdx = 63;
                    section.data(64).dtTransOffset = 170;

                    ;% rtB.mslzotztaf
                    section.data(65).logicalSrcIdx = 64;
                    section.data(65).dtTransOffset = 174;

                    ;% rtB.ghrb02xtti
                    section.data(66).logicalSrcIdx = 65;
                    section.data(66).dtTransOffset = 178;

                    ;% rtB.llfqz3cih1
                    section.data(67).logicalSrcIdx = 66;
                    section.data(67).dtTransOffset = 187;

                    ;% rtB.euwsxn4aph
                    section.data(68).logicalSrcIdx = 67;
                    section.data(68).dtTransOffset = 188;

                    ;% rtB.kiyg1swe1h
                    section.data(69).logicalSrcIdx = 68;
                    section.data(69).dtTransOffset = 189;

                    ;% rtB.el4rhtecud
                    section.data(70).logicalSrcIdx = 69;
                    section.data(70).dtTransOffset = 190;

                    ;% rtB.oqvw4bmbeg
                    section.data(71).logicalSrcIdx = 70;
                    section.data(71).dtTransOffset = 191;

                    ;% rtB.ndtffugziw
                    section.data(72).logicalSrcIdx = 71;
                    section.data(72).dtTransOffset = 194;

                    ;% rtB.bqbim0ae4p
                    section.data(73).logicalSrcIdx = 72;
                    section.data(73).dtTransOffset = 206;

                    ;% rtB.edgmu1taic
                    section.data(74).logicalSrcIdx = 73;
                    section.data(74).dtTransOffset = 212;

                    ;% rtB.a3fezsr2vw
                    section.data(75).logicalSrcIdx = 74;
                    section.data(75).dtTransOffset = 216;

                    ;% rtB.kimclls5ui
                    section.data(76).logicalSrcIdx = 75;
                    section.data(76).dtTransOffset = 217;

                    ;% rtB.eij4bqg1qu
                    section.data(77).logicalSrcIdx = 76;
                    section.data(77).dtTransOffset = 218;

                    ;% rtB.a5ybxummfl
                    section.data(78).logicalSrcIdx = 77;
                    section.data(78).dtTransOffset = 222;

                    ;% rtB.gs20g4hobc
                    section.data(79).logicalSrcIdx = 78;
                    section.data(79).dtTransOffset = 225;

                    ;% rtB.b5ehs0zt32
                    section.data(80).logicalSrcIdx = 79;
                    section.data(80).dtTransOffset = 231;

                    ;% rtB.hm15o25lmb
                    section.data(81).logicalSrcIdx = 80;
                    section.data(81).dtTransOffset = 234;

                    ;% rtB.chrkykmk4n
                    section.data(82).logicalSrcIdx = 81;
                    section.data(82).dtTransOffset = 237;

                    ;% rtB.nevppfxrse
                    section.data(83).logicalSrcIdx = 82;
                    section.data(83).dtTransOffset = 238;

                    ;% rtB.bfrpnyoemv
                    section.data(84).logicalSrcIdx = 83;
                    section.data(84).dtTransOffset = 239;

                    ;% rtB.p4vsv1mu0t
                    section.data(85).logicalSrcIdx = 84;
                    section.data(85).dtTransOffset = 240;

                    ;% rtB.blzsybl1pb
                    section.data(86).logicalSrcIdx = 85;
                    section.data(86).dtTransOffset = 241;

                    ;% rtB.nspxciplv0
                    section.data(87).logicalSrcIdx = 86;
                    section.data(87).dtTransOffset = 248;

                    ;% rtB.i2mlgup0vd
                    section.data(88).logicalSrcIdx = 87;
                    section.data(88).dtTransOffset = 271;

                    ;% rtB.jn52bjhkjf
                    section.data(89).logicalSrcIdx = 88;
                    section.data(89).dtTransOffset = 272;

                    ;% rtB.jhikopnu5c
                    section.data(90).logicalSrcIdx = 89;
                    section.data(90).dtTransOffset = 273;

            nTotData = nTotData + section.nData;
            sigMap.sections(1) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.ff5nefkxhm
                    section.data(1).logicalSrcIdx = 90;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(2) = section;
            clear section

            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% rtB.iroofsivyk.jeak4pqr3j
                    section.data(1).logicalSrcIdx = 91;
                    section.data(1).dtTransOffset = 0;

                    ;% rtB.iroofsivyk.h0dxk1yimp
                    section.data(2).logicalSrcIdx = 92;
                    section.data(2).dtTransOffset = 1;

            nTotData = nTotData + section.nData;
            sigMap.sections(3) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.aomn2ihkzv.nd52bn25fb
                    section.data(1).logicalSrcIdx = 93;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(4) = section;
            clear section

            section.nData     = 3;
            section.data(3)  = dumData; %prealloc

                    ;% rtB.jjm2phe1us.ozezoxky3t
                    section.data(1).logicalSrcIdx = 94;
                    section.data(1).dtTransOffset = 0;

                    ;% rtB.jjm2phe1us.g5m2irbsxw
                    section.data(2).logicalSrcIdx = 95;
                    section.data(2).dtTransOffset = 1;

                    ;% rtB.jjm2phe1us.h5cyove4ef
                    section.data(3).logicalSrcIdx = 96;
                    section.data(3).dtTransOffset = 2;

            nTotData = nTotData + section.nData;
            sigMap.sections(5) = section;
            clear section

            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% rtB.df0oudwkj0.jeak4pqr3j
                    section.data(1).logicalSrcIdx = 97;
                    section.data(1).dtTransOffset = 0;

                    ;% rtB.df0oudwkj0.h0dxk1yimp
                    section.data(2).logicalSrcIdx = 98;
                    section.data(2).dtTransOffset = 1;

            nTotData = nTotData + section.nData;
            sigMap.sections(6) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.fovau4dl3r.nd52bn25fb
                    section.data(1).logicalSrcIdx = 99;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(7) = section;
            clear section

            section.nData     = 3;
            section.data(3)  = dumData; %prealloc

                    ;% rtB.a4nohvrqys.ozezoxky3t
                    section.data(1).logicalSrcIdx = 100;
                    section.data(1).dtTransOffset = 0;

                    ;% rtB.a4nohvrqys.g5m2irbsxw
                    section.data(2).logicalSrcIdx = 101;
                    section.data(2).dtTransOffset = 1;

                    ;% rtB.a4nohvrqys.h5cyove4ef
                    section.data(3).logicalSrcIdx = 102;
                    section.data(3).dtTransOffset = 2;

            nTotData = nTotData + section.nData;
            sigMap.sections(8) = section;
            clear section

            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% rtB.gszk3bc3vp.jeak4pqr3j
                    section.data(1).logicalSrcIdx = 103;
                    section.data(1).dtTransOffset = 0;

                    ;% rtB.gszk3bc3vp.h0dxk1yimp
                    section.data(2).logicalSrcIdx = 104;
                    section.data(2).dtTransOffset = 1;

            nTotData = nTotData + section.nData;
            sigMap.sections(9) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.k4gpt5xlei.nd52bn25fb
                    section.data(1).logicalSrcIdx = 105;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(10) = section;
            clear section

            section.nData     = 3;
            section.data(3)  = dumData; %prealloc

                    ;% rtB.mzrdmi3ngp.ozezoxky3t
                    section.data(1).logicalSrcIdx = 106;
                    section.data(1).dtTransOffset = 0;

                    ;% rtB.mzrdmi3ngp.g5m2irbsxw
                    section.data(2).logicalSrcIdx = 107;
                    section.data(2).dtTransOffset = 1;

                    ;% rtB.mzrdmi3ngp.h5cyove4ef
                    section.data(3).logicalSrcIdx = 108;
                    section.data(3).dtTransOffset = 2;

            nTotData = nTotData + section.nData;
            sigMap.sections(11) = section;
            clear section

            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% rtB.mx32imycyi.jeak4pqr3j
                    section.data(1).logicalSrcIdx = 109;
                    section.data(1).dtTransOffset = 0;

                    ;% rtB.mx32imycyi.h0dxk1yimp
                    section.data(2).logicalSrcIdx = 110;
                    section.data(2).dtTransOffset = 1;

            nTotData = nTotData + section.nData;
            sigMap.sections(12) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.nbdejsvdft.nd52bn25fb
                    section.data(1).logicalSrcIdx = 111;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(13) = section;
            clear section

            section.nData     = 3;
            section.data(3)  = dumData; %prealloc

                    ;% rtB.dbik3caean.ozezoxky3t
                    section.data(1).logicalSrcIdx = 112;
                    section.data(1).dtTransOffset = 0;

                    ;% rtB.dbik3caean.g5m2irbsxw
                    section.data(2).logicalSrcIdx = 113;
                    section.data(2).dtTransOffset = 1;

                    ;% rtB.dbik3caean.h5cyove4ef
                    section.data(3).logicalSrcIdx = 114;
                    section.data(3).dtTransOffset = 2;

            nTotData = nTotData + section.nData;
            sigMap.sections(14) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.ejln4gh0kq.fkae5wqtcb
                    section.data(1).logicalSrcIdx = 115;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(15) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.gz3hxniyg2.fkae5wqtcb
                    section.data(1).logicalSrcIdx = 116;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(16) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.ka15ybowc1.fkae5wqtcb
                    section.data(1).logicalSrcIdx = 117;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(17) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.d3cawecdgq.fkae5wqtcb
                    section.data(1).logicalSrcIdx = 118;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(18) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.fe4ousljhv.osxy5zocx5
                    section.data(1).logicalSrcIdx = 119;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(19) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.hiok3cyxgg.osxy5zocx5
                    section.data(1).logicalSrcIdx = 120;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(20) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.py0l0jdlqp.owg3qz0vb0
                    section.data(1).logicalSrcIdx = 121;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(21) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.ddwcgokc4u.owg3qz0vb0
                    section.data(1).logicalSrcIdx = 122;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(22) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.gzwxmb2zl2.owg3qz0vb0
                    section.data(1).logicalSrcIdx = 123;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(23) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.n3omup2lzv.owg3qz0vb0
                    section.data(1).logicalSrcIdx = 124;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(24) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.awovp5grnq.owg3qz0vb0
                    section.data(1).logicalSrcIdx = 125;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(25) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.eosebepeyc.owg3qz0vb0
                    section.data(1).logicalSrcIdx = 126;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(26) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.ajpyzlqqkx.owg3qz0vb0
                    section.data(1).logicalSrcIdx = 127;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(27) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.jw1hn4rp4t.owg3qz0vb0
                    section.data(1).logicalSrcIdx = 128;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(28) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.jacwaaufsl.owg3qz0vb0
                    section.data(1).logicalSrcIdx = 129;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(29) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.o05svadaty.owg3qz0vb0
                    section.data(1).logicalSrcIdx = 130;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(30) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.fovozsjxj1.owg3qz0vb0
                    section.data(1).logicalSrcIdx = 131;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(31) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.axrlvoalzz.osxy5zocx5
                    section.data(1).logicalSrcIdx = 132;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(32) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.gwin1pepam.owg3qz0vb0
                    section.data(1).logicalSrcIdx = 133;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(33) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.ab0dpslgku.owg3qz0vb0
                    section.data(1).logicalSrcIdx = 134;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(34) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.dd2g34vqpy.a4ujzgnsun
                    section.data(1).logicalSrcIdx = 135;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(35) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.odjpekassu.a4ujzgnsun
                    section.data(1).logicalSrcIdx = 136;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(36) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.puqqfcdyyx.a4ujzgnsun
                    section.data(1).logicalSrcIdx = 137;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(37) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.fxdnyd3caz.a4ujzgnsun
                    section.data(1).logicalSrcIdx = 138;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(38) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.d3edomwivh.a4ujzgnsun
                    section.data(1).logicalSrcIdx = 139;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(39) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.jrtx1iz4hz.a4ujzgnsun
                    section.data(1).logicalSrcIdx = 140;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(40) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.jhrf4npwtn.a4ujzgnsun
                    section.data(1).logicalSrcIdx = 141;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(41) = section;
            clear section

            section.nData     = 6;
            section.data(6)  = dumData; %prealloc

                    ;% rtB.g5opol5dur.crs3vbajbr
                    section.data(1).logicalSrcIdx = 142;
                    section.data(1).dtTransOffset = 0;

                    ;% rtB.g5opol5dur.pyqwe5rsse
                    section.data(2).logicalSrcIdx = 143;
                    section.data(2).dtTransOffset = 1;

                    ;% rtB.g5opol5dur.agveekqpqv
                    section.data(3).logicalSrcIdx = 144;
                    section.data(3).dtTransOffset = 2;

                    ;% rtB.g5opol5dur.le233aiaq5
                    section.data(4).logicalSrcIdx = 145;
                    section.data(4).dtTransOffset = 3;

                    ;% rtB.g5opol5dur.b2jeeweznc
                    section.data(5).logicalSrcIdx = 146;
                    section.data(5).dtTransOffset = 4;

                    ;% rtB.g5opol5dur.cnte5pmho4
                    section.data(6).logicalSrcIdx = 147;
                    section.data(6).dtTransOffset = 5;

            nTotData = nTotData + section.nData;
            sigMap.sections(42) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.ca53m05hej.poahfmj3s1
                    section.data(1).logicalSrcIdx = 148;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(43) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.hdgmktoixc.poahfmj3s1
                    section.data(1).logicalSrcIdx = 149;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(44) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.ls5qu2j3gs.poahfmj3s1
                    section.data(1).logicalSrcIdx = 150;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(45) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.c5rolz011g.c1nd5nsrgs
                    section.data(1).logicalSrcIdx = 151;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(46) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.jclektca5o.aupbtlrqjk
                    section.data(1).logicalSrcIdx = 152;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(47) = section;
            clear section

            section.nData     = 6;
            section.data(6)  = dumData; %prealloc

                    ;% rtB.e1zykr3jbv.crs3vbajbr
                    section.data(1).logicalSrcIdx = 153;
                    section.data(1).dtTransOffset = 0;

                    ;% rtB.e1zykr3jbv.pyqwe5rsse
                    section.data(2).logicalSrcIdx = 154;
                    section.data(2).dtTransOffset = 1;

                    ;% rtB.e1zykr3jbv.agveekqpqv
                    section.data(3).logicalSrcIdx = 155;
                    section.data(3).dtTransOffset = 2;

                    ;% rtB.e1zykr3jbv.le233aiaq5
                    section.data(4).logicalSrcIdx = 156;
                    section.data(4).dtTransOffset = 3;

                    ;% rtB.e1zykr3jbv.b2jeeweznc
                    section.data(5).logicalSrcIdx = 157;
                    section.data(5).dtTransOffset = 4;

                    ;% rtB.e1zykr3jbv.cnte5pmho4
                    section.data(6).logicalSrcIdx = 158;
                    section.data(6).dtTransOffset = 5;

            nTotData = nTotData + section.nData;
            sigMap.sections(48) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.l15tbbx15x.c1nd5nsrgs
                    section.data(1).logicalSrcIdx = 159;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(49) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.aav5pusdkp.aupbtlrqjk
                    section.data(1).logicalSrcIdx = 160;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(50) = section;
            clear section


            ;%
            ;% Non-auto Data (signal)
            ;%


        ;%
        ;% Add final counts to struct.
        ;%
        sigMap.nTotData = nTotData;



    ;%*******************
    ;% Create DWork Map *
    ;%*******************
    
        nTotData      = 0; %add to this count as we go
        nTotSects     = 6;
        sectIdxOffset = 50;

        ;%
        ;% Define dummy sections & preallocate arrays
        ;%
        dumSection.nData = -1;
        dumSection.data  = [];

        dumData.logicalSrcIdx = -1;
        dumData.dtTransOffset = -1;

        ;%
        ;% Init/prealloc dworkMap
        ;%
        dworkMap.nSections           = nTotSects;
        dworkMap.sectIdxOffset       = sectIdxOffset;
            dworkMap.sections(nTotSects) = dumSection; %prealloc
        dworkMap.nTotData            = -1;

        ;%
        ;% Auto data (rtDW)
        ;%
            section.nData     = 23;
            section.data(23)  = dumData; %prealloc

                    ;% rtDW.hrquh23lee
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

                    ;% rtDW.bya5fxrz4g
                    section.data(2).logicalSrcIdx = 1;
                    section.data(2).dtTransOffset = 3;

                    ;% rtDW.ldpiguzau3
                    section.data(3).logicalSrcIdx = 2;
                    section.data(3).dtTransOffset = 4;

                    ;% rtDW.jx2njiskco
                    section.data(4).logicalSrcIdx = 3;
                    section.data(4).dtTransOffset = 5;

                    ;% rtDW.fg3gr5w1yf
                    section.data(5).logicalSrcIdx = 4;
                    section.data(5).dtTransOffset = 6;

                    ;% rtDW.l0mqdwlhk0
                    section.data(6).logicalSrcIdx = 5;
                    section.data(6).dtTransOffset = 7;

                    ;% rtDW.b5i1u5nxk5
                    section.data(7).logicalSrcIdx = 6;
                    section.data(7).dtTransOffset = 8;

                    ;% rtDW.ik23rulsvu
                    section.data(8).logicalSrcIdx = 7;
                    section.data(8).dtTransOffset = 9;

                    ;% rtDW.ia3ohifukf
                    section.data(9).logicalSrcIdx = 8;
                    section.data(9).dtTransOffset = 10;

                    ;% rtDW.ewzxpp1cyz
                    section.data(10).logicalSrcIdx = 9;
                    section.data(10).dtTransOffset = 11;

                    ;% rtDW.hdjjo4r4gm
                    section.data(11).logicalSrcIdx = 10;
                    section.data(11).dtTransOffset = 12;

                    ;% rtDW.coji3apumi
                    section.data(12).logicalSrcIdx = 11;
                    section.data(12).dtTransOffset = 13;

                    ;% rtDW.m2ylj5cu2h
                    section.data(13).logicalSrcIdx = 12;
                    section.data(13).dtTransOffset = 14;

                    ;% rtDW.dbnkttelok
                    section.data(14).logicalSrcIdx = 13;
                    section.data(14).dtTransOffset = 15;

                    ;% rtDW.fzlqp4iexm
                    section.data(15).logicalSrcIdx = 14;
                    section.data(15).dtTransOffset = 16;

                    ;% rtDW.hsxmncoiha
                    section.data(16).logicalSrcIdx = 15;
                    section.data(16).dtTransOffset = 19;

                    ;% rtDW.bpg2iofpcz
                    section.data(17).logicalSrcIdx = 16;
                    section.data(17).dtTransOffset = 22;

                    ;% rtDW.gvdcwkyokb
                    section.data(18).logicalSrcIdx = 17;
                    section.data(18).dtTransOffset = 23;

                    ;% rtDW.ip0upbstfm
                    section.data(19).logicalSrcIdx = 18;
                    section.data(19).dtTransOffset = 32;

                    ;% rtDW.mmkouxeune
                    section.data(20).logicalSrcIdx = 19;
                    section.data(20).dtTransOffset = 41;

                    ;% rtDW.jeeaiz3533
                    section.data(21).logicalSrcIdx = 20;
                    section.data(21).dtTransOffset = 42;

                    ;% rtDW.i3rfdszits
                    section.data(22).logicalSrcIdx = 21;
                    section.data(22).dtTransOffset = 43;

                    ;% rtDW.achzjspzj0
                    section.data(23).logicalSrcIdx = 22;
                    section.data(23).dtTransOffset = 46;

            nTotData = nTotData + section.nData;
            dworkMap.sections(1) = section;
            clear section

            section.nData     = 9;
            section.data(9)  = dumData; %prealloc

                    ;% rtDW.fkrgzvbnng.LoggedData
                    section.data(1).logicalSrcIdx = 23;
                    section.data(1).dtTransOffset = 0;

                    ;% rtDW.lqwrbhd21x.AQHandles
                    section.data(2).logicalSrcIdx = 24;
                    section.data(2).dtTransOffset = 2;

                    ;% rtDW.ko5el0avio.AQHandles
                    section.data(3).logicalSrcIdx = 25;
                    section.data(3).dtTransOffset = 3;

                    ;% rtDW.d11ycakunl.AQHandles
                    section.data(4).logicalSrcIdx = 26;
                    section.data(4).dtTransOffset = 4;

                    ;% rtDW.gfupvo0drt.LoggedData
                    section.data(5).logicalSrcIdx = 27;
                    section.data(5).dtTransOffset = 5;

                    ;% rtDW.dygea0idgb.LoggedData
                    section.data(6).logicalSrcIdx = 28;
                    section.data(6).dtTransOffset = 7;

                    ;% rtDW.hflxu4olzs.LoggedData
                    section.data(7).logicalSrcIdx = 29;
                    section.data(7).dtTransOffset = 9;

                    ;% rtDW.o3ta01udts.LoggedData
                    section.data(8).logicalSrcIdx = 30;
                    section.data(8).dtTransOffset = 13;

                    ;% rtDW.kelxgbj5f2.LoggedData
                    section.data(9).logicalSrcIdx = 31;
                    section.data(9).dtTransOffset = 14;

            nTotData = nTotData + section.nData;
            dworkMap.sections(2) = section;
            clear section

            section.nData     = 19;
            section.data(19)  = dumData; %prealloc

                    ;% rtDW.kjzrcidvjf
                    section.data(1).logicalSrcIdx = 32;
                    section.data(1).dtTransOffset = 0;

                    ;% rtDW.mc4jx3i45v
                    section.data(2).logicalSrcIdx = 33;
                    section.data(2).dtTransOffset = 3;

                    ;% rtDW.eqyhiq4b21
                    section.data(3).logicalSrcIdx = 34;
                    section.data(3).dtTransOffset = 4;

                    ;% rtDW.pvrk0p3rm1
                    section.data(4).logicalSrcIdx = 35;
                    section.data(4).dtTransOffset = 5;

                    ;% rtDW.jlc5fbv0er
                    section.data(5).logicalSrcIdx = 36;
                    section.data(5).dtTransOffset = 6;

                    ;% rtDW.mcbywo0nsz
                    section.data(6).logicalSrcIdx = 37;
                    section.data(6).dtTransOffset = 7;

                    ;% rtDW.izuwdoquaq
                    section.data(7).logicalSrcIdx = 38;
                    section.data(7).dtTransOffset = 8;

                    ;% rtDW.iy3vcqbba5
                    section.data(8).logicalSrcIdx = 39;
                    section.data(8).dtTransOffset = 9;

                    ;% rtDW.inevc2d42p
                    section.data(9).logicalSrcIdx = 40;
                    section.data(9).dtTransOffset = 10;

                    ;% rtDW.omztnckksa
                    section.data(10).logicalSrcIdx = 41;
                    section.data(10).dtTransOffset = 11;

                    ;% rtDW.peboqqfifh
                    section.data(11).logicalSrcIdx = 42;
                    section.data(11).dtTransOffset = 12;

                    ;% rtDW.hjlfer4jb5
                    section.data(12).logicalSrcIdx = 43;
                    section.data(12).dtTransOffset = 13;

                    ;% rtDW.bhy4lqzamt
                    section.data(13).logicalSrcIdx = 44;
                    section.data(13).dtTransOffset = 14;

                    ;% rtDW.l3fdu4jify
                    section.data(14).logicalSrcIdx = 45;
                    section.data(14).dtTransOffset = 15;

                    ;% rtDW.dplhf1lj21
                    section.data(15).logicalSrcIdx = 46;
                    section.data(15).dtTransOffset = 16;

                    ;% rtDW.kjjgprkxtu
                    section.data(16).logicalSrcIdx = 47;
                    section.data(16).dtTransOffset = 19;

                    ;% rtDW.eh3i2huuk3
                    section.data(17).logicalSrcIdx = 48;
                    section.data(17).dtTransOffset = 22;

                    ;% rtDW.dslhvlg4ym
                    section.data(18).logicalSrcIdx = 49;
                    section.data(18).dtTransOffset = 23;

                    ;% rtDW.czp4qnh0py
                    section.data(19).logicalSrcIdx = 50;
                    section.data(19).dtTransOffset = 26;

            nTotData = nTotData + section.nData;
            dworkMap.sections(3) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtDW.cu35sqihey
                    section.data(1).logicalSrcIdx = 51;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            dworkMap.sections(4) = section;
            clear section

            section.nData     = 5;
            section.data(5)  = dumData; %prealloc

                    ;% rtDW.azyx1ts0yu
                    section.data(1).logicalSrcIdx = 52;
                    section.data(1).dtTransOffset = 0;

                    ;% rtDW.gxgp4hskcm
                    section.data(2).logicalSrcIdx = 53;
                    section.data(2).dtTransOffset = 1;

                    ;% rtDW.kddtry4ekq
                    section.data(3).logicalSrcIdx = 54;
                    section.data(3).dtTransOffset = 2;

                    ;% rtDW.ggsva4qu4a
                    section.data(4).logicalSrcIdx = 55;
                    section.data(4).dtTransOffset = 3;

                    ;% rtDW.icv4qsjrec
                    section.data(5).logicalSrcIdx = 56;
                    section.data(5).dtTransOffset = 4;

            nTotData = nTotData + section.nData;
            dworkMap.sections(5) = section;
            clear section

            section.nData     = 5;
            section.data(5)  = dumData; %prealloc

                    ;% rtDW.hp42fr3fka
                    section.data(1).logicalSrcIdx = 57;
                    section.data(1).dtTransOffset = 0;

                    ;% rtDW.kc0x0orqmh
                    section.data(2).logicalSrcIdx = 58;
                    section.data(2).dtTransOffset = 1;

                    ;% rtDW.bdwu52mmaq
                    section.data(3).logicalSrcIdx = 59;
                    section.data(3).dtTransOffset = 2;

                    ;% rtDW.odkn5lgudq
                    section.data(4).logicalSrcIdx = 60;
                    section.data(4).dtTransOffset = 3;

                    ;% rtDW.lqozsqepug
                    section.data(5).logicalSrcIdx = 61;
                    section.data(5).dtTransOffset = 4;

            nTotData = nTotData + section.nData;
            dworkMap.sections(6) = section;
            clear section


            ;%
            ;% Non-auto Data (dwork)
            ;%


        ;%
        ;% Add final counts to struct.
        ;%
        dworkMap.nTotData = nTotData;



    ;%
    ;% Add individual maps to base struct.
    ;%

    targMap.paramMap  = paramMap;
    targMap.signalMap = sigMap;
    targMap.dworkMap  = dworkMap;

    ;%
    ;% Add checksums to base struct.
    ;%


    targMap.checksum0 = 2405234056;
    targMap.checksum1 = 151909971;
    targMap.checksum2 = 1794605402;
    targMap.checksum3 = 3767048926;

