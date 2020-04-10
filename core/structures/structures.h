/*
 * Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2019-2020

 * @Author Diogo Filipe Marinho Barbosa
 * @Number 2018012425
*/

#ifndef STRUCTURES_H
#define STRUCTURES_H



typedef struct Local  {
    int id;
    int capacity;
    int refLocal[3];
} Local;

typedef struct People {

} People;

typedef struct localsSmartList {
    struct Local *array;
    int length;
} localsSmartList;

#endif //STRUCTURES_H
