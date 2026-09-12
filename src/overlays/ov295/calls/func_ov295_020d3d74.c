/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x60];
    unsigned short flags60;       /* 0x060 */
};

extern void func_0203c634();
extern void func_ov295_020d3db4(void);
void func_ov295_020d3d74(int node) {
    int *s = *(int **)(node + 4);
    unsigned int h = ((struct AiState *)(*s))->flags60;
    ((struct AiState *)(*s))->flags60 = (h & ~0xff00) | (((((h << 0x10) >> 0x18) | 0xde) << 0x18) >> 0x10);
    func_0203c634(node, *(signed char *)(node + 0x20), func_ov295_020d3db4);
}
