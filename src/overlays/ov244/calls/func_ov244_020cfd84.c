/* Unless the busy byte at *(child+0x30) is set, map the counter at (child)+0x10 (0..3) to a
 * sub-state (4..7), advance the counter modulo 4 and dispatch with no handler. */
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c7];
    signed char pendingAction;    /* 0x1c7 */
};

extern int func_0203c634(int a, int b, void *handler);
void func_ov244_020cfd84(int param_1) {
    int child = *(int *)(param_1 + 4);
    if (*(unsigned char *)*(int *)(child + 0x30) != 0) return;
    switch (*(short *)(child + 0x10)) {
    case 0: ((struct AiState *)(*(int *)child))->pendingAction = 4; break;
    case 1: ((struct AiState *)(*(int *)child))->pendingAction = 5; break;
    case 2: ((struct AiState *)(*(int *)child))->pendingAction = 6; break;
    case 3: ((struct AiState *)(*(int *)child))->pendingAction = 7; break;
    }
    *(short *)(child + 0x10) = (*(short *)(child + 0x10) + 1) % 4;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)0);
}
