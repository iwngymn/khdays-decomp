struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1ae];
    unsigned short flags1ae;      /* 0x1ae */
    unsigned char pad1b0[0x16];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

extern void func_0203c634(void *obj, int idx, void *value);
extern void func_0203c9d0(int a, void *b);
extern int data_020420f8;
extern void func_ov118_020d063c(void);
extern void func_ov118_020d073c(void);
extern void func_ov118_020d086c(void);
extern void func_ov118_020d0a00(void);
extern void func_ov118_020d0b78(void);
extern void func_ov118_020d0ccc(void);
extern void func_ov118_020d0d94(void);
extern void func_ov118_020d12d8(void);
extern void func_ov118_020d1728(void);
extern void func_ov118_020d17f0(void);

void func_ov118_020d0328(int *node) {
    int *state = (int *)node[1];
    int c = ((struct AiState *)(*state))->pendingAction;
    if (c != -1) {
        { unsigned short *p = (unsigned short *)(*state + 0x60); unsigned int u = *p;
          *p = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10)); }
        ((struct hw60 *)(*state + 0x60))->hi &= ~0x8e;
        ((struct AiState *)(*state))->flags1ae &= ~1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
        func_0203c9d0(*(int *)(*state + 0x384) + 4, &data_020420f8);
        ((struct AiState *)(*state))->currentAction = ((struct AiState *)(*state))->pendingAction;
        switch (((struct AiState *)(*state))->currentAction) {
        case 0: func_0203c634(node, 1, func_ov118_020d063c); break;
        case 1: func_0203c634(node, 1, func_ov118_020d073c); break;
        case 2: func_0203c634(node, 1, func_ov118_020d086c); break;
        case 4: func_0203c634(node, 1, func_ov118_020d0a00); break;
        case 5: func_0203c634(node, 1, func_ov118_020d0b78); break;
        case 3: func_0203c634(node, 1, func_ov118_020d0ccc); break;
        case 6: func_0203c634(node, 1, func_ov118_020d0d94); break;
        case 7: func_0203c634(node, 1, func_ov118_020d12d8); break;
        case 8: func_0203c634(node, 1, func_ov118_020d1728); break;
        case 9: func_0203c634(node, 1, func_ov118_020d17f0); break;
        }
    }
    ((struct AiState *)(*state))->pendingAction = -1;
}
