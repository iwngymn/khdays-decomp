/* For sub-state 0, seed the child's +0x18 vector from the constant at data_02041dc8. Then copy
 * that vector into *(child)+0xf0 and drive the pose via func_0203c9d0. */
struct w3 { int a, b, c; };
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c6];
    signed char currentAction;    /* 0x1c6 */
};

extern const struct w3 data_02041dc8;
extern void func_0203c9d0(int a, int b);
void func_ov225_020d49f4(int param_1) {
    int child = *(int *)(param_1 + 4);
    switch (((struct AiState *)(*(int *)child))->currentAction) {
    case 0: *(struct w3 *)(child + 0x18) = data_02041dc8; break;
    case 1: break;
    }
    *(struct w3 *)(*(int *)child + 0xf0) = *(struct w3 *)(child + 0x18);
    func_0203c9d0(*(int *)child + 0xa0, child + 0x30);
}
