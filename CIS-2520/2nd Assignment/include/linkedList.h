#ifndef __icross_linkedList__
#define __icross_linkedList__

typedef struct avaliableList {
  char* plateNumber;
  int millage;
  struct avaliableList* nextCar;
} AvaliableList;

typedef struct rentedList {
  char* plateNumber;
  int millage;
  char* returnDate;
  struct rentedList* nextCar;
} RentedList;

typedef struct repairList {
  char* plateNumber;
  int millage;
  char* estimateRepair;
  struct repairList* nextCar;
} RepairList;

typedef struct list {
  AvaliableList* avHead;
  RentedList* renHead;
  RepairList* repHead;
  double income;
} List;

/*************
 *Function Name: createcar
 *Function Description:
 *Parameters In:
 *Parameters output:
 *Errors:
 *************/
List* createLists();

/*************
 *Function Name: createcar
 *Function Description:
 *Parameters In:
 *Parameters output:
 *Errors:
 *************/
void addCar (char *carInfo[],List **carsList, int listIndex);

void moveCar(char *carInfo[],List **carsList,int sourceIndex, int destinationIndex);

/*************
 *Function Name: createcar
 *Function Description:
 *Parameters In:
 *Parameters output:
 *Errors:
 *************/
void insertAvC (char *carInfo[], List **carsList);

/*************
 *Function Name: createcar
 *Function Description:
 *Parameters In:
 *Parameters output:
 *Errors:
 *************/
void insertRenC (char *carInfo[], List **carsList);

void insertRepC (char *carInfo[], List **carsList);
/*************
 *Function Name: createcar
 *Function Description:
 *Parameters In:
 *Parameters output:
 *Errors:
 *************/
void breakDate(char *date,int* year, int* month, int* day);

/*************
 *Function Name: createcar
 *Function Description:
 *Parameters In:
 *Parameters output:
 *Errors:
 *************/
 AvaliableList* newAvCar (char *carInfo[]);

 /*************
  *Function Name: createcar
  *Function Description:
  *Parameters In:
  *Parameters output:
  *Errors:
  *************/
  RentedList* newRenCar (char *carInfo[]);

 /*************
  *Function Name: createcar
  *Function Description:
  *Parameters In:
  *Parameters output:
  *Errors:
  *************/
  RepairList* newRepCar (char *carInfo[]);

  void deleteAv(AvaliableList* toDelete,List** carsList);
  void deleteRen(RentedList* toDelete,List** carsList);
  void deleteRep(RepairList* toDelete,List** carsList);

  void printList(List* carsList);
 /*************
  *Function Name: createcar
  *Function Description:
  *Parameters In:
  *Parameters output:
  *Errors:
  *************/
 void printAV(AvaliableList* car);

  /*************
   *Function Name: createcar
   *Function Description:
   *Parameters In:
   *Parameters output:
   *Errors:
   *************/
  void printRen(RentedList* car);

   /*************
    *Function Name: createcar
    *Function Description:
    *Parameters In:
    *Parameters output:
    *Errors:
    *************/
   void printRep(RepairList* car);

   char* removeNL(char* string);
#endif
