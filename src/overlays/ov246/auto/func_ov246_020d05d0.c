/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c6];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

int func_ov246_020d05d0(char *obj) {
    char *base = *(char **)(*(char **)(obj + 0x214));
    int s = ((struct AiState *)(base))->currentAction;
    /* goto forces cmp;cmpne over the range-opt (sub;cmp #1) for s==6||s==7 */
    if (s == 6 || s == 7) goto reject;
    if (0) {
    reject:
        return 0;
    }
    if (((struct AiState *)(base))->pendingAction == -1) {
        ((struct AiState *)(base))->pendingAction = 8;
        return 1;
    }
    return 0;
}
