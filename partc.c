#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    // TODO: Complete and document

    // Check for sufficient command-line arguments
    if (argc < 2) {
        fputs("USAGE: ./partc FILEIN \n", stderr);
        return 1;
    }

    // Create the pipe
    int pipe_read_fd[2];

    // Ensure pipe is valid
    if (pipe(pipe_read_fd) < 0) {
        perror("pipe failed");
        return 1;
    }

    // Create the child process
    pid_t pid = fork();

    // If Parent, close the read end of pipe and redirect STDOUT to the pipe's write end
    // and execute parta with the name of the input file
    //
    // If Child, close the write end of the pipe and redirect STDIN to the pipe's read end
    // and execute sort with all of the formatting arguments.
    if (pid > 0) {
        close(pipe_read_fd[0]);
        dup2(pipe_read_fd[1], STDOUT_FILENO);

        char *a_args[] = {"./parta", argv[1], NULL};
        execv("./parta", a_args);

        perror("execv parta failed");
        return 1;
    }
    else {
        close(pipe_read_fd[1]);
        dup2(pipe_read_fd[0], STDIN_FILENO);

        char *sort_args[] = {"sort", "-t,", "-k2", "-n", NULL};
        execv("/usr/bin/sort", sort_args);

        perror("execv sort failed");
        return 1;
    }
    return 0;
}
