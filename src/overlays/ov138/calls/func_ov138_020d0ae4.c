/* c634 handler: set owner hw60 hi bits 0x86, clear bit0 of the low byte at *(owner+0x384)+8,
 * and dispatch via func_0203c634. */
struct b8 { unsigned int b : 8; };
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x60];
    unsigned short flags60;       /* 0x060 */
};

extern void func_0203c634(int self, int index, void *cb);
extern void func_ov138_020d0b4c(void);
void func_ov138_020d0ae4(int self) {
    int *obj = *(int **)(self + 4);
    {
        unsigned short v = ((struct AiState *)(*obj))->flags60;
        ((struct AiState *)(*obj))->flags60 =
            (unsigned short)((v & ~0xff00) | (((((unsigned int)v << 0x10) >> 0x18 | 0x86) << 0x18) >> 0x10));
    }
    ((struct b8 *)(*(int *)(*obj + 0x384) + 8))->b &= ~1;
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov138_020d0b4c);
}
