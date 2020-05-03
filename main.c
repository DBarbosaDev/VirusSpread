/*
 * Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2019-2020

 * @Author Diogo Filipe Marinho Barbosa
 * @Number 2018012425
*/

#include <stdio.h>
#include "helpers/utils.c"
#include "core/models/propagationModel.h"

int main() {
    initRandom();

    char *spaceFile = "./data/spaces/E1.bin";
    char *peopleFile = "./data/people/pessoasC.txt";

    Propagation_Model propagationModel = initPropagationModel(spaceFile, peopleFile);

}

/*
   puts("------------------------------- \n");
    for (int i = 0; i < propagationModel.spaceList->length; i++) {
        printf("%i \t",propagationModel.spaceList->localsSmartList[i].local.id);
        printf("%i \t",propagationModel.spaceList->localsSmartList[i].local.capacity);
        printf("%i \t",propagationModel.spaceList->localsSmartList[i].local.refLocal[0]);
        printf("%i \t",propagationModel.spaceList->localsSmartList[i].local.refLocal[1]);
        printf("%i \t",propagationModel.spaceList->localsSmartList[i].local.refLocal[2]);

        puts("\n");
    }
    puts("------------------------------- \n Relations \n");

    for (int i = 0; i < propagationModel.spaceList->length; i++) {
        printf("%i \t",propagationModel.spaceList->localsSmartList[i].local.id);
        printf("%i \t",propagationModel.spaceList->localsSmartList[i].local.capacity);
        puts("\n## Healthy ##\n");
        for (int j = 0; j < propagationModel.spaceList->localsSmartList[i].numberOfHealthyPersons ; ++j) {
            printf("%s %i \t",propagationModel.spaceList->localsSmartList[i].listOfHealthyPersons[j].person->name, propagationModel.spaceList->localsSmartList[i].listOfHealthyPersons[j].person->age);
        }
        puts("\n## Infected ##\n");
        for (int j = 0; j < propagationModel.spaceList->localsSmartList[i].numberOfInfectedPersons ; ++j) {
            printf("%s %i \t",propagationModel.spaceList->localsSmartList[i].listOfInfectedPersons[j].person->name, propagationModel.spaceList->localsSmartList[i].listOfInfectedPersons[j].person->age);
        }
        puts("\n");
    }

    puts("------------------------------- \n");
    for (int ii = 0; ii < propagationModel.populationList->length; ii++) {
        printf("%i \t",propagationModel.populationList->array[ii].id);
        printf("%s \t",propagationModel.populationList->array[ii].name);
        printf("%i \t",propagationModel.populationList->array[ii].age);
        printf("%s \t",propagationModel.populationList->array[ii].state);
        printf("%i \t",propagationModel.populationList->array[ii].sickedDays);

        printf("--> %f \t",propagationModel.populationList->array[ii].vitalModel.probabilityOfRecovery);
        printf("--> %i \t",propagationModel.populationList->array[ii].vitalModel.maxDurationOfInfectionInDays);
        printf("--> %i \t",propagationModel.populationList->array[ii].vitalModel.immunityRate);
        puts("\n");
    }
    puts("------------------------------- \n");

    return 0;
 */