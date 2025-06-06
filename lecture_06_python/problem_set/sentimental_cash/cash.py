from cs50 import get_float

quarter = 0.25
dime = 0.10
nickel = 0.05
penny = 0.01


def main():
    while True:
        cash_owend = get_float("Change: ")
        if cash_owend > 0:
            break

    result = get_number_of_coins(cash_owend)
    print(result)


def get_number_of_coins(owed):
    n = 0

    while owed >= quarter:
        n += 1
        owed = round(owed - quarter, 2)

    while owed >= dime:
        n += 1
        owed = round(owed - dime, 2)

    while owed >= nickel:
        n += 1
        owed = round(owed - nickel, 2)

    while owed >= penny:
        n += 1
        owed = round(owed - penny, 2)

    return n


if __name__ == "__main__":
    main()
