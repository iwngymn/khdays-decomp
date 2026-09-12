/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x60];
    unsigned short flags60;       /* 0x060 */
};

extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov134_020ccba0(void);

struct hw60 { unsigned short lo : 8, hi : 8; };
struct LowByteFlags { unsigned bits : 8; };

void func_ov134_020ccb2c(int *node) {
    int *state = (int *)node[1];
    {
        unsigned short hw60 = ((struct AiState *)(*state))->flags60;
        ((struct AiState *)(*state))->flags60 =
            (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 0x86) << 0x18) >> 0x10);
    }
    ((struct LowByteFlags *)(*(int *)(*state + 0x38c) + 8))->bits &= ~1;
    *(unsigned char *)((char *)state + 0x42) &= ~1;
    func_0203c634(node, *(signed char *)(node + 8), func_ov134_020ccba0);
}
