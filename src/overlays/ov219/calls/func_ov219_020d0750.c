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
extern void func_ov219_020d0a90(void);
extern void func_ov219_020d0b3c(void);
extern void func_ov219_020d0b60(void);
extern void func_ov219_020d0bd8(void);
extern void func_ov219_020d0f14(void);
extern void func_ov219_020d1178(void);
extern void func_ov219_020d1268(void);
extern void func_ov219_020d167c(void);
extern void func_ov219_020d16a8(void);
extern void func_ov219_020d1778(void);

void func_ov219_020d0750(int *node) {
    int *state = (int *)node[1];
    int c = ((struct AiState *)(*state))->pendingAction;
    if (c != -1) {
        ((struct AiState *)(*state))->currentAction = (signed char)c;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xc6;
        ((struct AiState *)(*state))->flags1ae &= ~0x3;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 0x1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b &= ~0x2;
        switch (((struct AiState *)(*state))->currentAction) {
        case 0:
            func_0203c634(node, 1, func_ov219_020d0a90);
            break;
        case 1:
            func_0203c634(node, 1, func_ov219_020d0b3c);
            break;
        case 2:
            func_0203c634(node, 1, func_ov219_020d0b60);
            break;
        case 4:
            func_0203c634(node, 1, func_ov219_020d0bd8);
            break;
        case 5:
            func_0203c634(node, 1, func_ov219_020d0f14);
            break;
        case 6:
            func_0203c634(node, 1, func_ov219_020d1178);
            break;
        case 3:
            func_0203c634(node, 1, func_ov219_020d1268);
            break;
        case 8:
            func_0203c634(node, 1, func_ov219_020d1268);
            break;
        case 7:
            func_0203c634(node, 1, func_ov219_020d167c);
            break;
        case 9:
            func_0203c634(node, 1, func_ov219_020d16a8);
            break;
        case 10:
            func_0203c634(node, 1, func_ov219_020d1778);
            break;
        }
    }
    ((struct AiState *)(*state))->pendingAction = -1;
}
