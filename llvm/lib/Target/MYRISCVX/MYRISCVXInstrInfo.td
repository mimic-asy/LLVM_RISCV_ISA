
//--------------------------//
//ラッパクラスを使って命令を定義//
//-------------------------//

// 命令フォーマットをincludeする
include "MYRISCVXInstrFormats.td"



//===----------------------------------------------------------------------===//
// Instructions specific format
//===----------------------------------------------------------------------===//

//2レジスタオペランドを扱う算術論理演算命令
//◆(outs RC:$rd) : RCレジスタクラスの一員として$rdを定義する。これは出力ノードである。
//◆(ins RC:$rs1, RC:$rs2) : レジスタクラスの一員として、$rs1,$rs2レジスタを定義する。これらは入力ノードである
//◆この命令は、$rs1レジスタと$rs2レジスタに対してOpNodeに基く演算を行い、結果を$rdレジスタに格納する命令である。
class ArithLogicR<bits<7> opcode, bits<3> funct3, bits<7>funct7,
                  string instr_asm, SDNode OpNode,
                  RegisterClass RC> :
  MYRISCVX_R<opcode, funct3, funct7, (outs RC:$rd), (ins RC:$rs1, RC:$rs2),
  !strconcat(instr_asm, "\t$rd, $rs1, $rs2"),
  [(set RC:$rd, (OpNode RC:$rs1, RC:$rs2))], IIAlu> {
    let isReMaterializable = 1;
}

//1レジスタオペランドと即値オペランドを扱う算術論理演算命令
  //  //◆この命令は、$rs1レジスタと即値$imm12に対してOpNodeに基く演算を行い、結果を$rdレジスタに格納する命令である
class ArithLogicI<bits<7> opcode, bits<3> funct3,
                  string instr_asm, SDNode OpNode,
                  Operand Od, RegisterClass RC> :
  MYRISCVX_I<opcode, funct3, (outs RC:$rd), (ins RC:$rs1, Od:$simm12),
  !strconcat(instr_asm, "\t$rd, $rs1, $simm12"),
  [(set RC:$rd, (OpNode RC:$rs1, Od:$simm12))], IIAlu> {
    let isReMaterializable = 1;
}

//1つの即値オペランドを持つ算術論理演算命令
class ArithLogicU<bits<7> opcode,
                  string instr_asm, RegisterClass RC, Operand Od> :
  MYRISCVX_U<opcode, (outs RC:$rd), (ins Od:$imm20),
    !strconcat(instr_asm, "\t$rd, $imm20"), [], IIAlu> {
      let isReMaterializable = 1;
}


//===----------------------------------------------------------------------===//
// MYRISCVX Instructions
//===----------------------------------------------------------------------===//

def ADDI : ArithLogicI<0b0010011, 0b000, "addi", add, imm12, GPR>

def LUI : ArithLogicU<0b0110111, "lui", GPR, imm20>;

def ADD :  ArithLogicR<0b0110011, 0b000, 0b0000000, "add", add, GPR>;
