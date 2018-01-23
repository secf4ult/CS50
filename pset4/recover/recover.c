#include <stdio.h>
#include <stdlib.h>

// FAT file system's block size is 512 bytes
#define blocksize 512

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recorver filename\n");
        return 1;
    }

    // open file to be recovered
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        fclose(file);
        fprintf(stderr, "Cannot open %s\n", argv[1]);
        return 2;
    }

    // allocate the memory for info reading
    unsigned char *buffer = malloc(blocksize);
    if (!buffer)
    {
        fprintf(stderr, "Cannot allocate memory\n");
        return 3;
    }

    int file_num = 0;
    char filename[8];
    int buffer_size;
    FILE *img = NULL;

    while (1)
    {
        buffer_size = fread(buffer, 1, blocksize, file);

        // when close to EOF, buffer returned less than 512 bytes
        if (buffer_size != 512)
        {
            break;
        }

        // check if the start of a new jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 &&
            buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // close the predecessor img file if any
            if (img)
            {
                fclose(img);
            }

            // file names ###.jpg where ### is number
            sprintf(filename, "%03i.jpg", file_num++);
            img = fopen(filename, "w");
        }
        // check if already found a jpeg
        if (img)
        {
            fwrite(buffer, 1, blocksize, img);
        }
    }

    // close the last img file
    fclose(img);

    // close file
    fclose(file);

    free(buffer);

    return 0;
}