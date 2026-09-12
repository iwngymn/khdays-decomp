/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c7];
    signed char pendingAction;    /* 0x1c7 */
};

int func_ov267_020d16d0(char *obj) {
    char *base = *(char **)(*(char **)(obj + 0x214));
    if (((struct AiState *)(base))->pendingAction == -1) {
        ((struct AiState *)(base))->pendingAction = 0xe;
        return 1;
    }
    return 0;
}
