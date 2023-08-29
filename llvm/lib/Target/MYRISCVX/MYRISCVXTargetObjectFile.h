//===--------------------------------===//
// ELF形式ファイルを生成する際に使用するクラス //
//===--------------------------------===//

class MYRISCVXTargetObjectFile : public TargetLoweringObjectFileELF {
    const MYRISCVXTargetMachine *TM;
    public:

    void Initialize(MCCOntext &Ctx, const TargetMachine &TM) override;
};



