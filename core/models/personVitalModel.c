/*
 * Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2019-2020

 * @Author Diogo Filipe Marinho Barbosa
 * @Number 2018012425
*/

#include "personVitalModel.h"

Vital_Model getPersonVitalModel(int age) {
    Vital_Model vitalDataModel;

    vitalDataModel.probabilityOfRecovery = (float) 1/age;
    vitalDataModel.maxDurationOfInfectionInDays = (int) floor(age/10) + 5;
    vitalDataModel.immunityRate = 20;

    return vitalDataModel;
}