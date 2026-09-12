struct bf { unsigned b : 8; };
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1ae];
    unsigned short flags1ae;      /* 0x1ae */
    unsigned char pad1b0[0x1e4];
    int field_394;                /* 0x394 */
};

extern void func_ov107_020c9264(int node, int a, int b);
extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_0203c634();
extern void func_ov288_020d4c98(void);

void func_ov288_020d4bcc(int this_) {
    int holder = *(int *)(this_ + 4);
    func_ov107_020c9264(*(int *)holder, 3, 0);
    ((struct AiState *)(*(int *)holder))->flags1ae |= 0x10;
    ((struct bf *)(*(int *)(*(int *)holder + 0x388) + 8))->b &= ~1;
    ((struct AiState *)(*(int *)holder))->flags1ae |= 1;
    func_ov107_020c5af8(*(int *)holder, 0x15b,
                        (unsigned short)(*(int *)(*(int *)holder + 0x38c) == 0 ? 4 : 5),
                        *(int *)(holder + 0xc));
    ((struct AiState *)(*(int *)holder))->field_394 = 0;
    *(int *)(holder + 0x34) = 0;
    *(int *)(holder + 0x4c) = 0;
    *(int *)(holder + 0x50) = 0;
    *(signed char *)(holder + 0x54) = 0;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), (int)&func_ov288_020d4c98);
}
