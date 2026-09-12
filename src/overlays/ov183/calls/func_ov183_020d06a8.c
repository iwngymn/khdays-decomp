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
extern void func_ov183_020d0954(void);
extern void func_ov183_020d0a04(void);
extern void func_ov183_020d0b58(void);
extern void func_ov183_020d0dec(void);
extern void func_ov183_020d11ec(void);
extern void func_ov183_020d178c(void);
extern void func_ov183_020d1914(void);
extern void func_ov183_020d19e0(void);
extern void func_ov183_020d1adc(void);
extern void func_ov183_020d1d90(void);
extern void func_ov183_020d2248(void);
extern void func_ov183_020d2478(void);
extern void func_ov183_020d25c0(void);

void func_ov183_020d06a8(int *node) {
    int *state = (int *)node[1];
    if (((struct AiState *)(*state))->pendingAction != -1) {
        ((struct AiState *)(*state))->flags1ae &= ~1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        ((struct AiState *)(*state))->field_394 = 0x1000;
        ((struct AiState *)(*state))->currentAction = ((struct AiState *)(*state))->pendingAction;
        switch (((struct AiState *)(*state))->currentAction) {
        case 0:
            func_0203c634(node, 1, func_ov183_020d0954);
            break;
        case 1:
            func_0203c634(node, 1, func_ov183_020d0a04);
            break;
        case 2:
            func_0203c634(node, 1, func_ov183_020d0b58);
            break;
        case 4:
            func_0203c634(node, 1, func_ov183_020d0dec);
            break;
        case 5:
            func_0203c634(node, 1, func_ov183_020d11ec);
            break;
        case 6:
            func_0203c634(node, 1, func_ov183_020d178c);
            break;
        case 3:
            func_0203c634(node, 1, func_ov183_020d1914);
            break;
        case 7:
            func_0203c634(node, 1, func_ov183_020d19e0);
            break;
        case 8:
            func_0203c634(node, 1, func_ov183_020d1adc);
            break;
        case 9:
            func_0203c634(node, 1, func_ov183_020d1d90);
            break;
        case 0xa:
            func_0203c634(node, 1, func_ov183_020d2248);
            break;
        case 0xb:
            func_0203c634(node, 1, func_ov183_020d2478);
            break;
        case 0xc:
            func_0203c634(node, 1, func_ov183_020d25c0);
            break;
        }
    }
    ((struct AiState *)(*state))->pendingAction = -1;
}
