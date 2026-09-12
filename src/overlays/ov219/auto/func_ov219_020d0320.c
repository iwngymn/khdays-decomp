/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c6];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

void func_ov219_020d0320(char *obj) {
    char *base = *(char **)(*(char **)(obj + 0x214));
    if (((struct AiState *)(base))->currentAction != 3) {
        ((struct AiState *)(base))->pendingAction = 3;
    }
}
