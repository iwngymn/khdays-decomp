/* ⚠ `func_01ffa724(obj[8] = 0x500, dst, …)` -- the store is INSIDE the call argument.
 * That is what makes mwcc materialise 0x500 once into a scratch register and use it for
 * both the store and the argument, as the ROM does; a separate `obj[8] = 0x500;`
 * statement plus a literal argument is 4 B short, and so is a shared local.
 * `dst` is hoisted for the same reason. House form copied from ov137_020cee94. */
struct vec { int x, y, z; };
struct hw60 { unsigned short lo : 8, hi : 8; };
struct b8 { unsigned int b : 8, rest : 24; };
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x60];
    unsigned short flags60;       /* 0x060 */
};

extern void func_01ffa724(int scale, int *v, unsigned int *out);
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov154_020d0938(void);

void func_ov154_020d0868(int self) {
    int *obj = *(int **)(self + 4);
    int *dst = obj + 5;
    obj[9] = 0;
    {
        unsigned short v = ((struct AiState *)(*obj))->flags60;
        ((struct AiState *)(*obj))->flags60 =
            (unsigned short)((v & ~0xff00) | (((((unsigned int)v << 0x10) >> 0x18 | 1) << 0x18) >> 0x10));
    }
    ((struct hw60 *)(*obj + 0x60))->hi &= ~0x8c;
    ((struct b8 *)(*(int *)(*obj + 0x388) + 8))->b |= 1;
    *(struct vec *)(obj + 5) = *(struct vec *)(*obj + 0x394);
    func_01ffa724(obj[8] = 0x500, dst, (unsigned int *)(obj + 2));
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov154_020d0938);
}
