/* Point +0x18 at obj+0xb0, reset the sub-state (+0x1c6=0, +0x1c7=-1), clear bit0 of the hw60 hi
 * byte and +0x1ae, then hand off across the func_ov260_020d1d10 / func_ov260_020d1dc8 / func_ov260_020d1d88 trio. */
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1ae];
    unsigned short flags1ae;      /* 0x1ae */
    unsigned char pad1b0[0x17];
    signed char pendingAction;    /* 0x1c7 */
};

extern int func_0203c634(int, int, void *);
extern int func_ov260_020d1d10(int);
extern int func_ov260_020d1dc8(int);
extern int func_ov260_020d1d88(int);
struct hw60 { unsigned short lo : 8, hi : 8; };
void func_ov260_020d1c68(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(int *)(owner + 0x18) = *(int *)owner + 0xb0;
    *(unsigned char *)(*(int *)owner + 0x1c6) = 0;
    ((struct AiState *)(*(int *)owner))->pendingAction = -1;
    ((struct hw60 *)(*(int *)owner + 0x60))->hi &= ~1;
    ((struct AiState *)(*(int *)owner))->flags1ae &= ~1;
    func_0203c634(param_1, 0, (void *)&func_ov260_020d1d10);
    func_0203c634(param_1, 1, (void *)&func_ov260_020d1dc8);
    func_0203c634(param_1, 2, (void *)&func_ov260_020d1d88);
}
