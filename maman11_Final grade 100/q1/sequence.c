/* 
 * This program is getting a string from a user and prints the type of the order of the string - by ascii value
 * it will print of the screen if the program is very acceding, accending, very Descending or descending.
 * @Leonid Mazarsky ID: 319401980
 * @03-04-202020 18:10
*/
#include <stdio.h>
#include <string.h>
#define MAXLINE 101 /*maximum input line size*/

void f_sequence(char s[]);

/*prints if the string user entered and the*/
int main(void) {
	char line[MAXLINE];
	printf("\nHello,Please Enter a string, max input of 100 chars: \n");
	scanf("%100s", line); /*get only the first 100 chars*/
	printf("\nYour Line is: %s\n", line);

	f_sequence(line);

	return 0;
}
/*Prints the type of the string - very acceding,acceding,very Descending or descending
@param char s[] is a string with the user input
*/

void f_sequence(char s[]) {
	int i;
	int check = 0;/* 0 its false 1 is true*/
	int t = strlen(s);
	/*Checking if the String is null or have only one char*/
	if (t == 0 || t == 1) {
		printf("\nThis Line is: A very  UP series\n");
	}

	/*Checking if the String is in Very Acceding order*/
	check = 1;
	for (i = 1; i < t; i++) {
		if (s[i - 1] >= s[i])
			check = 0;
	}
	if (check == 1) {
		printf("\nThe series is Very Acceding order\n");
		return;
	}

	/*Checking if the String is in Acceding order*/
	check = 1;
	for (i = 1; i < t; i++) {
		if (s[i - 1] > s[i])
			check = 0;
	}
	if (check == 1) {
		printf("\nThe series is Acceding order\n");
		return;
	}

	/*Checking if the String is in very Descending order*/
	check = 1;
	for (i = 1; i < t; i++) {
		if(s[i - 1] <= s[i])
			check = 0;
	}
	if (check == 1) {
		printf("\nThe series is Very Descending order\n");
		return;
	}
	/*Checking if the String is in  Descending order*/
	check = 1;
	for (i = 1; i < t; i++) {
		if (s[i - 1] < s[i])
			check = 0;
	}
	if (check == 1) {
		printf("\nThe series is  Descending order\n");
		return;
	}
	if(check==0)
	{
		printf("\nThere is no order\n");
	}

}


