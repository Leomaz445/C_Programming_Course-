#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define START_LINE 100 /*The Program is loaded to memory address starting here*/
#define MAX_SIZE_INSTRUCTION 7
#define MAX_SIZE_LABEL 31
#define MAX_SIZE_LINE 82
#define NUMBER_OF_OP 16 /*There is 16 different commands*/
#define TYPE_MAX 7
#define LOCATION_MAX 7

#define RED "\033[1;31m" /*color red for the printf*/
#define REST "\033[0m" /*reset color for thr printf*/

/* This is a Block of the enum that is used in the program that helps it to be more understandable*/
enum Addressing {
    IMMEDIATELY, DIRECT, RELATIVE, REGISTER_DIRECT, EMPTY
};
enum paramFlag {
    FIRST_PARAM, SECOND_PARAM, NO_PARAM=-2
};

enum {
    FALSE=-1, TRUE
};
enum {
    FIRST_PASS,SECOND_PASS
};

typedef struct{ /* This struct represents a word in the assembly code */
    unsigned int val : 24;
}word;

/*This list contains all the details regarding a label, we also use this list to save the extern labels*/
typedef struct node* ptr;
typedef struct node{
    char name[MAX_SIZE_LABEL]; /*Name of the label*/
    int address; /*The address of the label*/
    char type[TYPE_MAX]; /*code,data,string*/
    char location[LOCATION_MAX]; /*extern,entry,zero*/
    ptr next;
}label;

/*This sturct help us to save the details of each param that is used in the program*/
typedef struct{
    char paramName[33]; /*the name or the label*/
    int addressing;/*the method we using*/
    int val;
}param;

/*All the name opcode number and the funct of the program*/
extern struct table{
    char *name;
    int opCode;
    int  funct;
} opCodeTable[NUMBER_OF_OP];

extern char *instruction[]; /*type of all the instruction in the program .data,.string,.extern.,.entry and empty*/
extern char *illegalName[];/*illegalNames are the names of the opcode and the instruction*/
extern char *error[];/*All the error outputs of the program are here*/
extern char *myRegister[]; /*The registers of the program r0,r1,r2,r3,r4,r5,r6,r7*/

/*These 3 variables are for the error output*/
char *fileName;
int lineNum;
int errorFlag;

/*List function that work with the list - add,print,free list*/
void addTwoList(label *,ptr *,int); /*it will and a new node to the list*/
void printList(label *head);/*Will print the list if needed*/
void freeList(ptr *head);/*Will free the list after each file*/
label* findLabel(char *,ptr *,int,char*);/*Will find if the label already existing*/
void copyNode(label*new,label*old);/*Will copy the given node to a allocated node*/
void reset(label *);/*Will reset the label to empty*/


/*Sitting the Word in assembly code*/
void setOpcode(word*, int); /*Will set the opcode of the word*/
void setAddressingSource(word*, int); /*Will set the addressing source of the code*/
void setSourceRegister(word*, int);/*Will set the source register code*/
void setAddressingDestination(word*, int);/*Will set the addressing destination*/
void setTargetRegister(word*, int); /*Will set the Target register*/
void SetFunct(word*, int);/*Will set the function number*/
void setARE(word*, int);/*Will set A-R-E of the word*/
void setNum(word*, int);/*Will insert the whole number to the all 24 bits*/
void set(word*, int,int,int);/*Will move the bites as needed*/
void setValue(word*, int);/*Entering the number as an immediately*/


/*Utility Function that helps analyze the code*/
int isRegister(char *);/*Will return if the param is register*/
int isOpCode(char *);/*Will return if the given name is an opcode*/
int isInstruction(char *);/*Will return if the given name is instruction*/
int isIllegalName(char *);/*Will return if the name of the label is an illegal name*/
int skipSpace(char *, int *);/*Will skip spaces and return an not empty char*/
int findComma(char *, int *);/*Will find if there is a comma in the right place*/
int findEnd(char *, int *);/*Will see if there any other command that should not be there*/
int validNumber(char *str, int *cnt);/*Check if number is valid number*/
int checkStatement(int,int ,int);/*Will check if the given assigned values of the parameter and the opcode match*/
char findChar(char *, int *);/*Will help us to find the char we looking for*/
void resetParam(param *);/*Will reset the param*/
void printError(int errorIndex);/*Printing the error of the program*/
int validBits(int num);/*Check if the bits are valid for the size of 24 bit word*/


/*SECOND PASS FUNCTION*/
/*Operation function that are checking and assigned the needed values*/
void buildWord(int,int,int,int,int,int,int,int,word*[]);/*Will use all the values to create a word*/
void buildVal(int,int,int,word *[]);/*Will use its values to build a number as binary*/
void countIC(int,int,int *);/*Function used in the first pass to count the created IC*/
void TwoParam(char *, int *, int, int , ptr *,ptr *,int *,word *[]);/*Getting two param opcode*/
void OneParam(char *, int *, int, int , ptr *,ptr *,int *,word *[]);/*Getting one param opcode*/
void ZeroParam(char *, int *, int, int , ptr *,ptr *,int *,word *[]);/*Getting zero param opcode*/
void getParameterName(char *, int *, char *);/*Get the parameter name*/

/*Main Function*/
int firstPass(FILE * ,ptr *);/*First pass to check all the errors*/
void secondPass(FILE *fd1,ptr *symbolList,char *name);/*Second pass to check all the error and build the image*/
void makeOutPutFiles(char * ,word *[],word *[],int *,int *,ptr *,ptr *);/*Build the output files*/
void openFiles(int argc, char *argv[]);/*Get the command*/