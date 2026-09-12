struct hw60 { unsigned short lo : 8, hi : 8; };
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1ae];
    unsigned short flags1ae;      /* 0x1ae */
    unsigned char pad1b0[0x16];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov151_020ccf28(void);
extern void func_ov151_020cd084(void);
extern void func_ov151_020ccfa0(void);
void func_ov151_020cce80(int *node) {
    int *state = (int *)node[1];
    state[2] = *state + 0xb0;
    ((struct AiState *)(*state))->currentAction = 0;
    ((struct AiState *)(*state))->pendingAction = 0xff;
    ((struct hw60 *)(*state + 0x60))->hi &= ~1;
    ((struct AiState *)(*state))->flags1ae &= ~1;
    func_0203c634(node, 0, func_ov151_020ccf28);
    func_0203c634(node, 1, func_ov151_020cd084);
    func_0203c634(node, 2, func_ov151_020ccfa0);
}
