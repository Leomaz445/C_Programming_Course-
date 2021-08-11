/*
 * This if Second Pass - If we got to here there is a minimal opetion to an error so it here we just collcting
 * the given values of the operands using the symbol table that we created, in this pass we also creating the
 * external symbol table. if the second pass will go good we will start to create files.
 * @Leonid Mazarsky ID: 319401980
 * @21-08-202020 17:27
*/


#include "secondPass.h"

/*it will go to the function of each the uer wrote*/
struct {
    char *name;
    void (*func)(char *, int *, int , int , ptr *,ptr *,int *,word *[]);
} cmd[] = {{"mov",  TwoParam},
           {"cmp",  TwoParam},
           {"add",  TwoParam},
           {"sub",  TwoParam},
           {"lea",  TwoParam},
           {"clr",  OneParam},
           {"not",  OneParam},
           {"inc",  OneParam},
           {"dec",  OneParam},
           {"jmp",  OneParam},
           {"bne",  OneParam},
           {"jsr",  OneParam},
           {"red",  OneParam},
           {"prn",  OneParam},
           {"rst",  ZeroParam},
           {"stop", ZeroParam},
           {"Undefined command name", NULL}};


/*Will will go throw evey line of a given assembly code count the data to the Instruction table and the Data table
 * and we will be creating the external list also, if we will found an error we will not continue to create the out put files
 * if there is no error we will crete the files.
 * @param fd1 - pointer to the beginning of the file
 * @param symollist - pointer to the list with all the symbols of the program
 * @param name - the name of the file we will creating*/

void secondPass(FILE *fd1,ptr *symbolList,char *name) {
    char str[MAX_SIZE_LINE]; /*will save the given line here*/
    int IC = 0;/*will count the IC*/
    int DC = 0;/*will count the DC*/
    ptr externList=NULL;/*a list to extern words*/
    word *instructionTable[INSTRUCTION_TABLE_LEN];/*will save here the instructions*/
    word *dataTable[DATA_TABLE_LEN];/*will save here the data*/
    lineNum=0;/*starting the scan from the begining*/

    while (!feof(fd1)) {
        memset(str, 0, sizeof(str));
        fgets(str, MAX_SIZE_LINE, fd1);
        lineNum++;
        secondPassLine(str, symbolList, &externList, instructionTable, dataTable, &IC, &DC);
    }
    if(errorFlag==TRUE) /*if we went throw the lines we will crete the files*/
    {    /*files created*/
        printf("\033[1;32m");
        printf("\n----Your files successfully created ----\n");
        printf("\033[0m;");
        makeOutPutFiles(name, instructionTable, dataTable, &IC, &DC, symbolList, &externList);
    }


}
/*Will will go throw evey line of a given assembly code and collect data and look for errors
 * @param fd1 - pointer to the beginning of the file
 * @param symollist - pointer to the list of all the symbols of the program
 * @para, externList - pointer to the list were we will save the extern label appearance
 * @param instructionTable - we will save the insturction here.
 * @param dataTable - will save the data we collcting here
 * @param IC - IC counter
 * @param C - DC counter */
void secondPassLine(char *str, ptr *symbolList,ptr *externList, word *instructionTable[], word *dataTable[], int *IC, int *DC) {
    int lineSize = strlen(str) + 2;
    int flagLabel = FALSE;/*If its -1,no label*/
    int fileChar;
    int cnt = 0;
    fileChar = *(str + cnt);


    while (fileChar != '\n' && cnt < lineSize) {
        if (fileChar==';') /*if its a comment we skip the line*/
            return;
        if (isalpha(fileChar) != 0) { /*if its A-Z will chake if its an label or an opcode*/
            SPcheckIfLabelOrOpcode(str, &cnt, symbolList,externList, instructionTable, IC, &flagLabel);
        } else if (fileChar=='.') { /*check if its insturction*/
            SPcheckIfInstruction(str, &cnt, symbolList, dataTable, DC);
        }
        cnt++;
        fileChar = *(str + cnt);
    }
}
/*The function will cheack if its a label or an opcode
 * @param str -the line we are scanning
 * @param cnt - counter we scanning the line with
 * @para, symbolList - the symbol list we have from the program
 * @param instructionTable - an array that will be saving all the instuction.
 * @param IC - IC counter
 * @param flagLabel - to know if its a a label before him*/
