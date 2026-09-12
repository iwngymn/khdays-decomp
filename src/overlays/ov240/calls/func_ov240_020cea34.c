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
extern void func_ov240_020cec88(void);
extern void func_ov240_020ced2c(void);
extern void func_ov240_020cee04(void);
extern void func_ov240_020cee7c(void);
extern void func_ov240_020cf004(void);
extern void func_ov240_020cf250(void);
extern void func_ov240_020cf424(void);
extern void func_ov240_020cf6e0(void);
extern void func_ov240_020cf7a8(void);
extern void func_ov240_020cf8c0(void);
extern void func_ov240_020cfa2c(void);

void func_ov240_020cea34(int *node) {
    int *state = (int *)node[1];
    int c = ((struct AiState *)(*state))->pendingAction;
    if (c != -1) {
        ((struct AiState *)(*state))->currentAction = (signed char)c;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xc6;
        ((struct AiState *)(*state))->flags1ae &= ~3;
        ((struct bf *)(*(int *)(*state + 0x38c) + 8))->b |= 1;
        switch (((struct AiState *)(*state))->currentAction) {
        case 0:
            func_0203c634(node, 1, func_ov240_020cec88);
            break;
        case 1:
            func_0203c634(node, 1, func_ov240_020ced2c);
            break;
        case 2:
            func_0203c634(node, 1, func_ov240_020cee04);
            break;
        case 4:
            func_0203c634(node, 1, func_ov240_020cee7c);
            break;
        case 5:
            func_0203c634(node, 1, func_ov240_020cf004);
            break;
        case 6:
            func_0203c634(node, 1, func_ov240_020cf250);
            break;
        case 7:
            func_0203c634(node, 1, func_ov240_020cf424);
            break;
        case 8:
            func_0203c634(node, 1, func_ov240_020cf6e0);
            break;
        case 3:
            func_0203c634(node, 1, func_ov240_020cf7a8);
            break;
        case 9:
            func_0203c634(node, 1, func_ov240_020cf8c0);
            break;
        case 0xa:
            func_0203c634(node, 1, func_ov240_020cfa2c);
            break;
        }
    }
    ((struct AiState *)(*state))->pendingAction = -1;
}
