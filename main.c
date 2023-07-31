#include "stdio.h"
#include "defs.h"

int main(int argc, char *argv[]) {
    AllInit();

    int index;

    for (index = 0; index < BRD_SQ_NUM; ++index) {
        if (index % 10 == 0) // Board across size, newline
            printf("\n");
        printf("%5d", Sq120ToSq64[index]);
    }

    for (int i = 0; i < 2; i++)
        printf("\n");

    for (index = 0; index < 64; ++index) {
        if (index % 8 == 0)
            printf("\n");
        printf("%5d", Sq64ToSq120[index]);
    }

    printf("\n");
    return 0;
}