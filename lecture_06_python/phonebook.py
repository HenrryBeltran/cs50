import csv

name = input("Name: ")
number = input("Number: ")

with open("phonebook.csv", "a") as file:
    writer = csv.DictWriter(file, fieldnames=["name", "number"])
    writer.writerow({"name": name, "number": number})

# people = {
#     "Yuliia": "+1-617-495-1000",
#     "David": "+1-617-495-1000",
#     "John": "+1-949-648-2750",
# }
#
# name = input("Name: ")
#
# if name in people:
#     print(f"Found {people[name]}")
# else:
#     print("Not found")
