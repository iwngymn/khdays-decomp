struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1ae];
    unsigned short flags1ae;      /* 0x1ae */
    unsigned char pad1b0[0x16];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
    unsigned char pad1c8[0x1cc];
    int field_394;                /* 0x394 */
};

extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov250_020d0784(void);
extern void func_ov250_020d0834(void);
extern void func_ov250_020d0988(void);
extern void func_ov250_020d0c00(void);
extern void func_ov250_020d1000(void);
extern void func_ov250_020d15a0(void);
extern void func_ov250_020d1728(void);
extern void func_ov250_020d17f4(void);
extern void func_ov250_020d1b08(void);
extern void func_ov250_020d1fcc(void);
extern void func_ov250_020d24a0(void);
extern void func_ov250_020d26d0(void);
extern void func_ov250_020d2818(void);

void func_ov250_020d04d8(int *node) {
    int *state = (int *)node[1];
    if (((struct AiState *)(*state))->pendingAction != -1) {
        ((struct AiState *)(*state))->flags1ae &= ~1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        ((struct AiState *)(*state))->field_394 = 0x1000;
        ((struct AiState *)(*state))->currentAction = ((struct AiState *)(*state))->pendingAction;
        switch (((struct AiState *)(*state))->currentAction) {
        case 0:
            func_0203c634(node, 1, func_ov250_020d0784);
            break;
        case 1:
            func_0203c634(node, 1, func_ov250_020d0834);
            break;
        case 2:
            func_0203c634(node, 1, func_ov250_020d0988);
            break;
        case 4:
            func_0203c634(node, 1, func_ov250_020d0c00);
            break;
        case 5:
            func_0203c634(node, 1, func_ov250_020d1000);
            break;
        case 6:
            func_0203c634(node, 1, func_ov250_020d15a0);
            break;
        case 3:
            func_0203c634(node, 1, func_ov250_020d1728);
            break;
        case 7:
            func_0203c634(node, 1, func_ov250_020d17f4);
            break;
        case 8:
            func_0203c634(node, 1, func_ov250_020d1b08);
            break;
        case 9:
            func_0203c634(node, 1, func_ov250_020d1fcc);
            break;
        case 0xa:
            func_0203c634(node, 1, func_ov250_020d24a0);
            break;
        case 0xb:
            func_0203c634(node, 1, func_ov250_020d26d0);
            break;
        case 0xc:
            func_0203c634(node, 1, func_ov250_020d2818);
            break;
        }
    }
    ((struct AiState *)(*state))->pendingAction = -1;
}
