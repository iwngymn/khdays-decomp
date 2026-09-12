struct v3 { int a, b, c; };
struct b1 { unsigned char b : 1; };
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c7];
    signed char pendingAction;    /* 0x1c7 */
};

extern void func_01ffa724(int scale, void *v, void *out);
extern void func_0203c634(void *obj, int idx, void *value);

void func_ov269_020d2cf0(int *node) {
    int *state = (int *)node[1];
    *(struct v3 *)(state + 6) = *(struct v3 *)(state + 9);
    func_01ffa724(0xb00, state + 9, state + 9);
    if (*(unsigned char *)(state[1] + 0xad) != 0) return;
    if (((struct b1 *)(*state + 0x17a))->b || ((struct b1 *)(*state + 0x17c))->b) {
        state[0x11] = 3;
        ((struct AiState *)(*state))->pendingAction = 2;
        func_0203c634(node, *(signed char *)(node + 8), (void *)0);
    }
}
