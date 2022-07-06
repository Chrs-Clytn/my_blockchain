#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int my_strlen(char *str)
{
    int counter = 0;
    while(str[counter] != '\0')
        counter++;    
    return counter;
}

void my_strcpy(char *dst, char *src)
{
    // create a pointer pointing to the beginning of the destination string's address
    int i = 0;
    while(src[i] != '\0')
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = src[i];
}

char *my_strdup(char *str)
{
    int size;
    char *dupStr;
    size = my_strlen(str) + 1;

    dupStr = (char*)malloc(sizeof(char) * size);
    if(dupStr == NULL)
    {
        // printf("malloc of size %d failed!\n", size);
        return NULL;
    }
    for(int i = 0; i < size; i++)
        dupStr[i] = str[i];
    dupStr[size-1] = '\0';
    
    /*  while(*str) {       // the same thing
        *ptr++ = *str++;
    }
    *ptr = '\0'; */
    return dupStr;   
}

int my_strcmp(char *s1, char *s2) 
{
    while (*s1)
    {
        // if characters differ, or end of the second string is reached
        if (*s1 != *s2)
            break;

        // move to the next pair of characters
        s1++;
        s2++;
        // return the ASCII difference after converting `char*` to `unsigned char*`
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}                  

void my_strcat(char *dest, char *src)
{
    while(*dest) dest++;
    while((*dest++ = *src++));
    --dest;
}

void my_memset(char *str, char c, int n)
{
    int i = 0;
    for (; i < n; i++)
        str[i] = c;
    
    str[i] = '\0';
}

int my_putchar(char c)
{
    return write(1, &c, 1);
}

void my_putstr(char *string)
{
    while(*string)
    { 
        my_putchar(*string);
        string++;
    }
}