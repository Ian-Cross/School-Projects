#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "linkedList.h"

List* createLists(){
  List* newList = NULL;

  newList = malloc(sizeof(List));
  if (newList == NULL) {
    printf("Sorry, there isn't enough memory\n");
    exit(1);
  }
  newList->avHead = NULL;
  newList->renHead = NULL;
  newList->repHead = NULL;
  newList->income = 0;

  return newList;
}

void addCar(char *carInfo[],List **carsList,int listIndex){

  if (listIndex == 1) {
      if ((*carsList)->avHead == NULL) {
        (*carsList)->avHead = newAvCar(carInfo);
      } else {
        insertAvC(carInfo,carsList);
      }
  } else if (listIndex == 2) {
    if ((*carsList)->renHead == NULL) {
      (*carsList)->renHead = newRenCar(carInfo);
    } else {
      insertRenC(carInfo,carsList);
    }
  } else if (listIndex == 3) {
    if ((*carsList)->repHead == NULL) {
      (*carsList)->repHead = newRepCar(carInfo);
    } else {
      insertRepC(carInfo,carsList);
    }
  }
}

void moveCar(char *carInfo[],List **carsList,int sourceIndex, int destinationIndex) {
  if (sourceIndex == 1){
      AvaliableList* tempCar = malloc(sizeof(AvaliableList));
      tempCar = (*carsList)->avHead;
      if (tempCar == NULL) {
        printf("Im sorry, there are no items in that list\n");
        return;
      }
      carInfo[2] = carInfo[0];
      carInfo[0] = malloc(sizeof(tempCar->plateNumber));
      carInfo[0] = tempCar->plateNumber;
      carInfo[1] = malloc(sizeof(tempCar->millage));
      sprintf(carInfo[1],"%d",tempCar->millage);
      printf("Congradulations, you just rented the car %s.\n",tempCar->plateNumber);
      addCar(carInfo,carsList,destinationIndex);
      deleteAv(tempCar,carsList);
  } else if (sourceIndex == 2){
      RentedList* tempCar = malloc(sizeof(RentedList));
      tempCar = (*carsList)->renHead;
      double rentalFee = 40;
      if (tempCar == NULL) {
        printf("Im sorry, there are no items in that list\n");
        return;
      }
      //move through the rentedcar list
      while (tempCar != NULL) {
        carInfo[0] = removeNL(carInfo[0]);
        //if it finds a matching license plate
        if (strcmp(tempCar->plateNumber,carInfo[0]) == 0){
          if (atoi(carInfo[1])-tempCar->millage > 100){
            rentalFee += (atoi(carInfo[1])-tempCar->millage-100)*0.15;
          }
          (*carsList)->income += rentalFee;
          if (destinationIndex == 1) printf("Moving car %s from the Rented list, to the Avaliable to rent list.\n",tempCar->plateNumber);
          if (destinationIndex == 3) printf("Moving car %s from the Rented list, to the Repair list.\n",tempCar->plateNumber);
          deleteRen(tempCar,carsList);
          addCar(carInfo,carsList,destinationIndex);
          return;
        }
        tempCar = tempCar->nextCar;
      }
      printf("That rental car is not on the list, sorry\n");
  } else if (sourceIndex == 3){
      RepairList* tempCar = malloc(sizeof(RepairList));
      tempCar = (*carsList)->repHead;
      if (tempCar == NULL) {
        printf("Im sorry, there are no items in that list\n");
        return;
      }
      //move through the repaircar list
      while (tempCar != NULL) {
        carInfo[0] = removeNL(carInfo[0]);
        //if it finds a matching license plate
        if (strcmp(tempCar->plateNumber,carInfo[0]) == 0){
          sprintf(carInfo[1],"%d",tempCar->millage);
          printf("Moving car %s from the Rapair list, to the Avaliable to rent list.\n",tempCar->plateNumber);
          deleteRep(tempCar,carsList);
          addCar(carInfo,carsList,destinationIndex);
          return;
        }
        tempCar = tempCar->nextCar;
      }
      printf("That car is not on the repair list, sorry\n");
  }
}

