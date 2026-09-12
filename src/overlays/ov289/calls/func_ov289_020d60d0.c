/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c6];
    signed char currentAction;    /* 0x1c6 */
};

extern int data_02041dc8;

struct w3 { int a, b, c; };

void func_ov289_020d60d0(int this_) {
    int node = *(int *)(this_ + 4);
    if (((struct AiState *)(*(int *)node))->currentAction != 2) {
        *(struct w3 *)(node + 0x1c) = *(struct w3 *)&data_02041dc8;
    }
    *(struct w3 *)(*(int *)node + 0xf0) = *(struct w3 *)(node + 0x1c);
}
