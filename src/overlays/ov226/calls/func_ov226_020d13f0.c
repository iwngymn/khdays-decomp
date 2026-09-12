/* c634 init: reset owner status bytes (+0x1c6=0, +0x1c7=-1, +0x40c=-1), clear bit0 of the
 * low byte at each of the 5 sub-objects (owner+0x3ac[i]+8), cache the owner's pos pointer
 * (owner+0xb0) into obj[2] and its parent's pos (*(owner+0x3b0)->+0x20) into obj[3], set
 * owner hw60 hi bits 6, then arm the three phase callbacks (slots 1/0/2) via func_0203c634. */
struct b8 { unsigned int b : 8; };
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x60];
    unsigned short flags60;       /* 0x060 */
    unsigned char pad062[0x164];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

extern void func_0203c634(int self, int index, void *cb);
extern void func_ov226_020d1b84(void);
extern void func_ov226_020d14d8(void);
extern void func_ov226_020d17fc(void);
void func_ov226_020d13f0(int self) {
    int *obj = *(int **)(self + 4);
    int i = 0;
    ((struct AiState *)(*obj))->currentAction = 0;
    ((struct AiState *)(*obj))->pendingAction = -1;
    *(char *)(*obj + 0x40c) = -1;
    do {
        int e = ((int *)*obj)[i + 0xeb];
        i++;
        ((struct b8 *)(e + 8))->b &= ~1;
    } while (i < 5);
    obj[2] = *obj + 0xb0;
    obj[3] = **(int **)(*obj + 0x3b0) + 0x20;
    {
        unsigned short v = ((struct AiState *)(*obj))->flags60;
        ((struct AiState *)(*obj))->flags60 =
            (unsigned short)((v & ~0xff00) | (((((unsigned int)v << 0x10) >> 0x18 | 6) << 0x18) >> 0x10));
    }
    func_0203c634(self, 1, &func_ov226_020d1b84);
    func_0203c634(self, 0, &func_ov226_020d14d8);
    func_0203c634(self, 2, &func_ov226_020d17fc);
}
