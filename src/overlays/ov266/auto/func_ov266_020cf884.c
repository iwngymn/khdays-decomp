/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c6];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

int func_ov266_020cf884(char *obj) {
    char *base = *(char **)(*(char **)(obj + 0x214));
    if (((struct AiState *)(base))->currentAction != 0xd) {
        ((struct AiState *)(base))->pendingAction = 0xd;
        return 1;
    }
    return 0;
}
