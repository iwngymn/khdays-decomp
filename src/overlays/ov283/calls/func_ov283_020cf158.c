typedef unsigned short u16;

/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x60];
    unsigned short flags60;       /* 0x060 */
};

extern int func_0203c634(int self, int idx, void *handler);

/* Reaction: clear hw60 high-byte bit 0x80, then set its bit 0, re-arm the slot with no handler.
 * hw60 = *(u16*)(*node+0x60), reloaded each op. node=*(ReactionAiNode**)(self+4); *node=pActor. */
void func_ov283_020cf158(int self) {
    int *node = *(int **)(self + 4);
    u16 hw;
    hw = ((struct AiState *)(*node))->flags60;
    ((struct AiState *)(*node))->flags60 = (hw & ~0xff00) |
        (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~0x80) << 0x18) >> 0x10);
    hw = ((struct AiState *)(*node))->flags60;
    ((struct AiState *)(*node))->flags60 = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 1) << 0x18) >> 0x10);
    func_0203c634(self, *(signed char *)(self + 0x20), 0);
}
