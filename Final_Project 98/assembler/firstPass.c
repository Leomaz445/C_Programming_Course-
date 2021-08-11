/*
 * This if First Pass - We going throw all the given code in the file and look for any syntax error
 * or our assembly related rules if  there is no errors we will not continue to the second pass.
 * another goal in this pass is to count the instruction and the data given by the user and create
 * the symbol table of all the label used in the code and there addresses.
 * @Leonid Mazarsky ID: 319401980
 * @21-08-202020 17:27
*/

#include "firstPass.h"

/*Will save the instruction type of the code*/
char *instruction[] = {"data", "string", "entry", "extern", "code", "noSymb"};

/*Will save the illegal labels name of the code*/
char *illegalName[] = {
        "mov", "cmp", "add", "sub", "lea", "clr", "not", "inc",
        "dec", "jmp", "bne", "red", "prn", "jsr", "rts", "stop",
        "data", "string", "extern", "entry", "code"
};

/*The registers of the code*/
char *myRegister[] = {
        "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"
};

/*The full opcode table of the program*/
struct table opCodeTable[] = {
        {"mov",  0,  0},/*0*/
        {"cmp",  1,  0},/*1*/
        {"add",  2,  1},/*2*/
        {"sub",  2,  2},/*3*/
        {"lea",  4,  0},/*4*/
        {"clr",  5,  1},/*5*/
        {"not",  5,  2},/*6*/
        {"inc",  5,  3},/*7*/
        {"dec",  5,  4},/*8*/
        {"jmp",  9,  1},/*9*/
        {"bne",  9,  2},/*10*/
        {"jsr",  9,  3},/*11*/
        {"red",  12, 3},/*12*/
        {"prn",  13, 0},/*13*/
        {"rts",  14, 0},/*14*/
        {"stop", 15, 0},/*15*/

};
/*Will will go throw evey line of a given assembly code and look for error and count the image and data.
 * @param fd1 - pointer to the beginning of the file
 * @param symollist - pointer to the list we will save all the labels and there addresses
 * return TRUE/FALSE - if there is one error we will stop the will continue to the next file*/

int firstPass(FILE *fd1, ptr *symbolList) {
    char str[MAX_SIZE_LINE];/*Our line*/
    int IC = 0; /*The IC counter*/
    int DC = 0;/* The DC counter*/
    while (!feof(fd1)) {
        fgets(str, MAX_SIZE_LINE, fd1); /*getting the line*/
        lineNum++; /*counting the line number after each pass*/
        analysisLine(str, symbolList, &IC, &DC);
        memset(str, 0, sizeof(str)); /*resetting the line*/
    }

    if (errorFlag == FALSE) /*if we found even one error on the first pass we stop*/
        return FALSE;

    rewind(fd1);/*if there is no error we rewind and continue to the second pass*/
    return TRUE;


}

