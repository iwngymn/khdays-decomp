/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c6];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

extern void func_ov107_020cb100(int sub);
extern void func_ov107_020c7ca4(int obj);

// If flagged (this[0x1c4]&0xa) and idle (this[0x1c7]==-1) and the current
// sub-state isn't one of the reserved values, force sub-state 5. Then, unless the
// sub-state is 10, release the pending sub-object (this[0x398]) if present.
void func_ov277_020d19d4(int *this)
{
    if ((*(unsigned char *)((int)this + 0x1c4) & 0xa) != 0 &&
        ((struct AiState *)((int)this))->pendingAction == -1) {
        signed char cur = ((struct AiState *)((int)this))->currentAction;
        if (cur != 0 && cur != 1 && cur != 3 && cur != 5 && cur != 0xb && cur != 7) {
            ((signed char *)this)[0x1c7] = 5;
        }
    }
    if (((struct AiState *)((int)this))->currentAction != 10 && *(int *)((int)this + 0x398) != 0) {
        func_ov107_020cb100(*(int *)((int)this + 0x398));
        *(int *)((int)this + 0x398) = 0;
    }
    func_ov107_020c7ca4((int)this);
}
