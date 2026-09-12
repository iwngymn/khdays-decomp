/* Latch the queued sub-state +0x1c7 into +0x1c6, clear bit1 of the hw60 hi byte, dispatch the
 * matching handler, then reset +0x1c7 to -1. */
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c6];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

extern int func_0203c634(int, int, void *);
extern int func_ov245_020d3f84(int);
extern int func_ov245_020d403c(int);
extern int func_ov245_020d465c(int);
struct hw60 { unsigned short lo : 8, hi : 8; };
void func_ov245_020d3e74(int param_1) {
    int owner = *(int *)(param_1 + 4);
    int sub = ((struct AiState *)(*(int *)owner))->pendingAction;
    if (sub != -1) {
        ((struct AiState *)(*(int *)owner))->currentAction = sub;
        ((struct hw60 *)(*(int *)owner + 0x60))->hi &= ~2;
        switch (((struct AiState *)(*(int *)owner))->currentAction) {
        case 0: func_0203c634(param_1, 1, (void *)&func_ov245_020d3f84); break;
        case 1: func_0203c634(param_1, 1, (void *)&func_ov245_020d403c); break;
        case 2: func_0203c634(param_1, 1, (void *)&func_ov245_020d465c); break;
        }
    }
    ((struct AiState *)(*(int *)owner))->pendingAction = -1;
}
