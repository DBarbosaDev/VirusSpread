/*
 * Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2019-2020

 * @Author Diogo Filipe Marinho Barbosa
 * @Number 2018012425
*/
#include "feedbackMessages.h"

void delay(float seconds) {
    int milli_seconds = 1000 * seconds;

    clock_t start_time = clock();

    while (clock() < start_time + milli_seconds);
}

void messageWithDelay(char *text){
    printf("%s", text);
    delay(0.5);
}

