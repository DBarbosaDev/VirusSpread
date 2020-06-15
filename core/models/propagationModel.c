/*
 * Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2019-2020

 * @Author Diogo Filipe Marinho Barbosa
 * @Number 2018012425
*/

#include "propagationModel.h"

Propagation_Model initPropagationModel(char *spaceFilename, char *peopleFilename) {
    Propagation_Model propagationModel;

    Space *spaceDataStruct = buildSpaceList(spaceFilename);
    Population *peopleDataStruct = buildPopulationList(peopleFilename);

    propagationModel.spaceList = spaceDataStruct;
    propagationModel.populationList = peopleDataStruct;
    propagationModel.spreadRate = (float) 5/100;

    buildPropagationModel(spaceDataStruct, peopleDataStruct);

    return propagationModel;
}

int makeConnection(localsSmartList *smartList, Person *person) {
    if (smartList->numberOfPeople == smartList->local.capacity) return 0;

    if (person->state[0] == 'D') {
        smartList->listOfInfectedPeople = realloc(smartList->listOfInfectedPeople, sizeof(Person) * (smartList->numberOfInfectedPeople + 1));
        smartList->listOfInfectedPeople[smartList->numberOfInfectedPeople].person = person;
        smartList->numberOfInfectedPeople ++;
    } else {
        smartList->listOfHealthyPeople = realloc(smartList->listOfHealthyPeople, sizeof(Person) * (smartList->numberOfHealthyPeople + 1));
        smartList->listOfHealthyPeople[smartList->numberOfHealthyPeople].person = person;
        smartList->numberOfHealthyPeople ++;
    }

    smartList->numberOfPeople ++;

    return 1;
}

int buildPropagationModel(Space *space,  Population *listOfPersons) {
    localsSmartList *randLocal;

    for (int i = 0; i < listOfPersons->length; i++) {
        randLocal = space->localsSmartList + intUniformRnd(1, space->length) - 1;
        makeConnection(randLocal, listOfPersons->array + i);
    }

    return 1;
}

int getLocalIndexById(Propagation_Model *propagationModel, int localId) {
    for (int i = 0; i < propagationModel->spaceList->length; i++) {
        if (propagationModel->spaceList->localsSmartList[i].local.id == localId)
            return i;
    }

    return -1;
}

void switchPersonToTheHealthyList(localsSmartList *smartList, int index) {
    int positionsToShift = smartList->numberOfInfectedPeople - 1 - index;

    smartList->listOfHealthyPeople = realloc(smartList->listOfHealthyPeople, sizeof(Connection) * (smartList->numberOfHealthyPeople + 1));
    smartList->listOfHealthyPeople[smartList->numberOfHealthyPeople] = smartList->listOfInfectedPeople[index];

    for (int i = 0; i < positionsToShift; i++)
        smartList->listOfInfectedPeople[index + i] = smartList->listOfInfectedPeople[index + i + 1];

    smartList->numberOfInfectedPeople--;
    smartList->numberOfHealthyPeople++;

    smartList->listOfInfectedPeople = realloc(smartList->listOfInfectedPeople, sizeof(Connection) * smartList->numberOfInfectedPeople);
}

void switchPersonToInfectedList(localsSmartList *smartList, int index) {
    int positionsToShift = smartList->numberOfHealthyPeople - 1 - index;

    smartList->listOfInfectedPeople = realloc(smartList->listOfInfectedPeople, sizeof(Connection) * (smartList->numberOfInfectedPeople + 1));
    smartList->listOfInfectedPeople[smartList->numberOfInfectedPeople] = smartList->listOfHealthyPeople[index];

    for (int i = 0; i < positionsToShift; i++)
        smartList->listOfHealthyPeople[index + i] = smartList->listOfHealthyPeople[index + i + 1];

    smartList->numberOfInfectedPeople++;
    smartList->numberOfHealthyPeople--;

    smartList->listOfHealthyPeople = realloc(smartList->listOfHealthyPeople, sizeof(Connection) * smartList->numberOfHealthyPeople);
}

