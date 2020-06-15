/*
 * Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2019-2020

 * @Author Diogo Filipe Marinho Barbosa
 * @Number 2018012425
*/

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

    historic->length--;
}

void addToHistoric(Historic *historic, Propagation_Model propagationModel) {
    Propagation_Model *nodePropagationModel = malloc(sizeof(Propagation_Model));
    *nodePropagationModel = propagationModel;

    if(historic->length != HISTORIC_SIZE)
        historic->array = realloc(historic->array, sizeof(Historic) * historic->length + 1);

    manageHistoricLength(historic);

    (historic->array + historic->length)->propagationModel = nodePropagationModel;

    historic->length++;
}

