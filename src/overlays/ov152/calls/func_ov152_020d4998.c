struct w4 { int a, b, c, d; };
struct hw60 { unsigned short lo : 8, hi : 8; };
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c7];
    signed char pendingAction;    /* 0x1c7 */
};

extern void func_0203c634();

void func_ov152_020d4998(int this_) {
    int holder = *(int *)(this_ + 4);
    if ((((struct hw60 *)(*(int *)holder + 0x60))->lo & 1) == 0) return;
    *(struct w4 *)(holder + 0x18) = *(struct w4 *)(*(int *)holder + 0x394);
    ((struct AiState *)(*(int *)holder))->pendingAction = 1;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
}
