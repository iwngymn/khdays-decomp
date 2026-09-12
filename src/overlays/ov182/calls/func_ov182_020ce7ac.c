/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c6];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
    unsigned char pad1c8[0x1cc];
    int field_394;                /* 0x394 */
};

extern void func_0203c634(int *self, int idx, void *cb);
extern void func_ov182_020ceb34(void);
extern void func_ov182_020ce888(void);
extern void func_ov182_020cea80(void);

struct hw60 { unsigned short lo : 8, hi : 8; };
struct b8 { unsigned int f : 8; };

void func_ov182_020ce7ac(int *self) {
    int *s = (int *)self[1];
    int zero = 0;
    ((struct AiState *)(*s))->currentAction = zero;
    ((struct AiState *)(*s))->pendingAction = zero - 1;
    ((struct b8 *)(*(int *)(*s + 0x388) + 8))->f &= ~1;
    s[1] = *s + 0xb0;
    s[2] = *s + 0x74;
    s[3] = *(int *)(*s + 0x384) + 0xad;
    ((struct AiState *)(*s))->field_394 = 1;
    ((struct hw60 *)(*s + 0x60))->hi |= (unsigned char)6;
    func_0203c634(self, 1, (void *)&func_ov182_020ceb34);
    func_0203c634(self, 0, (void *)&func_ov182_020ce888);
    func_0203c634(self, 2, (void *)&func_ov182_020cea80);
}
