namespace llvm {
    class StringRef;
    class MYRISCVXTargetMachine;
    class MYRISCVXSubtarget : public MYRISCVXGenSubtargetInfo {
        virtual void anchor();
        public:
        protected:

        bool HasRV64 = false;
    }
}