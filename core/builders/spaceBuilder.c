/*
 * Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2019-2020

 * @Author Diogo Filipe Marinho Barbosa
 * @Number 2018012425
*/

#include <stdio.h>
#include <stdlib.h>
#include "spaceBuilder.h"

Space *buildSpaceList(char *filename) {
    Space *newSpace = malloc(sizeof(Space));

    newSpace->localsSmartList = malloc(0);
    newSpace->length = 0;

    getLocalContentFromBinFile(filename, newSpace);

    return newSpace;
}

void appendLocalToList(Space *currentSpace, Local local) {
    int index = currentSpace->length;

    currentSpace->localsSmartList = realloc(currentSpace->localsSmartList, sizeof(localsSmartList)*(index+1));
    if (currentSpace->localsSmartList == NULL) return perror("Erro na alocacao de memoria");

    currentSpace->localsSmartList[index].local = local;
    currentSpace->localsSmartList[index].connections = malloc(0);
    currentSpace->localsSmartList[index].sizeOfConnections = 0;

    currentSpace->length = index + 1;
}

void getLocalContentFromBinFile(char *filename, Space *currentSpace) {
    FILE *file;
    Local local;

    file = fopen(filename, "rb");
    if (file == NULL) return perror("O ficheiro binario nao existe");

    //fread retorna 1 sempre que o ficheiro contem informação para ler
    while (fread(&local, sizeof(Local), 1, file) == 1)
        appendLocalToList(currentSpace, local);

    fclose(file);
}
