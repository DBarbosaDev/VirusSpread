/*
 * Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2019-2020

 * @Author Diogo Filipe Marinho Barbosa
 * @Number 2018012425
*/

#ifndef PROPAGATIONMODEL_H
#define PROPAGATIONMODEL_H

#include "../builders/populationBuilder.h"
#include "../builders/spaceBuilder.h"

typedef struct {
    Space *spaceList;
    peopleSmartList *populationList;
    int spreadRate;
} Propagation_Model;

Propagation_Model initPropagationModel(char *spaceFilename, char *peopleFilename);
int makeConnection(localsSmartList *smartList, Person *person);
int buildPropagationModel(Space *space,  peopleSmartList *listOfPersons);

#endif //PROPAGATIONMODEL_H
