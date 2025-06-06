def main():
    my_boolean = True

    if my_boolean:
        name = "Foo"

    run_something(name)

    print("~ main:", name)


def run_something(value):
    print("... running some bussiness")
    print("~ r_s:", value)
    value = "Bar"
    print("~ r_s:", value)


if __name__ == "__main__":
    main()
