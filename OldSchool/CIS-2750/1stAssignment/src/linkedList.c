#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

List* createList(){
  List* newList = NULL;

  /* gives memory for the list */
  newList = malloc(sizeof(List));
  if (newList == NULL) {
      /* quites when there isn't enought memory */
      printf("Sorry, there isn't enough memory\n");
      exit(1);
  }
  /* initalizes values */
  newList->head = NULL;
  newList->nextList = NULL;

  return newList;
}

Item* createItem(char* data){
    Item* newItem = NULL;

    /* creates space for the item */
    newItem = (Item*)malloc(sizeof(Item));
    if (newItem == NULL) {
        /* quites when there isn't enought memory */
        printf("Sorry, there isn't enough memory\n");
        exit(1);
    }
    /* creates space to store the itesm name */
    newItem->name = (char*)malloc(sizeof(char)*strlen(data) + 1);
    if (newItem->name == NULL) {
        /* quites when there isn't enought memory */
        printf("Sorry, there isn't enough memory\n");
        exit(1);
    }
    /* initalizes the values with the given data */
    strcpy(newItem->name,data);
    newItem->nextItem = NULL;
    newItem->prevItem = NULL;

    return newItem;
 }

List* addItem(List* list, char* data){
    /* making sure that there is something to add to */
    if (list == NULL){
        printf("I'm sorry, no list exists\n");
    } else {
        Item* newItem = NULL;
        Item* myItem = list->head;
        /* creates the new item to append to the list */
        newItem = createItem(data);
        /* define it as the head of the list if the list was empty */
        if (myItem == NULL){
            list->head = newItem;
        } else {
            /* move to the end of the list */
            while (myItem->nextItem != NULL){
                myItem = myItem->nextItem;
            }
            /* link it to the last item in the list */
            myItem->nextItem = newItem;
            newItem->prevItem = myItem;
        }
    }
    return list;
}

void deleteList(List* list){
    /* Clean up the items if there are any*/
    if (list->head != NULL){
        deleteItems(list->head);
    }
    /* cleans up the memory used by the list */
    free(list);
}

void deleteItems(Item* item){
    /* recursively moves to the end of the list */
    if (item->nextItem != NULL){
        deleteItems(item->nextItem);
    }
    /* cleans up the memory used by the items */
    free(item->name);
    free(item);
}

void printList(List* theList, FILE* outputFile){
    Item* printItem = theList->head;
    /* move through the list printing each item as you go */
    while (printItem != NULL){
        fprintf(outputFile,"%s\n",printItem->name);
        printItem = printItem->nextItem;
    }
}

List* addItemFront(List* list, char* data){
    Item* newItem;
    Item* oldHead = list->head;

    /* creates a new item */
    newItem = createItem(data);
    /* sets the head to our new item, linking the old list on after */
    newItem->nextItem = oldHead;
    oldHead->prevItem = newItem;
    list->head = newItem;
    return list;
}

List* removeItemFront(List* list){
    Item* tempItem = list->head;
    /* points the head to the next item effectivly "forgetting" the first item */
    list->head = tempItem->nextItem;

    /* cleans up the memory used by the item */
    free(tempItem->name);
    free(tempItem);
    return list;
}

List* removeItemBack(List* list){
    Item* tempItem = list->head;

    /* Move to the end of the list */
    while (tempItem->nextItem != NULL){
        tempItem = tempItem->nextItem;
    }

    tempItem->prevItem->nextItem = NULL;

    /* cleans up the memory used by the item */
    free(tempItem->name);
    free(tempItem);
    return list;
}

