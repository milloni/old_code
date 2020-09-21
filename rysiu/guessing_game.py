from random import randint

# raw_input() -> "12"
# int("12") -> 12

targetNumber = randint(1, 100)
guessNumber = int(raw_input("Enter the number: "))
while guessNumber != targetNumber:
    if guessNumber < targetNumber:
        print "Too little"
    if guessNumber > targetNumber:
        print "Too much"
    guessNumber = int(raw_input("Try again: "))
print "U won gz"
