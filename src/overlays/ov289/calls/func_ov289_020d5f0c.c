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
extern void func_ov289_020d6114(void);
extern void func_ov289_020d5fa8(void);
extern void func_ov289_020d60d0(void);

void func_ov289_020d5f0c(int this_) {
    int holder = *(int *)(this_ + 4);
    ((struct AiState *)(*(int *)holder))->currentAction = 0;
    ((struct AiState *)(*(int *)holder))->pendingAction = -1;
    *(int *)(holder + 0xc) = *(int *)holder + 0xb0;
    ((struct bf *)(*(int *)(*(int *)holder + 0x388) + 8))->b &= ~1;
    ((struct AiState *)(*(int *)holder))->field_394 = 0;
    func_0203c634(this_, 1, (int)&func_ov289_020d6114);
    func_0203c634(this_, 0, (int)&func_ov289_020d5fa8);
    func_0203c634(this_, 2, (int)&func_ov289_020d60d0);
}
