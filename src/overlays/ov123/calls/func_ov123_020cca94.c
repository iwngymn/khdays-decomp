/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x60];
    unsigned short flags60;       /* 0x060 */
    unsigned char pad062[0x14c];
    unsigned short flags1ae;      /* 0x1ae */
};

extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov123_020ccb34(void);

struct ov123_LowByteFlags { unsigned bits : 8; };

void func_ov123_020cca94(int *node) {
    int *state = (int *)node[1];

    {
        unsigned short hw60 = ((struct AiState *)(*state))->flags60;
        ((struct AiState *)(*state))->flags60 =
            (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 0x82) << 0x18) >> 0x10);
    }

    ((struct AiState *)(*state))->flags1ae |= 1;
    ((struct ov123_LowByteFlags *)(*(int *)(*state + 0x388) + 8))->bits &= ~1;
    func_ov107_020c5af8(*state, 0, 0x48, state[5]);
    state[10] = 0;
    func_0203c634(node, *(signed char *)(node + 8), func_ov123_020ccb34);
}
