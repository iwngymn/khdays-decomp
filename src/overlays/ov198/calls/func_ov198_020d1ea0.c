/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c6];
    signed char currentAction;    /* 0x1c6 */
};

extern void func_01ffa724(int scale, void *src, void *dst);

struct vec3 { int a, b, c; };
extern struct vec3 data_02041dc8;

void func_ov198_020d1ea0(int *node) {
    int *state = (int *)node[1];
    if (((struct AiState *)(*state))->currentAction == 0) {
        *(struct vec3 *)(state + 2) = data_02041dc8;
    } else if (((struct AiState *)(*state))->currentAction == 1) {
        func_01ffa724(0x800, state + 5, state + 2);
    }
    *(struct vec3 *)(*state + 0xf0) = *(struct vec3 *)(state + 2);
}
