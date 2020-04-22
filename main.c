/*
 * Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2019-2020

 * @Author Diogo Filipe Marinho Barbosa
 * @Number 2018012425
*/

#include <stdio.h>
#include "helpers/utils.c"
#include "core/builders/spaceBuilder.h"
#include "core/builders/populationBuilder.h"
#include "core/models/propagationModel.h"

int main() {
    initRandom();
    char *spaceFile = "./data/spaces/E3.bin";
    char *peopleFile = "./data/people/pessoasA.txt";

    Propagation_Model *propagationModel = initPropagationModel(spaceFile, peopleFile);

    for (int i = 0; i < propagationModel->sizeOfConnections; i++) {
        printf("%i \t", propagationModel->conections[i].local->id);
        printf("%s \n", propagationModel->conections[i].person->name);
    }

    return 0;
}