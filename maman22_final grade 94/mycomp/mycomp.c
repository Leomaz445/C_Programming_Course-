/*
 * This library contain the main of the program and all the function that is working with the user input
 * and if the user input is ligal they will send it to function that will preform action and execute the the action user
 * chose or it will print and error message to the user.
 * @Leonid Mazarsky ID: 319401980
 * @24-05-202020 18:10
*/

#include "complex.h"

comp A, B, C, D, E, F; /*the 6 complex number of the program*/
/*this struct have the name and the pointers of the complex number its helps manage the and assign values*/
numberPtr compNum[] = {
        {'A', &A},
        {'B', &B},
        {'C', &C},
        {'D', &D},
        {'E', &E},
        {'F', &F},
        {'#', NULL},
};

/*the name and the function command and a pointer to the function*/
struct {
    char *name;

    void (*func)(char *, int *);

    int index;
} cmd[] = {
        {"print_comp",     checkPrint_comp,},
        {"read_comp",      checkRead_comp},
        {"add_comp",       checkAdd_comp},
        {"sub_comp",       checkSub_comp},
        {"mult_comp_real", checkMult_comp_real},
        {"mult_comp_img",  checkMult_comp_img},
        {"mult_comp_comp", checkMult_comp_comp},
        {"abs_comp",       checkAbs_comp},
        {"stop",           checkStop},
        {"Undefined command name", NULL}};

/*array that help manage and control the error message printed to the user*/

char *error[] = {
        RED"\nUndefined command name\n"REST,/*0*/
        RED"\nUndefined complex variable\n"REST,/*1*/
        RED"\nInvalid parameter - not a number\n"REST,/*2*/
        RED"\nMissing parameter\n"REST,/*3*/
        RED"\nExtraneous text after end of command\n" REST,/*4*/
        RED"\nMultiple consecutive commas\n"REST,/*5*/
        RED"\nMissing comma\n"REST,/*6*/
        RED"\nIllegal comma\n"REST,/*7*/
        RED"\nInvalid variable name\n"REST,/*8*/
        RED"\nYou didn't enter a command\n"REST,/*9*/
        RED"\nReached EOF before stop command\n"REST,/*10*/
        RED"\nUndefined complex variable,\nUse only capital letters for variables\n"REST,/*11*/
        RED"\nYou entered a number \nplease enter a complex variables\n"REST,/*12*/
        RED"\nThe second complex variable is undefended\n"REST,/*13*/

};

/*The main function of the program is taking as input of the command user putting and send it to examination*/
int main(void) {
    char str[MAX_SIZE_INPUT]; /*here the input of the command will be save*/
    char *checkEOF; /* pointer to the EOF*/
    resetComp(6, &A, &B, &C, &D, &E, &F); /*restart the complex number*/
    do {
        printf("\nHello,\nPlease Enter a command to continue:");
        checkEOF = fgets(str, MAX_SIZE_INPUT, stdin);
        if (checkEOF == NULL) {
            printf("%s", error[10]);/*Reached EOF before stop command*/
            return 0;
        }
        printf("%s", str);/*print the user input*/
        findCommand(str);/*the first validation of the command*/
    } while (TRUE); /*keeps going forever until user puts the stop command*/
}

/*This is the first validation of the command, it will find the action user want to perform
 * or print an error message, if it will find the right command it will send it there for further
 * examination and execution if valid.
 * @param str - pointer to the string user wrote
*/

void findCommand(char *str) {
    int cnt = 0; /*counter that go on the str and cheking every char*/

    int i = 0;/*counter for the while loop that count the white space before the command*/
    int j = 0; /*another counter for second while loop*/
    char newStr[COMMAND_SIZE_NAME];
    char c;

    c = *(str + i); /*get the first char*/
    while (isspace(c)) { /*while its white space continue to look for the first non white space*/
        i++;
        c = *(str + i);
    }
    cnt += i;
    while (*(str + i) != '\0' && *(str + i) != ' ' && *(str + i) != '\n' && *(str + i) != ',') {
        newStr[j] = *(str + i); /*while we did not got to the end of the command start save the command*/
        j++;
        i++;
    }

    for (i = 0; cmd[i].func != NULL; i++)/*Searching for the first command*/
        if (strncmp(cmd[i].name, newStr, strlen(cmd[i].name)) == 0)/*If we found the first command we continue*/
            break;


    if (*str == '\n') /*enter empty line */
        printf("%s", error[9]);/* it will print did not enter a command*/

    else if (cmd[i].func == NULL)/*did not found the function*/
    {

        if (*(str + cnt + j - 1) == ',') { /*if there is a comma after the command. for example: command,*/

            printf("%s", error[7]);/*Illegal comma*/
        } else
            printf("%s", error[0]);/*Undefined command name*/

    } else {
        cnt += j; /*save the exact location where are you now in the string and continue*/
        (*(cmd[i].func))(str, &cnt); /*go to the function the user wrote*/
    }
}

