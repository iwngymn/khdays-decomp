/* Ease the pursuit speed towards its cap and, once the target byte at state[3] clears,
 * lock it at 1.0 and roll the next hold time.
 *
 * The travelled distance at state[0x11] accumulates the owner's per-frame delta, is turned
 * into a fraction of 0x2aa by FX_Inv, and biased by 0xcc into the speed field at +0x390,
 * clamped to 0x1000. When the gate byte is clear the speed is pinned to 0x1000, a hold time
 * is rolled uniformly between the bounds at +0x224/+0x228, and the action byte at +0x1c7 is
 * set to 2 before re-registering the think callback. */
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c7];
    signed char pendingAction;    /* 0x1c7 */
    unsigned char pad1c8[0x5c];
    int field_224;                /* 0x224 */
    int field_228;                /* 0x228 */
    unsigned char pad22c[0x164];
    int field_390;                /* 0x390 */
};

extern int FX_Inv(int a, int b);
extern int func_02023eb4(int scale);
extern void func_0203c634(void *node, int idx, void *cb);

void func_ov244_020d2e74(int *node) {
    int *owner = (int *)node[0];
    int *state = (int *)node[1];
    int v;
    int lo;

    state[0x11] = state[0x11] + *(int *)((int)owner + 0x2c);
    v = FX_Inv(state[0x11], 0x2aa);
    ((struct AiState *)(state[0]))->field_390 = v + 0xcc;
    if (((struct AiState *)(state[0]))->field_390 > 0x1000) {
        ((struct AiState *)(state[0]))->field_390 = 0x1000;
    }
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    ((struct AiState *)(state[0]))->field_390 = 0x1000;
    lo = ((struct AiState *)(state[0]))->field_224;
    v = ((struct AiState *)(state[0]))->field_228 - lo;
    if (v < 0) {
        v = -v;
    }
    state[0x13] = lo + func_02023eb4(v + 1);
    ((struct AiState *)(state[0]))->pendingAction = 2;
    func_0203c634(node, *(signed char *)((int)node + 0x20), 0);
}
