#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void collatz(unsigned long long n) {
    printf("%llu", n);
    while (n != 1) {
        if (n % 2 == 0) {
            n = n / 2;
        } else {
            n = 3 * n + 1;
        }
        printf(" , %llu", n);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return 1;
    }

    unsigned long long n = strtoull(argv[1], NULL, 10);  // <-- Convert argument

    if (n == 0) {
        fprintf(stderr, "Please enter a positive integer greater than 0\n");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        collatz(n);
        exit(0);
    } else {
        // Parent process
        waitpid(pid, NULL, 0);
    }

    return 0;
}
