def main():
    text = get_input()
    score = score_text(text)

    if score > 16:
        print("Grade 16+")
    elif score < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {round(score)}")

def get_input():
    text = input("Text: ")
    return text

def score_text(text):
    length = 0
    sentences = 0
    wordCount = 0

    for i in text:
        if i == " ":
            wordCount += 1
        elif i == '.' or i == '?' or i == '!':
            sentences += 1
        else:
            length += 1

    return ((0.0588 * (length / wordCount * 100)) - (0.296 * (sentences / wordCount * 100)) - 15.8)


if __name__ == "__main__":
    main()
