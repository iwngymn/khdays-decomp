/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x60];
    unsigned short flags60;       /* 0x060 */
    unsigned char pad062[0x165];
    signed char pendingAction;    /* 0x1c7 */
    unsigned char pad1c8[0x1];
    signed char field_1c9;        /* 0x1c9 */
    unsigned char pad1ca[0x5a];
    int field_224;                /* 0x224 */
    int field_228;                /* 0x228 */
};

extern int func_02023eb4(int range);
extern void func_0203c634(void *node, int idx, void *value);

void func_ov204_020d07f8(int node)
{
    int *state = *(int **)(node + 4);
    int start;
    int range;
    int flags;

    flags = ((struct AiState *)(*state))->flags60;
    flags = (unsigned int)(flags << 24) >> 24;
    if ((flags & 1) == 0) {
        return;
    }

    start = ((struct AiState *)(*state))->field_224;
    range = ((struct AiState *)(*state))->field_228 - start;
    if (range < 0) {
        range = -range;
    }
    state[0x30 / 4] = start + func_02023eb4(range + 1);
    ((struct AiState *)(*state))->pendingAction = ((struct AiState *)(*state))->field_1c9;
    func_0203c634((void *)node, *(signed char *)(node + 0x20), 0);
}
