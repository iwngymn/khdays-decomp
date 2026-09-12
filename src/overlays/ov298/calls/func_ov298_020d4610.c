struct hw60 { unsigned short lo : 8, hi : 8; };

/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x224];
    int field_224;                /* 0x224 */
    int field_228;                /* 0x228 */
};

extern int func_02023eb4(int range);
extern void func_0203c634(void *node, int idx, void *value);

void func_ov298_020d4610(int node) {
    int *state = *(int **)(node + 4);
    int obj = *state;
    int start;
    int delta;

    if ((((struct hw60 *)(obj + 0x60))->lo & 1) == 0) return;

    start = ((struct AiState *)(obj))->field_224;
    delta = ((struct AiState *)(obj))->field_228 - start;
    if (delta < 0) {
        delta = -delta;
    }

    state[0xf] = start + func_02023eb4(delta + 1);
    state[0x12] = 0;
    *(signed char *)(*state + 0x1c7) = *(signed char *)(*state + 0x1c9);
    func_0203c634((void *)node, *(signed char *)(node + 0x20), 0);
}
