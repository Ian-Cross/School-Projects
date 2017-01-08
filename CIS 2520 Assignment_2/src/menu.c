#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "linkedList.h"
#include "fileParsing.h"
#include "menu.h"

void menu (List **carsList,char* fileName){
  int command = 0;
  system("clear");
  printf("Hello, and welcome to the online car rental service\n");
  while (command != 7) {
    printf("Please press the number of the command you want\n");
    printf("1. Add a new car to the available-for-rent list\n");
    printf("2. Add a returned car to the available-for-rent list\n");
    printf("3. Add a returned car to the repiar list\n");
    printf("4. Transfer a car from the repair list to the available-for-rent list\n");
    printf("5. Rent the first available car\n");
    printf("6. Print all the lists\n");
    printf("7. Quit\n");

    scanf("%d",&command);
    getchar();

    switch (command) {
      case 1:
        command1(carsList);
        break;
      case 2:
        command2(carsList);
        break;
      case 3:
        command3(carsList);
        break;
      case 4:
        command4(carsList);
        break;
      case 5:
        command5(carsList);
        break;
      case 6:
        printList(*carsList);
        break;
      case 7:
        command7(carsList,fileName);
        return;
        break;
    }
  }
}

void command1(List **carsList){
  char plateNumber[256];
  char millage[256];
  char* carInfo[2];
  printf("Please enter the License plate number of the car (XXXX-###, where x's are letters and #'s are numbers)\n");
  fgets(plateNumber,255, stdin);
  while (strlen(plateNumber) != 9 || !isGoodPlate(plateNumber)){
    printf("Please enter the license plate number in the correct format %d\n",(int)strlen(plateNumber));
    fgets(millage,255, stdin);
  }
  printf("Please enter the Millage that is currently on the car (#######)\n");
  fgets(millage,255, stdin);
  //the length will equal 8 with the newline character
  while (strlen(millage) != 8 || !isNum(millage)){
    printf("Please enter a 7 digit number for the millage\n");
    fgets(millage,255, stdin);
  }
  carInfo[0] = malloc(sizeof(plateNumber));
  carInfo[0] = plateNumber;
  carInfo[0] = upperCase(carInfo[0]);
  carInfo[1] = malloc(sizeof(millage));
  carInfo[1] = millage;

  printf("Adding to the Avaliable list, the car %s",carInfo[0]);

  addCar(carInfo,carsList,1);
}

int isNum(char* millage) {
  for (int i = 0; i < strlen(millage); i++){
    if (!isdigit(millage[i]) && millage[i] != '\n'){
      return 0;
    }
  }
  return 1;
}

void command2(List **carsList){
  char plateNumber[256];
  char millage[256];
  char* carInfo[2];
  printf("Please enter the License plate number of the car (XXXX-###, where x's are letters and #'s are numbers)\n");
  fgets(plateNumber,255, stdin);
  //the length will be 9 with the \n character
  while (strlen(plateNumber) != 9 || !isGoodPlate(plateNumber)){
    printf("Please enter the license plate number in the correct format %d\n",(int)strlen(plateNumber));
    fgets(plateNumber,255, stdin);
  }
  printf("Please enter the Millage that is currently on the car (#######)\n");
  fgets(millage,255, stdin);
  //the length will equal 8 with the newline character
  while (strlen(millage) != 8 || !isNum(millage)){
    printf("Please enter a 7 digit number for the millage\n");
    fgets(millage,255, stdin);
  }
  carInfo[0] = malloc(sizeof(plateNumber));
  carInfo[0] = plateNumber;
  carInfo[0] = upperCase(carInfo[0]);
  carInfo[1] = malloc(sizeof(millage));
  carInfo[1] = millage;

  moveCar(carInfo,carsList,2,1);
}

