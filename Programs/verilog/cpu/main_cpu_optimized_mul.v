/*
 * Highly Optimized Verilog Export for Verilator
 * - Clock Gating and Stall logic eradicated.
 * - Instruction and Data ROMs consolidated into a single Dual-Port ROM.
 * - Logic ROMs RESTORED to Arrays for O(1) C++ Pointer lookups
 */

module AddressSpace (
  input [31:0] Ain,
  output [2:0] Enable
);
  assign Enable[0] = (Ain[31:18] == 14'h0); 
  assign Enable[1] = (Ain[31:18] == 14'h1); 
  assign Enable[2] = ~(Enable[0] | Enable[1]);
endmodule

module DualPortROM (
    input [10:0] A1,
    input [10:0] A2,
    output reg [31:0] D1,
    output reg [31:0] D2
);
    reg [31:0] my_rom [0:2047];

    always @ (*) begin
        D1 = (A1 > 11'h130) ? 32'h0 : my_rom[A1];
        D2 = (A2 > 11'h130) ? 32'h0 : my_rom[A2];
    end

    initial begin
        integer i;
        for (i = 0; i < 2048; i = i + 1) my_rom[i] = 32'h0;

        my_rom[0] = 32'h802b7;
        my_rom[1] = 32'h2a023;
        my_rom[2] = 32'h40437;
        my_rom[3] = 32'h82ab7;
        my_rom[4] = 32'hfff00c13;
        my_rom[5] = 32'hc93;
        my_rom[6] = 32'h1f400fef;
        my_rom[7] = 32'hd13;
        my_rom[8] = 32'hd93;
        my_rom[9] = 32'h3e00513;
        my_rom[10] = 32'h220000ef;
        my_rom[11] = 32'h2000513;
        my_rom[12] = 32'h218000ef;
        my_rom[13] = 32'h493;
        my_rom[14] = 32'h913;
        my_rom[15] = 32'h80337;
        my_rom[16] = 32'h2430313;
        my_rom[17] = 32'h32383;
        my_rom[18] = 32'h13f393;
        my_rom[19] = 32'hfe038ce3;
        my_rom[20] = 32'h80337;
        my_rom[21] = 32'h2030313;
        my_rom[22] = 32'h34503;
        my_rom[23] = 32'h6100293;
        my_rom[24] = 32'h554863;
        my_rom[25] = 32'h7a00293;
        my_rom[26] = 32'ha2c463;
        my_rom[27] = 32'hfe050513;
        my_rom[28] = 32'h1d8000ef;
        my_rom[29] = 32'hd00293;
        my_rom[30] = 32'h4550e63;
        my_rom[31] = 32'ha00293;
        my_rom[32] = 32'h4550a63;
        my_rom[33] = 32'h3a00293;
        my_rom[34] = 32'ha550063;
        my_rom[35] = 32'h5200293;
        my_rom[36] = 32'h14550c63;
        my_rom[37] = 32'h3000293;
        my_rom[38] = 32'hfa5542e3;
        my_rom[39] = 32'h3900293;
        my_rom[40] = 32'ha2c663;
        my_rom[41] = 32'hfd050293;
        my_rom[42] = 32'h180006f;
        my_rom[43] = 32'h4100293;
        my_rom[44] = 32'hf85546e3;
        my_rom[45] = 32'h4600293;
        my_rom[46] = 32'hf8a2c2e3;
        my_rom[47] = 32'hfc950293;
        my_rom[48] = 32'hf2f293;
        my_rom[49] = 32'h449493;
        my_rom[50] = 32'h54e4b3;
        my_rom[51] = 32'h100913;
        my_rom[52] = 32'hf6dff06f;
        my_rom[53] = 32'h90463;
        my_rom[54] = 32'h48413;
        my_rom[55] = 32'h3a00513;
        my_rom[56] = 32'h168000ef;
        my_rom[57] = 32'h2000513;
        my_rom[58] = 32'h160000ef;
        my_rom[59] = 32'h42983;
        my_rom[60] = 32'h1c00a13;
        my_rom[61] = 32'h149d2b3;
        my_rom[62] = 32'hf2f293;
        my_rom[63] = 32'ha00313;
        my_rom[64] = 32'h62c663;
        my_rom[65] = 32'h3728293;
        my_rom[66] = 32'h80006f;
        my_rom[67] = 32'h3028293;
        my_rom[68] = 32'h28513;
        my_rom[69] = 32'h134000ef;
        my_rom[70] = 32'hffca0a13;
        my_rom[71] = 32'hfc0a5ce3;
        my_rom[72] = 32'h440413;
        my_rom[73] = 32'he00006f;
        my_rom[74] = 32'h90463;
        my_rom[75] = 32'h48413;
        my_rom[76] = 32'h493;
        my_rom[77] = 32'h913;
        my_rom[78] = 32'h80337;
        my_rom[79] = 32'h2430313;
        my_rom[80] = 32'h32383;
        my_rom[81] = 32'h13f393;
        my_rom[82] = 32'hfe038ce3;
        my_rom[83] = 32'h80337;
        my_rom[84] = 32'h2030313;
        my_rom[85] = 32'h34503;
        my_rom[86] = 32'h6100293;
        my_rom[87] = 32'h554863;
        my_rom[88] = 32'h7a00293;
        my_rom[89] = 32'ha2c463;
        my_rom[90] = 32'hfe050513;
        my_rom[91] = 32'hdc000ef;
        my_rom[92] = 32'h2000293;
        my_rom[93] = 32'h4550a63;
        my_rom[94] = 32'hd00293;
        my_rom[95] = 32'h4550e63;
        my_rom[96] = 32'ha00293;
        my_rom[97] = 32'h4550a63;
        my_rom[98] = 32'h3000293;
        my_rom[99] = 32'hfa5546e3;
        my_rom[100] = 32'h3900293;
        my_rom[101] = 32'ha2c663;
        my_rom[102] = 32'hfd050293;
        my_rom[103] = 32'h180006f;
        my_rom[104] = 32'h4100293;
        my_rom[105] = 32'hf8554ae3;
        my_rom[106] = 32'h4600293;
        my_rom[107] = 32'hf8a2c6e3;
        my_rom[108] = 32'hfc950293;
        my_rom[109] = 32'hf2f293;
        my_rom[110] = 32'h449493;
        my_rom[111] = 32'h54e4b3;
        my_rom[112] = 32'h100913;
        my_rom[113] = 32'hf75ff06f;
        my_rom[114] = 32'hf60908e3;
        my_rom[115] = 32'h942023;
        my_rom[116] = 32'h440413;
        my_rom[117] = 32'hf5dff06f;
        my_rom[118] = 32'h2090663;
        my_rom[119] = 32'h942023;
        my_rom[120] = 32'h440413;
        my_rom[121] = 32'h200006f;
        my_rom[122] = 32'h90463;
        my_rom[123] = 32'h48413;
        my_rom[124] = 32'hd13;
        my_rom[125] = 32'hd93;
        my_rom[126] = 32'h1400fef;
        my_rom[127] = 32'h93;
        my_rom[128] = 32'h40067;
        my_rom[129] = 32'h120000ef;
        my_rom[130] = 32'he1dff06f;
        my_rom[131] = 32'ha8293;
        my_rom[132] = 32'h1337;
        my_rom[133] = 32'hfa030313;
        my_rom[134] = 32'h182a023;
        my_rom[135] = 32'h182a223;
        my_rom[136] = 32'h182a423;
        my_rom[137] = 32'h182a623;
        my_rom[138] = 32'h182a823;
        my_rom[139] = 32'h182aa23;
        my_rom[140] = 32'h182ac23;
        my_rom[141] = 32'h182ae23;
        my_rom[142] = 32'h2028293;
        my_rom[143] = 32'hfff30313;
        my_rom[144] = 32'hfc031ce3;
        my_rom[145] = 32'hf8067;
        my_rom[146] = 32'ha00293;
        my_rom[147] = 32'hc550c63;
        my_rom[148] = 32'hd00293;
        my_rom[149] = 32'hc550863;
        my_rom[150] = 32'h2000293;
        my_rom[151] = 32'ha550e63;
        my_rom[152] = 32'he000fef;
        my_rom[153] = 32'h2d1293;
        my_rom[154] = 32'h1a282b3;
        my_rom[155] = 32'h2d9313;
        my_rom[156] = 32'h1d9393;
        my_rom[157] = 32'h730333;
        my_rom[158] = 32'h831e93;
        my_rom[159] = 32'h631f13;
        my_rom[160] = 32'h1ee8eb3;
        my_rom[161] = 32'h5e8eb3;
        my_rom[162] = 32'h1e9e93;
        my_rom[163] = 32'h15e8eb3;
        my_rom[164] = 32'h1300893;
        my_rom[165] = 32'h393;
        my_rom[166] = 32'h115df33;
        my_rom[167] = 32'h1f7f13;
        my_rom[168] = 32'hf0663;
        my_rom[169] = 32'h19e9023;
        my_rom[170] = 32'h80006f;
        my_rom[171] = 32'h18e9023;
        my_rom[172] = 32'hfff88893;
        my_rom[173] = 32'h115df33;
        my_rom[174] = 32'h1f7f13;
        my_rom[175] = 32'hf0663;
        my_rom[176] = 32'h19e9123;
        my_rom[177] = 32'h80006f;
        my_rom[178] = 32'h18e9123;
        my_rom[179] = 32'hfff88893;
        my_rom[180] = 32'h115df33;
        my_rom[181] = 32'h1f7f13;
        my_rom[182] = 32'hf0663;
        my_rom[183] = 32'h19e9223;
        my_rom[184] = 32'h80006f;
        my_rom[185] = 32'h18e9223;
        my_rom[186] = 32'hfff88893;
        my_rom[187] = 32'h115df33;
        my_rom[188] = 32'h1f7f13;
        my_rom[189] = 32'hf0663;
        my_rom[190] = 32'h19e9323;
        my_rom[191] = 32'h80006f;
        my_rom[192] = 32'h18e9323;
        my_rom[193] = 32'hfff88893;
        my_rom[194] = 32'h280e8e93;
        my_rom[195] = 32'h138393;
        my_rom[196] = 32'h500f13;
        my_rom[197] = 32'hf9e3c2e3;
        my_rom[198] = 32'h1d0d13;
        my_rom[199] = 32'h4000293;
        my_rom[200] = 32'h5d4e63;
        my_rom[201] = 32'hd13;
        my_rom[202] = 32'h1d8d93;
        my_rom[203] = 32'h2100293;
        my_rom[204] = 32'h5dc663;
        my_rom[205] = 32'hd93;
        my_rom[206] = 32'hed5fffef;
        my_rom[207] = 32'h8067;
        my_rom[208] = 32'h3000293;
        my_rom[209] = 32'h8550e63;
        my_rom[210] = 32'h3100293;
        my_rom[211] = 32'ha550063;
        my_rom[212] = 32'h3200293;
        my_rom[213] = 32'ha550263;
        my_rom[214] = 32'h3300293;
        my_rom[215] = 32'ha550463;
        my_rom[216] = 32'h3400293;
        my_rom[217] = 32'ha550663;
        my_rom[218] = 32'h3500293;
        my_rom[219] = 32'ha550863;
        my_rom[220] = 32'h3600293;
        my_rom[221] = 32'ha550a63;
        my_rom[222] = 32'h3700293;
        my_rom[223] = 32'ha550c63;
        my_rom[224] = 32'h3800293;
        my_rom[225] = 32'ha550e63;
        my_rom[226] = 32'h3900293;
        my_rom[227] = 32'hc550063;
        my_rom[228] = 32'h4100293;
        my_rom[229] = 32'hc550263;
        my_rom[230] = 32'h4200293;
        my_rom[231] = 32'hc550463;
        my_rom[232] = 32'h4300293;
        my_rom[233] = 32'hc550663;
        my_rom[234] = 32'h4400293;
        my_rom[235] = 32'hc550863;
        my_rom[236] = 32'h4500293;
        my_rom[237] = 32'hc550a63;
        my_rom[238] = 32'h4600293;
        my_rom[239] = 32'hc550c63;
        my_rom[240] = 32'h5200293;
        my_rom[241] = 32'hc550e63;
        my_rom[242] = 32'h3a00293;
        my_rom[243] = 32'he550063;
        my_rom[244] = 32'h3e00293;
        my_rom[245] = 32'he550263;
        my_rom[246] = 32'h593;
        my_rom[247] = 32'hf8067;
        my_rom[248] = 32'h6a5b7;
        my_rom[249] = 32'h99658593;
        my_rom[250] = 32'hf8067;
        my_rom[251] = 32'h4c5b7;
        my_rom[252] = 32'h44e58593;
        my_rom[253] = 32'hf8067;
        my_rom[254] = 32'h695b7;
        my_rom[255] = 32'h24f58593;
        my_rom[256] = 32'hf8067;
        my_rom[257] = 32'hf15b7;
        my_rom[258] = 32'h61f58593;
        my_rom[259] = 32'hf8067;
        my_rom[260] = 32'h9a5b7;
        my_rom[261] = 32'hf1158593;
        my_rom[262] = 32'hf8067;
        my_rom[263] = 32'hf95b7;
        my_rom[264] = 32'he1e58593;
        my_rom[265] = 32'hf8067;
        my_rom[266] = 32'h795b7;
        my_rom[267] = 32'he9658593;
        my_rom[268] = 32'hf8067;
        my_rom[269] = 32'hf15b7;
        my_rom[270] = 32'h24458593;
        my_rom[271] = 32'hf8067;
        my_rom[272] = 32'h695b7;
        my_rom[273] = 32'h69658593;
        my_rom[274] = 32'hf8067;
        my_rom[275] = 32'h695b7;
        my_rom[276] = 32'h71658593;
        my_rom[277] = 32'hf8067;
        my_rom[278] = 32'h6a5b7;
        my_rom[279] = 32'hf9958593;
        my_rom[280] = 32'hf8067;
        my_rom[281] = 32'hea5b7;
        my_rom[282] = 32'he9e58593;
        my_rom[283] = 32'hf8067;
        my_rom[284] = 32'h6a5b7;
        my_rom[285] = 32'h89658593;
        my_rom[286] = 32'hf8067;
        my_rom[287] = 32'hea5b7;
        my_rom[288] = 32'h99e58593;
        my_rom[289] = 32'hf8067;
        my_rom[290] = 32'hf95b7;
        my_rom[291] = 32'he8f58593;
        my_rom[292] = 32'hf8067;
        my_rom[293] = 32'hf95b7;
        my_rom[294] = 32'he8858593;
        my_rom[295] = 32'hf8067;
        my_rom[296] = 32'hea5b7;
        my_rom[297] = 32'hea958593;
        my_rom[298] = 32'hf8067;
        my_rom[299] = 32'h25b7;
        my_rom[300] = 32'h2058593;
        my_rom[301] = 32'hf8067;
        my_rom[302] = 32'h845b7;
        my_rom[303] = 32'h24858593;
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
        if (~sel)
            D = 13'hz;
        else if (A > 5'h1b)
            D = 13'h0;
        else
            D = my_rom[A];
    end

    initial begin
        my_rom[0] = 13'h1026;
        my_rom[1] = 13'h0;
        my_rom[2] = 13'h0;
        my_rom[3] = 13'h0;
        my_rom[4] = 13'h22;
        my_rom[5] = 13'h312;
        my_rom[6] = 13'h0;
        my_rom[7] = 13'h0;
        my_rom[8] = 13'h1121;
        my_rom[9] = 13'h0;
        my_rom[10] = 13'h0;
        my_rom[11] = 13'h0;
        my_rom[12] = 13'h802;
        my_rom[13] = 13'h30e;
        my_rom[14] = 13'h0;
        my_rom[15] = 13'h0;
        my_rom[16] = 13'h0;
        my_rom[17] = 13'h0;
        my_rom[18] = 13'h0;
        my_rom[19] = 13'h0;
        my_rom[20] = 13'h0;
        my_rom[21] = 13'h0;
        my_rom[22] = 13'h0;
        my_rom[23] = 13'h0;
        my_rom[24] = 13'h1ac0;
        my_rom[25] = 13'h10aa;
        my_rom[26] = 13'h0;
        my_rom[27] = 13'h44a;
    end
endmodule

module DIG_ROM_64X5_ALUOP (
    input [5:0] A,
    input sel,
    output reg [4:0] D
);
    reg [4:0] my_rom [0:61];

    always @ (*) begin
        if (~sel)
            D = 5'hz;
        else if (A > 6'h3d)
            D = 5'h0;
        else
            D = my_rom[A];
    end

    initial begin
        my_rom[0] = 5'h0;
        my_rom[1] = 5'h0;
        my_rom[2] = 5'h0;
        my_rom[3] = 5'h0;
        my_rom[4] = 5'h7;
        my_rom[5] = 5'h0;
        my_rom[6] = 5'h0;
        my_rom[7] = 5'h0;
        my_rom[8] = 5'h6;
        my_rom[9] = 5'h6;
        my_rom[10] = 5'h6;
        my_rom[11] = 5'h6;
        my_rom[12] = 5'h5;
        my_rom[13] = 5'h5;
        my_rom[14] = 5'h5;
        my_rom[15] = 5'h5;
        my_rom[16] = 5'h4;
        my_rom[17] = 5'h4;
        my_rom[18] = 5'h4;
        my_rom[19] = 5'h4;
        my_rom[20] = 5'h8;
        my_rom[21] = 5'h0;
        my_rom[22] = 5'h9;
        my_rom[23] = 5'h0;
        my_rom[24] = 5'h3;
        my_rom[25] = 5'h3;
        my_rom[26] = 5'h3;
        my_rom[27] = 5'h3;
        my_rom[28] = 5'h2;
        my_rom[29] = 5'h2;
        my_rom[30] = 5'h2;
        my_rom[31] = 5'h2;
        my_rom[32] = 5'h0;
        my_rom[33] = 5'ha;
        my_rom[34] = 5'h1;
        my_rom[35] = 5'h0;
        my_rom[36] = 5'h7;
        my_rom[37] = 5'hb;
        my_rom[38] = 5'h0;
        my_rom[39] = 5'h0;
        my_rom[40] = 5'h6;
        my_rom[41] = 5'hd;
        my_rom[42] = 5'h0;
        my_rom[43] = 5'h0;
        my_rom[44] = 5'h5;
        my_rom[45] = 5'hc;
        my_rom[46] = 5'h0;
        my_rom[47] = 5'h0;
        my_rom[48] = 5'h4;
        my_rom[49] = 5'he;
        my_rom[50] = 5'h0;
        my_rom[51] = 5'h0;
        my_rom[52] = 5'h8;
        my_rom[53] = 5'hf;
        my_rom[54] = 5'h9;
        my_rom[55] = 5'h0;
        my_rom[56] = 5'h3;
        my_rom[57] = 5'h10;
        my_rom[58] = 5'h0;
        my_rom[59] = 5'h0;
        my_rom[60] = 5'h2;
        my_rom[61] = 5'h11;
    end
endmodule

module InstructionSplicer (
  input [2:0] ImmSel, 
  input [31:0] INSin,
  output [6:0] funct7,
  output [2:0] funct3,
  output [6:0] opcode,
  output [4:0] rs1,
  output [4:0] rs2,
  output [4:0] rd,
  output reg [31:0] Imm
);
  assign opcode = INSin[6:0];
  assign rd     = INSin[11:7];
  assign funct3 = INSin[14:12];
  assign rs1    = INSin[19:15];
  assign rs2    = INSin[24:20];
  assign funct7 = INSin[31:25];

  always @(*) begin
      case (ImmSel)
          3'h0: Imm = { {20{INSin[31]}}, INSin[31:20] };                                     
          3'h1: Imm = { {20{INSin[31]}}, INSin[31:25], INSin[11:7] };                        
          3'h2: Imm = { {20{INSin[31]}}, INSin[7], INSin[30:25], INSin[11:8], 1'b0 };        
          3'h3: Imm = { INSin[31:12], 12'b0 };                                               
          3'h4: Imm = { {12{INSin[31]}}, INSin[19:12], INSin[20], INSin[30:21], 1'b0 };      
          default: Imm = 32'b0;
      endcase
  end
endmodule

module ControlLogic (
  input [6:0] funct7,
  input [2:0] funct3,
  input [6:0] opcode,
  output [2:0] InsTypeSel, 
  output [1:0] BrInsSel, 
  output [1:0] PCInSel,
  output DSigned,
  output DHalf,
  output DByte,
  output reg [4:0] ALUOpSel,
  output ALUInSel,
  output [2:0] RegInSel,
  output RegWe,
  output MemWe
);
  assign BrInsSel = {funct3[2], funct3[0]};
  assign DSigned  = ~funct3[2];
  assign DByte    = (funct3[1:0] == 2'h0);
  assign DHalf    = (funct3[1:0] == 2'h1);

  // RESTORED: Fast C++ Array Lookup
  wire [12:0] ins_rom_data;
  DIG_ROM_32X13_INSLogic rom0 (.A(opcode[6:2]), .sel(1'b1), .D(ins_rom_data));

  assign MemWe      = ins_rom_data[0];
  assign RegWe      = ins_rom_data[1];
  assign RegInSel   = ins_rom_data[4:2];
  assign ALUInSel   = ins_rom_data[5];
  assign PCInSel    = ins_rom_data[7:6];
  assign InsTypeSel = ins_rom_data[10:8];

  wire [1:0] s2 = ins_rom_data[12:11];
  wire s7 = (s2 == 2'h1);

  // RESTORED: Fast C++ Array Lookup
  wire [5:0] alu_rom_addr = {s7, funct3, funct7[5], funct7[0]};
  wire [4:0] alu_rom_data;
  DIG_ROM_64X5_ALUOP rom1 (.A(alu_rom_addr), .sel(1'b1), .D(alu_rom_data));

  wire [4:0] s4 = funct3[1] ? 5'b101 : 5'b110;

  always @(*) begin
      case (s2)
          2'h0: ALUOpSel = alu_rom_data;
          2'h1: ALUOpSel = alu_rom_data;
          2'h2: ALUOpSel = 5'b0;
          2'h3: ALUOpSel = s4;
      endcase
  end
endmodule

module ALU (
  input [4:0] OPSELECT,
  input [31:0] B,
  input [31:0] A,
  input clock,
  output reg [31:0] O,
  output [1:0] Flags
);
  wire [31:0] sub_res = A - B;
  wire lt_u = (A < B);
  wire lt_s = ($signed(A) < $signed(B));

  wire [63:0] mul_uu = {32'b0, A} * {32'b0, B};
  wire [63:0] mul_ss = $signed(A) * $signed(B);
  wire [63:0] mul_su = $signed(A) * $signed({1'b0, B});

  wire is_div_overflow = (A == 32'h80000000 && B == 32'hFFFFFFFF);

  always @(*) begin
    case (OPSELECT)
      5'b00000: O = A + B;
      5'b00001: O = sub_res;
      5'b00010: O = A & B;
      5'b00011: O = A | B;
      5'b00100: O = A ^ B;
      5'b00101: O = {31'b0, lt_u};
      5'b00110: O = {31'b0, lt_s};
      5'b00111: O = A << B[4:0];
      5'b01000: O = A >> B[4:0];
      5'b01001: O = $unsigned($signed(A) >>> B[4:0]);
      5'b01010: O = mul_uu[31:0];      
      5'b01011: O = mul_ss[63:32];     
      5'b01100: O = mul_uu[63:32];     
      5'b01101: O = mul_su[63:32];     
      5'b01110: O = (B == 0) ? 32'hFFFFFFFF : (is_div_overflow ? 32'h80000000 : $unsigned($signed(A) / $signed(B))); 
      5'b01111: O = (B == 0) ? 32'hFFFFFFFF : (A / B);                                                                
      5'b10000: O = (B == 0) ? A            : (is_div_overflow ? 32'h0 : $unsigned($signed(A) % $signed(B)));         
      5'b10001: O = (B == 0) ? A            : (A % B);                                                                
      default:  O = 32'b0;
    endcase
  end

  assign Flags[0] = (OPSELECT == 5'b00110) ? lt_s : lt_u;
  assign Flags[1] = (A == B);
endmodule

module Registers (
  input Clock,
  input [31:0] Din,
  input We,
  input [4:0] rs1,
  input [4:0] rs2,
  input [4:0] rd,
  output [31:0] rs1O,
  output [31:0] rs2O
);
  reg [31:0] regs [0:31];
  
  always @(posedge Clock) begin
      // Stall network removed.
      if (We && rd != 5'b0) begin
          regs[rd] <= Din;
      end
  end
  
  assign rs1O = (rs1 == 5'b0) ? 32'b0 : regs[rs1];
  assign rs2O = (rs2 == 5'b0) ? 32'b0 : regs[rs2];
endmodule

module PcInSelector (
  input [1:0] BranchIns, 
  input [1:0] PcInSel,
  input [1:0] Flags, 
  input [31:0] ALU,
  input [31:0] AdAdd,
  input [31:0] PC_plus_4,
  output reg [31:0] PC
);
  reg branch_taken;
  always @(*) begin
      case (BranchIns)
          2'b00: branch_taken = Flags[1];  
          2'b01: branch_taken = ~Flags[1]; 
          2'b10: branch_taken = Flags[0];  
          2'b11: branch_taken = ~Flags[0]; 
      endcase
  end

  always @(*) begin
      case (PcInSel)
          2'h0: PC = PC_plus_4;
          2'h1: PC = AdAdd;
          2'h2: PC = ALU;
          2'h3: PC = branch_taken ? AdAdd : PC_plus_4;
      endcase
  end
endmodule

module ProgramCounter (
  input Clock,
  input [31:0] Din,
  output reg [31:0] Dout,
  output [31:0] \PC+4 
);
  initial Dout = 32'b0;

  always @(posedge Clock) begin
      // Stall network removed.
      Dout <= {Din[31:1], 1'b0};
  end

  assign \PC+4 = Dout + 32'h4;
endmodule

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
  reg [31:0] memory [0:65535];
  wire [3:0] we_mask = We ? ByteSelect[3:0] : 4'b0000;

  always @(posedge Clock) begin
      if (we_mask[0]) memory[AddressIn][7:0]   <= Din[7:0];
      if (we_mask[1]) memory[AddressIn][15:8]  <= Din[15:8];
      if (we_mask[2]) memory[AddressIn][23:16] <= Din[23:16];
      if (we_mask[3]) memory[AddressIn][31:24] <= Din[31:24];
  end

  always @(*) begin
      Dout = memory[AddressIn];
      INSout = memory[INSAddressIn];
  end
endmodule

module MemoryMapperExp (
  input Clock,
  input [31:0] Din,
  input [31:0] Ain,
  input [31:0] INSAin,
  input [5:0] ByteSelect,
  input We,
  input [2:0] RegInsel,
  input [31:0] DrIO,
  output [31:0] INSout,
  output [31:0] Dout,
  output [31:0] AddIO,
  output [31:0] DwIO,
  output [3:0] WeIO,
  output ReIO,
  output CLKIO
);
  wire isbyte = ByteSelect[4];
  wire half   = ByteSelect[5];

  assign DwIO = isbyte ? {4{Din[7:0]}} :
                half   ? {2{Din[15:0]}} : Din;

  // Latch removed; pure combinatorial tie since Stall is gone
  assign CLKIO = Clock;

  // AddressSpace module purely inlined
  wire cs_rom = (Ain[31:18] == 14'h0);
  wire cs_ram = (Ain[31:18] == 14'h1);
  wire cs_io  = ~(cs_rom | cs_ram);
  wire ins_cs_ram = (INSAin[31:18] == 14'h1);

  assign WeIO = (We & cs_io) ? ByteSelect[3:0] : 4'h0;
  assign ReIO = cs_io & (RegInsel == 3'h1);
  assign AddIO = Ain;

  // Employs our new consolidated Dual Port ROM
  wire [31:0] rom_data_out, rom_ins_out;
  DualPortROM shared_rom (
      .A1(INSAin[12:2]),
      .A2(Ain[12:2]),
      .D1(rom_ins_out),
      .D2(rom_data_out)
  );

  wire [31:0] ram_data_out, ram_ins_out;
  RAM_256KB ram (
      .INSAddressIn(INSAin[17:2]),
      .ByteSelect(ByteSelect),
      .AddressIn(Ain[17:2]),
      .Din(DwIO),
      .We(We & cs_ram),
      .Clock(CLKIO),
      .Dout(ram_data_out),
      .INSout(ram_ins_out)
  );

  assign Dout = cs_io ? DrIO : (cs_ram ? ram_data_out : rom_data_out);
  assign INSout = ins_cs_ram ? ram_ins_out : rom_ins_out;
endmodule

module DataController (
  input [31:0] AddressIn,
  input [31:0] DinMMU,
  input \Signed ,
  input half,
  input isbyte,
  output [31:0] AddressOut,
  output reg [31:0] DoCPU,
  output reg [5:0] ByteSelect
);
  assign AddressOut = AddressIn;
  wire [1:0] align = AddressIn[1:0];

  always @(*) begin
      ByteSelect[5] = half;
      ByteSelect[4] = isbyte;
      if (isbyte) begin
          ByteSelect[3:0] = 4'b0001 << align;
      end else if (half) begin
          ByteSelect[3:0] = 4'b0011 << align; 
      end else begin
          ByteSelect[3:0] = 4'b1111;
      end

      if (isbyte) begin
          case (align)
              2'b00: DoCPU = \Signed ? { {24{DinMMU[7]}}, DinMMU[7:0] }   : { 24'b0, DinMMU[7:0] };
              2'b01: DoCPU = \Signed ? { {24{DinMMU[15]}}, DinMMU[15:8] }  : { 24'b0, DinMMU[15:8] };
              2'b10: DoCPU = \Signed ? { {24{DinMMU[23]}}, DinMMU[23:16] } : { 24'b0, DinMMU[23:16] };
              2'b11: DoCPU = \Signed ? { {24{DinMMU[31]}}, DinMMU[31:24] } : { 24'b0, DinMMU[31:24] };
          endcase
      end else if (half) begin
          case (align)
              2'b00: DoCPU = \Signed ? { {16{DinMMU[15]}}, DinMMU[15:0] }  : { 16'b0, DinMMU[15:0] };
              2'b01: DoCPU = \Signed ? { {16{DinMMU[23]}}, DinMMU[23:8] }  : { 16'b0, DinMMU[23:8] };
              2'b10: DoCPU = \Signed ? { {16{DinMMU[31]}}, DinMMU[31:16] } : { 16'b0, DinMMU[31:16] };
              2'b11: DoCPU = 32'b0; 
          endcase
      end else begin
          DoCPU = DinMMU;
      end
  end
endmodule

module main_cpu (
  input CLK,
  input [31:0] DrIO,
  output [31:0] AddIO,
  output [31:0] DwIO,
  output [3:0] WeIO,
  output ReIO,
  output CLKIO
);
  wire [4:0] s0;
  wire [31:0] s1;
  wire [31:0] s2;
  wire [31:0] s3;
  wire [1:0] s4;
  
  // Stall wire fully removed!
  
  reg [31:0] s6; 
  wire s7;
  wire [4:0] s8;
  wire [4:0] s9;
  wire [4:0] s10;
  wire [31:0] s11;
  wire [31:0] s12;
  wire s13;
  wire s14;
  wire s15;
  wire [31:0] s16;
  wire [31:0] s17;
  wire [5:0] s18;
  wire [2:0] s19;
  wire [31:0] s20;
  wire [31:0] s21;
  wire [31:0] s22;
  wire [31:0] s23;
  wire [31:0] s24;
  wire s25;
  wire [2:0] s26;
  wire [31:0] s27;
  wire [6:0] s28;
  wire [2:0] s29;
  wire [6:0] s30;
  wire [1:0] s31;
  wire [1:0] s32;
  wire s33;

  MemoryMapperExp MemoryMapperExp_i0 (
    .Clock( CLK ),
    .Din( s11 ),
    .Ain( s16 ),
    .INSAin( s24 ),
    .ByteSelect( s18 ),
    .We( s33 ),
    .RegInsel( s19 ),
    .DrIO( DrIO ),
    .INSout( s27 ),
    .Dout( s12 ),
    .AddIO( AddIO ),
    .DwIO( DwIO ),
    .WeIO( WeIO ),
    .ReIO( ReIO ),
    .CLKIO( CLKIO )
  );
  
  DataController DataController_i1 (
    .AddressIn( s3 ),
    .DinMMU( s12 ),
    .\Signed ( s13 ),
    .half( s14 ),
    .isbyte( s15 ),
    .AddressOut( s16 ),
    .DoCPU( s17 ),
    .ByteSelect( s18 )
  );
  
  InstructionSplicer InstructionSplicer_i2 (
    .ImmSel( s26 ),
    .INSin( s27 ),
    .funct7( s28 ),
    .funct3( s29 ),
    .opcode( s30 ),
    .rs1( s8 ),
    .rs2( s9 ),
    .rd( s10 ),
    .Imm( s21 )
  );
  
  ControlLogic ControlLogic_i3 (
    .funct7( s28 ),
    .funct3( s29 ),
    .opcode( s30 ),
    .InsTypeSel( s26 ),
    .BrInsSel( s31 ),
    .PCInSel( s32 ),
    .DSigned( s13 ),
    .DHalf( s14 ),
    .DByte( s15 ),
    .ALUOpSel( s0 ),
    .ALUInSel( s25 ),
    .RegInSel( s19 ),
    .RegWe( s7 ),
    .MemWe( s33 )
  );
  
  ALU ALU_i4 (
    .OPSELECT( s0 ),
    .B( s1 ),
    .A( s2 ),
    .clock( CLK ),
    .O( s3 ),
    .Flags( s4 )
  );
  
  Registers Registers_i5 (
    .Clock( CLK ),
    .Din( s6 ),
    .We( s7 ),
    .rs1( s8 ),
    .rs2( s9 ),
    .rd( s10 ),
    .rs1O( s2 ),
    .rs2O( s11 )
  );
  
  always @(*) begin
      case (s19)
          3'h0: s6 = s3;  
          3'h1: s6 = s17; 
          3'h2: s6 = s20; 
          3'h3: s6 = s21; 
          3'h4: s6 = s22; 
          default: s6 = 32'b0;
      endcase
  end

  assign s22 = s21 + s24;
  assign s1 = s25 ? s21 : s11;

  PcInSelector PcInSelector_i9 (
    .BranchIns( s31 ),
    .PcInSel( s32 ),
    .Flags( s4 ),
    .ALU( s3 ),
    .AdAdd( s22 ),
    .PC_plus_4( s20 ),
    .PC( s23 )
  );
  
  ProgramCounter ProgramCounter_i10 (
    .Clock( CLK ),
    .Din( s23 ),
    .Dout( s24 ),
    .\PC+4 ( s20 )
  );
endmodule