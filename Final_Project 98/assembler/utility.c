/*
 * This library contains a function used both by the first pass and the second pass the goal of
* This library is to help the first pass and the second pass analysis the line it's going through
 * @Leonid Mazarsky ID: 319401980
 * @21-08-202020 17:27
*/

#include "assembler.h"
#include <math.h>

#define NUMBER_OF_INSTRUCTION 5
#define NUMBER_OF_ILLIGAL_NAMES 21
#define NUMBER_OF_REGISTERS 8

/*Will find a legal char and return it or return false
 * @param str - pointer to a string that have the command user wrote,approved by Juddy Issac that its not const
 * @param cnt - pointer to the counter that works with the string
 * return fileChar - is the char we found or return false if we did not find anything*/
char findChar(char *str, int *cnt) {
    char fileChar;
    fileChar = *(str + *(cnt));
    /*while we did not get to the end*/
    while (fileChar != '\0' && fileChar != '\n') {
        if (isdigit(fileChar) || fileChar == ',' || isalpha(fileChar)) {
            *(cnt) = *(cnt) + 1;
            return fileChar;/*return the valid char*/
        }
        *(cnt) = *(cnt) + 1;
        fileChar = *(str + *(cnt)); /*move to the next char in the string*/
    }
    return (char) FALSE;/*did not find legal char return false*/
}

/*It will find the comma or else print an error message
 * @param str - pointer to a string that have the command user wrote.
 * @param cnt - pointer to  the counter that works with the string.
 * return TRUE if we found the comma or false if we didnt find him*/
int findComma(char *str, int *cnt) {
    char fileChar; /*will save the first legal char in the string*/
    fileChar = findChar(str, cnt);/*find the first legal char*/
    if (fileChar != ',' && fileChar != '\n') {
        printError(26);/*missing a comma*/

        return FALSE;
    }

    return TRUE;
}

/*It will find end are report if there is an illegal chars.
 * @param str - pointer to a string that have the command user wrote.
 * @param cnt - pointer to  the counter that works with the string.
 * return TRUE if we got to the end*/
int findEnd(char *str, int *cnt) {

    int fileChar = skipSpace(str, cnt);

    if (fileChar != '\0' && fileChar != 10) {
        printError(27);/*Extra test after end of command*/

        while (*(str + *(cnt)) != '\0') {
            *(cnt) = *(cnt) + 1;
        }
        return FALSE;
    }
    return TRUE;
}

/*It will count the needed IC to the IC counter
 * @param firstparam - the addressing method of the first param
 * @param secondpara - the addressing method of the second param.
 * @param IC - IC counter to add the needed spaces in the code
*/
void countIC(int firstParam, int secondParam, int *IC) {

    if (firstParam == IMMEDIATELY && secondParam == IMMEDIATELY)
        *IC = *IC + 3;
    if (firstParam == IMMEDIATELY && secondParam == DIRECT)
        *IC = *IC + 3;
    if (firstParam == IMMEDIATELY && secondParam == REGISTER_DIRECT)
        *IC = *IC + 2;
    if (firstParam == DIRECT && secondParam == IMMEDIATELY)
        *IC = *IC + 3;
    if (firstParam == DIRECT && secondParam == DIRECT)
        *IC = *IC + 3;
    if (firstParam == DIRECT && secondParam == REGISTER_DIRECT)
        *IC = *IC + 2;
    if (firstParam == REGISTER_DIRECT && secondParam == IMMEDIATELY)
        *IC = *IC + 2;
    if (firstParam == REGISTER_DIRECT && secondParam == DIRECT)
        *IC = *IC + 2;
    if (firstParam == REGISTER_DIRECT && secondParam == REGISTER_DIRECT)
        *IC = *IC + 1;

    /*For One Parameter*/
    if (firstParam == EMPTY && secondParam == DIRECT)
        *IC = *IC + 2;
    if (firstParam == EMPTY && secondParam == REGISTER_DIRECT)
        *IC = *IC + 1;
    if (firstParam == EMPTY && secondParam == RELATIVE)
        *IC = *IC + 2;
    if (firstParam == EMPTY && secondParam == IMMEDIATELY)
        *IC = *IC + 2;

    /*For Zero Parameter*/
    if (firstParam == EMPTY && secondParam == EMPTY)
        *IC = *IC + 1;
    if (firstParam == EMPTY && secondParam == FALSE)
        printError(39);/*probelm with the rts or stop command*/
}

