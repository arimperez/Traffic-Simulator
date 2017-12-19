/**
 * @file LinkedListAPI.h
 *

 */


#include <stdio.h>
#include <stdlib.h>
#include "Car.h"

/**
*Node of a linked list. This list is doubly linked, meaning that it has points to both the node immediately in front
of it, as well as the node immediately behind it.
**/
typedef struct listNode{
    void *data;
    struct listNode *previous;
    struct listNode *next;
} Node;

/**
 *Dummy head of the list. Contains no actual data on it beyond a pointer to the front and end of the list.
 **/
typedef struct listHead{
    Node *head;
    Node *tail;
    void (*deleteNode)(void *toBeDeleted);
    int (*compare)(const void *first,const void *second);
    void (*printNode)(void *toBePrinted);
} List;

/**Function to point the list head to the appropriate functions. Allocates memory to the struct.
*@return pointer to the list head
*@param printFunction function pointer to print a single node of the list
*@param deleteFunction function pointer to delete a single piece of data from the list
*@param compareFunction function pointer to compare two nodes of the list in order to test for equality or order
**/
List *initializeList(void (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first,const void *second))
{
    List* new = malloc(sizeof(List));

    //new->head = malloc(sizeof(Node));
    //new->tail = malloc(sizeof(Node));
    new->head = NULL;
    new->tail = NULL;

    new->deleteNode = deleteFunction;
    new->compare = compareFunction;
    new->printNode = printFunction;

    return (new);

}
/**Function for creating a node for a linked list. This node contains generic data and may be connected to
other notes in a list.
*@pre data should be of same size of void pointer on the users machine to avoid size conflicts. data must be valid.
*data must be cast to void pointer before being added.
*@post data is valid to be added to a linked list
*@return On success returns a node that can be added to a linked list. On failure, returns NULL.
*@param data - is a generic pointer to any data type.
**/
Node *initializeNode(void *data)
{
    Node *new = malloc(sizeof(Node));
    new->data = data;
    new->previous = NULL;
    new->next = NULL;

    return (new);

}

/**Inserts a Node to the front of a linked list. The list then updates accordingly to adhere to the ADT.
*@pre 'List' type must exist and be used in order to keep track of the linked list.
*@param list pointer to the dummy head of the list
*@param toBeAdded a pointer to data that is to be added to the linked list
**/
void insertFront(List *list, void *toBeAdded)
{
    Node *temp = initializeNode(toBeAdded);//(Node *)toBeAdded;

    /////temp->next = list->head;
    ////temp->previous = NULL;

    if (list->head != NULL) {
        temp->next = list->head;
        temp->previous = NULL;

        list->head->previous = temp;

        list->head = temp;
    }
    if (list->head == NULL && list->tail == NULL) {
        list->head = temp;
        list->tail = temp;
    }
    list->head = temp;
    /////list->head = temp;
    //list->head->data = temp->data;


    /*if (list->tail == NULL) {
        list->tail
    }*/

    return;

}

/**Inserts a Node to the back of a linked list. The list then updates accordingly to adhere to the ADT.
*@pre 'List' type must exist and be used in order to keep track of the linked list.
*@param list pointer to the dummy head of the list
*@param toBeAdded a pointer to data that is to be added to the linked list
**/
void insertBack(List *list, void *toBeAdded)
{

    Node *temp = initializeNode(toBeAdded);//(Node *)toBeAdded;

    temp->previous = list->tail;
    temp->next = NULL;

    if (list->tail != NULL) {
        list->tail->next = temp;
    }
    if (list->head == NULL && list->tail == NULL) {
        list->head = temp;
        list->tail = temp;
    }

    list->tail = temp;

    /*
    Node *temp = (Node *)toBeAdded;
    temp->previous = list->tail;

    list->tail->next = temp;
    list->tail = temp;
    */

    return;
}

/** Deletes the entire linked list head to tail, starting with the nodes, followed by the list itself.
*@pre 'List' type must exist and be used in order to keep track of the linked list.
*@param list pointer to the List-type dummy node
**/
void deleteList(List *list)
{
    Node *curr = list->head;//->next;
    while (curr != NULL) {
        //if (curr != NULL) {
        list->deleteNode(curr->data);


            //deleteNodeFromList(list, curr);
        //}
        curr = curr->next;
        if (curr != NULL){
            free(curr->previous);
        }

        //curr->previous = NULL;

        //free(curr->previous);
    }

    if (list->head == NULL || list->tail == NULL){

        free(list->head);
        //free(list->tail); // TA comented out
    }

    free(list);
    //free(curr);
}

/** Uses the comparison function in the List struct to place the element in the appropriate position in the list.
*this is intended to be used from the beginning in order to keep the list completely sorted.
*@pre List exists and has memory allocated to it. Node to be added is valid.
*@post The node to be added will be placed immediately before or after the first occurrence of a related node
*@param list a pointer to the dummy head of the list containing function pointers for delete and compare, as well
as a pointer to the first and last element of the list.
*@param toBeAdded a pointer to data that is to be added to the linked list
**/
void insertSorted(List *list, void *toBeAdded)
{


    Node *curr = list->head;
    if (curr == NULL)
    {
        //printf("First Element!\n");
        insertFront(list, toBeAdded);
        //if (list->head->data != NULL)
        //{
        //    printCar(list->head->data);
        //}
        return;
    }
    Node *add = initializeNode(toBeAdded);
    while (curr != NULL) {
        /*
        if (list->)
        {
            insertFront(list, toBeAdded);
        }*/
        if (list->compare(add->data, curr->data) <= 0) {
            //printf("Found spot!\n");
            if (list->head == curr) {
                insertFront(list, toBeAdded);
                free(add);
                return;
            }

            else
            {
                add->next = curr->next;
                add->previous = curr;

                curr->next->previous = add;
                curr->previous->next = add;
                return;
            }

        }
        curr = curr->next;
    }

    insertBack(list, toBeAdded);
    free(add);
    return;
}

