/*
 * Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2019-2020

 * @Author Diogo Filipe Marinho Barbosa
 * @Number 2018012425
*/

#ifndef POPULATIONBUILDER_H
#define POPULATIONBUILDER_H

#include <stdio.h>
#include <stdlib.h>
#include "../models/personVitalModel.h"

#define STRING_SIZE_BUFFER 100

typedef struct Person {
    int id;
    char name[100];
    int age;
    char state[1];
    int sickedDays;
    Vital_Model vitalModel;
} Person;

typedef struct Population {
    Person *array;
    int length;
} Population;

/*
 * Função que constroi a lista da população e retorna o ponteiro dessa lista
 * @param filename -> nome do ficheiro da população
*/
Population *buildPopulationList(char *filename);

/*
 * Função que adiciona de forma dinâmica ao array da estrutura passada em argumento;
 * @param currentList -> ponteiro para a lista principal criada em buildPopulationList
 * @param person -> estrutura a inserir ao array
*/
void appendPersonToList(Population *currentList, Person person);

/*
 * Função que retira a informação do ficheiro da população
 * @param filename -> nome do ficheiro
 * @param currentList -> ponteiro para a minha lista principal
*/
void getPersonsFromFile(char *filename, Population *currentList);

#endif //POPULATIONBUILDER_H
