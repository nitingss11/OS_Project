) #include <stdio.h>
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
/    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    { //changes to resolve parsing
        if (a_delim == *tmp &&(*(tmp+1)!=' '))
        {  
            count++;
            last_comma = tmp;
        }
/        tmp++;
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
        //changes to resolve parsing
        printf(token);
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
       printf("Disc     :\n%s", *(tokens + 0)); 
       printf("\nSize     :\n%s", *(tokens + 1)); 
       printf("\nUsed     :\n%s", *(tokens + 2)); 
       //printf("\nAvailable:\n%s", *(tokens + 3)); 
        
    }
  //printf("%s \n",line);
 }

 return 0;
}
