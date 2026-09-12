/* Latch the pending state byte (+0x1c7) into +0x1c6; if valid and it names
 * transition 0 or 1, dispatch the matching handler; then mark +0x1c7 consumed. */
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c6];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

extern int func_0203c634(int a, int b, void *handler);
extern void func_ov256_020d079c(void);
extern void func_ov256_020d0874(void);
void func_ov256_020d06b4(int param_1) {
    int child = *(int *)(param_1 + 4);
    signed char v = ((struct AiState *)(*(int *)child))->pendingAction;
    if (v != -1) {
        ((struct AiState *)(*(int *)child))->currentAction = v;
        switch (((struct AiState *)(*(int *)child))->currentAction) {
        case 0:
            func_0203c634(param_1, 1, (void *)&func_ov256_020d079c);
            break;
        case 1:
            func_0203c634(param_1, 1, (void *)&func_ov256_020d0874);
            break;
        }
    }
    ((struct AiState *)(*(int *)child))->pendingAction = -1;
}
