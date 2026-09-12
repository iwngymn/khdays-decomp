/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c6];
    signed char currentAction;    /* 0x1c6 */
};

extern void func_01ffa724(int scale, void *src, void *dst);

struct vec3 { int a, b, c; };
extern struct vec3 data_02041dc8;

void func_ov259_020d2b2c(int *node) {
    int *state = (int *)node[1];
    if (((struct AiState *)(*state))->currentAction == 0) {
        *(struct vec3 *)(state + 3) = data_02041dc8;
    } else if (((struct AiState *)(*state))->currentAction == 1) {
        func_01ffa724(0x500, state + 6, state + 3);
    }
    *(struct vec3 *)(*state + 0xf0) = *(struct vec3 *)(state + 3);
}
