/*
 * Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2019-2020

 * @Author Diogo Filipe Marinho Barbosa
 * @Number 2018012425
*/

#include <stdio.h>
#include <stdlib.h>
#include "spaceBuilder.h"

localsSmartList *buildSpaceList(char *filename) {
    localsSmartList *newSmartList = malloc(sizeof(localsSmartList));

    newSmartList->array = malloc(0);
    newSmartList->length = 0;

    getLocalContentFromBinFile(filename, newSmartList);

    return newSmartList;
}

void appendLocalToList(localsSmartList *currentList, Local local) {
    int index = currentList->length;

    currentList->array = realloc(currentList->array, sizeof(Local)*(index+1));
    if (currentList->array == NULL) return perror("Erro na alocacao de memoria");

    currentList->array[index] = local;
    currentList->length = index + 1;
}

void getLocalContentFromBinFile(char *filename, localsSmartList *currentList) {
    FILE *file;
    Local local;

    file = fopen(filename, "rb");
    if (file == NULL) return perror("File doesn\'t exist");

    //fread retorna 1 sempre que o ficheiro contem informação para ler
    while (fread(&local, sizeof(Local), 1, file) == 1)
        appendLocalToList(currentList, local);

    fclose(file);
}
