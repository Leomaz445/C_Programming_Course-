#include "assembler.h"
int legalTwoParam(char *, int *, param *, param *, int );
int legalOneParam(char *, int *, param *, param *, int );
int legalZeroParam(char *, int *, param *, param *, int );
int findParam(char *, int *, param *, int );
int checkParameter(char *, int *, char *);
int emptyLabel(char *, int *);
void analysisLine(char *, ptr *, int *, int *);
void checkIfLabelOrOpcode(char *, int *, ptr *, int *, label *);
void checkIfInstruction(char *, int *, ptr *, int *, int *, label *);
void checkInstruction(char *, int *, ptr *, int *, int *, label *, int );
void checkTwoParam(char *, int *, int *IC, int indexOp);
void checkOneParam(char *str, int *cnt, int *IC, int opCode);
void checkZeroParam(char *str, int *cnt, int *IC, int opCode);
void checkDataInteger(char *str, int *cnt, int *DC, int *IC);
void checkDataString(char *str, int *cnt, int *DC, int *IC);
void findComplexError(char *str, int *cnt);
