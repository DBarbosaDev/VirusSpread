/*
 * Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2019-2020

 * @Author Diogo Filipe Marinho Barbosa
 * @Number 2018012425
*/

#include "populationBuilder.h"
#include "../../helpers/validations.h"

Population *buildPopulationList(char *filename) {
    Population *newSmartList = malloc(sizeof(Population));

    newSmartList->array = malloc(0);
    newSmartList->length = 0;

    getPersonsFromFile(filename, newSmartList);

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
    char ageToTest[STRING_SIZE_BUFFER] = "\0", daysSickedToTest[STRING_SIZE_BUFFER] = "\0";

    file = fopen(filename, "r");
    if (file == NULL) {
        perror("O ficheiro binario dos locais nao existe");
        exit(1);
    }

    while (feof(file) == 0)
    {
        fscanf(file, " %s ", person.name);
        fscanf(file, " %s ", ageToTest);
        fscanf(file, " %s ", person.state);
        person.vitalModel = getPersonVitalModel(person.age);

        person.sickedDays = -1;
        if(person.state[0] == 'D') {
            fscanf(file, " %s ", daysSickedToTest);

            if (!isValidNumber(daysSickedToTest, &person.sickedDays)) {
                perror("O valor da quantidades de dias doente deve ser um numero inteiro natural maior do que zero.");
                exit(1);
            }

        }

        if (person.state[0] != 'D' && person.state[0] != 'I' && person.state[0] != 'S') {
            perror("So sao aceites estados com as letras D, S e I.");
            exit(1);
        }

        if (!isValidNumber(ageToTest, &person.age)) {
            perror("O valor da idade deve ser um numero inteiro natural maior do que zero.");
            exit(1);
        }

        appendPersonToList(currentList, person);
    }

    fclose(file);
}