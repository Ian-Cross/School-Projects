#ifndef __icross__a3__
#define  __icross__a3__

typedef enum type {button,horLine,executable,heading,input,link,picture,radio,text,dropdown} Type;

typedef struct element {
    Type type;
    char* name;
    char* link;
    char* exe;
    char* size;
    char* text;
    char* value;
    char* action;
    char* image;
    char* file;
    struct element * nextElement;
} Element;

/*************
 *Function Name: createElement()
 *Function Description: this function will take in all the needed information of that type
 *Parameters In: (Type enum) describing the html type, (char*) a string to be used in a element description x 4
 *Parameters output: (Element struct) The newly assembled element
 *Errors: if the data is recieved incorrectly it will return NULL
 *************/
Element * createElement(Type type, char* field1, char* field2, char* field3, char* field4);

/*************
 *Function Name: destroyElement()
 *Function Description: cleans up the memory of the given element
 *Parameters In: (Element struct) The element to delete
 *Parameters output: N/A
 *Errors: N/A
 *************/
void destroyElement(Element* todestroy);

/*************
 *Function Name: addElement()
 *Function Description: Takes in the given element and adds it the the list
 *Parameters In: (Element struct) The list to add to (Element struct) the element to add to the list
 *Parameters output: (Element struct) the newly appended list
 *Errors: N/A
 *************/
Element * addElement(Element* list, Element* newElement);

/*************
 *Function Name: removeElement()
 *Function Description: takes in the given element, searches for it in the list
  and removes it from the list.
 *Parameters In: (Element struct) The list containing the element (Element struct) The element to delete
 *Parameters output: (Element struct) the newly edited list
 *Errors: N/A
 *************/
Element * removeElement(Element* list, Element* toRemove);

/*************
 *Function Name: equals()
 *Function Description: Compares two elements and tests if they are equal
 *Parameters In: (Element struct) The first element to compare (Element struct) The second element to compare
 *Parameters output: (int) a success flag, 1 if equal, 0 otherwise
 *Errors: N/A
 *************/
 int equals(Element* first, Element* second);



#endif
