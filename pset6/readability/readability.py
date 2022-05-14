from cs50 import get_string
#from math import round

def grade(text):
    grade, L, S = 0.0, 0.0, 0.0
    l, w = 0, 1
    sents = 0

    for i in range(len(text)):
        c = text[i]
        if c == ' ':
            w += 1      # spaces delimit words
        elif c.isalpha():
            l += 1     # letters
        elif c == '.' or c == '!' or c == '?':
            sents += 1



    L = 100 * float(l / w)
    S = 100 * float(sents / w)

    grade = 0.0588 * L - 0.296 * S - 15.8

    return round(grade)

def main():

    while True:
        ut = get_string("Text: ")
        if len(ut) > 0:
            break

    if grade(ut) < 1:
        print("Before Grade 1")
    elif grade(ut) > 16:
        print("Grade 16+")
    else:
        print("Grade", grade(ut))


main()
