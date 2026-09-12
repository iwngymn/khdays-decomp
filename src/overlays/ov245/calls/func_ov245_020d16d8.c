/* Latch the queued sub-state +0x1c7 into +0x1c6 (bail if -1), clear bit4 of +0x1ae, dispatch the
 * matching handler, then reset +0x1c7 to -1. */
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1ae];
    unsigned short flags1ae;      /* 0x1ae */
    unsigned char pad1b0[0x16];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

extern int func_0203c634(int, int, void *);
extern int func_ov245_020d1798(int);
extern int func_ov245_020d1858(int);
extern int func_ov245_020d1bcc(int);
void func_ov245_020d16d8(int param_1) {
    int owner = *(int *)(param_1 + 4);
    int sub = ((struct AiState *)(*(int *)owner))->pendingAction;
    if (sub == -1) return;
    ((struct AiState *)(*(int *)owner))->currentAction = sub;
    ((struct AiState *)(*(int *)owner))->flags1ae &= ~0x10;
    switch (((struct AiState *)(*(int *)owner))->currentAction) {
    case 0: func_0203c634(param_1, 1, (void *)&func_ov245_020d1798); break;
    case 1: func_0203c634(param_1, 1, (void *)&func_ov245_020d1858); break;
    case 2: func_0203c634(param_1, 1, (void *)&func_ov245_020d1bcc); break;
    }
    ((struct AiState *)(*(int *)owner))->pendingAction = -1;
}
