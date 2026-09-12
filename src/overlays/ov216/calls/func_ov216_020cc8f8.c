/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x5c];
    int flags5c;                  /* 0x05c */
};

extern void func_ov216_020cc660(void *this);
extern void func_ov107_020c7ca4(void *this);

void func_ov216_020cc8f8(char *this) {
    if (*(signed char *)(this + 0x1c6) != 5) {
        func_ov216_020cc660(this);
    } else {
        if (*(int *)(this + 0x454) != 0) {
            int *p = *(int **)(this + 0x450);
            ((struct AiState *)((char *)p))->flags5c = (((struct AiState *)((char *)p))->flags5c & ~2) |
                (((unsigned)(*(unsigned char *)(this + 0x1c4) & 2) << 0x1f) >> 0x1e);
        }
        if (*(int *)(this + 0x464) != 0) {
            int *p = *(int **)(this + 0x460);
            ((struct AiState *)((char *)p))->flags5c = (((struct AiState *)((char *)p))->flags5c & ~2) |
                (((unsigned)(*(unsigned char *)(this + 0x1c4) & 2) << 0x1f) >> 0x1e);
        }
    }
    func_ov107_020c7ca4(this);
}
