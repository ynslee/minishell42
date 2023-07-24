#include <stdio.h>
#include <signal.h>

void sig_handler(int signo) {
    if (signo == SIGINT) {
        printf("\nReceived SIGINT\n");
    }
    if (signo == SIGQUIT) {
        printf("\nReceived SIGQUIT\n");
    }
}

int main() {
    if (signal(SIGINT, sig_handler) == SIG_ERR) {
        printf("\nCannot catch SIGINT\n");
    }

    if (signal(SIGQUIT, sig_handler) == SIG_ERR) {
        printf("\nCannot catch SIGQUIT\n");
    }

    // continue to read input until EOF (Ctrl+D)
    char c;
    while ((c = getchar()) != EOF) {
        putchar(c);
    }

    return 0;
}
