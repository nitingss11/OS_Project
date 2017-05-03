#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//*******************************************
char *substr(char *str, int left)
{
char substring[strlen(str)-left+1];
  int c=left;
int sub_i=0;
 while (c <strlen(str)) {
      substring[sub_i] = str[c];
     c++;
     sub_i++;
   }
   substring[sub_i] = '\0';
   //printf("%s",substring);
 str=substring;
return str;
}

//*******************************************
 
int main() 
{char *s="<<Myname";
printf("%s",substr(s,2));
//printf("\n%s",s);
   return 0;

}
