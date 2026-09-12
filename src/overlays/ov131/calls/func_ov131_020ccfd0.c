/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x60];
    unsigned short flags60;       /* 0x060 */
    unsigned char pad062[0x14c];
    unsigned short flags1ae;      /* 0x1ae */
};

extern void func_ov107_020c5af8(int, int, int, int);
extern void func_0203c634(int, int, void *);
extern void func_ov131_020cd098(void);

struct node60 { unsigned short lo : 8; unsigned short hi : 8; };
struct flagword { unsigned f8 : 8; };

void func_ov131_020ccfd0(int param_1) {
    int *node = *(int **)(param_1 + 4);
    unsigned short h = ((struct AiState *)(*node))->flags60;

    ((struct AiState *)(*node))->flags60 =
        h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 0x82) << 0x18) >> 0x10);
    ((struct node60 *)(*node + 0x60))->hi &= ~0xc;
    ((struct AiState *)(*node))->flags1ae |= 1;
    ((struct flagword *)(*(int *)(*node + 0x388) + 8))->f8 &= ~1;
    node[0xc] = 0;
    func_ov107_020c5af8(*node, 0, 0x48, node[0x10]);
    func_0203c634(param_1, *(char *)(param_1 + 0x20), func_ov131_020cd098);
}
