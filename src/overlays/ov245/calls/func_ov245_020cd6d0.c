/* func_ov245_020cd6d0 -- reaction enter, gated on bit 0 of the actor's hw60 flags.
 * Seeds the reaction timer (node[0xb] = 0x4000) and the step size (node[0xd] = 0x1000),
 * clears the actor's pending-reaction word at +0x4c4 and its two per-node counters, marks
 * the reaction slot free (0xff at +0x4d8), promotes the queued reaction id (+0x1c9) into
 * the active one (+0x1c7) and re-arms the think callback.
 *
 * Two shapes are load-bearing:
 *  - the 0xff is `(char *)0 + zero` minus one. The ROM keeps the zero live in a register and
 *    derives 0xff from it (`sub r3, r2, #1`); a literal 0xff, a literal -1 and a plain
 *    `zero - 1` all constant-fold to a late `mov r3, #0xff`. The pointer round-trip is what
 *    stops the fold, the same idiom as func_ov004_0204cecc.
 *  - the last two zero stores are CHAINED. With them as separate statements mwcc schedules
 *    the shared zero and the subtract below the first store instead of above it; merging the
 *    two statements moves the whole group back. Same lever as func_02023c60.
 *  - the reaction-id copy is `*(char *) = *(char *)` (signed), which keeps the ROM's
 *    ldrsb + add split instead of one wide-offset ldrb. */
struct hw60 { unsigned short lo : 8, hi : 8; };

/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c7];
    signed char pendingAction;    /* 0x1c7 */
    unsigned char pad1c8[0x1];
    signed char field_1c9;        /* 0x1c9 */
};

extern int func_0203c634(int self, int idx, void *handler);

void func_ov245_020cd6d0(int self) {
    int *node = *(int **)(self + 4);
    int zero;

    if ((((struct hw60 *)(*node + 0x60))->lo & 1) == 0) {
        return;
    }
    node[0xb] = 0x4000;
    zero = 0;
    *(int *)(*node + 0x4c4) = zero;
    *(unsigned char *)(*node + 0x4d8) = (unsigned char)((int)((char *)0 + zero) - 1);
    node[0x11] = *(unsigned char *)((char *)node + 0x43) = zero;
    node[0xd] = 0x1000;
    ((struct AiState *)(*node))->pendingAction = ((struct AiState *)(*node))->field_1c9;
    func_0203c634(self, *(signed char *)(self + 0x20), 0);
}