/*Will go throw the line and analyze it  if its a label or a instruction or an opcode.
 * @param str - the line we are now analyzing
 * @param symollist - pointer to the list we will save all the labels and there addresses
 * @param IC - pointer to count the IC variables
 * @param DC - pointer to count the DC variables
*/
void analysisLine(char *str, ptr *symbolList, int *IC, int *DC) {

    int fileChar; /*save the char we in*/
    int cnt = 0; /*the counter will help us move throw the line*/
    unsigned long lineSize = strlen(str) + 2;/*will save the maximum size of the line*/
    label new;/*create a new label so we will be able to save the info if there is any label*/
    new.address = -1;/*If its FALSE,no label*/

    if (lineSize > MAX_SIZE_LINE) {/*if the line size is to big it will report an error and continue to check it*/
        printError(20);/*The max size line is 80 char*/
        return;
    }

    fileChar = skipSpace(str, &cnt);/*find the first char of the line*/


    if (fileChar != '.') { /*this is if the user wrote a number in the beginning of the code*/
        if ((isdigit(fileChar) != 0 && isalpha(fileChar) == 0)) {
            printError(33); /*name of the label can only start with letters*/
            return;
        }
    }


    if (fileChar == ';')/*if the first char is a comment comeback and skip the line*/
        return;

    while (fileChar != '\n' && cnt < lineSize && fileChar != 0) {
        if (isalpha(fileChar) != 0) { /*if its an alpha its can be a opcode or a label*/
            checkIfLabelOrOpcode(str, &cnt, symbolList, IC, &new);
        }
        if (fileChar == '.') { /*if its a . its can be data,string,entyrn,external*/
            checkIfInstruction(str, &cnt, symbolList, DC, IC, &new);
        }
        if (fileChar == ',') { /* if we have a comma its an illegal comma*/
            printError(4);/*illegal comma*/
        }
        cnt++;/*move to the next char*/
        fileChar = *(str + cnt);
    }
}
/*Will save the word and decide if its a opcode or a label or en error.
 * @param str - the line we are now analyzing
 * @param cnt - the counter we using to scan throw the code
 * @param symollist - pointer to the list we will save all the labels and there addresses
 * @param IC - pointer to count the IC variables
 * @param new - a possible new label , we will save the info here for the beggining
*/
void checkIfLabelOrOpcode(char *str, int *cnt, ptr *symbolList, int *IC, label *new) {
    char name[MAX_SIZE_LABEL];/*Using to save the string*/
    int i = 0;/*counter*/
    int indexOp;/*save the index op the opCode*/
    int fileChar = skipSpace(str, cnt);

    /* this part is saving the name of the label or the opcode and checking that is legal code*/
    while (fileChar != '\n' && fileChar != ' ' && i < MAX_SIZE_LABEL - 1) {
        if (isalpha(fileChar) || isdigit(fileChar)) {
            name[i] = (char) fileChar;
            i++;
        } else {
            if (fileChar == ':')/*we found the label*/
                break;
            else {
                printError(1);/*can use only numbers and the ABC*/
                /*scanning to the end or to the : symbol. to continue the line scanning*/
                while (fileChar != '\n' && fileChar != ':' && fileChar != ' ') {
                    *cnt = *cnt + 1;
                    i++;
                    fileChar = *(str + *cnt);
                }
                if (i + 1 >= MAX_SIZE_LABEL) {
                    printError(22); /*the label name is too long*/
                }
                return;
            }
        }
        /*if we got here the char is legal and we can continue the scan*/
        *cnt = *cnt + 1;
        fileChar = *(str + *cnt);
    }
      /* the name of the label is too long - in this case its a legel chars but its too long*/
    if (i + 1 >= MAX_SIZE_LABEL) {
        printError(22);/*the label name is too long*/
        return;
    }
    name[i] = '\0';

    /*In case its an label*/
    if (fileChar == ':') {
        if (emptyLabel(str, cnt) == TRUE) {
            printError(38); /*its an empty label like without anything after it.*/
            return;
        }
        if (isIllegalName(name) == TRUE) {
            printError(3); /*chose illegal name for the label*/
            return;
        } else {
            if (findLabel(name, symbolList, FIRST_PASS, 0) != NULL) {
                printError(2);/*the name of the label is already in use*/
                return;
            }
            else {
                strcpy(new->name, name);/*save the label name*/
                new->address = *IC;/*save the label address*/
            }
        }
        return;/*continue the scan*/
    }

        /*in case its an opCode*/

    else {
        if ((indexOp = isOpCode(name)) != FALSE) {
            if (new->address != -1) { /*if its not false we have a label before the opcode*/
                strcpy(new->type, "code"); /*save the type of the opcode*/
                strcpy(new->location, "zero"); /*the location can be entry or extern or zero if its in this file*/
                addTwoList(new, symbolList, FIRST_PASS);/*Try to add the label to the list*/
            }
            fileChar = skipSpace(str, cnt); /*skipping the empty chars*/
            if (fileChar == ',')/*if we found a comma its an error*/
                printError(4);/* Illegal comma*/
            if (indexOp >= 0 && indexOp <= 4)
                checkTwoParam(str, cnt, IC, indexOp);/*Checking if 2 instruction after the opcode is legal*/
            if (indexOp >= 5 && indexOp <= 13)
                checkOneParam(str, cnt, IC, indexOp);/*Checking if 1 instruction after the opcode is legal*/
            if (indexOp == 14 || indexOp == 15)
                checkZeroParam(str, cnt, IC, indexOp);/*Checking if 0 instruction after the opcode is legal*/
        } else
            /*In this part the case that this is not a label and not a opcode,probrly a mistake
             * now will will check what kind of mistake*/
            findComplexError(str, cnt); /*find the mistake*/
    }
}


