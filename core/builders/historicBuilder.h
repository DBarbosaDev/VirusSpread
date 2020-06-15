//
// Created by QuBit on 13/06/2020.
//

#ifndef HISTORICBUILDER_H
#define HISTORICBUILDER_H

#include <string.h>
#include "../models/propagationModel.h"

#define HISTORIC_SIZE 3

typedef struct {
    Propagation_Model *propagationModel;
} Pointers;

typedef struct {
    Pointers *array;
    int length;
} Historic;

Historic initHistoric();

void manageHistoricLength(Historic *historic);

void addToHistoric(Historic *historic, Propagation_Model propagationModel);

#endif //VIRUSSPREAD_HISTORICBUILDER_H
