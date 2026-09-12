/* func_ov232_020d0d58 -- enter the state: reset the move slots, cache three sub-object pointers,
 * roll the cooldown, then register the three per-slot handlers.
 *
 * ctx[0]+0x1c6 is cleared and +0x1c7 set to -1 ("no move chosen"); bit 0 of the byte field at
 * target+8 is cleared. The cached pointers are ctx[0]+0xb0, ctx[0]+0x74 and
 * *(ctx[0]+0x384)+0xad.
 *
 * The cooldown at +0x24 is rolled into [lo, lo + |hi - lo|] from the ctx[0]+0x224/+0x228 pair --
 * the same idiom func_ov228_020cf150 uses.
 *
 * Two bit-twiddles here are written the way the ROM's shape demands (see codegen-cracks.md):
 *   - target+8 is a byte-in-word field, so `struct { unsigned f : 8; }` + `&= ~1`;
 *   - the hw60 hi-byte |= 6 has NO `lsl#0x10 ; lsr#0x10` trunc pair in the ROM, so it needs the
 *     explicit extract/reassemble rather than the bitfield form -- and the lo-byte keep must be
 *     `v & ~0xff00` (bic), not `v & 0xff` (and). */

typedef struct {
    unsigned f : 8;
} B8;

/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x60];
    unsigned short flags60;       /* 0x060 */
    unsigned char pad062[0x165];
    signed char pendingAction;    /* 0x1c7 */
    unsigned char pad1c8[0x5c];
    int field_224;                /* 0x224 */
    int field_228;                /* 0x228 */
};

extern int func_02023eb4(int n);
extern void func_0203c634(int self, int slot, void (*cb)(void));
extern void func_ov232_020d0e54(void);
extern void func_ov232_020d0ef4(void);
extern void func_ov232_020d1150(void);

void func_ov232_020d0d58(int self) {
    int *ctx;
    int lo;
    int spread;
    unsigned short v;

    ctx = *(int **)(self + 4);
    *(unsigned char *)(ctx[0] + 0x1c6) = 0;
    ((struct AiState *)(ctx[0]))->pendingAction = -1;
    ((B8 *)(*(int *)(ctx[0] + 0x3bc) + 8))->f &= ~1;

    ctx[2] = ctx[0] + 0xb0;
    ctx[3] = ctx[0] + 0x74;
    ctx[4] = *(int *)(ctx[0] + 0x384) + 0xad;

    lo = ((struct AiState *)(ctx[0]))->field_224;
    spread = ((struct AiState *)(ctx[0]))->field_228 - lo;
    if (spread < 0) {
        spread = -spread;
    }
    ctx[9] = lo + func_02023eb4(spread + 1);

    v = ((struct AiState *)(ctx[0]))->flags60;
    ((struct AiState *)(ctx[0]))->flags60 =
        (unsigned short)((v & ~0xff00)
                         | (((((unsigned int)v << 0x10) >> 0x18 | 6) << 0x18) >> 0x10));

    func_0203c634(self, 1, func_ov232_020d0e54);
    func_0203c634(self, 0, func_ov232_020d0ef4);
    func_0203c634(self, 2, func_ov232_020d1150);
}
