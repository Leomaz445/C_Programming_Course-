/*
 * This is the main library that creating the word and putting it in a table
 * @Leonid Mazarsky ID: 319401980
 * @21-08-202020 17:27
*/

#include "assembler.h"

int getIndex(int,int);/*getting the the number of how much IC needed to be created 1,2,3*/
void setParam(char *, int *, param *, ptr *,int *);/*getting info about the param*/
void createIC(param *, param *, int ,int , int index, word *[],int *,ptr *);/*creating the IC*/
enum ARE {
    A = 4, R = 2, E = 1
};
/*The function will check that syntax of the both parameter is legall and create the IC
 * @param str -the line we are scanning
 * @param cnt - counter we scanning the line with
 * @para opcode - the opcode of the action
 * @param symbolList - the symboList with all the labels from the first scan
 * @param externList - the list were we will save all the external label apperance
 * @param IC - IC counter
 * @param instructionTable - were we will save the created insturction*/
void TwoParam(char *str, int *cnt, int opCode, int funct, ptr *symbolList, ptr *externList, int *IC, word *instructionTable[])
{
    int fileChar = *(str + *cnt);
    int index=0;
    param paramOne;
    param paramTwo;
    resetParam(&paramOne);
    resetParam(&paramTwo);

    setParam(str, cnt, &paramOne, symbolList, IC); /*getting the info for the param*/

    /*skipping white spaces and the , between the two params*/
    while (isspace(fileChar) != 0) {
        *cnt = *cnt + 1;
        fileChar = *(str + *cnt);
    }
    *cnt = *cnt + 1;
    fileChar = *(str + *cnt);

    while (isspace(fileChar) != 0) {
        *cnt = *cnt + 1;
        fileChar = *(str + *cnt);

    }

    setParam(str, cnt, &paramTwo, symbolList, IC);/*getting the info of the second param*/

    index=getIndex(paramOne.addressing,paramTwo.addressing);/*getting the number of IC needed*/

    /*adding the values to the IC table*/
    createIC(&paramOne,&paramTwo,opCode,funct,index,instructionTable,IC,externList);
}
/*The function will check that syntax of command with one param
 * @param str -the line we are scanning
 * @param cnt - counter we scanning the line with
 * @para opcode - the opcode of the action
 * @param symbolList - the symboList with all the labels from the first scan
 * @param externList - the list were we will save all the external label apperance
 * @param IC - IC counter
 * @param instructionTable - were we will save the created insturction*/
void OneParam(char *fileLine, int *cnt, int opCode, int funct, ptr *symbolList,ptr *externList,int *IC,
              word *instructionTable[]) {
    param paramOne;
    param paramTwo;
    int index=0;
    resetParam(&paramOne);
    resetParam(&paramTwo);

    setParam( fileLine, cnt, &paramTwo, symbolList,IC);/*getting the info of the second param*/
    index=getIndex(paramOne.addressing,paramTwo.addressing);/*getting the number of IC needed*/
    /*adding the values to the IC table*/
    createIC(&paramOne,&paramTwo,opCode,funct,index,instructionTable,IC,externList);

}
/*The function will check that syntax of the command with zero param*
 * @param str -the line we are scanning
 * @param cnt - counter we scanning the line with
 * @para opcode - the opcode of the action
 * @param symbolList - the symboList with all the labels from the first scan
 * @param externList - the list were we will save all the external label apperance
 * @param IC - IC counter
 * @param instructionTable - were we will save the created insturction*/

void ZeroParam(char *fileLine, int *cnt, int opCode, int funct, ptr *symbolList,ptr *externList,int *IC,word *instructionTable[])
{
    int index=1;
    param paramOne;
    param paramTwo;
    resetParam(&paramOne);
    resetParam(&paramTwo);

/*adding the values to the IC table*/
    createIC(&paramOne,&paramTwo,opCode,funct,index,instructionTable,IC,externList);


}

/*
 * Gitting the name of the opernad - label or register
 * @opernad str - the line we are scanning
 * @cnt - the counter that we scanning the line
 * @name - were the name of the param will be saved
 */
