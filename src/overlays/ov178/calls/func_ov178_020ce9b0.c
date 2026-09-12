/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c6];
    signed char currentAction;    /* 0x1c6 */
};

extern void func_ov107_020cb100();
extern void func_ov107_020c7ca4();

void func_ov178_020ce9b0(int this_) {
    if (((struct AiState *)(this_))->currentAction != 1 && *(int *)(this_ + 0x38c) != 0) {
        func_ov107_020cb100(*(int *)(this_ + 0x38c));
        *(int *)(this_ + 0x38c) = 0;
    }
    func_ov107_020c7ca4(this_);
}
