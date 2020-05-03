/*
 * Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2019-2020

 * @Author Diogo Filipe Marinho Barbosa
 * @Number 2018012425
*/

#include "propagationModel.h"

Propagation_Model initPropagationModel(char *spaceFilename, char *peopleFilename) {
    Propagation_Model propagationModel;
    messageWithDelay("%%%% Construcao do modelo da simulacao iniciada %%%% \n\n");

    Space *spaceDataStruct = buildSpaceList(spaceFilename);
    Population *peopleDataStruct = buildPopulationList(peopleFilename);

    propagationModel.spaceList = spaceDataStruct;
    propagationModel.populationList = peopleDataStruct;
    propagationModel.spreadRate = 5;

    buildPropagationModel(spaceDataStruct, peopleDataStruct);

    messageWithDelay("%%%% Preparacao da simulacao finalizada com sucesso %%%% \n\n");
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
    messageWithDelay("A distribuir pessoas pelos locais... \n");

    for (int i = 0; i < listOfPersons->length; i++) {
        randLocal = space->localsSmartList + intUniformRnd(1, space->length) - 1;
        makeConnection(randLocal, listOfPersons->array + i);
    }

    messageWithDelay("Pessoas distribuidas com sucesso! \n");
    return 1;
}