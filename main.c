/*
 * Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2019-2020

 * @Author Diogo Filipe Marinho Barbosa
 * @Number 2018012425
*/

#include <stdio.h>
#include "helpers/utils.c"
#include "./core/structures/structures.h"
#include "core/spaceBuilder.h"

int main() {
    char filename[] = "./data/spaces/E3.bin";
    localsSmartList *localsList = buildList(filename);

    for (int i = 0; i <= localsList->length; i++) {
        printf("%i \n",localsList->array[i].id);
    }

    return 0;
}
