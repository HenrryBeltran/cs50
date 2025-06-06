#include <cs50.h>
#include <stdio.h>

const int quarter = 25;
const int dime = 10;
const int nickel = 5;
const int penny = 1;

int get_number_of_coins(int owed);

int main(void)
{
    int cash_owed;

    do
    {
        cash_owed = get_int("Cash owed: ");
    } while (cash_owed < 0);

    int result = get_number_of_coins(cash_owed);

    printf("%i\n", result);
}

int get_number_of_coins(int owed)
{
    int n = 0;
    while (owed >= quarter)
    {
        n++;
        owed -= quarter;
    }
    while (owed >= dime)
    {
        n++;
        owed -= dime;
    }
    while (owed >= nickel)
    {
        n++;
        owed -= nickel;
    }
    while (owed >= penny)
    {
        n++;
        owed -= penny;
    }
    return n;
}
