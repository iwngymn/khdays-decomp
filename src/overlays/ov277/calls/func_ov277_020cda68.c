/* Unless the hw60 gate bit is set, copy the +0x394 vector into +0x4 and dispatch. */
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c7];
    signed char pendingAction;    /* 0x1c7 */
};

extern int func_0203c634(int, int, void *);
struct hw60 { unsigned short lo : 8; unsigned short hi : 8; };
struct w4 { int a, b, c, d; };
void func_ov277_020cda68(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if ((((struct hw60 *)(*(int *)owner + 0x60))->lo & 1) == 0) return;
    *(struct w4 *)(owner + 0x4) = *(struct w4 *)(*(int *)owner + 0x394);
    ((struct AiState *)(*(int *)owner))->pendingAction = 1;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
