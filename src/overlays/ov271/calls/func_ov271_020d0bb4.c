/* Only when bit 0 of the u16 flags low byte at *(obj)+0x60 is set: copy the sub-state from
 * *(obj)+0x1c9 into +0x1c7, build a spawn descriptor from *(child)+0xb0 (offsetting word[1] by
 * 0x54cc), fire ov107_020c5c54 with it and dispatch with no handler. */
struct hw60 { unsigned short lo : 8; unsigned short hi : 8; };
struct w3 { int a, b, c; };
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c7];
    signed char pendingAction;    /* 0x1c7 */
    unsigned char pad1c8[0x1];
    signed char field_1c9;        /* 0x1c9 */
};

extern void func_ov107_020c5c54(int a, struct w3 *b);
extern int func_0203c634(int a, int b, void *handler);
void func_ov271_020d0bb4(int param_1) {
    int child = *(int *)(param_1 + 4);
    int obj = *(int *)child;
    struct w3 buf;
    if ((((struct hw60 *)(obj + 0x60))->lo & 1) == 0) return;
    ((struct AiState *)(obj))->pendingAction = ((struct AiState *)(obj))->field_1c9;
    buf = *(struct w3 *)(*(int *)child + 0xb0);
    buf.b += 0x54cc;
    func_ov107_020c5c54(*(int *)child, &buf);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)0);
}
