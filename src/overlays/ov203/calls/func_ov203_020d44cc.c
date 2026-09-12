// variant: popeq=False mirror_top=True
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
extern void func_ov203_020d4770(void);
extern void func_ov203_020d4814(void);
extern void func_ov203_020d4a08(void);
extern void func_ov203_020d4ad8(void);
extern void func_ov203_020d4d54(void);
extern void func_ov203_020d4fc0(void);
extern void func_ov203_020d50ac(void);
extern void func_ov203_020d572c(void);
extern void func_ov203_020d5934(void);
extern void func_ov203_020d6240(void);
extern void func_ov203_020d6308(void);

void func_ov203_020d44cc(int *node) {
    int *state = (int *)node[1];
    int c = ((struct AiState *)(*state))->pendingAction;
    if (c != -1) {
        ((struct AiState *)(*state))->currentAction = (signed char)c;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        ((struct AiState *)(*state))->flags1ae &= ~1;
        ((struct bf *)(*(int *)(*state + 0x38c) + 8))->b |= 1;
        switch (((struct AiState *)(*state))->currentAction) {
        case 0:
            func_0203c634(node, 1, func_ov203_020d4770);
            break;
        case 1:
            func_0203c634(node, 1, func_ov203_020d4814);
            break;
        case 2:
            func_0203c634(node, 1, func_ov203_020d4a08);
            break;
        case 4:
            func_0203c634(node, 1, func_ov203_020d4ad8);
            break;
        case 9:
            func_0203c634(node, 1, func_ov203_020d4d54);
            break;
        case 5:
            func_0203c634(node, 1, func_ov203_020d4fc0);
            break;
        case 6:
            func_0203c634(node, 1, func_ov203_020d50ac);
            break;
        case 7:
            func_0203c634(node, 1, func_ov203_020d572c);
            break;
        case 8:
            func_0203c634(node, 1, func_ov203_020d5934);
            break;
        case 3:
            func_0203c634(node, 1, func_ov203_020d6240);
            break;
        case 0xa:
            func_0203c634(node, 1, func_ov203_020d6308);
            break;
        }
    }
    ((struct AiState *)(*state))->pendingAction = -1;
}
