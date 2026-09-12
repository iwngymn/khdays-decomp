/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x60];
    unsigned short flags60;       /* 0x060 */
};

void func_ov290_020cbfc4(char *p) {
    *(int *)(p + 0x70) = 0x800;
    *(int *)(p + 0x64) = 0;
    *(int *)(p + 0x68) = 0x800;
    *(int *)(p + 0x6c) = 0;
    {
        unsigned int v = ((struct AiState *)(p))->flags60;
        unsigned int hi = ((v << 16) >> 24) | 6;
        v &= ~0xff00u;
        ((struct AiState *)(p))->flags60 = v | ((hi << 24) >> 16);
    }
}
