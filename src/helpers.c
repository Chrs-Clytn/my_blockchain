#include "helpers.h"

static char *reverse_string(char *word);

int my_atoi(char *str)
{
    if (str == NULL)
        return 0;

    for (int i = 0; str[i] != '\0'; i++)
        if (!((str[i] >= '0' && str[i] <= '9') || str[i] == '-'))
            return 0;

    int i = 0;
    int sign = 1;
    // If number is negative, then update sign; the sign is added in return step at the end of the function
    if (str[0] == '-')
    {
        sign = -1;
        i++; // update i, so the following loop skips the negative sign if it's there
    }

    int result = 0;
    for (; str[i] != '\0'; i++)
    {
        result = result * 10;           // multiplication by 10 is for always keeping 1st digit on the left pos of result
        result = result + str[i] - '0'; // take ASCII character of corresponding digit in str and subtract '0' to get numerical value
    }
    return result * sign;
}

char* my_itoa(int num)
{
    // find number of digits
    int len = 0;
    long numCopy = num;
    do {
        len++;
        numCopy /= 10;  // for decimal nbrs
    } while (numCopy != 0);

    char* str = malloc(sizeof(int) * len);
    int i = 0;
    bool isNegative = false;
 
    // handle 0 explicitly, otherwise empty string is printed for 0
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
 
    // in standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if(num < 0)
    {
        isNegative = true;
        num = -num;
    }
 
    // process individual digits
    while (num != 0)
    {
        int rem = num % 10;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/10;
    }
 
    // if number is negative, append '-'
    if(isNegative)
        str[i++] = '-';
 
    str[i] = '\0'; // append string terminator
 
    // reverse the string
    reverse_string(str);
    return str;
}

static char *reverse_string(char *word)
{
    int length, c;
    char *begin, *end;
    
    length = my_strlen(word);
    begin  = word;  // gives begin the same address as word
    end    = word;  // gives end the same address as word
    
    for(c = 0; c < length - 1; c++)
        end++;          // -1 because the last cell contains the

    for(c = 0; c < length/2; c++) // if odd number, the middle letter stays the same  
    {      
        char temp;
        temp   = *end;     
        *end   = *begin;   
        *begin = temp;
    
        begin++;
        end--;
    }
    return word;
}