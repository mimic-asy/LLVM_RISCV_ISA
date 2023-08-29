//===----------------------------------------------------------------------===//
//  ターゲット記述のルートとなるファイル
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"


//===----------------------------------------------------------------------===//
// Target-dependent interfaces
//===----------------------------------------------------------------------===//

def RV64 : HwMode<"+64bit">; // 64-bit mode
def RV32 : HwMode<"-64bit">; // 32-bit mode

include "MYRISCVXRegisterInfo.td" // レジスタ定義 td fire.
include "MYRISCVXSchedule.td" //スケジューリング定義
include "MYRISCVXInstrInfo.td" // 命令定義 td fire.

def  MYRISCVXInstrInfo : InstrInfo;

//MYRISCVX Target Architectureを作成する
def MYRISCVX:Target{

    let InstructionSet = MYRISCVXInstrInfo;
}

//<属性の名前、属性を格納する変数名、属性に設定される値、属性の説明>
def FeatureRV64 : SubtargetFeature<"64bit", "HasRV64", "true", "RV64_support">;

//CPUモデル...cpurv-32/cpurv-64
//cpurv-64のときはFeatureRV64を有効になる
def : ProcessorModel<"cpu-rv32", NoSchedModel, []>;
def : ProcessorModel<"cpu -rv64", NoSchedModel, [FeatureRV64]>;

