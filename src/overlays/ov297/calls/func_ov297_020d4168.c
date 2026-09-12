typedef struct { int x, y, z; } VecFx32;

/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x80];
    int field_80;                 /* 0x080 */
    unsigned char pad084[0x143];
    signed char pendingAction;    /* 0x1c7 */
    unsigned char pad1c8[0x1cc];
    int field_394;                /* 0x394 */
};

extern int func_ov107_020cab14(int a, int b);
extern void VEC_Subtract(VecFx32 *a, VecFx32 *b, VecFx32 *out);
extern int func_01ff8d18(VecFx32 *src, VecFx32 *dst);
extern int func_020050b4(int x, int z);

int func_ov297_020d4168(int this_) {
    int *state = (int *)(*(int *)(this_ + 4));
    int t = func_ov107_020cab14(*state, 0);
    VecFx32 delta;
    int dist, radiusSum;

    ((struct AiState *)(*state))->field_394 = t;
    if (((struct AiState *)(*state))->field_394 == 0) {
        ((struct AiState *)(*state))->pendingAction = 2;
        return -1;
    }
    VEC_Subtract((VecFx32 *)(((struct AiState *)(*state))->field_394 + 0x190),
                 (VecFx32 *)(*state + 0xb0), &delta);
    dist = func_01ff8d18(&delta, &delta);
    radiusSum = *(int *)(((struct AiState *)(*state))->field_394 + 0x80) + ((struct AiState *)(*state))->field_80;
    dist -= radiusSum;
    if (dist < 0) dist = 0;
    *(int *)((int)state + 0x30) = func_020050b4(delta.x, delta.z);
    return dist;
}
