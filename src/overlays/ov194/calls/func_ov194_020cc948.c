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

extern void func_0203c634(void *node, int idx, void *value);
extern void func_ov194_020ccc2c(void);
extern void func_ov194_020cccd8(void);
extern void func_ov194_020ccecc(void);
extern void func_ov194_020cd220(void);
extern void func_ov194_020cd318(void);
extern void func_ov194_020cd710(void);
extern void func_ov194_020cd7d8(void);
extern void func_ov194_020cdcdc(void);
extern void func_ov194_020ce1c8(void);
extern void func_ov194_020ce2fc(void);
extern void func_ov194_020ce3b0(void);
extern void func_ov194_020ce570(void);
extern void func_ov194_020ce730(void);
extern void func_ov194_020ce7fc(void);
extern void func_ov194_020ce8c8(void);
extern void func_ov194_020ce9b4(void);

void func_ov194_020cc948(int *node) {
    int *state = (int *)node[1];
    int c = ((struct AiState *)(*state))->pendingAction;
    if (c != -1) {
        ((struct AiState *)(*state))->currentAction = (signed char)c;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        ((struct AiState *)(*state))->flags1ae &= ~1;
        ((struct bf *)(*(int *)(*state + 0x38c) + 8))->b |= 1;
        switch (((struct AiState *)(*state))->currentAction) {
        case 0: func_0203c634(node, 1, func_ov194_020ccc2c); break;
        case 1: func_0203c634(node, 1, func_ov194_020cccd8); break;
        case 2: func_0203c634(node, 1, func_ov194_020ccecc); break;
        case 5: func_0203c634(node, 1, func_ov194_020cd220); break;
        case 4: func_0203c634(node, 1, func_ov194_020cd318); break;
        case 3: func_0203c634(node, 1, func_ov194_020cd710); break;
        case 6: func_0203c634(node, 1, func_ov194_020cd7d8); break;
        case 7: func_0203c634(node, 1, func_ov194_020cdcdc); break;
        case 8: func_0203c634(node, 1, func_ov194_020ce1c8); break;
        case 9: func_0203c634(node, 1, func_ov194_020ce2fc); break;
        case 10: func_0203c634(node, 1, func_ov194_020ce3b0); break;
        case 11: func_0203c634(node, 1, func_ov194_020ce570); break;
        case 12: func_0203c634(node, 1, func_ov194_020ce730); break;
        case 13: func_0203c634(node, 1, func_ov194_020ce7fc); break;
        case 14: func_0203c634(node, 1, func_ov194_020ce8c8); break;
        case 15: func_0203c634(node, 1, func_ov194_020ce9b4); break;
        }
    }
    ((struct AiState *)(*state))->pendingAction = -1;
}
