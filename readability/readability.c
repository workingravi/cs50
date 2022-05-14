#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <ctype.h>


int get_grade(string s)
{
    int grade = 1;
    int l = 0, sents = 0, w = 1;
    int i = 0;
    float L = 0.0, S = 0.0;
    char c;

    while((c = s[i]) != '\0')
    {
        if (c == ' ')
        {
            w += 1; // spaces delimit words
        }
        else if (isalpha(c))
        {
            l++;
        }
        else if (c == '.' || c == '!' || c == '?')
        {
            sents += 1; //sentences are delimited by 3 chars
        }

        i++;    // avoid the infinite! :)
    }

    printf("%d words\n", w);
    printf("%d sents\n", sents);
    printf("%d letss\n", l);


    L = 100 * (float)l / w;
    S = 100 * (float)sents / w;

    printf("%f = L\n", L);
    printf("%f = S\n", S);

    grade = round(0.0588 * L - 0.296 * S - 15.8);

    return grade;
}

int main(void)
{
    string s = get_string("Text: ");

    int res = get_grade(s);

    if (res < 1){
        printf("Before Grade 1\n");
    }
    else if (res > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", res);
    }
}
