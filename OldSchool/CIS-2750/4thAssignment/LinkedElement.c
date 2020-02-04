#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedElement.h"

/*************
 *Function Name: createElement()
 *Function Description: this function will take in all the needed information of that type
 *Parameters In: (Type enum) describing the html type, (char*) a string to be used in a element description x 4
 *Parameters output: (Element struct) The newly assembled element
 *Errors: if the data is recieved incorrectly it will return NULL
 *************/
Element * createElement(Type type, char* field1, char* field2, char* field3, char* field4){
    Element * newElement = NULL;

    /* Alocate space and quit out if it fails */
    newElement = malloc(sizeof(Element));
    if (newElement == NULL) {
        printf("I'm sorry there wasn't enough room to create the new Element\n");
        return newElement;
    }

    /* Init values */
    newElement->name = NULL;
    newElement->link = NULL;
    newElement->exe = NULL;
    newElement->size = NULL;
    newElement->text = NULL;
    newElement->value = NULL;
    newElement->action = NULL;
    newElement->image = NULL;
    newElement->file = NULL;


    /* Based of the given type, allocate space for an element */
    switch (type) {
        case button:
            newElement->name = malloc(sizeof(char) * strlen(field1) + 1);
            newElement->link = malloc(sizeof(char) * strlen(field2) + 1);
            break;
        case horLine:

        break;
        case executable:
            newElement->exe = malloc(sizeof(char) * strlen(field1) + 1);
            break;
        case heading:
            newElement->size = malloc(sizeof(char) * strlen(field1) + 1);
            break;
        case input:
            newElement->action = malloc(sizeof(char) * strlen(field1) + 1);
            newElement->text = malloc(sizeof(char) * strlen(field2) + 1);
            newElement->name = malloc(sizeof(char) * strlen(field3) + 1);
            newElement->value = malloc(sizeof(char) * strlen(field4) + 1);
            break;
        case link:
            newElement->text = malloc(sizeof(char) * strlen(field1) + 1);
            newElement->link = malloc(sizeof(char) * strlen(field2) + 1);
            break;
        case picture:
            newElement->image = malloc(sizeof(char) * strlen(field1) + 1);
            newElement->size = malloc(sizeof(char) * strlen(field2) + 1);
            break;
        case radio:
            newElement->action = malloc(sizeof(char) * strlen(field1) + 1);
            newElement->name = malloc(sizeof(char) * strlen(field1) + 1);
            newElement->value = malloc(sizeof(char) * strlen(field1) + 1);
            break;
        case text:
            if (field1 != NULL) newElement->text = malloc(sizeof(char) * strlen(field1) + 1);
            else newElement->file = malloc(sizeof(char) * strlen(field2) + 1);
            break;
        case dropdown:
            /* Figure this one out */
        break;
    }

    return newElement;
}

/*************
 *Function Name: destroyElement()
 *Function Description: cleans up the memory of the given element
 *Parameters In: (Element struct) The element to delete
 *Parameters output: N/A
 *Errors: N/A
 *************/
void destroyElement(Element* todestroy){
    /* Finding the correct data in the struct and setting it free */
    if (todestroy->name != NULL){
        free(todestroy->name);
    }
    if (todestroy->link != NULL){
        free(todestroy->link);
    }
    if (todestroy->exe != NULL){
        free(todestroy->exe);
    }
    if (todestroy->size != NULL){
        free(todestroy->size);
    }
    if (todestroy->text != NULL){
        free(todestroy->text);
    }
    if (todestroy->value != NULL){
        free(todestroy->value);
    }
    if (todestroy->action != NULL){
        free(todestroy->action);
    }
    if (todestroy->image != NULL){
        free(todestroy->image);
    }
    if (todestroy->file != NULL){
        free(todestroy->file);
    }
    /* free the struct itself */
    free(todestroy);
}

/*************
 *Function Name: addElement()
 *Function Description: Takes in the given element and adds it the the list
 *Parameters In: (Element struct) The list to add to (Element struct) the element to add to the list
 *Parameters output: (Element struct) the newly appended list
 *Errors: N/A
 *************/
Element * addElement(Element* list, Element* newElement){
    Element * page = list;

    /* Add tothe head of the list if the list is empty */
    if (page == NULL){
        list = newElement;
    } else {
        /* Otherwaise move to the back of the list and add it there */
        while (page->nextElement != NULL){
            page = page->nextElement;
        }
        page->nextElement = newElement;
    }
    return list;
}

/*************
 *Function Name: removeElement()
 *Function Description: takes in the given element, searches for it in the list
  and removes it from the list.
 *Parameters In: (Element struct) The list containing the element (Element struct) The element to delete
 *Parameters output: (Element struct) the newly edited list
 *Errors: N/A
 *************/
Element * removeElement(Element* list, Element* toRemove){
    Element* page = list;
    Element* tempElement;

    /* Make sure there is a list */
    if (page == NULL) return NULL;

    /* Move through the list */
    while (page->nextElement != NULL) {
        /* Find the item to remove */
        if (equals(page->nextElement,toRemove)){
            /* Remove it and call something to deal with the memory */
            tempElement = page->nextElement;
            page->nextElement = page->nextElement->nextElement;
            destroyElement(tempElement);
            break;
        }
        page = page->nextElement;
    }
    return list;
}

/*************
 *Function Name: equals()
 *Function Description: Compares two elements and tests if they are equal
 *Parameters In: (Element struct) The first element to compare (Element struct) The second element to compare
 *Parameters output: (int) a success flag, 1 if equal, 0 otherwise
 *Errors: N/A
 *************/
 int equals(Element* first, Element* second){
     /* Check if they are different sizes */
     if (sizeof(first) == sizeof(second)){
         /* If there is data check to see if it matches */
         if (first->name != NULL && second->name != NULL){
             if (strcmp(first->name,second->name) == 0) return 1;
         }
         if (first->link != NULL && second->link != NULL){
             if (strcmp(first->link,second->link) == 0) return 1;
         }
         if (first->exe != NULL && second->exe != NULL){
             if (strcmp(first->exe,second->exe) == 0) return 1;
         }
         if (first->size != NULL && second->size != NULL){
             if (strcmp(first->size,second->size) == 0) return 1;
         }
         if (first->text != NULL && second->text != NULL){
             if (strcmp(first->text,second->text) == 0) return 1;
         }
         if (first->value != NULL && second->value != NULL){
             if (strcmp(first->value,second->value) == 0) return 1;
         }
         if (first->action != NULL && second->action != NULL){
             if (strcmp(first->action,second->action) == 0) return 1;
         }
         if (first->image != NULL && second->image != NULL){
             if (strcmp(first->image,second->image) == 0) return 1;
         }
         if (first->file != NULL && second->file != NULL){
             if (strcmp(first->file,second->file) == 0) return 1;
         }
     }
     return 0;
 }
