/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c6];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

int func_ov263_020d0d3c(char *obj) {
    char *base = *(char **)(*(char **)(obj + 0x214));
    signed char v = ((struct AiState *)(base))->currentAction;
    if (v == 0xd) return 0;
    if (v == 2 || v == 4) {
        ((struct AiState *)(base))->pendingAction = 0xd;
        return 1;
    }
    return 0;
}
