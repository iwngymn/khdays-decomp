/* Raise the "alert" pose (hw60 high-byte bit 0x80) and register the alert think callback, but only
 * while the flag at *node[2] is clear. */
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x60];
    unsigned short flags60;       /* 0x060 */
};

extern void func_0203c634(int self, int idx, void *cb);
extern void func_ov213_020ceb7c(void);

void func_ov213_020ceb2c(int param_1) {
    int *node = *(int **)(param_1 + 4);
    unsigned short hw60;
    if (*(unsigned char *)node[2] != 0) {
        return;
    }
    hw60 = ((struct AiState *)(*node))->flags60;
    ((struct AiState *)(*node))->flags60 =
        (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 0x80) << 0x18) >> 0x10);
    func_0203c634(param_1, *(signed char *)((char *)param_1 + 0x20), &func_ov213_020ceb7c);
}
