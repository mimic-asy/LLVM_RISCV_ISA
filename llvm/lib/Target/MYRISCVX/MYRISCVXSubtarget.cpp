//--------------------------------------//
// 　　　　サブターゲットの管理を行う　　　　　//
//--------------------------------------//
//Subtargetの依存関係を解析する
MYRISCVXSubtarget &
MYRISCVXSubtarget::intializeSubtargetDependencies(StringRef CPU, StringRef TuneCPU,
                                                  StringRef FS, const TargetMachine &TM) {
  if (TargetTriple.getArch() == Triple::myriscvx32) {
    //--march=MYriscvx32が指定された場合のCPUモデルを返す
    if(CPU.empty() || CPU = "generic") {
        CPU = "cpu-rv32";
    }
  }else if (TargetTriple.getArch() == Triple::myriscvx64) {
    //--march=myriscvx64が指定された場合のCPUモデルを返す
    if(CPU.empty() || CPU == "generic") {
        CPU = "cpu-rv64";
    }
  }else{
    //--march=myriscvxxx以外を選択した場合
    errs() << "!!!Error, TargetTriple.getArch() =" << TargetTriple.getArch()
           << "CPU = " << CPU << "\n";
    exit(0);
  }

//llcのオプションから属性を解析する
ParseSubtargetFeatures(CPU, TuneCPU, FS);
//特定のCPU構成における命令スケジューリングの初期化
InstrItins = getInstrItineraryForCPU(CPU);
//ParseSubtargetFeatureの属性からXLenを変える
if(HasRV64 == true){
    XLen = MVT::i64;
}else{
    XLen = MVT::i32;
}
return *this;

}