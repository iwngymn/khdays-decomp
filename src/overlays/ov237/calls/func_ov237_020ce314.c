/* If the "can act" hw60 bit 0 is set, pick a random hold time between the min (*node+0x224) and max
 * (*node+0x228), store it in node[10], enter the hold state (1), and register the think callback. */
struct hw60 { unsigned short lo : 8, hi : 8; };
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c7];
    signed char pendingAction;    /* 0x1c7 */
    unsigned char pad1c8[0x5c];
    int field_224;                /* 0x224 */
    int field_228;                /* 0x228 */
};

extern int func_02023eb4();
extern void func_0203c634(int self, int idx, int cb);

void func_ov237_020ce314(int param_1) {
    int *node = *(int **)(param_1 + 4);
    int lo;
    int range;
    if ((((struct hw60 *)(*node + 0x60))->lo & 1) == 0) {
        return;
    }
    lo = ((struct AiState *)(*node))->field_224;
    range = ((struct AiState *)(*node))->field_228 - lo;
    if (range < 0) {
        range = -range;
    }
    node[10] = lo + func_02023eb4(range + 1);
    ((struct AiState *)(*node))->pendingAction = 1;
    func_0203c634(param_1, *(signed char *)((char *)param_1 + 0x20), 0);
}
