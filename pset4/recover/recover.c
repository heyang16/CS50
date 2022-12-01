#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
 
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover c {filename}");
        return 1;
    }
    
    int images = 0; // Initialize number of images already stored
    FILE *infile = fopen(argv[1], "r");
    FILE *outfile;
    char filename[8]; // Name of JPEG file to be stored
    uint8_t buffer[512];
    
    while (fread(&buffer, 512, 1, infile)) // Loops through file, 512 bytes at a time
    {
        // Checks for start of a JPEG file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (images > 0)
            {
                fclose(outfile); //Closes previous file
            }
            
            sprintf(filename, "%03i.jpg", images); // Sets name of new file
            images++;
            outfile = fopen(filename, "w"); //Creates a new file to write to
        }
        
        if (images > 0)
        {
            fwrite(buffer, 512, 1, outfile);
        }
    }
    fclose(outfile);
    fclose(infile);
}