Prog* createProgram(List* data){
    Item* programInfo = data->head;
    Item* tempItem = programInfo;

    int scope = 0;
    int links = 0;

    /* Give space for the new Program */
    Prog* newProgram = (Prog*)malloc(sizeof(Prog));
    if (newProgram == NULL){
        printf("Sorry, there wasn't enough space\n");
        exit(1);
    }

    /* initalize values */
    newProgram->functions = NULL;
    newProgram->globalVars = NULL;
    newProgram->garbage = createList();
    newProgram->classes = NULL;
    newProgram->prototype = NULL;
    newProgram->includes = createList();
    newProgram->nextProgram = NULL;

    /* Make sure that the data was sent properly */
    if (programInfo == NULL){
        printf("I can't create a program from nothing\n");
        exit(1);
    } else {
        /* Cycle through all the given data */
        while (programInfo != NULL){
            /* Looking for classes in the program */
            if (strcmp(programInfo->name,"class") == 0 || strcmp(programInfo->name,"struct") == 0){
                tempItem = programInfo->nextItem->nextItem;
                /* If following the class keyword is a "{" we know that it
                will be a class definition*/
                if (strcmp(tempItem->name,"{") == 0){
                    scope++;
                    links = 3;
                    printf("I found a class Definition\n");
                    /* Move through the list until the end of the class
                    taking everything inside with it */
                    while (scope != 0){
                        tempItem = tempItem->nextItem;
                        if (strcmp(tempItem->name,"{") == 0)scope++;
                        else if (strcmp(tempItem->name,"}") == 0)scope--;
                        links++;
                    }
                    /* Create the class  */
                    newProgram->classes = addClass(newProgram->classes,programInfo,links);
                    /* Adjust the info pointer */
                    int i;
                    for (i = 0; i < links; i++){
                        programInfo = programInfo->nextItem;
                    }
                    links = 0;
                } else {
                    printf("I found a class Creation\n");
                }
            } else if (isType(programInfo->name,NULL)){
                /* Moves past all the type calls */
                tempItem = programInfo;
                List* newVariable = createList();
                links = 1;
                while (isType(tempItem->name,NULL)){
                    newVariable = addItem(newVariable,tempItem->name);
                    tempItem = tempItem->nextItem;
                    links++;
                }
                /* look at the thing after the name */
                newVariable = addItem(newVariable,tempItem->name);
                tempItem = tempItem->nextItem;
                links++;

                if (strcmp(tempItem->name,"(") == 0){
                    links++;
                    /* Move past the parameters for now, counting how many there are */
                    while (tempItem != NULL){
                        if (strcmp(tempItem->name,"{") == 0){
                            printf("I found a Function definition\n");
                            scope++;
                            /* Move to the end of the funtion and send it all to be handled */
                            while (scope != 0){
                                tempItem = tempItem->nextItem;
                                if (strcmp(tempItem->name,"{") == 0)scope++;
                                else if (strcmp(tempItem->name,"}") == 0)scope--;
                                links++;
                            }
                            newProgram->functions = addFunction(newProgram->functions,programInfo,links);
                            break;
                        } else if (strcmp(tempItem->name,";") == 0) {
                            /* Handle the creation of a function prototype */
                            printf("I found a Function prototype\n");
                            /* newProgram->prototype = addPrototype(newProgram->prototype,programInfo,links); */
                            break;
                        }
                        tempItem = tempItem->nextItem;
                        links++;
                    }
                    /* Move the main pointer along */
                    int i;
                    for (i = 2; i < links; i++){
                        programInfo = programInfo->nextItem;
                    }
                    links = 0;
                } else {
                    /* Move to the end of the variable collecting the data */
                    printf("I found a Variable\n");
                    while (strcmp(tempItem->name,";") != 0){
                        if (strcmp(tempItem->name,",") == 0){
                            newVariable = addItem(newVariable,";");
                            newProgram->globalVars = addVariable(newProgram->globalVars,newVariable->head,links);
                            links-=2;
                            newVariable = removeItemBack(newVariable);
                            newVariable = removeItemBack(newVariable);
                        } else {
                            newVariable = addItem(newVariable,tempItem->name);
                        }
                        tempItem = tempItem->nextItem;
                        links++;
                    }
                    /* send off the data to be created */
                    newVariable = addItem(newVariable,tempItem->name);
                    newProgram->globalVars = addVariable(newProgram->globalVars,newVariable->head,links);
                    /* Update the info pointer */
                    int i;
                    for (i = 1; i < links; i++){
                        programInfo = programInfo->nextItem;
                    }
                    links = 0;
                }
                deleteList(newVariable);
            } else if (strcmp(programInfo->name,"#include") == 0) {
                /* Store away the includes, to add to the top of the file later */
                programInfo = programInfo->nextItem;
                newProgram->includes = addItem(newProgram->includes,programInfo->name);
            } else {
                /* Just incase something gets through store it away */
                printf("I found some garbage %s\n", programInfo->name);
                newProgram->garbage = addItem(newProgram->garbage,programInfo->name);
            }
            programInfo = programInfo->nextItem;
        }
        newProgram->nextProgram = NULL;
        printf("DONE PROGRAM CREATION\n");
    }

    return newProgram;
}

