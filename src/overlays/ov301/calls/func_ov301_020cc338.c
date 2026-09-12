/* ov301 enemy state-enter handler (288B). Latches the pending sub-state byte
 * (+0x1c7 -> +0x1c6), adjusts the +0x60 flag byte (clear 0xc6, set 0x40), clears
 * the two low bits of +0x1ae, marks +0x388->+8, then dispatches the matching slot.
 * MATCHED byte-exact. The +0x60 high-byte ops read/modify/write the halfword: the
 * clear is a plain bitfield &=; the set uses an explicit barrel-shift reinsert
 * (t<<24)>>16 because the bitfield |= path emits a redundant width-mask mwcc's
 * original codegen omits here. */
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x60];
    unsigned short flags60;       /* 0x060 */
    unsigned char pad062[0x14c];
    unsigned short flags1ae;      /* 0x1ae */
    unsigned char pad1b0[0x16];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

extern void func_0203c634(int a, int b, int slot);
extern int func_ov301_020cc63c, func_ov301_020cc6f8, func_ov301_020cc6fc;

struct hw { unsigned short lo : 8, hi : 8; };   /* the flag halfword at obj+0x60 */
struct wd { unsigned b : 8, rest : 24; };       /* the low byte of *(obj+0x388)+8 */

void func_ov301_020cc338(int param_1) {
    int *pp = *(int **)(param_1 + 4);
    unsigned int t;
    signed char c = ((struct AiState *)(*pp))->pendingAction;
    if (c != -1) {
        ((struct AiState *)(*pp))->currentAction = c;
        ((struct hw *)(*pp + 0x60))->hi &= ~0xc6;
        ((struct AiState *)(*pp))->flags1ae &= ~3;
        ((struct wd *)(*(int *)(*pp + 0x388) + 8))->b |= 1;
        t = ((unsigned)((struct AiState *)(*pp))->flags60 << 16) >> 24;
        t |= 0x40;
        ((struct AiState *)(*pp))->flags60 =
            (((struct AiState *)(*pp))->flags60 & ~0xff00) | ((t << 24) >> 16);
        switch (((struct AiState *)(*pp))->currentAction) {
        case 0:
            func_0203c634(param_1, 1, (int)&func_ov301_020cc63c);
            break;
        case 2:
            func_0203c634(param_1, 1, (int)&func_ov301_020cc6f8);
            break;
        case 3:
            func_0203c634(param_1, 1, (int)&func_ov301_020cc6fc);
            break;
        }
    }
    ((struct AiState *)(*pp))->pendingAction = 0xff;
}
