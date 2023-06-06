#include "stdio.h"
#include "defs.h"

int main(int argc, char *argv[]) {

    AllInit();

    S_BOARD pos[1];
    S_SEARCHINFO info[1];
    info->quit = false;
    pos->HashTable->pTable = NULL;

    InitHashTable(pos->HashTable, 64)
    setbuf(stdin, NULL);

    int ArgNum = 0;

    for (ArgNum = 0; ArgNum < argc; ArgNum++) {
        if (strncmp(argv[ArgNum], "NoBook", 6) == 0) {
            EngineOptions->UseBook = false
        }
    }

    return 0;
}
