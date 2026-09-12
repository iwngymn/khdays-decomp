/* Clear the linked node's +0x4e0, latch the queued sub-state +0x1c7 into +0x1c6, dispatch the
 * matching handler, then reset +0x1c7 to -1. */
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c6];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
    unsigned char pad1c8[0x1c8];
    int field_390;                /* 0x390 */
};

extern int func_0203c634(int, int, void *);
extern int func_ov254_020d2564(int);
extern int func_ov254_020d2608(int);
extern int func_ov254_020d2980(int);
void func_ov254_020d24bc(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(int *)(((struct AiState *)(*(int *)owner))->field_390 + 0x4e0) = 0;
    int sub = ((struct AiState *)(*(int *)owner))->pendingAction;
    if (sub != -1) {
        ((struct AiState *)(*(int *)owner))->currentAction = sub;
        switch (((struct AiState *)(*(int *)owner))->currentAction) {
        case 0: func_0203c634(param_1, 1, (void *)&func_ov254_020d2564); break;
        case 1: func_0203c634(param_1, 1, (void *)&func_ov254_020d2608); break;
        case 2: func_0203c634(param_1, 1, (void *)&func_ov254_020d2980); break;
        }
    }
    ((struct AiState *)(*(int *)owner))->pendingAction = -1;
}
