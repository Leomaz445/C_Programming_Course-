#include "assembler.h"
/*
 *
 */
int main(int argc, char *argv[])
{
    if(argc==1)
        printError(47);
    else
    openFiles(argc, argv);


    return 0;
}
