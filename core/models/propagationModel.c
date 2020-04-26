/*
 * Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2019-2020

 * @Author Diogo Filipe Marinho Barbosa
 * @Number 2018012425
*/

#include <stdio.h>
#include <stdlib.h>
#include "../../helpers/utils.h"
#include "propagationModel.h"

Propagation_Model initPropagationModel(char *spaceFilename, char *peopleFilename) {
    Propagation_Model propagationModel;

    Space *spaceDataStruct = buildSpaceList(spaceFilename);
    peopleSmartList *peopleDataStruct = buildPopulationList(peopleFilename);

    propagationModel.spaceList = spaceDataStruct;
    propagationModel.populationList = peopleDataStruct;
    propagationModel.spreadRate = 5;

    buildPropagationModel(spaceDataStruct, peopleDataStruct);

    return propagationModel;
}

int makeConnection(localsSmartList *smartList, Person *person) {
    if (smartList->sizeOfConnections == smartList->local.capacity) {
        printf("Capacidade maxima atingida no local %i: Fica de fora o/a %s \n", smartList->local.id, person->name);
        return 0;
    }
    smartList->connections = realloc(smartList->connections, sizeof(Person) * (smartList->sizeOfConnections + 1));
    smartList->connections[smartList->sizeOfConnections].person = person;

    smartList->sizeOfConnections ++;

    printf("=== |%s| adicionada ao local |%i| === \n", person->name, smartList->local.id);

    return 1;
}

int buildPropagationModel(Space *space,  peopleSmartList *listOfPersons) {
    localsSmartList *randLocal;

    for (int i = 0; i < listOfPersons->length; i++) {
        randLocal = space->localsSmartList + intUniformRnd(1, space->length) - 1;
        makeConnection(randLocal, listOfPersons->array + i);
    }

    return 1;
    /* model->conections = malloc(0);
    model->spreadRate = 5;

    for (int i = 0; i < listOfPersons->length; i++) {
        model->conections = realloc(model->conections, sizeof(Connections) * (i + 1));
        randLocal = listOfLocals->array + intUniformRnd(1, listOfLocals->length) - 1;

        model->conections[i].person = listOfPersons->array + i;
        model->conections[i].local = randLocal;

        // validação aqui
        randLocal->capacity -= 1;
    }

    model->sizeOfConnections = listOfPersons->length;*/

}