void getParameterName(char *str, int *cnt, char *name) {
    int i = 0;
    int fileChar=0;
    while (fileChar != '\n' && fileChar != ' ' && fileChar != ',') {
        fileChar = *(str + *cnt);

        if ((isalpha(fileChar) != 0) || isdigit(fileChar) != 0) {
            *(name + i) =(char) fileChar;
            i++;
        }
        *cnt = *cnt + 1;
        fileChar = *(str + *cnt);
    }
    name[i] = '\0';

}
/*
 *This function send all the valuse to the function that will create the word in the index cell
 * @param index - number of the IC
 * @param opCode - number of the opcode
 * @param addressingSource - addressing source represented by a number
 * @param sourceRegister - source register represented by a number
 * @param addressTarget - address target represented by a number
 * @param targetRegister - target register - represnted by a number
 * @param funct - funct number
 * @param are - are represnted by a number
 */
void buildWord(int index, int opCode, int addressingSource, int sourceRegister, int addressTarget, int targetRegister,
               int funct,
               int are, word *instructionTable[]) {
    setOpcode(instructionTable[index], opCode);
    setAddressingSource(instructionTable[index], addressingSource);
    setSourceRegister(instructionTable[index], sourceRegister);
    setAddressingDestination(instructionTable[index], addressTarget);
    setTargetRegister(instructionTable[index], targetRegister);
    SetFunct(instructionTable[index], funct);
    setARE(instructionTable[index], are);
}
/* This function determined the adressing values
 * @param str - the line we are reading from
 * @param cnt - the counter that help us read from the line
 * @param opernad - the operand we work with
 * @param symbolList - the symbol list we created
 * @param IC - IC counter
 */
void setParam(char *str, int *cnt, param *operand, ptr *symbolList,int *IC) {

    int fileChar;
    label *holdName;
    fileChar = *(str + *cnt);
    /*skip the space*/
    while (isspace(fileChar)) {
        *cnt = *cnt + 1;
        fileChar = *(str + *cnt);
    }
    if (fileChar == '#') { /*cheking if the adressing is immediately*/
        *cnt = *cnt + 1;
        operand->val = validNumber(str, cnt);
        if(validBits(operand->val)==2)
            operand->addressing = IMMEDIATELY;
        else
            printError(44);
        return;
    }
    if (fileChar == '&') { /*cheking if the adressing is realtive*/
        *cnt = *cnt + 1;
        operand->addressing = RELATIVE;
        getParameterName(str, cnt, operand->paramName);
        if((holdName=findLabel(operand->paramName,symbolList,FIRST_PASS,NULL))!=NULL)
            operand->val=holdName->address-(*IC);
        else
            printError(31);/*label not found*/
        return;
    }
    getParameterName(str, cnt, operand->paramName); /*getting the param name*/

    operand->val = isRegister(operand->paramName);
    if (operand->val != FALSE) {/*if its not regiter its a label*/
        operand->addressing = REGISTER_DIRECT;
        return;
    }
    else
    {
        operand->addressing = DIRECT;
        if((holdName=findLabel(operand->paramName,symbolList,FIRST_PASS,NULL))!=NULL) {
            operand->val = holdName->address;
        }
        else
            printError(31);/*label not found*/
    }

}

/*Function creating with a given index - 1 ,2 ,3 the number of the IC he needed in the instruction table.
 * then the function looking for matching addressing methodnd of the parameters.
 * @param one - the first opernad
 * @param two - the second opernad
 * @param opCode - the opcode
 * @param funct - the number of the funct
 * @param index - how many IC cells we need to create in the insturction table
 * @param instructionTable - were will save the instuction
 * @param IC - IC Counter
 * @param externList - the extern list were we will save the apperance of extern label
 */
