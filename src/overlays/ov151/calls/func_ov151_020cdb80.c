// variant: popeq=False mirror_top=True
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
extern void func_ov151_020cdda0(void);
extern void func_ov151_020cde44(void);
extern void func_ov151_020ce008(void);
extern void func_ov151_020ce114(void);
extern void func_ov151_020ce4f0(void);
extern void func_ov151_020ce864(void);
extern void func_ov151_020ce658(void);
extern void func_ov151_020ce79c(void);
extern void func_ov151_020ceb2c(void);

void func_ov151_020cdb80(int *node) {
    int *state = (int *)node[1];
    int c = ((struct AiState *)(*state))->pendingAction;
    if (c != -1) {
        ((struct AiState *)(*state))->currentAction = (signed char)c;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        ((struct AiState *)(*state))->flags1ae &= ~0x41;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
        switch (((struct AiState *)(*state))->currentAction) {
        case 0:
            func_0203c634(node, 1, func_ov151_020cdda0);
            break;
        case 1:
            func_0203c634(node, 1, func_ov151_020cde44);
            break;
        case 2:
            func_0203c634(node, 1, func_ov151_020ce008);
            break;
        case 4:
            func_0203c634(node, 1, func_ov151_020ce114);
            break;
        case 5:
            func_0203c634(node, 1, func_ov151_020ce4f0);
            break;
        case 6:
            func_0203c634(node, 1, func_ov151_020ce864);
            break;
        case 7:
            func_0203c634(node, 1, func_ov151_020ce658);
            break;
        case 3:
            func_0203c634(node, 1, func_ov151_020ce79c);
            break;
        case 8:
            func_0203c634(node, 1, func_ov151_020ceb2c);
            break;
        }
    }
    ((struct AiState *)(*state))->pendingAction = -1;
}
