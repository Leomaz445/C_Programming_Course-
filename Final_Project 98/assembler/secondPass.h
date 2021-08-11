#include "assembler.h"

#define INSTRUCTION_TABLE_LEN 500
#define DATA_TABLE_LEN 200

void secondPassLine(char*,ptr *,ptr *, word *[],word *[],int *,int *);/*the main function that go throw each line*/
void SPcheckIfInstruction(char *,int *,ptr *,word *[],int *);/*the function analyzing the insturction that been given*/
void SPcheckIfLabelOrOpcode(char *,int *,ptr *,ptr *,word *[],int *,int *);/*the function analyzing the label or the opcode*/
void getDataString(char *,int *,word *[],int *);/*getting and couting the chars from the string*/
void getDataInteger(char *,int *,word *[],int *);/*getting and counting the numbers*/