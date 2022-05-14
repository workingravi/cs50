// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N =  100003 ;    // apparently it must be in the order of the dictionary - saw this number in a page on hashing

unsigned int insert_count = 0;

// Hash table
node *table[N];


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // get hash of word and index into table

    char lword[LENGTH+1];
    int c = 0;

    while (word[c] != '\0') {
      if (word[c] >= 'A' && word[c] <= 'Z') {
         lword[c] = word[c] + 32;
      }
      else
      {
          lword[c] = word[c];
      }
      c++;
    }
    lword[c] = '\0';

    unsigned int hw = hash(lword);
    unsigned int hi = hw % N;

    // if present in table or list, return true
    if (table[hi]!=NULL)
    {
        node *tmp = table[hi];
        do
        {
            if(strcmp(lword, tmp->word)==0)
            {
                return true;
            }
            tmp = tmp->next;
        }
        while (tmp != NULL);
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{

    unsigned long hash = 5381;
    int c;

    while ((c = *word++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

int ReadLine(char *buff, int size, FILE *fp)
{
  buff[0] = '\0';
  buff[size - 1] = '\0';             /* mark end of buffer */
  char *tmp;

  if (fgets(buff, size, fp) == NULL) {
      *buff = '\0';                   /* EOF */
      return false;
  }
  else {
      /* remove newline */
      if ((tmp = strrchr(buff, '\n')) != NULL) {
        *tmp = '\0';
      }
  }
  return true;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // large or small?
    int i = 0;
    FILE *file;
    char line[LENGTH+2];


    if(dictionary[0] != '\0')
    {
        file = fopen(dictionary,"r");
    }
    else
    {
        file = fopen("dictionaries/large","r");
    }
    if(file == NULL)
    {
            return false;
    }

    // while not the end of file, read the word/line into 'line'
    while(ReadLine(line, LENGTH+2, file))
    {
    // hash it + mod N
        unsigned int word_hash = hash(line);
        unsigned int word_index = word_hash%N;


    // insert into hash
    // if collision, then add a node to next + count collisions
        if(table[word_index]==NULL)   //empty
        {
            node *tmp = malloc(sizeof(node));

            strcpy(tmp->word, line);
            tmp->next = NULL;

            table[word_index] = tmp;
            //printf("inserted %s\n", line );
            insert_count++;
            //free(tmp);
        }
        else
        {
            int tc = 1;
            node *tmp; //= malloc(sizeof(node));
            tmp = table[word_index];
            //traverse the next till we get a space and then insert
            while(tmp->next != NULL)
            {
                tmp = tmp->next;
                tc++;
            }
            // now, we can insert!
            node *tmp2 = malloc(sizeof(node));
            strcpy(tmp2->word, line);
            tmp2->next = NULL;

            tmp->next = tmp2;
            //printf("inserted as a collision%s after %d traversals\n", line, tc );
            //free(tmp);
            insert_count++;
            //free(tmp2);
        }
    }

    fclose(file);
    return true;
}



// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return insert_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{

    for (int i = 0; i < N; i++) // for each pointer
    {
        if(table[i] != NULL)    // if it has a malloced value or list of values
        {
            node *list, *tmp;
            list = table[i];
            while(list != NULL)
            {
                tmp = list->next;
                free(list);
                list = tmp;
            }
        }
    }

    return true;

}
