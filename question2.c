#include <stdio.h>


/*
Implementing the function using normal recursion that will take O(2^n) time complexity.
I wrote more detailed explanation in the README.md file.
*/
unsigned long long function_way_1(int n){
    if(n == 0){
        return 0;
    }
    else if(n == 1){
        return 1;
    }
    else if(n == 2){
        return 2;
    }
    else{
        return function_way_1(n-3) + function_way_1(n-2);
    }
}

/*
In the second way, I will use bottom up dynamic programming approach that will take O(n) time complexity.
I wrote more detailed explanation in the README.md file.
*/
unsigned long long function_way_2(int n){
    unsigned long long f0 = 0;
    unsigned long long f1 = 1;
    unsigned long long f2 = 2;
    if( n == 0){
        return f0;
    }
    else if(n == 1){
        return f1;
    }
    else if(n == 2){
        return f2;
    }
    unsigned long long fn = 0;
    for(int i = 3; i <= n; i++){
        fn = f0 + f1;
        f0 = f1;
        f1 = f2;
        f2 = fn;
    }
    return fn;

}

/*
In this thierd way, I will use top down dynamic programming approach that will take O(n) time complexity.
I wrote more detailed explanation in the README.md file.
*/
#define MAX 176

unsigned long long memo[MAX]= {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1, -1, -1, -1};

unsigned long long function_way_3(int n){
    if(n == 0){
        return 0;
    }
    else if(n == 1){
        return 1;
    }
    else if(n == 2){
        return 2;
    }
    else{
        if(memo[n] != -1){
            return memo[n];
        }
        else{
            memo[n] = function_way_3(n-3) + function_way_3(n-2);
            return memo[n];
        }
    }    
}

/*
In the next way I use tail recursion that will take O(n) time complexity.
I wrote more detailed explanation in the README.md file.
*/

unsigned long long function_way_4(unsigned long long n, unsigned long long f0, unsigned long long f1, unsigned long long f2){
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
        return function_way_4(n-1, f1, f2, f0+f1);
    }
}

int main(){
   // ask the user to enter the number n to calculate the function
    printf("Please enter the number n to calculate the function (0 < n < 156): ");
    // scan the number n
    int n=150;
    scanf("%d", &n);
    if(n < 0){
        printf("The number n must be positive.\n");
        return 0;
    }
    if(n > 156){
        printf("The number n must be less than 156.\n");
        return 0;
    }
    // ask the user to choose the way to calculate the function
    printf("Please choose the way to calculate the function:\n");
    printf("1. Normal recursion\n");
    printf("2. Bottom up dynamic programming\n");
    printf("3. Top down dynamic programming\n");
    printf("4. Tail recursion\n");
    // scan the way
    int way;
    scanf("%d", &way);
    // calculate the function
    unsigned long long result;
    if(way == 1){
        result = function_way_1(n);
    }
    else if(way == 2){
        result = function_way_2(n);
    }
    else if(way == 3){
        result = function_way_3(n);
    }
    else if(way == 4){
        result = function_way_4(n, 0, 1, 2);
    }
    // print the result
    printf("The result is: %lld\n", result);
    return 0;
}