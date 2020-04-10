/*
 * Trabalho Pratico Programacao - LEI
 * DEIS-ISEC 2019-2020

 * @Author Diogo Filipe Marinho Barbosa
 * @Number 2018012425
*/

#ifndef SPACEBUILDER_H
#define SPACEBUILDER_H

localsSmartList *buildList(char *filename);

void appendToList(localsSmartList *currentList, Local local, int index);
void getLocalContentFromBinFile(char *filename, localsSmartList *currentList);

#endif //SPACEBUILDER_H