/*If user typed read_comp, this function will
 *send it to the check function to see that the command writen in a good way
 * and send it to the function that do the assigning
 * @param str - Pointer to a string that have the command user wrote.
 * @param cnt - the counter that works with the string*/
void checkRead_comp(char *str, int *cnt) {

    numberPtr x; /*complex number that the user entered save the name and the pointer to that variable*/
    comp newNumber; /*new complex number the user entered that he want to assign */

    if (checkReadComp(str, cnt, &x, &newNumber) == TRUE)
        read_comp(x, newNumber.rel, newNumber.im);

}

/*If user typed print_comp, this function will
 *send it to the check function to see that the command writen in a good way
 * and send it to the function that will print it.
 * @param str - Pointer to a string that have the command user wrote.
 * @param cnt - the counter that works with the string.*/
void checkPrint_comp(char *str, int *cnt) {

    numberPtr x; /*complex number that the user entered save the name and the pointer to that variable*/
    comp newNumber; /*new complex number the user entered that he want to assign */

    char name[2];
    if (checkPrintAbs(str, cnt, &x) == TRUE) {
        /*saving the info of the number before sending it to the print_comp*/
        newNumber.im = x.ptr->im;
        newNumber.rel = x.ptr->rel;
        name[0] = x.name;
        name[1] = '\0';
        print_comp(name, newNumber, 0, 0);

    }
}

/*If user typed add_comp, this function will
 *send it to the check function to see that the command writen in a good way
 * and send it to the function that do the add of the two complex number
 * @param str - pointer to a string that have the command user wrote.
 * @param cnt - pointer to  the counter that works with the string.*/
void checkAdd_comp(char *str, int *cnt) {

    numberPtr x; /*complex number that the user entered save the name and the pointer to that variable*/
    numberPtr y;/*the second complex number that a user might entered in the input command*/

    if (checkAddSubMult(str, cnt, &x, &y) == TRUE)
        add_comp(x, y);
}

/*If user typed sub_comp, this function will
 *send it to the check function to see that the command writen in a good way
 * and send it to the function that do the sub of two complex number
 * @param str - pointer to a string that have the command user wrote.
 * @param cnt - pointer to  the counter that works with the string.*/
void checkSub_comp(char *str, int *cnt) {

    numberPtr x; /*complex number that the user entered save the name and the pointer to that variable*/
    numberPtr y;/*the second complex number that a user might entered in the input command*/

    if (checkAddSubMult(str, cnt, &x, &y) == TRUE)
        sub_comp(x, y);
}

/*if user typed mult_comp_real, this function will
 *send it to the check function to see that the command writen in a good way
 * and send it to the function that do multiplication by a scalar that is real number with a complex number.
 * @param str - pointer to a string that have the command user wrote.
 * @param cnt - pointer to  the counter that works with the string.*/
void checkMult_comp_real(char *str, int *cnt) {

    numberPtr x; /*complex number that the user entered save the name and the pointer to that variable*/
    comp newNumber; /*will save the scalar user want to use*/

    if (checkMultCompScalar(str, cnt, &x, &newNumber) == TRUE)
        mult_comp_real(x, newNumber.rel);
}

/*if user typed mult_comp_img, this function will
 *send it to the check function to see that the command written in a good way
 * and send it to the function that does multiplication by a scalar that is an imaginary number with a complex number.
 * @param str - pointer to a string that have the command user wrote.
 * @param cnt - pointer to  the counter that works with the string.*/
void checkMult_comp_img(char *str, int *cnt) {

    numberPtr x; /*complex number that the user entered save the name and the pointer to that variable*/
    comp newNumber; /*will save the scalar user want to use*/

    if (checkMultCompScalar(str, cnt, &x, &newNumber) == TRUE)
        mult_comp_img(x, newNumber.rel);
}

/*if user typed mult_comp_comp, this function will
 *send it to the check function to see that the command writen in a good way
 * and send it to the function that do multiplication of two complex numbers.
 * @param str - pointer to a string that have the command user wrote.
 * @param cnt - pointer to  the counter that works with the string.*/
void checkMult_comp_comp(char *str, int *cnt) {

    numberPtr x; /*complex number that the user entered save the name and the pointer to that variable*/
    numberPtr y;/*the second complex number that a user might entered in the input command*/

    if (checkAddSubMult(str, cnt, &x, &y) == TRUE)
        mult_comp_comp(x, y);
}


/*If the user typed abs_comp, this function will
 *send it to the check function to see that the command written in a good way
 * and send it to the function that does the calculation of the absolute value of the complex.
 * @param str - pointer to a string that have the command user wrote.
 * @param cnt - pointer to  the counter that works with the string.*/
