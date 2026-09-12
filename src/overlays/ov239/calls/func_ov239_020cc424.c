/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c6];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

extern void func_ov107_020c7ca4();

void func_ov239_020cc424(int this_) {
    if ((*(unsigned char *)(this_ + 0x1c4) & 0xa) &&
        ((struct AiState *)(this_))->currentAction != 0 &&
        ((struct AiState *)(this_))->currentAction != 1 &&
        ((struct AiState *)(this_))->currentAction != 3 &&
        ((struct AiState *)(this_))->currentAction != 7) {
        ((struct AiState *)(this_))->pendingAction = 7;
    }
    func_ov107_020c7ca4(this_);
}
