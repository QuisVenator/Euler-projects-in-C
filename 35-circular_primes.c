#include<stdio.h>
#include<stdbool.h>

#define LIMIT 1000000

bool isPrime(int num);
bool preCalc(int num);
bool isCircPrime(int num);
void mutate(int digits[], int start, int size, bool* const circPrime);
int separateDigits(int num, int digits[]);
int putTogetherDgits(int digits[]);
void swap(int* const num1, int* const num2);

int main(void)
{
    printf("Found circular primes: 2, 3, 5");
    for(int i = 7; i <= 1000000; i+=2)
    {
        if(preCalc(i))
        {
            if(isCircPrime(i))
            {
                printf(", %d", i);
            }
        }
    }
}

bool isPrime(int num)
{
    if(num % 2 == 0) return false;
    for(int i = 3; i*i <= num; i+=2)
    {
        if(num%i==0) return false;
    }
    return true;
}

bool preCalc(int num)
{
    int divisor = 1, digit;
    while(num/divisor > 0)
    {
        digit = num / divisor;
        divisor *= 10;
        digit %= 10;
        if(digit%2 == 0 || digit%5==0) return false;
    }
    return true;
}

bool isCircPrime(int num)
{
    static int digits[7], length;
    bool circPrime = true;
    for(int i = 0; i < 7; i++)
    {
        digits[i] = 0;
    }
    length = separateDigits(num, digits);
    mutate(digits, 7 - length, 7, &circPrime);
    return circPrime;
}

void mutate(int digits[], int start, int size, bool* const circPrime)
{
    for(int i = 0; i < size - start && *circPrime; i++)
    {
        for(int j = 0; j + 1 < size - start && *circPrime; j++)
        {
            swap(&digits[start + j], &digits[start + j + 1]);
        }

        if(isPrime(putTogetherDgits(digits)))
        {
            //return;
        }
        else
        {
            *circPrime = false;
            return;
        }
    }

    /*
    if(start == size - 1)
    {
        if(isPrime(putTogetherDgits(digits)))
        {
            return;
        }
        else
        {
            *circPrime = false;
            return;
        }
        
    }
    for(int i = start; i < size && *circPrime == true; i++)
    {
        swap(&digits[start], &digits[i]);
        mutate(digits, start + 1, size, circPrime);
        swap(&digits[start], &digits[i]);
    }
    */
}

int separateDigits(int num, int digits[])
{
    int div = 1, digit, counter = 0;
    while(num / div)
    {
        digit = num / div;
        div *= 10;
        digit %= 10;
        digits[6-counter] = digit;
        counter++;
    }
    return counter;
}

int putTogetherDgits(int digits[])
{
    int num = 0;
    for(int i = 0; i < 7; i++)
    {
        num *= 10;
        num += digits[i];
    }
    return num;
}

void swap(int* const num1, int* const num2)
{
    int aux;
    aux = *num1;
    *num1 = *num2;
    *num2 = aux;
    return;
}