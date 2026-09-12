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
extern void func_ov127_020ccc1c(void);
extern void func_ov127_020cccc8(void);
extern void func_ov127_020cce90(void);
extern void func_ov127_020ccf04(void);
extern void func_ov127_020cd15c(void);
extern void func_ov127_020cd300(void);
extern void func_ov127_020cd368(void);
extern void func_ov127_020cd4d0(void);
extern void func_ov127_020cd5a0(void);

void func_ov127_020cc988(int *node) {
    int *state = (int *)node[1];
    int c = ((struct AiState *)(*state))->pendingAction;
    if (c != -1) {
        ((struct AiState *)(*state))->currentAction = (signed char)c;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        ((struct AiState *)(*state))->flags1ae &= ~1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
        switch (((struct AiState *)(*state))->currentAction) {
        case 0:
            func_0203c634(node, 1, func_ov127_020ccc1c);
            break;
        case 1:
            func_0203c634(node, 1, func_ov127_020cccc8);
            break;
        case 2:
            func_0203c634(node, 1, func_ov127_020cce90);
            break;
        case 4:
            func_0203c634(node, 1, func_ov127_020ccf04);
            break;
        case 5:
            func_0203c634(node, 1, func_ov127_020cd15c);
            break;
        case 6:
            func_0203c634(node, 1, func_ov127_020cd300);
            break;
        case 7:
            func_0203c634(node, 1, func_ov127_020cd368);
            break;
        case 3:
            func_0203c634(node, 1, func_ov127_020cd4d0);
            break;
        case 8:
            func_0203c634(node, 1, func_ov127_020cd5a0);
            break;
        }
    }
    ((struct AiState *)(*state))->pendingAction = -1;
}
