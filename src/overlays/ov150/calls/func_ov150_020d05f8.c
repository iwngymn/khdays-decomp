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
extern void func_ov150_020d0820(void);
extern void func_ov150_020d08c4(void);
extern void func_ov150_020d0a5c(void);
extern void func_ov150_020d0b68(void);
extern void func_ov150_020d0ef4(void);
extern void func_ov150_020d126c(void);
extern void func_ov150_020d105c(void);
extern void func_ov150_020d11a4(void);
extern void func_ov150_020d14fc(void);

void func_ov150_020d05f8(int *node) {
    int *state = (int *)node[1];
    int c = ((struct AiState *)(*state))->pendingAction;
    if (c != -1) {
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        ((struct AiState *)(*state))->flags1ae &= ~0x41;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
        ((struct AiState *)(*state))->currentAction = ((struct AiState *)(*state))->pendingAction;
        switch (((struct AiState *)(*state))->currentAction) {
        case 0:
            func_0203c634(node, 1, func_ov150_020d0820);
            break;
        case 1:
            func_0203c634(node, 1, func_ov150_020d08c4);
            break;
        case 2:
            func_0203c634(node, 1, func_ov150_020d0a5c);
            break;
        case 4:
            func_0203c634(node, 1, func_ov150_020d0b68);
            break;
        case 5:
            func_0203c634(node, 1, func_ov150_020d0ef4);
            break;
        case 6:
            func_0203c634(node, 1, func_ov150_020d126c);
            break;
        case 7:
            func_0203c634(node, 1, func_ov150_020d105c);
            break;
        case 3:
            func_0203c634(node, 1, func_ov150_020d11a4);
            break;
        case 8:
            func_0203c634(node, 1, func_ov150_020d14fc);
            break;
        }
    }
    ((struct AiState *)(*state))->pendingAction = -1;
}
