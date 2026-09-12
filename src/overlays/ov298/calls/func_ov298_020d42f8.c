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
extern void func_ov298_020d45a8(void);
extern void func_ov298_020d467c(void);
extern void func_ov298_020d47c0(void);
extern void func_ov298_020d4cb0(void);
extern void func_ov298_020d4f28(void);
extern void func_ov298_020d510c(void);
extern void func_ov298_020d5258(void);
extern void func_ov298_020d53c4(void);
extern void func_ov298_020d5484(void);

void func_ov298_020d42f8(int *node) {
    int *state = (int *)node[1];
    int c = ((struct AiState *)(*state))->pendingAction;
    if (c != -1) {
        ((struct AiState *)(*state))->currentAction = (signed char)c;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xc6;
        ((struct AiState *)(*state))->flags1ae &= ~3;
        ((struct bf *)(*(int *)(*state + 0x38c) + 8))->b |= 1;
        switch (((struct AiState *)(*state))->currentAction) {
        case 0:
            func_0203c634(node, 1, func_ov298_020d45a8);
            break;
        case 2:
            func_0203c634(node, 1, func_ov298_020d467c);
            break;
        case 4:
            func_0203c634(node, 1, func_ov298_020d47c0);
            break;
        case 5:
            func_0203c634(node, 1, func_ov298_020d4cb0);
            break;
        case 6:
            func_0203c634(node, 1, func_ov298_020d4f28);
            break;
        case 7:
            func_0203c634(node, 1, func_ov298_020d510c);
            break;
        case 8:
            func_0203c634(node, 1, func_ov298_020d5258);
            break;
        case 9:
            func_0203c634(node, 1, func_ov298_020d53c4);
            break;
        case 3:
            func_0203c634(node, 1, func_ov298_020d5484);
            break;
        }
    }
    ((struct AiState *)(*state))->pendingAction = -1;
}
