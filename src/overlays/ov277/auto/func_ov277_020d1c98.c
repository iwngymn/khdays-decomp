typedef struct { unsigned char flag : 1; } BitByte;

/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c6];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

int func_ov277_020d1c98(char *obj) {
    char *node = *(char **)*(char **)(obj + 0x214);
    signed char state = ((struct AiState *)(node))->currentAction;
    if (state == 0xc) {
        ((struct AiState *)(node))->pendingAction = 0;
        return 1;
    }
    if (((struct AiState *)(node))->pendingAction != 0xb && state != 0xb) {
        if (((BitByte *)(node + 0x17a))->flag) {
            if (!(state != 2 && state != 4 && state != 9 && state != 0xa))
                ((struct AiState *)(node))->pendingAction = 0xb;
        }
    }
    return 0;
}
