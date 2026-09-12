struct hw60 { unsigned short lo : 8, hi : 8; };
struct bf { unsigned b : 8; };
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1ae];
    unsigned short flags1ae;      /* 0x1ae */
    unsigned char pad1b0[0x16];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov215_020d10fc(void);
extern void func_ov215_020d11dc(void);
extern void func_ov215_020d1374(void);
extern void func_ov215_020d1488(void);
extern void func_ov215_020d1a24(void);
extern void func_ov215_020d1644(void);
extern void func_ov215_020d22c4(void);
extern void func_ov215_020d23a8(void);
extern void func_ov215_020d2534(void);

void func_ov215_020d0e90(int *node) {
    int *state = (int *)node[1];
    if (((struct AiState *)(*state))->pendingAction != -1) {
        ((struct AiState *)(*state))->currentAction = ((struct AiState *)(*state))->pendingAction;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xc6;
        ((struct AiState *)(*state))->flags1ae &= ~3;
        ((struct bf *)(*(int *)(*state + 0x3ac) + 8))->b |= 1;
        switch (((struct AiState *)(*state))->currentAction) {
        case 0: func_0203c634(node, 1, func_ov215_020d10fc); break;
        case 1: func_0203c634(node, 1, func_ov215_020d11dc); break;
        case 2: func_0203c634(node, 1, func_ov215_020d1374); break;
        case 4: func_0203c634(node, 1, func_ov215_020d1488); break;
        case 5: func_0203c634(node, 1, func_ov215_020d1a24); break;
        case 6: func_0203c634(node, 1, func_ov215_020d1644); break;
        case 3: func_0203c634(node, 1, func_ov215_020d22c4); break;
        case 7: func_0203c634(node, 1, func_ov215_020d23a8); break;
        case 8: func_0203c634(node, 1, func_ov215_020d2534); break;
        }
    }
    ((struct AiState *)(*state))->pendingAction = -1;
}
