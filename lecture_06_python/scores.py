from cs50 import get_int

scores = []

for i in range(3):
    score = get_int(f"Score #{i + 1}: ")
    scores.append(score)

average = sum(scores) / len(scores)

print(f"Average: {average}")