void checkAbs_comp(char *str, int *cnt) {
    numberPtr x; /*complex number that the user entered save the name and the pointer to that variable*/

    if (checkPrintAbs(str, cnt, &x) == TRUE)
        abs_comp(x);
}

/*if the user typed stop, this function will
 *send it to the check function to see that the command written in a good way
 * and send it to the function that will exit the program
 * @param str - pointer to a string that have the command user wrote.
 * @param cnt - pointer to  the counter that works with the string.*/
void checkStop(char *str, int *cnt) {
    if (chStop(str, cnt) == TRUE)
        stop();

}

/*It will check the command line for print_comp and abs_comp written in a correct way.
 * @param str - pointer to a string that have the command user wrote.
 * @param cnt - pointer to  the counter that works with the string.
 * @param x - is a pointer to the complex number the user want to print.
 * @return TRUE if its a good command line or FALSE if its bad command line*/
int checkPrintAbs(char *str, int *cnt, numberPtr *x) {
    if (findComplexNumber(str, cnt, x) != TRUE) /*find the complex number you want to print*/
        return FALSE;
    if (findEnd(str, cnt) != TRUE) /*check that the rest of the command is clear*/
        return FALSE;

    return TRUE;
}


/*It will check the command line for read_comp written in a ligal way.
 * @param str - pointer to a string that have the command user wrote.
 * @param cnt - pointer to  the counter that works with the string.
 * @param x - pointer to the complex number the user want to assign values to
 * @param newNumber - pointer to the new complex number value user want to assign
 * @return TRUE if its a good command line or FALSE if its bad command line*/
int checkReadComp(char *str, int *cnt, numberPtr *x, comp *newNumber) {
    if (findComplexNumber(str, cnt, x) != TRUE) /*find complex number to were you want to assign values*/
        return FALSE;
    if (findComma(str, cnt) != TRUE) /*find the first comma*/
        return FALSE;
    if (findNumber(str, cnt, newNumber, REAL) != TRUE) /*find the first number that is real number*/
        return FALSE;
    if (findComma(str, cnt) != TRUE) /*find another comma*/
        return FALSE;
    if (findNumber(str, cnt, newNumber, IMG) != TRUE) /*find the imaginary number*/
        return FALSE;
    if (findEnd(str, cnt) != TRUE) /*check that the rest of the command is clear*/
        return FALSE;
    return TRUE;

}

/*It will check the command line for add_comp and sub_comp and mult_comp_comp and if its a good command
 * it will return true or print an error message and return false
 * @param str - pointer to a string that have the command user wrote.
 * @param cnt - pointer to  the counter that works with the string.
 * @param x - pointer to the first complex number user want to use.
 * @param y - pointer to the second complex number user want use.
 * @return TRUE if its a good command line or FALSE if its bad command line*/
int checkAddSubMult(char *str, int *cnt, numberPtr *x, numberPtr *y) {
    if (findComplexNumber(str, cnt, x) != TRUE) /*find the complex number*/
        return FALSE;
    if (findComma(str, cnt) != TRUE) /*find the first comma*/
        return FALSE;
    if (findComplexNumber(str, cnt, y) != TRUE) /*find the second complex number*/
        return FALSE;
    if (findEnd(str, cnt) != TRUE) /*check that the rest of the command is clear*/
        return FALSE;

    return TRUE;
}

/*It will check the command line for mult_comp_img and mult_comp_real and if its a good command
 * it will return true or print an error message and return false.
 * @param str - pointer to a string that have the command user wrote.
 * @param cnt - pointer to  the counter that works with the string.
 * @param x - pointer to the complex number user want to use.
 * @param newNumber - pointer to save the value of the scalar.
 * @return TRUE if its a good command line or FALSE if its bad command line*/
int checkMultCompScalar(char *str, int *cnt, numberPtr *x, comp *newNumber) {
    if (findComplexNumber(str, cnt, x) != TRUE) /*find the complex number*/
        return FALSE;
    if (findComma(str, cnt) != TRUE) /*find the first comma*/
        return FALSE;
    if (findNumber(str, cnt, newNumber, REAL) != TRUE) /*find the scalar number*/
        return FALSE;
    if (findEnd(str, cnt) != TRUE)/*check that the rest of the command is clear*/
        return FALSE;

    return TRUE;
}

/*It will check if the command line for stop command is a legal and return true or it will return an error message
 * @param str - pointer to a string that have the command user wrote.
 * @param cnt - pointer to  the counter that works with the string.*/
int chStop(char *str, int *cnt) {
    if (findEnd(str, cnt) != TRUE)/*see if there nothing in the end of the command*/
        return FALSE;

    return TRUE;
}

