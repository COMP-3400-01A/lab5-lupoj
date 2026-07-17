#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    // TODO: Complete and document

    // Declare two pointers for filenames provided in the command
    char *input = argv[1];
    char *output = argv[2];

    // If number of arguments is not 3, return error message and exit with status of 1
    if (argc != 3) {
        fputs("USAGE: partb FILEIN FILEOUT\n", stderr);
        return 1;
    }

    // Open the file that we want to direct output to
    int fd = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0770);

    // If there was an error opening the file, return error message and exit with status of 1
    if (fd < 0) {
        perror("Error opening output file");
        return 1;
    }

    // Otherwise, redirect output to the output file
    dup2(fd, STDOUT_FILENO);

    printf("Category,Count\n");
    fflush(stdout);

    // Initialize an array to represent the command line arguments
    char *parta_args[] = {"./parta", input, NULL};

    // Execute the command
    int eret = execv("./parta", parta_args);

    // If execution fails, print error message and exit with status of 1
    if (eret == -1) {
        perror("Execv failed");
        return 1;
    }

    return 0;
}
