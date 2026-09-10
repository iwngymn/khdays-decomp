/* ov002 .data tables, 0x0207ec00-0x0207eca0.
 *
 * 5 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

/* mwccarm gives every char array a .rodata/.data section of its own (it handles
 * them like string literals) while int/short/struct tables pool into one section,
 * and the ROM interleaves the two, so no single object layout can reproduce it.
 * Pooling strings folds the char arrays into that one section; the data layout
 * step (tools/reorder_data_sections.py) then places the whole file. Content is
 * unchanged; a non-CodeWarrior compiler ignores the pragma. */
#pragma pool_strings on

typedef unsigned char u8;
typedef unsigned short u16;

int data_ov002_0207ec00[10] = {
    4, 13, 15, 2, 0, 12, 0, 22,
    0, 64,
};

u8 data_ov002_0207ec28[40] = {
    28, 0, 0, 0, 0, 0, 0, 0, 64, 0, 0, 0, 2, 0, 0, 0,
    96, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 20, 0, 0, 0,
    0, 0, 0, 0, 64, 0, 0, 0,
};

int data_ov002_0207ec50[9] = {
    20, 2, 25, 2, 0, 12, 0, 22,
    0,
};

int data_ov002_0207ec74[1] = {
    64,
};

int data_ov002_0207ec78[10] = {
    22, 15, 15, 2, 0, 12, 0, 22,
    0, 64,
};
