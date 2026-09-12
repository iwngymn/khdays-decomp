/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c7];
    signed char pendingAction;    /* 0x1c7 */
    unsigned char pad1c8[0x5c];
    int field_224;                /* 0x224 */
    int field_228;                /* 0x228 */
};

extern void func_ov183_020d0344(int a, int b, int c);
extern int func_02023eb4(int range);
extern void func_0203c634(int *self, int idx, void *cb);

void func_ov183_020d1a34(int *self) {
    int *p = (int *)self[0];
    int *s = (int *)self[1];
    int t = s[7] + p[0xb];
    s[7] = t;
    if (t >= 0x555 && t < 0x800 && *(unsigned char *)((char *)s + 0x50) == 0) {
        *(unsigned char *)((char *)s + 0x50) = 1;
        func_ov183_020d0344((int)s, 0, 1);
    }
    if (*(unsigned char *)s[3] != 0) return;
    {
        int lo = ((struct AiState *)(s[0]))->field_224;
        int d = ((struct AiState *)(s[0]))->field_228 - lo;
        if (d < 0) d = -d;
        s[0x1d] = lo + func_02023eb4(d + 1);
    }
    ((struct AiState *)(s[0]))->pendingAction = 2;
    func_0203c634(self, *(signed char *)((char *)self + 0x20), 0);
}
