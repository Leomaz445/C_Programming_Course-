/*
 * This library contain function that help analyzing the string the user entered
 * the main purpose of the function is going char by char and look for valid an ligal chars
 * and return them to the function that called them.
 * @Leonid Mazarsky ID: 319401980
 * @24-05-202020 18:10
*/

#include "complex.h"
#include <stdarg.h>


/*Will find a legal number user puts in the input it will scan char by char
 * @param str - pointer to a string that have the command user wrote,approved by Juddy Issac that its not const
 * @param cnt - pointer to the counter that works with the string
 * @return returnNum - a new number that was found in the user input*/
double validNumber(char *str, int *cnt) {
    double newNum; /*the number we will return*/
    char c; /*save the specific char of the input string*/
    int i = 0;
    char temp[sizeof(double)];/*will save up to 8 chars*/
    int dotCounter = 0; /*counter for the dot in the expression if there 2 dots its not ligal */
    int plusCounter = 0;/*counter the + sign in the string more that 2 is not ligal*/
    int minusCounter = 0;/*counter of the - sign more that 2 in not ligal*/

    /*cheking for the minus sign two spots before the number like -.543 */
    if ('-' == *(str + *(cnt) - 2)) {
        temp[i] = '-';
        i++;
        minusCounter++;
        temp[i] = '0';
        i++;
        temp[i] = '.';
        i++;
        dotCounter++;

        /*cheking for a dot before a number like .5*/
    } else if ('.' == *(str + *(cnt) - 1)) {
        temp[i] = '0';
        i++;
        temp[i] = '.';
        i++;
        dotCounter++;

        /*cheking for a minus before a number like -5.6*/
    } else if ('-' == *(str + *(cnt) - 1)) {
        temp[i] = '-';
        minusCounter++;
        i++;
    }
    /*while we didnt got to the end of string or the end of the string and didnt see any space or comma
     * keep working*/

    while (((*(str + *(cnt)) && (isspace(*(str + *(cnt)))) == 0)) && (*(str + *(cnt)) != ',') &&
           (*(str + *(cnt)) != '\n' && i < sizeof(double) - 1)) {
        c = *(str + *(cnt));/*save the char in the position str+cnt*/
        switch (c) {
            case '.':
                if (++dotCounter > 1)
                    return FALSE;
                break;
            case '+':
                if (++plusCounter)
                    return FALSE;
                break;

            case '-':
                if (++minusCounter > 1)
                    return FALSE;
                break;
            default:
                if (c < '0' || c > '9')
                    return FALSE;
        }
        temp[i] = *(str + *(cnt));/*if its valid number save it*/
        i++;
        *(cnt) = *(cnt) + 1;
    }
    temp[i] = '\0';
    if (i == sizeof(double) - 1) /*if the number is to big(to many digits) we will skip the other digits*/
    {
        while (isdigit(*(str + *(cnt)))) {
            *(cnt) = *(cnt) + 1;
        }
    }

    newNum = atof(temp);/*if we got to here the number is valid and covert him to double*/


    return newNum;
}

/*Will find a ligal complex number or return an illegal char
 * @param str - pointer to a string that have the command user wrote,approved by Juddy Issac that its not const
 * @param cnt - pointer to the counter that works with the string
 * @param x - pointer to the complex were we will save users complex number he asks for
 * return it will return a the invalid char or it will return 0 or 1*/
char findComplex(char *str, int *cnt, numberPtr *x) {
    char c;
    c = *(str + *(cnt));
    /*while we did not get to the end*/
    while (c != '\0' && c != '\n') {
        if (isalpha(c) || isdigit(c) || c == ',') {
            *(cnt) = *(cnt) + 1;
            if (islower(c) || isdigit(c) || c == ',') /*is a char and its a lower case*/
                return c; /*not valid because it lower case*/


            return (char) setVariableXY(x, c);
        }

        *(cnt) = *(cnt) + 1;
        c = *(str + *(cnt)); /*move to the next char in the string*/
    }

    return (char) FALSE;/*did not find ligal char return false*/
}

/*Will find a ligal char and return it or return false
 * @param str - pointer to a string that have the command user wrote,approved by Juddy Issac that its not const
 * @param cnt - pointer to the counter that works with the string
 * return c - is the char we found or return false if we did not find anything*/
char findChar(char *str, int *cnt) {
    char c;
    c = *(str + *(cnt));
    /*while we did not get to the end*/
    while (c != '\0' && c != '\n') {
        if (isdigit(c) || c == ',' || isalpha(c)) {
            *(cnt) = *(cnt) + 1;
            return c;/*return the valid char*/
        }
        *(cnt) = *(cnt) + 1;
        c = *(str + *(cnt)); /*move to the next char in the string*/
    }
    return (char) FALSE;/*did not find ligal char return false*/
}


/*function the reset the complex numbers.
@param i representing how many complex number you want to reset.
@param ... the complex number you want to reset
*/
void resetComp(int i, ...) {
    va_list p; /*start of the list*/
    comp *ptr; /*pointer to the comp number*/
    va_start(p, i);
    while (i != 0) { /*keep reset them while have numbers*/
        ptr = (comp *) va_arg(p, comp*);
        ptr->im = 0;
        ptr->rel = 0;
        i--;
    }
    va_end(p);

}


/*Color function*/
void green() {
    printf("\033[1;32m");
}

void reset() {
    printf("\033[0m");
}
