/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x60];
    unsigned short flags60;       /* 0x060 */
};

void func_ov107_020cafb4(int p, int q)
{
    if (*(unsigned char *)(q + 2) != 0)
        return;
    ((struct AiState *)(p))->flags60 = (((struct AiState *)(p))->flags60 & ~0xff) | *(unsigned char *)(q + 4);
}