void insertAvC (char *carInfo[], List **carsList) {
  AvaliableList* tempCar = malloc(sizeof(AvaliableList));
  AvaliableList* leftCar = malloc(sizeof(AvaliableList));
  AvaliableList* rightCar = malloc(sizeof(AvaliableList));

  rightCar = (*carsList)->avHead;
  leftCar = rightCar;
  tempCar = newAvCar(carInfo);

  if (tempCar->millage < rightCar->millage){
    tempCar->nextCar = rightCar;
    (*carsList)->avHead = tempCar;
  } else {
    while (rightCar != NULL){
      if (rightCar->millage < tempCar->millage) {
        rightCar = rightCar->nextCar;
      } else break;
    }

    while (leftCar->nextCar != rightCar) {
      leftCar = leftCar->nextCar;
    }

    leftCar->nextCar = tempCar;
    tempCar->nextCar = rightCar;
  }
}

void insertRenC (char *carInfo[], List **carsList) {
  RentedList* tempCar = malloc(sizeof(RentedList));
  RentedList* leftCar = malloc(sizeof(RentedList));
  RentedList* rightCar = malloc(sizeof(RentedList));

  rightCar = (*carsList)->renHead;
  leftCar = rightCar;
  tempCar = newRenCar(carInfo);

  int year1 = 0,month1 = 0,day1 = 0;
  int year2 = 0,month2 = 0,day2 = 0;

  breakDate(tempCar->returnDate,&year1,&month1,&day1);
  breakDate(rightCar->returnDate,&year2,&month2,&day2);
  if (((year1 <= year2) && (month1 <= month2) && (day1 < day2)) || (year1 < year2) || ((year1 <= year2) && (month1 < month2))){
    tempCar->nextCar = rightCar;
    (*carsList)->renHead = tempCar;
  } else {
    rightCar = rightCar->nextCar;
    while (rightCar != NULL){
      breakDate(rightCar->returnDate,&year2,&month2,&day2);
      if ((year2 < year1) || ((year2 <= year1) && (month2 < month1)) || ((year2 <= year1) && (month2 <= month1) && (day2 < day1))){
        rightCar = rightCar->nextCar;
      } else break;
    }

    int i = 0;
    while (leftCar->nextCar != rightCar) {
      leftCar = leftCar->nextCar;
      i++;
    }
    leftCar->nextCar = tempCar;
    tempCar->nextCar = rightCar;
  }
}

void insertRepC (char *carInfo[], List **carsList) {
  RepairList* tempCar = malloc(sizeof(RepairList));
  RepairList* rightCar = malloc(sizeof(RepairList));

  rightCar = (*carsList)->repHead;
  tempCar = newRepCar(carInfo);
  tempCar->nextCar = rightCar;
  (*carsList)->repHead = tempCar;
}

void breakDate(char *date,int* year, int* month, int* day) {
  char sYear[3];
  char sMonth[3];
  char sDay[3];
  sYear[0] = date[0];
  sYear[1] = date[1];
  sYear[2] = '\0';
  sMonth[0] = date[2];
  sMonth[1] = date[3];
  sMonth[2] = '\0';
  sDay[0] = date[4];
  sDay[1] = date[5];
  sDay[2] = '\0';
  *year = atoi(sYear);
  *month = atoi(sMonth);
  *day = atoi(sDay);
}

AvaliableList* newAvCar (char *carInfo[]) {
  AvaliableList* newAv = NULL;
  char* plateNumber;
  int millage;

  newAv = malloc(sizeof(AvaliableList));
  plateNumber = malloc(sizeof(carInfo[0]));

  //getting rid of the new line at the end of the last Info from the file formating
  if (carInfo[0][strlen(carInfo[0])-1] == '\n') carInfo[0][strlen(carInfo[0])-1] = '\0';

  strcpy(plateNumber,carInfo[0]);
  millage = atoi(carInfo[1]);

  newAv->plateNumber = plateNumber;
  newAv->millage = millage;
  newAv->nextCar = NULL;
  return newAv;
}

RentedList* newRenCar (char *carInfo[]) {
  RentedList* newRen = NULL;
  char* plateNumber;
  int millage;
  char* returnDate;

  newRen = malloc(sizeof(RentedList));
  plateNumber = malloc(sizeof(carInfo[0]));
  returnDate = malloc(sizeof(carInfo[2]));

  //getting rid of the new line at the end of the last Info from the file formating
  carInfo[0] = removeNL(carInfo[0]);
  carInfo[2] = removeNL(carInfo[2]);

  strcpy(plateNumber,carInfo[0]);
  millage = atoi(carInfo[1]);
  strcpy(returnDate,carInfo[2]);

  newRen->plateNumber = plateNumber;
  newRen->returnDate = returnDate;
  newRen->millage = millage;
  newRen->nextCar = NULL;
  return newRen;
}

