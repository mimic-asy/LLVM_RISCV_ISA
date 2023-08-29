
//--------------------------------------//
// 　　　　レジスタ周りの実装　　　　　　　　　//
//--------------------------------------//


//レジスタ割り付け時に使用される関数です。
//getCalleeSavedRegs()はCallee Savedなレジスタのリストを返します。
const MCPhysReg *
MYRISCVXRegisterInfo::getCalleeSavedRegs(
const MachineFunction *MF) const {
// MYRISCVXCallingConv.tdで定義したCSR_LP32のリストをそのまま返せば良い
return CSR_LP32_SaveList;
}


//レジスタ割付につかう　ビットマスクを返す
const unit32_t *
MYRISCVXRegisterInfo::getCallPreservedMask(
  const MachineFunction &MF,
  CallingConv::ID) const{
  return CSR_LP32_regMask;
}

//reg割付に使用しない予約済みレジスタを返す
BitVector MYRISCVXRegisterInfo::
getReservedRegs(const MachineFunction &MF) const {
  static const unit16_t ReservedCPURegs[] = {
  MYRISCVX::ZERO, MYRISCVX::RA, MYRISCVX::FP, MYRISCVX::SP,
  MYRISCVX::GP, MYRISCVX::TP
  };
  for (unsigned I = 0; I < array_lengthof(ReservedCPURegs); ++I)
    Reserved.set(ReservedCPURegs[I]);

    return Reserved;
}

void MYRISCVXRegisterInfo::
eliminateFrameIndex(MachineBasicBlock::iterator II, int SPAdj,
                    unsigned FIOperandNum, RegScavenger *RS) const {
                        //フレームインデックスを削除するための関数
                        //まだ記述しない
                    }

