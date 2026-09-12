struct bf { unsigned b : 8; };
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c6];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov246_020d0ab0(void);
extern void func_ov246_020d0874(void);
extern void func_ov246_020d09fc(void);

void func_ov246_020d07b0(int *node) {
    int *state = (int *)node[1];
    ((struct AiState *)(*state))->currentAction = 0;
    ((struct AiState *)(*state))->pendingAction = -1;
    ((struct bf *)(*(int *)(*state + 0x384) + 8))->b &= ~1;
    state[0x13] = *state + 0xb0;
    state[0x14] = *state + 0x74;
    {
        unsigned short *p = (unsigned short *)(*state + 0x60);
        unsigned int u = *p;
        *p = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 6) << 0x18) >> 0x10));
    }
    func_0203c634(node, 1, func_ov246_020d0ab0);
    func_0203c634(node, 0, func_ov246_020d0874);
    func_0203c634(node, 2, func_ov246_020d09fc);
}
