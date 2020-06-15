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
#include "core/builders/historicBuilder.h"

#define STRING_SIZE_BUFFER 100


void menuOfAvailableLocations(Propagation_Model *propagationModel) {
    for (int i = 0; i < propagationModel->spaceList->length; ++i) {
        int population = propagationModel->spaceList->localsSmartList[i].numberOfPeople;
        int maxCapacity = propagationModel->spaceList->localsSmartList[i].local.capacity;

        if (population < maxCapacity) {
            printf("%i:\tLocal %i com uma populacao de %i/%i \n", propagationModel->spaceList->localsSmartList[i].local.id, propagationModel->spaceList->localsSmartList[i].local.id, population, maxCapacity);
        }

    }
}

void menuOfAvailableLocationsWithConnections(Propagation_Model *propagationModel) {
    for (int i = 0; i < propagationModel->spaceList->length; i++) {
        int hasConnections = spaceHasConnections(propagationModel->spaceList, i);
        int population = propagationModel->spaceList->localsSmartList[i].numberOfPeople;
        int maxCapacity = propagationModel->spaceList->localsSmartList[i].local.capacity;

        if (hasConnections) {
            printf("%i:\tLocal %i com uma populacao de %i/%i -> Conexoes: ", propagationModel->spaceList->localsSmartList[i].local.id, propagationModel->spaceList->localsSmartList[i].local.id, population, maxCapacity);
        }

        for (int ii = 0; ii < TAM_CONNECTIONS; ii++)
            if (propagationModel->spaceList->localsSmartList[i].local.refLocal[ii] != -1)
                printf("Local %i | \t", propagationModel->spaceList->localsSmartList[i].local.refLocal[ii]);

        puts("\n");
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
        printf("| 2 -> Recuar interacoes                |\n");
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
            if (local->numberOfPeople == 0) return;

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

        if(local.numberOfPeople == 0) {
            printf("\nO local com ID %i nao apresenta populacao.\n", local.local.id);
            continue;
        }

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

        if(local.numberOfPeople == 0) {
            fprintf(f,"\n# O local com ID %i nao apresenta populacao. #\n", local.local.id);
            fputs("##############################################\n", f);
            continue;
        }

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
    if (!hasLocalWithSpace(propagationModel->spaceList)) {
        puts("Os Locais estao todos lotados\n");
        return;
    }

    Person person;
    int localId = -1, loopController = 1;
    char localIdToTest[STRING_SIZE_BUFFER] = "\0",
        ageToTest[STRING_SIZE_BUFFER] = "\0",
        daysSickedToTest[STRING_SIZE_BUFFER] = "\0";

    puts("=== Novo doente ===");
    puts("Nome: ");
    scanf("%99s", person.name);

    while(loopController) {
        if (!isValidNumber(localIdToTest, &localId) || localId == -1) {
            puts("Locais disponiveis para incluir o doente (valor inteiro natural): ");
            menuOfAvailableLocations(propagationModel);
            printf("ID> ");
            scanf("%99s", localIdToTest);
            continue;
        }

        if (!hasFreeSpace(propagationModel->spaceList->localsSmartList[getLocalIndexById(propagationModel,localId)])) {
            localId = -1;
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

    addSickPerson(propagationModel, person, getLocalIndexById(propagationModel,localId));
}

void movePerson(Propagation_Model *propagationModel) {
    int firstLocalId = -1, secondLocalId = -1, numberOfpeopleToTransfer = -1;

    menuOfAvailableLocationsWithConnections(propagationModel);

    puts("Id Local: ");
    scanf(" %i",&firstLocalId);

    puts("Id do local que vai receber as pessoas: ");
    scanf(" %i",&secondLocalId);

    puts("Numero de pessoas para transferir: ");
    scanf(" %i",&numberOfpeopleToTransfer);

    movePersons(propagationModel, numberOfpeopleToTransfer, getLocalIndexById(propagationModel,firstLocalId), getLocalIndexById(propagationModel,secondLocalId));

}

void testFilesExistance(char *spaceFile, char *populationFile) {
    int spaceFileExists = 0;
    int populationFileExists = 0;

    while(1) {

        if(!spaceFileExists) {
            puts("Caminho do ficheiro dos locais: ");
            scanf("%99s", spaceFile);
            spaceFileExists = theFileExists(spaceFile);
        }
        else if(!populationFileExists) {
            puts("Caminho do ficheiro da populacao: ");
            scanf("%99s", populationFile);
            populationFileExists = theFileExists(populationFile);
        }
        else
            return;

    }
}

void simulation() {
    int days = 0;
    char spaceFile[STRING_SIZE_BUFFER] = "\0", populationFile[STRING_SIZE_BUFFER] = "\0";

    testFilesExistance(spaceFile, populationFile);

    Propagation_Model propagationModel = initPropagationModel(spaceFile, populationFile);
    Historic historic = initHistoric();

    char option = simulationMenu(1);
    while(1) {
        switch (option) {
            case '1':
                makeInteractions(&propagationModel, 1, &days);
                addToHistoric(&historic, propagationModel);
                break;
            case '2':
                puts("Funcionalidade por terminar");
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