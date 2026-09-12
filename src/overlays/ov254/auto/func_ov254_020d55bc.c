/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c6];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

void func_ov254_020d55bc(char *obj) {
    char *base = *(char **)obj;
    signed char v = ((struct AiState *)(base))->currentAction;
    if (v == 1) {
        ((struct AiState *)(base))->pendingAction = 2;
    }
}
