/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c6];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

extern int OS_IsThreadAvailable_0x020c9848(void);

// When idle (this[0x1c7]==-1) and the current sub-state is neither 0 nor 6,
// request sub-state 6 and latch the active target's field (query[0x2c], or 0 if
// no target) into this[0x3ac].
void func_ov291_020cc5a8(int *this)
{
    if (((struct AiState *)((int)this))->pendingAction != -1) {
        return;
    }
    if (((struct AiState *)((int)this))->currentAction != 0 && ((struct AiState *)((int)this))->currentAction != 6) {
        ((signed char *)this)[0x1c7] = 6;
        {
            int target = OS_IsThreadAvailable_0x020c9848();
            *(int *)((int)this + 0x3ac) = (target != 0) ? *(int *)(target + 0x2c) : 0;
        }
    }
}
