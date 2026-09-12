struct b1 { unsigned char b : 1; };
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c7];
    signed char pendingAction;    /* 0x1c7 */
};

extern void func_0203c634();

void func_ov136_020d3794(int this_) {
    int holder = *(int *)(this_ + 4);
    int node = *(int *)holder;
    if (((struct b1 *)(node + 0x17a))->b == 0) return;
    if (((struct b1 *)(holder + 0x42))->b) {
        ((struct AiState *)(node))->pendingAction = 4;
        func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
    } else {
        ((struct AiState *)(node))->pendingAction = 2;
        func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
    }
}
