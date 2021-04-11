#include <stdio.h>

int get_positive_int(char* format);
void print_blocks(int height, int length);

int main(void) {
    int height = get_positive_int("Height");
    int length = get_positive_int("Length");
    print_blocks(height, length);
}

int get_positive_int(char* format) {
    int x;
    do {
        printf("%s: ", format);
        scanf("%i", &x);
    } while (x < 1);
    return x;
}

void print_blocks(int height, int length) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < length; j++) {
            printf("#");
        }
        printf("\n");
    }
}