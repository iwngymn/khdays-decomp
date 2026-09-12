/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1ae];
    unsigned short flags1ae;      /* 0x1ae */
    unsigned char pad1b0[0x17];
    signed char pendingAction;    /* 0x1c7 */
};

extern void func_0203c634();
void func_ov240_020cf208(int node) {
    int *s = *(int **)(node + 4);
    if (*(unsigned char *)(s[1] + 0xad) != 0) return;
    ((struct AiState *)(*s))->flags1ae &= ~1;
    ((struct AiState *)(*s))->pendingAction = 2;
    func_0203c634(node, *(signed char *)(node + 0x20), 0);
}