/*It will find the complex variable or else print an error message
 * @param str - pointer to a string that have the command user wrote.
 * @param cnt - pointer to  the counter that works with the string.
 * @param x - pointer that will point to the one of the six 6 complex number of the program
 * return TRUE if we found the variable or false if we didnt find him*/
int findComplexNumber(char *str, int *cnt, numberPtr *x) {
    char c;/*will save the first ligal char in the string*/
    c = findComplex(str, cnt, x); /*find the first ligal char*/
    if (c == ',') {
        if (*(str + *(cnt) - 2) == ',')
            printf("%s", error[5]);/*there is two illegal commas*/
        else
            printf("%s", error[7]);/*Cheking for illegal comma*/

        return FALSE;
    }
    if (islower(c)) { /*check if its a lower case*/
        printf("%s", error[11]);/*use only capital letters for variables*/
        return FALSE;
    }
    if (isdigit(c) != 0) { /*check if its number*/
        printf("%s", error[12]);/*you entered a number please enter a variables*/
        return FALSE;
    }
    if (c != TRUE) {
        if (*(str + *(cnt)) == '\n') {
            if (isupper(*(str + (*(cnt) - 1))))
                printf("%s", error[13]);/*did not find the second  parameter*/
            else
                printf("%s", error[3]);/*missing first parameter*/
            return FALSE;
        }
        printf("%s", error[1]);/*did not find the  parameter*/
        return FALSE;
    }

    return TRUE;

}

/*It will find the comma or else print an error message
 * @param str - pointer to a string that have the command user wrote.
 * @param cnt - pointer to  the counter that works with the string.
 * return TRUE if we found the comma or false if we didnt find him*/
int findComma(char *str, int *cnt) {
    char c; /*will save the first ligal char in the string*/
    c = findChar(str, cnt);/*find the first ligal char*/
    if (c != ',') {
        if (*(str + *(cnt)) == '\n' && !isupper(c))
            printf("%s", error[3]);/*missing a parameter*/
        else
            printf("%s", error[6]);/*missing a comma*/

        return FALSE;
    }

    return TRUE;
}

/*It will find the scalar or else print an error message
 * @param str - pointer to a string that have the command user wrote.
 * @param cnt - pointer to  the counter that works with the string.
 * @param newNumber - it will save a full number if a user want to assign new number or it will use it for scalar
 * @param type - if have the value REAL or IMG and it will save the number in the specified place.
 * return TRUE if we found the scalar or false if we didnt find him*/
int findNumber(char *str, int *cnt, comp *newNumber, int type) {
    char c;/*will save the first ligal char in the string*/
    c = findChar(str, cnt);/*find the first ligal char*/
    if (c == ',') {
        printf("%s", error[5]);/*Cheking for the multiple comma*/
        return FALSE;
    }
    if (isalpha(c)) {
        printf("%s", error[2]);/*Invalid parameter - not a number*/
        return FALSE;
    }

    if (isdigit(c) == 0) {
        if (*(str + *(cnt)) == '\n') /*check if its the end of the string*/
            printf("%s", error[3]);/*missing parameter*/
        else
            printf("%s", error[2]);/*NOT A NUMBER*/

        return FALSE;
    }
    *(cnt) = *(cnt) - 1; /*go back one char*/
    if ('-' == *(str + *(cnt) - 2)) {
        if (*(str + *(cnt) - 1) == '-') /*cant be two -- one after another*/
        {
            printf("%s", error[2]);/*NOT A NUMBER*/
            return FALSE;
        }
    }
    if (type == REAL)
        newNumber->rel = validNumber(str, cnt); /*get the full number*/
    else if (type == IMG)
        newNumber->im = validNumber(str, cnt);/*get the full number*/
    return TRUE;
}

/*It will check if in the end command is ligal and there is nothing more
 * @param str - pointer to a string that have the command user wrote,approved by Juddy Issac that its not const.
 * @param cnt - pointer to  the counter that works with the string.
 * return TRUE if the end command is empty after stop or FALSE if there something more*/
int findEnd(char *str, int *cnt) {

    while (isspace(*(str + *(cnt))))
        *(cnt) = *(cnt) + 1;

    if (*(str + *(cnt)) != '\0') {
        printf("%s", error[4]);/*Extra test after end of command*/
        return FALSE;
    }


    return TRUE;
}

/*if the complex number the user entered is valid it will save the pointer to him
 * @param x - a pointer to one of the six number of the program that the user choose
 * @param c - a char that have the name of the complex number
 * return True if its was done and we found the complex number or false if we did not fount it*/
int setVariableXY(numberPtr *x, char c) {
    int i = 0;
    while (compNum[i].ptr != NULL && compNum[i].name != c)
        i++;

    if (compNum[i].name == c) {
        /*if the x variable is empty put a value inside him*/
        x->name = c;
        x->ptr = compNum[i].ptr;
        return TRUE;
    }
    return FALSE;


}

