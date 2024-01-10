def main():
    card = get_card()
    check_type(card)


def get_card():
    while True:
        try:
            num = int(input("Number: "))
            if 12 < len(str(num)) < 17:
                return num
        except ValueError:
            print("", end="")


def check_valid(card):
    t = 0
    end = 0
    for i in card:
        if int(i) % 2 == 0:
            t += int(i) * 2
    for i in card:
        if int(i) % 2 == 1:
            end += int(i)
    return (end % 10 == 0)
    

def check_type(card):
    card = str(card)
    one = int(card[0])
    two = int(card[1])
    if check_valid(card):
        if len(card) == 15 and one == 3 and (two == 4 or two == 7):
            print("AMEX")
        elif len(card) == 16 and one == 5 and 1 <= two <= 5:
            print("MASTERCARD")
        elif (len(card) == 13 or len(card) == 16) and one == 4:
            print("VISA")
        else:
            print("INVALID")

if __name__ == "__main__":
    main()
