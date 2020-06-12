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

int isNumberBetween(int value, int minValue, int maxValue) {
    if (value < minValue || value > maxValue)
        return 0;
    return 1;
}

int hasFreeSpace(localsSmartList smartList) {
    if (smartList.numberOfPeople >= smartList.local.capacity)
        return 0;
    return 1;
}