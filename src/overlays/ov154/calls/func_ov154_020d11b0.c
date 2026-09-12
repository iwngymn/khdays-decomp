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
extern void func_ov154_020d1394(void);
extern void func_ov154_020d1438(void);
extern void func_ov154_020d1604(void);
extern void func_ov154_020d1848(void);
extern void func_ov154_020d18d8(void);
extern void func_ov154_020d19a0(void);
extern void func_ov154_020d1a54(void);

void func_ov154_020d11b0(int *node) {
    int *state = (int *)node[1];
    if (((struct AiState *)(*state))->pendingAction == -1) return;
    ((struct hw60 *)(*state + 0x60))->hi &= ~0xc6;
    ((struct AiState *)(*state))->flags1ae &= ~0x41;
    ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
    ((struct AiState *)(*state))->currentAction = ((struct AiState *)(*state))->pendingAction;
    switch (((struct AiState *)(*state))->currentAction) {
    case 0:
        func_0203c634(node, 1, func_ov154_020d1394);
        break;
    case 1:
        func_0203c634(node, 1, func_ov154_020d1438);
        break;
    case 2:
        func_0203c634(node, 1, func_ov154_020d1604);
        break;
    case 5:
        func_0203c634(node, 1, func_ov154_020d1848);
        break;
    case 3:
        func_0203c634(node, 1, func_ov154_020d18d8);
        break;
    case 4:
        func_0203c634(node, 1, func_ov154_020d19a0);
        break;
    case 6:
        func_0203c634(node, 1, func_ov154_020d1a54);
        break;
    }
    ((struct AiState *)(*state))->pendingAction = -1;
}