void command3(List **carsList){
  char plateNumber[256];
  char millage[256];
  char repairDate[256];
  char* carInfo[3];
  printf("Please enter the License plate number of the car (XXXX-###, where x's are letters and #'s are numbers)\n");
  fgets(plateNumber, 255, stdin);
  //the length will be 9 with the \n character
  while (strlen(plateNumber) != 9 || !isGoodPlate(plateNumber)){
    printf("Please enter the license plate number in the correct format %d\n",(int)strlen(plateNumber));
    fgets(plateNumber, 255, stdin);
  }
  printf("Please enter the Millage that is currently on the car (#######)\n");
  fgets(millage, 255, stdin);
  //the length will equal 8 with the newline character
  while (strlen(millage) != 8 || !isNum(millage)){
    printf("Please enter a 7 digit number for the millage\n");
    fgets(millage, 255, stdin);
  }
  printf("Please enter the Estimated data that the car will be repaired by (YYMMDD)\n");
  fgets(repairDate, 255, stdin);
  //the length will equal 8 with the newline character
  while (strlen(repairDate) != 7 || !isGoodYear(repairDate)){
    printf("Please enter the date in the correct format, with real dates in the future\n");
    fgets(repairDate, 255, stdin);
  }
  carInfo[0] = malloc(sizeof(plateNumber));
  carInfo[0] = plateNumber;
  carInfo[0] = upperCase(carInfo[0]);
  carInfo[1] = malloc(sizeof(millage));
  carInfo[1] = millage;

  carInfo[2] = malloc(sizeof(repairDate));
  carInfo[2] = repairDate;

  moveCar(carInfo,carsList,2,3);
}

void command4(List **carsList){
  char plateNumber[256];
  char* carInfo[3];
  printf("Please enter the License plate number of the car (XXXX-###, where x's are letters and #'s are numbers)\n");
  fgets(plateNumber, 255, stdin);
  //the length will be 9 with the \n character
  while (strlen(plateNumber) != 9 || !isGoodPlate(plateNumber)){
    printf("Please enter the license plate number in the correct format %d\n",(int)strlen(plateNumber));
    fgets(plateNumber, 255, stdin);
  }

  carInfo[0] = malloc(sizeof(plateNumber));
  carInfo[0] = plateNumber;
  carInfo[0] = upperCase(carInfo[0]);
  moveCar(carInfo,carsList,3,1);
}

void command5(List **carsList){
  char returnDate[256];
  char* carInfo[3];
  printf("Please enter the expected Return date of the car (yymmdd)\n");
  fgets(returnDate, 255, stdin);
  //the length will be 9 with the \n character
  while (strlen(returnDate) != 7 || !isGoodYear(returnDate)){
    printf("Please enter the expected return date in the correct format using future dates \n");
    fgets(returnDate, 255, stdin);
  }

  carInfo[0] = malloc(sizeof(returnDate));
  carInfo[0] = returnDate;

  moveCar(carInfo,carsList,1,2);
}

void command7(List **carsList, char* fileName){
  printf("Quitting the program, and printing out the save file.\n");
  printf("Total Income for the service: $%0.2lf\n",(*carsList)->income);
  printFile(carsList,fileName);
}

int isGoodPlate(char* plateNumber){

  for (int i = 0; i < strlen(plateNumber)/2; i++){
    if (!isalpha(plateNumber[i])){
      return 0;
    }
  }

  if (plateNumber[4] != '-') return 0;

  for (int i = 5; i < strlen(plateNumber); i++){
    if (!isdigit(plateNumber[i]) && plateNumber[i] != '\n'){
      return 0;
    }
  }
  return 1;
}

int isGoodYear(char* date){
  int year,month,day;
  breakDate(date,&year,&month,&day);
  if (year < 16) return 0;
  if (month <= 0 || month > 12) return 0;
  if (day <= 0 || ((day != 28) && (month == 2)) || ((day > 30) && ((month == 4) || (month == 6) || (month == 9) || (month == 11))) || ((day > 31) && ((month == 1) || (month == 3) || (month == 5) || (month == 7) || (month == 8) || (month == 10) || (month == 12)))) return 0;
  return 1;
}
