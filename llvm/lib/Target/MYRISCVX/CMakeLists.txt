add_llvm_component_group(MYRISCVX)
set(LLVM_TARGET_DEFINITIONS MYRISCVX.td)
# MYRISCVXGenRegisterInfo.incを生成する
# 以下ヘッダファイル(.inc)はMYRISCVXRegisterInfo.tdから生成される
# MYRISCVXRegisterInfo.inc :　MYRISCVXRegisterInfo.tdで記述したレジスタの情報
tablegen(LLVM MYRISCVXGenRegisterInfo.inc -gen-register-info)
# MYRISCVXGenInstrInfo.inc : MYRISCVXInstrinfo.tdで記述した命令定義の情報
tablegen(LLVM MYRISCVXGenInstrInfo.inc -gen-instr-info)
# サブターゲットの情報
tablegen(LLVM MYRISCVXGenSubtargetInfo.inc -gen-subtarget)
# 疑似命令に関する情報
tablegen(LLVM MYRISCVXGenMCPseudoLowering.inc -gen-pseudo-lowering)

#MYRISCVCallingConv.tdからMYRISCVXGenCallingConv.incを生成
tablegen(LLVM MYRISCVXGenCallingConv.inc -gen-callingconv)
# MYRISCVXCommonTableGenを定義しなければならない
add_public_tablegen_target(MYRISCVXCommonTableGen)
# MYRISCVXCodeGen はLLVMBuild.txtのMYRISCVXCodeGenと一致しなければならない
add_llvm_target(MYRISCVXCodeGen
MYRISCVXTargetMachine.cpp
MYRISCVXSubtarget.cpp
MYRISCVXFrameLowering.cpp
MYRISCVXRegisterInfo.cpp
MYRISCVXISelLowering.cpp


)

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)