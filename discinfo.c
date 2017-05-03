#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <string.h>
char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
   delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    { //changes to resolve parsing
        if (a_delim == *tmp &&(*(tmp+1)!=' '))
        {  
            count++;
            last_comma = tmp;
        }
       tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);
        
        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}
//*****************************trim function 
char *trim(char *str)
{
char ptr[strlen(str)+1];
int i,j=0;
for(i=0;str[i]!='\0';i++)
{
if (str[i] != ' ' && str[i] != '\t') 
ptr[j++]=str[i];
} 
ptr[j]='\0';
str=ptr;
return str;
}

//******************************
int main(void)
{
 FILE* fp;
 char* command;
 char* line;

 line = malloc(200 * sizeof(char));
 command = malloc(200 * sizeof(char));
 strcpy(command,"pydf");

 fp = popen(command,"r");
 fgets(line,  INT_MAX, fp);
 while((fgets(line,  INT_MAX, fp)))
 {  char** tokens;
     
     tokens = str_split(line, ' ');
  if (tokens)
    {  
       int token_i=0;
       while(trim(*(tokens+token_i))=="\0"){token_i++;}
       printf("\nDisc     :\n%s", *(tokens + token_i));
       token_i++;
       while(trim(*(tokens+token_i))=="\0"){token_i++;}
       printf("\nSize     :\n%s", *(tokens + token_i));
       printf("\n");
       token_i++; 
       /*while(trim(*(tokens+token_i))=="\0"){token_i++;} 
       printf("\n%s",*(tokens + token_i));
       printf("\nUsed     :\n%s", *(tokens + token_i));
       token_i++;  
       //printf("\nAvailable:\n%s", *(tokens + 3)); 
*/
        
    }

  //printf("%s \n",line);
 }

 return 0;
}
