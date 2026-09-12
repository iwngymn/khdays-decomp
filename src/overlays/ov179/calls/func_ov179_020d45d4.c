/* Flip the stance flags: drop bit 0 of the hw60 high byte and then set 0x82 in it, and hand off.
 *
 * Matched byte-exact 2026-07-23, first compile. The AND is the `hi &= ~K` bitfield (it carries
 * the ROM's 16-bit truncation) and the OR is the explicit shift expression (it does not).
 *
 * One of three byte-identical siblings. */
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x60];
    unsigned short flags60;       /* 0x060 */
};

extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov179_020d4640(void);

struct hw60 { unsigned short lo : 8, hi : 8; };

void func_ov179_020d45d4(int *node) {
    int *state = (int *)node[1];

    ((struct hw60 *)(state[0] + 0x60))->hi &= ~1;
    {
        unsigned short hw60 = ((struct AiState *)(state[0]))->flags60;
        ((struct AiState *)(state[0]))->flags60 =
            (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 0x82) << 0x18) >> 0x10);
    }
    func_0203c634(node, *(signed char *)((int)node + 0x20), func_ov179_020d4640);
}
