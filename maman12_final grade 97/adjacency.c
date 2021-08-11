/* 
 * This program is bulding adjacency matrix and printing it and it will tell you if there is a path between 
 * the father junction and he son junction
 * @Leonid Mazarsky ID: 319401980
 * @02-05-202020 18:10
 */

#include "adjacency.h"

/*The main calling all the function and declearing the adjmat matrix*/
/*@param adjmat is a matrix of the size NxN*/
int main() {
	adjmat matrix;
	userInput(matrix);
	printMatrix(matrix);
	checkPath(matrix);
	return 0;
}

/*The user will enter the adjacency matrix*/
/*@param adjmat is a matrix of the size NxN*/
void userInput(adjmat mat) {
	int i;/*index for the for loop*/
	int j;/*index for the for loop*/
	printf("\nHello,\nThe Matrix size is: %d x %d ", N, N);
	printf("\nPleese enter the values of the matrix use only 1 or 0: \n");
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			scanf("%d", &mat[i][j]);
		}
		
	}
        printf("\n");


}

/*The function will print the matrix*/
/*@param adjmat is a matrix of the size NxN*/
void printMatrix(adjmat mat) {
	int i;
	int j;
	int k;
	printf("%11s", ""); /*the space from the begining for the upper index*/
	for (i = 0; i < N; i++) {
		green();
		printf("%5d", i);/*Printing the upper index of the matrix*/
		reset();
	}
	printf("\n");
	for (i = 0; i < N; i++)/*Printing the matrix*/
	{
		green();
		printf("%8d", i);/*Printing the side index of the matrix*/
		reset();
		printf("%5s", "|");

		for (j = 0; j < N; j++) {
			if (mat[i][j] == 0) /*if the value is 0 print it in yellow*/
			{
				yellow();
				printf("%3d ", mat[i][j]);
				reset();
			}
			if (mat[i][j] == 1)/*if the value is 1 print it in red*/
			{
				red();
				printf("%3d ", mat[i][j]);
				reset();
			}
			printf("|");
		}
		/*for the --- char between the lines*/
		printf("\n");
		printf("%13s", "");
		for (k = 0; k < N; k++)
			printf("-----");

		/*new line before printing agian*/
		printf("\t\n");

	}
}

/*The function will print the matrix*/
/*@param adjmat is a matrix of the size NxN*/
void checkPath(adjmat mat) {
	int index1;/*for the user input*/
	int index2;/*for the user input*/

	printf("\nPlese enter the father junction, and the son junction: ");
	while (scanf("%d%d", &index1, &index2) == 2
			&& (index1 != -1 || index2 != -1)) {
		/*printing in green color there is a path*/
		if (path(mat, index1, index2) == TRUE) {
			printf("\nThe result you got is ");
			green();
			printf("TRUE ");
			reset();
			printf("there is a path between ");
			green();
			printf("%d ", index1);
			reset();
			printf("and ");
			green();
			printf("%d", index2);
			reset();
			printf(".\n");
		}
		/*printing in red color there is no path*/
		else {
			printf("\nThe result you got is ");
			red();
			printf("FALSE ");
			reset();
			printf("there is NO a path between ");
			red();
			printf("%d ", index1);
			reset();
			printf("and ");
			red();
			printf("%d", index2);
			reset();
			printf(".\n");
		}
		printf("\nPlese enter the father junction, and the son junction:");
	}
	printf("\nThank you for using the program\n\n");
}

/*The function check if there is a path*/
/*@param adjmat is a matrix of the size NxN*/
/*@param u the father junction*/
/*@param v the son junction*/
/*@return TRUE if there is a path or FALSE if there is no path*/
int path(adjmat mat, int u, int v) {
	int i;

	if (u > N || u < 0 || v > N || v < 0)/*cheking the borders*/
		return FALSE;

	if (u == v)/*cheking if its the same node*/
		return TRUE;

	for (i = 0; i < N; i++) {
		if (mat[u][i] == 1 && path(mat, i, v) == TRUE)
			return TRUE;
	}

	return FALSE;

}

/*Color function*/
void red() {
	printf("\033[1;31m");
}

void yellow() {
	printf("\033[1;33m");
}

void green() {
	printf("\033[1;32m");
}
void reset() {
	printf("\033[0m");
}