Class* createClass(Item* data, int links){
    Item* classInfo = data;
    Item* tempItem;
    int localLinks = 0;
    int scope = 0;

    Class* newClass = malloc(sizeof(Class));
    if (newClass == NULL) {
        printf("Sorry, there wasn't enough space\n");
        exit(1);
    }

    /* Initalize the values */
    newClass->localFuncs = NULL;
    newClass->localVars = NULL;
    newClass->name = NULL;
    newClass->constructor = 0;
    newClass->nextClass = NULL;

    /* We have a list containing all the information needed about the class */
    /* if the first thing in the list isn't the right keyword, just quit out */
    if (strcmp(classInfo->name,"class") != 0 && strcmp(classInfo->name,"struct") != 0){
        printf("Something is wrong, the data list given is not a class\n");
        free(newClass);
        return NULL;
    }

    /* The second thing should be the class name */
    classInfo = classInfo->nextItem;
    newClass->name = malloc(sizeof(char)*strlen(classInfo->name) + 1);
    if (newClass->name == NULL) {
        printf("Sorry, there wasn't enough space\n");
        exit(1);
    }
    strcpy(newClass->name,classInfo->name);

    /* Our for loop is starting at 3 here to cut off the
    the tokens we have already used, and what we know will be there, "class x {" */
    classInfo = classInfo->nextItem->nextItem;
    int i;
    for (i = 3; i < links; i++){
        if (isType(classInfo->name,NULL)){
            /* Move passed all the types and name to see if it is a variable or a function */
            tempItem = classInfo;
            localLinks++;
            List* newVariable = createList();
            int variablelinks = 0;
            while (isType(tempItem->name,NULL)) {
                newVariable = addItem(newVariable,tempItem->name);
                variablelinks++;
                tempItem = tempItem->nextItem;
                localLinks++;
            }
            newVariable = addItem(newVariable,tempItem->name);
            variablelinks++;

            tempItem = tempItem->nextItem;
            localLinks++;

            /* Finding out it is a function */
            if (strcmp(tempItem->name,"(") == 0){
                printf("I found a function in this class\n");
                /* Move past the parameters for now, counting how many there are */
                while (strcmp(tempItem->name,"{") != 0){
                    tempItem = tempItem->nextItem;
                    localLinks++;
                }
                scope++;
                /* Move to the end of the funtion and send it all to be handled */
                while (scope != 0){
                    tempItem = tempItem->nextItem;
                    if (strcmp(tempItem->name,"{") == 0)scope++;
                    else if (strcmp(tempItem->name,"}") == 0)scope--;
                    localLinks++;
                }
                newClass->localFuncs = addFunction(newClass->localFuncs,classInfo,localLinks);
                printf("The number of links in the Function are %d\n",localLinks);
                /* Move the main pointer along */
                int j;
                for (j = 1; j < localLinks; j++){
                    classInfo = classInfo->nextItem;
                }
                i+=localLinks;
                localLinks = 0;
            } else {
                printf("I found a variable in this Class\n");
                /* Move to the end of the variable collecting all the data */
                while (strcmp(tempItem->name,";") != 0){
                    if (strcmp(tempItem->name,",") == 0){
                        newVariable = addItem(newVariable,";");
                        variablelinks++;
                        newClass->localVars = addVariable(newClass->localVars,newVariable->head,variablelinks);
                        variablelinks-=2;
                        newVariable = removeItemBack(newVariable);
                        newVariable = removeItemBack(newVariable);
                    } else {
                        newVariable = addItem(newVariable,tempItem->name);
                    }
                    tempItem = tempItem->nextItem;
                    localLinks++;
                }
                /* send off the data to be created */
                newVariable = addItem(newVariable,tempItem->name);
                newClass->localVars = addVariable(newClass->localVars,newVariable->head,variablelinks);
                printf("The number of links in the Variable are %d\n",localLinks);
                /* Move the info pointer along */
                int j;
                for (j = 1; j < localLinks; j++){
                    classInfo = classInfo->nextItem;
                }
                i+=localLinks;
                localLinks = 0;
            }
            deleteList(newVariable);
        } else {
            /* If something bad happens dont quit */
            printf("I don't know what I'm looking at  %s\n", classInfo->name);
        }
        classInfo = classInfo->nextItem;
    }
    printf("DONE CLASS CREATION\n");
    return newClass;
}

Function* createFunction(Item* data, int links){
    Item* funcInfo = data;
    Function* newFunc = NULL;
    int localLinks = 0;

    if (funcInfo == NULL){
        printf("I can't make a function from nothing\n");
    } else {
        newFunc = malloc(sizeof(Function));
        if (newFunc == NULL) {
            printf("Sorry, there wasn't enough space\n");
            exit(1);
        }

        /* Initalizing values */
        newFunc->type = NULL;
        newFunc->name = NULL;
        newFunc->localVars = NULL;
        newFunc->parameters = NULL;
        newFunc->guts = NULL;
        newFunc->classVar = 0;
        newFunc->oldName = NULL;
        newFunc->nextFunc = NULL;

        newFunc->type = malloc(sizeof(char)*100);
        if (newFunc->type == NULL) {
            printf("Sorry, there wasn't enough space\n");
            exit(1);
        }

        /* The first thing sent should be the
        return type of the function */
        strcpy(newFunc->type,funcInfo->name);
        funcInfo = funcInfo->nextItem;
        while (isType(funcInfo->name,NULL)){
            strcat(newFunc->type," ");
            strcat(newFunc->type,funcInfo->name);
            funcInfo = funcInfo->nextItem;
        }

        /* The next thing after the type should
        be the name of the function */
        newFunc->name = (char*)malloc(sizeof(char)*(strlen(funcInfo->name) + 1));
        newFunc->oldName = malloc(sizeof(char)*strlen(funcInfo->name) + 1);
        if (newFunc->name == NULL) {
            printf("Sorry, there wasn't enough space\n");
            exit(1);
        }
        if (newFunc->oldName == NULL) {
            printf("Sorry, there wasn't enough space\n");
            exit(1);
        }
        strcpy(newFunc->name,funcInfo->name);
        strcpy(newFunc->oldName,funcInfo->name);
        funcInfo = funcInfo->nextItem;

        /* We should be at the parameters now,
        double check to make sure nothing went wrong */
        if (strcmp(funcInfo->name,"(") != 0){
            deleteFunction(newFunc);
            printf("Something went wrong with the parameters, %s\n",newFunc->name);
            return NULL;
        }

        localLinks = 0;
        int scope = 0;
        Item* tempItem = funcInfo;

        /* Look until the close bracket */
        do {
            tempItem = tempItem->nextItem;
            localLinks++;
            if ((strcmp(tempItem->name,",") == 0 || strcmp(tempItem->name,")") == 0) && localLinks > 1){
                newFunc->parameters = addVariable(newFunc->parameters,funcInfo,localLinks);
                int i;
                for (i = 0; i < localLinks; i++){
                    funcInfo = funcInfo->nextItem;
                }
                localLinks = 0;
            }
        } while (strcmp(tempItem->name,")") != 0);

        printf("PARAMETERS FOR FUNCTION %s\n",newFunc->name);
        Variable* params = newFunc->parameters;
        while (params != NULL){
            printf("%s %s\n",params->type,params->name);
            params = params->nextVar;
            printf("break\n");
        }

        /* Move past the ")" */
        funcInfo = tempItem->nextItem;

        if (strcmp(funcInfo->name,"{") == 0){
            newFunc->guts = createList();
            /* We then have to deal with what is actually in the function */
            newFunc->guts = addItem(newFunc->guts,funcInfo->name);
            scope++;
            funcInfo = funcInfo->nextItem;

            while(scope != 0){
                if (strcmp(funcInfo->name,"{") == 0){
                    scope++;
                } else if (strcmp(funcInfo->name,"}") == 0) {
                    scope--;
                }

                /* take all the collected data and add to the function body */
                newFunc->guts = addItem(newFunc->guts,funcInfo->name);
                funcInfo = funcInfo->nextItem;
            }
            scope = 0;
        } else if (strcmp(funcInfo->name,";") == 0){
            printf("Created Funtion prototype\n");
        } else {
            printf("Something went horribly wrong\n");
        }


        newFunc->localVars = NULL;
        printf("DONE FUNCTION CREATION\n");
    }
    return newFunc;
}

