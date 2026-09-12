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
extern void func_ov286_020d3dac(void);
extern void func_ov286_020d3e50(void);
extern void func_ov286_020d4038(void);
extern void func_ov286_020d4188(void);
extern void func_ov286_020d43ec(void);
extern void func_ov286_020d44b4(void);

void func_ov286_020d3bd0(int *node) {
    int *state = (int *)node[1];
    int c = ((struct AiState *)(*state))->pendingAction;
    if (c != -1) {
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        ((struct AiState *)(*state))->flags1ae &= ~1;
        ((struct bf *)(*(int *)(*state + 0x38c) + 8))->b |= 1;
        ((struct AiState *)(*state))->currentAction = ((struct AiState *)(*state))->pendingAction;
        switch (((struct AiState *)(*state))->currentAction) {
        case 0:
            func_0203c634(node, 1, func_ov286_020d3dac);
            break;
        case 1:
            func_0203c634(node, 1, func_ov286_020d3e50);
            break;
        case 2:
            func_0203c634(node, 1, func_ov286_020d4038);
            break;
        case 4:
            func_0203c634(node, 1, func_ov286_020d4188);
            break;
        case 3:
            func_0203c634(node, 1, func_ov286_020d43ec);
            break;
        case 5:
            func_0203c634(node, 1, func_ov286_020d44b4);
            break;
        }
    }
    ((struct AiState *)(*state))->pendingAction = -1;
}
