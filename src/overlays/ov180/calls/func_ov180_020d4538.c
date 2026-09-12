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
extern void func_ov180_020d47d8(void);
extern void func_ov180_020d48c4(void);
extern void func_ov180_020d4a9c(void);
extern void func_ov180_020d4f1c(void);
extern void func_ov180_020d51b8(void);
extern void func_ov180_020d53d8(void);
extern void func_ov180_020d5a04(void);
extern void func_ov180_020d5630(void);
extern void func_ov180_020d5bc0(void);
extern void func_ov180_020d5c00(void);
extern void func_ov180_020d5e5c(void);
extern void func_ov180_020d5d70(void);

void func_ov180_020d4538(int *node) {
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
            func_0203c634(node, 1, func_ov180_020d47d8);
            break;
        case 1:
            func_0203c634(node, 1, func_ov180_020d48c4);
            break;
        case 2:
            func_0203c634(node, 1, func_ov180_020d4a9c);
            break;
        case 4:
            func_0203c634(node, 1, func_ov180_020d4f1c);
            break;
        case 5:
            func_0203c634(node, 1, func_ov180_020d51b8);
            break;
        case 6:
            func_0203c634(node, 1, func_ov180_020d53d8);
            break;
        case 8:
            func_0203c634(node, 1, func_ov180_020d5a04);
            break;
        case 9:
            func_0203c634(node, 1, func_ov180_020d5630);
            break;
        case 0xc:
            func_0203c634(node, 1, func_ov180_020d5bc0);
            break;
        case 0xd:
            func_0203c634(node, 1, func_ov180_020d5c00);
            break;
        case 0xe:
            func_0203c634(node, 1, func_ov180_020d5e5c);
            break;
        case 3:
            func_0203c634(node, 1, func_ov180_020d5d70);
            break;
        }
    }
    ((struct AiState *)(*state))->pendingAction = -1;
}
