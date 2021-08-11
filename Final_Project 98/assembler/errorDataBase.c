#include "assembler.h"

#define RED "\033[1;31m" /*color red for the printf*/
#define REST "\033[0m" /*reset color for thr printf*/


char *error[] = {
        RED"There was an error opening the file.\n"REST,/*0*/
        RED"Illegal label name - You can use only latters from A-Z and number from 0-9\n"REST,/*1*/
        RED"The name of the label is already in use\n"REST,/*2*/
        RED"You chose an illegal name for you label\n"REST,/*3*/
        RED"Illegal Comma,Please check your code\n"REST,/*4*/
        RED"After the & operand must come an label\n"REST,/*5*/
        RED"Missing source operand\n"REST,/*6*/
        RED"Missing target operand\n"REST,/*7*/
        RED"Missing source and target operands\n"REST,/*8 - NOT READY*/
        RED"Invalid instruction command\n"REST,/*9*/
        RED"Waring you have label before entry instruction\n"REST,/*10*/
        RED"After the Opcode you cant put comma\n"REST,/*11*/
        RED"Unexpected comma after .data instruction\n"REST,/*12*/
        RED"Invalid addressing mode for source operand.\n"REST,/*13*/
        RED"Invalid addressing mode for target operand.\n"REST,/*14*/
        RED"Invalid addressing mode for  source and target operand.\n"REST,/*15*/
        RED"Expected integer for .data instruction\n"REST,/*16*/
        RED"You have missed an comma after writing a data\n"REST,/*17*/
        RED"Double Comma\n"REST,/*18*/
        RED"String must be defined between quotation marks - missing left side\n"REST,/*19*/
        RED"The max Line Size is 80 chars\n"REST,/*20*/
        RED"Missing a name for the extern label\n"REST,/*21*/
        RED"The label name is too long\n"REST,/*22*/
        RED"Missing quotation on both sides\n"REST,/*23*/
        RED"String must be defined between quotation marks - missing right side\n"REST,/*24*/
        RED"Your are missing an opernad ind the opCode command\n"REST,/*25*/
        RED"Your are missing a comma\n"REST,/*26*/
        RED"You entered an extra text \n"REST,/*27*/
        RED"First latter should start with the ABC  \n"REST,/*28*/
        RED"Illegal Opcode\n"REST,/*29*/
        RED"Please Write a data after a comma\n"REST,/*30*/
        RED"Label not found\n"REST,/*31*/
        RED"Illegal String\n"REST,/*32*/
        RED"Name of the label can only start with an a letter\n"REST,/*33*/
        RED"Illegal label\n"REST,/*34*/
        RED"You should put the ':' close to the label name\n"REST,/*35*/
        RED"Illegal source operand\n"REST,/*36*/
        RED"Illegal target operand\n"REST,/*37*/
        RED"There is an empty label\n"REST,/*38*/
        RED"Error with the rst or end command\n"REST,/*39*/
        RED"There are problem with the addressing methods\n"REST,/*40*/
        RED"Error allocating memory for the fileName\n"REST,/*41*/
        RED"Error allocating memory for the Data table \n"REST,/*42*/
        RED"Error allocating memory for the Instruction table \n"REST,/*43*/
        RED"The number is overflowing or underflowing\n"REST,/*44*/
        RED"\nThere was a problem to allocate memory for the symbol List\n"REST,/*45*/
        RED"\nThe Label name is already in use\n"REST,/*46*/
        RED"\nPlease enter a file\n"REST,/*47*/
};

