#include "assembler.h"
/*
 * This librery will help us mange the list we using the program all related lists operation are here.
 * operation like add a node to a list, print list, free list etc.
 * @Leonid Mazarsky ID: 319401980
 * @21-08-202020 17:27
*/

/*Will copy a data from an old label to a new label.
 * @param new - param to the new label we want to copy to
 * @param old -the old label we copy from.
*/
void copyNode(label *new, label *old) {
    strcpy(new->name, old->name);
    strcpy(new->type, old->type);
    strcpy(new->location, old->location);
    new->address = old->address;
}
/*Reset the label to an empty.
 * @param new - pointer to a list we want to reset
*/
void reset(label *new) {
    strcpy(new->name, "NULL");
    strcpy(new->type, "NULL");
    strcpy(new->location, "NULL");
    new->address = 0;
}
/*If the label name is not already in use we will add it
 * @param new - the label we want to add
 * @param hptr - pointer to the head of the list we want to add to
 * @param index - to know if its a first pass or a second pass of the codes
*/
void addTwoList(label *new, ptr *hptr, int index) {
    ptr p1, p2, newLabel;

    newLabel = (ptr) malloc(sizeof(label));
    if (!newLabel) {
        printError(45);/*error allocate memory*/
    } else {
        reset(newLabel);
        copyNode(newLabel, new);
        if (!(*hptr)) { /*place the new node at the top of the list*/
            newLabel->next = NULL;
            *hptr = newLabel;
            return;
        }
        p1 = *hptr;
        while ((p1)) { /*if its the first pass check if the name alredy in use*/
            if (index == FIRST_PASS) {
                if (strcmp(p1->name, (new->name)) == 0) {
                    printError(46);/*The name is already in use*/
                }
            }
            /*this way we moving to the end of list*/
            p2 = p1;
            p1 = p1->next;
        }
/*adding a new node to the list*/
        newLabel->next = p1;
        p2->next = newLabel;
    }
}
/*This function will find the label and return its pointer to her
 * @param name - name of the label
 * @param hptr - the list we want to check
 * @param index - to know if its a first pass or a second pass of the codes
 * @param type - if its the second pass we wand to save the label type
 * return label - a pointer to a label we found or NULL
*/
label *findLabel(char *name, ptr *hptr, int index, char *type) {
    ptr p1 = *hptr;
    while (p1) {
        if (index == FIRST_PASS) {
            if (strcmp(p1->name, name) == 0) { /*if its the first pass we want to find if its already in use*/
                return p1;
            }
        }
        if (index == SECOND_PASS) /*we want to find the label to save its type - extern or entry*/
            if (strcmp(p1->name, name) == 0) {
                strcpy(p1->location, type);
                return p1;
            }
        p1 = p1->next;
    }
    return NULL;
}

void printList(label *head) {

    while (head !=NULL) {
        printf("\nThe name: %s  ", head->name);
        printf("The address: %d  ",  head->address);
        printf("The location: %s   ", head->location);
        printf("The type: %s   ",  head->type);
        head =  head->next;
    }
}
/*This function will get the list and free all the memory
 * @param head- first node of the list
*/

void freeList(ptr *head) {
    ptr temp;
    while (*head) {
        temp = *head;
        *head = temp->next;
        free(temp);
    }
}
