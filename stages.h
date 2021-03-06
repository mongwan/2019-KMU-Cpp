#ifndef PUSHBOX_STAGES_H
#define PUSHBOX_STAGES_H

const int STAGEN = 5;
const int heights[STAGEN] = {7, 9, 6, 8, 8};
const int widths[STAGEN] = {6, 7, 8, 7, 10};
const int init_curr[STAGEN][2] = {
        {5, 2},
        {2, 2},
        {2, 6},
        {6, 3},
        {4, 6}
};
const int boxn[STAGEN] = {3, 3, 3, 6, 3};
int stage1[7][6] = {
        {1, 1, 1, 1, 1, 4},
        {1, 0, 0, 0, 1, 4},
        {1, 3, 3, 3, 1, 4},
        {1, 2, 2, 2, 1, 1},
        {1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1}
};

int stage2[9][7] = {
        {1, 1, 1, 1, 4, 4, 4},
        {1, 3, 0, 1, 1, 4, 4},
        {1, 3, 0, 0, 1, 4, 4},
        {1, 3, 0, 2, 1, 4, 4},
        {1, 1, 2, 0, 1, 1, 1},
        {4, 1, 0, 2, 0, 0, 1},
        {4, 1, 0, 0, 0, 0, 1},
        {4, 1, 0, 0, 1, 1, 1},
        {4, 1, 1, 1, 1, 4, 4}
};

int stage3[6][8] = {
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 3, 0, 0 ,0, 0, 0, 1},
        {1, 0, 3, 2, 2, 2, 0, 1},
        {1, 3, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 0, 0, 1},
        {4, 4, 4, 4, 1, 1, 1, 1}
};

int stage4[8][7] = {
        {1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 1},
        {1, 0, 3, 2, 3, 0, 1},
        {1, 0, 2, 3, 2, 0, 1},
        {1, 0, 3, 2, 3, 0, 1},
        {1, 0, 2, 3, 2, 0, 1},
        {1, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1}
};

int stage5[8][10] = {
        {4, 1, 1, 1, 1, 4, 4, 4, 4, 4},
        {4, 1, 0, 0, 1, 1, 1, 1, 4, 4},
        {4, 1, 0, 0, 0, 0, 0, 1, 1, 4},
        {1, 1, 0, 1, 1, 0, 0, 0, 1, 4},
        {1, 3, 0, 3, 1, 0, 0, 2, 1, 1},
        {1, 0, 0, 0, 1, 0, 2, 2, 0, 1},
        {1, 0, 0, 3, 1, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int* stagep[STAGEN] = {(int*)stage1, (int*)stage2, (int*)stage3, (int*)stage4, (int*)stage5};
#endif //PUSHBOX_STAGES_H
