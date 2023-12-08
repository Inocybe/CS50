#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

 
int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./recouver IMAGE.raw\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 2;
    }

    // what i needa do is store blocks of 512 arrays
    unsigned char buffer[512];

    //counter for # of images generated
    int image_count = 0;

    //file pointer for recouvered images
    FILE *output = NULL;

    //file name lel
    char *filename = malloc(8 * sizeof(char));

    //read blocks of 512 bytes idk what I even doing send help
    while (fread(buffer, sizeof(char), 512, input))
    {
        //check to see if the byte thingies start with a jpeg, last if thingy basically is weird, it like compares each bit and like checks to see if true and false and like only returns true if both values are true
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)  
        {
            //write name
            sprintf(filename, "%03i.jpg", image_count);

            //open an output for writigin
            output = fopen(filename, "w");

            image_count++;
        }
        //check if input that has been used is valid
        if (output != NULL)
        {
            //writing adsaiudhaiudidsaiu
            fwrite(buffer, sizeof(char), 512, output);
        }
    }

    free(filename);
    fclose(output);
    fclose(input);
    
    return 0;
}