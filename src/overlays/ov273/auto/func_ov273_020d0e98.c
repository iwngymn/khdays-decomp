/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c6];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

int func_ov273_020d0e98(char *obj) {
    char *node = *(char **)*(char **)(obj + 0x214);
    signed char state = ((struct AiState *)(node))->currentAction;
    if (!(state != 2 && state != 4 && state != 5 && state != 6 && state != 7)) {
        if (((struct AiState *)(node))->pendingAction == -1) {
            ((struct AiState *)(node))->pendingAction = 0xf;
            return 1;
        }
    }
    return 0;
}
