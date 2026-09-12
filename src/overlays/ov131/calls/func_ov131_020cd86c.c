/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x60];
    unsigned short flags60;       /* 0x060 */
};

extern void func_ov107_020c9ee8();
extern void func_ov107_020c9264();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov131_020cd8d8(void);

void func_ov131_020cd86c(char *obj) {
    int *state = *(int **)(obj + 4);
    unsigned int h = ((struct AiState *)(*state))->flags60;
    unsigned int masked = h & ~0xff00;
    ((struct AiState *)(*state))->flags60 =
        masked | (((((h << 0x10) >> 0x18) | 0x40) << 0x18) >> 0x10);
    func_ov107_020c9ee8(*(void **)(*state + 0x3c8), 0, 0, masked);
    func_ov107_020c9264(*state, 4, 0);
    func_0203c634(obj, *(signed char *)(obj + 0x20), func_ov131_020cd8d8);
}
