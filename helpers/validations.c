/*
 * Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2019-2020

 * @Author Diogo Filipe Marinho Barbosa
 * @Number 2018012425
*/

#include "validations.h"


int isValidNumber(char *numberInString, int *associateTo) {
    if (strlen(numberInString) == 0) return 0;
    for (int i = 0; i < strlen(numberInString); i++) {
        if (!isdigit(numberInString[i]))
            return 0;
    }
    *associateTo = atoi(numberInString);
    return 1;
}

int hasFreeSpace(localsSmartList smartList) {
    if (smartList.numberOfPeople >= smartList.local.capacity)
        return 0;
    return 1;
}

int hasSpaceCorrectConnections(Space *space) {
    int countNonRefLocal = 0;
    for (int i = 0; i < space->length; i++) {
        for (int ii = 0; ii < TAM_CONNECTIONS; ii++) {
            int refLocalId = space->localsSmartList[i].local.refLocal[ii];

            if (refLocalId == -1) {
                countNonRefLocal ++;
                break;
            }

            if (countNonRefLocal == TAM_CONNECTIONS) return 1;

            int connectionIndex = getLocalIndexById(space, refLocalId);

            for (int j = 0; j < TAM_CONNECTIONS; j++) {
                if (space->localsSmartList[connectionIndex].local.refLocal[j] == space->localsSmartList[i].local.id)
                    return 1;
            }
        }
    }

    return 0;
}

int spaceHasConnections(Space *space, int indexOfFather) {

    for (int i = 0; i < TAM_CONNECTIONS; i++) {
        if (space->localsSmartList[indexOfFather].local.refLocal[i] != -1) {
            return 1;
        }
    }

    return 0;
}

int theFileExists(char *fileName) {
    FILE *file;

    file = fopen(fileName, "r+");
    if (file != NULL) return 1;

    puts("O ficheiro nao existe!\n");
    strcpy(fileName, "\0");

    return 0;
}

int hasLocalWithSpace(Space *space) {
    for (int i = 0; i < space->length; i++) {
        if (space->localsSmartList[i].numberOfPeople < space->localsSmartList[i].local.capacity)
            return 1;
    }

    return 0;
}

