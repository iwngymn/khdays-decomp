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
extern void func_ov205_020d43d0(void);
extern void func_ov205_020d44a0(void);
extern void func_ov205_020d4668(void);
extern void func_ov205_020d4960(void);
extern void func_ov205_020d4da4(void);
extern void func_ov205_020d4eb8(void);
extern void func_ov205_020d4f80(void);
extern void func_ov205_020d54cc(void);
extern void func_ov205_020d5994(void);
extern void func_ov205_020d5a94(void);
extern void func_ov205_020d639c(void);
extern void func_ov205_020d6450(void);

void func_ov205_020d4108(int *node) {
    int *state = (int *)node[1];
    int c = ((struct AiState *)(*state))->pendingAction;
    if (c != -1) {
        ((struct AiState *)(*state))->flags1ae &= ~1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        ((struct AiState *)(*state))->currentAction = ((struct AiState *)(*state))->pendingAction;
        switch (((struct AiState *)(*state))->currentAction) {
        case 0:
            func_0203c634(node, 1, func_ov205_020d43d0);
            break;
        case 1:
            func_0203c634(node, 1, func_ov205_020d44a0);
            break;
        case 2:
            func_0203c634(node, 1, func_ov205_020d4668);
            break;
        case 4:
            func_0203c634(node, 1, func_ov205_020d4960);
            break;
        case 5:
            func_0203c634(node, 1, func_ov205_020d4da4);
            break;
        case 3:
            func_0203c634(node, 1, func_ov205_020d4eb8);
            break;
        case 6:
            func_0203c634(node, 1, func_ov205_020d4f80);
            break;
        case 7:
            func_0203c634(node, 1, func_ov205_020d54cc);
            break;
        case 8:
            func_0203c634(node, 1, func_ov205_020d5994);
            break;
        case 9:
            func_0203c634(node, 1, func_ov205_020d5a94);
            break;
        case 0xa:
            func_0203c634(node, 1, func_ov205_020d639c);
            break;
        case 0xb:
            func_0203c634(node, 1, func_ov205_020d6450);
            break;
        }
    }
    ((struct AiState *)(*state))->pendingAction = -1;
}
