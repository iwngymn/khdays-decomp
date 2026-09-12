/* Latch the queued sub-state into +0x1c6, reset +0x1c7, and dispatch the matching handler. */
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c6];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

extern int func_0203c634(int, int, void *);
extern int func_ov255_020d1d00(int);
extern int func_ov255_020d1df8(int);
void func_ov255_020d1c5c(int param_1) {
    int owner = *(int *)(param_1 + 4);
    int sub = ((struct AiState *)(*(int *)owner))->pendingAction;
    if (sub == -1) return;
    ((struct AiState *)(*(int *)owner))->currentAction = sub;
    ((struct AiState *)(*(int *)owner))->pendingAction = -1;
    switch (((struct AiState *)(*(int *)owner))->currentAction) {
    case 0: func_0203c634(param_1, 1, (void *)&func_ov255_020d1d00); break;
    case 1: func_0203c634(param_1, 1, (void *)&func_ov255_020d1df8); break;
    }
}