/*We will analyze the given instruction to see if its legal and if we able we will save it.
 * @param str - the line we are now analyzing
 * @param cnt - the counter we using to scan throw the code
 * @param symollist - pointer to the list we will save all the labels and there addresses
 * @param IC - pointer to count the IC variables
 * @param DC - pointer to count the DC variables
 * @param new - a possible new label , we will save the info here for the beginning
*/
void checkIfInstruction(char *str, int *cnt, ptr *symbolList, int *DC, int *IC, label *new) {
    int i = 0;
    int flagInsturction;
    int fileChar = *(str + *cnt);
    char temp[MAX_SIZE_INSTRUCTION + 1]; /*the instruction command will be saved here*/

    /*Scanning throw the line and saving the instruction*/
    while (*str != '\0' && fileChar != ' ' && i < MAX_SIZE_INSTRUCTION && fileChar != '\n') {
        if (isalpha(fileChar)) {
            temp[i] = fileChar;
            i++;
        }
        *cnt = *cnt + 1;
        fileChar = *(str + *cnt);
    }
    temp[i] = '\0';

    flagInsturction = isInstruction(temp);/*cheking if the instruction is valid*/
    if (flagInsturction != FALSE) {
        checkInstruction(str, cnt, symbolList, DC, IC, new, flagInsturction); /*if its an instruction we will continue*/

    } else
        printError(9);/*Invalid instuction command*/

}
/*We will analyze the given instruction to see if its legal and if we able we will save it.
 * @param str - the line we are now analyzing
 * @param cnt - the counter we using to scan throw the code
 * @param symollist - pointer to the list we will save all the labels and there addresses
 * @param DC - pointer to count the DC variables
 * @param new - a possible new label , we will save the info here for the beginning
 * @param flag - to  know what type of instuction it is.
*/
void checkInstruction(char *str, int *cnt, ptr *symbolList, int *DC, int *IC, label *new, int flag) {
    int fileChar = *(str + *cnt); /*save the first Char*/
    int flagParam; /*flag to know if the label after the instruction is legal*/
    int counter = 0; /*co count the save of the label after the instruction*/

    strcpy(new->type, instruction[flag]);/*save the type of the instruction*/

    if (new->address != -1) { /*this instruction have label*/
        switch (flag) {
            case 0:/*its a data instruction*/
                strcpy(new->location, "0");
                addTwoList(new, symbolList, FIRST_PASS);
                checkDataInteger(str, cnt, DC, IC);
                break;
            case 1: /*its a string instruction*/
                strcpy(new->location, "0");
                addTwoList(new, symbolList, FIRST_PASS);
                checkDataString(str, cnt, DC, IC);
                break;
            case 2:/*its an entry instuction with a label so we putting a warring*/
                printf(RED"Waring - In File: %s in Line: %d you have label before entry instruction\n"REST, fileName,
                       lineNum);
                while (fileChar != '\n') { /*moving to the end of the line to start scan the next line, will come back later*/
                    fileChar = *(str + *cnt);
                    *cnt = *cnt + 1;
                    counter++;
                }
                if (counter > MAX_SIZE_LABEL || (counter + 2) > MAX_SIZE_LABEL)
                    printError(22);/*the label name is to long*/
                break;
            case 3:/*its an external instruction with a label so we putting a waring*/
                printf(RED"Waring - In File: %s in Line: %d you have label before extern instruction\n"REST, fileName,
                       lineNum);
                flagParam = checkParameter(str, cnt, new->name);
                strcpy(new->location, instruction[3]);/*external*/
                new->address = 0; /*address of the insturction is 0*/
                if (flagParam) /*to check that there is a symbol*/
                {
                    if (findLabel(new->name, symbolList, FIRST_PASS, 0) == NULL)
                        addTwoList(new, symbolList, FIRST_PASS);
                    else
                        printError(2);/*the name of the label is already in use*/
                }
                break;
        }
    }

    if (new->address == -1) { /*if there is no label*/
        switch (flag) {
            case 0:
                checkDataInteger(str, cnt, DC, IC); /*continue to analyze the line and see if there are integers*/
                break;
            case 1:
                checkDataString(str, cnt, DC, IC);/*continue to analyze the line and see if there are chars*/
                break;
            case 2: /*This is an entry will work with it on the second pass*/
                while (fileChar != '\n') {
                    fileChar = *(str + *cnt);
                    *cnt = *cnt + 1;
                    counter++;
                }
                if (counter > MAX_SIZE_LABEL || (counter + 2) > MAX_SIZE_LABEL)
                    printError(22);/*the label name too long*/
                break;
            case 3:
                flagParam = checkParameter(str, cnt, new->name);
                if (flagParam != FALSE) /*to check that there is a symbol*/
                {

                    strcpy(new->location, instruction[3]);/*external*/
                    new->address = 0;
                }

                if (findLabel(new->name, symbolList, FIRST_PASS, 0) == NULL)
                    addTwoList(new, symbolList, FIRST_PASS); /*if the name is not taken add it to the list*/
                break;

        }
    }

}


