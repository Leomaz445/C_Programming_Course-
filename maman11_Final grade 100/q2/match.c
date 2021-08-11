/* 
 * This program is getting 2 string from a user: 1 is for the pattern and 2nd is for the text.
 * the program is lookinf from what position they have the best match.
 * @Leonid Mazarsky ID: 319401980
 * @03-04-202020 21:10
*/
#include <stdio.h>
#include <string.h>
#define MAXLINE 100 /*maximum input line size*/

int match(char str1[],char str2[]);/*the main function that getting 2 string and returning the position*/

/*prints if the string user entered and the*/

int main(void) {
	char ptr[MAXLINE];
	char text[MAXLINE];
	printf("\nPlease Enter a pattern string: \n");
	fgets(ptr,MAXLINE,stdin);
	printf("\nPlease Enter a text String:\n");
	fgets(text,MAXLINE,stdin);
	printf("\nYour pattern line is: %s\n", ptr);
	printf("\nYour pattern line is: %s\n", text);
    printf("\nThe best position is:%d\n",match(ptr,text));

	return 0;

}
/*Return the place for the best match for the both strings.
@param char str1[] - represting the pattern user puted in the input.
@param char str2[] - represting the text user puted in the input.
@return pos - represtring the best position for maximum match.
*/
int match(char str1[],char str2[])
{
	int i=0,j;
	int temp=0,min=100,pos=0;
        /*while we didnt got the the end of the text string keep adding i*/
	while(strlen(str1)+i<=strlen(str2))
	{
                /*for each position count the number the string dont match*/
		for(j=0;j<strlen(str1);j++)
		{
			if(str1[j]!=str2[j+i])
			     ++temp;

		}
                /*if the matched most of the time save the position*/
		if(min>temp) 
		{
			min=temp;
			pos=i;
		}
		temp=0;
		i++;

	}
	return pos;
}



