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
extern void func_ov188_020cee9c(void);
extern void func_ov188_020cef40(void);
extern void func_ov188_020cf124(void);
extern void func_ov188_020cf2d8(void);
extern void func_ov188_020cf538(void);
extern void func_ov188_020cf624(void);
extern void func_ov188_020cf79c(void);
extern void func_ov188_020cf9e0(void);
extern void func_ov188_020cfc24(void);
extern void func_ov188_020cff08(void);
extern void func_ov188_020cffd0(void);
extern void func_ov188_020d0128(void);

void func_ov188_020cec30(int *node) {
    int *state = (int *)node[1];
    int c = ((struct AiState *)(*state))->pendingAction;
    if (c != -1) {
        ((struct AiState *)(*state))->currentAction = (signed char)c;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xc6;
        ((struct AiState *)(*state))->flags1ae &= ~1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
        switch (((struct AiState *)(*state))->currentAction) {
        case 0:
            func_0203c634(node, 1, func_ov188_020cee9c);
            break;
        case 1:
            func_0203c634(node, 1, func_ov188_020cef40);
            break;
        case 2:
            func_0203c634(node, 1, func_ov188_020cf124);
            break;
        case 4:
            func_0203c634(node, 1, func_ov188_020cf2d8);
            break;
        case 5:
            func_0203c634(node, 1, func_ov188_020cf538);
            break;
        case 6:
            func_0203c634(node, 1, func_ov188_020cf624);
            break;
        case 7:
            func_0203c634(node, 1, func_ov188_020cf79c);
            break;
        case 8:
            func_0203c634(node, 1, func_ov188_020cf9e0);
            break;
        case 9:
            func_0203c634(node, 1, func_ov188_020cfc24);
            break;
        case 3:
            func_0203c634(node, 1, func_ov188_020cff08);
            break;
        case 0xa:
            func_0203c634(node, 1, func_ov188_020cffd0);
            break;
        case 0xb:
            func_0203c634(node, 1, func_ov188_020d0128);
            break;
        }
    }
    ((struct AiState *)(*state))->pendingAction = -1;
}
