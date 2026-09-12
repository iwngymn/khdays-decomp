/* Initialise a spawned child: point its +8 at obj+0xb0, reset state bytes
 * +0x1c6/+0x1c7, clear the low bit of its high-byte flags at +0x60 and of the u16
 * at +0x1ae, then run the 0/1/2 dispatch sequence. */
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1ae];
    unsigned short flags1ae;      /* 0x1ae */
    unsigned char pad1b0[0x16];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

extern int func_0203c634(int a, int b, void *handler);
extern void func_ov245_020cecd8(void);
extern void func_ov245_020ced68(void);
extern void func_ov245_020ced50(void);

struct hi_flags_020cfaac { unsigned short pad : 8; unsigned short flags : 8; };

void func_ov245_020cec30(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(int *)(child + 8) = *(int *)child + 0xb0;
    ((struct AiState *)(*(int *)child))->currentAction = 0;
    ((struct AiState *)(*(int *)child))->pendingAction = -1;
    ((struct hi_flags_020cfaac *)(*(int *)child + 0x60))->flags &= ~1;
    ((struct AiState *)(*(int *)child))->flags1ae &= ~1;
    func_0203c634(param_1, 0, (void *)&func_ov245_020cecd8);
    func_0203c634(param_1, 1, (void *)&func_ov245_020ced68);
    func_0203c634(param_1, 2, (void *)&func_ov245_020ced50);
}
