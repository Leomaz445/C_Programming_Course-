#include "firstPass.h"


/*The function will check if the integer is legal and count them to the IC and the DC
 * @param str - Pointer to a string in the file
 * @param cnt - the counter that works with the string
 * @param DC - the DC counter
 * @param IC- the IC counter*/
void checkDataInteger(char *str, int *cnt, int *DC, int *IC) {
    int fileChar = *(str + *cnt);
    int newNum = 0;

    while (isspace(fileChar)) { /*skip space*/
        *cnt = *cnt + 1;
        fileChar = *(str + *cnt);
    }

    if (fileChar == ',') {
        printError(11);/*illegal place for the comma*/
        *cnt = *cnt + 1;
        fileChar = *(str + *cnt);
    }


    while (fileChar != '\n') { /*scan the line untill the end*/
        newNum = validNumber(str, cnt);
        fileChar = *(str + *cnt);

        if (newNum == FALSE) { /*if the number not valid find the next digit*/
            while (isdigit(fileChar) || fileChar != '\n') {
                *cnt = *cnt + 1;
                fileChar = *(str + *cnt);
            }
            if (fileChar == '\n')/*if we went to the end ot the file and did not find anything return*/
                return;
        } else {
            /*count the DC and the IC*/
            *DC = *DC + 1;
            *IC = *IC + 1;
        }
        /*conditio to check if the comma is in the right place and if not to put the right message*/
        if (fileChar == '\0')
            return;
        if (fileChar == ' ') {
            while (isspace(fileChar)) {
                *cnt = *cnt + 1;
                fileChar = *(str + *cnt);
            }
            if (fileChar != ',') {
                printError(17);/*missing comma after data*/
            }

        }
        if (fileChar == ',') {
            *cnt = *cnt + 1;
            fileChar = *(str + *cnt);
            while (isspace(fileChar)) {
                *cnt = *cnt + 1;
                fileChar = *(str + *cnt);
            }
            if (fileChar == ',') {
                printError(18);/*double comma*/
                *cnt = *cnt + 1;
                fileChar = *(str + *cnt);
            }
            if (fileChar == '\n' || fileChar == '\0') {
                printError(30);/*please write a data after a comma*/
                *cnt = *cnt + 1;
                fileChar = *(str + *cnt);
            }
        }

    }
}

/*The function will check if the string is legal and count the chars to the IC and the DC
 * @param str - Pointer to a string in the file
 * @param cnt - the counter that works with the string
 * @param DC - the DC counter
 * @param IC- the IC counter*/
void checkDataString(char *str, int *cnt, int *DC, int *IC) {
    char temp[MAX_SIZE_LINE];
    int i = 0, j;/*counter*/
    int flagStart = FALSE;
    int flagEnd = FALSE;
    int fileChar = *(str + *cnt);
    int ch = 0;

    while (isspace(fileChar)) { /*skip empty space*/
        *cnt = *cnt + 1;
        fileChar = *(str + *cnt);
    }

    if (fileChar == '"') {/*check there is a " sign in the beggining*/
        flagStart = TRUE;
        *cnt = *cnt + 1;
        fileChar = *(str + *cnt);
    }
/*until we went to the end of the line or get over the max size line*/
    while (fileChar != '\0' && fileChar != '\n' && (*(cnt) <= 80)) {

        temp[i] = (char) fileChar;
        i++;

        *cnt = *cnt + 1;
        fileChar = *(str + *cnt);
    }
    temp[i] = '\0';
    if (*cnt >= 80)
        printError(20);/*the max size line is 80*/
    if (i == 0)
        printError(32);/*illegal string*/

    for (j = 0; j < i; j++) {
        if (temp[j] == '"')
            ch = j;
    }
    if (ch != 0)
        flagEnd = TRUE;
    findEnd(str, cnt);

    if (flagStart == FALSE || flagEnd == FALSE) {
        if (flagStart == FALSE && flagEnd == FALSE)
            printError(23);/*misiing on the both sides*/
        if (flagStart == FALSE && flagEnd == TRUE)
            printError(19);/*missing on the left side*/
        if (flagStart == TRUE && flagEnd == FALSE)
            printError(24);/*missing on the right side*/
    } else {
        /*if we got here everything is good count the IC and the DC*/
        *DC = *DC + (i);
        *IC = *IC + (i);
    }
}
