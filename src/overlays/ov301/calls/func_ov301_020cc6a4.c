struct hw60 { unsigned short lo : 8, hi : 8; };
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c7];
    signed char pendingAction;    /* 0x1c7 */
    unsigned char pad1c8[0x1];
    signed char field_1c9;        /* 0x1c9 */
};

extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(void *node, int idx, void *value);

void func_ov301_020cc6a4(int *node) {
    int *state = (int *)node[1];
    if (!(((struct hw60 *)(*state + 0x60))->lo & 1)) return;
    ((struct AiState *)(*state))->pendingAction = ((struct AiState *)(*state))->field_1c9;
    func_ov107_020c9264(*state, 0, 1);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
