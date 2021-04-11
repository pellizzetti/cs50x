#include <stdio.h>
#include <string.h>

#include "../../utils.h"

int get_positive_int(void);
void print_blocks(int height);
void append(char* s, char c);

int main(void) {
    int height = get_positive_int();
    print_blocks(height);
}

int get_positive_int(void) {
    int x;
    do {
        x = get_int("Height: ");
    } while (x < 1 || x > 8);
    return x;
}

void print_blocks(int height) {
    char whitespace_list[9] = {0x00};
    char whitespace = ' ';
    char block_list[8] = {0x00};
    char block = '#';
    for (int i = 0; i < height; i++) {
        for (int j = 1; j <= height - i - 1; j++) {
            append(whitespace_list, whitespace);
        }
        for (int j = 0; j < i + 1; j++) {
            append(block_list, block);
        }
        printf("%s%s  %s\n", whitespace_list, block_list, block_list);
        memset(block_list, 0, sizeof(block_list));
        memset(whitespace_list, 0, sizeof(whitespace_list));
    }
}

void append(char* s, char c) {
    int len = strlen(s);
    s[len] = c;
    s[len + 1] = '\0';
}