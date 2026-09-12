struct w3 { int a, b, c; };
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c7];
    signed char pendingAction;    /* 0x1c7 */
};

extern int func_ov145_020ce78c(int holder, int flag);
extern void func_0203c634();

void func_ov145_020cf26c(int this_) {
    int holder = *(int *)(this_ + 4);
    if (func_ov145_020ce78c(holder, 1) != 0) {
        *(int *)(holder + 0x4c) = 1;
        ((struct AiState *)(*(int *)holder))->pendingAction = 4;
        func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
    } else {
        int node = *(int *)holder;
        int v39c = *(int *)(node + 0x39c);
        if (v39c == 0 || *(int *)(node + 0x3b8) == 0) return;
        *(struct w3 *)(holder + 0xc) = *(struct w3 *)(v39c + *(int *)(holder + 0x44) * 16);
        ((struct AiState *)(*(int *)holder))->pendingAction = 3;
        func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
    }
}
