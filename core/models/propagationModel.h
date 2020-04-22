/*
 * Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2019-2020

 * @Author Diogo Filipe Marinho Barbosa
 * @Number 2018012425
*/

#ifndef PROPAGATIONMODEL_H
#define PROPAGATIONMODEL_H

#include "../builders/populationBuilder.h"
#include "../builders/spaceBuilder.h"

typedef struct Connections {
    Person *person;
    Local *local;
} Connections;
typedef struct Propagation_Model {
    Connections *conections;
    /* Percentagem de pessoas de uma determinada população
    nas quais um infetado pode transmitir o virus.
    *   @Nota -> Valor arredondado por defeito
    */
    int spreadRate;
    int sizeOfConnections;
} Propagation_Model;

Propagation_Model *initPropagationModel(char *spaceFile, char *peopleFile);

Propagation_Model *getPropagationModel(localsSmartList *listOfLocals, peopleSmartList *listOfPersons);

#endif //PROPAGATIONMODEL_H
