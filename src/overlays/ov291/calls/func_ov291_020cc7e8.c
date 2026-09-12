typedef unsigned char u8;
typedef signed char s8;

/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c7];
    signed char pendingAction;    /* 0x1c7 */
};

extern void func_0203c634(int *a, int i, int v);
extern void func_ov291_020ccc18(int node);
extern void func_ov291_020cc870(void);
extern void func_ov291_020ccab4(void);

/* Enter the state: reset the actor's sub-state bytes, clear the task's
 * work fields, cache two actor-relative pointers, then register the three
 * phase handlers (slot 1, 0, 2). */
void func_ov291_020cc7e8(int *node)
{
    int *task = (int *)node[1];

    *(u8 *)(*task + 0x1c6) = 0;
    ((struct AiState *)(*task))->pendingAction = -1;
    task[2] = task[1] = 0;
    task[3] = *task + 0xb0;
    task[8] = *(int *)(*task + 0x384) + 0xad;
    task[0xd] = 0;

    func_0203c634(node, 1, (int)&func_ov291_020ccc18);
    func_0203c634(node, 0, (int)&func_ov291_020cc870);
    func_0203c634(node, 2, (int)&func_ov291_020ccab4);
}
