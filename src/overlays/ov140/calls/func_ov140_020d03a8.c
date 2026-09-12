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
extern void func_ov140_020d0654(void);
extern void func_ov140_020d06f8(void);
extern void func_ov140_020d08ec(void);
extern void func_ov140_020d0b74(void);
extern void func_ov140_020d1138(void);
extern void func_ov140_020d176c(void);
extern void func_ov140_020d1d2c(void);
extern void func_ov140_020d1e58(void);
extern void func_ov140_020d0f58(void);
extern void func_ov140_020d1070(void);
extern void func_ov140_020d2788(void);

void func_ov140_020d03a8(int *node) {
    int *state = (int *)node[1];
    int c = ((struct AiState *)(*state))->pendingAction;
    if (c != -1) {
        ((struct AiState *)(*state))->currentAction = (signed char)c;
        ((struct AiState *)(*state))->flags1ae &= ~1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        switch (((struct AiState *)(*state))->currentAction) {
        case 0:
            func_0203c634(node, 1, func_ov140_020d0654);
            break;
        case 1:
            func_0203c634(node, 1, func_ov140_020d06f8);
            break;
        case 2:
            func_0203c634(node, 1, func_ov140_020d08ec);
            break;
        case 4:
            func_0203c634(node, 1, func_ov140_020d0b74);
            break;
        case 5:
            func_0203c634(node, 1, func_ov140_020d1138);
            break;
        case 6:
            func_0203c634(node, 1, func_ov140_020d176c);
            break;
        case 7:
            func_0203c634(node, 1, func_ov140_020d1d2c);
            break;
        case 8:
            func_0203c634(node, 1, func_ov140_020d1e58);
            break;
        case 9:
            func_0203c634(node, 1, func_ov140_020d0f58);
            break;
        case 3:
            func_0203c634(node, 1, func_ov140_020d1070);
            break;
        case 0xa:
            func_0203c634(node, 1, func_ov140_020d2788);
            break;
        }
    }
    ((struct AiState *)(*state))->pendingAction = -1;
}