Function* createPrototype(Function* func){
    Function* newFunc = malloc(sizeof(Function));
    if (newFunc == NULL){
        printf("Sorry there wasn't enough space\n");
        exit(1);
    }

    /* Initalizing values */
    newFunc->type = func->type;
    newFunc->name = func->name;
    newFunc->localVars = NULL;
    newFunc->parameters = func->parameters;
    newFunc->guts = NULL;
    newFunc->classVar = 0;
    newFunc->oldName = NULL;
    newFunc->nextFunc = NULL;

    return newFunc;
}

Variable* createVariable(Item* data, int links){
    Item* varInfo = data;
    Variable* newVar = NULL;
    if (varInfo == NULL){
        printf("I can't make a variable from nothing\n");
    } else {
        newVar = malloc(sizeof(Variable));
        if (newVar == NULL){
            printf("I'm sorry there wasn't enough space\n");
            exit(1);
        }

        /* Initalizing values */
        newVar->type = NULL;
        newVar->name = NULL;
        newVar->value = NULL;
        newVar->nextVar = NULL;

        newVar->type = malloc(sizeof(char)*100);
        if (newVar->type == NULL) {
            printf("I'm sorry there wasn't enough space\n");
            exit(1);
        }

        /* If there is a leading bracket or  we know we are
        dealing with function parameters so just skip it */
        if (strcmp(varInfo->name,"(") == 0 || strcmp(varInfo->name,",") == 0) {
            /* Move passed the leading "(" */
            varInfo = varInfo->nextItem;
        }

        /* Next thing we need is the type of the variable */
        strcpy(newVar->type,varInfo->name);
        varInfo = varInfo->nextItem;
        while (isType(varInfo->name,NULL)){
            strcat(newVar->type," ");
            strcat(newVar->type,varInfo->name);
            varInfo = varInfo->nextItem;
        }
        /* Pointer type */
        if (strcmp(varInfo->name,"*") == 0){
            strcat(newVar->type," *");
            varInfo = varInfo->nextItem;
        }

        if (strcmp(varInfo->name,",") != 0){
            /* The name of the variable should be next */
            newVar->name = malloc(sizeof(char)*strlen(varInfo->name) + 1);
            strcpy(newVar->name,varInfo->name);
            varInfo = varInfo->nextItem;

            /* Next will either be a ";" or an "=" if there is an assignemnt as well */
            if (strcmp(varInfo->name,";") != 0 && strcmp(varInfo->name,",") != 0 && strcmp(varInfo->name,")") != 0){
                newVar->value = malloc(sizeof(char)*(strlen(varInfo->nextItem->name) + 3));
                strcpy(newVar->value,varInfo->name);
                strcat(newVar->value," ");
                varInfo = varInfo->nextItem;
                strcat(newVar->value,varInfo->name);
            }
        }
        printf("DONE VARIABLE CREATION\n");
    }
    return newVar;
}

Class* addClass(Class* classList, Item* data, int links){
    Class* tempClass = classList;
    Class* newClass = NULL;
    /* No classes have been created yet */
    if (tempClass == NULL){
        classList = createClass(data,links);
    /* Some classes have been created */
    } else {
        newClass = createClass(data, links);
        while (tempClass->nextClass != NULL){
            tempClass = tempClass->nextClass;
        }
        tempClass->nextClass = newClass;
    }
    return classList;
}

Function* addFunction(Function* funcList, Item* data, int links){
    Function* tempFunc = funcList;
    Function* newFunc = NULL;
    /* No Functions have been created yet */
    if (tempFunc == NULL){
        funcList = createFunction(data,links);
    /* Some Functions have been created */
    } else {
        newFunc = createFunction(data, links);
        while (tempFunc->nextFunc != NULL){
            tempFunc = tempFunc->nextFunc;
        }
        tempFunc->nextFunc = newFunc;
    }
    return funcList;
}

