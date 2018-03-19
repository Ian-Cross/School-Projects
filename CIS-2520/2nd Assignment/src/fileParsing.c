#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "linkedList.h"
#include "fileOpening.h"
#include "fileParsing.h"

List* readFile(List* Head, char* fileName){
	List* carsList = NULL;
	carsList = createLists();
	char data[151];
	int listIndex = 0;
	FILE* diskFile = openFile(fileName,"r");

	while (fgets(data,150,diskFile) != NULL){
		if (isdigit(data[0])){
			listIndex++;
		} else {
			char *carInfo[3];
			char *token;
			int i = 0;

			//breaking up each line and storing the individual parts into their lists
			token = strtok(data," ");
			while (token != NULL){
				//making space for the string in the array
				carInfo[i] = malloc(strlen(token)+1);
				strcpy(carInfo[i],token);
				token = strtok(NULL," ");
				i++;
			}
			carInfo[0] = upperCase(carInfo[0]);
			addCar(carInfo,&carsList,listIndex);

			free(carInfo[0]); free(carInfo[1]); free(carInfo[2]);
		}
	}
	fclose(diskFile);
	return carsList;
}

void printFile(List** carsList,char* fileName){
	FILE* diskFile = openFile(fileName,"w");
	AvaliableList* avCar = malloc(sizeof(AvaliableList));
	avCar = (*carsList)->avHead;
	fprintf(diskFile, "1\n");
	while (avCar != NULL) {
		fprintf(diskFile, "%s %d\n",avCar->plateNumber,avCar->millage);
		avCar = avCar->nextCar;
	}
	free(avCar);
	RentedList* renCar = malloc(sizeof(RentedList));
	renCar = (*carsList)->renHead;
	fprintf(diskFile, "1\n");
	while (renCar != NULL) {
		fprintf(diskFile, "%s %d %s\n",renCar->plateNumber,renCar->millage,renCar->returnDate);
		renCar = renCar->nextCar;
	}
	free(renCar);
	RepairList* repCar = malloc(sizeof(RepairList));
	repCar = (*carsList)->repHead;
	fprintf(diskFile, "1\n");
	while (repCar != NULL) {
		fprintf(diskFile, "%s %d %s\n",repCar->plateNumber,repCar->millage,repCar->estimateRepair);
		repCar = repCar->nextCar;
	}
	free(repCar);
	fclose(diskFile);
}

char* upperCase(char* toblow){
	char* upper =  malloc(sizeof(toblow));
	for (int i = 0; i < strlen(toblow); i++){
		upper[i] = toupper(toblow[i]);
	}
	return upper;
}
