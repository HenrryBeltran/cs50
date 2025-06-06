import cs50

while True:
    n = cs50.get_int("n: ")
    if n > 0:
        break

for i in range(n):
    print("#" * n)
