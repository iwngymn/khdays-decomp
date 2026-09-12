/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c7];
    signed char pendingAction;    /* 0x1c7 */
    unsigned char pad1c8[0x1];
    signed char field_1c9;        /* 0x1c9 */
};

extern void func_0203c634();

struct hw60 { unsigned short lo : 8, hi : 8; };

void func_ov128_020d4504(int this_) {
    int node = *(int *)(this_ + 4);
    if ((((struct hw60 *)(*(int *)node + 0x60))->lo & 1) == 0) return;
    *(int *)(node + 0x3c) = 0;
    ((struct AiState *)(*(int *)node))->pendingAction = ((struct AiState *)(*(int *)node))->field_1c9;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
}
