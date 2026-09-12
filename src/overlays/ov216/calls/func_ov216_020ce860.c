struct hw { unsigned short lo:8, hi:8; };

/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c7];
    signed char pendingAction;    /* 0x1c7 */
};

extern void func_0203c634(int node, int slot, void *cb);

void func_ov216_020ce860(int *param_1) {
    int *state = (int *)param_1[1];
    int acc = state[0x14] + *(int *)(*param_1 + 0x2c);
    state[0x14] = acc;
    if (acc < 0xd48) return;
    {
        unsigned short *p = (unsigned short *)(*state + 0x60);
        unsigned int u = *p;
        *p = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 0x80) << 0x18) >> 0x10));
    }
    ((struct hw *)(*state + 0x60))->hi &= ~1;
    ((struct AiState *)(*state))->pendingAction = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 8), 0);
}
