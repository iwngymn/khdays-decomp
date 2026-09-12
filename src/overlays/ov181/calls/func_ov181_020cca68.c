struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1ae];
    unsigned short flags1ae;      /* 0x1ae */
    unsigned char pad1b0[0x16];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
    unsigned char pad1c8[0x1cc];
    int field_394;                /* 0x394 */
};

extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov181_020ccd14(void);
extern void func_ov181_020ccdc4(void);
extern void func_ov181_020ccf18(void);
extern void func_ov181_020cd1ac(void);
extern void func_ov181_020cd5ac(void);
extern void func_ov181_020cdb4c(void);
extern void func_ov181_020cdcd4(void);
extern void func_ov181_020cdda0(void);
extern void func_ov181_020cde9c(void);
extern void func_ov181_020ce150(void);
extern void func_ov181_020ce608(void);
extern void func_ov181_020ce838(void);
extern void func_ov181_020ce980(void);

void func_ov181_020cca68(int *node) {
    int *state = (int *)node[1];
    if (((struct AiState *)(*state))->pendingAction != -1) {
        ((struct AiState *)(*state))->flags1ae &= ~1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        ((struct AiState *)(*state))->field_394 = 0x1000;
        ((struct AiState *)(*state))->currentAction = ((struct AiState *)(*state))->pendingAction;
        switch (((struct AiState *)(*state))->currentAction) {
        case 0:
            func_0203c634(node, 1, func_ov181_020ccd14);
            break;
        case 1:
            func_0203c634(node, 1, func_ov181_020ccdc4);
            break;
        case 2:
            func_0203c634(node, 1, func_ov181_020ccf18);
            break;
        case 4:
            func_0203c634(node, 1, func_ov181_020cd1ac);
            break;
        case 5:
            func_0203c634(node, 1, func_ov181_020cd5ac);
            break;
        case 6:
            func_0203c634(node, 1, func_ov181_020cdb4c);
            break;
        case 3:
            func_0203c634(node, 1, func_ov181_020cdcd4);
            break;
        case 7:
            func_0203c634(node, 1, func_ov181_020cdda0);
            break;
        case 8:
            func_0203c634(node, 1, func_ov181_020cde9c);
            break;
        case 9:
            func_0203c634(node, 1, func_ov181_020ce150);
            break;
        case 0xa:
            func_0203c634(node, 1, func_ov181_020ce608);
            break;
        case 0xb:
            func_0203c634(node, 1, func_ov181_020ce838);
            break;
        case 0xc:
            func_0203c634(node, 1, func_ov181_020ce980);
            break;
        }
    }
    ((struct AiState *)(*state))->pendingAction = -1;
}
