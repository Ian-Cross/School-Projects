#ifndef __icross_menu__
#define __icross_menu__

void menu(List **carsList,char* fileName);
void command1(List **carsList);
int isNum(char *millage);
void command2(List **carsList);
void command3(List **carsList);
void command4(List **carsList);
void command5(List **carsList);
void command7(List **carsList,char* fileName);
int isGoodPlate(char *plateNumber);
int isGoodYear(char *date);

#endif
