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
extern void func_ov169_020cce84(void);
extern void func_ov169_020ccf70(void);
extern void func_ov169_020cd148(void);
extern void func_ov169_020cd554(void);
extern void func_ov169_020cd790(void);
extern void func_ov169_020cd998(void);
extern void func_ov169_020cdb84(void);
extern void func_ov169_020cddec(void);
extern void func_ov169_020cde20(void);
extern void func_ov169_020ce034(void);
extern void func_ov169_020cdf48(void);

void func_ov169_020ccbf8(int *node) {
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
            func_0203c634(node, 1, func_ov169_020cce84);
            break;
        case 1:
            func_0203c634(node, 1, func_ov169_020ccf70);
            break;
        case 2:
            func_0203c634(node, 1, func_ov169_020cd148);
            break;
        case 4:
            func_0203c634(node, 1, func_ov169_020cd554);
            break;
        case 5:
            func_0203c634(node, 1, func_ov169_020cd790);
            break;
        case 6:
            func_0203c634(node, 1, func_ov169_020cd998);
            break;
        case 8:
            func_0203c634(node, 1, func_ov169_020cdb84);
            break;
        case 0xc:
            func_0203c634(node, 1, func_ov169_020cddec);
            break;
        case 0xd:
            func_0203c634(node, 1, func_ov169_020cde20);
            break;
        case 0xe:
            func_0203c634(node, 1, func_ov169_020ce034);
            break;
        case 3:
            func_0203c634(node, 1, func_ov169_020cdf48);
            break;
        }
    }
    ((struct AiState *)(*state))->pendingAction = -1;
}
