struct bf { unsigned b : 8; };
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1ae];
    unsigned short flags1ae;      /* 0x1ae */
    unsigned char pad1b0[0x1e0];
    int field_390;                /* 0x390 */
};

extern int func_ov107_020cab14();
extern void VEC_Subtract();
extern int func_020050b4();
extern void func_ov107_020c9264();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov277_020d24a8(void);
void func_ov277_020d23e0(int *node) {
    int *state = (int *)node[1];
    int t = func_ov107_020cab14(*state, 0);
    state[4] = t;
    if (t != 0) {
        int buf[3];
        int a;
        VEC_Subtract(t + 0x190, state[1], buf);
        a = func_020050b4(buf[0], buf[2]);
        state[6] = a;
        state[5] = a;
    }
    func_ov107_020c9264(*state, 0, 0);
    ((struct AiState *)(*state))->field_390 = 1;
    ((struct AiState *)(*state))->flags1ae |= 1;
    ((struct bf *)(*(int *)(*state + 0x388) + 8))->b &= ~1;
    state[17] = 0;
    func_0203c634(node, *(signed char *)(node + 8), func_ov277_020d24a8);
}
