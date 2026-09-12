/*
 * func_ov271_020d07d0 -- x3 (ov200/201/271). Reset the aim/attack state and (re)arm three dispatch
 * slots. Clear the mode byte *(*state+0x1c6)=0 and set the "dirty" byte *(*state+0x1c7)=-1; clear bit 0
 * of the low byte at *(*state+0x388)+8; cache the two rig pointers state[0x12]=*state+0xb0 and
 * state[0x13]=*state+0x74; set hw60.hi |= 6. Load the identity quaternion into state[0x21..0x24] and
 * mirror it to state[0x25..0x28]. Pick a random target between *(*state+0x224) and *(*state+0x228)
 * into state[0x20]. Finally arm dispatch slots 1, 0 and 2 with their handlers via 0203c634.
 */
struct b8 { unsigned f : 8; };
struct q4 { int w[4]; };

/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c7];
    signed char pendingAction;    /* 0x1c7 */
    unsigned char pad1c8[0x5c];
    int field_224;                /* 0x224 */
    int field_228;                /* 0x228 */
};

extern void func_0202ea34(int *quat, int a, int b, int c, int e);
extern int func_02023eb4(int range);
extern void func_0203c634(int self, int idx, void *cb);
extern void func_ov271_020d0b4c(void);
extern void func_ov271_020d08e8(void);
extern void func_ov271_020d0aac(void);

void func_ov271_020d07d0(int self) {
    int *state = *(int **)(self + 4);
    unsigned short *hw;
    unsigned int h;
    int base, diff, r;

    *(unsigned char *)(*state + 0x1c6) = 0;
    ((struct AiState *)(*state))->pendingAction = -1;
    ((struct b8 *)(*(int *)(*state + 0x388) + 8))->f &= ~1;
    state[0x12] = *state + 0xb0;
    state[0x13] = *state + 0x74;
    hw = (unsigned short *)(*state + 0x60);
    h = *hw;
    *hw = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 6) << 0x18) >> 0x10);
    func_0202ea34(&state[0x21], 0, 0, 0, 0);
    *(struct q4 *)&state[0x25] = *(struct q4 *)&state[0x21];
    base = ((struct AiState *)(*state))->field_224;
    diff = ((struct AiState *)(*state))->field_228 - base;
    if (diff < 0) {
        diff = -diff;
    }
    r = func_02023eb4(diff + 1);
    state[0x20] = base + r;
    func_0203c634(self, 1, &func_ov271_020d0b4c);
    func_0203c634(self, 0, &func_ov271_020d08e8);
    func_0203c634(self, 2, &func_ov271_020d0aac);
}
