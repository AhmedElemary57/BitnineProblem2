#include <stdio.h>
#include "big_int.h"
#include <time.h>

/*
Implementing the function using normal recursion that will take O(2^n) time complexity.
I wrote more detailed explanation in the README.md file.
*/
BigInt* function_way_1(int n) {
    BigInt *sum = create_bigint(0);
    if (n == 0) {
        return create_bigint(0);
    }
    else if (n == 1) {
        return create_bigint(1);
    }
    else if (n == 2) {
        return create_bigint(2);
    }
    else {
        BigInt* result1 = function_way_1(n - 3);
        BigInt* result2 = function_way_1(n - 2);
        add( sum,result1, result2);
        destroy_bigint(result1);
        destroy_bigint(result2);
        return sum;
    }
}

/*
In the second way, I will use bottom up dynamic programming approach that will take O(n) time complexity.
I wrote more detailed explanation in the README.md file.
*/
BigInt* function_way_2(int n) {
    if (n == 0) {
        return create_bigint(0);
    }
    else if (n == 1) {
        return create_bigint(1);
    }
    else if (n == 2) {
        return create_bigint(2);
    }
    BigInt* f0 = create_bigint(0);
    BigInt* f1 = create_bigint(1);
    BigInt* f2 = create_bigint(2);
    BigInt* fn = create_bigint(0);
    for (int i = 3; i <= n; i++) {
        add(fn, f0, f1);
        copy(f0, f1);
        copy(f1, f2);
        copy(f2, fn);
    }
    destroy_bigint(f0);
    destroy_bigint(f1);
    destroy_bigint(f2);
    return fn;
}

/*
In this thierd way, I will use top down dynamic programming approach that will take O(n) time complexity.
I wrote more detailed explanation in the README.md file.
*/
#define MAX 100000000

BigInt* memo [MAX] = {NULL} ;

BigInt* function_way_3(int n) {
    // top down dynamic programming
    // base case
    if (n == 0) {
        return create_bigint(0);
    }
    else if (n == 1) {
        return create_bigint(1);
    }
    else if (n == 2) {
        return create_bigint(2);
    }
    // check if the result is already calculated
    if (memo[n] != NULL) {
        return memo[n];
    }
    BigInt* sum = create_bigint(0);
    add(sum, function_way_3(n - 2), function_way_3(n - 3));
    memo[n] = sum;
    return sum;

}

/*
In the next way I use tail recursion that will take O(n) time complexity.
I wrote more detailed explanation in the README.md file.
*/
BigInt* function_way_4(int n, BigInt *f0, BigInt *f1, BigInt *f2){
    if(n == 0){
        return f0;
    }
    else if(n == 1){
        return f1;
    }
    else if(n == 2){
        return f2;
    }
    else{
        BigInt* fn = create_bigint(0);

        add(fn,f0, f1);
        copy(f0, f1);
        copy(f1, f2);
        copy(f2, fn);
        destroy_bigint(fn);
        return function_way_4(n-1, f0, f1, f2);
    }
}



int main(){

    // ask the user to enter the number n to calculate the function
    printf("Please enter the number n to calculate the function: ");
    // scan the number n
    int n;
    scanf("%d", &n);
    // ask the user to choose the way to calculate the function
    printf("Please choose the way to calculate the function:\n");
    printf("1. Normal recursion\n");
    printf("2. Bottom up dynamic programming\n");
    printf("3. Top down dynamic programming\n");
    printf("4. Tail recursion\n");
    // scan the way
    int way;
    scanf("%d", &way);
    //calculate the function
    BigInt *result = NULL;
    int start_s = clock();
    if(way == 1){
        result = function_way_1(n);
    }
    else if(way == 2){
        result = function_way_2(n);
    }else if (way == 3)
    {
        result = function_way_3(n);
    } else if( way == 4){
        result = function_way_4(n, create_bigint(0),
                                create_bigint(1),
                                create_bigint(2));

    }
    else{
        printf("Invalid input\n");
    }
    int stop_s = clock();

    printf("The result is: ");
    print_bigint(result);
    printf("\n");
    printf("The time is: %d\n", (stop_s - start_s));
    return 0;
}