Function* addPrototype(Function* funcList, Function* func){
    Function* newProto = NULL;
    Function* tempFunc = funcList;
    /* No Functions have been created yet */
    if (tempFunc == NULL){
        funcList = createPrototype(func);
    /* Some Functions have been created */
    } else {
        newProto = createPrototype(func);
        while (tempFunc->nextFunc != NULL){
            tempFunc = tempFunc->nextFunc;
        }
        tempFunc->nextFunc = newProto;
    }
    return funcList;
}

Variable* addVariable(Variable* varList, Item* data, int links){
    Variable* tempVar = varList;
    /* No variables have been created yet */
    if (tempVar == NULL){
        varList = createVariable(data,links);
    /* some variables have been created */
    } else {
        while (tempVar->nextVar != NULL) {
            tempVar = tempVar->nextVar;
        }
        tempVar->nextVar = createVariable(data,links);
    }
    return varList;
}

int isType(char* data,char* newType){
    List* types = createList();
    char* defaultTypes[16] = {"int","char","long","short","double","float","signed","unsigned", "extern", "register", "auto", "static", "const","void","typedef","volatile"};
    int i;

    /* Adding in all the default types */
    for (i = 0; i < 16; i++){
        types = addItem(types,defaultTypes[i]);
    }

    if (data == NULL && newType != NULL) {
        printf("FUCK off\n");
    }

    /* Tries to match up a given type */
    Item * currentType = types->head;
    while (currentType != NULL){
        if (strcmp(data,currentType->name) == 0){
            deleteList(types);
            return 1;
        }
        currentType = currentType->nextItem;
    }
    deleteList(types);
    return 0;
}

void printProgram(Prog* myProgram, FILE* outputFile){
    if (myProgram != NULL){

        myProgram = analyze(myProgram);

        /* Print out the includes in the file */
        if (myProgram->includes->head != NULL){
            printList(myProgram->includes, outputFile);
        }
        fprintf(outputFile,"\n");

        /* Print out all the global variables that are in the file */
        if (myProgram->globalVars != NULL){
            Variable* tempVar = myProgram->globalVars;
            while (tempVar != NULL) {
                printVariable(tempVar,0, outputFile);
                fprintf(outputFile,";\n");
                tempVar = tempVar->nextVar;
            }
            fprintf(outputFile,"\n");
        }

        /* Printing out the prototypes */
        if (myProgram->prototype != NULL){
            fprintf(outputFile, "/* Function Prototypes */\n");
            printFunction(myProgram->prototype,0, outputFile,myProgram->classes);
        }

        fprintf(outputFile,"\n");

        /* Printing out the structs of the file */
        if (myProgram->classes != NULL){
            printClass(myProgram->classes, outputFile);
        }

        fprintf(outputFile,"\n");

        /* Printing out functions that aren't part of a class */
        if (myProgram->functions != NULL){
            printFunction(myProgram->functions,0, outputFile,myProgram->classes);
        }

        /* Used for Debugging
        if (myProgram->garbage->head != NULL){
            fprintf(outputFile,"\n\nGarbage That slipped Through\n");
            printList(myProgram->garbage, outputFile);
        } */
    } else {
        printf("The program you tried to print was NULL\n");
    }
}

Prog* analyze(Prog* myProgram){
    /* First thing, we've got to do is make sure all the function
     names have been changed and the constructors have been created*/
    Class* tempClass = myProgram->classes;
    while (tempClass != NULL){
        /* change the function names in the program to match the naming style */
        tempClass = renameFuncs(tempClass);

        /* moving through all the functions associated with the class */
        Function* tempFunc = tempClass->localFuncs;
        while (tempFunc != NULL){
            Item* data = tempFunc->guts->head;
            Variable* param = tempFunc->parameters;
            List* localVars = NULL;
            localVars = createList();

            /* Store the function parameters in a searchable list */
            while (param != NULL){
                localVars = addItem(localVars,param->name);
                param = param->nextVar;
            }

            while (data != NULL){

                if (isType(data->name,NULL)){
                    data = data->nextItem;
                    localVars = addItem(localVars,data->name);
                }
                if (isClassVar(data->name,tempClass->localVars)){
                    if (!isLocalVar(data->name,localVars)){
                        char* newName = malloc(sizeof(char)*(strlen(data->name)+10));
                        strcpy(newName,"myClass->");
                        strcat(newName,data->name);
                        free(data->name);
                        data->name = newName;

                        if (tempFunc->classVar == 0){
                            tempFunc->classVar = 1;
                            List* newParam = createList();
                            char* paramType = malloc(sizeof(char) * (strlen(tempClass->name) + 9));
                            strcpy(paramType,"struct ");
                            strcat(paramType,tempClass->name);
                            strcat(paramType,"*");
                            newParam = addItem(newParam,paramType);
                            newParam = addItem(newParam,"myClass");
                            newParam = addItem(newParam,",");
                            tempFunc->parameters = addVariable(tempFunc->parameters,newParam->head,2);
                            free(paramType);
                            deleteList(newParam);
                        }
                    }
                }
                data = data->nextItem;
            }
            tempFunc = classReference(tempFunc,myProgram->classes);
            tempFunc = tempFunc->nextFunc;
            if (localVars != NULL) deleteList(localVars);
        }
        /* Build constructors to the funcion pointers give the pointes meaning */
        tempClass = createConstructor(tempClass);
        tempClass = tempClass->nextClass;
    }

    Function* globalFuncs = myProgram->functions;
    while (globalFuncs != NULL){
        globalFuncs = classReference(globalFuncs,myProgram->classes);
        globalFuncs = globalFuncs->nextFunc;
    }

    /* Prototyping each function so that there is no undelcared funcitons by accident */
    Function* currentFunc = myProgram->functions;
    while (currentFunc != NULL){
        if (strcmp(currentFunc->name,"main") != 0)
        myProgram->prototype = addPrototype(myProgram->prototype,currentFunc);
        currentFunc = currentFunc->nextFunc;
    }

    return myProgram;
}

