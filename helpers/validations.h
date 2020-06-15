/*
 * Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2019-2020

 * @Author Diogo Filipe Marinho Barbosa
 * @Number 2018012425
*/

#ifndef VALIDATIONS_H
#define VALIDATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../core/builders/spaceBuilder.h"
#include "../core/models/propagationModel.h"

#define TAM_CONNECTIONS 3

/*
 * Função que verifica se um valor é um número
 * @param numberInString -> valor em string
 * @param associateTo -> ponteiro que vai receber o valor convertido para inteiro
*/
int isValidNumber(char *numberInString, int *associateTo);

/*
 * Função que verifica se um determinado espaço tem capacidade
 * @param smartList -> ponteiro da minha lista principal do espaço
*/
int hasFreeSpace(localsSmartList smartList);

/*
 * Função que verifica se os locais dum espaço estão conectados corretamente
 * @param space -> ponteiro para o espaço da simulação
*/
int hasSpaceCorrectConnections(Space *space);

/*
 * Função que verifica se um local apresenta as conexoe
 * @param space -> ponteiro para o espaço da simulação
 * @param indexOfFather -> indice do local
*/
int spaceHasConnections(Space *space, int indexOfFather);

/*
 * Função testa a existencia de um ficheiro
 * @param filename -> nome do ficheiro
*/
int theFileExists(char *fileName);

/*
 * Função que verifica se existe pelo menos um local que não esteja lotado
 * @param space -> ponteiro para o espaço da simulação
*/
int hasLocalWithSpace(Space *space);

#endif //VIRUSSPREAD_VALIDATIONS_H
