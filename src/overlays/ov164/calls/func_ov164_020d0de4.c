/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c7];
    signed char pendingAction;    /* 0x1c7 */
    unsigned char pad1c8[0x5c];
    int field_224;                /* 0x224 */
    int field_228;                /* 0x228 */
};

extern int func_02023eb4(int max);
extern void func_0203c634(void *node, int idx, void *value);

void func_ov164_020d0de4(int *node) {
    int *state = (int *)node[1];
    if (*(unsigned char *)state[0x16] != 0) return;
    int base = ((struct AiState *)(*state))->field_224;
    int d = ((struct AiState *)(*state))->field_228 - base;
    if (d < 0) d = -d;
    state[0xd] = base + func_02023eb4(d + 1);
    ((struct AiState *)(*state))->pendingAction = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
