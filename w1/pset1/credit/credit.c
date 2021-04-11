#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../utils.h"

void parse_card_number(long card_number);
int get_long_length(long card_number);

int main(void) {
    long card_number = get_long("Number: ");
    parse_card_number(card_number);
}

void parse_card_number(long card_number) {
    int card_number_length = get_long_length(card_number);
    long card_number_digits = card_number;
    int sum, digit, first_digit, issuer_code = 0;
    int i = 0;
    for (int i = 1; i <= card_number_length; i++) {
        issuer_code = first_digit;
        first_digit = card_number_digits;
        digit = card_number_digits % 10L;
        if (i % 2 == 0) {
            digit *= 2;
            if (digit > 9) {
                digit -= 9;
            }
        }
        sum += digit;
        card_number_digits /= 10L;
    }

    if (sum % 10 != 0) {
        printf("INVALID\n");
        return;
    }

    if (issuer_code > 50 && issuer_code < 56 && card_number_length == 16) {
        printf("MASTERCARD\n");
    } else if ((issuer_code == 34 || issuer_code == 37) && (card_number_length == 15)) {
        printf("AMEX\n");
    } else if (first_digit == 4 && (card_number_length == 13 || card_number_length == 16)) {
        printf("VISA\n");
    } else {
        printf("INVALID\n");
    }
}

int get_long_length(long card_number) {
    int length = 0;
    do {
        card_number = card_number / 10;
        ++length;
    } while (card_number != 0);
    return length;
}