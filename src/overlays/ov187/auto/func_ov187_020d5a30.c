/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c6];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

int func_ov187_020d5a30(char *arg) {
    char *base = *(char **)(arg + 0x214);
    char *s = *(char **)base;
    signed char a = ((struct AiState *)(s))->currentAction;
    if (a == 9) {
        ((struct AiState *)(s))->pendingAction = 0;
        return 1;
    }
    {
        signed char b = ((struct AiState *)(s))->pendingAction;
        if (b != 8 && a != 8) {
            if (a == 7 || a == 2 || a == 4 || a == 6) {
                ((struct AiState *)(s))->pendingAction = 8;
            }
        }
    }
    return 0;
}