void createIC(param *one, param *two, int opCode, int funct, int index, word *instructionTable[],int *IC,ptr *externList) {
    label newExtern; /*new extern label will be adedd to the extern list if needed*/
    reset(&newExtern);

  /*if we need only one IC cell*/
    if (index == 1) {
        instructionTable[*IC] = (word *)calloc(1, sizeof(word)); /* Allocating memory for the machine code */
        if(!instructionTable[*IC])
            printError(43);/*error allocating memory*/
        else {
            if (one->addressing == REGISTER_DIRECT && two->addressing == REGISTER_DIRECT)
                buildWord(*IC, opCode, one->addressing, one->val, two->addressing, two->val, funct, A,
                          instructionTable);
            else if (one->addressing == EMPTY && two->addressing == REGISTER_DIRECT)
                buildWord(*IC, opCode, 0, 0, two->addressing, two->val, funct, A, instructionTable);
            else if (one->addressing == EMPTY && two->addressing == EMPTY)
                buildWord(*IC, opCode, 0, 0, 0, 0, funct, A, instructionTable);
            *IC = *IC + 1;
        }
        return;
    }
    /*two IC cells*/
    if (index == 2) {
        instructionTable[*IC] = (word *) calloc(1, sizeof(word)); /* Allocating memory for the machine code */
        instructionTable[*IC + 1] = (word *) calloc(1, sizeof(word));
        if (!instructionTable[*IC] || !instructionTable[*IC + 1])
            printError(43);/*error allocating memory*/
        else {
            if (one->addressing == IMMEDIATELY && two->addressing == REGISTER_DIRECT) {
                buildWord(*IC, opCode, one->addressing, 0, two->addressing, two->val, funct, A,
                          instructionTable);
                buildVal((*IC=*IC+1), one->val, A, instructionTable);
                *IC = *IC + 1;
                return;
            } else if (one->addressing == DIRECT && two->addressing == REGISTER_DIRECT) {
                buildWord(*IC, opCode, one->addressing, 0, two->addressing, two->val, funct, A,
                          instructionTable);
                if (one->val != 0)
                    buildVal((*IC=*IC+1), one->val + START_LINE, R, instructionTable);
                else {
                    buildVal((*IC=*IC+1), 0, E, instructionTable);
                    strcpy(newExtern.name, one->paramName);
                    newExtern.address = *IC;
                    strcpy(newExtern.location,instruction[3]);
                    addTwoList(&newExtern, externList, SECOND_PASS);
                }

                *IC = *IC + 1;
                return;
            } else if (one->addressing == REGISTER_DIRECT && two->addressing == IMMEDIATELY) {
                buildWord(*IC, opCode, one->addressing, one->val, two->addressing, 0, funct, A,
                          instructionTable);
                buildVal((*IC=*IC+1), one->val, A, instructionTable);
                *IC = *IC + 1;
                return;
            } else if (one->addressing == REGISTER_DIRECT && two->addressing == DIRECT) {
                buildWord(*IC, opCode, one->addressing, one->val, two->addressing, 0, funct, A,
                          instructionTable);
                if (two->val != 0)
                    buildVal((*IC=*IC+1), two->val + START_LINE, R, instructionTable);
                else {
                    buildVal((*IC=*IC+1), 0, E, instructionTable);
                    strcpy(newExtern.name, two->paramName);
                    newExtern.address = *IC;
                    strcpy(newExtern.location,instruction[3]);
                    addTwoList(&newExtern, externList, SECOND_PASS);
                }
                *IC = *IC + 1;
                return;
            } else if (one->addressing == EMPTY && two->addressing == IMMEDIATELY) {
                buildWord(*IC, opCode, 0, 0, two->addressing, 0, funct, A,
                          instructionTable);
                buildVal((*IC=*IC+1), two->val, A, instructionTable);
                *IC = *IC + 1;
                return;

            } else if (one->addressing == EMPTY && two->addressing == DIRECT) {
                buildWord(*IC, opCode, 0, 0, two->addressing, 0, funct, A,
                          instructionTable);
                if (two->val != 0)
                    buildVal((*IC=*IC+1), two->val + START_LINE, R, instructionTable);
                else {
                    buildVal((*IC=*IC+1), 0, E, instructionTable);
                    strcpy(newExtern.name, two->paramName);
                    newExtern.address = *IC;
                    strcpy(newExtern.location,instruction[3]);
                    addTwoList(&newExtern, externList, SECOND_PASS);
                }
                *IC = *IC + 1;
                return;


            } else if (one->addressing == EMPTY && two->addressing == RELATIVE) {
                buildWord(*IC, opCode, 0, 0, two->addressing, 0, funct, A,
                          instructionTable);
                buildVal((*IC=*IC+1), two->val, A, instructionTable);
                *IC = *IC + 1;
                return;

            }
        }
    }
   /*3 IC cells*/
    if (index == 3) {
        instructionTable[*IC] = (word *) calloc(1, sizeof(word)); /* Allocating memory for the machine code */
        instructionTable[*IC + 1] = (word *) calloc(1, sizeof(word));
        instructionTable[*IC + 2] = (word *) calloc(1, sizeof(word));
        if (!instructionTable[*IC] || !instructionTable[*IC + 1] || !instructionTable[*IC + 2])
            printError(43);/*error allocating memory*/
        else {

            if (one->addressing == IMMEDIATELY && two->addressing == IMMEDIATELY) {
                buildWord(*IC, opCode, one->addressing, 0, two->addressing, 0, funct, A, instructionTable);
                buildVal((*IC=*IC+1), one->val, A, instructionTable);
                buildVal((*IC=*IC+1), two->val, A, instructionTable);
                *IC = *IC + 1;
                return;
            } else if (one->addressing == IMMEDIATELY && two->addressing == DIRECT) {
                buildWord(*IC, opCode, one->addressing, 0, two->addressing, 0, funct, A, instructionTable);
                buildVal(*IC=*IC+1, one->val, A, instructionTable);
                if (two->val != 0)
                    buildVal(*IC=*IC+1, two->val + START_LINE, R, instructionTable);
                else {
                    buildVal((*IC=*IC+1), 0, E, instructionTable);
                    strcpy(newExtern.name, two->paramName);
                    newExtern.address = *IC;
                    strcpy(newExtern.location,instruction[3]);
                    addTwoList(&newExtern, externList, SECOND_PASS);
                }
                *IC = *IC + 1;
                return;
            } else if (one->addressing == DIRECT && two->addressing == IMMEDIATELY) {
                buildWord(*IC, opCode, one->addressing, 0, two->addressing, 0, funct, A, instructionTable);
                if (one->val != 0)
                    buildVal(*IC=*IC+1, one->val + START_LINE, R, instructionTable);
                else {
                    buildVal((*IC=*IC+1), 0, E, instructionTable);
                    strcpy(newExtern.name, one->paramName);
                    newExtern.address = *IC;
                    strcpy(newExtern.location,instruction[3]);
                    addTwoList(&newExtern, externList, SECOND_PASS);
                }
                buildVal((*IC=*IC+1), two->val, A, instructionTable);
                *IC = *IC + 1;
                return;
            } else if (one->addressing == DIRECT && two->addressing == DIRECT) {
                buildWord(*IC, opCode, one->addressing, 0, two->addressing, 0, funct, A, instructionTable);
                if (one->val != 0)
                    buildVal((*IC=*IC+1), one->val + START_LINE, R, instructionTable);
                else {
                    buildVal(*IC=*IC+1, 0, E, instructionTable);
                    strcpy(newExtern.name, one->paramName);
                    newExtern.address = *IC;
                    strcpy(newExtern.location,instruction[3]);
                    addTwoList(&newExtern, externList, SECOND_PASS);
                }
                if (two->val != 0)
                    buildVal(*IC=*IC+1, two->val + START_LINE, R, instructionTable);
                else {
                    buildVal(*IC=*IC+1, 0, E, instructionTable);
                    strcpy(newExtern.name, two->paramName);
                    newExtern.address = *IC;
                    strcpy(newExtern.location,instruction[3]);
                    addTwoList(&newExtern, externList, SECOND_PASS);
                }
                *IC = *IC + 1;
                return;
            }

        }
    }
}

