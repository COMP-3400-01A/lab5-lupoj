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

    int uppercase = 0;
    int lowercase = 0;
    int nums = 0;
    int spaces = 0;
    int others = 0;

    int file = open(argv[1], O_RDONLY);

    if (file < 0) {
        perror("Error opening the file");
        return 1;
    }

    int i;

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

    close(file);

    printf("Upper,%d\n", uppercase);
    printf("Lower,%d\n", lowercase);
    printf("Number,%d\n", nums);
    printf("Space,%d\n", spaces);
    printf("Others,%d\n", others);


    return 0;
}
