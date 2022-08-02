#include "helpers.h"

static char *reverse_string(char *word);
static int find_str_num(char *str, char *sep);
static void str_cut(char *str, char cut);

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

string_array *my_split(char *str, char *sep)
{
    // set up the struct that will be returned
    string_array *structPtr;
    structPtr = malloc(sizeof(string_array));
    if (structPtr == NULL)
        printf("Error\n");

    // find how many separated strings there will be
    int size = find_str_num(str, sep);
    structPtr->size = size + 1;
    structPtr->array = (char**)malloc(sizeof(char*) * size);

    // if input is empty
    if (*str == '\0' && *sep == '\0')
    {
        structPtr->size = 1;
        structPtr->array[0] = str;
        return structPtr;
    }    

    int i = 0;
    int j;
    int strCount = 0;
    int len = my_strlen(str) + 1;

    // go through input string, malloc space for each output string and assign chars till sep is hit
    while (str[i] != '\0')
    {   
        structPtr->array[strCount] = (char*)malloc(sizeof(char) * len);
        for (j = 0; str[i] != *sep && str[i] != '\0'; j++)
        {
            structPtr->array[strCount][j] = str[i];
            i++;
        }
        structPtr->array[strCount][j] = '\0';
        strCount++;
        if (str[i]) i++;
    }
    return structPtr;
}

static int find_str_num(char *str, char *sep)
{
    int strNum = 0;
    if (str && *str != '\0')
        strNum = 1;

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == *sep && str[i + 1] != '\0')
            strNum++;
    }
    return strNum;
}

char *my_readline(int fd)
{
    // guard against wrong use
    if (fd < 0) return NULL;

    // set up strings
    char *line = malloc(sizeof(char) * MAX_SIZE);
    my_memset(line, '\0', MAX_SIZE - 1);

    char tmp[MAX_SIZE];
    tmp[0] = '\0';

    char buff[READLINE_READ_SIZE + 1]; 
    
    if (STORAGE && STORAGE[0] == '\n')
    {
        // skip the newline, then copy storage to line first
        STORAGE++;
        my_strcat(line, STORAGE);
        // flush storage
        my_memset(STORAGE, '\0', my_strlen(STORAGE));
    }

    int read_bytes;
    while ((read_bytes = read(fd, buff, READLINE_READ_SIZE)) > 0)
    {
        if (read_bytes == -1) return NULL;
        
        buff[read_bytes] = '\0';
        // check if newline is present and copy everything from newline to storage for later use
        if (my_strchr(buff, '\n') != NULL)
        {
            char *rest = my_strchr(buff, '\n');
            STORAGE = my_strdup(rest);
            my_strcat(tmp, buff);
            break;
        }
        // put everything read into tmp string
        my_strcat(tmp, buff);
    }
    // cut temp string before newline, then append to line
    str_cut(tmp, '\n');
    my_strcat(line, tmp);

    if (my_strlen(line) == 0 && read_bytes == 0)
        return NULL;
    
    return line;
}

static void str_cut(char *str, char cut)
{
    // cut newline and replace with terminating 0
    for (size_t i = 0; str[i]; i++)
    {
        if (str[i] == cut)
        {
            str[i] = '\0';
            return;
        }
    }
}