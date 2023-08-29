//------------------------------------------//
//このファイルでは明確なクラスは定義しません
//その代わりにターゲット記述ファイルが生成した
//C++ファイルをincludeしそれらを初期化するコードを記述します
//------------------------------------------//

//MYRISCVXRegsterInfo.inc / MYRISCVXGenInstrInfo.inc/
//MYRISCVXGenSubtargetInfo.incからヘッダファイルに必要な情報を抽出する。
#define GET_REGINFO_ENUM
#include "MYRISCVXRegisterInfo.inc"


#define GET_INSTRINFO_ENUM
#include "MYRISCVXGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "MYRISCVXGenSubtargetInfo.inc"