#include <stdio.h>

int main(void) {
    char answer[64];
    printf("What's your name? ");
    if (fgets(answer, sizeof answer, stdin)) {
        printf("hello, %s", answer);
    }
}