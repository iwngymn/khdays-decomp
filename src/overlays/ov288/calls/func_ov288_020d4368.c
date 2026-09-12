/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c7];
    signed char pendingAction;    /* 0x1c7 */
    unsigned char pad1c8[0x1];
    signed char field_1c9;        /* 0x1c9 */
};

extern unsigned int func_02023eb4(int);
extern void func_ov107_020c9264(int node, int a, int b);
extern void func_0203c634();

struct hw60 { unsigned short lo : 8, hi : 8; };

void func_ov288_020d4368(int this_) {
    int node = *(int *)(this_ + 4);
    if ((((struct hw60 *)(*(int *)node + 0x60))->lo & 1) == 0) return;
    *(int *)(*(int *)node + 0x38c) = func_02023eb4(0x64) < 0xa;
    func_ov107_020c9264(*(int *)node, 1, 0);
    ((struct AiState *)(*(int *)node))->pendingAction = ((struct AiState *)(*(int *)node))->field_1c9;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
}
