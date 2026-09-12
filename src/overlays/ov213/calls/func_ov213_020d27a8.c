/* Clear the +0x1c6 byte, mark sub-state -1, set +4 = *(child)+0xb0 and register two handlers
 * in turn (slot 1 then slot 0). */
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c6];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

extern int func_0203c634(int a, int b, void *handler);
extern void func_ov213_020d289c(int);
extern void func_ov213_020d2800(int);
void func_ov213_020d27a8(int param_1) {
    int child = *(int *)(param_1 + 4);
    ((struct AiState *)(*(int *)child))->currentAction = 0;
    ((struct AiState *)(*(int *)child))->pendingAction = -1;
    *(int *)(child + 4) = *(int *)child + 0xb0;
    func_0203c634(param_1, 1, (void *)&func_ov213_020d289c);
    func_0203c634(param_1, 0, (void *)&func_ov213_020d2800);
}