void SPcheckIfLabelOrOpcode(char *str, int *cnt, ptr *symbolList,ptr *externList, word *instructionTable[], int *IC, int *flagLabel) {
    char name[MAX_SIZE_LABEL];/*Using to save the string*/
    int i = 0;/*counter*/
    int indexOp;/*save the index op the opCode*/
    int fileChar = *(str + *cnt);
    fileChar=skipSpace(str,cnt);
    if (fileChar == ' ') {
        while (isspace(fileChar)) {
            *cnt = *cnt + 1;
            fileChar = *(str + *cnt);
        }
    }
    /*Saveing the label name*/
    while (fileChar != '\n' && fileChar != ' ' && i < MAX_SIZE_LABEL - 1) {
        if (isalpha(fileChar) || isdigit(fileChar)) {
            name[i] = (char) fileChar;
            i++;
        } else if (fileChar == ':')/*we found the label*/
        {
            *flagLabel = TRUE;
            name[i] = '\0';
            return;
        }
        *cnt = *cnt + 1;
        fileChar = *(str + *cnt);
    }

    name[i] = '\0';
    /*In Case its opCode*/
    if ((indexOp = isOpCode(name)) != FALSE) {
        while (isspace(fileChar) != 0) {
            *cnt = *cnt + 1;
            fileChar = *(str + *cnt);
        }

        for (i = 0; i < NUMBER_OF_OP; i++) { /*going to find the operands and build them*/
            if (strncmp(cmd[i].name, name,4) == TRUE) {
                /*go to the function the user wrote*/
                (*(cmd[i].func))(str, cnt, opCodeTable[i].opCode,
                                 opCodeTable[i].funct, symbolList,externList,IC ,instructionTable);
                return;
            }
        }

    }
}
/*The function will check if its an instruction and we need to save data
 * @param str -the line we are scanning
 * @param cnt - counter we scanning the line with
 * @para, symbolList - the symbol list we have from the program
 * @param dataTable - an array that will be saving all the data.
 * @param DC - DC counter*/
void SPcheckIfInstruction(char *str, int *cnt, ptr *symbolList,word* dataTable[], int *DC) {
    int i = 0;
    int flagInsturction;
    int fileChar = *(str + *cnt);
    char name[MAX_SIZE_LINE];

    /*save the insturction name*/

    while (*str != '\0' && fileChar != ' '  && fileChar != '\n') {
        if (isalpha(fileChar)) {
            name[i] = (char)fileChar;
            i++;
        }
        *cnt = *cnt + 1;
        fileChar = *(str + *cnt);
    }
    name[i] = '\0';

    flagInsturction = isInstruction(name);
    switch (flagInsturction) {
        case 0:
            getDataInteger(str, cnt, dataTable, DC); /*save the integers in the array*/
            break;
        case 1:
            getDataString(str, cnt, dataTable, DC);/*save the data string in the array*/
            break;
        case 2:
            getParameterName(str, cnt, name);
            if (findLabel(name, symbolList, SECOND_PASS, instruction[2]) == NULL) {
                printError(31);/*did not find the label*/
            }
            break;
    }



}


void getDataInteger(char *str, int *cnt, word *dataTable[], int *DC) {
    int fileChar = *(str + *cnt);
    int newNum;

    while (isspace(fileChar)) {
        *cnt = *cnt + 1;
        fileChar = *(str + *cnt);
    }

    while (fileChar != '\n'&& fileChar!='\0') {
        while (isspace(fileChar)) {
            *cnt = *cnt + 1;
            fileChar = *(str + *cnt);
        }
        newNum = validNumber(str, cnt);
        if(!validBits(newNum))
            printError(44);
        else {
            dataTable[*DC] = (word *) calloc(1, sizeof(word)); /* Allocating memory for the machine code */
            if (!dataTable[*DC])
                printError(42);
            else {
                setNum(dataTable[*DC], newNum);
                *DC = *DC + 1;
            }
        }
        while (fileChar == ',') {
            *cnt = *cnt + 1;
            fileChar = *(str + *cnt);
        }
        *cnt = *cnt + 1;
        fileChar = *(str + *cnt);
    }
}
/*Function will save all the char of the sring in the data table.
 * @param str -the line we are scanning
 * @param cnt - counter we scanning the line with
 * @param dataTable - an array that will be saving all the data.
 * @param DC - DC counter*/
void getDataString(char *str, int *cnt, word *dataTable[], int *DC) {
    char temp[MAX_SIZE_LINE];
    int i = 0;
    int j;
    int ch = 0;
    int fileChar = *(str + *cnt);

    while (isspace(fileChar)) {
        *cnt = *cnt + 1;
        fileChar = *(str + *cnt);
    }
    *cnt = *cnt + 1;
    fileChar = *(str + *cnt);


    while (fileChar != '\0' && fileChar != '\n' && (*(cnt) <= 80)) {

        temp[i] = (char) fileChar;
        i++;

        *cnt = *cnt + 1;
        fileChar = *(str + *cnt);
    }
    temp[i] = '\0';
    /*we will save everything between 2 ""*/
    for (j = 0; j < i; j++) {
        if (temp[j] == '"')
            ch = j;
    }

    for (j = 0; j < ch; j++) {
        dataTable[*DC] = (word *)calloc(1, sizeof(word)); /* Allocating memory for the machine code */
        if(!dataTable[*DC])
            printError(42);/*error allocate memory for the data table*/
        else {
            setNum(dataTable[*DC], temp[j]);
            *DC = *DC + 1;
        }
    }
    dataTable[*DC] = (word *)calloc(1, sizeof(word)); /* Allocating memory for the machine code */
    if(!dataTable[*DC])
        printError(42);/*error allocate memory for the data table*/
    else {
        setNum(dataTable[*DC], 0);
        *DC = *DC + 1;
    }
}
