#include <cs50.h>
#include <math.h>
#include <stdio.h>

int get_first_two_digits(long value);
int get_first_digit(long value);
int get_lenght(long value);
int get_digit_sum(int value);

int main(void)
{
    const long credit_number = get_long("Number: ");

    long number = credit_number;
    int i = 0;
    int first_sum = 0;
    int second_sum = 0;

    // Process the credit number with luhn's algorithm
    while (number > 0)
    {
        if (i % 2 == 0)
        {
            second_sum += number % 10;
        }
        else
        {
            int by_two = (number % 10) * 2;
            first_sum += get_digit_sum(by_two);
        }
        i++;
        number *= 0.1;
    }

    const int overall_sum = first_sum + second_sum;

    // Define the predicates of the if statements for readability
    const bool is_amex = (get_first_two_digits(credit_number) == 34 ||
                          get_first_two_digits(credit_number) == 37) &&
                         get_lenght(credit_number) == 15;

    const bool is_mastercard = get_first_two_digits(credit_number) >= 51 &&
                               get_first_two_digits(credit_number) <= 55 &&
                               get_lenght(credit_number) == 16;

    const bool is_visa =
        get_first_digit(credit_number) == 4 &&
        (get_lenght(credit_number) == 16 || get_lenght(credit_number) == 13);

    // Validate the luhn's algorithm
    if (overall_sum % 10 != 0)
    {
        printf("INVALID\n");
    }
    else
    {
        // Validate the credit type and digit length
        // like in a database
        if (is_amex)
        {
            printf("AMEX\n");
        }
        else if (is_mastercard)
        {
            printf("MASTERCARD\n");
        }
        else if (is_visa)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
}

int get_first_two_digits(long value)
{
    while (value >= 100)
    {
        value *= 0.1;
    }
    return (int)value;
}

int get_first_digit(long value)
{
    while (value >= 10)
    {
        value *= 0.1;
    }
    return (int)value;
}

int get_lenght(long value)
{
    return floor(log10(value)) + 1;
}

int get_digit_sum(int value)
{
    int sum = 0;
    while (value > 0)
    {
        sum += value % 10;
        value *= 0.1;
    }
    return sum;
}
