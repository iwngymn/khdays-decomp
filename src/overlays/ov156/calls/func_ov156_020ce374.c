/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c6];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

extern void func_0203c634(int obj, int slot, int cb);
extern void func_ov156_020ce410(void);
extern void func_ov156_020ce4f8(void);

// If a sub-state transition is pending (node[0][0x1c7] != -1), commit it into the
// current sub-state (0x1c6), clear the busy flag (node[0x24] bit0), install the
// matching state callback (for sub-state 0 or 1), and clear the pending slot.
void func_ov156_020ce374(int *this)
{
    int node = this[1];
    signed char pending = ((struct AiState *)(*(int *)node))->pendingAction;
    if (pending == -1) {
        return;
    }
    ((struct AiState *)(*(int *)node))->currentAction = pending;
    *(unsigned char *)(node + 0x24) &= ~1;
    switch (((struct AiState *)(*(int *)node))->currentAction) {
    case 0:
        func_0203c634((int)this, 1, (int)&func_ov156_020ce410);
        break;
    case 1:
        func_0203c634((int)this, 1, (int)&func_ov156_020ce4f8);
        break;
    }
    ((struct AiState *)(*(int *)node))->pendingAction = -1;
}
