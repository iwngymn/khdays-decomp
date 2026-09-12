/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c7];
    signed char pendingAction;    /* 0x1c7 */
    unsigned char pad1c8[0x5c];
    int field_224;                /* 0x224 */
    int field_228;                /* 0x228 */
};

extern int func_02023eb4(int);
extern void func_0203c634(void *obj, int idx, void *value);

void func_ov192_020d2e1c(int *node) {
    int *state = (int *)node[1];
    if (*(unsigned char *)state[1] == 0) {
        int lo = ((struct AiState *)(*state))->field_224;
        int hi = ((struct AiState *)(*state))->field_228;
        int d = hi - lo;
        if (d < 0) d = -d;
        state[0xd] = lo + func_02023eb4(d + 1);
        ((struct AiState *)(*state))->pendingAction = 2;
        func_0203c634(node, *(signed char *)(node + 8), (void *)0);
    }
}