/*Cheking if the addressing methods are legal it will return TRUE
 * @param opCode - the opcode of the command
 * @param firstparam - the addressing method of the first param
 * @param secondpara - the addressing method of the second param.
 * @return True if its legal addressing methods of both the operands.
*/

int checkStatement(int opCode, int firstParam, int secondParam) {
    int firstFlag = TRUE;
    int secondFlag = TRUE;

    switch (opCode) {
        case 0:
        case 2:
            if (firstParam == RELATIVE)
                firstFlag = FALSE;
            if (secondParam == RELATIVE || secondParam == IMMEDIATELY)
                secondFlag = FALSE;
            break;
        case 1:
            if (firstParam == RELATIVE)
                firstFlag = FALSE;
            if (secondParam == RELATIVE)
                secondFlag = FALSE;
            break;
        case 4:
            if (firstParam != DIRECT)
                firstFlag = FALSE;
            if (secondParam == IMMEDIATELY || secondParam == RELATIVE)
                secondFlag = FALSE;
            break;
        case 5:
            if (firstParam != EMPTY)
                firstFlag = FALSE;
            if (secondParam == IMMEDIATELY || secondParam == RELATIVE)
                secondFlag = FALSE;
            break;
        case 9:
            if (firstParam != EMPTY)
                firstFlag = FALSE;
            if (secondParam == IMMEDIATELY || secondParam == REGISTER_DIRECT)
                secondFlag = FALSE;
            break;
        case 12:
            if (firstParam != EMPTY)
                firstFlag = FALSE;
            if (secondParam == IMMEDIATELY || secondParam == RELATIVE)
                case 13:
                    if (firstParam != EMPTY)
                        firstFlag = FALSE;
            if (secondParam == RELATIVE)
                secondFlag = FALSE;
            break;
        case 14:
        case 15:
            if (firstParam != EMPTY)
                firstFlag = FALSE;
            if (secondParam != EMPTY)
                secondFlag = FALSE;
            break;
        default:
            printError(40);/*problem with the addressing methods*/
    }
    if (firstFlag == FALSE && secondFlag == TRUE) {
        printError(13);/*Invalid addressing mode for the first opernad*/
        return FALSE;
    }
    if (firstFlag == TRUE && secondFlag == FALSE) {
        printError(14);/*Invalid addressing mode for the second opernad*/
        return FALSE;
    }
    if (firstFlag == FALSE) {
        printError(15);/*Invalid addressing mode for the both opernad*/
        return FALSE;
    }

    return TRUE;


}

/*Cheking the number is valid number
 * @param opCode - the opcode of the command
 * @param firstparam - the addressing method of the first param
 * @param secondpara - the addressing method of the second param.
 * @return True if its legal addressing methods of both the operands.
*/
int validNumber(char *str, int *cnt) {
    int newNum; /*the number we will return*/
    int i = 0;
    char temp[12];/*the biggest unsigned integer that can be represented in 24 bites is 16,777,215*/
    int dotCounter = 0; /*counter for the dot in the expression if there one dot its not ligal */
    int plusCounter = 0;/*counter the + sign in the string more that one is not ligal*/
    int minusCounter = 0;/*counter of the - sign more that one in not ligal*/
    int fileChar = *(str + *cnt);

    if (fileChar == '-') { /*found a minus char*/
        minusCounter++;
        temp[i] = '-';
        i++;
        *cnt = *cnt + 1;
        fileChar = *(str + *cnt);
    }
    if (fileChar == '+') { /*found the plus char*/
        plusCounter++;
        temp[i] = '+';
        i++;
        *cnt = *cnt + 1;
        fileChar = *(str + *cnt);
    }
    if (fileChar == '.') { /*found a dot char */
        printError(16);/*illegal integer*/
        *cnt = *cnt + 1;
        return FALSE;
    }
    /*while we didnt got to the end of string or the end of the string and didnt see any space or comma
     * keep working*/

    while (fileChar != ',' && fileChar != ' ' && fileChar != '\0' && fileChar != '\n') {
        switch (fileChar) {
            case '.':
                if (++dotCounter == 1) {
                    printError(16);/*no dot allowed*/
                    return FALSE;
                }
                break;
            case '+':
                if (++plusCounter == 2) {
                    printError(16);/*only one plus is allowed*/
                    return FALSE;
                }
                break;

            case '-':
                if (++minusCounter == 1) {
                    printError(16);/*only one minus is allowed*/
                    return FALSE;
                }
                break;
            default:
                if (fileChar < '0' || fileChar > '9') {
                    printError(16);
                    return FALSE;
                }

        }
        temp[i] = *(str + *(cnt));/*if its valid number save it*/
        i++;
        fileChar = *(str + *cnt);
        *cnt = *cnt + 1;
    }
    temp[i] = '\0';
    newNum = atoi(temp);/*if we got to here the number is valid and covert him to double*/
    *cnt = *cnt - 1;
    if (newNum == FALSE) {
        return TRUE;
    }
    return newNum;
}

