from cs50 import get_int

while True:
    height = get_int("Height: ")

    if height > 0 and height <= 8:
        break

for i in range(height):
    n = i + 1
    print(" " * (height - n) + "#" * n, end="  ")
    print("#" * n)
