typedef struct { int x, y, z; } Vec3;
struct b2 { unsigned char b0:1, b1:1; };

/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c7];
    signed char pendingAction;    /* 0x1c7 */
};

extern void func_01ffa724(int s, int dst, int src);
extern int func_ov298_020d404c(void *param);
extern unsigned int func_02023e80(unsigned int range);
extern void func_0203c634(int obj, int idx, int cb);

void func_ov298_020d5034(int *this)
{
    int node = this[1];
    Vec3 *v = (Vec3 *)(node + 0x1c);
    *(Vec3 *)(node + 0x10) = *v;
    func_01ffa724(0xb00, (int)v, (int)v);

    {
        int diff = func_ov298_020d404c(this);

        if (((struct b2 *)(*(int *)node + 0x17a))->b1) {
            *(int *)(node + 0x8c) = 1;
        }
        if (*(unsigned char *)(*(int *)(node + 4) + 0xad) != 0) {
            return;
        }

        *(int *)(node + 0x28) = func_02023e80(0x1922) + 0x1922;

        if (diff > 0x9000) {
            ((struct AiState *)(*(int *)node))->pendingAction = 4;
        } else {
            if (*(int *)(node + 0x8c) != 0 && *(int *)(node + 0x40) <= 0) {
                ((struct AiState *)(*(int *)node))->pendingAction = 5;
            } else {
                ((struct AiState *)(*(int *)node))->pendingAction = 4;
            }
        }
    }

    func_0203c634((int)this, *(signed char *)((int)this + 0x20), 0);
}
