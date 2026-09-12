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
extern void func_ov199_020d47c8(void);
extern void func_ov199_020d486c(void);
extern void func_ov199_020d4ba0(void);
extern void func_ov199_020d4c40(void);
extern void func_ov199_020d4f30(void);
extern void func_ov199_020d511c(void);
extern void func_ov199_020d51ac(void);
extern void func_ov199_020d5290(void);
extern void func_ov199_020d53c4(void);

void func_ov199_020d455c(int *node) {
    int *state = (int *)node[1];
    int c = ((struct AiState *)(*state))->pendingAction;
    if (c != -1) {
        ((struct AiState *)(*state))->currentAction = (signed char)c;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0x86;
        ((struct AiState *)(*state))->flags1ae &= ~3;
        ((struct bf *)(*(int *)(*state + 0x38c) + 8))->b |= 1;
        switch (((struct AiState *)(*state))->currentAction) {
        case 0:
            func_0203c634(node, 1, func_ov199_020d47c8);
            break;
        case 1:
            func_0203c634(node, 1, func_ov199_020d486c);
            break;
        case 2:
            func_0203c634(node, 1, func_ov199_020d4ba0);
            break;
        case 4:
            func_0203c634(node, 1, func_ov199_020d4c40);
            break;
        case 5:
            func_0203c634(node, 1, func_ov199_020d4f30);
            break;
        case 6:
            func_0203c634(node, 1, func_ov199_020d511c);
            break;
        case 3:
            func_0203c634(node, 1, func_ov199_020d51ac);
            break;
        case 7:
            func_0203c634(node, 1, func_ov199_020d5290);
            break;
        case 8:
            func_0203c634(node, 1, func_ov199_020d53c4);
            break;
        }
    }
    ((struct AiState *)(*state))->pendingAction = -1;
}
