/* Clear the hw60 flag; unless busy mark state 2 and dispatch. */
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c7];
    signed char pendingAction;    /* 0x1c7 */
};

extern int func_0203c634(int, int, void *);
struct hw60 { unsigned short lo : 8; unsigned short hi : 8; };
void func_ov245_020cff94(int param_1) {
    int owner = *(int *)(param_1 + 4);
    ((struct hw60 *)(*(int *)owner + 0x60))->hi &= ~0x80;
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    ((struct AiState *)(*(int *)owner))->pendingAction = 2;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
