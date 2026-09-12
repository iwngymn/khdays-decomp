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
extern void func_ov284_020cca5c(void);
extern void func_ov284_020ccad8(void);
extern void func_ov284_020ccba0(void);
extern void func_ov284_020ccc9c(void);
extern void func_ov284_020cd080(void);
extern void func_ov284_020cd178(void);
extern void func_ov284_020cd21c(void);

void func_ov284_020cc86c(int *node) {
    int *state = (int *)node[1];
    int c = ((struct AiState *)(*state))->pendingAction;
    if (c != -1) {
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xca;
        ((struct AiState *)(*state))->flags1ae &= ~0x1;
        ((struct bf *)(*(int *)(*state + 0x3a8) + 8))->b &= ~1;
        ((struct AiState *)(*state))->currentAction = ((struct AiState *)(*state))->pendingAction;
        switch (((struct AiState *)(*state))->currentAction) {
        case 0:
            func_0203c634(node, 1, func_ov284_020cca5c);
            break;
        case 1:
            func_0203c634(node, 1, func_ov284_020ccad8);
            break;
        case 2:
            func_0203c634(node, 1, func_ov284_020ccba0);
            break;
        case 7:
            func_0203c634(node, 1, func_ov284_020ccc9c);
            break;
        case 3:
            func_0203c634(node, 1, func_ov284_020cd080);
            break;
        case 8:
            func_0203c634(node, 1, func_ov284_020cd178);
            break;
        case 9:
            func_0203c634(node, 1, func_ov284_020cd21c);
            break;
        }
    }
    ((struct AiState *)(*state))->pendingAction = -1;
}
