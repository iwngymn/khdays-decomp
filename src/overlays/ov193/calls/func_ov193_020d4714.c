struct bf { unsigned b : 8; };
struct st1c7 { signed char _pad[0x1c7]; signed char sub; };
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
extern void func_ov193_020d49b4(void);
extern void func_ov193_020d4a80(void);
extern void func_ov193_020d4c9c(void);
extern void func_ov193_020d4e14(void);
extern void func_ov193_020d50d0(void);
extern void func_ov193_020d5160(void);
extern void func_ov193_020d5250(void);
extern void func_ov193_020d532c(void);

void func_ov193_020d4714(int *node) {
    int *state = (int *)node[1];
    if (*(unsigned char *)(*state + 0x1c4) & 2) {
        if (*(short *)(*state + 0x21a) > 0 &&
            ((struct AiState *)(*state))->currentAction != 3 &&
            *(signed char *)(*state + 0x1c8) != 3 &&
            ((struct AiState *)(*state))->pendingAction != 3) {
            ((struct st1c7 *)*state)->sub = 5;
        } else {
            *(unsigned char *)(*state + 0x1c4) ^= 2;
            ((struct AiState *)(*state))->pendingAction = 3;
        }
    }
    int c = ((struct AiState *)(*state))->pendingAction;
    if (c == -1) return;
        ((struct AiState *)(*state))->currentAction = (signed char)c;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xc6;
        ((struct AiState *)(*state))->flags1ae &= ~0x1;
        ((struct bf *)(*(int *)(*state + 0x38c) + 8))->b |= 0x1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 0x1;
        switch (((struct AiState *)(*state))->currentAction) {
        case 0:
            func_0203c634(node, 1, func_ov193_020d49b4);
            break;
        case 1:
            func_0203c634(node, 1, func_ov193_020d4a80);
            break;
        case 2:
            func_0203c634(node, 1, func_ov193_020d4c9c);
            break;
        case 4:
            func_0203c634(node, 1, func_ov193_020d4e14);
            break;
        case 5:
            func_0203c634(node, 1, func_ov193_020d50d0);
            break;
        case 3:
            func_0203c634(node, 1, func_ov193_020d5160);
            break;
        case 7:
            func_0203c634(node, 1, func_ov193_020d5250);
            break;
        case 6:
            func_0203c634(node, 1, func_ov193_020d532c);
            break;
        }
    ((struct AiState *)(*state))->pendingAction = -1;
}
