/* Setter: hand the caller's vector (param v) to func_ov107_020c5c54, store the second
 * triple (param_5..7) into owner fields +0x398/+0x39c/+0x3a0, and set owner hw60 hi bit 1. */
struct vec { int x, y, z; };
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x60];
    unsigned short flags60;       /* 0x060 */
};

extern void func_ov107_020c5c54(int owner, struct vec *v);
void func_ov229_020d5c34(int param_1, struct vec v, struct vec v2) {
    func_ov107_020c5c54(param_1, &v);
    *(struct vec *)(param_1 + 0x398) = v2;
    {
        unsigned short hv = ((struct AiState *)(param_1))->flags60;
        ((struct AiState *)(param_1))->flags60 =
            (unsigned short)((hv & ~0xff00) | (((((unsigned int)hv << 0x10) >> 0x18 | 1) << 0x18) >> 0x10));
    }
}
