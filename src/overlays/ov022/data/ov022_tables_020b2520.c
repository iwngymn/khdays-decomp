/* ov022 .rodata bit tables, 0x020b2520-0x020b2538.
 *
 * One entry per part of an action owner (see func_ov022_0209441c): the bit
 * that marks the part done in the owner's flag word, and the bit that marks
 * it wanted in the request mask. Both are structs rather than arrays so a
 * function can copy-initialise a stack copy from the named global.
 */

typedef unsigned int u32;

typedef struct {
    u32 nBit[3];
} Ov022PartBits;

/* done bits, one per part */
const Ov022PartBits data_ov022_020b2520 = {{ 0x04, 0x08, 0x10 }};

/* wanted bits, one per part */
const Ov022PartBits data_ov022_020b252c = {{ 0x01, 0x02, 0x04 }};
