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
#include "personVitalModel.h"
#include "../builders/populationBuilder.h"
#include "../builders/spaceBuilder.h"
#include "../../helpers/utils.h"

typedef struct {
    Space *spaceList;
    Population *populationList;
    float spreadRate;
} Propagation_Model;

Propagation_Model initPropagationModel(char *spaceFilename, char *peopleFilename);

int makeConnection(localsSmartList *smartList, Person *person);

int buildPropagationModel(Space *space,  Population *listOfPersons);

int getLocalIndexById(Propagation_Model *propagationModel, int localId);

void switchPersonToTheHealthyList(localsSmartList *space, int index);

void switchPersonToInfectedList(localsSmartList *smartList, int index);

void addSickPerson(Propagation_Model *propagationModel, Person person, int indexOfLocal);

void addPersonToLocal(localsSmartList *sourceLocal, localsSmartList *destinationLocal, int indexOfPerson, int isSick);

void movePersons(Propagation_Model *propagationModel, int numberOfPersons, int indexOfLocal, int destinationLocationIndex);

#endif //PROPAGATIONMODEL_H
