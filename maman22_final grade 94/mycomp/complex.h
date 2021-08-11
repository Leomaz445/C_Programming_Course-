
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define COMMAND_SIZE_NAME 15 /*the max char in a command line that in the program*/
#define MAX_SIZE_INPUT 1000 /*max str size for the command user will input*/
#define RED "\033[1;31m" /*color red for the printf*/
#define REST "\033[0m" /*reset color for thr printf*/


enum boolean { /*boolean for reading better that program*/
    FALSE, TRUE, ABS, REAL, IMG, STOP, READ
};

typedef struct { /*the complex number struct in the program*/
    double rel;
    double im;
} comp;

typedef struct complexNumber { /*struct that save a name and a pointer to a complex number */
    char name;
    comp *ptr;
} numberPtr;

/*this function job is to give the final answer if its a good command it will be preformed else error message will
 *be printed and it will go back to ask for another command*/
void findCommand(char *);/*it will check if the command is ligal ,if true it will continue or print error message*/
void checkRead_comp(char *str, int *cnt);/*check if the read_comp iscommand  ligal*/
void checkPrint_comp(char *str, int *cnt);/*check if the print_comp is command ligal*/
void checkAdd_comp(char *str, int *cnt);/*check if the add_comp is command ligal*/
void checkSub_comp(char *str, int *cnt);/*check if the sub_comp is command ligal*/
void checkMult_comp_real(char *str, int *cnt);/*check if the mult_comp_real command is ligal*/
void checkMult_comp_img(char *str, int *cnt);/*check if the mult_comp_img command is ligal*/
void checkMult_comp_comp(char *str, int *cnt);/*check if the mult_comp_comp command is ligal*/
void checkAbs_comp(char *str, int *cnt);/*check if the abs_comp command is ligal*/
void checkStop(char *str, int *cnt);/*check if the stop command is ligal*/

/*this function hold the "struct" of each command line in the end if the struct is good it will return true*/
int checkPrintAbs(char *str, int *cnt,
                  numberPtr *x);/*It will check that the print_comp and abs_comp are written in a ligal way*/
int checkReadComp(char *str, int *cnt, numberPtr *x,
                  comp *newNumber);/*Will check that the read_comp is written in a ligal way*/
int checkAddSubMult(char *str, int *cnt, numberPtr *x,
                    numberPtr *y);/*Will check that the add_comp,sub_comp,mult_comp_comp is ligal*/
int checkMultCompScalar(char *str, int *cnt, numberPtr *x,
                        comp *newNumber);/*Will check if comp_mult_real and comp_mult img is ligal*/
int chStop(char *str, int *cnt);/*Will check that the end command is ligal*/

/*Function that Will analyze the string and look for a specific things or print an error message*/
int findComplexNumber(char *str, int *cnt, numberPtr *x);/*Will find the complex number or print error*/
int findComma(char *str, int *cnt);/*Will find the comma and or print error*/
int findNumber(char *str, int *cnt, comp *newNumber, int type);/*Will find a number user putted in the input*/
int findEnd(char *str, int *cnt);/*Will check if the end of the program is ligal*/

/*Function that help finding and analyzing the string and get the chars we looking for*/
int setVariableXY(numberPtr *x, char c);/*Will set the variables user putted in the input*/
double validNumber(char *str, int *cnt);/*Will check if the user input number is valid*/
char findComplex(char *str, int *cnt, numberPtr *x);/*Find the first complex number in the string and save it*/
char findChar(char *str, int *cnt);/*Find the next char in the string*/
void resetComp(int i, ...);/*It will reset the 6 complex number of the program*/


/*Complex Number Function that will preform action on them*/
void read_comp(numberPtr, double, double);/*put a value in a complex number*/
void print_comp(char [], comp, int, double);/*print complex number*/
void add_comp(numberPtr, numberPtr);/*add two complex number together*/
void sub_comp(numberPtr, numberPtr);/*sub two complex number*/
void mult_comp_comp(numberPtr, numberPtr);/* multiply two complex number together*/
void mult_comp_real(numberPtr, double);/*multiply  a complex number and a real number*/
void mult_comp_img(numberPtr, double);/*multiply  a complex number and a img number*/
void abs_comp(numberPtr);/*calculate the abs value of a given complex number*/
void stop(void);/*will exit the program and print goodbye message*/

/*Color function*/
void green();/*The color green*/
void reset();/*will reset the color back to regular*/
