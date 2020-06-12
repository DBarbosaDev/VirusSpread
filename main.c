/*
 * Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2019-2020

 * @Author Diogo Filipe Marinho Barbosa
 * @Number 2018012425
*/

#include <stdio.h>
#include <string.h>
#include "helpers/utils.c"
#include "helpers/validations.h"
#include "core/models/propagationModel.h"

#define STRING_SIZE_BUFFER 100


void menuOfAvailableLocations(Propagation_Model *propagationModel) {
    for (int i = 0; i < propagationModel->spaceList->length; ++i) {
        int population = propagationModel->spaceList->localsSmartList[i].numberOfPeople;
        int maxCapacity = propagationModel->spaceList->localsSmartList[i].local.capacity;

        if (population < maxCapacity) {
            printf("%i:\tLocal %i com uma populacao de %i/%i \n", i + 1, propagationModel->spaceList->localsSmartList[i].local.id, population, maxCapacity);
        }

    }
}

void menuOfAvailableConnectedLocations(Propagation_Model *propagationModel, int indexOfParentLocal) {
    for (int i = 0; i < 3; i++) {
        int refLocal = propagationModel->spaceList->localsSmartList[indexOfParentLocal].local.refLocal[i];

        for (int ii = 0; ii < propagationModel->spaceList->length; ii++) {
            int population = propagationModel->spaceList->localsSmartList[indexOfParentLocal].numberOfPeople;
            int maxCapacity = propagationModel->spaceList->localsSmartList[indexOfParentLocal].local.capacity;

            if (refLocal !=  propagationModel->spaceList->localsSmartList[ii].local.id || population >= maxCapacity) break;

            printf("%i:\tLocal %i com uma populacao de %i/%i \n", i + 1, propagationModel->spaceList->localsSmartList[i].local.id, population, maxCapacity);
            break;
        }
    }
}

char mainMenu(int showMenu) {
    char option;

    if(showMenu) {
        printf("\n");
        printf("| ============ Menu Option ============ |\n");
        printf("| 1 -> Preparar simulacao               |\n");
        printf("| 0 -> Sair                             |\n"
               "| ===================================== |\n");
    }

    printf("opcao > ");
    scanf("%3s", &option);

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
        printf("| 6 -> Tests(to delete)                 |\n");
        printf("| 0 -> Terminar simulacao               |\n"
               "| ===================================== |\n");
    }

    printf("opcao >");
    scanf("%3s", &option);

    return option;
}

// TODO verificar o que está a acontecer aqui
// * Sobra sempre um infetado ao fim de imensas interações. Em certas ocorrências passa a 0
void managePersonVitalState(Person *person, localsSmartList *local, int index) {
    if (person->sickedDays >= person->vitalModel.maxDurationOfInfectionInDays || probEvento(person->vitalModel.probabilityOfRecovery)) {
        person->state[0] = 'S';
        person->sickedDays = -1;

        if (probEvento(person->vitalModel.immunityRate)) person->state[0] = 'I';

        switchPersonToTheHealthyList(local, index);

        return;
    }

    person->sickedDays++;
}

void manageVirusSpread(localsSmartList *local, float spreadRate) {
    int peopleToInfect = (int) floor(local->numberOfPeople*spreadRate);
    int peopleToInfectPerSicked = peopleToInfect * local->numberOfInfectedPeople;

    for (int i = 0; i < peopleToInfectPerSicked || local->numberOfInfectedPeople == 0; i++) {
        int personToInfect = intUniformRnd(0, local->numberOfPeople - 1);

        if(personToInfect < local->numberOfHealthyPeople && local->listOfHealthyPeople[personToInfect].person->state[0] != 'I') {
            local->listOfHealthyPeople[personToInfect].person->state[0] = 'D';
            local->listOfHealthyPeople[personToInfect].person->sickedDays = 1;
            switchPersonToInfectedList(local, personToInfect);
        }

    }
}

void makeInteractions(Propagation_Model *propagationModel, int interactions, int *days) {
    *days += interactions;

    while (interactions > 0) {

        for (int i = 0; i < propagationModel->spaceList->length ; i++) {
            localsSmartList *local = &propagationModel->spaceList->localsSmartList[i];

            for (int ii = 0; ii < local->numberOfInfectedPeople; ii++) {
                Connection *person = &local->listOfInfectedPeople[ii];
                managePersonVitalState(person->person, local, ii);
            }

            manageVirusSpread(local, propagationModel->spreadRate);
        }

        interactions--;
    }
}

void getStatistics(Propagation_Model *propagationModel, int days) {
    puts("===== Estado atual da simulacao =====");
    printf("Dia: %i\n", days);

    for (int i = 0; i < propagationModel->spaceList->length; i++) {
        localsSmartList local = propagationModel->spaceList->localsSmartList[i];
        int percentageOfInfected = (int) (local.numberOfInfectedPeople*100)/local.numberOfPeople;
        int percentageOfHealthy = (int) (local.numberOfHealthyPeople*100)/local.numberOfPeople;

        printf("\nO local com ID %i apresenta:\n"
               "Populacao total:             %i\n"
               "Numero de pessoas infetadas: %i -> %i porcento\n"
               "Numero de pessoas saudaveis: %i -> %i porcento\n",
               local.local.id, local.numberOfPeople, local.numberOfInfectedPeople, percentageOfInfected, local.numberOfHealthyPeople, percentageOfHealthy);
    }
    puts("=====================================");
}

