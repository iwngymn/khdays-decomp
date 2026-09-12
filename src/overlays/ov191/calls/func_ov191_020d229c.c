/* Copy the queued sub-state +0x1c7 into +0x1c6 (bail if -1) and dispatch the matching handler. */
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c6];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

extern int func_0203c634(int, int, void *);
extern int func_ov191_020d2348(int);
extern int func_ov191_020d2430(int);
extern int func_ov191_020d2a60(int);
void func_ov191_020d229c(int param_1) {
    int owner = *(int *)(param_1 + 4);
    int sub = ((struct AiState *)(*(int *)owner))->pendingAction;
    if (sub == -1) return;
    ((struct AiState *)(*(int *)owner))->currentAction = sub;
    switch (((struct AiState *)(*(int *)owner))->currentAction) {
    case 0: func_0203c634(param_1, 1, (void *)&func_ov191_020d2348); break;
    case 1: func_0203c634(param_1, 1, (void *)&func_ov191_020d2430); break;
    case 2: func_0203c634(param_1, 1, (void *)&func_ov191_020d2a60); break;
    }
    ((struct AiState *)(*(int *)owner))->pendingAction = -1;
}
