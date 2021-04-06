#include <stdio.h>

typedef struct _mixedFraction {
    long int integerPart;
    long int nominator;
    long int denominator;
} mixedFraction;

long int gcd(long int num1, long int num2);
void convertToMixed(mixedFraction *num);
void convertToProper(mixedFraction *num);
void initializeMixed(mixedFraction *num);
void print(mixedFraction num);
void addition(mixedFraction *pResult, mixedFraction num1, mixedFraction num2);
void subtraction(mixedFraction *pResult, mixedFraction num1, mixedFraction num2);
void multiplication(mixedFraction *pResult, mixedFraction num1, mixedFraction num2);
void division(mixedFraction *pResult, mixedFraction num1, mixedFraction num2);

long int gcd(long int num1, long int num2) {
    long int i = 0;

    if(num1 < 0) {
        num1 *= -1;
    }
    if(num2 < 0) {
        num2 *= -1;
    }

    while(num2 != 0) {
        i = num1%num2;
        num1 = num2;
        num2 = i;
    }

    return i;
}

void convertToMixed(mixedFraction *num) {
    int sign = 1;

    if(num->integerPart < 0) {
        num->integerPart *= -1;
        sign = -1;
    }    
   
    num->nominator += (num->denominator*num->integerPart)*sign;
    num->integerPart = 0;

    return;
}

void convertToProper(mixedFraction *num) {
    int sign = 1;

    //print(*num);
    if(num->nominator < num->denominator) {
        return; //nothing to convert
    }

    if(num->nominator < 0) {
        num->nominator *= -1;
        sign = -1; //it is negative
    }

    num->integerPart = (long int)((num->nominator/num->denominator)*sign);
    num->nominator -= num->integerPart*num->denominator;

    return;
}

void initializeMixed(mixedFraction *num) {
    num->integerPart = 0;
    num->nominator = 0;
    num->denominator = 0;
}

void print(mixedFraction num) {
    printf("(%d,%d,%d)\n", num.integerPart, num.nominator, num.denominator);
}

void addition(mixedFraction *pResult, mixedFraction num1, mixedFraction num2) {
    initializeMixed(pResult);
    convertToMixed(&num1);
    convertToMixed(&num2);

    pResult->nominator = (num1.nominator*num2.denominator) + (num2.nominator*num1.denominator);
    pResult->denominator = num1.denominator*num2.denominator;

    convertToProper(pResult);
}

void subtraction(mixedFraction *pResult, mixedFraction num1, mixedFraction num2) {
    initializeMixed(pResult);
    convertToMixed(&num1);
    convertToMixed(&num2);

    pResult->nominator = (num1.nominator*num2.denominator) - (num2.nominator*num1.denominator);
    pResult->denominator = num1.denominator*num2.denominator;

    convertToProper(pResult);
}

void multiplication(mixedFraction *pResult, mixedFraction num1, mixedFraction num2) {
    initializeMixed(pResult);
    convertToMixed(&num1);
    convertToMixed(&num2);

    pResult->nominator = num1.nominator*num2.nominator;
    pResult->denominator = num1.denominator*num2.denominator;

    convertToProper(pResult);
}

void division(mixedFraction *pResult, mixedFraction num1, mixedFraction num2) {
    initializeMixed(pResult);
    convertToMixed(&num1);
    convertToMixed(&num2);

    pResult->nominator = num1.nominator*num2.denominator;
    pResult->denominator = num1.denominator*num2.nominator;

    convertToProper(pResult);
}

int main() {
    mixedFraction num1 = {1,2,3};
    mixedFraction num2 = {1,3,4};
    mixedFraction result;

    addition(&result, num1, num2);
    print(result);
    subtraction(&result, num1, num2);
    print(result);
    multiplication(&result, num1, num2);
    print(result);
    division(&result, num1, num2);
    print(result);

    return 0;
}