struct bf { unsigned b : 8; };
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c6];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
    unsigned char pad1c8[0x1cc];
    int field_394;                /* 0x394 */
};

extern void func_0203c634();
extern void func_ov287_020d06b4(void);
extern void func_ov287_020d0548(void);
extern void func_ov287_020d0670(void);

void func_ov287_020d04ac(int this_) {
    int holder = *(int *)(this_ + 4);
    ((struct AiState *)(*(int *)holder))->currentAction = 0;
    ((struct AiState *)(*(int *)holder))->pendingAction = -1;
    *(int *)(holder + 0xc) = *(int *)holder + 0xb0;
    ((struct bf *)(*(int *)(*(int *)holder + 0x388) + 8))->b &= ~1;
    ((struct AiState *)(*(int *)holder))->field_394 = 0;
    func_0203c634(this_, 1, (int)&func_ov287_020d06b4);
    func_0203c634(this_, 0, (int)&func_ov287_020d0548);
    func_0203c634(this_, 2, (int)&func_ov287_020d0670);
}
