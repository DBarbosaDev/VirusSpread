/*
 * Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2019-2020

 * @Author Diogo Filipe Marinho Barbosa
 * @Number 2018012425
*/

#ifndef SPACEBUILDER_H
#define SPACEBUILDER_H

#include <stdio.h>
#include <stdlib.h>
#include "populationBuilder.h"
#include "../../helpers/feedbackMessages.h"

/* Criação da estrutura de dados
 * -> Local: Estrutura que irá conter a informação necessária de cada local;
 * -> localsSmartList (Espaço): Estrutura que irá conter os vários locais agrupados em array e o seu tamanho;
*/
typedef struct {
    int id;
    int capacity;
    int refLocal[3];
} Local;

typedef struct {
    Person *person;
} Connection;

typedef struct {
    Local local;
    Connection *listOfInfectedPersons, *listOfHealthyPersons;
    int numberOfInfectedPersons,numberOfHealthyPersons,numberOfPersons;
} localsSmartList;

typedef struct {
    localsSmartList *localsSmartList;
    int length;
} Space;

/* Construtor da minha estrutura de dados;
 * Recebe como argumento o caminho ou nome do ficheiro;
 *
 * @return Retorna um Espaço populado de informação:
 *          - A propriedade array contem a info dos locais;
 *          - length contem o tam do array | nr total de locais
*/
Space *buildSpaceList(char *filename);

/*
 * Função que adiciona de forma dinâmica ao array da estrutura passada em argumento;
 * @param currentList -> ponteiro para a lista principal criada em buildList
 * @param local -> estrutura a inserir ao array da lista principal
 * @param index -> posição atual da leitura do ficheiro (estrutura atual)
*/
void appendLocalToList(Space *currentSpace, Local local);

/* Função que retira informação dos ficheiros binários
 * @param filename -> nome do ficheiro
 * @param currentList -> ponteiro para a lista principal criada em buildList
 *
*/
void getLocalContentFromBinFile(char *filename, Space *currentSpace);

#endif //SPACEBUILDER_H