RepairList* newRepCar (char *carInfo[]) {
  RepairList* newRep = NULL;
  char* plateNumber;
  int millage;
  char* estimateRepair;

  newRep = malloc(sizeof(RepairList));
  plateNumber = malloc(sizeof(carInfo[0]));
  estimateRepair = malloc(sizeof(carInfo[2]));

  //getting rid of the new line at the end of the last Info from the file formating
  carInfo[0] = removeNL(carInfo[0]);
  carInfo[2] = removeNL(carInfo[2]);

  strcpy(plateNumber,carInfo[0]);
  millage = atoi(carInfo[1]);
  strcpy(estimateRepair,carInfo[2]);

  newRep->plateNumber = plateNumber;
  newRep->millage = millage;
  newRep->estimateRepair = estimateRepair;
  newRep->nextCar = NULL;
  return newRep;
}

void deleteAv(AvaliableList* toDelete, List** carsList){
  AvaliableList* leftCar = malloc(sizeof(AvaliableList));

  leftCar = (*carsList)->avHead;

  if (leftCar == toDelete){
    (*carsList)->avHead = leftCar->nextCar;
  } else {
    while (leftCar->nextCar != toDelete) {
      leftCar = leftCar->nextCar;
    }

    leftCar->nextCar = toDelete->nextCar;
  }

  free(toDelete->plateNumber);
  free(toDelete);
}

void deleteRen(RentedList* toDelete, List** carsList){
  RentedList* leftCar = malloc(sizeof(RentedList));

  leftCar = (*carsList)->renHead;

  if (leftCar == toDelete){
    (*carsList)->renHead = leftCar->nextCar;
  } else {
    while (leftCar->nextCar != toDelete) {
      leftCar = leftCar->nextCar;
    }

    leftCar->nextCar = toDelete->nextCar;
  }

  free(toDelete->plateNumber);
  free(toDelete->returnDate);
  free(toDelete);
}

void deleteRep(RepairList* toDelete, List** carsList){
  RepairList* leftCar = malloc(sizeof(RepairList));

  leftCar = (*carsList)->repHead;

  if (leftCar == toDelete){
    (*carsList)->repHead = leftCar->nextCar;
  } else {
    while (leftCar->nextCar != toDelete) {
      leftCar = leftCar->nextCar;
    }

    leftCar->nextCar = toDelete->nextCar;
  }

  free(toDelete->plateNumber);
  free(toDelete->estimateRepair);
  free(toDelete);
}

void printList(List* carsList){
  printf("***********************\n");
  printf("Available for Rent List\n");
  printf("***********************\n");
  printAV(carsList->avHead);
  printf("***********************\n");
  printf("Rented List\n");
  printf("***********************\n");
  printRen(carsList->renHead);
  printf("***********************\n");
  printf("Repair List\n");
  printf("***********************\n");
  printRep(carsList->repHead);
}

void printAV(AvaliableList* car) {
  AvaliableList* tempcar = malloc(sizeof(AvaliableList));
  tempcar = car;
  while (tempcar != NULL){
    printf("License Plate: %s Millage: %0.7d\n",tempcar->plateNumber,tempcar->millage);
    printf("--------------\n");
    tempcar = tempcar->nextCar;
  }
}

void printRen(RentedList* car) {
  RentedList* tempcar = malloc(sizeof(RentedList));
  tempcar = car;
  while (tempcar != NULL){
    printf("License Plate: %s Millage: %0.7d Return Date: %s\n",tempcar->plateNumber,tempcar->millage,tempcar->returnDate);
    printf("--------------\n");
    tempcar = tempcar->nextCar;
  }
}

void printRep(RepairList* car) {
  RepairList* tempcar = malloc(sizeof(RepairList));
  tempcar = car;
  while (tempcar != NULL){
    printf("License Plate: %s Millage: %0.7d Estimated Repair date: %s\n",tempcar->plateNumber,tempcar->millage,tempcar->estimateRepair);
    printf("--------------\n");
    tempcar = tempcar->nextCar;
  }
}

char* removeNL(char* string){
  if (string[strlen(string)-1] == '\n') string[strlen(string)-1] = '\0';
  return string;
}
