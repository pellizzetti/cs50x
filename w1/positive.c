#include <stdio.h>

int get_positive_int(void);

int main(void) {
    int positive = get_positive_int();
    printf("%i\n", positive);
}

int get_positive_int(void) {
    int x;
    do {
        printf("Positive Integer: ");
        scanf("%i", &x);
    } while (x < 1);
    return x;
}