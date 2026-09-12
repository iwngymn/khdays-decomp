/* Init the reaction: point (child)+8 at (*child)+0xb0, reset the sub-state bytes (+0x1c6=0,
 * +0x1c7=-1), clear flag 0 in the high byte at (*child)+0x60 and bit 0 of the halfword at
 * (*child)+0x1ae, then register the two phase handlers on slots 0 and 1. */
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1ae];
    unsigned short flags1ae;      /* 0x1ae */
    unsigned char pad1b0[0x16];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

extern int func_0203c634(int a, int b, void *handler);
extern void func_ov230_020d5ff4(int);
extern void func_ov230_020d606c(int);
struct node60_020d5f60 { unsigned short lo : 8; unsigned short hi : 8; };
void func_ov230_020d5f60(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(int *)(child + 8) = *(int *)child + 0xb0;
    ((struct AiState *)(*(int *)child))->currentAction = 0;
    ((struct AiState *)(*(int *)child))->pendingAction = -1;
    ((struct node60_020d5f60 *)(*(int *)child + 0x60))->hi &= ~1;
    ((struct AiState *)(*(int *)child))->flags1ae &= ~1;
    func_0203c634(param_1, 0, (void *)&func_ov230_020d5ff4);
    func_0203c634(param_1, 1, (void *)&func_ov230_020d606c);
}
