/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

int main(int argc, char* argv[])
{
    if (argc != 1)
    {
        printf("Usage: don't need argument.");
        return 1;
    }
    
    // Open memory card file.
    FILE* src = fopen("card.raw", "r");
    
    if (src == NULL)
    {
        printf("Can't open file");
        return 2;
    }

    int jpg_name = 0;
    uint8_t buffer[512];
    char title[8];
    FILE* img = NULL;
        
    while(fread(buffer, 512, 1, src) == 1)
    {    
        // Read 512 bytes of a block.
        // fread(buffer, 512, 1, src);
        
        // Find beginning of jpg.
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
        {
            // Close file if it is opened.
            if (img)
                fclose(img);
            
            // Open a new jpg.
            sprintf(title, "%03d.jpg", jpg_name++);
            img = fopen(title, "w");
        }

        // Write 512 bytes if found a img.
        if (img)
            fwrite(buffer, 512, 1, img);
    }
    
    // Close the file.
    fclose(img);
    fclose(src);
    
    return 0;
}
