/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x60];
    unsigned short flags60;       /* 0x060 */
};

extern void func_0203c634(int, int, void *);
extern void func_ov131_020ccf94(void);

struct flagword { unsigned f8 : 8; };

void func_ov131_020ccf2c(int param_1) {
    void *cb = func_ov131_020ccf94;
    int *node = *(int **)(param_1 + 4);
    int obj = *node;
    unsigned short h = ((struct AiState *)(obj))->flags60;

    ((struct AiState *)(obj))->flags60 =
        h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 0x86) << 0x18) >> 0x10);
    ((struct flagword *)(*(int *)(*node + 0x388) + 8))->f8 &= ~1;
    func_0203c634(param_1, *(char *)(param_1 + 0x20), cb);
}
