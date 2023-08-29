
//===------------------------------------------===//
// ターゲットマシンをLLVMに認識させるための関数を作る　　　//
//===------------------------------------------===//

extern "C" void LLVMInitializeMYRISCVXTarget(){
    //MYRISCVXターゲットマシンの登録
    RegisterTargetMachine<MYRISCVX32TargetMachine> X(getTheMYRISCVX32Target());
    RegisterTargetMachine<MYRISCVX64TargetMachine> Y(getTheMYRISCVX64Target());
}

//MYRISCVX32ターゲットのコンストラクタ:
//MYRISCVXTargetMachineインスタンスを生成する
MYRISCVX32TargetMachine::MYRISCVX32TargetMachine(const Target &T, const Triple &TT,
                                                 StringRef CPU, StringRef FS,
                                                 const TargetOptions &Options,
                                                 Optional<Reloc::Model> RM,
                                                 Optional<CodeModel::Model> CM,
                                                 CodeGenOpt::Level OL, bool JIT)
  :MYRISCVXTargetMachine(T, TT, CPU, FS, Options, RM, CM, OL, JIT) {}

void MYRISCVX64TargetMachine::anchor(){}

MYRISCVX64TargetMachine::MYRISCVX64TargetMachine(const Target &T, const Triple &TT,
                                                 StringRef CPU, StringRef FS,
                                                 const TargetOptions &Options,
                                                 Optional<Reloc::Model> RM,
                                                 Optional<CodeModel::Model> CM,
                                                 CodeGenOpt::Level OL, bool JIT)
  :MYRISCVXTargetMachine(T, TT, CPU, FS, Options, RM, CM, OL, JIT){}


//MARISCVXTergetMachineのコンストラクタ
//  MYRISCVX32TargetMachine/MYRISCVX64TargetMachine()から呼び出される
MYRISCVXTargetMachine::MYRISCVXTargetMachine(const Target &T, const Triple &TT,
                                             StringRef CPU, StringRef FS,
                                             const TargetOptions &Options,
                                             Optional<Reloc::Model> RM,
                                             Optional<CodeModel::Model> CM,
                                             CodeGenOpt::Level OL, bool JIT)
  :LLVMTargetMachine(T, computerDataLayout(TT, CPU, Options), TT,
                     CPU, FS, Options,
                     getEffectiveRelocModel(JIT, RM),
                     /*コードモデルの設定。デフォルトではsmall(static),Medium(PIC)も指定できる*/
                     getEffectiveCodeModel(CM,CodeModel::Small),OL),
                     /*オブジェクトファイルに関する情報TLOF*/
                     TLOF(std::make_unique<MYRISCVXTargetObjectFile>()),
                     /*ABIに関する情報*/
                     ABI(MYRISCVXABIInfo::computeTargetABI(Options.MCOptions.getABIName())),
                     DefaultSubtarget(TT, CPU, /*TuneCPU*/CPU, FS, *this) {
                        initAsmInfo();
                     }


//===------------------------------------------===//
// 　　　　　computeDataLayout()を実装する　　　　　　 //
//===------------------------------------------===//

static std::string computerDataLayout(const Triple &TT, StringRef CPU,
                                      const TargetOptions &Options) {
  std::string Ret = "";
  Ret += "e";
  Ret += "-m:m";

  //ポインタのサイズを指定する。RV32の場合は32bit RV64の場合は64bit
  if (TT.isArch64Bit()){
    Ret += "-p:64:64";
  }else{
    Ret += "-p:32:32";
  }
  //8bitと16bit変数は32bitにアラインする
  //64bit変数は64bitにアラインする
  Ret += "-i8:8:32:-i16:16:32:-i64:64";
  //整数レジスタ・スタックのアライメント
  if(TT.isArch64Bit()){
    Ret += "-n64-S128";
  }else{
    Ret += "-n32-S64";
  }
  return Ret;
}

//MYRISCVXの有効なリロケーションモデルを返す
//*RMを返すので、殆どの場合にはオプションで指定したモデルがそのまま使用される
static Reloc::Model getEffectiverelocModel(bool JIT, Optional<Reloc::Model> RM) {
  if(!RM.hasValue() || JIT)
  return Reloc::Static;
  return *RM;
}


