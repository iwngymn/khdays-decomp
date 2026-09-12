/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1ae];
    unsigned short flags1ae;      /* 0x1ae */
    unsigned char pad1b0[0x16];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

extern void func_0203c634(int, int, void *);
extern void func_ov131_020ccf2c(void);
extern void func_ov131_020ccfd0(void);
extern void func_ov131_020cd1c0(void);
extern void func_ov131_020cd290(void);
extern void func_ov131_020cd510(void);
extern void func_ov131_020cd780(void);
extern void func_ov131_020cd86c(void);
extern void func_ov131_020cdeec(void);
extern void func_ov131_020ce0e8(void);
extern void func_ov131_020ce9f4(void);
extern void func_ov131_020ceabc(void);

struct node60 { unsigned short lo : 8; unsigned short hi : 8; };
struct flagword { unsigned f8 : 8; };

void func_ov131_020ccc90(int param_1) {
    int *node = *(int **)(param_1 + 4);
    int obj = *node;

    if (((struct AiState *)(obj))->pendingAction != -1) {
        ((struct node60 *)(obj + 0x60))->hi &= ~0xce;
        ((struct AiState *)(*node))->flags1ae &= ~1;
        ((struct flagword *)(*(int *)(*node + 0x388) + 8))->f8 |= 1;
        ((struct AiState *)(*node))->currentAction = ((struct AiState *)(*node))->pendingAction;
        switch (((struct AiState *)(*node))->currentAction) {
        case 0:  func_0203c634(param_1, 1, func_ov131_020ccf2c); break;
        case 1:  func_0203c634(param_1, 1, func_ov131_020ccfd0); break;
        case 2:  func_0203c634(param_1, 1, func_ov131_020cd1c0); break;
        case 4:  func_0203c634(param_1, 1, func_ov131_020cd290); break;
        case 9:  func_0203c634(param_1, 1, func_ov131_020cd510); break;
        case 5:  func_0203c634(param_1, 1, func_ov131_020cd780); break;
        case 6:  func_0203c634(param_1, 1, func_ov131_020cd86c); break;
        case 7:  func_0203c634(param_1, 1, func_ov131_020cdeec); break;
        case 8:  func_0203c634(param_1, 1, func_ov131_020ce0e8); break;
        case 3:  func_0203c634(param_1, 1, func_ov131_020ce9f4); break;
        case 10: func_0203c634(param_1, 1, func_ov131_020ceabc); break;
        }
    }
    ((struct AiState *)(*node))->pendingAction = -1;
}
