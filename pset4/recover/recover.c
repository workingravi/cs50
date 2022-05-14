#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

const int false = 0;
const int true = 1;
typedef uint8_t BOOL;

typedef uint8_t BYTE;

BOOL starts_with_jpeg(BYTE *block)
{
    static int fc;
    if(block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff)
    {
        if((block[3] & 0xf0) == 0xe0)
        {
            fc++;
            printf("%d\n", fc);
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover <rawfile>\n");
        return 1;
    }
    else
    {
        FILE *file = fopen(argv[1], "r");
        if(file == NULL)
        {
            printf("Error opening input file\n");
            return 1;
        }

        size_t rb = 0;
        BYTE fcount = 0; //filenames start with 0

        char jpg_filename[8];
        //sprintf(jpg_filename, "%03i%s", (int)fcount, ".jpg");

        BYTE *block = (BYTE *)malloc(512*sizeof(BYTE));
        FILE *curr_jpg_file = NULL;
        BOOL writing = false;

        //while not end of file - some say it's the wrong way...so making it a do while
        do
        {
            //read 512 bytes at a time
            rb = fread(block, sizeof(BYTE), 512, file);
            if(rb == 512)
            {
                //check if they start with a jpeg sig
                if(starts_with_jpeg(block))
                {
                    writing = true;

                    //if a file was open, close it and open new one
                    if(curr_jpg_file != NULL)
                    {
                        fclose(curr_jpg_file);
                        fcount++;
                    }

                    sprintf(jpg_filename, "%03d.jpg", fcount);
                    curr_jpg_file = fopen(jpg_filename, "a");

                    if (fwrite(block, sizeof(BYTE), rb, curr_jpg_file) != rb)
                    {
                        printf("Error wrting file\n");
                        return 1;
                    }
                }

                else
                {
                    // write byes to old one...
                    if (writing)
                    {
                        if (fwrite(block, sizeof(BYTE), rb, curr_jpg_file) != rb)
                        {
                            printf("Error wrting file\n");
                            return 1;
                        }
                    }

                }

            }
            if (rb != 0 && rb != 512)
            {
                printf("Error reading file\n");
                return 1;
            }
        }
        while(!feof(file));

        free(block);
    }
}
