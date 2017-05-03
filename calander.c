#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <string.h>

int main(void)
{
 FILE* fp;
 char* command;
 char* line;

 line = malloc(200 * sizeof(char));
 command = malloc(200 * sizeof(char));
 strcpy(command,"cal");

 fp = popen(command,"r");
 
 while((fgets(line,  INT_MAX, fp)))
 { 
  printf("%s \n",line);
 }

 return 0;
}
