/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c6];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
    unsigned char pad1c8[0x1c8];
    int field_390;                /* 0x390 */
};

extern void func_0203c634(int *self, int idx, void *cb);
extern void func_ov277_020d2330(void);
extern void func_ov277_020d2074(void);
extern void func_ov277_020d2270(void);

struct hw60 { unsigned short lo : 8, hi : 8; };
struct b8 { unsigned int f : 8; };

void func_ov277_020d1f98(int *self) {
    int *s = (int *)self[1];
    int zero = 0;
    ((struct AiState *)(*s))->currentAction = zero;
    ((struct AiState *)(*s))->pendingAction = zero - 1;
    ((struct b8 *)(*(int *)(*s + 0x388) + 8))->f &= ~1;
    s[1] = *s + 0xb0;
    s[2] = *s + 0x74;
    s[3] = *(int *)(*s + 0x384) + 0xad;
    ((struct AiState *)(*s))->field_390 = 1;
    ((struct hw60 *)(*s + 0x60))->hi |= (unsigned char)6;
    func_0203c634(self, 1, (void *)&func_ov277_020d2330);
    func_0203c634(self, 0, (void *)&func_ov277_020d2074);
    func_0203c634(self, 2, (void *)&func_ov277_020d2270);
}
