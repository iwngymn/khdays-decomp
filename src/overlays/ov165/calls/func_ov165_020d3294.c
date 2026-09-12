struct w3 { int a, b, c; };
struct b1 { unsigned char b : 1; };
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c7];
    signed char pendingAction;    /* 0x1c7 */
};

extern void func_01ffa724(int factor, void *src, void *dst);
extern void func_0203c634();

void func_ov165_020d3294(int this_) {
    int holder = *(int *)(this_ + 4);
    void *src = (void *)(holder + 0x24);
    *(struct w3 *)(holder + 0x18) = *(struct w3 *)src;
    func_01ffa724(0xb00, src, src);
    if (*(unsigned char *)*(int *)(holder + 0x58) != 0) return;
    {
        int node = *(int *)holder;
        if (((struct b1 *)(node + 0x17a))->b || ((struct b1 *)(node + 0x17c))->b) {
            ((struct AiState *)(node))->pendingAction = 2;
            func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
        }
    }
}
