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
extern void func_ov192_020d2b94(void);
extern void func_ov192_020d2c60(void);
extern void func_ov192_020d2e7c(void);
extern void func_ov192_020d2ff4(void);
extern void func_ov192_020d32b0(void);
extern void func_ov192_020d3340(void);
extern void func_ov192_020d3430(void);
extern void func_ov192_020d350c(void);

void func_ov192_020d28f4(int *node) {
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
            func_0203c634(node, 1, func_ov192_020d2b94);
            break;
        case 1:
            func_0203c634(node, 1, func_ov192_020d2c60);
            break;
        case 2:
            func_0203c634(node, 1, func_ov192_020d2e7c);
            break;
        case 4:
            func_0203c634(node, 1, func_ov192_020d2ff4);
            break;
        case 5:
            func_0203c634(node, 1, func_ov192_020d32b0);
            break;
        case 3:
            func_0203c634(node, 1, func_ov192_020d3340);
            break;
        case 7:
            func_0203c634(node, 1, func_ov192_020d3430);
            break;
        case 6:
            func_0203c634(node, 1, func_ov192_020d350c);
            break;
        }
    ((struct AiState *)(*state))->pendingAction = -1;
}
