/*
 * RV32IM CPU - Highly Optimized for Xilinx Artix-7 (A7-100)
 */

module AddressSpace (
	input [31:0] Ain,
	output [2:0] Enable
);
	wire s0;
	wire s1;
	assign s0 = ~ (~ Ain[18] | Ain[19] | Ain[20] | Ain[21] | Ain[22] | Ain[23] | Ain[24] | Ain[25] | Ain[26] | Ain[27] | Ain[28] | Ain[29] | Ain[30] | Ain[31]);
	assign s1 = ~ (Ain[18] | Ain[19] | Ain[20] | Ain[21] | Ain[22] | Ain[23] | Ain[24] | Ain[25] | Ain[26] | Ain[27] | Ain[28] | Ain[29] | Ain[30] | Ain[31]);
	assign Enable[0] = s1;
	assign Enable[1] = s0;
	assign Enable[2] = ~ (s1 | s0);
endmodule

module Decoder2 (
	output out_0,
	output out_1,
	output out_2,
	output out_3,
	input [1:0] sel
);
	assign out_0 = (sel == 2'h0);
	assign out_1 = (sel == 2'h1);
	assign out_2 = (sel == 2'h2);
	assign out_3 = (sel == 2'h3);
endmodule

module Decoder3 (
	output out_0, output out_1, output out_2, output out_3,
	output out_4, output out_5, output out_6, output out_7,
	input [2:0] sel
);
	assign out_0 = (sel == 3'h0);
	assign out_1 = (sel == 3'h1);
	assign out_2 = (sel == 3'h2);
	assign out_3 = (sel == 3'h3);
	assign out_4 = (sel == 3'h4);
	assign out_5 = (sel == 3'h5);
	assign out_6 = (sel == 3'h6);
	assign out_7 = (sel == 3'h7);
endmodule

module DIG_ROM_2048X32_INSROM (
	input [10:0] A,
	input sel,
	output reg [31:0] D
);
	reg [31:0] my_rom [0:304];

	always @ (*) begin
		if (~sel) D = 32'h0;
		else if (A > 11'h130) D = 32'h0;
		else D = my_rom[A];
	end

	initial begin
		my_rom[0] = 32'h802b7; my_rom[1] = 32'h2a023; my_rom[2] = 32'h40437; my_rom[3] = 32'h82ab7;
		my_rom[4] = 32'hfff00c13; my_rom[5] = 32'hc93; my_rom[6] = 32'h1f400fef; my_rom[7] = 32'hd13;
		my_rom[8] = 32'hd93; my_rom[9] = 32'h3e00513; my_rom[10] = 32'h220000ef; my_rom[11] = 32'h2000513;
		my_rom[12] = 32'h218000ef; my_rom[13] = 32'h493; my_rom[14] = 32'h913; my_rom[15] = 32'h80337;
		my_rom[16] = 32'h2430313; my_rom[17] = 32'h32383; my_rom[18] = 32'h13f393; my_rom[19] = 32'hfe038ce3;
		my_rom[20] = 32'h80337; my_rom[21] = 32'h2030313; my_rom[22] = 32'h34503; my_rom[23] = 32'h6100293;
		my_rom[24] = 32'h554863; my_rom[25] = 32'h7a00293; my_rom[26] = 32'ha2c463; my_rom[27] = 32'hfe050513;
		my_rom[28] = 32'h1d8000ef; my_rom[29] = 32'hd00293; my_rom[30] = 32'h4550e63; my_rom[31] = 32'ha00293;
		my_rom[32] = 32'h4550a63; my_rom[33] = 32'h3a00293; my_rom[34] = 32'ha550063; my_rom[35] = 32'h5200293;
		my_rom[36] = 32'h14550c63; my_rom[37] = 32'h3000293; my_rom[38] = 32'hfa5542e3; my_rom[39] = 32'h3900293;
		my_rom[40] = 32'ha2c663; my_rom[41] = 32'hfd050293; my_rom[42] = 32'h180006f; my_rom[43] = 32'h4100293;
		my_rom[44] = 32'hf85546e3; my_rom[45] = 32'h4600293; my_rom[46] = 32'hf8a2c2e3; my_rom[47] = 32'hfc950293;
		my_rom[48] = 32'hf2f293; my_rom[49] = 32'h449493; my_rom[50] = 32'h54e4b3; my_rom[51] = 32'h100913;
		my_rom[52] = 32'hf6dff06f; my_rom[53] = 32'h90463; my_rom[54] = 32'h48413; my_rom[55] = 32'h3a00513;
		my_rom[56] = 32'h168000ef; my_rom[57] = 32'h2000513; my_rom[58] = 32'h160000ef; my_rom[59] = 32'h42983;
		my_rom[60] = 32'h1c00a13; my_rom[61] = 32'h149d2b3; my_rom[62] = 32'hf2f293; my_rom[63] = 32'ha00313;
		my_rom[64] = 32'h62c663; my_rom[65] = 32'h3728293; my_rom[66] = 32'h80006f; my_rom[67] = 32'h3028293;
		my_rom[68] = 32'h28513; my_rom[69] = 32'h134000ef; my_rom[70] = 32'hffca0a13; my_rom[71] = 32'hfc0a5ce3;
		my_rom[72] = 32'h440413; my_rom[73] = 32'he00006f; my_rom[74] = 32'h90463; my_rom[75] = 32'h48413;
		my_rom[76] = 32'h493; my_rom[77] = 32'h913; my_rom[78] = 32'h80337; my_rom[79] = 32'h2430313;
		my_rom[80] = 32'h32383; my_rom[81] = 32'h13f393; my_rom[82] = 32'hfe038ce3; my_rom[83] = 32'h80337;
		my_rom[84] = 32'h2030313; my_rom[85] = 32'h34503; my_rom[86] = 32'h6100293; my_rom[87] = 32'h554863;
		my_rom[88] = 32'h7a00293; my_rom[89] = 32'ha2c463; my_rom[90] = 32'hfe050513; my_rom[91] = 32'hdc000ef;
		my_rom[92] = 32'h2000293; my_rom[93] = 32'h4550a63; my_rom[94] = 32'hd00293; my_rom[95] = 32'h4550e63;
		my_rom[96] = 32'ha00293; my_rom[97] = 32'h4550a63; my_rom[98] = 32'h3000293; my_rom[99] = 32'hfa5546e3;
		my_rom[100] = 32'h3900293; my_rom[101] = 32'ha2c663; my_rom[102] = 32'hfd050293; my_rom[103] = 32'h180006f;
		my_rom[104] = 32'h4100293; my_rom[105] = 32'hf8554ae3; my_rom[106] = 32'h4600293; my_rom[107] = 32'hf8a2c6e3;
		my_rom[108] = 32'hfc950293; my_rom[109] = 32'hf2f293; my_rom[110] = 32'h449493; my_rom[111] = 32'h54e4b3;
		my_rom[112] = 32'h100913; my_rom[113] = 32'hf75ff06f; my_rom[114] = 32'hf60908e3; my_rom[115] = 32'h942023;
		my_rom[116] = 32'h440413; my_rom[117] = 32'hf5dff06f; my_rom[118] = 32'h2090663; my_rom[119] = 32'h942023;
		my_rom[120] = 32'h440413; my_rom[121] = 32'h200006f; my_rom[122] = 32'h90463; my_rom[123] = 32'h48413;
		my_rom[124] = 32'hd13; my_rom[125] = 32'hd93; my_rom[126] = 32'h1400fef; my_rom[127] = 32'h93;
		my_rom[128] = 32'h40067; my_rom[129] = 32'h120000ef; my_rom[130] = 32'he1dff06f; my_rom[131] = 32'ha8293;
		my_rom[132] = 32'h1337; my_rom[133] = 32'hfa030313; my_rom[134] = 32'h182a023; my_rom[135] = 32'h182a223;
		my_rom[136] = 32'h182a423; my_rom[137] = 32'h182a623; my_rom[138] = 32'h182a823; my_rom[139] = 32'h182aa23;
		my_rom[140] = 32'h182ac23; my_rom[141] = 32'h182ae23; my_rom[142] = 32'h2028293; my_rom[143] = 32'hfff30313;
		my_rom[144] = 32'hfc031ce3; my_rom[145] = 32'hf8067; my_rom[146] = 32'ha00293; my_rom[147] = 32'hc550c63;
		my_rom[148] = 32'hd00293; my_rom[149] = 32'hc550863; my_rom[150] = 32'h2000293; my_rom[151] = 32'ha550e63;
		my_rom[152] = 32'he000fef; my_rom[153] = 32'h2d1293; my_rom[154] = 32'h1a282b3; my_rom[155] = 32'h2d9313;
		my_rom[156] = 32'h1d9393; my_rom[157] = 32'h730333; my_rom[158] = 32'h831e93; my_rom[159] = 32'h631f13;
		my_rom[160] = 32'h1ee8eb3; my_rom[161] = 32'h5e8eb3; my_rom[162] = 32'h1e9e93; my_rom[163] = 32'h15e8eb3;
		my_rom[164] = 32'h1300893; my_rom[165] = 32'h393; my_rom[166] = 32'h115df33; my_rom[167] = 32'h1f7f13;
		my_rom[168] = 32'hf0663; my_rom[169] = 32'h19e9023; my_rom[170] = 32'h80006f; my_rom[171] = 32'h18e9023;
		my_rom[172] = 32'hfff88893; my_rom[173] = 32'h115df33; my_rom[174] = 32'h1f7f13; my_rom[175] = 32'hf0663;
		my_rom[176] = 32'h19e9123; my_rom[177] = 32'h80006f; my_rom[178] = 32'h18e9123; my_rom[179] = 32'hfff88893;
		my_rom[180] = 32'h115df33; my_rom[181] = 32'h1f7f13; my_rom[182] = 32'hf0663; my_rom[183] = 32'h19e9223;
		my_rom[184] = 32'h80006f; my_rom[185] = 32'h18e9223; my_rom[186] = 32'hfff88893; my_rom[187] = 32'h115df33;
		my_rom[188] = 32'h1f7f13; my_rom[189] = 32'hf0663; my_rom[190] = 32'h19e9323; my_rom[191] = 32'h80006f;
		my_rom[192] = 32'h18e9323; my_rom[193] = 32'hfff88893; my_rom[194] = 32'h280e8e93; my_rom[195] = 32'h138393;
		my_rom[196] = 32'h500f13; my_rom[197] = 32'hf9e3c2e3; my_rom[198] = 32'h1d0d13; my_rom[199] = 32'h4000293;
		my_rom[200] = 32'h5d4e63; my_rom[201] = 32'hd13; my_rom[202] = 32'h1d8d93; my_rom[203] = 32'h2100293;
		my_rom[204] = 32'h5dc663; my_rom[205] = 32'hd93; my_rom[206] = 32'hed5fffef; my_rom[207] = 32'h8067;
		my_rom[208] = 32'h3000293; my_rom[209] = 32'h8550e63; my_rom[210] = 32'h3100293; my_rom[211] = 32'ha550063;
		my_rom[212] = 32'h3200293; my_rom[213] = 32'ha550263; my_rom[214] = 32'h3300293; my_rom[215] = 32'ha550463;
		my_rom[216] = 32'h3400293; my_rom[217] = 32'ha550663; my_rom[218] = 32'h3500293; my_rom[219] = 32'ha550863;
		my_rom[220] = 32'h3600293; my_rom[221] = 32'ha550a63; my_rom[222] = 32'h3700293; my_rom[223] = 32'ha550c63;
		my_rom[224] = 32'h3800293; my_rom[225] = 32'ha550e63; my_rom[226] = 32'h3900293; my_rom[227] = 32'hc550063;
		my_rom[228] = 32'h4100293; my_rom[229] = 32'hc550263; my_rom[230] = 32'h4200293; my_rom[231] = 32'hc550463;
		my_rom[232] = 32'h4300293; my_rom[233] = 32'hc550663; my_rom[234] = 32'h4400293; my_rom[235] = 32'hc550863;
		my_rom[236] = 32'h4500293; my_rom[237] = 32'hc550a63; my_rom[238] = 32'h4600293; my_rom[239] = 32'hc550c63;
		my_rom[240] = 32'h5200293; my_rom[241] = 32'hc550e63; my_rom[242] = 32'h3a00293; my_rom[243] = 32'he550063;
		my_rom[244] = 32'h3e00293; my_rom[245] = 32'he550263; my_rom[246] = 32'h593; my_rom[247] = 32'hf8067;
		my_rom[248] = 32'h6a5b7; my_rom[249] = 32'h99658593; my_rom[250] = 32'hf8067; my_rom[251] = 32'h4c5b7;
		my_rom[252] = 32'h44e58593; my_rom[253] = 32'hf8067; my_rom[254] = 32'h695b7; my_rom[255] = 32'h24f58593;
		my_rom[256] = 32'hf8067; my_rom[257] = 32'hf15b7; my_rom[258] = 32'h61f58593; my_rom[259] = 32'hf8067;
		my_rom[260] = 32'h9a5b7; my_rom[261] = 32'hf1158593; my_rom[262] = 32'hf8067; my_rom[263] = 32'hf95b7;
		my_rom[264] = 32'he1e58593; my_rom[265] = 32'hf8067; my_rom[266] = 32'h795b7; my_rom[267] = 32'he9658593;
		my_rom[268] = 32'hf8067; my_rom[269] = 32'hf15b7; my_rom[270] = 32'h24458593; my_rom[271] = 32'hf8067;
		my_rom[272] = 32'h695b7; my_rom[273] = 32'h69658593; my_rom[274] = 32'hf8067; my_rom[275] = 32'h695b7;
		my_rom[276] = 32'h71658593; my_rom[277] = 32'hf8067; my_rom[278] = 32'h6a5b7; my_rom[279] = 32'hf9958593;
		my_rom[280] = 32'hf8067; my_rom[281] = 32'hea5b7; my_rom[282] = 32'he9e58593; my_rom[283] = 32'hf8067;
		my_rom[284] = 32'h6a5b7; my_rom[285] = 32'h89658593; my_rom[286] = 32'hf8067; my_rom[287] = 32'hea5b7;
		my_rom[288] = 32'h99e58593; my_rom[289] = 32'hf8067; my_rom[290] = 32'hf95b7; my_rom[291] = 32'he8f58593;
		my_rom[292] = 32'hf8067; my_rom[293] = 32'hf95b7; my_rom[294] = 32'he8858593; my_rom[295] = 32'hf8067;
		my_rom[296] = 32'hea5b7; my_rom[297] = 32'hea958593; my_rom[298] = 32'hf8067; my_rom[299] = 32'h25b7;
		my_rom[300] = 32'h2058593; my_rom[301] = 32'hf8067; my_rom[302] = 32'h845b7; my_rom[303] = 32'h24858593;
		my_rom[304] = 32'hf8067;
	end
endmodule

module DIG_ROM_2048X32_RROM (
	input [10:0] A,
	input sel,
	output reg [31:0] D
);
	reg [31:0] my_rom [0:304];

	always @ (*) begin
		if (~sel) D = 32'h0;
		else if (A > 11'h130) D = 32'h0;
		else D = my_rom[A];
	end

	initial begin
		my_rom[0] = 32'h802b7; my_rom[1] = 32'h2a023; my_rom[2] = 32'h40437; my_rom[3] = 32'h82ab7;
		my_rom[4] = 32'hfff00c13; my_rom[5] = 32'hc93; my_rom[6] = 32'h1f400fef; my_rom[7] = 32'hd13;
		my_rom[8] = 32'hd93; my_rom[9] = 32'h3e00513; my_rom[10] = 32'h220000ef; my_rom[11] = 32'h2000513;
		my_rom[12] = 32'h218000ef; my_rom[13] = 32'h493; my_rom[14] = 32'h913; my_rom[15] = 32'h80337;
		my_rom[16] = 32'h2430313; my_rom[17] = 32'h32383; my_rom[18] = 32'h13f393; my_rom[19] = 32'hfe038ce3;
		my_rom[20] = 32'h80337; my_rom[21] = 32'h2030313; my_rom[22] = 32'h34503; my_rom[23] = 32'h6100293;
		my_rom[24] = 32'h554863; my_rom[25] = 32'h7a00293; my_rom[26] = 32'ha2c463; my_rom[27] = 32'hfe050513;
		my_rom[28] = 32'h1d8000ef; my_rom[29] = 32'hd00293; my_rom[30] = 32'h4550e63; my_rom[31] = 32'ha00293;
		my_rom[32] = 32'h4550a63; my_rom[33] = 32'h3a00293; my_rom[34] = 32'ha550063; my_rom[35] = 32'h5200293;
		my_rom[36] = 32'h14550c63; my_rom[37] = 32'h3000293; my_rom[38] = 32'hfa5542e3; my_rom[39] = 32'h3900293;
		my_rom[40] = 32'ha2c663; my_rom[41] = 32'hfd050293; my_rom[42] = 32'h180006f; my_rom[43] = 32'h4100293;
		my_rom[44] = 32'hf85546e3; my_rom[45] = 32'h4600293; my_rom[46] = 32'hf8a2c2e3; my_rom[47] = 32'hfc950293;
		my_rom[48] = 32'hf2f293; my_rom[49] = 32'h449493; my_rom[50] = 32'h54e4b3; my_rom[51] = 32'h100913;
		my_rom[52] = 32'hf6dff06f; my_rom[53] = 32'h90463; my_rom[54] = 32'h48413; my_rom[55] = 32'h3a00513;
		my_rom[56] = 32'h168000ef; my_rom[57] = 32'h2000513; my_rom[58] = 32'h160000ef; my_rom[59] = 32'h42983;
		my_rom[60] = 32'h1c00a13; my_rom[61] = 32'h149d2b3; my_rom[62] = 32'hf2f293; my_rom[63] = 32'ha00313;
		my_rom[64] = 32'h62c663; my_rom[65] = 32'h3728293; my_rom[66] = 32'h80006f; my_rom[67] = 32'h3028293;
		my_rom[68] = 32'h28513; my_rom[69] = 32'h134000ef; my_rom[70] = 32'hffca0a13; my_rom[71] = 32'hfc0a5ce3;
		my_rom[72] = 32'h440413; my_rom[73] = 32'he00006f; my_rom[74] = 32'h90463; my_rom[75] = 32'h48413;
		my_rom[76] = 32'h493; my_rom[77] = 32'h913; my_rom[78] = 32'h80337; my_rom[79] = 32'h2430313;
		my_rom[80] = 32'h32383; my_rom[81] = 32'h13f393; my_rom[82] = 32'hfe038ce3; my_rom[83] = 32'h80337;
		my_rom[84] = 32'h2030313; my_rom[85] = 32'h34503; my_rom[86] = 32'h6100293; my_rom[87] = 32'h554863;
		my_rom[88] = 32'h7a00293; my_rom[89] = 32'ha2c463; my_rom[90] = 32'hfe050513; my_rom[91] = 32'hdc000ef;
		my_rom[92] = 32'h2000293; my_rom[93] = 32'h4550a63; my_rom[94] = 32'hd00293; my_rom[95] = 32'h4550e63;
		my_rom[96] = 32'ha00293; my_rom[97] = 32'h4550a63; my_rom[98] = 32'h3000293; my_rom[99] = 32'hfa5546e3;
		my_rom[100] = 32'h3900293; my_rom[101] = 32'ha2c663; my_rom[102] = 32'hfd050293; my_rom[103] = 32'h180006f;
		my_rom[104] = 32'h4100293; my_rom[105] = 32'hf8554ae3; my_rom[106] = 32'h4600293; my_rom[107] = 32'hf8a2c6e3;
		my_rom[108] = 32'hfc950293; my_rom[109] = 32'hf2f293; my_rom[110] = 32'h449493; my_rom[111] = 32'h54e4b3;
		my_rom[112] = 32'h100913; my_rom[113] = 32'hf75ff06f; my_rom[114] = 32'hf60908e3; my_rom[115] = 32'h942023;
		my_rom[116] = 32'h440413; my_rom[117] = 32'hf5dff06f; my_rom[118] = 32'h2090663; my_rom[119] = 32'h942023;
		my_rom[120] = 32'h440413; my_rom[121] = 32'h200006f; my_rom[122] = 32'h90463; my_rom[123] = 32'h48413;
		my_rom[124] = 32'hd13; my_rom[125] = 32'hd93; my_rom[126] = 32'h1400fef; my_rom[127] = 32'h93;
		my_rom[128] = 32'h40067; my_rom[129] = 32'h120000ef; my_rom[130] = 32'he1dff06f; my_rom[131] = 32'ha8293;
		my_rom[132] = 32'h1337; my_rom[133] = 32'hfa030313; my_rom[134] = 32'h182a023; my_rom[135] = 32'h182a223;
		my_rom[136] = 32'h182a423; my_rom[137] = 32'h182a623; my_rom[138] = 32'h182a823; my_rom[139] = 32'h182aa23;
		my_rom[140] = 32'h182ac23; my_rom[141] = 32'h182ae23; my_rom[142] = 32'h2028293; my_rom[143] = 32'hfff30313;
		my_rom[144] = 32'hfc031ce3; my_rom[145] = 32'hf8067; my_rom[146] = 32'ha00293; my_rom[147] = 32'hc550c63;
		my_rom[148] = 32'hd00293; my_rom[149] = 32'hc550863; my_rom[150] = 32'h2000293; my_rom[151] = 32'ha550e63;
		my_rom[152] = 32'he000fef; my_rom[153] = 32'h2d1293; my_rom[154] = 32'h1a282b3; my_rom[155] = 32'h2d9313;
		my_rom[156] = 32'h1d9393; my_rom[157] = 32'h730333; my_rom[158] = 32'h831e93; my_rom[159] = 32'h631f13;
		my_rom[160] = 32'h1ee8eb3; my_rom[161] = 32'h5e8eb3; my_rom[162] = 32'h1e9e93; my_rom[163] = 32'h15e8eb3;
		my_rom[164] = 32'h1300893; my_rom[165] = 32'h393; my_rom[166] = 32'h115df33; my_rom[167] = 32'h1f7f13;
		my_rom[168] = 32'hf0663; my_rom[169] = 32'h19e9023; my_rom[170] = 32'h80006f; my_rom[171] = 32'h18e9023;
		my_rom[172] = 32'hfff88893; my_rom[173] = 32'h115df33; my_rom[174] = 32'h1f7f13; my_rom[175] = 32'hf0663;
		my_rom[176] = 32'h19e9123; my_rom[177] = 32'h80006f; my_rom[178] = 32'h18e9123; my_rom[179] = 32'hfff88893;
		my_rom[180] = 32'h115df33; my_rom[181] = 32'h1f7f13; my_rom[182] = 32'hf0663; my_rom[183] = 32'h19e9223;
		my_rom[184] = 32'h80006f; my_rom[185] = 32'h18e9223; my_rom[186] = 32'hfff88893; my_rom[187] = 32'h115df33;
		my_rom[188] = 32'h1f7f13; my_rom[189] = 32'hf0663; my_rom[190] = 32'h19e9323; my_rom[191] = 32'h80006f;
		my_rom[192] = 32'h18e9323; my_rom[193] = 32'hfff88893; my_rom[194] = 32'h280e8e93; my_rom[195] = 32'h138393;
		my_rom[196] = 32'h500f13; my_rom[197] = 32'hf9e3c2e3; my_rom[198] = 32'h1d0d13; my_rom[199] = 32'h4000293;
		my_rom[200] = 32'h5d4e63; my_rom[201] = 32'hd13; my_rom[202] = 32'h1d8d93; my_rom[203] = 32'h2100293;
		my_rom[204] = 32'h5dc663; my_rom[205] = 32'hd93; my_rom[206] = 32'hed5fffef; my_rom[207] = 32'h8067;
		my_rom[208] = 32'h3000293; my_rom[209] = 32'h8550e63; my_rom[210] = 32'h3100293; my_rom[211] = 32'ha550063;
		my_rom[212] = 32'h3200293; my_rom[213] = 32'ha550263; my_rom[214] = 32'h3300293; my_rom[215] = 32'ha550463;
		my_rom[216] = 32'h3400293; my_rom[217] = 32'ha550663; my_rom[218] = 32'h3500293; my_rom[219] = 32'ha550863;
		my_rom[220] = 32'h3600293; my_rom[221] = 32'ha550a63; my_rom[222] = 32'h3700293; my_rom[223] = 32'ha550c63;
		my_rom[224] = 32'h3800293; my_rom[225] = 32'ha550e63; my_rom[226] = 32'h3900293; my_rom[227] = 32'hc550063;
		my_rom[228] = 32'h4100293; my_rom[229] = 32'hc550263; my_rom[230] = 32'h4200293; my_rom[231] = 32'hc550463;
		my_rom[232] = 32'h4300293; my_rom[233] = 32'hc550663; my_rom[234] = 32'h4400293; my_rom[235] = 32'hc550863;
		my_rom[236] = 32'h4500293; my_rom[237] = 32'hc550a63; my_rom[238] = 32'h4600293; my_rom[239] = 32'hc550c63;
		my_rom[240] = 32'h5200293; my_rom[241] = 32'hc550e63; my_rom[242] = 32'h3a00293; my_rom[243] = 32'he550063;
		my_rom[244] = 32'h3e00293; my_rom[245] = 32'he550263; my_rom[246] = 32'h593; my_rom[247] = 32'hf8067;
		my_rom[248] = 32'h6a5b7; my_rom[249] = 32'h99658593; my_rom[250] = 32'hf8067; my_rom[251] = 32'h4c5b7;
		my_rom[252] = 32'h44e58593; my_rom[253] = 32'hf8067; my_rom[254] = 32'h695b7; my_rom[255] = 32'h24f58593;
		my_rom[256] = 32'hf8067; my_rom[257] = 32'hf15b7; my_rom[258] = 32'h61f58593; my_rom[259] = 32'hf8067;
		my_rom[260] = 32'h9a5b7; my_rom[261] = 32'hf1158593; my_rom[262] = 32'hf8067; my_rom[263] = 32'hf95b7;
		my_rom[264] = 32'he1e58593; my_rom[265] = 32'hf8067; my_rom[266] = 32'h795b7; my_rom[267] = 32'he9658593;
		my_rom[268] = 32'hf8067; my_rom[269] = 32'hf15b7; my_rom[270] = 32'h24458593; my_rom[271] = 32'hf8067;
		my_rom[272] = 32'h695b7; my_rom[273] = 32'h69658593; my_rom[274] = 32'hf8067; my_rom[275] = 32'h695b7;
		my_rom[276] = 32'h71658593; my_rom[277] = 32'hf8067; my_rom[278] = 32'h6a5b7; my_rom[279] = 32'hf9958593;
		my_rom[280] = 32'hf8067; my_rom[281] = 32'hea5b7; my_rom[282] = 32'he9e58593; my_rom[283] = 32'hf8067;
		my_rom[284] = 32'h6a5b7; my_rom[285] = 32'h89658593; my_rom[286] = 32'hf8067; my_rom[287] = 32'hea5b7;
		my_rom[288] = 32'h99e58593; my_rom[289] = 32'hf8067; my_rom[290] = 32'hf95b7; my_rom[291] = 32'he8f58593;
		my_rom[292] = 32'hf8067; my_rom[293] = 32'hf95b7; my_rom[294] = 32'he8858593; my_rom[295] = 32'hf8067;
		my_rom[296] = 32'hea5b7; my_rom[297] = 32'hea958593; my_rom[298] = 32'hf8067; my_rom[299] = 32'h25b7;
		my_rom[300] = 32'h2058593; my_rom[301] = 32'hf8067; my_rom[302] = 32'h845b7; my_rom[303] = 32'h24858593;
		my_rom[304] = 32'hf8067;
	end
endmodule

module DIG_ROM_32X13_INSLogic (
	input [4:0] A,
	input sel,
	output reg [12:0] D
);
	reg [12:0] my_rom [0:27];

	always @ (*) begin
		if (~sel) D = 13'h0;
		else if (A > 5'h1b) D = 13'h0;
		else D = my_rom[A];
	end

	initial begin
		my_rom[0] = 13'h1026; my_rom[1] = 13'h0; my_rom[2] = 13'h0; my_rom[3] = 13'h0;
		my_rom[4] = 13'h22; my_rom[5] = 13'h312; my_rom[6] = 13'h0; my_rom[7] = 13'h0;
		my_rom[8] = 13'h1121; my_rom[9] = 13'h0; my_rom[10] = 13'h0; my_rom[11] = 13'h0;
		my_rom[12] = 13'h802; my_rom[13] = 13'h30e; my_rom[14] = 13'h0; my_rom[15] = 13'h0;
		my_rom[16] = 13'h0; my_rom[17] = 13'h0; my_rom[18] = 13'h0; my_rom[19] = 13'h0;
		my_rom[20] = 13'h0; my_rom[21] = 13'h0; my_rom[22] = 13'h0; my_rom[23] = 13'h0;
		my_rom[24] = 13'h1ac0; my_rom[25] = 13'h10aa; my_rom[26] = 13'h0; my_rom[27] = 13'h44a;
	end
endmodule

module DIG_ROM_64X5_ALUOP (
	input [5:0] A,
	input sel,
	output reg [4:0] D
);
	reg [4:0] my_rom [0:61];

	always @ (*) begin
		if (~sel) D = 5'h0;
		else if (A > 6'h3d) D = 5'h0;
		else D = my_rom[A];
	end

	initial begin
		my_rom[0] = 5'h0; my_rom[1] = 5'h0; my_rom[2] = 5'h0; my_rom[3] = 5'h0;
		my_rom[4] = 5'h7; my_rom[5] = 5'h0; my_rom[6] = 5'h0; my_rom[7] = 5'h0;
		my_rom[8] = 5'h6; my_rom[9] = 5'h6; my_rom[10] = 5'h6; my_rom[11] = 5'h6;
		my_rom[12] = 5'h5; my_rom[13] = 5'h5; my_rom[14] = 5'h5; my_rom[15] = 5'h5;
		my_rom[16] = 5'h4; my_rom[17] = 5'h4; my_rom[18] = 5'h4; my_rom[19] = 5'h4;
		my_rom[20] = 5'h8; my_rom[21] = 5'h0; my_rom[22] = 5'h9; my_rom[23] = 5'h0;
		my_rom[24] = 5'h3; my_rom[25] = 5'h3; my_rom[26] = 5'h3; my_rom[27] = 5'h3;
		my_rom[28] = 5'h2; my_rom[29] = 5'h2; my_rom[30] = 5'h2; my_rom[31] = 5'h2;
		my_rom[32] = 5'h0; my_rom[33] = 5'ha; my_rom[34] = 5'h1; my_rom[35] = 5'h0;
		my_rom[36] = 5'h7; my_rom[37] = 5'hb; my_rom[38] = 5'h0; my_rom[39] = 5'h0;
		my_rom[40] = 5'h6; my_rom[41] = 5'hd; my_rom[42] = 5'h0; my_rom[43] = 5'h0;
		my_rom[44] = 5'h5; my_rom[45] = 5'hc; my_rom[46] = 5'h0; my_rom[47] = 5'h0;
		my_rom[48] = 5'h4; my_rom[49] = 5'he; my_rom[50] = 5'h0; my_rom[51] = 5'h0;
		my_rom[52] = 5'h8; my_rom[53] = 5'hf; my_rom[54] = 5'h9; my_rom[55] = 5'h0;
		my_rom[56] = 5'h3; my_rom[57] = 5'h10; my_rom[58] = 5'h0; my_rom[59] = 5'h0;
		my_rom[60] = 5'h2; my_rom[61] = 5'h11;
	end
endmodule

module Mux_2x1_NBits #(parameter Bits = 2) (
	input [0:0] sel,
	input [(Bits - 1):0] in_0, input [(Bits - 1):0] in_1,
	output reg [(Bits - 1):0] out
);
	always @ (*) out = sel ? in_1 : in_0;
endmodule

module Mux_4x1 (
	input [1:0] sel,
	input in_0, input in_1, input in_2, input in_3,
	output reg out
);
	always @ (*) begin
		case (sel)
			2'h0: out = in_0; 2'h1: out = in_1;
			2'h2: out = in_2; 2'h3: out = in_3;
			default: out = 1'b0;
		endcase
	end
endmodule

module Mux_4x1_NBits #(parameter Bits = 2) (
	input [1:0] sel,
	input [(Bits - 1):0] in_0, input [(Bits - 1):0] in_1,
	input [(Bits - 1):0] in_2, input [(Bits - 1):0] in_3,
	output reg [(Bits - 1):0] out
);
	always @ (*) begin
		case (sel)
			2'h0: out = in_0; 2'h1: out = in_1;
			2'h2: out = in_2; 2'h3: out = in_3;
			default: out = 'h0;
		endcase
	end
endmodule

module Mux_8x1_NBits #(parameter Bits = 2) (
	input [2:0] sel,
	input [(Bits - 1):0] in_0, input [(Bits - 1):0] in_1,
	input [(Bits - 1):0] in_2, input [(Bits - 1):0] in_3,
	input [(Bits - 1):0] in_4, input [(Bits - 1):0] in_5,
	input [(Bits - 1):0] in_6, input [(Bits - 1):0] in_7,
	output reg [(Bits - 1):0] out
);
	always @ (*) begin
		case (sel)
			3'h0: out = in_0; 3'h1: out = in_1; 3'h2: out = in_2; 3'h3: out = in_3;
			3'h4: out = in_4; 3'h5: out = in_5; 3'h6: out = in_6; 3'h7: out = in_7;
			default: out = 'h0;
		endcase
	end
endmodule

module Mux_16x1_NBits #(parameter Bits = 2) (
	input [3:0] sel,
	input [(Bits - 1):0] in_0, input [(Bits - 1):0] in_1,
	input [(Bits - 1):0] in_2, input [(Bits - 1):0] in_3,
	input [(Bits - 1):0] in_4, input [(Bits - 1):0] in_5,
	input [(Bits - 1):0] in_6, input [(Bits - 1):0] in_7,
	input [(Bits - 1):0] in_8, input [(Bits - 1):0] in_9,
	input [(Bits - 1):0] in_10, input [(Bits - 1):0] in_11,
	input [(Bits - 1):0] in_12, input [(Bits - 1):0] in_13,
	input [(Bits - 1):0] in_14, input [(Bits - 1):0] in_15,
	output reg [(Bits - 1):0] out
);
	always @ (*) begin
		case (sel)
			4'h0: out = in_0; 4'h1: out = in_1; 4'h2: out = in_2; 4'h3: out = in_3;
			4'h4: out = in_4; 4'h5: out = in_5; 4'h6: out = in_6; 4'h7: out = in_7;
			4'h8: out = in_8; 4'h9: out = in_9; 4'ha: out = in_10; 4'hb: out = in_11;
			4'hc: out = in_12; 4'hd: out = in_13; 4'he: out = in_14; 4'hf: out = in_15;
			default: out = 'h0;
		endcase
	end
endmodule

module DIG_BitExtender #(parameter inputBits = 2, parameter outputBits = 4) (
	input [(inputBits-1):0] in,
	output [(outputBits - 1):0] out
);
	assign out = {{(outputBits - inputBits){in[inputBits - 1]}}, in};
endmodule

module DIG_BitExtenderSingle #(parameter outputBits = 2) (
	input in,
	output [(outputBits - 1):0] out
);
	assign out = {outputBits{in}};
endmodule

// ===================================================================================
// Optimized BRAM Implementation - 4 Byte Lanes mapped natively to Vivado Block RAM
// ===================================================================================
module RAM_256KB (
	input [15:0] INSAddressIn,
	input [5:0] ByteSelect,
	input [15:0] AddressIn,
	input [31:0] Din,
	input We,
	input Clock,
	output reg [31:0] Dout,
	output reg [31:0] INSout
);
	(* ram_style = "block" *) reg [7:0] mem0 [0:65535];
	(* ram_style = "block" *) reg [7:0] mem1 [0:65535];
	(* ram_style = "block" *) reg [7:0] mem2 [0:65535];
	(* ram_style = "block" *) reg [7:0] mem3 [0:65535];

	always @(posedge Clock) begin
		// Port 1: Read & Write Data
		if (We) begin
			if (ByteSelect[0]) mem0[AddressIn] <= Din[7:0];
			if (ByteSelect[1]) mem1[AddressIn] <= Din[15:8];
			if (ByteSelect[2]) mem2[AddressIn] <= Din[23:16];
			if (ByteSelect[3]) mem3[AddressIn] <= Din[31:24];
		end
		Dout[7:0]   <= mem0[AddressIn];
		Dout[15:8]  <= mem1[AddressIn];
		Dout[23:16] <= mem2[AddressIn];
		Dout[31:24] <= mem3[AddressIn];

		// Port 2: Read-Only Instruction Fetch
		INSout[7:0]   <= mem0[INSAddressIn];
		INSout[15:8]  <= mem1[INSAddressIn];
		INSout[23:16] <= mem2[INSAddressIn];
		INSout[31:24] <= mem3[INSAddressIn];
	end
endmodule

module MemoryMapperExp (
	input Clock,
	input [31:0] Din, input [31:0] Ain, input [31:0] INSAin, input [5:0] ByteSelect,
	input We, input [2:0] RegInsel, input [31:0] DrIO,
	output [31:0] INSout, output [31:0] Dout, output [31:0] AddIO, output [31:0] DwIO,
	output [3:0] WeIO, output ReIO, output CLKIO
);
	wire [15:0] s0 = INSAin[17:2];
	wire [15:0] s1 = Ain[17:2];
	wire [31:0] DwIO_temp;
	wire [31:0] s3, s4;
	wire [10:0] s6 = Ain[12:2];
	wire [31:0] s7, s8, s10;
	wire [2:0] s11, s13;
	wire [10:0] s16 = INSAin[12:2];
	wire s17 = ByteSelect[4];
	wire s25 = ByteSelect[5];
	
	wire [7:0] s19 = Din[7:0];
	wire [7:0] s18 = Din[15:8];
	wire [7:0] s21 = Din[23:16];
	wire [7:0] s23 = Din[31:24];
	
	wire [7:0] s20, s22, s24, s26, s27;
	wire [3:0] s28;
	wire s15;

	AddressSpace AddressSpace_i0 (.Ain(Ain), .Enable(s11));
	AddressSpace AddressSpace_i1 (.Ain(INSAin), .Enable(s13));
	Decoder3 Decoder3_i2 (.sel(RegInsel), .out_1(s15));
	
	DIG_ROM_2048X32_INSROM DIG_ROM_2048X32_INSROM_i3 (.A(s16), .sel(1'b1), .D(s10));
	DIG_ROM_2048X32_RROM DIG_ROM_2048X32_RROM_i4 (.A(s6), .sel(1'b1), .D(s7));

	Mux_2x1_NBits #(.Bits(8)) Mux_2x1_NBits_i5 (.sel(s17), .in_0(s18), .in_1(s19), .out(s20));
	Mux_2x1_NBits #(.Bits(8)) Mux_2x1_NBits_i6 (.sel(s17), .in_0(s21), .in_1(s19), .out(s22));
	Mux_2x1_NBits #(.Bits(8)) Mux_2x1_NBits_i7 (.sel(s17), .in_0(s23), .in_1(s19), .out(s24));

	wire s5 = s11[1];
	wire s12 = s11[2];
	wire s9 = s13[1];
	wire s2 = (We & s5);
	wire s14 = (We & s12);
	assign ReIO = (s12 & s15);

	Mux_2x1_NBits #(.Bits(8)) Mux_2x1_NBits_i8 (.sel(s25), .in_0(s22), .in_1(s19), .out(s26));
	Mux_2x1_NBits #(.Bits(8)) Mux_2x1_NBits_i9 (.sel(s25), .in_0(s24), .in_1(s20), .out(s27));

	assign DwIO_temp = {s27, s26, s20, s19};
	DIG_BitExtenderSingle #(.outputBits(4)) DIG_BitExtenderSingle_i10 (.in(s14), .out(s28));

	RAM_256KB RAM_256KB_i11 (
		.INSAddressIn(s0), .ByteSelect(ByteSelect), .AddressIn(s1),
		.Din(DwIO_temp), .We(s2), .Clock(Clock), .Dout(s3), .INSout(s4)
	);

	assign WeIO = (s28 & ByteSelect[3:0]);
	Mux_2x1_NBits #(.Bits(32)) Mux_2x1_NBits_i12 (.sel(s5), .in_0(s7), .in_1(s3), .out(s8));
	Mux_2x1_NBits #(.Bits(32)) Mux_2x1_NBits_i13 (.sel(s9), .in_0(s10), .in_1(s4), .out(INSout));
	Mux_2x1_NBits #(.Bits(32)) Mux_2x1_NBits_i14 (.sel(s12), .in_0(s8), .in_1(DrIO), .out(Dout));

	assign AddIO = Ain;
	assign DwIO = DwIO_temp;
	assign CLKIO = Clock;
endmodule

module DataController (
	input [31:0] AddressIn, input [31:0] DinMMU,
	input \Signed , input half, input isbyte,
	output [31:0] AddressOut, output [31:0] DoCPU, output [5:0] ByteSelect
);
	wire [1:0] s0 = AddressIn[1:0];
	wire [7:0] s1 = DinMMU[7:0], s2 = DinMMU[15:8], s3 = DinMMU[23:16], s4 = DinMMU[31:24];
	wire [15:0] s5 = {s2, s1}, s6 = {s3, s2}, s7 = {s4, s3};
	wire [31:0] s8, s12, s16, s20, s10, s14, s18;
	
	DIG_BitExtender #(.inputBits(8), .outputBits(32)) DIG_BitExtender_i0 (.in(s1), .out(s8));
	wire [31:0] s9 = {24'b0, s1};
	DIG_BitExtender #(.inputBits(8), .outputBits(32)) DIG_BitExtender_i1 (.in(s2), .out(s12));
	wire [31:0] s13 = {24'b0, s2};
	DIG_BitExtender #(.inputBits(8), .outputBits(32)) DIG_BitExtender_i2 (.in(s3), .out(s16));
	wire [31:0] s17 = {24'b0, s3};
	DIG_BitExtender #(.inputBits(8), .outputBits(32)) DIG_BitExtender_i3 (.in(s4), .out(s20));
	wire [31:0] s21 = {24'b0, s4};
	
	DIG_BitExtender #(.inputBits(16), .outputBits(32)) DIG_BitExtender_i5 (.in(s5), .out(s10));
	wire [31:0] s11 = {16'b0, s5};
	DIG_BitExtender #(.inputBits(16), .outputBits(32)) DIG_BitExtender_i6 (.in(s6), .out(s14));
	wire [31:0] s15 = {16'b0, s6};
	DIG_BitExtender #(.inputBits(16), .outputBits(32)) DIG_BitExtender_i7 (.in(s7), .out(s18));
	wire [31:0] s19 = {16'b0, s7};
	
	wire s27, s28, s29, s30;
	Decoder2 Decoder2_i4 (.sel(s0), .out_0(s27), .out_1(s28), .out_2(s29), .out_3(s30));

	wire [3:0] s22 = {s0, ~isbyte, ~\Signed };
	wire [31:0] s23;
	Mux_16x1_NBits #(.Bits(32)) Mux_16x1_NBits_i8 (
		.sel(s22), .in_0(s8), .in_1(s9), .in_2(s10), .in_3(s11),
		.in_4(s12), .in_5(s13), .in_6(s14), .in_7(s15),
		.in_8(s16), .in_9(s17), .in_10(s18), .in_11(s19),
		.in_12(s20), .in_13(s21), .in_14(32'b0), .in_15(32'b0), .out(s23)
	);

	wire [3:0] s25 = {((s29 & half) | s30), ((s28 & half) | s29), ((s27 & half) | s28), s27};
	wire s24 = (half | isbyte);
	wire [3:0] s26;
	Mux_2x1_NBits #(.Bits(4)) Mux_2x1_NBits_i9 (.sel(s24), .in_0(4'b1111), .in_1(s25), .out(s26));
	Mux_2x1_NBits #(.Bits(32)) Mux_2x1_NBits_i10 (.sel(s24), .in_0(DinMMU), .in_1(s23), .out(DoCPU));

	assign ByteSelect = {half, isbyte, s26};
	assign AddressOut = AddressIn;
endmodule

module InstructionSplicer (
	input [2:0] ImmSel, input [31:0] INSin,
	output [6:0] funct7, output [2:0] funct3, output [6:0] opcode,
	output [4:0] rs1, output [4:0] rs2, output [4:0] rd,
	output [31:0] Imm
);
	wire [31:0] s1, s3, s5, s8;
	DIG_BitExtender #(.inputBits(12), .outputBits(32)) DIG_BitExtender_i0 (.in(INSin[31:20]), .out(s1));
	DIG_BitExtender #(.inputBits(12), .outputBits(32)) DIG_BitExtender_i1 (.in({INSin[31:25], INSin[11:7]}), .out(s3));
	DIG_BitExtender #(.inputBits(13), .outputBits(32)) DIG_BitExtender_i2 (.in({INSin[31], INSin[7], INSin[30:25], INSin[11:8], 1'b0}), .out(s5));
	DIG_BitExtender #(.inputBits(21), .outputBits(32)) DIG_BitExtender_i3 (.in({INSin[31], INSin[19:12], INSin[20], INSin[30:21], 1'b0}), .out(s8));
	wire [31:0] s6 = {INSin[31:12], 12'b0};

	assign opcode = INSin[6:0]; assign rd = INSin[11:7]; assign funct3 = INSin[14:12];
	assign rs1 = INSin[19:15]; assign rs2 = INSin[24:20]; assign funct7 = INSin[31:25];

	Mux_8x1_NBits #(.Bits(32)) Mux_8x1_NBits_i4 (
		.sel(ImmSel), .in_0(s1), .in_1(s3), .in_2(s5), .in_3(s6),
		.in_4(s8), .in_5(32'b0), .in_6(32'b0), .in_7(32'b0), .out(Imm)
	);
endmodule

module ControlLogic (
	input [6:0] funct7, input [2:0] funct3, input [6:0] opcode,
	output [2:0] InsTypeSel, output [1:0] BrInsSel, output [1:0] PCInSel,
	output DSigned, output DHalf, output DByte,
	output [4:0] ALUOpSel, output ALUInSel, output [2:0] RegInSel,
	output RegWe, output MemWe
);
	wire [12:0] s1;
	wire [4:0] s3, s4;
	wire s7;
	assign BrInsSel = {funct3[2], funct3[0]};
	assign DSigned = ~ funct3[2];
	
	DIG_ROM_32X13_INSLogic DIG_ROM_32X13_INSLogic_i0 (.A(opcode[6:2]), .sel(1'b1), .D(s1));
	Decoder2 Decoder2_i1 (.sel(funct3[1:0]), .out_0(DByte), .out_1(DHalf));
	Mux_2x1_NBits #(.Bits(5)) Mux_2x1_NBits_i2 (.sel(funct3[1]), .in_0(5'b110), .in_1(5'b101), .out(s4));
	
	assign MemWe = s1[0]; assign RegWe = s1[1]; assign RegInSel = s1[4:2];
	assign ALUInSel = s1[5]; assign PCInSel = s1[7:6]; assign InsTypeSel = s1[10:8];
	
	Decoder2 Decoder2_i3 (.sel(s1[12:11]), .out_1(s7));
	DIG_ROM_64X5_ALUOP DIG_ROM_64X5_ALUOP_i4 (.A({s7, funct3, funct7[5], funct7[0]}), .sel(1'b1), .D(s3));
	Mux_4x1_NBits #(.Bits(5)) Mux_4x1_NBits_i5 (.sel(s1[12:11]), .in_0(s3), .in_1(s3), .in_2(5'b0), .in_3(s4), .out(ALUOpSel));
endmodule

// ===================================================================================
// OPTIMIZED: 16-Cycle Radix-4 Unrolled Restoring Divider FSM (2 bits per clock cycle)
// ===================================================================================
module SequentialDivider (
	input clk,
	input start,
	input [31:0] dividend,
	input [31:0] divisor,
	input is_signed,
	input is_rem,
	output reg [31:0] out,
	output ready
);
	reg [31:0] Q, R, B;
	reg [4:0] count;
	reg sign_Q, sign_R, div_by_zero;
	reg busy, ready_reg;

	assign ready = ready_reg;

	// Stage 1 (Combinational - MUST be 33 bits to prevent MSB truncation during shift)
	wire [32:0] R_stage1 = {R[31:0], Q[31]};
	wire [32:0] B_ext = {1'b0, B};
	wire stage1_sub = (R_stage1 >= B_ext);
	wire [31:0] R_next1 = stage1_sub ? (R_stage1 - B_ext) : R_stage1[31:0];

	// Stage 2 (Combinational - MUST be 33 bits)
	wire [32:0] R_stage2 = {R_next1[31:0], Q[30]};
	wire stage2_sub = (R_stage2 >= B_ext);
	wire [31:0] R_next2 = stage2_sub ? (R_stage2 - B_ext) : R_stage2[31:0];

	initial begin busy = 0; ready_reg = 0; out = 0; end

	always @(posedge clk) begin
		// Wait for start, but ONLY if we aren't currently emitting a finished result
		if (start && !busy && !ready_reg) begin
			busy <= 1;
			count <= 16;
			B <= (is_signed && divisor[31]) ? -divisor : divisor;
			Q <= (is_signed && dividend[31]) ? -dividend : dividend;
			R <= 0;
			sign_Q <= is_signed && (dividend[31] ^ divisor[31]);
			sign_R <= is_signed && dividend[31];
			div_by_zero <= (divisor == 0);
		end else if (busy) begin
			if (count > 0) begin
				R <= R_next2;
				Q <= {Q[29:0], stage1_sub, stage2_sub};
				count <= count - 1;
			end else begin
				if (div_by_zero) out <= is_rem ? dividend : 32'hFFFFFFFF;
				else out <= is_rem ? (sign_R ? -R : R) : (sign_Q ? -Q : Q);
				busy <= 0;
				ready_reg <= 1; // Signal to ALU that math is complete
			end
		end else if (ready_reg) begin
			ready_reg <= 0; // Clear flag instantly once CPU commits the result
		end
	end
endmodule

// ===================================================================================
// OPTIMIZED: Behavioral ALU mapping cleanly to DSP Slices and LUT Barrel Shifters
// ===================================================================================
module ALU (
	input CLK,
	input [4:0] OPSELECT,
	input [31:0] B,
	input [31:0] A,
	output reg [31:0] O,
	output [1:0] Flags,
	output Busy
);
	wire is_div = (OPSELECT >= 5'b01110) && (OPSELECT <= 5'b10001);
	wire div_ready;
	wire [31:0] div_out;

	SequentialDivider div_inst (
		.clk(CLK),
		.start(is_div), 
		.dividend(A),
		.divisor(B),
		.is_signed(OPSELECT == 5'b01110 || OPSELECT == 5'b10000),
		.is_rem(OPSELECT == 5'b10000 || OPSELECT == 5'b10001),
		.out(div_out),
		.ready(div_ready) // Hook up the new ready flag
	);

	// CPU stalls immediately when a DIV is seen, and resumes exactly when ready goes high
	assign Busy = is_div && !div_ready; 

	// Fast Hardware Multiplier (DSP48E1 Inference)
	wire signed [32:0] a_ext = {(OPSELECT == 5'b01011 || OPSELECT == 5'b01101) ? A[31] : 1'b0, A};
	wire signed [32:0] b_ext = {(OPSELECT == 5'b01011) ? B[31] : 1'b0, B};
	wire signed [65:0] prod = a_ext * b_ext;

	always @(*) begin
		case (OPSELECT)
			5'b00000: O = A + B;
			5'b00001: O = A - B;
			5'b00010: O = A & B;
			5'b00011: O = A | B;
			5'b00100: O = A ^ B;
			5'b00101: O = {31'b0, A < B}; 
			5'b00110: O = {31'b0, $signed(A) < $signed(B)}; 
			5'b00111: O = A << B[4:0];	
			5'b01000: O = A >> B[4:0];
			5'b01001: O = $signed(A) >>> B[4:0];
			5'b01010: O = prod[31:0];	 
			5'b01011, 5'b01100, 5'b01101: O = prod[63:32]; 
			5'b01110, 5'b01111, 5'b10000, 5'b10001: O = div_out; 
			default: O = 32'b0;
		endcase
	end

	// Branch evaluation relies on these exactly mapping back to PcInSelector
	assign Flags[1] = (A == B); // Zero Flag
	assign Flags[0] = O[0];	 // LessThan Flag (derived directly from compare ops)
endmodule

module DIG_RegisterFile #(parameter Bits = 8, parameter AddrBits = 4) (
	input [(Bits-1):0] Din, input we, input [(AddrBits-1):0] Rw,
	input C, input [(AddrBits-1):0] Ra, input [(AddrBits-1):0] Rb,
	output [(Bits-1):0] Da, output [(Bits-1):0] Db
);
	reg [(Bits-1):0] memory[0:((1 << AddrBits)-1)];
	assign Da = memory[Ra];
	assign Db = memory[Rb];
	always @ (posedge C) begin
		if (we) memory[Rw] <= Din;
	end
endmodule

module Registers (
	input clk, input EN, input [31:0] Din, input We,
	input [4:0] rs1, input [4:0] rs2, input [4:0] rd,
	output [31:0] rs1O, output [31:0] rs2O
);
	wire [31:0] s1, s2;
	// Stall register write if EN is low (e.g. during division)
	wire s0 = (We & (rd != 0) & EN);
	
	DIG_RegisterFile #(.Bits(32), .AddrBits(5)) DIG_RegisterFile_i0 (
		.Din(Din), .we(s0), .Rw(rd), .C(clk), .Ra(rs1), .Rb(rs2), .Da(s1), .Db(s2)
	);
	
	assign rs1O = (rs1 == 0) ? 32'b0 : s1;
	assign rs2O = (rs2 == 0) ? 32'b0 : s2;
endmodule

module PcInSelector (
	input [1:0] BranchIns, input [1:0] PcInSel, input [1:0] Flags,
	input [31:0] ALU, input [31:0] AdAdd, input [31:0] \PC+4 ,
	output [31:0] PC
);
	wire s1;
	wire s4 = Flags[0];
	wire s2 = Flags[1];
	wire s3 = ~ s2;
	wire s5 = ~ s4;
	Mux_4x1 Mux_4x1_i0 (.sel(BranchIns), .in_0(s2), .in_1(s3), .in_2(s4), .in_3(s5), .out(s1));
	
	wire [31:0] s0;
	Mux_2x1_NBits #(.Bits(32)) Mux_2x1_NBits_i1 (.sel(s1), .in_0(\PC+4 ), .in_1(AdAdd), .out(s0));
	Mux_4x1_NBits #(.Bits(32)) Mux_4x1_NBits_i2 (.sel(PcInSel), .in_0(\PC+4 ), .in_1(AdAdd), .in_2(ALU), .in_3(s0), .out(PC));
endmodule

// ===================================================================================
// OPTIMIZED: Program Counter with direct internal register & Stall Enable
// ===================================================================================
module ProgramCounter (
	input Clock,
	input EN, // Added for pipeline stall capability
	input [31:0] Din,
	output reg [31:0] Dout,
	output [31:0] \PC+4 
);
	initial Dout = 32'b0;
	always @ (posedge Clock) begin
		// PC is frozen while CPU is Busy (Division)
		if (EN) Dout <= {Din[31:1], 1'b0};
	end
	assign \PC+4 = Dout + 4;
endmodule

module main_cpu (
	input CLK,
	input [31:0] DrIO,
	output [31:0] AddIO, output [31:0] DwIO, output [3:0] WeIO,
	output ReIO, output CLKIO
);
	wire [4:0] s0;
	wire [31:0] s1, s2, s3;
	wire [1:0] s4;
	wire [31:0] s5;
	wire s6;
	wire [4:0] s7, s8, s9;
	wire [31:0] s10, s11;
	wire s12, s13, s14;
	wire [31:0] s15, s16;
	wire [5:0] s17;
	wire [2:0] s18;
	wire [31:0] s19, s20, s21, s22, s23;
	wire s24;
	wire [2:0] s25;
	wire [31:0] s26;
	wire [6:0] s27;
	wire [2:0] s28;
	wire [6:0] s29;
	wire [1:0] s30, s31;
	wire s32;
	
	wire cpu_busy; // Core Stall Signal (High during Multi-cycle Math)

	MemoryMapperExp MemoryMapperExp_i0 (
		.Clock(CLK), .Din(s10), .Ain(s15), .INSAin(s23), .ByteSelect(s17),
		.We(s32 & ~cpu_busy), // Protect against writes during stalls
		.RegInsel(s18), .DrIO(DrIO), .INSout(s26), .Dout(s11), .AddIO(AddIO),
		.DwIO(DwIO), .WeIO(WeIO), .ReIO(ReIO), .CLKIO(CLKIO)
	);
	
	DataController DataController_i1 (
		.AddressIn(s3), .DinMMU(s11), .\Signed (s12), .half(s13), .isbyte(s14),
		.AddressOut(s15), .DoCPU(s16), .ByteSelect(s17)
	);
	
	InstructionSplicer InstructionSplicer_i2 (
		.ImmSel(s25), .INSin(s26), .funct7(s27), .funct3(s28), .opcode(s29),
		.rs1(s7), .rs2(s8), .rd(s9), .Imm(s20)
	);
	
	ControlLogic ControlLogic_i3 (
		.funct7(s27), .funct3(s28), .opcode(s29), .InsTypeSel(s25), .BrInsSel(s30),
		.PCInSel(s31), .DSigned(s12), .DHalf(s13), .DByte(s14),
		.ALUOpSel(s0), .ALUInSel(s24), .RegInSel(s18), .RegWe(s6), .MemWe(s32)
	);
	
	ALU ALU_i4 (
		.CLK(CLK), 
		.OPSELECT(s0), .B(s1), .A(s2), .O(s3), .Flags(s4), 
		.Busy(cpu_busy)
	);
	
	Registers Registers_i5 (
		.clk(CLK), 
		.EN(~cpu_busy), // Stall writeback
		.Din(s5), .We(s6), .rs1(s7), .rs2(s8), .rd(s9), .rs1O(s2), .rs2O(s10)
	);
	
	Mux_8x1_NBits #(.Bits(32)) Mux_8x1_NBits_i6 (
		.sel(s18), .in_0(s3), .in_1(s16), .in_2(s19), .in_3(s20), .in_4(s21),
		.in_5(32'b0), .in_6(32'b0), .in_7(32'b0), .out(s5)
	);
	
	// OPTIMIZED: Replaced the bulky DIG_Add module with native addition to generate branch target
	assign s21 = s20 + s23;

	Mux_2x1_NBits #(.Bits(32)) Mux_2x1_NBits_i8 (.sel(s24), .in_0(s10), .in_1(s20), .out(s1));
	
	PcInSelector PcInSelector_i9 (
		.BranchIns(s30), .PcInSel(s31), .Flags(s4), .ALU(s3), .AdAdd(s21),
		.\PC+4 (s19), .PC(s22)
	);
	
	ProgramCounter ProgramCounter_i10 (
		.Clock(CLK),
		.EN(~cpu_busy), // Stall Program Counter
		.Din(s22), .Dout(s23), .\PC+4 (s19)
	);
endmodule