/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c7];
    signed char pendingAction;    /* 0x1c7 */
    unsigned char pad1c8[0x1cc];
    int field_394;                /* 0x394 */
};

extern int FX_Inv(int a, int b);
extern void func_0203c634();

void func_ov251_020d63e0(int this_) {
    int field0 = *(int *)this_;
    int holder = *(int *)(this_ + 4);
    int t = *(int *)(holder + 0x1c) + *(int *)(field0 + 0x2c);
    *(int *)(holder + 0x1c) = t;
    ((struct AiState *)(*(int *)holder))->field_394 = 0x1000 - FX_Inv(t, 0x555);
    if (((struct AiState *)(*(int *)holder))->field_394 < 1) {
        ((struct AiState *)(*(int *)holder))->field_394 = 1;
    }
    if (*(int *)(holder + 0x1c) < 0x555) return;
    ((struct AiState *)(*(int *)holder))->pendingAction = 0xc;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
}
