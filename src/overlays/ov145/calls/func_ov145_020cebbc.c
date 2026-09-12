/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c6];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov145_020cf028(void);
extern void func_ov145_020cec28(void);
extern void func_ov145_020ceea0(void);

void func_ov145_020cebbc(int *node) {
    int *state = (int *)node[1];
    ((struct AiState *)(*state))->currentAction = 0;
    ((struct AiState *)(*state))->pendingAction = -1;
    state[2] = *state + 0xb0;
    func_0203c634(node, 1, func_ov145_020cf028);
    func_0203c634(node, 0, func_ov145_020cec28);
    func_0203c634(node, 2, func_ov145_020ceea0);
}
