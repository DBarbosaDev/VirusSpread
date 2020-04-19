/*
 * Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2019-2020

 * @Author Diogo Filipe Marinho Barbosa
 * @Number 2018012425
*/

#include <stdio.h>
#include <stdlib.h>
#include "populationBuilder.h"

peopleSmartList *buildPopulationList(char *filename) {
    peopleSmartList *newSmartList = malloc(sizeof(peopleSmartList));

    newSmartList->array = malloc(0);
    newSmartList->length = 0;

    getPersonsFromFile(filename, newSmartList);

    return newSmartList;
}

void appendPersonToList(peopleSmartList *currentList, Person person) {
    int index = currentList->length;

    currentList->array = realloc(currentList->array, sizeof(Person)*(index+1));
    if (currentList->array == NULL) return perror("Erro na alocacao de memoria");

    currentList->array[index] = person;
    currentList->length = index + 1;
}

void getPersonsFromFile(char *filename, peopleSmartList *currentList) {
    FILE *file;
    Person person;

    file = fopen(filename, "r");
    if (file == NULL) return perror("File doesn\'t exist");

    while (feof(file) == 0)
    {
        person.id = currentList->length + 1;
        fscanf(file, " %s ", person.name);
        fscanf(file, " %i ", &person.age);
        fscanf(file, " %s ", person.state);
        person.vitalModel = getPersonVitalModel(person.age);

        person.sickedDays = -1;
        if(person.state[0] == 'D')
            fscanf(file, " %i ", &person.sickedDays);

        appendPersonToList(currentList, person);
    }

    fclose(file);
}