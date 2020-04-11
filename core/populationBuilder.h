/*
 * Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2019-2020

 * @Author Diogo Filipe Marinho Barbosa
 * @Number 2018012425
*/

#ifndef POPULATIONBUILDER_H
#define POPULATIONBUILDER_H

typedef struct Person {
    char name[100];
    int age;
    char state[1];
    int sickedDays;
} Person;
typedef struct peopleSmartList {
    struct Person *array;
    int length;
} peopleSmartList;

peopleSmartList *buildPopulationList(char *filename);

void appendToList(peopleSmartList *currentList, Person person, int index);
void getPersonFromFile(char *filename, peopleSmartList *currentList);

#endif //POPULATIONBUILDER_H