/**Function to remove a node from the list and alter the pointers accordingly to not disrupt the order of the
 *data structure.
 *@pre List must exist and have memory allocated to it
 *@post toBeDeleted will have its memory freed if it exists in the list.
 *@param list pointer to the dummy head of the list containing deleteFunction function pointer
 *@param toBeDeleted pointer to data that is to be removed from the list
 *@return returns EXIT_SUCCESS on success, and EXIT_FAILURE when empty. Returns -1 when the node cannot be found.
 **/
int deleteNodeFromList(List *list, void *toBeDeleted)
{

    Node *curr = list->head;

    //Node *del = (Node *)toBeDeleted;

    if (curr == NULL) {
        return (EXIT_FAILURE);
    }

    //If array list only has one element
    if (list->head == list->tail)
    {
        //printf("Last element\n");
        list->deleteNode(curr->data);
        free(curr);
        list->head = NULL;
        list->tail = NULL;
        return (EXIT_SUCCESS);
    }
    while (curr != NULL) {
        if (curr->data == toBeDeleted)
        {

            /*printf("from the head---------\n");
            if (list->head == curr) {
                //list->deleteNode(toBeDeleted);
                Node *temp = curr->next;
                list->deleteNode(toBeDeleted);
                free(curr);
                list->head = temp;
                list->head->previous = NULL;




                return (EXIT_SUCCESS);


            }

            else {*/


            if (curr == list->head){
                Node *temp = curr->next;
                list->deleteNode(toBeDeleted);
                //free(curr);
                list->head = temp;//->next;
                temp->previous = list->head;
                //curr->next->previous = list->head;

            }

            else {
                curr->previous->next = curr->next;
                curr->next->previous = curr->previous;

                list->deleteNode(curr->data);
                free(curr);
            }

            return (EXIT_SUCCESS);
            //}
        }

        else {
          curr = curr->next;
        }
      /*
        curr = curr->next;
        if (curr->previous == del) {
            curr->previous->next = curr->next;
            curr->next->previous = curr->previous;

            //Changed this from (tobeDeleted)
            list->deleteNode(curr->previous->data);
            free(toBeDeleted);
            return (EXIT_SUCCESS);
        }*/
    }

    return -1;


}

/**Function to return the data at the front of the list.
 *@pre The list exists and has memory allocated to it
 *@param list pointer to the dummy head of the list containing the head of the list
 *@return pointer to the data located at the head of the list
 **/
void *getFromFront(List *list)
{
    return(list->head);
}

/**Function to return the data at the back of the list.
 *@pre The list exists and has memory allocated to it
 *@param list pointer to the dummy head of the list containing the tail of the list
 *@return pointer to the data located at the tail of the list
 **/
void *getFromBack(List *list)
{
    return(list->tail);
}

/**Function to print list from head to tail. This will utilize the list's printNode function pointer to print.
 *@pre List must exist, but does not have to have elements.
 *@param list Pointer to linked list dummy head.
 **/
void printForward(List *list)
{

    Node *curr = list->head;


    //printf("HEAD: %c\n", getGoingDirec(list->head->data));
    while (curr != NULL) {

        //printf("Working hard! %c\n", getFromDirec(curr->data));
        if (curr->data != NULL){


            list->printNode(curr->data);
            curr = curr->next;
            printf("\n");
        }
    }

    //free(curr);

    return;
}

/**Function to print list from tail to head. This will utilize the list's printNode function pointer to print.
 *@pre List must exist, but does not have to have elements.
 *@param list Pointer to linked list dummy head.
 **/
void printBackwards(List *list)
{

    Node *curr = list->tail;
    while (curr != NULL) {
        list->printNode(curr->data);
        curr = curr->previous;
        printf("\n");
    }

    return;
}


/**User defined function to delete linked list node based on the incoming data.
 *@pre Data must not already be freed or NULL
 *@param toBeDeleted Pointer to generic data to be deleted in the list.
 **/
void deleteListNode(void *toBeDeleted)
{
    return;
}

/**
 *User-defined comparison for two pointers to generic data. Must define an element of these pointers to use to compare
 *the two pointers with each other.
 *@pre first and second must be comparable.
 *@param first pointer to data to be compared with second.
 *@param second pointer to data to be compared with first.
 *@return for sorting purposes,
 *<0 The element pointed by 'first' goes before the element pointed by 'second'
 *0  The element pointed by 'first' is equivalent to the element pointed by 'second'
 *>0 The element pointed by 'first' goes after the element pointed by 'second'
 **/
int compare(const void *first,const void *second)
{
    return 0;
}

/**User defined function to print an element of the list.
 *@pre Data must be able to be printed via a standard print function
 *@param toBePrinted pointer to the data that is to be printed. Taken from a data structure.
 **
void printNode(void *toBePrinted)
{
    return;

}*/
