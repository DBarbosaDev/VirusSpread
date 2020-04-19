/*
 * Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2019-2020

 * @Author Diogo Filipe Marinho Barbosa
 * @Number 2018012425
*/

#ifndef POPULATIONBUILDER_H
#define POPULATIONBUILDER_H

#include "../models/personVitalModel.h"

typedef struct Person {
    int id;
    char name[100];
    int age;
    char state[1];
    int sickedDays;
    Vital_Model vitalModel;
} Person;

typedef struct peopleSmartList {
    Person *array;
    int length;
} peopleSmartList;

peopleSmartList *buildPopulationList(char *filename);

void appendPersonToList(peopleSmartList *currentList, Person person);
void getPersonsFromFile(char *filename, peopleSmartList *currentList);

#endif //POPULATIONBUILDER_H
