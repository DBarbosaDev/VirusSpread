/*
 * Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2019-2020

 * @Author Diogo Filipe Marinho Barbosa
 * @Number 2018012425
*/


#ifndef PERSONMODEL_H
#define PERSONMODEL_H

typedef struct Vital_Model {
    /* Probabilidade de recuperação em cada iteração
    *   @formula: 1/idade
    */
    float probabilityOfRecovery;

    /* Número de dias qua uma pessoa estará doente
    *   @formula: (idade/10) + 5
    *   @nota: (idade/10) -> arredondado por defeito
    */
    int maxDurationOfInfectionInDays;

    /* Taxa de uma pessoa ficar imune após recuperação */
    int immunityRate;

} Vital_Model;

Vital_Model getPersonVitalModel(int age);

#endif //PERSONMODEL_H
