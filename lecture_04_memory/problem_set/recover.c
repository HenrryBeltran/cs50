#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file\n");
        return 2;
    }

    uint8_t buffer[BLOCK_SIZE];
    int n = 0;
    FILE *output = NULL;
    char *filename = malloc(8 * sizeof(char));

    // While there's still data left to read from the memory card
    while (fread(buffer, sizeof(char), BLOCK_SIZE, input))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            if (n != 0 && output != NULL)
            {
                fclose(output);
            }

            // Create JPEGs from the data
            sprintf(filename, "%03i.jpg", n);
            output = fopen(filename, "w");
            n++;
        }

        if (output != NULL)
        {
            fwrite(buffer, sizeof(char), BLOCK_SIZE, output);
        }
    }

    free(filename);
    fclose(output);
    fclose(input);
}

