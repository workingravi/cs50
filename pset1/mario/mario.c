#include<stdio.h>
#include<cs50.h>
void spaces(int n)
{
    for (int i = 0; i < n; i++){
        printf("%c", ' ');
    }
}
void hashes(int n)
{
    for (int i = 0; i < n; i++){
        printf("%c", '#');
    }
}
int main(void)
{
    int ht = 0;
    do{
        ht = get_int("Height:");
    }while ((ht < 1) || (ht > 8));


    for (int i = 0; i < ht; i++)
    {
        spaces(ht-(i+1));
        hashes(i+1);
        printf("\n");
    }
}