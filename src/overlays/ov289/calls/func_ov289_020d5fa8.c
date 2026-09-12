struct bf { unsigned b : 8; };
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
extern void func_ov289_020d6114(void);
extern void func_ov289_020d61fc(void);
extern void func_ov289_020d63ac(void);
extern void func_ov289_020d69ec(void);
extern void func_ov289_020d6f94(void);

void func_ov289_020d5fa8(int *node) {
    int *state = (int *)node[1];
    int c = ((struct AiState *)(*state))->pendingAction;
    if (c == -1) return;
    ((struct AiState *)(*state))->currentAction = (signed char)c;
    ((struct hw60 *)(*state + 0x60))->hi &= ~0x80;
    ((struct AiState *)(*state))->flags1ae &= ~0x13;
    ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
    switch (((struct AiState *)(*state))->currentAction) {
    case 0:
        func_0203c634(node, 1, func_ov289_020d6114);
        break;
    case 1:
        func_0203c634(node, 1, func_ov289_020d61fc);
        break;
    case 2:
        func_0203c634(node, 1, func_ov289_020d63ac);
        break;
    case 4:
        func_0203c634(node, 1, func_ov289_020d69ec);
        break;
    case 3:
        func_0203c634(node, 1, func_ov289_020d6f94);
        break;
    }
    ((struct AiState *)(*state))->pendingAction = -1;
}
