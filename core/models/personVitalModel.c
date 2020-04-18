/*
 * Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2019-2020

 * @Author Diogo Filipe Marinho Barbosa
 * @Number 2018012425
*/

#include <stdlib.h>
#include <math.h>
#include "personVitalModel.h"

Vital_Model* getPersonVitalModel(int age) {
    Vital_Model* vitalDataModel = malloc(sizeof(Vital_Model));

    vitalDataModel->probabilityOfRecovery = 1/age;
    vitalDataModel->maxDurationOfInfection = (int) floor(age/10) + 5;
    vitalDataModel->immunityRate = 20;

    return vitalDataModel;
}