void createReport(Propagation_Model *propagationModel, int days) {
    FILE *f;
    f = fopen("report.txt", "w");

    fputs("===================================== Relatorio da simulacao =====================================", f);
    fprintf(f,"\nDias|Interacoes: %i\n", days);

    for (int i = 0; i < propagationModel->spaceList->length; i++) {
        localsSmartList local = propagationModel->spaceList->localsSmartList[i];
        int percentageOfInfected = (int) (local.numberOfInfectedPeople*100)/local.numberOfPeople;
        int percentageOfHealthy = (int) (local.numberOfHealthyPeople*100)/local.numberOfPeople;

        fprintf(f,"\n\n###### O local com ID %i apresenta: ######\n"
               "Populacao total:             %i\n"
               "Numero de pessoas infetadas: %i -> %i porcento\n"
               "Numero de pessoas saudaveis: %i -> %i porcento\n\n",
               local.local.id, local.numberOfPeople, local.numberOfInfectedPeople, percentageOfInfected, local.numberOfHealthyPeople, percentageOfHealthy);

        fputs("### Populacao:\n", f);

        for (int j = 0; j < local.numberOfHealthyPeople ; j++) {
            fprintf(f,"Nome: %s \t\t\t Idade: %i \t\t\t Estado: %s \n",local.listOfHealthyPeople[j].person->name, local.listOfHealthyPeople[j].person->age, local.listOfHealthyPeople[j].person->state);
        }
        for (int j = 0; j < local.numberOfInfectedPeople ; j++) {
            fprintf(f,"Nome: %s \t\t\t Idade: %i \t\t\t Estado: %s \n",local.listOfInfectedPeople[j].person->name, local.listOfInfectedPeople[j].person->age, local.listOfInfectedPeople[j].person->state);
        }

        fputs("############################################\n", f);
    }
    fputs("===================================================================================================",f);

    fclose(f);
}

// TODO Não deixa selecionar o ultimo local e por vezes aceita locais lotados(parece ser o ultimo), ver
void newSickPerson(Propagation_Model *propagationModel) {
    Person person;
    int indexOfLocal = -1, loopController = 1;
    char localIdToTest[STRING_SIZE_BUFFER] = "\0",
        ageToTest[STRING_SIZE_BUFFER] = "\0",
        daysSickedToTest[STRING_SIZE_BUFFER] = "\0";

    puts("=== Novo doente ===");
    puts("Nome: ");
    scanf("%99s", person.name);

    while(loopController) {
        if (!isValidNumber(localIdToTest, &indexOfLocal) || indexOfLocal == -1) {
            puts("Locais disponiveis para incluir o doente (valor inteiro natural): ");
            menuOfAvailableLocations(propagationModel);
            printf("opcao> ");
            scanf("%99s", localIdToTest);
            continue;
        }

        if (isValidNumber(localIdToTest, &indexOfLocal) && indexOfLocal != -1 && !isNumberBetween(indexOfLocal, 1, propagationModel->spaceList->length + 1)) {
            indexOfLocal = -1;
            strcpy(localIdToTest, "\0");
            continue;
        } else if (!hasFreeSpace(propagationModel->spaceList->localsSmartList[indexOfLocal])) {
            indexOfLocal = -1;
            strcpy(localIdToTest, "\0");
            continue;
        }

        if (!isValidNumber(ageToTest, &person.age)) {
            printf("Idade (valor inteiro natural): ");
            scanf("%3s", ageToTest);
            continue;
        }

        if (!isValidNumber(daysSickedToTest, &person.sickedDays)) {
            printf("Dias doente(valor inteiro natural): ");
            scanf("%99s", daysSickedToTest);
            continue;
        }

        loopController = 0;
    }

    strcpy(person.state, "D");
    person.vitalModel = getPersonVitalModel(person.age);

    addSickPerson(propagationModel, person, indexOfLocal - 1);
}

