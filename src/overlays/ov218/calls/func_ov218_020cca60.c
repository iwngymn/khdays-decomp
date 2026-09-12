/* func_ov218_020cca60 -- ov218's move dispatcher. The plain family shape: -1 at ctx[0]+0x1c7 means
 * nothing queued, the id is copied to +0x1c6 and it is that copy the switch reads, and the slot is
 * cleared on every path.
 *
 * The reset drops 0xc6 from the hw60 hi-byte and bits 0-1 of the halfword at +0x1ae, then touches
 * the sub-object at ctx[0]+0x388 TWICE: bit 0 on, then bit 1 off. The two are separate read-modify
 * -write sequences in the ROM (each reloads ctx[0] and +0x388), so they stay separate expressions.
 *
 * Case 3 is out of order (after 7) as everywhere else, and 8 and 9 are swapped on top of that.
 *
 * Both the hw60 and the +8 writes carry the lsl/lsr trunc pair -> bitfield form. See
 * codegen-cracks.md. */

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
extern void func_ov218_020ccdbc(void);
extern void func_ov218_020cce68(void);
extern void func_ov218_020cce8c(void);
extern void func_ov218_020ccf04(void);
extern void func_ov218_020cd35c(void);
extern void func_ov218_020cd658(void);
extern void func_ov218_020cd7d4(void);
extern void func_ov218_020cd8c4(void);
extern void func_ov218_020cdc18(void);
extern void func_ov218_020cddf8(void);
extern void func_ov218_020cde24(void);
extern void func_ov218_020cded0(void);

void func_ov218_020cca60(int self) {
    int *ctx;

    ctx = *(int **)(self + 4);
    if (((struct AiState *)(ctx[0]))->pendingAction != -1) {
        ((struct AiState *)(ctx[0]))->currentAction = ((struct AiState *)(ctx[0]))->pendingAction;
        ((Hw60 *)(ctx[0] + 0x60))->hi &= ~0xc6;
        ((struct AiState *)(ctx[0]))->flags1ae &= ~3;
        ((B8 *)(*(int *)(ctx[0] + 0x388) + 8))->f |= 1;
        ((B8 *)(*(int *)(ctx[0] + 0x388) + 8))->f &= ~2;

        switch (((struct AiState *)(ctx[0]))->currentAction) {
        case 0:
            func_0203c634(self, 1, func_ov218_020ccdbc);
            break;
        case 1:
            func_0203c634(self, 1, func_ov218_020cce68);
            break;
        case 2:
            func_0203c634(self, 1, func_ov218_020cce8c);
            break;
        case 4:
            func_0203c634(self, 1, func_ov218_020ccf04);
            break;
        case 5:
            func_0203c634(self, 1, func_ov218_020cd35c);
            break;
        case 6:
            func_0203c634(self, 1, func_ov218_020cd658);
            break;
        case 7:
            func_0203c634(self, 1, func_ov218_020cd7d4);
            break;
        case 3:
            func_0203c634(self, 1, func_ov218_020cd8c4);
            break;
        case 9:
            func_0203c634(self, 1, func_ov218_020cdc18);
            break;
        case 8:
            func_0203c634(self, 1, func_ov218_020cddf8);
            break;
        case 10:
            func_0203c634(self, 1, func_ov218_020cde24);
            break;
        case 11:
            func_0203c634(self, 1, func_ov218_020cded0);
            break;
        }
    }

    ((struct AiState *)(ctx[0]))->pendingAction = -1;
}
