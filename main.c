/*
 * Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2019-2020

 * @Author Diogo Filipe Marinho Barbosa
 * @Number 2018012425
*/

#include <stdio.h>
#include "helpers/utils.c"
#include "core/builders/spaceBuilder.h"
#include "core/builders/populationBuilder.h"

int main() {
    char *spaceFile = "./data/spaces/E1.bin";
    char *peopleFile = "./data/people/pessoasA.txt";

    localsSmartList *spaceDataStruct = buildSpaceList(spaceFile);
    peopleSmartList *peopleDataStruct = buildPopulationList(peopleFile);

    return 0;
}





/* for (int i = 0; i < spaceDataStruct->length; i++) {
    printf("%i \t",spaceDataStruct->array[i].id);
    printf("%i \t",spaceDataStruct->array[i].capacity);
    printf("%i \t",spaceDataStruct->array[i].refLocal[0]);
    printf("%i \t",spaceDataStruct->array[i].refLocal[1]);
    printf("%i \t",spaceDataStruct->array[i].refLocal[2]);

    puts("\n");
}

for (int ii = 0; ii < peopleDataStruct->length; ii++) {
    printf("%i \t",peopleDataStruct->array[ii].id);
    printf("%s \t",peopleDataStruct->array[ii].name);
    printf("%i \t",peopleDataStruct->array[ii].age);
    printf("%s \t",peopleDataStruct->array[ii].state);
    printf("%i \t",peopleDataStruct->array[ii].sickedDays);

    printf("--> %f \t",peopleDataStruct->array[ii].vitalModel.probabilityOfRecovery);
    printf("--> %i \t",peopleDataStruct->array[ii].vitalModel.maxDurationOfInfectionInDays);
    printf("--> %i \t",peopleDataStruct->array[ii].vitalModel.immunityRate);
    puts("\n");
} */
