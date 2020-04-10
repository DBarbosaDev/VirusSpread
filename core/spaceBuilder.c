/*
 * Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2019-2020

 * @Author Diogo Filipe Marinho Barbosa
 * @Number 2018012425
*/

#include <stdio.h>
#include <stdlib.h>
#include "spaceBuilder.h"

localsSmartList *buildList(char *filename) {
    localsSmartList *newSmartList = malloc(sizeof(localsSmartList));

    newSmartList->array = malloc(sizeof(Local));
    newSmartList->length = 0;

    getLocalContentFromBinFile(filename, newSmartList);

    newSmartList->length += 1;
    return newSmartList;
}

void getLocalContentFromBinFile(char *filename, localsSmartList *currentList) {
    FILE *file;
    Local *listOfLocals = currentList->array, aux;

    int structCounter = 0;

    file = fopen(filename, "rb");
    if (file == NULL) {
        return perror("File doesn\'t exist");
    }

    fread(&aux, sizeof(Local), 1, file);

    while (feof(file) == 0)
    {
        appendToList(currentList, aux, structCounter);
        fread(&aux, sizeof(Local), 1, file);

        structCounter++;
    }

    fclose(file);
}

void appendToList(localsSmartList *currentList, Local local, int index) {
    if (index != 0){
        currentList->array = realloc(currentList->array, sizeof(Local) * (index+1));
    }
    if (currentList->array == NULL) {
        return perror("Error Allocating the memory");
    }
    currentList->length = index;
    currentList->array[index] = local;
}
