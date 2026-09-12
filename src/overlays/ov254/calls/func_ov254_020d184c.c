/* Commit the guard reaction: raise both "guarding" bits (+0x1ae |= 3), set hw60 high-byte bit
 * pair 0xc (guard pose), and re-register the think callback. */
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x60];
    unsigned short flags60;       /* 0x060 */
    unsigned char pad062[0x14c];
    unsigned short flags1ae;      /* 0x1ae */
};

extern void func_0203c634(int self, int idx, int cb);

void func_ov254_020d184c(int param_1) {
    int *node = *(int **)(param_1 + 4);
    unsigned short hw60;
    ((struct AiState *)(*node))->flags1ae |= 3;
    hw60 = ((struct AiState *)(*node))->flags60;
    ((struct AiState *)(*node))->flags60 =
        (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 0xc) << 0x18) >> 0x10);
    func_0203c634(param_1, *(signed char *)((char *)param_1 + 0x20), 0);
}
