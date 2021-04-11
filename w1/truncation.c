#include <stdio.h>

int main(void) {
    int x;
    printf("x: ");
    scanf("%i", &x);
    int y;
    printf("y: ");
    scanf("%i", &y);
    float z = x / (float)y;
    printf("%f\n", z);
}