int isClassVar(char* name, Variable* classVars){
    Variable* tempVars = classVars;
    while (tempVars != NULL){
        if(strcmp(name,tempVars->name) == 0) return 1;
        tempVars = tempVars->nextVar;
    }
    return 0;
}

int isLocalVar(char* name, List* localVars){
    Item* vars = localVars->head;
    while (vars != NULL){
        if (strcmp(name,vars->name) == 0) return 1;
        vars = vars->nextItem;
    }
    return 0;
}

Function* classReference(Function* theFunc, Class* classes){
    Item* data = theFunc->guts->head;
    Class* tempClasses = classes;
    List* definedClasses = NULL;
    List* matchedClass = NULL;
    definedClasses = createList();
    matchedClass = createList();
    while (data != NULL){
        if (strcmp(data->name,"class") == 0){
            data = data->nextItem;
            while(tempClasses != NULL) {
                if (strcmp(data->name,tempClasses->name) == 0){
                    matchedClass = addItem(matchedClass,tempClasses->name);
                    break;
                }
                tempClasses = tempClasses->nextClass;
            }
            data = data->nextItem;
            definedClasses = addItem(definedClasses,data->name);
        } else {
            Item* className = definedClasses->head;
            Item* classType = matchedClass->head;
            while (className != NULL){
                if(strcmp(className->name,data->name) == 0){
                    printf("Matched A class %s\n", data->name);
                    Class* tClass = classes;
                    while (tClass != NULL){
                        if (strcmp(tClass->name,classType->name) == 0){
                            break;
                        }
                        tClass = tClass->nextClass;
                    }
                    data = data->nextItem->nextItem;
                    if (strcmp(data->prevItem->name,".") == 0){
                        printf("Found a . operator %s  \n", tClass->name);
                    }
                    Function* classFuncs = tClass->localFuncs;
                    while (classFuncs != NULL){
                        if (strcmp(classFuncs->oldName,data->name) == 0){
                            data->name = realloc(data->name,sizeof(char)*strlen(classFuncs->name) + 1);
                            strcpy(data->name,classFuncs->name);
                            strcat(data->name,"\0");
                            data = data->nextItem;
                            if (strcmp(data->name,"(") == 0){
                                if (classFuncs->classVar == 1){
                                    data = data->nextItem;
                                    char* pName = malloc(sizeof(char)*(strlen(className->name)+ 4));
                                    if (strcmp(data->name,")") == 0) {
                                        strcpy(pName,"&");
                                    } else {
                                        strcpy(pName,", &");
                                    }
                                    strcat(pName,className->name);
                                    Item* newParam = createItem(pName);
                                    while (strcmp(data->name,")") != 0){
                                        data = data->nextItem;
                                    }
                                    newParam->nextItem = data;
                                    data->prevItem->nextItem = newParam;
                                    newParam->prevItem = data->prevItem;
                                    data->prevItem = newParam;
                                    free(pName);
                                }
                            }
                            break;
                        }
                        classFuncs = classFuncs->nextFunc;
                    }
                }
                classType = classType->nextItem;
                className = className->nextItem;
            }
        }

        data = data->nextItem;
    }
    if (definedClasses != NULL)deleteList(definedClasses);
    if (matchedClass != NULL) deleteList(matchedClass);
    return theFunc;
}

void printClass(Class* myClass, FILE* outputFile){
    Class* tempClass = myClass;
    while (tempClass != NULL){
        if (myClass != NULL){
            fprintf(outputFile,"struct %s {\n",tempClass->name);

            if (tempClass->localVars != NULL){
                Variable* tempVar = tempClass->localVars;
                while (tempVar != NULL){
                    printVariable(tempVar,1, outputFile);
                    fprintf(outputFile,";\n");
                    tempVar = tempVar->nextVar;
                }
            }
            fprintf(outputFile,"};\n");
            fprintf(outputFile,"\n");
            if (tempClass->localFuncs != NULL){
                printFunction(tempClass->localFuncs,0, outputFile,myClass);
            }
        } else {
            printf("The class you tried to print was NULL\n");
        }
        tempClass = tempClass->nextClass;
        fprintf(outputFile,"\n");
    }
}

