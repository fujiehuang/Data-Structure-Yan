#ifndef STATUS_H
#define STATUS_H

#include <stdio.h>

#define TRUE        1
#define FALSE       0
#define OK          1
#define ERROR       0

#ifndef OVERFLOW
#define OVERFLOW    -2
#endif

#ifndef NULL
#define NULL ((void*)0)
#endif

typedef int Status;
typedef int Boolean;
extern Boolean debug; 

int ReadData(FILE* fp, char* format, ...);
void PressEnterToContinue(Boolean debug);
void Wait(long time);
void skipBlank(FILE* fp);

#endif
