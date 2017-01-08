#include <stdio.h>
#include "linkedList.h"
#include "fileParsing.h"
#include "menu.h"

int main(int argc, char *argv[]) {
  List* Head = NULL;
  Head = readFile(Head,argv[1]);
  menu(&Head,argv[1]);
  return 0;
}
