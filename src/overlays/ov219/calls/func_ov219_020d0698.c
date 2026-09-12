/* All four forms from codegen-cracks.md: the -1 at +0x1c7 is a SIGNED char store, the
 * `&= ~1` at +8 is a byte BITFIELD, and the hw60 `hi |= 6` takes the EXPLICIT form. */
typedef struct { unsigned int lo : 8, rest : 24; } Byte8;
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x60];
    unsigned short flags60;       /* 0x060 */
    unsigned char pad062[0x164];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

extern void func_0203c634(int self, int index, void *cb);
extern void func_ov219_020d0a90(void);
extern void func_ov219_020d0750(void);
extern void func_ov219_020d092c(void);

void func_ov219_020d0698(int self) {
    int *obj = *(int **)(self + 4);
    unsigned short w;

    ((struct AiState *)(*obj))->currentAction = 0;
    ((struct AiState *)(*obj))->pendingAction = -1;
    ((Byte8 *)(*(int *)(*obj + 0x388) + 8))->lo &= ~1;
    obj[2] = *obj + 0xb0;
    w = ((struct AiState *)(*obj))->flags60;
    ((struct AiState *)(*obj))->flags60 =
        (unsigned short)((w & ~0xff00)
                         | (((((unsigned int)w << 0x10) >> 0x18 | 6) << 0x18) >> 0x10));
    func_0203c634(self, 1, &func_ov219_020d0a90);
    func_0203c634(self, 0, &func_ov219_020d0750);
    func_0203c634(self, 2, &func_ov219_020d092c);
}
