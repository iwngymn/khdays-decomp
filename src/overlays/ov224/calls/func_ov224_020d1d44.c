/* Accumulate the owner rate (+0x2c) into the child timer (+0x5c); once it reaches
 * 0x6ee, clear flag 7 in the high byte at (*child)+0x60, stop the anim, and dispatch. */
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x5c];
    int flags5c;                  /* 0x05c */
};

extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov224_020d1dc4(void);
struct hi_020d1d28 { unsigned short pad : 8; unsigned short flags : 8; };
void func_ov224_020d1d44(int param_1) {
    int child = *(int *)(param_1 + 4);
    int c = ((struct AiState *)(child))->flags5c + *(int *)(*(int *)param_1 + 0x2c);
    ((struct AiState *)(child))->flags5c = c;
    if (c < 0x6ee) return;
    ((struct hi_020d1d28 *)(*(int *)child + 0x60))->flags &= ~0x80;
    func_ov107_020c9264(*(int *)child, 0, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov224_020d1dc4);
}
