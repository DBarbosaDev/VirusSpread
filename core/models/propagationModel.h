/*
 * Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2019-2020

 * @Author Diogo Filipe Marinho Barbosa
 * @Number 2018012425
*/

#ifndef PROPAGATIONMODEL_H
#define PROPAGATIONMODEL_H

#include <stdio.h>
#include <stdlib.h>
#include "../builders/populationBuilder.h"
#include "../builders/spaceBuilder.h"
#include "../../helpers/utils.h"

typedef struct {
    Space *spaceList;
    Population *populationList;
    int spreadRate;
} Propagation_Model;

Propagation_Model initPropagationModel(char *spaceFilename, char *peopleFilename);
int makeConnection(localsSmartList *smartList, Person *person);
int buildPropagationModel(Space *space,  Population *listOfPersons);

void addPersonToTheHealthyList(localsSmartList *space, int index);

#endif //PROPAGATIONMODEL_H
