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
extern void func_ov115_020cd4c8(void);
extern void func_ov115_020cd5b4(void);
extern void func_ov115_020cd78c(void);
extern void func_ov115_020cdbac(void);
extern void func_ov115_020cdde4(void);
extern void func_ov115_020cdfec(void);
extern void func_ov115_020ce5dc(void);
extern void func_ov115_020ce20c(void);
extern void func_ov115_020ce7bc(void);
extern void func_ov115_020ce7f0(void);
extern void func_ov115_020cea04(void);
extern void func_ov115_020ce918(void);

void func_ov115_020cd228(int *node) {
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
            func_0203c634(node, 1, func_ov115_020cd4c8);
            break;
        case 1:
            func_0203c634(node, 1, func_ov115_020cd5b4);
            break;
        case 2:
            func_0203c634(node, 1, func_ov115_020cd78c);
            break;
        case 4:
            func_0203c634(node, 1, func_ov115_020cdbac);
            break;
        case 5:
            func_0203c634(node, 1, func_ov115_020cdde4);
            break;
        case 6:
            func_0203c634(node, 1, func_ov115_020cdfec);
            break;
        case 8:
            func_0203c634(node, 1, func_ov115_020ce5dc);
            break;
        case 9:
            func_0203c634(node, 1, func_ov115_020ce20c);
            break;
        case 0xc:
            func_0203c634(node, 1, func_ov115_020ce7bc);
            break;
        case 0xd:
            func_0203c634(node, 1, func_ov115_020ce7f0);
            break;
        case 0xe:
            func_0203c634(node, 1, func_ov115_020cea04);
            break;
        case 3:
            func_0203c634(node, 1, func_ov115_020ce918);
            break;
        }
    }
    ((struct AiState *)(*state))->pendingAction = -1;
}
