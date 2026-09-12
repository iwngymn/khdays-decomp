/* Unless the busy byte at *(child+0x28) is set, mark sub-state 2, pick a landing point at
 * (child)+0x54 = base(+0x224) + rand(|+0x228 - +0x224| + 1) and dispatch with no handler. */
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c7];
    signed char pendingAction;    /* 0x1c7 */
    unsigned char pad1c8[0x5c];
    int field_224;                /* 0x224 */
    int field_228;                /* 0x228 */
};

extern int func_02023eb4(int a);
extern int func_0203c634(int a, int b, void *handler);
void func_ov125_020cdf78(int param_1) {
    int child = *(int *)(param_1 + 4);
    int base, d;
    if (*(unsigned char *)*(int *)(child + 0x28) != 0) return;
    ((struct AiState *)(*(int *)child))->pendingAction = 2;
    base = ((struct AiState *)(*(int *)child))->field_224;
    d = ((struct AiState *)(*(int *)child))->field_228 - base;
    if (d < 0) d = -d;
    *(int *)(child + 0x54) = base + func_02023eb4(d + 1);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)0);
}
