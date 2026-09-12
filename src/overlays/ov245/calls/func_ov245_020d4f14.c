/* Latch the queued sub-state +0x1c7 into +0x1c6 (bail if -1), clear bit1 of the hw60 hi byte,
 * dispatch the matching handler, then reset +0x1c7 to -1. */
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c6];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

extern int func_0203c634(int, int, void *);
extern int func_ov245_020d4fd4(int);
extern int func_ov245_020d508c(int);
extern int func_ov245_020d5204(int);
struct hw60 { unsigned short lo : 8, hi : 8; };
void func_ov245_020d4f14(int param_1) {
    int owner = *(int *)(param_1 + 4);
    int sub = ((struct AiState *)(*(int *)owner))->pendingAction;
    if (sub == -1) return;
    ((struct AiState *)(*(int *)owner))->currentAction = sub;
    ((struct hw60 *)(*(int *)owner + 0x60))->hi &= ~2;
    switch (((struct AiState *)(*(int *)owner))->currentAction) {
    case 0: func_0203c634(param_1, 1, (void *)&func_ov245_020d4fd4); break;
    case 1: func_0203c634(param_1, 1, (void *)&func_ov245_020d508c); break;
    case 2: func_0203c634(param_1, 1, (void *)&func_ov245_020d5204); break;
    }
    ((struct AiState *)(*(int *)owner))->pendingAction = -1;
}