void addSickPerson(Propagation_Model *propagationModel, Person person, int indexOfLocal) {
    localsSmartList *smartList = propagationModel->spaceList->localsSmartList + indexOfLocal;

    appendPersonToList(propagationModel->populationList, person);

    smartList->listOfInfectedPeople = realloc(smartList->listOfInfectedPeople, sizeof(Connection) * (smartList->numberOfInfectedPeople + 1));
    smartList->listOfInfectedPeople[smartList->numberOfInfectedPeople].person = propagationModel->populationList->array + propagationModel->populationList->length - 1;

    smartList->numberOfInfectedPeople++;
    smartList->numberOfPeople++;
}

void addPersonToLocal(localsSmartList *sourceLocal, localsSmartList *destinationLocal, int indexOfPerson, int isSick) {
    if (isSick) {
        destinationLocal->listOfInfectedPeople = realloc(destinationLocal->listOfInfectedPeople, sizeof(Connection) * (destinationLocal->numberOfInfectedPeople + 1));
        destinationLocal->listOfInfectedPeople[destinationLocal->numberOfInfectedPeople] = sourceLocal->listOfInfectedPeople[indexOfPerson];

        for (int i = 0; i < sourceLocal->numberOfInfectedPeople; i++)
            sourceLocal->listOfInfectedPeople[i] = sourceLocal->listOfInfectedPeople[i + 1];

        destinationLocal->numberOfInfectedPeople++;
        sourceLocal->numberOfInfectedPeople--;

        sourceLocal->listOfInfectedPeople = realloc(sourceLocal->listOfInfectedPeople, sizeof(Connection) * sourceLocal->numberOfInfectedPeople);
    } else {
        destinationLocal->listOfHealthyPeople = realloc(destinationLocal->listOfHealthyPeople, sizeof(Connection) * (destinationLocal->numberOfHealthyPeople + 1));
        destinationLocal->listOfHealthyPeople[destinationLocal->numberOfHealthyPeople] = sourceLocal->listOfHealthyPeople[indexOfPerson];

        for (int i = 0; i < sourceLocal->numberOfHealthyPeople; i++)
            sourceLocal->listOfHealthyPeople[i] = sourceLocal->listOfHealthyPeople[i + 1];

        destinationLocal->numberOfHealthyPeople++;
        sourceLocal->numberOfHealthyPeople--;

        sourceLocal->listOfHealthyPeople = realloc(sourceLocal->listOfHealthyPeople, sizeof(Connection) * sourceLocal->numberOfHealthyPeople);
    }
    destinationLocal->numberOfPeople++;
    sourceLocal->numberOfPeople--;
}

void movePersons(Propagation_Model *propagationModel, int numberOfPeople, int indexOfSourceLocal, int destinationLocationIndex) {
    if (indexOfSourceLocal == -1 || destinationLocationIndex == -1) {
        puts("O id do local destino ou do local origem nao existe.");
        return;
    }

    localsSmartList *sourceLocal = &propagationModel->spaceList->localsSmartList[indexOfSourceLocal];
    localsSmartList *destinationLocal = &propagationModel->spaceList->localsSmartList[destinationLocationIndex];

    if (destinationLocal->numberOfPeople + numberOfPeople > destinationLocal->local.capacity) {
        puts("Numero de pessoas a transferir excede a capacidade maxima do local");
        printf("O local %i aceita apenas %i pessoas\n", destinationLocal->local.id, destinationLocal->local.capacity - destinationLocal->numberOfPeople);
        return;
    }

    if (destinationLocal->numberOfPeople + numberOfPeople > destinationLocal->local.capacity) {
        puts("Numere de pessoas superior a populacao existente no espaco.");
        printf("O local %i contem apenas %i pessoas\n", destinationLocal->local.id, destinationLocal->numberOfPeople);
        return;
    }

    for (int i = 0; i < numberOfPeople; i++) {
        int isSick = 0;
        int indexOfPerson = intUniformRnd(0,sourceLocal->numberOfPeople - 1);
        int indexOfPersonByState;

        if(indexOfPerson < sourceLocal->numberOfInfectedPeople){
            indexOfPersonByState = indexOfPerson;
            isSick = 1;
        }
        else {
            indexOfPersonByState = indexOfPerson - sourceLocal->numberOfHealthyPeople - 1;
        }

        addPersonToLocal(sourceLocal, destinationLocal, indexOfPersonByState, isSick);
    }

}