/* Raises bit 1 of the flag word at +0x5c of each of the four sub-objects listed at +0x3a4.
 *
 * The list access must be an ARRAY INDEX with the 0x3a4 folded into it (0x3a4/4 = 0xe9);
 * written as `base + i * 4 + 0x3a4` mwcc builds a second byte-offset induction variable
 * instead of the ROM's `add r0, r0, r3, lsl #2`. */
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x5c];
    int flags5c;                  /* 0x05c */
};

void func_ov257_020d2bf0(char *self) {
    char *ctx = *(char **)(self + 4);
    int i = 0;
    char *o;
    do {
        o = ((char **)*(char **)ctx)[i + 0xe9];
        i = i + 1;
        ((struct AiState *)(o))->flags5c = ((struct AiState *)(o))->flags5c | 2;
    } while (i < 4);
}
