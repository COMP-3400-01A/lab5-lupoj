#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    // Declare the buffer to use. Do NOT change!
    enum { BUFSIZE = 8 };
    char buffer[BUFSIZE];
    // TODO: Complete and document

    // If no file provided, print error with exit status of 1
    if (argc < 2) {
        fprintf(stderr, "USAGE: %s FILEIN\n", argv[0]);
        return 1;
    }

    // Initialize counters for all categories
    int uppercase = 0;
    int lowercase = 0;
    int nums = 0;
    int spaces = 0;
    int others = 0;

    // Open the provided file
    int file = open(argv[1], O_RDONLY);

    // If file doesn't exist, print error with exit status of 2
    if (file < 0) {
        fprintf(stderr, "ERROR: %s not found\n", argv[1]);
        return 2;
    }

    // Initialize counter for bytes being read
    int i;

    // Read through the file and increment a category by 1 each time a match is found
    while ((i = read(file, buffer, BUFSIZE)) > 0) {
        for (int j = 0; j < i; j++) {
            char c = buffer[j];

            if (isupper(c)) {
                uppercase++;
            }
            else if (islower(c)) {
                lowercase++;
            }
            else if (isdigit(c)) {
                nums++;
            }
            else if (isspace(c)) {
                spaces++;
            }
            else {
                others++;
            }
        }
    }

    // Close the file
    close(file);

    printf("Upper,%d\n", uppercase);
    printf("Lower,%d\n", lowercase);
    printf("Number,%d\n", nums);
    printf("Space,%d\n", spaces);
    printf("Others,%d\n", others);


    return 0;
}
