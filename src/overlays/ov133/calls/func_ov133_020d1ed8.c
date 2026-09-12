typedef struct { int w[11]; } SrtTransform;   /* 44 bytes, the node's SRT block */

/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c6];
    signed char currentAction;    /* 0x1c6 */
    signed char pendingAction;    /* 0x1c7 */
};

extern void func_0203c650(int owner, int handle);
extern void func_ov107_020cb100(void *attachment);
extern void func_ov107_020c7ca4(void *actor);

void func_ov133_020d1ed8(char *actor) {
    int state;

    if ((*(unsigned char *)(actor + 0x1c4) & 0xa) != 0) {
        state = ((struct AiState *)(actor))->currentAction;
        if (state != 0 && state != 1 && state != 3 && state != 5) {
            ((struct AiState *)(actor))->pendingAction = 5;
        }
    }

    if (((struct AiState *)(actor))->currentAction != 7) {
        if (*(int *)(*(char **)(actor + 0x3c4) + 0x14) != 0) {
            func_0203c650(*(int *)(actor + 0x3c),
                          *(int *)(*(char **)(actor + 0x3c4) + 0x14));
            *(int *)(*(char **)(actor + 0x3c4) + 0x14) = 0;
        }
        if (*(int *)(*(char **)(actor + 0x3c4) + 0x24) != 0) {
            func_0203c650(*(int *)(actor + 0x3c),
                          *(int *)(*(char **)(actor + 0x3c4) + 0x24));
            *(int *)(*(char **)(actor + 0x3c4) + 0x24) = 0;
        }
    }

    if (((struct AiState *)(actor))->currentAction != 6) {
        if (*(int *)(*(char **)(actor + 0x3c4) + 4) != 0) {
            func_0203c650(*(int *)(actor + 0x3c),
                          *(int *)(*(char **)(actor + 0x3c4) + 4));
            *(int *)(*(char **)(actor + 0x3c4) + 4) = 0;
        }
        if (*(void **)(actor + 0x3d0) != 0) {
            func_ov107_020cb100(*(void **)(actor + 0x3d0));
            *(void **)(actor + 0x3d0) = 0;
        }
    }

    *(SrtTransform *)(**(char ***)(actor + 0x388) + 0x10) =
        *(SrtTransform *)(*(char **)(actor + 0x3c0) + 4);
    *(SrtTransform *)(*(char **)(actor + 0x38c) + 0x10) =
        *(SrtTransform *)(*(char **)(actor + 0x3c0) + 4);

    func_ov107_020c7ca4(actor);
}
