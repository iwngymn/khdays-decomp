/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c6];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov153_020ccb40(void);
extern void func_ov153_020ccc28(void);
void func_ov153_020ccab0(int *node) {
    int *state = (int *)node[1];
    signed char c = ((struct AiState *)(*state))->pendingAction;
    if (c != -1) {
        ((struct AiState *)(*state))->currentAction = c;
        switch (((struct AiState *)(*state))->currentAction) {
        case 0:
            func_0203c634(node, 1, func_ov153_020ccb40);
            break;
        case 1:
            func_0203c634(node, 1, func_ov153_020ccc28);
            break;
        }
        ((struct AiState *)(*state))->pendingAction = 0xff;
    }
}
