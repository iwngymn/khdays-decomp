/* func_ov233_020cd5e8 -- the move dispatcher: play whatever move was queued at ctx[0]+0x1c7, then
 * clear the slot. This is the hub the whole ov228 state machine funnels through; the choosers
 * (func_ov228_020cf150, ...) park a move id here and this turns it into a c634 entry.
 *
 * -1 means nothing queued and the whole body is skipped -- but the slot is cleared either way,
 * which is why the early exit lands on the same store.
 *
 * Before dispatching, the id is copied to +0x1c6 (that copy, not the original, is what the switch
 * reads), the hw60 hi-byte is cleared of 0xc6, the halfword at +0x1ae drops bits 0-1, and bit 0
 * of the byte field at *(ctx[0]+0x3ac)+8 is set.
 *
 * The cases are dense 0..13, so mwcc builds a real jump table (`addls pc,pc,r1,lsl #2`). Case 3
 * is written out of order -- after case 11 -- because that is the block layout the ROM has; the
 * table is index-ordered but the blocks follow source order, so the position of case 3 is
 * observable. Do not tidy it into numeric order.
 *
 * The hw60 write HAS the `lsl#0x10 ; lsr#0x10` trunc pair, so it takes the bitfield form (see
 * codegen-cracks.md); the field at +8 is a byte-in-word, so it takes the `unsigned f : 8` form. */

typedef struct {
    unsigned short lo : 8;
    unsigned short hi : 8;
} Hw60;

typedef struct {
    unsigned f : 8;
} B8;

/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1ae];
    unsigned short flags1ae;      /* 0x1ae */
    unsigned char pad1b0[0x16];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

extern void func_0203c634(int self, int slot, void (*cb)(void));
extern void func_ov233_020cd97c(void);
extern void func_ov233_020cda70(void);
extern void func_ov233_020cdd7c(void);
extern void func_ov233_020cdf48(void);
extern void func_ov233_020ce44c(void);
extern void func_ov233_020cea64(void);
extern void func_ov233_020cee10(void);
extern void func_ov233_020cf0ac(void);
extern void func_ov233_020cf288(void);
extern void func_ov233_020cf57c(void);
extern void func_ov233_020cfba4(void);
extern void func_ov233_020cfd98(void);
extern void func_ov233_020cfe80(void);
extern void func_ov233_020cffdc(void);

void func_ov233_020cd5e8(int self) {
    int *ctx;
    int move;

    ctx = *(int **)(self + 4);
    move = ((struct AiState *)(ctx[0]))->pendingAction;
    if (move != -1) {
        ((struct AiState *)(ctx[0]))->currentAction = move;
        ((Hw60 *)(ctx[0] + 0x60))->hi &= ~0xc6;
        ((struct AiState *)(ctx[0]))->flags1ae &= ~3;
        ((B8 *)(*(int *)(ctx[0] + 0x3ac) + 8))->f |= 1;

        switch (((struct AiState *)(ctx[0]))->currentAction) {
        case 0:
            func_0203c634(self, 1, func_ov233_020cd97c);
            break;
        case 1:
            func_0203c634(self, 1, func_ov233_020cda70);
            break;
        case 2:
            func_0203c634(self, 1, func_ov233_020cdd7c);
            break;
        case 4:
            func_0203c634(self, 1, func_ov233_020cdf48);
            break;
        case 5:
            func_0203c634(self, 1, func_ov233_020ce44c);
            break;
        case 6:
            func_0203c634(self, 1, func_ov233_020cea64);
            break;
        case 7:
            func_0203c634(self, 1, func_ov233_020cee10);
            break;
        case 8:
            func_0203c634(self, 1, func_ov233_020cf0ac);
            break;
        case 9:
            func_0203c634(self, 1, func_ov233_020cf288);
            break;
        case 10:
            func_0203c634(self, 1, func_ov233_020cf57c);
            break;
        case 11:
            func_0203c634(self, 1, func_ov233_020cfba4);
            break;
        case 3:
            func_0203c634(self, 1, func_ov233_020cfd98);
            break;
        case 12:
            func_0203c634(self, 1, func_ov233_020cfe80);
            break;
        case 13:
            func_0203c634(self, 1, func_ov233_020cffdc);
            break;
        }
    }

    ((struct AiState *)(ctx[0]))->pendingAction = -1;
}
