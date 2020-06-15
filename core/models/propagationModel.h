/*
 * Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2019-2020

 * @Author Diogo Filipe Marinho Barbosa
 * @Number 2018012425
*/

#ifndef PROPAGATIONMODEL_H
#define PROPAGATIONMODEL_H

#include <stdio.h>
#include <stdlib.h>
#include "personVitalModel.h"
#include "../builders/populationBuilder.h"
#include "../builders/spaceBuilder.h"
#include "../../helpers/utils.h"

typedef struct {
    Space *spaceList;
    Population *populationList;
    float spreadRate;
} Propagation_Model;

/*
 * Função que inicia o modelo de propagação e retorna o modelo gerado
 * @param spaceFilename -> nome do ficheiro de espaços
 * @param peopleFilename -> nome do ficheiro da população
*/
Propagation_Model initPropagationModel(char *spaceFilename, char *peopleFilename);

/*
 * Função que adiciona o ponteiro de uma pessoa e dependendo do seu estado, adiciona a uma lista
 * @param smartList -> ponteiro da minha lista do local principal
 * @param local -> ponteiro da pessoa
*/
int makeConnection(localsSmartList *smartList, Person *person);

/*
 * Função que constroi o modelo de propagação associando as pessoas a um local aleatório
 * @param space -> ponteiro para a lista principal do espaço
 * @param listOfPersons -> ponteiro da população da simulação
*/
int buildPropagationModel(Space *space,  Population *listOfPersons);

/*
 * Função que retorna o indice de um local consoante o Id passado em argumento
 * @param space -> ponteiro para a lista principal do espaço
 * @param localId -> id do local
*/
int getLocalIndexById(Space *space, int localId);

/*
 * Função que transfere uma pessoa da lista de infetados para a lista de saudáveis
 * @param space -> ponteiro para a lista principal do meu espaço
 * @param index -> indice da pessoa na lista de infetados
*/
void switchPersonToTheHealthyList(localsSmartList *space, int index);

/*
 * Função que transfere uma pessoa da lista de saudáveis para a lista de infetados
 * @param smartList -> ponteiro para a lista principal do meu espaço
 * @param index -> indice da pessoa na lista de saudáveis
*/
void switchPersonToInfectedList(localsSmartList *smartList, int index);

/*
 * Função que transfere uma pessoa da lista de infetados para a lista de saudáveis
 * @param space -> ponteiro para a lista principal do meu espaço
 * @param index -> indice da pessoa na lista de infetados
*/
void addSickPerson(Propagation_Model *propagationModel, Person person, int indexOfLocal);

/*
 * Função que retira uma pessoa de um local e adiciona a outro tendo em consideração o seu estado
 * @param sourceLocal -> ponteiro do local origem que carrega a pessoa a transferir
 * @param destinationLocal -> ponteiro do local destino que vai receber a pessoa
 * @param indexOfPerson -> indice da pessoa da lista origem
 * @param isSick -> valor inteiro que indica se a pessoa está doente
*/
void addPersonToLocal(localsSmartList *sourceLocal, localsSmartList *destinationLocal, int indexOfPerson, int isSick);

/*
 * Função que move um determinado numero de pessoas de um local para o outro
 * @param propagationModel -> ponteiro do modelo de propagação
 * @param numberOfPersons -> numero de pessoas para serem transferidas
 * @param indexOfLocal -> indice do local origem
 * @param destinationLocationIndex -> indice do local destino
*/
void movePersons(Propagation_Model *propagationModel, int numberOfPersons, int indexOfLocal, int destinationLocationIndex);

#endif //PROPAGATIONMODEL_H
