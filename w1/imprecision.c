#include <stdio.h>

int main(void) {
    float x;
    printf("x: ");
    scanf("%f", &x);
    float y;
    printf("y: ");
    scanf("%f", &y);
    printf("%.50f\n", x / y);
}