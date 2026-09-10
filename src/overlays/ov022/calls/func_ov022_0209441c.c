/* ov022: have the owner's three parts and its slot all finished?
 *
 * Each part has a "wanted" bit in the request mask at 0x334 and a matching
 * "done" bit in the owner's flag word. A part that is wanted but not yet done is
 * asked whether it has finished; if it has, its done bit goes up, and if it has
 * not, the answer for the whole owner is no. The slot at the actor's 0xda0 block
 * is the fourth entry of the same pair of tables, but it answers the other way
 * round: a live slot is one that has NOT finished.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct Actor;

/* Ov022ActionOwner */
struct ActionOwner {
    u32 nFlags;                  /* 0x0000 */
    u8 pad0004[0x324];
    struct Actor *pActor;        /* 0x0328 */
    u8 pad032c[8];
    u8 nWanted;                  /* 0x0334 */
    u8 pad0335[11];
    u8 *apParts[3];              /* 0x0340 */
};

/* The bit tables live in ov022's .rodata (ov022_tables_020b2520.c) and the
 * function works on a stack copy of each. They are structs, not arrays,
 * because C only copy-initialises a struct from another object; an array
 * initialiser would make the compiler emit its own anonymous template instead
 * of referencing the shared table. */
typedef struct {
    u32 nBit[3];
} Ov022PartBits;

extern const Ov022PartBits data_ov022_020b2520;  /* done bits   { 0x04, 0x08, 0x10 } */
extern const Ov022PartBits data_ov022_020b252c;  /* wanted bits { 0x01, 0x02, 0x04 } */

extern int func_ov022_020b1510(u8 *pPart);
extern int func_ov022_020b1d54(u8 *pSlot);

int func_ov022_0209441c(struct ActionOwner *pOwner)
{
    struct Actor *pActor = pOwner->pActor;
    Ov022PartBits aDoneBit = data_ov022_020b2520;
    Ov022PartBits aWantBit = data_ov022_020b252c;
    int bAllDone;
    int i;

    bAllDone = 1;
    for (i = 0; i < 3; i++) {
        if ((pOwner->nFlags & aDoneBit.nBit[i]) == 0
            && (pOwner->nWanted & aWantBit.nBit[i]) != 0) {
            if (func_ov022_020b1510(pOwner->apParts[i]) == 0) {
                bAllDone = 0;
            } else {
                pOwner->nFlags |= aDoneBit.nBit[i];
            }
        }
    }
    if ((pOwner->nFlags & 0x20) == 0 && (pOwner->nWanted & 8) != 0) {
        if (func_ov022_020b1d54((u8 *)pActor + 0xda0) != 0) {
            bAllDone = 0;
        } else {
            pOwner->nFlags |= 0x20;
        }
    }
    return bAllDone;
}
