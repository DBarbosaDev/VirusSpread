/*
 * Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2019-2020

 * @Author Diogo Filipe Marinho Barbosa
 * @Number 2018012425
*/

#ifndef VALIDATIONS_H
#define VALIDATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../core/builders/spaceBuilder.h"

#define TAM_CONNECTIONS 3

int isValidNumber(char *numberInString, int *associateTo);

int isNumberBetween(int value, int minValue, int maxValue);

int hasFreeSpace(localsSmartList smartList);

int hasPeopleToMove(localsSmartList smartList, int peopleToMove);

int isAConnection(Space *space, int indexOfFather, int indexOfChield);

int spaceHasConnections(Space *space, int indexOfFather);

int theFileExists(char *fileName);

int hasLocalWithSpace(Space *space);

#endif //VIRUSSPREAD_VALIDATIONS_H
