/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x60];
    unsigned short flags60;       /* 0x060 */
    unsigned char pad062[0x164];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
    unsigned char pad1c8[0x5c];
    int field_224;                /* 0x224 */
    int field_228;                /* 0x228 */
};

extern int func_02023eb4(int);
extern void func_0203c634(int, int, void *);
extern void func_ov202_020ccef0(void);
extern void func_ov202_020ccc4c(void);
extern void func_ov202_020cce04(void);

struct flagword { unsigned f8 : 8; };

void func_ov202_020ccb4c(int param_1) {
    int *obj = *(int **)(param_1 + 4);
    unsigned short h;
    int lo, range;

    ((struct AiState *)(*obj))->currentAction = 0;
    ((struct AiState *)(*obj))->pendingAction = -1;
    ((struct flagword *)(*(int *)(*obj + 0x38c) + 8))->f8 &= ~1;
    obj[0xf] = *obj + 0xb0;
    obj[0x10] = *obj + 0x74;
    obj[0x11] = *(int *)(*obj + 900) + 0xad;
    h = ((struct AiState *)(*obj))->flags60;
    ((struct AiState *)(*obj))->flags60 =
        h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 6) << 0x18) >> 0x10);
    lo = ((struct AiState *)(*obj))->field_224;
    range = ((struct AiState *)(*obj))->field_228 - lo;
    if (range < 0) {
        range = -range;
    }
    obj[0xc] = lo + func_02023eb4(range + 1);
    func_0203c634(param_1, 1, func_ov202_020ccef0);
    func_0203c634(param_1, 0, func_ov202_020ccc4c);
    func_0203c634(param_1, 2, func_ov202_020cce04);
}
