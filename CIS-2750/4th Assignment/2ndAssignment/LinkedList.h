#ifndef _ICROSS_LINKEDLIST_
#define _ICROSS_LINKEDLIST_

typedef struct item{
    char* name;
    struct item* nextItem;
    struct item* prevItem;
}Item;

typedef struct list{
    Item* head;
    struct list* nextList;
}List;

typedef struct variable{
    char* type;
    char* name;
    char* value;
    struct variable* nextVar;
}Variable;

typedef struct function{
    char* name;
    char* oldName;
    char* type;
    Variable* parameters;
    Variable* localVars;
    List* guts;
    int classVar;
    struct function* nextFunc;
}Function;

typedef struct class{
    char* name;
    Variable* localVars;
    Function* localFuncs;
    int constructor;
    struct class* nextClass;
}Class;

typedef struct program{
    Variable* globalVars;
    Function* functions;
    Class* classes;
    List* garbage;
    Function* prototype;
    List* includes;
    List* types;
    struct program* nextProgram;
}Prog;

/*************
*Function Name:
*Function Description:
*Parameters In: N/A
*Parameters output: N/A
*Errors: N/A
*************/
List* createList();

/*************
*Function Name:
*Function Description:
*Parameters In: N/A
*Parameters output: N/A
*Errors: N/A
*************/
Item* createItem(char* data);

/*************
*Function Name:
*Function Description:
*Parameters In: N/A
*Parameters output: N/A
*Errors: N/A
*************/
List* addItem(List* list, char* data);

/*************
*Function Name:
*Function Description:
*Parameters In: N/A
*Parameters output: N/A
*Errors: N/A
*************/
void deleteList(List* list);

/*************
*Function Name:
*Function Description:
*Parameters In: N/A
*Parameters output: N/A
*Errors: N/A
*************/
void deleteItems(Item* item);

/*************
*Function Name:
*Function Description:
*Parameters In: N/A
*Parameters output: N/A
*Errors: N/A
*************/
void printList(List* theList, FILE* outputFile);

/*************
*Function Name:
*Function Description:
*Parameters In: N/A
*Parameters output: N/A
*Errors: N/A
*************/
List* addItemFront(List* list, char* data);

/*************
*Function Name:
*Function Description:
*Parameters In: N/A
*Parameters output: N/A
*Errors: N/A
*************/
List* removeItemFront(List* list);

/*************
*Function Name:
*Function Description:
*Parameters In: N/A
*Parameters output: N/A
*Errors: N/A
*************/
List* removeItemBack(List* list);

/*************
*Function Name:
*Function Description:
*Parameters In: N/A
*Parameters output: N/A
*Errors: N/A
*************/
Prog* createProgram(List* data);

/*************
*Function Name:
*Function Description:
*Parameters In: N/A
*Parameters output: N/A
*Errors: N/A
*************/
Class* createClass(Item* data, int links);

/*************
*Function Name:
*Function Description:
*Parameters In: N/A
*Parameters output: N/A
*Errors: N/A
*************/
Function* createFunction(Item* data, int links);

/*************
*Function Name:
*Function Description:
*Parameters In: N/A
*Parameters output: N/A
*Errors: N/A
*************/
Function* createPrototype(Function* func);

/*************
*Function Name:
*Function Description:
*Parameters In: N/A
*Parameters output: N/A
*Errors: N/A
*************/
Variable* createVariable(Item* data, int links);

/*************
*Function Name:
*Function Description:
*Parameters In: N/A
*Parameters output: N/A
*Errors: N/A
*************/
Class* addClass(Class* classList, Item* data, int links);

/*************
*Function Name:
*Function Description:
*Parameters In: N/A
*Parameters output: N/A
*Errors: N/A
*************/
Function* addFunction(Function* funcList, Item* data, int links);

/*************
*Function Name:
*Function Description:
*Parameters In: N/A
*Parameters output: N/A
*Errors: N/A
*************/
Function* addPrototype(Function* funcList, Function* func);

/*************
*Function Name:
*Function Description:
*Parameters In: N/A
*Parameters output: N/A
*Errors: N/A
*************/
Variable* addVariable(Variable* varList, Item* data, int links);

/*************
*Function Name:
*Function Description:
*Parameters In: N/A
*Parameters output: N/A
*Errors: N/A
*************/
int isType(char* data, char* newType);

/*************
*Function Name:
*Function Description:
*Parameters In: N/A
*Parameters output: N/A
*Errors: N/A
*************/
void printProgram(Prog* myProgram, FILE* outputFile);

/*************
*Function Name:
*Function Description:
*Parameters In: N/A
*Parameters output: N/A
*Errors: N/A
*************/
Prog* analyze(Prog* myProgram);

/*************
*Function Name:
*Function Description:
*Parameters In: N/A
*Parameters output: N/A
*Errors: N/A
*************/
int isClassVar(char* name, Variable* classVars);

/*************
*Function Name:
*Function Description:
*Parameters In: N/A
*Parameters output: N/A
*Errors: N/A
*************/
int isLocalVar(char* name, List* localVars);

/*************
*Function Name:
*Function Description:
*Parameters In: N/A
*Parameters output: N/A
*Errors: N/A
*************/
Function* classReference(Function* theFunc, Class* classes, Class* thisClass);

/*************
*Function Name:
*Function Description:
*Parameters In: N/A
*Parameters output: N/A
*Errors: N/A
*************/
void printClass(Class* myClass, FILE* outputFile);

/*************
*Function Name:
*Function Description:
*Parameters In: N/A
*Parameters output: N/A
*Errors: N/A
*************/
Class* renameFuncs(Class* parent);

/*************
*Function Name:
*Function Description:
*Parameters In: N/A
*Parameters output: N/A
*Errors: N/A
*************/
Class* createConstructor(Class* parent);

/*************
*Function Name:
*Function Description:
*Parameters In: N/A
*Parameters output: N/A
*Errors: N/A
*************/
void printFunction(Function* myFunc , int indent, FILE* outputFile, Class* classes);

/*************
*Function Name:
*Function Description:
*Parameters In: N/A
*Parameters output: N/A
*Errors: N/A
*************/
void printAsFunc(List* theList, int indent, FILE* outputFile, Class* classes);

int noSpace(char* token);

/*************
*Function Name:
*Function Description:
*Parameters In: N/A
*Parameters output: N/A
*Errors: N/A
*************/
void printVariable(Variable* myVars, int indent, FILE* outputFile);

/*************
*Function Name:
*Function Description:
*Parameters In: N/A
*Parameters output: N/A
*Errors: N/A
*************/
void deleteProgram(Prog* program);

/*************
*Function Name:
*Function Description:
*Parameters In: N/A
*Parameters output: N/A
*Errors: N/A
*************/
void deleteClass(Class* class);

/*************
*Function Name:
*Function Description:
*Parameters In: N/A
*Parameters output: N/A
*Errors: N/A
*************/
void deleteFunction(Function* func);

/*************
*Function Name:
*Function Description:
*Parameters In: N/A
*Parameters output: N/A
*Errors: N/A
*************/
void deleteProto(Function* func);

/*************
*Function Name:
*Function Description:
*Parameters In: N/A
*Parameters output: N/A
*Errors: N/A
*************/
void deleteVariable(Variable* var);

#endif
