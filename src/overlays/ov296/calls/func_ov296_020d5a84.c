struct bf { unsigned b : 8; };
struct st1c6 { signed char _pad[0x1c6]; signed char sub; };
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
extern void func_ov296_020d5b94(void);
extern void func_ov296_020d5c48(void);
extern void func_ov296_020d6094(void);

void func_ov296_020d5a84(int *node) {
    int *state = (int *)node[1];
    int c = ((struct AiState *)(*state))->pendingAction;
    if (c != -1) {
        ((struct hw60 *)(*state + 0x60))->hi &= ~0x8a;
        ((struct AiState *)(*state))->flags1ae &= ~0x1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b &= ~1;
        ((struct AiState *)(*state))->currentAction = ((struct AiState *)(*state))->pendingAction;
        switch (((struct AiState *)(*state))->currentAction) {
        case 0:
            func_0203c634(node, 1, func_ov296_020d5b94);
            break;
        case 1:
            ((struct st1c6 *)*state)->sub = 2;
            /* fall through */
        case 2:
            func_0203c634(node, 1, func_ov296_020d5c48);
            break;
        case 3:
            func_0203c634(node, 1, func_ov296_020d6094);
            break;
        }
    }
    ((struct AiState *)(*state))->pendingAction = -1;
}
