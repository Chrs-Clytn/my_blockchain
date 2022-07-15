#include "helpers.h"
#include "string_mgmt.h"

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