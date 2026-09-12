/* Accumulate the recovery cooldown (node[0xb] += owner delta *self+0x2c); once it passes 0x400,
 * set the hw60 high-byte "recovered" bit 0x80, clear the reaction state, and re-register the think
 * callback. */
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x60];
    unsigned short flags60;       /* 0x060 */
    unsigned char pad062[0x165];
    signed char pendingAction;    /* 0x1c7 */
};

extern void func_0203c634(int self, int idx, int cb);

void func_ov125_020ce3fc(int *param_1) {
    int *node = (int *)param_1[1];
    int cd;
    unsigned short hw60;
    cd = node[0xb] + *(int *)(*param_1 + 0x2c);
    node[0xb] = cd;
    if (cd < 0x400) {
        return;
    }
    hw60 = ((struct AiState *)(*node))->flags60;
    ((struct AiState *)(*node))->flags60 =
        (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 0x80) << 0x18) >> 0x10);
    ((struct AiState *)(*node))->pendingAction = 0;
    func_0203c634((int)param_1, *(signed char *)((char *)param_1 + 0x20), 0);
}
