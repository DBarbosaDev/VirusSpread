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

Propagation_Model *initPropagationModel(char *spaceFile, char *peopleFile) {
    localsSmartList *spaceDataStruct = buildSpaceList(spaceFile);
    peopleSmartList *peopleDataStruct = buildPopulationList(peopleFile);

    /* for (int i = 0; i < spaceDataStruct->length; i++) {
        printf("%i \t",spaceDataStruct->array[i].id);
        printf("%i \t",spaceDataStruct->array[i].capacity);
        printf("%i \t",spaceDataStruct->array[i].refLocal[0]);
        printf("%i \t",spaceDataStruct->array[i].refLocal[1]);
        printf("%i \t",spaceDataStruct->array[i].refLocal[2]);

        puts("\n");
    }

    for (int ii = 0; ii < peopleDataStruct->length; ii++) {
        printf("%i \t",peopleDataStruct->array[ii].id);
        printf("%s \t",peopleDataStruct->array[ii].name);
        printf("%i \t",peopleDataStruct->array[ii].age);
        printf("%s \t",peopleDataStruct->array[ii].state);
        printf("%i \t",peopleDataStruct->array[ii].sickedDays);

        printf("--> %f \t",peopleDataStruct->array[ii].vitalModel.probabilityOfRecovery);
        printf("--> %i \t",peopleDataStruct->array[ii].vitalModel.maxDurationOfInfectionInDays);
        printf("--> %i \t",peopleDataStruct->array[ii].vitalModel.immunityRate);
        puts("\n");
    } */

    return getPropagationModel(spaceDataStruct, peopleDataStruct);
}

Propagation_Model *getPropagationModel(localsSmartList *listOfLocals, peopleSmartList *listOfPersons) {
    Propagation_Model *model = malloc(sizeof(Propagation_Model));
    Local *randLocal;

    model->conections = malloc(0);
    model->spreadRate = 5;

    for (int i = 0; i < listOfPersons->length; i++) {
        model->conections = realloc(model->conections, sizeof(Connections) * (i + 1));
        randLocal = listOfLocals->array + intUniformRnd(1, listOfLocals->length) - 1;

        model->conections[i].person = listOfPersons->array + i;
        model->conections[i].local = randLocal;
    }

    model->sizeOfConnections = listOfPersons->length;

    return model;
}
