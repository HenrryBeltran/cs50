#include <cs50.h>
#include <stdio.h>

void draw_bricks(const int width, const int height);

int main(void) {
    int w;
    int h;

    // Prompt user for positive integer
    do {
        w = get_int("enter width: ");
    } while (w < 1);
    do {
        h = get_int("enter height: ");
    } while (h < 1);

    draw_bricks(w, h);
}

void draw_bricks(const int width, const int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("#");
        }
        printf("\n");
    }
    printf("\n");
}
