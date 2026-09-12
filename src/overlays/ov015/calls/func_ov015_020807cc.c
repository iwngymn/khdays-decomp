/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x5c];
    int flags5c;                  /* 0x05c */
};

extern int NNSi_FndFreeFromDefaultHeap(int block);
/* Free every live entry's buffer across the nine 0x1c-byte records at *(obj+8). */
void func_ov015_020807cc(int obj) {
    int i = 0;
    char *p = *(char **)(obj + 8);
    do {
        if (*(signed char *)(p + 0x58) > 0 && ((struct AiState *)(p))->flags5c != 0) {
            NNSi_FndFreeFromDefaultHeap(((struct AiState *)(p))->flags5c);
            ((struct AiState *)(p))->flags5c = 0;
        }
        i++;
        p += 0x1c;
    } while (i < 9);
}