Class* renameFuncs(Class* parent){
    char* className = malloc(sizeof(char)*strlen(parent->name) + 1);
    strcpy(className,parent->name);
    Function* localFuncs = parent->localFuncs;

    while (localFuncs != NULL){
        int count = 0;
        Variable* parameters = localFuncs->parameters;
        printf("Local func %s in class %s\n",localFuncs->name,className);
        while (parameters != NULL){
            count++;
            parameters = parameters->nextVar;
        }
        printf("count %d\n",count);
        char* newName = malloc(sizeof(char)*strlen(localFuncs->name) + 1 + sizeof(char)*strlen(className) + sizeof(char)*count);
        strcpy(newName,className);
        strcat(newName,localFuncs->name);

        parameters = localFuncs->parameters;
        count = strlen(newName);
        while (parameters != NULL){
            newName[count] = parameters->type[0];
            count++;
            parameters = parameters->nextVar;
        }
        newName[count] = '\0';
        free(localFuncs->name);
        localFuncs->name = newName;
        localFuncs = localFuncs->nextFunc;
    }


    free(className);
    return parent;
}

Class* createConstructor(Class* parent){
    printf("Creating Constructor %s\n",parent->name);
    Function* localFuncs = parent->localFuncs;
    /* Don't make a constructor if there are no functions in the class */
    if (localFuncs == NULL){
        return parent;
    }
    List* conData = createList();
    int links = 0;

    conData = addItem(conData,"void");
    char* conName = malloc(sizeof(char)*(strlen(parent->name) + 4));
    char* conType = malloc(sizeof(char)*(strlen(parent->name) + 9));
    strcpy(conName,"con");
    strcat(conName,parent->name);
    conData = addItem(conData,conName);
    conData = addItem(conData,"(");
    strcpy(conType,"struct ");
    strcat(conType,parent->name);
    strcat(conType,"*");
    conData = addItem(conData,conType);
    conData = addItem(conData,"myStruct");
    conData = addItem(conData,")");
    conData = addItem(conData,"{");

    links = 6;

    while (localFuncs != NULL){
        List* data = createList();
        data = addItem(data,localFuncs->type);
        int count = 0;
        Variable* paramList = localFuncs->parameters;
        while (paramList != NULL){
            count += strlen(paramList->type) + 2;
            paramList = paramList->nextVar;
        }
        char* name = malloc(sizeof(localFuncs->name) + sizeof(char)*(6 + count));
        strcpy(name,"(*");
        strcat(name,localFuncs->name);
        strcat(name,")(");
        paramList = localFuncs->parameters;
        while (paramList != NULL){
            strcat(name,paramList->type);
            paramList = paramList->nextVar;
            if (paramList != NULL){
                strcat(name,", ");
            }
        }
        strcat(name,")\0");
        data = addItem(data,name);
        data = addItem(data,";");

        conData = addItem(conData,"myStruct->");
        conData = addItem(conData,localFuncs->name);
        conData = addItem(conData,"=");
        conData = addItem(conData,localFuncs->name);
        conData = addItem(conData,";");

        links += 5;
        parent->localVars = addVariable(parent->localVars,data->head,3);
        localFuncs = localFuncs->nextFunc;
        deleteList(data);
        free(name);
    }
    conData = addItem(conData,"}");
    parent->localFuncs = addFunction(parent->localFuncs,conData->head,links);
    parent->constructor = 1;
    free(conName);
    free(conType);
    deleteList(conData);
    return parent;
}

void printFunction(Function* myFunc , int indent, FILE* outputFile, Class* classes){
    Function* tempFunc = myFunc;
    while (tempFunc != NULL){
        if (tempFunc != NULL){
            int i;
            for (i = 0; i < indent; i++) {
                fprintf(outputFile,"\t");
            }
            fprintf(outputFile,"%s %s",tempFunc->type,tempFunc->name);
            if (tempFunc->parameters != NULL){
                fprintf(outputFile,"( ");
                Variable* tempVar = tempFunc->parameters;
                while (tempVar != NULL){
                    printVariable(tempVar, 0, outputFile);
                    tempVar = tempVar->nextVar;
                    if (tempVar != NULL) fprintf(outputFile,", ");
                }
                fprintf(outputFile,")");
            } else {
                fprintf(outputFile,"()");
            }

            if (tempFunc->guts != NULL){
                printAsFunc(tempFunc->guts,indent, outputFile,classes);
            } else {
                fprintf(outputFile,";");
            }
        } else {
            printf("The function you tried to print was NULL\n");
        }
        tempFunc = tempFunc->nextFunc;
        fprintf(outputFile,"\n");
    }
}

void printProto(Function* myFunc , int indent, FILE* outputFile){
    Function* tempFunc = myFunc;
    while (tempFunc != NULL){

    }
    fprintf(outputFile,"IM HEREREERERER\n");
}

