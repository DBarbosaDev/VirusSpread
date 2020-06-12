/*
 * Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2019-2020

 * @Author Diogo Filipe Marinho Barbosa
 * @Number 2018012425
*/

#include "populationBuilder.h"

Population *buildPopulationList(char *filename) {
    Population *newSmartList = malloc(sizeof(Population));
    messageWithDelay("=== A iniciar a construcao da populacao... ===\n");

    newSmartList->array = malloc(0);
    newSmartList->length = 0;

    getPersonsFromFile(filename, newSmartList);

    messageWithDelay("=== Construcao finalizada com sucesso! ===\n\n");
    return newSmartList;
}

void appendPersonToList(Population *currentList, Person person) {
    int index = currentList->length;
    person.id = currentList->length + 1;

    currentList->array = realloc(currentList->array, sizeof(Person)*(index+1));
    if (currentList->array == NULL) return perror("Erro na alocacao de memoria");

    currentList->array[index] = person;
    currentList->length = index + 1;
}

void getPersonsFromFile(char *filename, Population *currentList) {
    FILE *file;
    Person person;

    messageWithDelay("A carregar dados do ficheiro...\n");

    file = fopen(filename, "r");
    if (file == NULL) {
        perror("O ficheiro da populacao nao existe");
        currentList = NULL;
        return;
    }

    while (feof(file) == 0)
    {
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

    messageWithDelay("Dados carregados com sucesso!\n");
}