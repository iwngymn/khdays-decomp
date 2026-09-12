struct flag8 {
    unsigned value : 8;
};

/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c6];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov301_020cc63c(void);
extern void func_ov301_020cc338(void);
extern void func_ov301_020cc458(void);

void func_ov301_020cc2a4(int *node)
{
    int *state = (int *)node[1];

    ((struct AiState *)(*state))->currentAction = 0;
    ((struct AiState *)(*state))->pendingAction = -1;
    ((struct flag8 *)(*(int *)(*state + 0x388) + 8))->value &= ~1;
    state[1] = *state + 0xb0;
    func_0203c634(node, 1, func_ov301_020cc63c);
    func_0203c634(node, 0, func_ov301_020cc338);
    func_0203c634(node, 2, func_ov301_020cc458);
}