// TODO Acabar
void movePerson(Propagation_Model *propagationModel) {
    int loopController = 1;
    int firstLocalId = -1, secondLocalId = -1, numberOfpeopleToTransfer = 0;
    char firstLocalIdToTest[STRING_SIZE_BUFFER] = "\0",
        secondLocalIdToTest[STRING_SIZE_BUFFER] = "\0",
        numberOfpeopleToTransferToTest[STRING_SIZE_BUFFER] = "\0";

    while (loopController) {
        if (!isValidNumber(firstLocalIdToTest, &firstLocalId) || firstLocalId == -1) {
            puts("Locais disponiveis para incluir o doente (valor inteiro natural): ");
            menuOfAvailableLocations(propagationModel);
            printf("opcao> ");
            scanf("%99s", firstLocalIdToTest);
            continue;
        }

        // verificer se o local está lotado
        if (isValidNumber(secondLocalIdToTest, &firstLocalId) && firstLocalId != -1 && !isNumberBetween(firstLocalId, 1, propagationModel->spaceList->length + 1)) {
            firstLocalId = -1;
            strcpy(secondLocalIdToTest, "\0");
            continue;
        } else if (!hasFreeSpace(propagationModel->spaceList->localsSmartList[firstLocalId])) {
            firstLocalId = -1;
            strcpy(secondLocalIdToTest, "\0");
            continue;
        }

        if (!isValidNumber(secondLocalIdToTest, &secondLocalId) || secondLocalId == -1) {
            puts("Locais ligados (valor inteiro natural): ");
            menuOfAvailableConnectedLocations(propagationModel, firstLocalId);
            printf("opcao> ");
            scanf("%99s", secondLocalIdToTest);
            continue;
        }

        // verificer se o local tem espaço e se está ligado ao primeiro
        if(0) {

            continue;
        }


        if (!isValidNumber(numberOfpeopleToTransferToTest, &numberOfpeopleToTransfer) || numberOfpeopleToTransfer == 0) {
            puts("Locais ligados (valor inteiro natural): ");
            printf("opcao> ");
            scanf("%99s", numberOfpeopleToTransferToTest);
            continue;
        }

        loopController = 0;
    }

    //adiciona aos locais
    //ter em consideração o estado.

}

// TODO eliminar quando for para entregar
void tests(Propagation_Model *propagationModel) {
    /*for (int i = 0; i < propagationModel->spaceList->length ; ++i) {
        int totalIn = 0, totalHealt = 0;

        for (int ii = 0; ii < propagationModel->spaceList->localsSmartList[i].numberOfHealthyPeople; ii++) {
            totalHealt += sizeof(propagationModel->spaceList->localsSmartList[i].listOfHealthyPeople[ii]);
        }
        for (int ii = 0; ii < propagationModel->spaceList->localsSmartList[i].numberOfInfectedPeople; ii++) {
            totalIn += sizeof(propagationModel->spaceList->localsSmartList[i].listOfInfectedPeople[ii]);
        }
        printf("infected: %i\thealthy: %i\n", totalIn, totalHealt);
    }
    for (int i = 0; i < propagationModel->spaceList->length; i++) {
        printf("%i \t %i \n",propagationModel->spaceList->localsSmartList[i].local.id, propagationModel->spaceList->localsSmartList[i].local.capacity);
        puts("## Healthy ##");
        for (int j = 0; j < propagationModel->spaceList->localsSmartList[i].numberOfHealthyPeople ; j++) {
            printf("%s \t %i \t %s \n",propagationModel->spaceList->localsSmartList[i].listOfHealthyPeople[j].person->name, propagationModel->spaceList->localsSmartList[i].listOfHealthyPeople[j].person->age,
                   propagationModel->spaceList->localsSmartList[i].listOfHealthyPeople[j].person->state);
        }
        puts("\n## Infected ##");
        for (int j = 0; j < propagationModel->spaceList->localsSmartList[i].numberOfInfectedPeople ; j++) {
            printf("%s \t %i \t %s \n",propagationModel->spaceList->localsSmartList[i].listOfInfectedPeople[j].person->name, propagationModel->spaceList->localsSmartList[i].listOfInfectedPeople[j].person->age,
                   propagationModel->spaceList->localsSmartList[i].listOfInfectedPeople[j].person->state);
        }
        puts("\n\n");
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
        printf("--> %0.2f \t",propagationModel->populationList->array[ii].vitalModel.immunityRate);
        puts("\n");
    }*/
    for (int i = 0; i < propagationModel->spaceList->length; i++) {
        printf("local: %i \t capacidade %i/%i\n", propagationModel->spaceList->localsSmartList[i].local.id,
               propagationModel->spaceList->localsSmartList[i].numberOfPeople,
               propagationModel->spaceList->localsSmartList[i].local.capacity);
    }
    puts("------------------------------- \n");

    /*puts("------------------------------- \n");
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
       printf("--> %0.2f \t",propagationModel->populationList->array[ii].vitalModel.immunityRate);
       puts("\n");
   }
   puts("------------------------------- \n");*/

}

void simulation() {
    int days = 0;
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
                makeInteractions(&propagationModel, 1, &days);
                break;
            case '2':
                makeInteractions(&propagationModel, 3, &days);
                break;
            case '3':
                getStatistics(&propagationModel, days);
                break;
            case '4':
                newSickPerson(&propagationModel);
                break;
            case '5':
                movePerson(&propagationModel);
                break;
            case '6':
                tests(&propagationModel);
                break;
            case '0':
                createReport(&propagationModel, days);
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
}

// TODO eliminar quando for para entregar
/*void main() {
    int days = 0;

    char *spaceFile = "./data/spaces/E1.bin";
    char *peopleFile = "./data/people/pessoasC.txt";

    Propagation_Model propagationModel = initPropagationModel(spaceFile, peopleFile);
    newSickPerson(&propagationModel);
}*/
