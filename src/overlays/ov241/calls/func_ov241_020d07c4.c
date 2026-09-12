struct hw60 { unsigned short lo : 8, hi : 8; };
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c7];
    signed char pendingAction;    /* 0x1c7 */
    unsigned char pad1c8[0x1];
    signed char field_1c9;        /* 0x1c9 */
};

extern void func_0203c634();

void func_ov241_020d07c4(int this_) {
    int holder = *(int *)(this_ + 4);
    if ((((struct hw60 *)(*(int *)holder + 0x60))->lo & 1) == 0) return;
    *(int *)(holder + 0x1c) = *(int *)(holder + 0x24) * 0x14 + *(int *)(*(int *)holder + 0x3a4);
    ((struct AiState *)(*(int *)holder))->pendingAction = ((struct AiState *)(*(int *)holder))->field_1c9;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
}
