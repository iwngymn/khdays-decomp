/* Begin the recoil slide: flag the owner charging bit (*node+0x390), clear the hw60 high-byte
 * "grounded" bit 0x80, roll a random slide duration into node[2], and register the think callback. */
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x60];
    unsigned short flags60;       /* 0x060 */
    unsigned char pad062[0x32e];
    int field_390;                /* 0x390 */
};

extern int func_02023eb4();
extern void func_0203c634(int self, int idx, void *cb);
extern void func_ov273_020d65fc(void);

void func_ov273_020d6590(int param_1) {
    int *node = *(int **)(param_1 + 4);
    int v;
    unsigned short hw60;
    ((struct AiState *)(*node))->field_390 = 1;
    hw60 = ((struct AiState *)(*node))->flags60;
    ((struct AiState *)(*node))->flags60 =
        (hw60 & ~0xff00) | ((unsigned int)(unsigned short)(((unsigned int)hw60 << 0x10) >> 0x18 & 0xffffff7f) << 0x18 >> 0x10);
    node[2] = func_02023eb4(0x801) + (v - v);
    func_0203c634(param_1, *(signed char *)((char *)param_1 + 0x20), &func_ov273_020d65fc);
}
