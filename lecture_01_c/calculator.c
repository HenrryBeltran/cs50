#include <cs50.h>
#include <stdio.h>

int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
float divide(int a, int b);

int main(void) {
    int x = get_int("x: ");
    int y = get_int("y: ");

    printf("addition: %i\n", add(x, y));
    printf("substraction: %i\n", subtract(x, y));
    printf("multiplication: %i\n", multiply(x, y));
    printf("division: %.2f\n", divide(x, y));
}

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

float divide(int a, int b) {
    return (float)a / (float)b;
}
