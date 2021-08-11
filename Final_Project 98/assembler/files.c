/*
 * This is the library scanning throw the given files and creating an output if there is no errors
 * @Leonid Mazarsky ID: 319401980
 * @21-08-202020 17:27
*/

#include "assembler.h"

void makeObjectFile(char *,word *[],word *[],int *,int *); /*main function that calls the function that create and free*/
void makeExternEntryFile(char *,ptr *,int );/*make the extern and the entry file*/
FILE *createFile(char *, char *);/*create the file itself*/
void freeTable(word *[],word *[],int *,int *);/*free the tables we used*/

enum {ENTRY=2,EXTERN=3};

/*
 * The function open the given files and creating a new files if there is no error
 * @param argc - number of the argument
 * @param argv - the name of each argument
 */
void openFiles(int argc, char *argv[])
{
    FILE *fd1;/*pointer to the file that we will be opening*/
    ptr symbolList=NULL;
    int i;
    errorFlag = TRUE;/*its a global error flag, its should be TRUE always*/

    for(i=1; i < argc; i++) {
        fileName = (char *) malloc(strlen(argv[i]) + strlen(".as"));
        if (!fileName)
            printError(41);/*Error allocate memory*/
        else {
            strcpy(fileName, argv[i]);
            strcat(fileName, ".as");
            fd1 = fopen(fileName, "r");

            if (!fd1) {
                printError(0);/*Error allocate memory*/
                errorFlag = TRUE;
                continue;
            }
            /*creating an intro*/
            printf("\033[1;32m");
            printf("\n\t\t----Data of the file %s ----\n", fileName);
            printf("\033[0m;");

            if (firstPass(fd1, &symbolList) == TRUE) { /*scanning to find error and create the symbol table*/
                secondPass(fd1, &symbolList, argv[i]);/*creating the the IC Table the DC table and the extern list*/
            }

            fclose(fd1); /*closing the file*/
            free(fileName);/*free the  filename*/
        }
    }
   printf("\nThank you for using the program\n");
}

/*
 * Making the out put files
 * @param name - the name of the file that will be given
 * @param instuctionTable - the table with all the IC values
 * @param dataTable - the table with all the DC values.
 * @param IC - IC counter
 * @param DC - DC counter
 * @param symbolList - the symbol list
 * @param externList - the extern list
 */

void makeOutPutFiles(char *name ,word *instructionTable[],word *dataTable[],int *IC,int *DC,ptr *symbolList,ptr *externList)
{
    /*files created*/
    printf("\033[1;32m");
    printf("\n\t\tYour files successfully created\n");
    printf("\033[0m;");

    makeObjectFile(name,instructionTable,dataTable,IC,DC);
    makeExternEntryFile(name,symbolList,ENTRY);
    makeExternEntryFile(name,externList,EXTERN);
    freeList(symbolList);
    freeList(externList);
    freeTable(instructionTable,dataTable,IC,DC);
}
/*
 * Making the object files
 * @param name - the name of the file that will be given
 * @param instuctionTable - the table with all the IC values
 * @param dataTable - the table with all the DC values.
 * @param IC - IC counter
 * @param DC - DC counter
 */
void makeObjectFile(char *name,word *instructionTable[],word *dataTable[],int *IC,int *DC)
{
    FILE *fd1 = createFile(name, ".ob");
    /*   FILE *fd1 = fopen("data.ob", "w");*/
    int i;
    fprintf(fd1, "\t%d %d\n", *IC, *DC);
    for(i=0; i < *IC; i++)
        fprintf(fd1,"%04d %06x\n", i + START_LINE, instructionTable[i]->val);
    for(i = 0; i < *DC; i++)
        fprintf(fd1, "%04d %06x\n", i + *IC +START_LINE, dataTable[i]->val);
    fclose(fd1);
}

/*
 * Making the extern or the entern file using the list
 * @param name - the name of the file that will be given
 * @param progList - its can be the symbolList or the externList
 * @param type - hold the type of the list
 */
void makeExternEntryFile(char *name,ptr *progList,int type)
{

    FILE *fd1;
    int flag=TRUE;
    ptr p1 = *progList;

    while (p1)
    {
        if(strcmp(p1->location, instruction[type]) == 0)
        {
            if(flag==TRUE)
            {
                flag = FALSE;
                if(type == ENTRY)
                    fd1 = createFile(name, ".ent");
                else if (type==EXTERN)
                    fd1 = createFile(name, ".ext");

            }
            if(type==ENTRY)
                fprintf(fd1, "%s %d\n", p1->name, p1->address+START_LINE);
            else if (type==EXTERN)
                fprintf(fd1, "%s\t%04d\n",p1->name, p1->address+START_LINE);
        }
        p1 = p1->next;
    }
    fclose(fd1);

}

/*
 * Creating a new file were we will put the values
 * @param name - the name of the file that will be given
 * @param ending - the ending of the file name.
 */
FILE *createFile(char *name, char *ending)
{
    FILE *fd1;
    char *newName = (char *)malloc(strlen(name) + strlen(ending));
    if(!newName)
        printError(0);/*Error allocate memory*/

    strcpy(newName, name);
    strcat(newName, ending);

    fd1 = fopen(newName, "w");
    free(newName);
    return fd1;
}
/*
 * Function that free the memory we used in the tables
 * @param insturctionTable - table that hold all the word type data
 * @param dataTable - table that hold all the data of the code - int and chars
 * @param IC - IC counter
 * @parm DC - DC counter
 */
void freeTable(word *instructionTable[],word *dataTable[],int *IC,int *DC)
{
    int i;

    for(i=0; i < *IC; i++) /* Frees the instructionTable */
        free(instructionTable[i]);

    for(i = 0; i < *DC; i++) /* Frees the data_table */
        free(dataTable[i]);


}