/*The function will check if the two param is legal and if its true will count it in the IC
 * @param str - Pointer to a string in the file
 * @param cnt - the counter that works with the string
 * @param IC - pointer to the IC counter
 * param indexOp - save the indexOp number */
void checkTwoParam(char *str, int *cnt, int *IC, int indexOp) {

    param firstParam; /*first param of the command*/
    param secondParam; /*second param of the command */
    resetParam(&firstParam);
    resetParam(&secondParam);

    if (legalTwoParam(str, cnt, &firstParam, &secondParam, indexOp) == TRUE)
        countIC(firstParam.addressing, secondParam.addressing, IC); /*If every thing is working add count the IC*/

}
/*The function will check if the one param is legal and if its true will count it in the IC
 * @param str - Pointer to a string in the file
 * @param cnt - the counter that works with the string
 * @param IC - pointer to the IC counter
 * param indexOp - save the indexOp number */

void checkOneParam(char *str, int *cnt, int *IC, int opCode) {

    param firstParam; /*first param of the command - is empty in this case*/
    param secondParam; /*second param of the command */
    resetParam(&firstParam);
    resetParam(&secondParam);

    if (legalOneParam(str, cnt, &firstParam, &secondParam, opCode) == TRUE)
        countIC(firstParam.addressing, secondParam.addressing, IC);/*If every thing is working add count the IC*/

}
/*The function will check if the zero param is legal and if its true will count it in the IC
 * @param str - Pointer to a string in the file
 * @param cnt - the counter that works with the string
 * @param IC - pointer to the IC counter
 * param indexOp - save the indexOp number */
void checkZeroParam(char *str, int *cnt, int *IC, int opCode) {

    param firstParam; /* is empty in this case*/
    param secondParam; /*is empty in this case*/
    resetParam(&firstParam);
    resetParam(&secondParam);

    if (legalZeroParam(str, cnt, &firstParam, &secondParam, opCode) == TRUE)
        countIC(firstParam.addressing, secondParam.addressing, IC);/*If every thing is working add count the IC*/

}
/*The function will check every component of the line to see if the syntax and the rules of the assemble is true
 * @param str - Pointer to a string in the file
 * @param cnt - the counter that works with the string
 * @param firstParam - will save the info of the first param here
 * @param secondParam - will save the info the second param here
 * param indexOp - save the indexOp number
 * return  return TRUE if everything as it should to be*/
