struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1ae];
    unsigned short flags1ae;      /* 0x1ae */
    unsigned char pad1b0[0x16];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
    unsigned char pad1c8[0x1c8];
    int field_390;                /* 0x390 */
};

extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov114_020ccd24(void);
extern void func_ov114_020ccdd4(void);
extern void func_ov114_020ccf28(void);
extern void func_ov114_020cd114(void);
extern void func_ov114_020cd2b0(void);
extern void func_ov114_020cd37c(void);
extern void func_ov114_020cd77c(void);
extern void func_ov114_020cd8a8(void);
extern void func_ov114_020cda14(void);
extern void func_ov114_020cdb14(void);
extern void func_ov114_020cdda4(void);
extern void func_ov114_020cde70(void);
extern void func_ov114_020cdf3c(void);

void func_ov114_020cca68(int *node) {
    int *state = (int *)node[1];
    int c = ((struct AiState *)(*state))->pendingAction;
    if (c != -1) {
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        ((struct AiState *)(*state))->flags1ae &= ~0x1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 0x1;
        ((struct AiState *)(*state))->field_390 = 0x1000;
        ((struct AiState *)(*state))->currentAction = ((struct AiState *)(*state))->pendingAction;
        switch (((struct AiState *)(*state))->currentAction) {
        case 0:
            func_0203c634(node, 1, func_ov114_020ccd24);
            break;
        case 1:
            func_0203c634(node, 1, func_ov114_020ccdd4);
            break;
        case 2:
            func_0203c634(node, 1, func_ov114_020ccf28);
            break;
        case 4:
            func_0203c634(node, 1, func_ov114_020cd114);
            break;
        case 6:
            func_0203c634(node, 1, func_ov114_020cd2b0);
            break;
        case 7:
            func_0203c634(node, 1, func_ov114_020cd37c);
            break;
        case 8:
            func_0203c634(node, 1, func_ov114_020cd77c);
            break;
        case 5:
            func_0203c634(node, 1, func_ov114_020cd8a8);
            break;
        case 9:
            func_0203c634(node, 1, func_ov114_020cda14);
            break;
        case 0xa:
            func_0203c634(node, 1, func_ov114_020cdb14);
            break;
        case 3:
            func_0203c634(node, 1, func_ov114_020cdda4);
            break;
        case 0xb:
            func_0203c634(node, 1, func_ov114_020cde70);
            break;
        case 0xc:
            func_0203c634(node, 1, func_ov114_020cdf3c);
            break;
        }
    }
    ((struct AiState *)(*state))->pendingAction = -1;
}
