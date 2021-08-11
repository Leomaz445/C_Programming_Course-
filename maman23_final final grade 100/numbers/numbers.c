/*
 * This program  will take as an input a number (int) and write it in as a string.
 * There is 3 main option to this program:
 * STD_IN_OUT - There is no file input so it will scan with Stdin and print with stdout.
 * STD_FILE_OUT - We will take in input using a file and the output to the stdout.
 * STD_FILE_FILE - The input will come from a file to a file.
 * @Leonid Mazarsky ID: 319401980
 * @06-06-202020 18:10
*/

#include <stdio.h>
#include <stdlib.h>

#define RED "\033[1;31m" /*color red for the printf*/
#define REST "\033[0m" /*reset color for thr printf*/

/*The three main option of the program*/
enum {
    STD_IN_OUT = 1, STD_FILE_OUT = 2, STD_FILE_FILE = 3
};


void numberProcessing(int, FILE *); /*The function that will take an input and make an output of the numbers*/
void numberWriting(int, char *[]); /*The function will get a number and print it*/

/*The main will check users will and send it to the right function*/
int main(int argc, char *argv[]) {

    switch (argc) {
        case STD_IN_OUT: /*The input will be from STDIN and the output from STDOUT*/
            numberWriting(STD_IN_OUT, NULL);
            break;
        case STD_FILE_OUT: /*The input will be from a file to STDOUT*/
            numberWriting(STD_FILE_OUT, argv);
            break;
        case STD_FILE_FILE:/*The input will be from a file to a new file*/
            numberWriting(STD_FILE_FILE, argv);
            break;
        default:
            fprintf(stderr, RED"Too many arguments,\nPlease try again.\n"REST);
    }


    return 0;

}

/*This function will open the right input and output and will try to open users file
 * @param type - in which way users will put and get the numbers.
 * @param argv - have the direction to the file user put if exists*/
void numberWriting(int type, char *argv[]) {
    FILE *fd1In = stdin; /*file that will be used as a pointer to the first file or default stdin*/
    FILE *fd2Out = stdout;/*file that will be use as a pointer to the second file or  default stdout*/
    int num; /*will save the user input*/

    if (type == STD_FILE_OUT || type == STD_FILE_FILE) { /*will try to open the first file or print an error*/
        if (!(fd1In = fopen(argv[STD_FILE_OUT - 1], "r"))) {
            fprintf(stderr, RED"Error opening the first file.\n"REST);
            exit(0);
        }
    }

    if (type == STD_FILE_FILE) { /*will open the second file or print an error*/
        if (!(fd2Out = fopen(argv[STD_FILE_FILE - 1], "w"))) {
            fprintf(stderr, RED"Error opening the second file.\n"REST);
            fclose(fd1In);/*closing the first file*/
            exit(0);
        }
    }
    while (fscanf(fd1In, "%d", &num) > 0) /*will scan each number using fscanf*/
        numberProcessing(num, fd2Out); /*send the output and the number for printing*/

    if (type == STD_FILE_OUT || type == STD_FILE_FILE) { /*closing the file we opened*/
        fclose(fd1In);/*closing the first file*/
        if (type == STD_FILE_FILE)
            fclose(fd2Out);/*closing the  second file*/
    }
}

/*This function will determine the number and print the output in the right place
 * @param num - the number user-entered or from a file.
 * @param out - a pointer to where we want to get out output.
*/
void numberProcessing(int num, FILE *out) {
    char *unitity[] = {
            "zero","one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
    };
    char *teens[] = {
            "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"
    };
    char *tens[] = {
            "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"
    };

    switch (num / 10) {
        case 0: /*this is a case were the number is  unity number*/
            fprintf(out, "%s\n", unitity[((num % 10))]);
            break;
        case 1: /*this is a case were the number is teens - from 10-19*/
            fprintf(out, "%s\n", teens[num % 10]);
            return;
        default: /*In other case were the number is 20-99*/
            if (num / 10 > 0 && num % 10 != 0)  /*if its a whole number*/
                fprintf(out, "%s %s\n", tens[((num / 10) - 2)], unitity[(num % 10)]);
            else if (num % 10 == 0) /*if its a tens number*/
                fprintf(out, "%s\n", tens[((num / 10) - 2)]);
    }


}