int legalTwoParam(char *str, int *cnt, param *firstParam, param *secondParam, int opCode) {
    int check1;
    int check2;
    int check3;
    int check4;
    int check5;

    check1 = findParam(str, cnt, firstParam, FIRST_PARAM); /*find the first param*/
    check2 = findComma(str, cnt); /*find the first comma*/
    check3 = findParam(str, cnt, secondParam, SECOND_PARAM); /*find the first number that is real number*/
    check4 = findEnd(str, cnt); /*check that the rest of the command is clear*/
    check5 = checkStatement(opCode, firstParam->addressing, secondParam->addressing);

    if (check1 == FALSE || check2 == FALSE || check3 == FALSE || check4 == FALSE || check5 == FALSE)
        return FALSE;

    return TRUE;
}
/*The function will check every component of the line to see if the syntax and the rules of the assemble is true
 * @param str - Pointer to a string in the file
 * @param cnt - the counter that works with the string
 * @param firstParam - will save the info of the first param here
 * @param secondParam - will save the info the second param here
 * param indexOp - save the indexOp number
 * return  return TRUE if everything as it should to be*/
int legalOneParam(char *str, int *cnt, param *firstParam, param *secondParam, int opCode) {
    int check1;
    int check2;
    int check3;

    check1 = findParam(str, cnt, secondParam, FIRST_PARAM); /*find the complex number you want to print*/
    check2 = findEnd(str, cnt); /*check that the rest of the command is clear*/
    check3 = checkStatement(opCode, firstParam->addressing, secondParam->addressing);

    if (check1 == FALSE || check2 == FALSE || check3 == FALSE)
        return FALSE;

    return TRUE;
}
/*The function will check every component of the line to see if the syntax and the rules of the assemble is true
 * @param str - Pointer to a string in the file
 * @param cnt - the counter that works with the string
 * @param firstParam - will save the info of the first param here
 * @param secondParam - will save the info the second param here
 * param indexOp - save the indexOp number
 * return  return TRUE if everything as it should to be*/
int legalZeroParam(char *str, int *cnt, param *firstParam, param *secondParam, int opCode) {
    int check1, check2;
    check1 = findEnd(str, cnt); /*check that the rest of the command is clear*/
    check2 = checkStatement(opCode, firstParam->addressing, secondParam->addressing);

    if (check1 == FALSE || check2 == FALSE)
        return FALSE;

    return TRUE;

}
/*The function will check every component of the line to see if the syntax and the rules of the assemble is true
 * @param str - Pointer to a string in the file
 * @param cnt - the counter that works with the string
 * @param name - the name of the param we want to check
 * return  return TRUE if the name is legal*/
int checkParameter(char *str, int *cnt, char *name) {
    int i = 0;
    int flagAlpha = TRUE;/*to check if the char is legal or not*/
    int fileChar = skipSpace(str, cnt);

    /*scanning throw the name and check if every component of him to see if its legal*/
    while (fileChar != '\n' && fileChar != ' ' && fileChar != ',' && fileChar != '\0' && i < MAX_SIZE_LABEL - 1) {
        if (flagAlpha == TRUE) {
            if (isalpha(fileChar) == 0) {

                printError(28);/*First latte shout start with the ABC*/

            }
            flagAlpha = FALSE; /*if there is more illegal chars we will not put this message again*/
        }
        /*if every thing its good we will save the char*/
        if ((isalpha(fileChar) != 0) || isdigit(fileChar) != 0) {
            name[i] = (char) fileChar;
            i++;
        } else {
            printError(1); /*in the middle or in the end we found illegal chars*/
            /*skipping to the end of the line*/
            while (fileChar != '\n' && fileChar != ' ' && fileChar != ',' && fileChar != '\0') {
                *cnt = *cnt + 1;
                fileChar = *(str + *cnt);
            }
            return FALSE;
        }
        /*if the char is legal we will continue to scan*/
        *cnt = *cnt + 1;
        fileChar = *(str + *cnt);
    }
    if (i + 1 >= MAX_SIZE_LABEL) {
        printError(22);/*the label is too long*/
        while (fileChar != '\n' && fileChar != ' ' && fileChar != ',' && fileChar != '\0') {
            *cnt = *cnt + 1;
            fileChar = *(str + *cnt);
        }
        return FALSE;
    }

    name[i] = '\0';

    if (i == 0) {
        printError(21);/*missing a name*/
        return FALSE;
    }
    return TRUE;
}
/*The function will find if the param name is legal.
 * @param str - Pointer to a string in the file
 * @param cnt - the counter that works with the string
 * @param operand - the name of the param we want to check
 * @param index - a flag to know if its a first operand or the second operand
 * return TRUE if the name is legal*/
