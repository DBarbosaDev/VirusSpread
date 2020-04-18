/*
 * Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2019-2020

 * @Author Diogo Filipe Marinho Barbosa
 * @Number 2018012425
*/

#ifndef PROPAGATIONMODEL_H
#define PROPAGATIONMODEL_H

typedef struct Propagation_Model {
    /* Percentagem de pessoas de uma determinada população
    nas quais um infetado pode transmitir o virus.
    *   @Nota -> Valor arredondado por defeito
    */
    int spreadRate;

} Propagation_Model;

Propagation_Model* initPropagationModel();



#endif //PROPAGATIONMODEL_H
