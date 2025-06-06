def main():
    count = int(input("How many meows? "))
    meow(count)


def meow(n):
    for _ in range(n):
        print("meow")


if __name__ == "__main__":
    main()
