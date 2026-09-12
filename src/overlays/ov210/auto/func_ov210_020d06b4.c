typedef struct { unsigned char flag : 1; } BitByte;

/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c6];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

int func_ov210_020d06b4(char *obj) {
    char *node = *(char **)*(char **)(obj + 0x214);
    signed char state = ((struct AiState *)(node))->currentAction;
    if (state == 0x12) {
        ((struct AiState *)(node))->pendingAction = 0;
        return 1;
    }
    if (((struct AiState *)(node))->pendingAction != 0x11 && state != 0x11) {
        if (((BitByte *)(node + 0x17a))->flag) {
            if (!(state != 2 && state != 9 && state != 0xa && state != 0xc && state != 0xd))
                ((struct AiState *)(node))->pendingAction = 0x11;
        }
    }
    return 0;
}
