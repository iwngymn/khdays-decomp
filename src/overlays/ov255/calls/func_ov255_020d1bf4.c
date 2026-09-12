/* Reset the reaction slot (mark 0, state -1) then fan out three dispatches. */
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c6];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

extern int func_0203c634(int, int, void *);
extern int func_ov255_020d1c5c(int);
extern int func_ov255_020d1d00(int);
extern int func_ov255_020d1cd0(int);
void func_ov255_020d1bf4(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(int *)(owner + 4) = *(int *)owner + 0xb0;
    ((struct AiState *)(*(int *)owner))->currentAction = 0;
    ((struct AiState *)(*(int *)owner))->pendingAction = -1;
    func_0203c634(param_1, 0, (void *)&func_ov255_020d1c5c);
    func_0203c634(param_1, 1, (void *)&func_ov255_020d1d00);
    func_0203c634(param_1, 2, (void *)&func_ov255_020d1cd0);
}