int findParam(char *str, int *cnt, param *operand, int index) {

    int paramFlag;
    int fileChar;

    fileChar = skipSpace(str, cnt);
    if (fileChar == '\n') {
        if (index == FIRST_PARAM)
            printError(6);/*missing a source operand*/
        else
            printError(7);/*missing a target operand*/
        return FALSE;
    }
    /*to see if its a legal operand*/
    if (isdigit(fileChar) == 0 && isalpha(fileChar) == 0 && fileChar != '&' && fileChar != '#') {
        while (fileChar != '\n' && fileChar != ' ') {
            *cnt = *cnt + 1;
            fileChar = *(str + *cnt);
        }
        if (index == FIRST_PARAM)
            printError(36);/*illegal source operand*/
        if (index == SECOND_PARAM)
            printError(37);/*illegal target operand*/
        return FALSE;
    }
    /*to check if its a valid number - it will not be able to covert it it will print in the second pass*/
    if (fileChar == '#') {
        *cnt = *cnt + 1;
        operand->val = validNumber(str, cnt);
        if (operand->val != FALSE) {
            operand->addressing = IMMEDIATELY;
            return TRUE;
        } else
            operand->addressing = EMPTY;

        return FALSE;
    }
    /*cheking if its a legal label after the & signg*/
    if (fileChar == '&') {
        *cnt = *cnt + 1;
        fileChar = *(str + *cnt);
        if (isalpha(fileChar) != 0) {
            operand->addressing = RELATIVE;
            checkParameter(str, cnt, operand->paramName);
            return TRUE;
        } else {
            printError(5);/*must come after & a label*/
            operand->addressing = EMPTY;
        }
        return FALSE;
    }
    /*cheking if we missing a operand*/
    paramFlag = checkParameter(str, cnt, operand->paramName);
    if (paramFlag == NO_PARAM) {
        if (index == FIRST_PARAM)
            printError(6);
        if (index == SECOND_PARAM)
            printError(7);
        return FALSE;
    }
    /*save the address of the label as a register or a direct*/
    operand->val = isRegister(operand->paramName);
    if (operand->val != FALSE) {
        operand->addressing = REGISTER_DIRECT;
        return TRUE;
    } else {
        operand->addressing = DIRECT;
        return TRUE;
    }

}
/*The function will return if the label is empty.
 * @param str - Pointer to a string in the file
 * @param cnt - the counter that works with the string
 * return TRUE if the name is legal*/
int emptyLabel(char *str, int *cnt) {
    int fileChar;
    int counter = *cnt;

    *cnt = *cnt + 1;
    fileChar = skipSpace(str, cnt);
    if (fileChar == 0 || fileChar == '\n')
        return TRUE;

    *cnt = counter;
    return FALSE;
}
/*If we got to these function there is an error and it will find it
 * @param str - Pointer to a string in the file
 * @param cnt - the counter that works with the string
 * return TRUE if the name is legal*/
void findComplexError(char *str, int *cnt) {
    int fileChar = *(str + *cnt);
    int counter = 0;
    while (fileChar != ':' && fileChar != '\n' && fileChar != '.') {
        *cnt = *cnt + 1;
        counter++;
        fileChar = *(str + *cnt);
    }
    if (fileChar == ':')
        printError(35);/*should put the : next to the label*/
    if (fileChar == '\n')
        printError(29);/*illegal opcode*/
    if (fileChar == '.') {
        printError(34);/*illegal lalbel*/
        *cnt = *cnt - 1;
    }

}
