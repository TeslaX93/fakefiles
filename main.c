#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

// Function to generate a random integer in the given range [min, max]
int random_int(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Function to generate a random string with uppercase letters
void random_string(char *str, int length) {
    for (int i = 0; i < length; i++) {
        str[i] = 'A' + rand() % 26;
    }
    str[length] = '\0';
}

void print_help() {
    printf("FakeFiles - Random File Generator\n");
    printf("=================================\n");
    printf("This program generates a list of files with random sizes and names.\n\n");

    printf("Parameters:\n");
    printf("--generate: Generates files with random content and exact names as in listing.\n");
    printf("--output: Saves the output to a results.txt file.\n");
    printf("--dir=<path>: Specifies the directory path for generating files and results.txt.\n");
    printf("--help: Displays this help message.\n");
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    char file_names[25][13]; // 8 characters for file name, 1 for '.', 3 for extension, 1 for null terminator
    int file_sizes[25];

    for (int i = 0; i < 25; i++) {
        random_string(file_names[i], 8);
        strcat(file_names[i], ".");
        random_string(file_names[i] + 9, 3);

        file_sizes[i] = random_int(1, 1474560);
    }

    int generate_files = 0;
    int save_output = 0;
    int show_help = 0;
    char dir_path[256] = ""; // Initialize dir_path to an empty string

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--generate") == 0) {
            generate_files = 1;
        } else if (strcmp(argv[i], "--output") == 0) {
            save_output = 1;
        } else if (strcmp(argv[i], "--help") == 0) {
            show_help = 1;
        } else if (strncmp(argv[i], "--dir=", 6) == 0) {
            strcpy(dir_path, argv[i] + 6); // Copy the path after "--dir=" into dir_path
        }
    }

    if (show_help) {
        print_help();
    } else if (generate_files) {
        if (dir_path[0] == '\0') {
            dir_path[0] = '.'; // Set current directory if --dir parameter is not provided
        }

        if (access(dir_path, F_OK) == -1) {
            printf("Error: Directory %s does not exist.\n", dir_path);
            return 1;
        }

        for (int i = 0; i < 25; i++) {
            char full_filename[256];
            snprintf(full_filename, sizeof(full_filename), "%s/%s", dir_path, file_names[i]);
            FILE *file = fopen(full_filename, "w");
            if (file == NULL) {
                printf("Error creating file %s\n", full_filename);
                return 1;
            }

            for (int j = 0; j < file_sizes[i]; j++) {
                fputc('A' + rand() % 26, file);
            }

            fclose(file);
            printf("Generated %s with %d bytes\n", full_filename, file_sizes[i]);
        }
    }

    if (save_output) {
        if (dir_path[0] == '\0') {
            dir_path[0] = '.'; // Set current directory if --dir parameter is not provided
        }

        if (access(dir_path, F_OK) == -1) {
            printf("Error: Directory %s does not exist.\n", dir_path);
            return 1;
        }

        char output_path[256];
        snprintf(output_path, sizeof(output_path), "%s/results.txt", dir_path);
        FILE *output_file = fopen(output_path, "w");
        if (output_file == NULL) {
            printf("Error opening the output file.\n");
            return 1;
        }

        for (int i = 0; i < 25; i++) {
            fprintf(output_file, "%-16s%8d\n", file_names[i], file_sizes[i]);
        }

        fclose(output_file);
        printf("Output saved to %s.\n", output_path);
    }

    if (!generate_files && !save_output && !show_help) {
        for (int i = 0; i < 25; i++) {
            printf("%-16s%8d\n", file_names[i], file_sizes[i]);
        }
    }

    return 0;
}
