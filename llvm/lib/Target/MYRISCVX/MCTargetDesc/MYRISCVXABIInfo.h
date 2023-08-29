//--------------------------//
// ABIとそれに関連する関数の定義//
//-------------------------//

class MYRISCVXABIInfo {

// ABIの種類を表す列挙型
  public :
  enum class ABI { Unknown , LP, STACK };

// ThisABI変数にABIの種類を格納する
  protected :
  ABI ThisABI;

// ABIの種類に応じてレジスタを格納する
  public :
  MYRISCVXABIInfo(ABI ThisABI) : ThisABI(ThisABI) {}

//ABIの種類を返す
  static MYRISCVXABIInfo Unknown() { return MYRISCVXABIInfo(ABI::Unknown); }
  static MYRISCVXABIInfo LP() { return MYRISCVXABIInfo(ABI::LP); }
  static MYRISCVXABIInfo STACK() { return MYRISCVXABIInfo(ABI::STACK);}


// ABIの種類によってMYRISCVXABIInfoオブジェクトを返す
  static MYRISCVXABIInfo computeTargetABI(StringRef ABIName);

// ABIが指定されているかどうかを返す
  bool IsKnown() const { return ThisABI != ABI::Unknown; }
// ABIがLPかどうかを返す
  bool ISLP() const { return ThisABI == ABI::LP; }
// ABIがSTACKかどうかを返す
  bool ISSTACK() const { return ThisABI == ABI::STACK; }

// const : ABIの列挙値を返す
  ABI GetEnumValue() const { return ThisABI; }

//byvalに使うレジスタの配列を取得
  ArrayRef<MCPhysReg> GetByVarArgRegs() const;

//可変引数リストに使うレジスタの配を取得
  ArrayRef<MCPhysReg> GetVarArgRegs() const;

//呼び出し側によって引数に割り当てられた領域のサイズを取得する
//CallingConv::FastCall　はO32の値に影響を与える
  unsigned GetCalleeAllocArgSizeInBytes(CallingConv::ID CC) const;

//ABIの順序  MYRISCVXABIInfoオブジェクト同士を比較する
//複数のABIオプションが指定されたときに使う関数
  bool operator<(const MYRISCVXABIInfo Other) const {
    return ThisABI < Other.GetEnumValue();
  }

//　スタックポインタ、フレームポインタ、NULLポインタの値を取得する
  unsigned GetStackPtr() const;
  unsigned GetFramePtr() const;
  unsigned GetNullPtr() const;

//　例外処理のためのレジスタを値を取得する
  unsigned GetEhDataReg(unsigned I) const;
//　例外処理のためのレジスタのサイズを取得する
  int EhDataRegSize() const;

};