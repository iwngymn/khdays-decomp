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
extern void func_ov189_020d0cbc(void);
extern void func_ov189_020d0d60(void);
extern void func_ov189_020d0f44(void);
extern void func_ov189_020d10f8(void);
extern void func_ov189_020d1358(void);
extern void func_ov189_020d1444(void);
extern void func_ov189_020d15bc(void);
extern void func_ov189_020d1800(void);
extern void func_ov189_020d1a44(void);
extern void func_ov189_020d1d28(void);
extern void func_ov189_020d1df0(void);
extern void func_ov189_020d1f48(void);

void func_ov189_020d0a50(int *node) {
    int *state = (int *)node[1];
    int c = ((struct AiState *)(*state))->pendingAction;
    if (c != -1) {
        ((struct AiState *)(*state))->currentAction = (signed char)c;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xc6;
        ((struct AiState *)(*state))->flags1ae &= ~1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
        switch (((struct AiState *)(*state))->currentAction) {
        case 0:
            func_0203c634(node, 1, func_ov189_020d0cbc);
            break;
        case 1:
            func_0203c634(node, 1, func_ov189_020d0d60);
            break;
        case 2:
            func_0203c634(node, 1, func_ov189_020d0f44);
            break;
        case 4:
            func_0203c634(node, 1, func_ov189_020d10f8);
            break;
        case 5:
            func_0203c634(node, 1, func_ov189_020d1358);
            break;
        case 6:
            func_0203c634(node, 1, func_ov189_020d1444);
            break;
        case 7:
            func_0203c634(node, 1, func_ov189_020d15bc);
            break;
        case 8:
            func_0203c634(node, 1, func_ov189_020d1800);
            break;
        case 9:
            func_0203c634(node, 1, func_ov189_020d1a44);
            break;
        case 3:
            func_0203c634(node, 1, func_ov189_020d1d28);
            break;
        case 0xa:
            func_0203c634(node, 1, func_ov189_020d1df0);
            break;
        case 0xb:
            func_0203c634(node, 1, func_ov189_020d1f48);
            break;
        }
    }
    ((struct AiState *)(*state))->pendingAction = -1;
}
