/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c6];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov299_020d3b18(void);
extern void func_ov299_020d3b54(void);

void func_ov299_020d3a9c(int *node)
{
    int *state = (int *)node[1];
    signed char next = ((struct AiState *)(*state))->pendingAction;

    if (next == -1) {
        return;
    }
    ((struct AiState *)(*state))->currentAction = next;
    switch (((struct AiState *)(*state))->currentAction) {
    case 0:
        func_0203c634(node, 1, func_ov299_020d3b18);
        break;
    case 2:
        func_0203c634(node, 1, func_ov299_020d3b54);
        break;
    }
    ((struct AiState *)(*state))->pendingAction = -1;
}
