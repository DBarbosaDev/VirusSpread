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
#include "../../helpers/feedbackMessages.h"

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

Population *buildPopulationList(char *filename);

void appendPersonToList(Population *currentList, Person person);
void getPersonsFromFile(char *filename, Population *currentList);

#endif //POPULATIONBUILDER_H
