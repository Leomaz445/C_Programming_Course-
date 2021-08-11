/*
 * This library contain function that doing arithmetic calculation with complex numbers:
 * Add,Sub,mult, mult a scalar with complex number, and finding the absolute value of the complex number.
 * this function have one print_comp function that printing all the expression that created in arithmetic
 * function.
 * @Leonid Mazarsky ID: 319401980
 * @24-05-202020 18:10
*/

#include "complex.h"
#include <math.h>

/*printing informative exit message and exit from the program.*/
void stop(void) {
    comp empty;
    print_comp("Exit", empty, STOP, 0);
    exit(0);
}

/*function that get a new complex number and assign it to existed complex number the user choose
 * and send it to print_comp..
@param new stores the name of the complex number and a pointer to that complex number.
@param rel is a value of the real number of the complex number.
@param im is the imaginary value of the complex number.
*/
void read_comp(numberPtr new, double rel, double im) {

    comp empty;
    char newStr[2];
    /*saving the name of the complex number*/
    newStr[0] = new.name;
    newStr[1] = '\0';

    /*calculation and printing*/
    new.ptr->rel = rel;
    new.ptr->im = im;
    print_comp(newStr, empty, READ, 0);

}

/*printing the complex number value or the expression after arithmetic calculation
@param name[] stores the name of the complex number or the expression of the calculated value
 for example A-B.
@param new the new calculated complex number or an empty number for EXIT and read_comp command.
@param parameter stores expression that needed to be printed like ABS,MULT,READ,EXIT etc..
@param scalar its saves the real or the imaginary number to be printed.
*/
void print_comp(char name[], comp new, int parameter, double scalar) {
    if (new.rel == 0) new.rel = 0;
    if (new.im == 0) new.im = 0;
    green();/*it will be printed in color green*/
/*switch case to choose the right print command*/
    switch (parameter) {
        case ABS:
            printf("The value of %s is %.2f\n", name, new.rel);
            break;
        case READ:
            printf("\nThe Number %s was added successfully.\n", name);
            break;
        case STOP:
            printf(RED"\nThank You For Using the program!\nHave A Good Day.\n"REST);
            break;
        case REAL:
        case IMG:
            if (new.im < 0)
                printf("The Value of (%.2f%s) is %.2f - (%.2f)i\n", scalar, name, new.rel, fabs(new.im));
            else
                printf("The Value of (%.2f%s) is %.2f + (%.2f)i\n", scalar, name, new.rel, new.im);
            break;
        default:
            if (new.im < 0)
                printf("The value of %s is %.2f - (%.2f)i\n", name, new.rel, fabs(new.im));
            else
                printf("The value of %s is %.2f + (%.2f)i\n", name, new.rel, new.im);
            break;
    }
    reset();


}

/*add two complex number together and sends them to print_comp for printing.
@param a representing the first complex number of which action will be preformed.
@param b representing the first complex number of which action will be preformed.
*calculation made with this formula: *(a+bi)+(c+di)=(a+c)+(b+d)i
*/
void add_comp(numberPtr a, numberPtr b) {
    comp result;
    char newName[3];
    /*building the string of the expression*/
    newName[0] = a.name;
    newName[1] = '+';
    newName[2] = b.name;
    /*calculation and printing*/
    result.rel = (a.ptr->rel) + (b.ptr->rel);
    result.im = (a.ptr->im) + (b.ptr->im);
    print_comp(newName, result, 0, 0);
}

/*sub two complex number  and sends them to print_comp for printing.
@param a representing the first complex number of which action will be preformed.
@param b representing the first complex number of which action will be preformed.
 * calculation made with this formula: *(a+bi)-(c+di)=(a-c)+(b-d)i
*/
void sub_comp(numberPtr a, numberPtr b) {
    comp result;
    char newName[3];
    /*building the string of the expression*/
    newName[0] = a.name;
    newName[1] = '-';
    newName[2] = b.name;

    /*calculation and printing*/
    result.rel = (a.ptr->rel) - (b.ptr->rel);
    result.im = (a.ptr->im) - (b.ptr->im);
    print_comp(newName, result, 0, 0);

}

/*mult two complex number  and sends them to print_comp for printing.
@param a representing the first complex number of which action will be preformed.
@param b representing the first complex number of which action will be preformed.
*calculation made with this formula: *(a+bi)*(c+di)=(ac-bd)+(ad+bc)i
*/
void mult_comp_comp(numberPtr a, numberPtr b) {
    comp result;
    char newName[3];
    /*building the string of the expression*/
    newName[0] = a.name;
    newName[1] = '*';
    newName[2] = b.name;

    /*calculation and printing*/
    result.rel = (((a.ptr->rel) * (b.ptr->rel)) - ((a.ptr->im) * (b.ptr->im)));
    result.im = (((a.ptr->rel) * (b.ptr->im) + ((a.ptr->im) * (b.ptr->rel))));
    print_comp(newName, result, 0, 0);
}

/*mult a scalar represented by real number with complex number  and sends them to print_comp for printing.
@param a representing the first complex number of which action will be preformed.
@param rel representing the real number.
*calculation made with this formula: m*(a+bi)=ma+(mb)i
*/
void mult_comp_real(numberPtr a, double rel) {
    comp result;
    char newName[2];
    /*building the string of the expression*/
    newName[0] = '*';
    newName[1] = a.name;

    /*calculation and printing*/
    result.rel = rel * (a.ptr->rel);
    result.im = rel * (a.ptr->im);
    print_comp(newName, result, REAL, rel);
}

/*mult a scalar represented by imaginary number with complex number  and sends them to print_comp for printing.
@param a representing the first complex number of which action will be preformed.
@param im representing the imaginary number.
*calculation made with this formula: mi*(a+bi)=-mb +(ma)i
*/
void mult_comp_img(numberPtr a, double im) {
    comp result;
    char newName[2];
    /*building the string of the expression*/
    newName[0] = '*';
    newName[1] = a.name;

    /*calculation and printing*/
    result.rel = im * (a.ptr->im);
    result.im = im * (a.ptr->rel);
    print_comp(newName, result, IMG, im);
}

/*finds the absolute value of the complex number.
@param a the number that on him we will be doing the calculation.
*calculation made with this formula: |a+bi|=sqrt(a^2 + b^2).
*/
void abs_comp(numberPtr a) {
    comp result;
    char newName[3];
    /*building the string of the expression*/
    newName[0] = '|';
    newName[1] = a.name;
    newName[2] = '|';

    /*calculation and printing*/
    result.im = 0;
    result.rel = sqrt(((pow(a.ptr->rel, 2) + pow(a.ptr->im, 2))));
    print_comp(newName, result, ABS, 0);

}
