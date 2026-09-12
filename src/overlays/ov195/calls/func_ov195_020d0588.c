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
extern void func_ov195_020d086c(void);
extern void func_ov195_020d0918(void);
extern void func_ov195_020d0b0c(void);
extern void func_ov195_020d0e60(void);
extern void func_ov195_020d0f58(void);
extern void func_ov195_020d1350(void);
extern void func_ov195_020d1418(void);
extern void func_ov195_020d191c(void);
extern void func_ov195_020d1e08(void);
extern void func_ov195_020d1f3c(void);
extern void func_ov195_020d1ff0(void);
extern void func_ov195_020d21b0(void);
extern void func_ov195_020d2370(void);
extern void func_ov195_020d243c(void);
extern void func_ov195_020d2508(void);
extern void func_ov195_020d25f4(void);

void func_ov195_020d0588(int *node) {
    int *state = (int *)node[1];
    int c = ((struct AiState *)(*state))->pendingAction;
    if (c != -1) {
        ((struct AiState *)(*state))->currentAction = (signed char)c;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        ((struct AiState *)(*state))->flags1ae &= ~1;
        ((struct bf *)(*(int *)(*state + 0x38c) + 8))->b |= 1;
        switch (((struct AiState *)(*state))->currentAction) {
        case 0: func_0203c634(node, 1, func_ov195_020d086c); break;
        case 1: func_0203c634(node, 1, func_ov195_020d0918); break;
        case 2: func_0203c634(node, 1, func_ov195_020d0b0c); break;
        case 5: func_0203c634(node, 1, func_ov195_020d0e60); break;
        case 4: func_0203c634(node, 1, func_ov195_020d0f58); break;
        case 3: func_0203c634(node, 1, func_ov195_020d1350); break;
        case 6: func_0203c634(node, 1, func_ov195_020d1418); break;
        case 7: func_0203c634(node, 1, func_ov195_020d191c); break;
        case 8: func_0203c634(node, 1, func_ov195_020d1e08); break;
        case 9: func_0203c634(node, 1, func_ov195_020d1f3c); break;
        case 10: func_0203c634(node, 1, func_ov195_020d1ff0); break;
        case 11: func_0203c634(node, 1, func_ov195_020d21b0); break;
        case 12: func_0203c634(node, 1, func_ov195_020d2370); break;
        case 13: func_0203c634(node, 1, func_ov195_020d243c); break;
        case 14: func_0203c634(node, 1, func_ov195_020d2508); break;
        case 15: func_0203c634(node, 1, func_ov195_020d25f4); break;
        }
    }
    ((struct AiState *)(*state))->pendingAction = -1;
}
