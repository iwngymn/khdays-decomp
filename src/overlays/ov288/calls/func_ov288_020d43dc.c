/* Enter the guard-break stance: set 0x80 in the hw60 high byte, raise bit 0 of the flags at
 * +0x1ae, clear bit 0 of the status word at +8 of the component at +0x388, zero the field at
 * +0x394, aim effect 1 at the vector held in state[3] and start event 0x15b anchored on the
 * object's own transform, then clear the travel accumulator.
 *
 * Matched byte-exact 2026-07-23, first compile. The aim vector is passed BY VALUE: mwcc builds
 * it just below sp, which is exactly the ROM's `sub r3,sp,#8 / ldm / stm`.
 *
 * One of three byte-identical siblings. */
typedef struct { int x, y, z; } VecFx32;

/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x60];
    unsigned short flags60;       /* 0x060 */
    unsigned char pad062[0x14c];
    unsigned short flags1ae;      /* 0x1ae */
    unsigned char pad1b0[0x1e4];
    int field_394;                /* 0x394 */
};

extern void func_ov107_020c0b90(int obj, int a, VecFx32 v, int d);
extern void func_ov107_020c5af8(int obj, int a, int b, int c);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov288_020d44b8(void);

struct LowByte32 { unsigned bits : 8; };

void func_ov288_020d43dc(int *node) {
    int *state = (int *)node[1];

    {
        unsigned short hw60 = ((struct AiState *)(state[0]))->flags60;
        ((struct AiState *)(state[0]))->flags60 =
            (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 0x80) << 0x18) >> 0x10);
    }
    ((struct AiState *)(state[0]))->flags1ae |= 1;
    ((struct LowByte32 *)(*(int *)(state[0] + 0x388) + 8))->bits &= ~1;
    ((struct AiState *)(state[0]))->field_394 = 0;
    func_ov107_020c0b90(state[0], 1, *(VecFx32 *)state[3], 0);
    func_ov107_020c5af8(state[0], 0x15b, 6, state[0] + 0x74);
    state[0xd] = 0;
    func_0203c634(node, *(signed char *)((int)node + 0x20), func_ov288_020d44b8);
}
