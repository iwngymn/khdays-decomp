/* Reset the reaction slot (state -1, mark 1, clear hw60/1ae bits) then fan out three dispatches. */
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1ae];
    unsigned short flags1ae;      /* 0x1ae */
    unsigned char pad1b0[0x16];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

extern int func_0203c634(int, int, void *);
struct hw60 { unsigned short lo : 8, hi : 8; };
extern int func_ov256_020d166c(int);
extern int func_ov256_020d1a40(int);
extern int func_ov256_020d1714(int);
void func_ov256_020d15c0(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(int *)(owner + 0xc) = *(int *)owner + 0xb0;
    ((struct AiState *)(*(int *)owner))->currentAction = 1;
    ((struct AiState *)(*(int *)owner))->pendingAction = -1;
    ((struct hw60 *)(*(int *)owner + 0x60))->hi &= ~1;
    ((struct AiState *)(*(int *)owner))->flags1ae &= ~1;
    func_0203c634(param_1, 0, (void *)&func_ov256_020d166c);
    func_0203c634(param_1, 1, (void *)&func_ov256_020d1a40);
    func_0203c634(param_1, 2, (void *)&func_ov256_020d1714);
}
