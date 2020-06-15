/*
 * Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2019-2020

 * @Author Diogo Filipe Marinho Barbosa
 * @Number 2018012425
*/

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

/*
 * Função que inicia e controi a estrutura do histórico
*/
Historic initHistoric();

/*
 * Função que gere o tamanho máximo do meu histórico.
 * + antigo ->>>>>>> + recente
 * @param historic -> ponteiro da minha estrutura principal do histórico
*/
void manageHistoricLength(Historic *historic);

/*
 * Função incrementa cada iteração ao histórico
 * @param historic -> ponteiro da minha estrutura principal do histórico
 * @param propagationModel -> modelo de propagação no dia x para ser inserido no histórico
*/
void addToHistoric(Historic *historic, Propagation_Model propagationModel);

#endif //VIRUSSPREAD_HISTORICBUILDER_H
