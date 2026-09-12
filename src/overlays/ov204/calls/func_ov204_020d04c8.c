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
extern void func_ov204_020d0790(void);
extern void func_ov204_020d0860(void);
extern void func_ov204_020d0a28(void);
extern void func_ov204_020d0d20(void);
extern void func_ov204_020d1164(void);
extern void func_ov204_020d1278(void);
extern void func_ov204_020d1340(void);
extern void func_ov204_020d188c(void);
extern void func_ov204_020d1d54(void);
extern void func_ov204_020d1e54(void);
extern void func_ov204_020d275c(void);
extern void func_ov204_020d2810(void);

void func_ov204_020d04c8(int *node) {
    int *state = (int *)node[1];
    int c = ((struct AiState *)(*state))->pendingAction;
    if (c != -1) {
        ((struct AiState *)(*state))->flags1ae &= ~1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        ((struct AiState *)(*state))->currentAction = ((struct AiState *)(*state))->pendingAction;
        switch (((struct AiState *)(*state))->currentAction) {
        case 0:
            func_0203c634(node, 1, func_ov204_020d0790);
            break;
        case 1:
            func_0203c634(node, 1, func_ov204_020d0860);
            break;
        case 2:
            func_0203c634(node, 1, func_ov204_020d0a28);
            break;
        case 4:
            func_0203c634(node, 1, func_ov204_020d0d20);
            break;
        case 5:
            func_0203c634(node, 1, func_ov204_020d1164);
            break;
        case 3:
            func_0203c634(node, 1, func_ov204_020d1278);
            break;
        case 6:
            func_0203c634(node, 1, func_ov204_020d1340);
            break;
        case 7:
            func_0203c634(node, 1, func_ov204_020d188c);
            break;
        case 8:
            func_0203c634(node, 1, func_ov204_020d1d54);
            break;
        case 9:
            func_0203c634(node, 1, func_ov204_020d1e54);
            break;
        case 0xa:
            func_0203c634(node, 1, func_ov204_020d275c);
            break;
        case 0xb:
            func_0203c634(node, 1, func_ov204_020d2810);
            break;
        }
    }
    ((struct AiState *)(*state))->pendingAction = -1;
}
