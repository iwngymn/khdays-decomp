struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1ae];
    unsigned short flags1ae;      /* 0x1ae */
    unsigned char pad1b0[0x16];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
    unsigned char pad1c8[0x1c8];
    int field_390;                /* 0x390 */
};

extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov277_020d2330(void);
extern void func_ov277_020d23e0(void);
extern void func_ov277_020d2534(void);
extern void func_ov277_020d2720(void);
extern void func_ov277_020d28bc(void);
extern void func_ov277_020d2988(void);
extern void func_ov277_020d2d88(void);
extern void func_ov277_020d2eb4(void);
extern void func_ov277_020d3020(void);
extern void func_ov277_020d3120(void);
extern void func_ov277_020d33b0(void);
extern void func_ov277_020d347c(void);
extern void func_ov277_020d3548(void);

void func_ov277_020d2074(int *node) {
    int *state = (int *)node[1];
    int c = ((struct AiState *)(*state))->pendingAction;
    if (c != -1) {
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        ((struct AiState *)(*state))->flags1ae &= ~0x1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 0x1;
        ((struct AiState *)(*state))->field_390 = 0x1000;
        ((struct AiState *)(*state))->currentAction = ((struct AiState *)(*state))->pendingAction;
        switch (((struct AiState *)(*state))->currentAction) {
        case 0:
            func_0203c634(node, 1, func_ov277_020d2330);
            break;
        case 1:
            func_0203c634(node, 1, func_ov277_020d23e0);
            break;
        case 2:
            func_0203c634(node, 1, func_ov277_020d2534);
            break;
        case 4:
            func_0203c634(node, 1, func_ov277_020d2720);
            break;
        case 6:
            func_0203c634(node, 1, func_ov277_020d28bc);
            break;
        case 7:
            func_0203c634(node, 1, func_ov277_020d2988);
            break;
        case 8:
            func_0203c634(node, 1, func_ov277_020d2d88);
            break;
        case 5:
            func_0203c634(node, 1, func_ov277_020d2eb4);
            break;
        case 9:
            func_0203c634(node, 1, func_ov277_020d3020);
            break;
        case 0xa:
            func_0203c634(node, 1, func_ov277_020d3120);
            break;
        case 3:
            func_0203c634(node, 1, func_ov277_020d33b0);
            break;
        case 0xb:
            func_0203c634(node, 1, func_ov277_020d347c);
            break;
        case 0xc:
            func_0203c634(node, 1, func_ov277_020d3548);
            break;
        }
    }
    ((struct AiState *)(*state))->pendingAction = -1;
}
