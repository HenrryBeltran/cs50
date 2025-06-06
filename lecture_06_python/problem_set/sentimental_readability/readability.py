from cs50 import get_string


def main():
    text = get_string("Text: ")
    letters_count = get_letters_count(text)
    words_count = get_words_count(text)
    sentences_count = get_sentences_count(text)

    L = letters_count / words_count * 100
    S = sentences_count / words_count * 100

    index = round(0.0588 * L - 0.296 * S - 15.8)

    if index < 1:
        print("Before Grade 1")
    elif 0 < index < 16:
        print(f"Grade {index}")
    else:
        print("Grade 16+")


def get_letters_count(text):
    return sum(1 for char in text if char.isalpha())


def get_words_count(text):
    return len(text.split())


def get_sentences_count(text):
    return sum(1 for char in text if char in ".!?")


if __name__ == "__main__":
    main()
