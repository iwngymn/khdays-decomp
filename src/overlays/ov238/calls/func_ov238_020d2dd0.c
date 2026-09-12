/* Clear the hw60 flag; if +0x390 was armed, clear it, mark state 0 and dispatch. */
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c7];
    signed char pendingAction;    /* 0x1c7 */
    unsigned char pad1c8[0x1c8];
    int field_390;                /* 0x390 */
};

extern int func_0203c634(int, int, void *);
struct hw60 { unsigned short lo : 8; unsigned short hi : 8; };
void func_ov238_020d2dd0(int param_1) {
    int owner = *(int *)(param_1 + 4);
    ((struct hw60 *)(*(int *)owner + 0x60))->hi &= ~0x80;
    if (((struct AiState *)(*(int *)owner))->field_390 == 0) return;
    ((struct AiState *)(*(int *)owner))->field_390 = 0;
    ((struct AiState *)(*(int *)owner))->pendingAction = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
