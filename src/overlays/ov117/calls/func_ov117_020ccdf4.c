/* The early-exit is written as the POSITIVE case (`dist <= 0x1000 || dist >= thresh`
 * -> set state 2 and return) so that block is the fall-through, which is where the ROM
 * has it. Writing it as `if (in range) { rand } else { state2 }` emits the two blocks
 * the other way round.
 * func_ov117_020cc5c0 takes THREE arguments; Ghidra shows a fourth (leftover in r3). */
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c7];
    signed char pendingAction;    /* 0x1c7 */
    unsigned char pad1c8[0x5c];
    int field_224;                /* 0x224 */
    int field_228;                /* 0x228 */
    unsigned char pad22c[0xac];
    int field_2d8;                /* 0x2d8 */
};

extern int  func_ov107_020cab14(int obj, int *out);
extern void func_0203c634(int self, int index, void *cb);
extern int  FX_Sqrt(int x);
extern int  func_02023eb4();
extern void func_ov117_020cc5c0();
extern void func_0202f384();
extern void func_01ffa724();
extern char data_02042258[];

void func_ov117_020ccdf4(int self) {
    int *obj = *(int **)(self + 4);
    int dist;
    int owner, target;

    target = obj[1] = func_ov107_020cab14(*obj, &dist);
    if (target == 0) {
        ((struct AiState *)(*obj))->pendingAction = 2;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }
    obj[10] = *(int *)(*(int *)self + 0x2c) * 0x1e / 20;
    owner = *obj;
    target = obj[1];
    dist = FX_Sqrt(dist) - (*(int *)(target + 0x80) + *(int *)(owner + 0x80));
    func_ov117_020cc5c0((int)obj, obj + 6, dist);
    func_0202f384(obj + 0xb, obj + 2, data_02042258);
    func_01ffa724(0x100, obj + 0xb, obj + 0xb);
    if (dist <= 0x1000 || dist >= ((struct AiState *)(*obj))->field_2d8) {
        ((struct AiState *)(*obj))->pendingAction = 2;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }
    if (obj[0x10] > 0) {
        return;
    }
    {
        int lo = ((struct AiState *)(*obj))->field_224;
        int range = ((struct AiState *)(*obj))->field_228 - lo;
        if (range < 0) {
            range = -range;
        }
        obj[0x10] = lo + func_02023eb4(range + 1);
    }
    ((struct AiState *)(*obj))->pendingAction = 6;
    func_0203c634(self, *(signed char *)(self + 0x20), 0);
}
