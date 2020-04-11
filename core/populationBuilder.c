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

    newSmartList->array = malloc(sizeof(Person));
    newSmartList->length = 0;

    getPersonFromFile(filename, newSmartList);

    newSmartList->length += 1;

    return newSmartList;
}

void appendPersonToList(peopleSmartList *currentList, Person person, int index) {
    if (index != 0){
        currentList->array = realloc(currentList->array, sizeof(Person) * (index+1));
    }
    if (currentList->array == NULL) {
        return perror("Error Allocating the memory");
    }
    currentList->length = index;
    currentList->array[index] = person;
}


void getPersonFromFile(char *filename, peopleSmartList *currentList) {
    FILE *file;
    Person *listOfPersons = currentList->array, aux;

    int personCounter = 0;

    file = fopen(filename, "r");
    if (file == NULL) {
        return perror("File doesn\'t exist");
    }

    while (feof(file) == 0)
    {
        fscanf(file, " %s ", aux.name);
        fscanf(file, " %i ", &aux.age);
        fscanf(file, " %s ", aux.state);

        aux.sickedDays = -1;

        if(aux.state[0] == 'D')
            fscanf(file, " %i ", &aux.sickedDays);

        appendPersonToList(currentList, aux, personCounter);

        personCounter++;
    }

    fclose(file);
}