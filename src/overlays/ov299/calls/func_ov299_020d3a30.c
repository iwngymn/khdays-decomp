/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c6];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov299_020d3a9c(void);
extern void func_ov299_020d3b14(void);
extern void func_ov299_020d3b18(void);

void func_ov299_020d3a30(int *node)
{
    int *state = (int *)node[1];

    ((struct AiState *)(*state))->currentAction = 0;
    ((struct AiState *)(*state))->pendingAction = -1;
    state[1] = *state + 0xb0;
    func_0203c634(node, 1, func_ov299_020d3b18);
    func_0203c634(node, 0, func_ov299_020d3a9c);
    func_0203c634(node, 2, func_ov299_020d3b14);
}
