
//--------------------------------------//
// SelectionDAGの変換に関する処理を担うクラス//
//--------------------------------------//



//LowerFormalArguments()
//引数渡しにおいて、引数を渡す方法を実装する
SDValue
MYRISCVXTargetLowering::LowerFormalArguments(SDValue Chain,
                                                CallingConv::ID CallConv,
                                                bool IsVarArg,
                                                const SmallVectorImp<ISD::InputArg> &Ins,
                                                const SDLoc &DL SelectionDAG &DAG,
                                                SmallVectorImpl<SDValue> &InVals)
const {
    //あとで書く
    return Chain;
}

//LowerReturn
//関数から戻る処理、LLVM iRのreturn文をどのようにSelectionDAGに書き換えるかをここで指定する
SDValue
MYRISCVXTargetLowering::LowerReturn(SDValue Chain,
                                    CallingConv::ID CallConv. bool ISVarArg,
                                    const SmallVectorImpl<ISD::OutputArg> &Outs,
                                    const SmallVectorImpl<SDValue> &OutVals,
                                    const SDLoc &DL, SelectionDAG &DAG) const {
//  あとで
return Chain;
}