void printAsFunc(List* theList, int indent, FILE* outputFile, Class* classes){
    Item* printItem = theList->head;
    int scope = indent;
    int first = 0;
    int needCon = 0;
    char* conName = malloc(sizeof(char));
    char* varName = malloc(sizeof(char));
    while (printItem != NULL) {
        if (strcmp(printItem->name,"}") == 0) {
            scope-=1;
        }

        if (first == 1){
            /* Printing out leading tabs */
            int i;
            for (i = 0; i < scope; i++){
                fprintf(outputFile,"\t");
            }
            first = 0;
        }

        /* Go to the next line after it finds a key that would end a line */
        if (strcmp(printItem->name,";") == 0){
            fprintf(outputFile,"%s\n",printItem->name);
            first = 1;
            if (needCon){
                int i;
                for (i = 0; i < scope; i++){
                    fprintf(outputFile,"\t");
                }
                fprintf(outputFile,"con%s( &%s );\n",conName,varName);
                needCon = 0;
            }
        /* This key was put in place to handle comments, justs skips over and prints */
        } else if (strcmp(printItem->name,"\0") == 0) {
            printItem = printItem->nextItem;
            fprintf(outputFile,"%s\n",printItem->name);
            first = 1;
        /* We know that we are nesting, so we need to increase the indent */
        } else if (strcmp(printItem->name,"{") == 0) {
            fprintf(outputFile,"%s\n",printItem->name);
            first = 1;
            scope++;
        /* Thats the end of a block so we can lower the indent */
        } else if (strcmp(printItem->name,"}") == 0) {
            fprintf(outputFile,"%s\n",printItem->name);
            first = 1;
        /* When we find something that doesn't cause a newline handle it accordingly */
        } else {
            /*recognizing the declatation of a class, so we can switch it over to struct
              and add in the call to the proper constructor*/
            if (strcmp(printItem->name,"class") == 0){
                fprintf(outputFile,"struct ");
                /* Building up the constructer call line */
                conName = realloc(conName,sizeof(char) * (strlen(printItem->nextItem->name) + 1));
                strcpy(conName,printItem->nextItem->name);
                varName = realloc(varName,sizeof(char) * (strlen(printItem->nextItem->nextItem->name) + 1));
                strcpy(varName,printItem->nextItem->nextItem->name);
                /* Make sure there is actually a constructor to call */
                Class* currentClass = classes;
                while (currentClass != NULL){
                    if (strcmp(conName,currentClass->name) == 0) {
                        printf("Matched %s with %s\n",conName,currentClass->name);
                        break;
                    }
                    currentClass = currentClass->nextClass;
                }
                printf("Current name %s\n",currentClass->name);
                if (currentClass->constructor == 1){
                    needCon = 1;
                }
            } else if (noSpace(printItem->name)){
                fprintf(outputFile,"%s ",printItem->name);
            } else {
                fprintf(outputFile,"%s",printItem->name);
            }
        }

        printItem = printItem->nextItem;
    }
    free(conName);
    free(varName);
}

int noSpace(char* token){
    char* punctuation[] = {".",",",";",")","(","{","}","[","]","1","2","3","4","5","6","7","8","9","0"};
    if (isType(token,NULL)){
        return 1;
    }

    int i;
    for (i = 0; i < 19; i++){
        if (strcmp(token,punctuation[i])==0){
            return 0;
        }
    }

    return 1;
}

void printVariable(Variable* myVars, int indent, FILE* outputFile){
    Variable* tempVars = myVars;
    int i;
    for (i = 0; i < indent; i++) {
        fprintf(outputFile,"\t");
    }
    if (tempVars != NULL){
        if (tempVars->type != NULL){
            fprintf(outputFile,"%s ",tempVars->type);
        }
        if (tempVars->name != NULL){
            fprintf(outputFile,"%s ",tempVars->name);
        }
        if (tempVars->value != NULL){
            fprintf(outputFile,"%s",tempVars->value);
        }
    } else {
        printf("The Variable you tried to print was NULL\n");
    }
}

void deleteProgram(Prog* program){
    if (program != NULL){
        if (program->classes != NULL){
            deleteClass(program->classes);
        }
        if (program->functions != NULL){
            deleteFunction(program->functions);
        }
        if (program->globalVars != NULL){
            deleteVariable(program->globalVars);
        }
        if (program->prototype != NULL){
            deleteProto(program->prototype);
        }
        if (program->garbage != NULL){
            deleteList(program->garbage);
        }
        if (program->includes != NULL){
            deleteList(program->includes);
        }
    }
}

void deleteClass(Class* class){
    if (class->nextClass != NULL){
        deleteClass(class->nextClass);
    }
    if (class->localVars != NULL){
        deleteVariable(class->localVars);
    }
    if (class->localFuncs != NULL){
        deleteFunction(class->localFuncs);
    }
    free(class->name);
    class->nextClass = NULL;
    free(class);
}

void deleteFunction(Function* func){
    if (func->nextFunc != NULL){
        deleteFunction(func->nextFunc);
    }
    if (func->parameters != NULL){
        deleteVariable(func->parameters);
    }
    if (func->guts != NULL){
        deleteList(func->guts);
    }
    free(func->name);
    free(func->oldName);
    free(func->type);
    func->nextFunc = NULL;
    free(func);
}

void deleteProto(Function* func){
    if (func->nextFunc != NULL){
        deleteProto(func->nextFunc);
    }
    func->nextFunc = NULL;
    free(func);
}

void deleteVariable(Variable* var){
    if (var->nextVar != NULL){
        deleteVariable(var->nextVar);
    }
    var->nextVar = NULL;
    free(var->value);
    free(var->name);
    free(var->type);
    free(var);
}