/*This function will put the number val in the 21 bites, and the other 3 with ARE
 * @param index - the IC number
 * @param val- the number we want to put in the table
 * @param are - the ARE code
 * @param instructionTable - the instuction table
 */
void buildVal(int index, int val, int are, word *instructionTable[]) {
    setValue(instructionTable[index], val);
    setARE(instructionTable[index], are);
}
/* The function will return the number of cells of IC needed
 * @param paramOne - the addressing methond of the first param
 * @param paramTWo - the addressing method of the second param
 * return the number of IC cells needed.
 */
int getIndex(int paramOne,int paramTwo) {
    /*For Two Parameters*/
    if (paramOne == IMMEDIATELY && paramTwo == IMMEDIATELY)return 3;
    if (paramOne == IMMEDIATELY && paramTwo == DIRECT)return 3;
    if (paramOne == IMMEDIATELY && paramTwo == REGISTER_DIRECT)return 2;
    if (paramOne == DIRECT && paramTwo == IMMEDIATELY)return 3;
    if (paramOne == DIRECT && paramTwo == DIRECT)return 3;
    if (paramOne == DIRECT && paramTwo == REGISTER_DIRECT)return 2;
    if (paramOne == REGISTER_DIRECT && paramTwo == IMMEDIATELY)return 2;
    if (paramOne == REGISTER_DIRECT && paramTwo == DIRECT)return 2;
    if (paramOne == REGISTER_DIRECT && paramTwo == REGISTER_DIRECT)return 1;

    /*For One Parameter*/
    if (paramOne == EMPTY && paramTwo == DIRECT)return 2;
    if (paramOne == EMPTY && paramTwo == REGISTER_DIRECT)return 1;
    if (paramOne == EMPTY && paramTwo == RELATIVE)return 2;
    if (paramOne == EMPTY && paramTwo == IMMEDIATELY)return 2;

    /*For Zero Parameter*/
    if (paramOne == EMPTY && paramTwo == EMPTY)return 1;

    return FALSE;
}

