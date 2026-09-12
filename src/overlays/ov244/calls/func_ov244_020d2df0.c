/* Set bit 0 of the u16 at *(child)+0x1ae, clear bit 0 of the low byte at *(*child+0x388)+8,
 * play the anim (ov107 mode 7), clear +0x44, set *(*child)+0x390 = 0xcc and register the handler. */
struct b8 { unsigned int f : 8; };
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1ae];
    unsigned short flags1ae;      /* 0x1ae */
    unsigned char pad1b0[0x1e0];
    int field_390;                /* 0x390 */
};

extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov244_020d2e74(int);
void func_ov244_020d2df0(int param_1) {
    int child = *(int *)(param_1 + 4);
    ((struct AiState *)(*(int *)child))->flags1ae |= 1;
    ((struct b8 *)(*(int *)(*(int *)child + 0x388) + 8))->f &= ~1;
    func_ov107_020c9264(*(int *)child, 7, 0);
    *(int *)(child + 0x44) = 0;
    ((struct AiState *)(*(int *)child))->field_390 = 0xcc;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov244_020d2e74);
}
