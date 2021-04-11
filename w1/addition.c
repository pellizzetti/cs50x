#include <stdio.h>

int main(void) {
    long x;
    printf("x: ");
    scanf("%li", &x);
    long y;
    printf("y: ");
    scanf("%li", &y);
    printf("%li\n", x + y);
}