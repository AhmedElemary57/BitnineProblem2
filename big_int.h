#ifndef BIG_INT_H
#define BIG_INT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE LLONG_MAX/2-1

typedef struct BigInt {
    long long* digits;
    int size;
} BigInt;

BigInt* create_bigint(long long num);
void print_bigint(BigInt* num);
void destroy_bigint(BigInt* num);
void copy(BigInt *dest, BigInt *src);
void add( BigInt *result, BigInt* num1, BigInt* num2);

#endif /* BIG_INT_H */
