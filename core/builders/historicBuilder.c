//
// Created by QuBit on 13/06/2020.
//

#include "historicBuilder.h"

Historic initHistoric() {
    Historic historic;

    historic.array = malloc(sizeof(Historic) * HISTORIC_SIZE);
    historic.length = 0;

    return historic;
}

void manageHistoricLength(Historic *historic) {
    if(historic->length != HISTORIC_SIZE) return;

    free((historic->array + 0)->propagationModel);

    for (int i = 0; i < HISTORIC_SIZE; i++) {
        if(i == HISTORIC_SIZE - 1) break;
        (historic->array + i)->propagationModel = (historic->array + i + 1)->propagationModel;
    }
    //free((historic->array + (HISTORIC_SIZE - 1))->propagationModel);
    historic->length--;
}

void addToHistoric(Historic *historic, Propagation_Model propagationModel) {
    /*for (int i = 0; i < propagationModel.spaceList->length; i++) {
        printf("%i \t %i \n", propagationModel.spaceList->localsSmartList[i].numberOfInfectedPeople, propagationModel.spaceList->localsSmartList[i].numberOfHealthyPeople);
    }
    puts("--");
    for (int i = 0; i < historic->length; i++) {
        for (int ii = 0; ii < historic->array[i].propagationModel->spaceList->length; ii++) {
            printf("%i \t %i \n", historic->array[i].propagationModel->spaceList->localsSmartList[ii].numberOfInfectedPeople, historic->array[i].propagationModel->spaceList->localsSmartList[ii].numberOfHealthyPeople);
        }
        puts("---");
    }
    puts("--------------");*/
    Propagation_Model *nodePropagationModel = malloc(sizeof(Propagation_Model));
    *nodePropagationModel = propagationModel;

    if(historic->length != HISTORIC_SIZE)
        historic->array = realloc(historic->array, sizeof(Historic) * historic->length + 1);

    manageHistoricLength(historic);

    (historic->array + historic->length)->propagationModel = nodePropagationModel;

    historic->length++;
}

