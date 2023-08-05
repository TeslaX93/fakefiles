#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function to generate a random integer in the given range [min, max]
int random_int(int min, int max)
{
    return min + rand() % (max - min + 1);
}

// Function to generate a random string with uppercase letters
void random_string(char *str, int length)
{
    for (int i = 0; i < length; i++)
    {
        str[i] = 'A' + rand() % 26;
    }
    str[length] = '\0';
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    char file_names[25][13]; // 8 characters for file name, 1 for '.', 3 for extension, 1 for null terminator
    int file_sizes[25];

    for (int i = 0; i < 25; i++)
    {
        random_string(file_names[i], 8);
        strcat(file_names[i], ".");
        random_string(file_names[i] + 9, 3);

        file_sizes[i] = random_int(1, 1474560);
    }

    if (argc == 2 && strcmp(argv[1], "--output") == 0)
    {
        FILE *output_file = fopen("results.txt", "w");
        if (output_file == NULL)
        {
            printf("Error opening the output file.\n");
            return 1;
        }

//        fprintf(output_file, "Filename         Size\n");
        for (int i = 0; i < 25; i++)
        {
            fprintf(output_file, "%-16s%8d\n", file_names[i], file_sizes[i]);
        }

        fclose(output_file);
        printf("Output saved to results.txt.\n");
    }
    else if(argc == 2 && strcmp(argv[1], "--help"))
    {
        printf("FakeFiles - generates list of fake files. Use with --output to write to file.\n");
        printf("MIT License, https://teslax93.github.io");
    }
    else
    {
        for (int i = 0; i < 25; i++)
        {
            printf("%-16s%8d\n", file_names[i], file_sizes[i]);
        }
    }

    return 0;
}
