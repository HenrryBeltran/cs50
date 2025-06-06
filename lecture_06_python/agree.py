ask_again = True

while ask_again:
    s = input("Do you agree? ").lower()

    if s in "yes":
        print("Agreed.")
        ask_again = False
    elif s in "not":
        print("Not agreed.")
        ask_again = False
