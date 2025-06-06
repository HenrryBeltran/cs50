def main():
    try:
        card_number = int(input("Number: "))
    except ValueError:
        print("INVALID")

    str_num = str(card_number)
    first_two = int(str_num[:2])
    first_digit = int(str_num[0])
    length = len(str_num)

    if luhn_checksum(card_number) % 10 != 0:
        result = "INVALID"
    elif length == 15 and first_two in {34, 37}:
        result = "AMEX"
    elif length == 16 and 51 <= first_two <= 55:
        result = "MASTERCARD"
    elif length in {13, 16} and first_digit == 4:
        result = "VISA"
    else:
        result = "INVALID"

    print(result)


def luhn_checksum(card_number):
    digits = [int(d) for d in str(card_number)]
    checksum = 0

    # Reverse for processing from right to left
    for i, digit in enumerate(reversed(digits)):
        if i % 2 == 0:
            checksum += digit
        else:
            checksum += get_digit_sum(digit * 2)
    return checksum


def get_digit_sum(value):
    return sum(int(digit) for digit in str(value))


if __name__ == "__main__":
    main()
