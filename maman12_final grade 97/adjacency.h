#include <stdio.h>
#define N 11
enum boolean {FALSE,TRUE};
typedef int adjmat[N][N];

int path(adjmat mat,int u,int v);/*returning if there is a path between u and v*/
void userInput(adjmat mat);/*will resive the user input of the matrix*/
void printMatrix(adjmat mat);/*will print the matrix*/
void checkPath(adjmat mat);/*will ask the user to enter 2 digit of the junction to see if there is a path*/

/*coloring function*/
void red();
void yellow();
void green();
void reset();

