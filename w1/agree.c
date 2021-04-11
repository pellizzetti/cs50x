#include <stdio.h>

int main(void) {
    char answer[2];
    printf("Do you agree? [y/n] ");
    if (fgets(answer, sizeof answer, stdin)) {
        if (*answer == 'y' || *answer == 'Y') {
            printf("Agreed.\n");
        } else {
            printf("Not agreed.\n");
        }
    }
}