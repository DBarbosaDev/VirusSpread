/*
 * Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2019-2020

 * @Author Diogo Filipe Marinho Barbosa
 * @Number 2018012425
*/

#include <stdio.h>
#include <stdlib.h>
#include "propagationModel.h"

Propagation_Model initPropagationModel() {
    Propagation_Model model;

    model.spreadRate = 5;

    return model;
}