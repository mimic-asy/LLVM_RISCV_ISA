//===----------------------------------------------------===//
// tdファイルで定義した命令をインスタンス化し、LLVMに渡すためのクラス //
//===----------------------------------------------------===//
#include "MYRISCVXGenInstrInfo.inc"
#include "llvm/CodeGen/TargetInstrInfo.h"

class MYRISCVXInstrInfo : public MYRISCVXGenInstrInfo{};