#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

bool isNumeric(const char *str)
{
    while(*str != '\0')
    {
        if(*str < '0' || *str > '9')
            return false;
        str++;
    }
    return true;
}

int numeric(const char *str)
{
    int result = 0;
    int pos = strlen(str);

    while(pos > 0)
    {
        int dig = *(str) - 48;
        result += dig * pow(10, pos-1);
        str++;
        pos--;
    }
    return result;
}

char rotate_char(char c, int key)
{
    char nc;

    if (c > 96) // small a - z
    {
        key %= 26;

        if ( c + key > 122)
        {
            nc = (char)(96 + (key - (122-c)));
        }
        else
        {
            nc = (char) (c + key);
        }

    }
    else // caps A - Z
    {
       if ( c + key > 90)
        {
            nc = (char)(64 + (key - (90-c)));
        }
        else
        {
            nc = (char) (c + key);
        }

    }
    return nc;
}


int main(int argc, string argv[])
{

    if (argc != 2)
    {
        printf("Error");
        return 1;
    }
    if (isNumeric(argv[1]))
    {
        int key = numeric(argv[1]);
        string str = get_string("plaintext: ");
        //printf("%s", str);
        char *cptr = str;

        while (*str != '\0')
        {
            if(isalpha(*str))
            {
                char nc = rotate_char(*str, key);
                *str = nc;
                str++;
            }
            else{
                str++;
            }

            //string c =
        }
        printf("ciphertext: %s\n", cptr);
    }
    else
    {
        printf("Error");
        return 1;
    }
}