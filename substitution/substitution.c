#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


string get_cipher(string pt, string key)
{
    string ct = pt;
    int i = 0;
    char c;

    while((c = pt[i]) != '\0')
    {
        int tch = 0;
        // for each character, get its corresponding index in key
        if (isalpha(c))
        {
            if(isupper(c))
            {
                tch = (int)c - 65;
                ct[i] = toupper(key[tch]);
            }
            else
            {
                tch = (int)c - 97;
                ct[i] = tolower(key[tch]);

            }
        }

        i++;
    }
    return ct;

}

bool is_invalid(string key)
{


    if(strlen(key) != 26)
    {
        return true;
    }

    bool once_only[26]; // to check for repeated chars - not sure if there is a better way
    for (int i = 0; i < 26; i++)
    {
        once_only[i] = false;
    }

    for (int i = 0; i < 26; i++)
    {
        if (!isalpha(key[i])){
            return true;
        }
        int index = toupper(key[i]) - 65;
        if (!once_only[index])
        {
            once_only[index] = true;
        }
        else
        {
            // this letter came earlier
            return true;
        }
    }
    return false;   // can use this key!
}

int main(int argc, string argv[])
{
    // Check input format here...

    if (argc != 2)
    {
        printf("%s\n", "Usage: ./substitution key");
        return 1;
    }
    string key = argv[1];
    if (is_invalid(key))
    {
        printf("%s\n", "Key must be alphabetic of exactly 26 letters, each occuring once");
        return 1;
    }


    // If all ok, get the plaintext
    string pt = get_string("PlainText: ");

    printf("ciphertext: %s\n",get_cipher(pt, key));
}
