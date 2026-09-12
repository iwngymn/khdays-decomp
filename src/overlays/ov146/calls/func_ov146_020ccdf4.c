/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c7];
    signed char pendingAction;    /* 0x1c7 */
    unsigned char pad1c8[0x1];
    signed char field_1c9;        /* 0x1c9 */
};

extern void func_ov146_020ce298(int a, int b);
extern void func_0203c634(int self, int index, void *cb);
struct hw60 { unsigned short lo:8, hi:8; };
void func_ov146_020ccdf4(int self) {
    int obj = *(int *)(self + 4);
    if ((((struct hw60 *)(*(int *)obj + 0x60))->lo & 1) == 0) {
        return;
    }
    *(int *)(obj + 0x58) = 1;
    func_ov146_020ce298(*(int *)(obj + 8), 1);
    ((struct AiState *)(*(int *)obj))->pendingAction = ((struct AiState *)(*(int *)obj))->field_1c9;
    func_0203c634(self, *(signed char *)(self + 0x20), 0);
}
