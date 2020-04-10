/*
 * Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2019-2020

 * @Author Diogo Filipe Marinho Barbosa
 * @Number 2018012425
*/

#include <stdio.h>
#include "helpers/utils.c"
#include "core/spaceBuilder.h"

int main() {
    char filename[] = "./data/spaces/E1.bin";
    localsSmartList *localsList = buildList(filename);

    for (int i = 0; i < localsList->length; i++) {
        printf("%i \t",localsList->array[i].id);
        printf("%i \t",localsList->array[i].capacity);
        printf("%i \t",localsList->array[i].refLocal[0]);
        printf("%i \t",localsList->array[i].refLocal[1]);
        printf("%i \t",localsList->array[i].refLocal[2]);
        puts("\n");
    }

    return 0;
}
