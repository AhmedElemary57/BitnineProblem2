#include "big_int.h"

BigInt* create_bigint(long long num) {
    if (num == 0) {
        BigInt* result = (BigInt*) malloc(sizeof(BigInt));
        result->size = 1;
        result->digits = (long long*) calloc(1, sizeof(long long));
        result->digits[0] = 0;
        return result;
    }

    // Calculate the number of digits required to represent the input number
    long long temp = num;
    int num_digits = 0;
    while (temp != 0) {
        num_digits++;
        temp /= BASE;
    }

    BigInt* result = (BigInt*) malloc(sizeof(BigInt));
    result->size = num_digits;
    result->digits = (long long*) calloc(num_digits, sizeof(long long));

    // Check if memory allocation was successful
    if (result == NULL || result->digits == NULL) {
        printf("Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    // Convert the input number into a big integer
    for (int i = 0; i < num_digits; i++) {
        result->digits[i] = num % BASE;
        num /= BASE;
    }

    return result;
}

void copy(BigInt* dest, BigInt* src) {
    dest->size = src->size;
    dest->digits = (long long*) realloc(dest->digits, src->size * sizeof(long long));
    for (int i = 0; i < src->size; i++) {
        dest->digits[i] = src->digits[i];
    }
}

void print_bigint(BigInt* num) {
    char* str = (char*) malloc(sizeof(char) * (num->size * 10 + 1)); // Allocate extra byte for null terminator
    if (str == NULL) {
        printf("Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    // Convert the BigInt to a string using base conversion algorithm
    int i = 0;
    BigInt* copyNum = create_bigint(0);
    copy(copyNum,num);
    while (copyNum->size > 1 || copyNum->digits[0] != 0) {
        long long remainder = 0;
        for (int j = copyNum->size - 1; j >= 0; j--) {
            long long temp = copyNum->digits[j] + remainder * BASE;
            copyNum->digits[j] = temp / 10;
            remainder = temp % 10;
        }
        str[i++] = remainder + '0';
        while (copyNum->size > 1 && copyNum->digits[copyNum->size - 1] == 0) {
            copyNum->size--;
        }
    }
    free(copyNum->digits);
    free(copyNum);

    // Reverse the string
    for (int j = 0; j < i / 2; j++) {
        char temp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = temp;
    }

    str[i] = '\0';
    printf("%s\n", str);

    free(str);
}

void destroy_bigint(BigInt* num) {
    free(num->digits);
    free(num);
}


void add(BigInt* result, BigInt* num1, BigInt* num2) {
    // Find the maximum size between the two input BigInts
    int max_size = (num1->size > num2->size) ? num1->size : num2->size;

    // Create a new BigInt to hold the result
    result->size = max_size;
    free(result->digits); // Free the memory allocated for the digits array
    result->digits = (long long*) calloc(max_size + 1, sizeof( long long ));
    // Add extra digit in case carry happens in the last addition

    // Perform the addition digit by digit
    long long carry = 0;
    for (int i = 0; i < max_size; i++) {
        long long sum = carry;
        if (i < num1->size) {
            sum += num1->digits[i];
        }
        if (i < num2->size) {
            sum += num2->digits[i];
        }
        result->digits[i] = sum % BASE;
        carry = sum / BASE;
    }

    // Handle the carry if necessary
    if (carry > 0) {
        result->digits[max_size] = carry;
        result->size++;
    }

}
