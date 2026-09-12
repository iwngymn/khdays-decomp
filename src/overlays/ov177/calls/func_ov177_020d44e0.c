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
extern void func_ov177_020d476c(void);
extern void func_ov177_020d4858(void);
extern void func_ov177_020d4a30(void);
extern void func_ov177_020d4e3c(void);
extern void func_ov177_020d5078(void);
extern void func_ov177_020d5280(void);
extern void func_ov177_020d546c(void);
extern void func_ov177_020d56d4(void);
extern void func_ov177_020d5708(void);
extern void func_ov177_020d591c(void);
extern void func_ov177_020d5830(void);

void func_ov177_020d44e0(int *node) {
    int *state = (int *)node[1];
    int c = ((struct AiState *)(*state))->pendingAction;
    if (c != -1) {
        ((struct AiState *)(*state))->currentAction = (signed char)c;
        ((struct AiState *)(*state))->flags1ae &= ~1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
        {
            unsigned short *p = (unsigned short *)(*state + 0x60);
            unsigned int u = *p;
            *p = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10));
        }
        ((struct hw60 *)(*state + 0x60))->hi &= ~0x8e;
        switch (((struct AiState *)(*state))->currentAction) {
        case 0:
            func_0203c634(node, 1, func_ov177_020d476c);
            break;
        case 1:
            func_0203c634(node, 1, func_ov177_020d4858);
            break;
        case 2:
            func_0203c634(node, 1, func_ov177_020d4a30);
            break;
        case 4:
            func_0203c634(node, 1, func_ov177_020d4e3c);
            break;
        case 5:
            func_0203c634(node, 1, func_ov177_020d5078);
            break;
        case 6:
            func_0203c634(node, 1, func_ov177_020d5280);
            break;
        case 8:
            func_0203c634(node, 1, func_ov177_020d546c);
            break;
        case 0xc:
            func_0203c634(node, 1, func_ov177_020d56d4);
            break;
        case 0xd:
            func_0203c634(node, 1, func_ov177_020d5708);
            break;
        case 0xe:
            func_0203c634(node, 1, func_ov177_020d591c);
            break;
        case 3:
            func_0203c634(node, 1, func_ov177_020d5830);
            break;
        }
    }
    ((struct AiState *)(*state))->pendingAction = -1;
}