/*Prints a message of the error and changing the flag of the function
 * @param errorIndex - The error number
*/
void printError(int errorIndex) {

    if (errorFlag == TRUE)
        errorFlag = FALSE;/*fond an error so th files will not be created*/

    printf("In File: %s in Line: %d Error: %s ", fileName, lineNum, error[errorIndex]);


}

/*Return the insturction value
 * @param name - the name of the insturction
 * return the insturction number if true else return FALSE
*/
int isInstruction(char *name) {
    int i = 0;
    for (i = 0; i < NUMBER_OF_INSTRUCTION; i++) {
        if (strcmp(instruction[i], name) == 0) {
            return i;
        }
    }
    return FALSE;
}

/*Return the opcode number if its true
 * @param name - the name of the opcode
 * return the opcode number if true else return FALSE
*/
int isOpCode(char *name) {
    int i;
    for (i = 0; i < NUMBER_OF_OP; i++) {
        if (strcmp(opCodeTable[i].name, name) == 0) {
            return opCodeTable[i].opCode;
        }
    }
    return FALSE;
}

/*Return the if its a legal or illegal name
 * @param name - the name of the label
 * return the True if its legal name or false if its illegal name
*/
int isIllegalName(char *name) {
    int i;
    for (i = 0; i < NUMBER_OF_ILLIGAL_NAMES; i++) {
        if (strcmp(illegalName[i], name) == 0) {
            return TRUE;
        }
    }
    return FALSE;
}

/*Return the register number
 * @param name - the name of the register
 * return the register number if true else return FALSE
*/
int isRegister(char *name) {
    int i;
    for (i = 0; i < NUMBER_OF_REGISTERS; i++) {
        if (strcmp(myRegister[i], name) == 0) {
            return i;
        }
    }
    return FALSE;
}

/*reseting the param to empty
 * @param new - pointer to a param we want to reset
*/
void resetParam(param *new) {
    new->paramName[0] = '\0';
    new->addressing = EMPTY;
    new->val = 0;
}

/*Skipping all the white space
 * @param str - the string line
 * @param cnt - the counter that we moving with on the str line
 * return the first char that is not white space
*/
int skipSpace(char *str, int *cnt) {
    int fileChar = *(str + *cnt);

    if (fileChar == '\n')
        return fileChar;

    while (isspace(fileChar)) {
        *cnt = *cnt + 1;
        fileChar = *(str + *cnt);
    }
    return fileChar;
}

/*This function will help us to see that the number we enter is no to long to be save in 24
 * or 21 bites.
 * @param num - the number we want to put;
 * return 2 if its can be put only in 24 bit 21 if it can be put in the 21 bit and zero if its to big
*/
int validBits(int num) {
    int numBits;
    if (num == 0 || num == -1)
        numBits = 2;
    else /* Calculating, using log to base 2, the number of bits the number takes */
        numBits = ((num > 0) ? (int) (log(num) / log(2)) : (int) (log(-num - 1) / log(2))) + 2;

    return (numBits >= 0 && numBits <= 24) ? ((numBits <= 21) ? 2 : 1) : 0;
}
