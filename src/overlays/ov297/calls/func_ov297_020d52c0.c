/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x1c7];
    signed char pendingAction;    /* 0x1c7 */
};

extern void func_ov297_020d4168(int this_);
extern void func_ov297_020d4240(int this_);
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov297_020d5354(int this_);

void func_ov297_020d52c0(int this_) {
    int node = *(int *)(this_ + 4);

    func_ov297_020d4168(this_);
    func_ov297_020d4240(this_);

    if (*(int *)(node + 0x60) >= 4 && *(int *)(node + 0x80) == 0) {
        ((struct AiState *)(*(int *)node))->pendingAction = 0xa;
        func_0203c634((void *)this_, *(signed char *)(this_ + 0x20), 0);
        return;
    }
    if (*(int *)(node + 0x7c) >= 4) {
        ((struct AiState *)(*(int *)node))->pendingAction = 9;
        func_0203c634((void *)this_, *(signed char *)(this_ + 0x20), 0);
        return;
    }
    func_0203c634((void *)this_, *(signed char *)(this_ + 0x20), (void *)func_ov297_020d5354);
}
