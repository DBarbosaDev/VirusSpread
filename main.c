/*
 * Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2019-2020

 * @Author Diogo Filipe Marinho Barbosa
 * @Number 2018012425
*/
#define STRING_SIZE 30
#include<stdio.h>
#include "helpers/utils.c"
#include "core/models/propagationModel.h"

char mainMenu(int showMenu) {
    char option;

    if(showMenu) {
        printf("\n");
        printf("| ============ Menu Option ============ |\n");
        printf("| 1 -> Preparar simulacao               |\n");
        printf("| 0 -> Sair                             |\n"
               "| ===================================== |\n");
    }

    printf("option > ");
    scanf("%s", &option);

    return option;
}

char simulationMenu(int showMenu) {
    char option;

    if(showMenu) {
        printf("\n");
        printf("| ============= Simulacao ============= |\n");
        printf("| 1 -> Avancar uma iteracao             |\n");
        printf("| 2 -> Avancar 3 iteracoes              |\n");
        printf("| 3 -> Apresentar estatistica           |\n");
        printf("| 4 -> Adicionar doente                 |\n");
        printf("| 5 -> Transferir pessoa                |\n");
        printf("| 0 -> Terminar simulacao               |\n"
               "| ===================================== |\n");
    }

    printf("option >");
    scanf("%s", &option);

    return option;
}

void makeInteractions(Propagation_Model *propagationModel, int interactions) {
    while (interactions > 0) {

        interactions--;
    }
}

void report(Propagation_Model *propagationModel) {
    puts("------------------------------- \n");
    for (int i = 0; i < propagationModel->spaceList->length; i++) {
        printf("%i \t",propagationModel->spaceList->localsSmartList[i].local.id);
        printf("%i \t",propagationModel->spaceList->localsSmartList[i].local.capacity);
        printf("%i \t",propagationModel->spaceList->localsSmartList[i].local.refLocal[0]);
        printf("%i \t",propagationModel->spaceList->localsSmartList[i].local.refLocal[1]);
        printf("%i \t",propagationModel->spaceList->localsSmartList[i].local.refLocal[2]);

        puts("\n");
    }
    puts("------------------------------- \n Relations \n");

    for (int i = 0; i < propagationModel->spaceList->length; i++) {
        printf("%i \t",propagationModel->spaceList->localsSmartList[i].local.id);
        printf("%i \t",propagationModel->spaceList->localsSmartList[i].local.capacity);
        puts("\n## Healthy ##\n");
        for (int j = 0; j < propagationModel->spaceList->localsSmartList[i].numberOfHealthyPeople ; ++j) {
            printf("%s %i \t",propagationModel->spaceList->localsSmartList[i].listOfHealthyPeople[j].person->name, propagationModel->spaceList->localsSmartList[i].listOfHealthyPeople[j].person->age);
        }
        puts("\n## Infected ##\n");
        for (int j = 0; j < propagationModel->spaceList->localsSmartList[i].numberOfInfectedPeople ; ++j) {
            printf("%s %i \t",propagationModel->spaceList->localsSmartList[i].listOfInfectedPeople[j].person->name, propagationModel->spaceList->localsSmartList[i].listOfInfectedPeople[j].person->age);
        }
        puts("\n");
    }

    puts("------------------------------- \n");
    for (int ii = 0; ii < propagationModel->populationList->length; ii++) {
        printf("%i \t",propagationModel->populationList->array[ii].id);
        printf("%s \t",propagationModel->populationList->array[ii].name);
        printf("%i \t",propagationModel->populationList->array[ii].age);
        printf("%s \t",propagationModel->populationList->array[ii].state);
        printf("%i \t",propagationModel->populationList->array[ii].sickedDays);

        printf("--> %f \t",propagationModel->populationList->array[ii].vitalModel.probabilityOfRecovery);
        printf("--> %i \t",propagationModel->populationList->array[ii].vitalModel.maxDurationOfInfectionInDays);
        printf("--> %i \t",propagationModel->populationList->array[ii].vitalModel.immunityRate);
        puts("\n");
    }
    puts("------------------------------- \n");
}

void addSick(Propagation_Model *propagationModel) {

}

void movePerson(Propagation_Model *propagationModel) {

}

void simulation() {
    /*char spaceFile[STRING_SIZE], populationFile[STRING_SIZE];
    puts("Caminho do ficheiro dos locais: ");
    scanf("%s", spaceFile);
    puts("Caminho do ficheiro da populacao: ");
    scanf("%s", populationFile);*/

    char *spaceFile = "./data/spaces/E1.bin";
    char *peopleFile = "./data/people/pessoasC.txt";

    Propagation_Model propagationModel = initPropagationModel(spaceFile, peopleFile);

    char option = simulationMenu(1);
    while(1) {
        switch (option) {
            case '1':
                makeInteractions(&propagationModel, 1);
                break;
            case '2':
                makeInteractions(&propagationModel, 3);
                break;
            case '3':
                report(&propagationModel);
                break;
            case '4':
                addSick(&propagationModel);
                break;
            case '5':
                movePerson(&propagationModel);
                break;
            case '0':
                puts("Programa terminado");
                return;
            default:
                puts("Opcao invalida!");
                break;
        }

        option = simulationMenu(1);
    }
}

void main() {
    initRandom();
    char option = mainMenu(1);

    while(1) {
        switch (option) {
            case '1':
                simulation();
                return;
            case '0':
                puts("Programa terminado");
                return;
            default:
                puts("Opcao invalida!\n");
                option = mainMenu(0);
                break;
        }
    }

    return;
}
