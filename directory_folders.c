#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(void)
{
 FILE* fp;
 char* command;
 char* line;

 line = malloc(200 * sizeof(char));
 command = malloc(200 * sizeof(char));
 strcpy(command,"ls Documents");

 fp = popen(command,"r");
 while((fgets(line,  INT_MAX, fp)))
 {
  printf("%s \n",line);
 }

 return 0;
}

