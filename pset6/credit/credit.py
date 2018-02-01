from cs50 import get_string

# prompt user for credit card number
while True:
    n = get_string("Number: ")
    if (float(n) > 0):
        break

# calculate the checksum
checksum = 0
# the most significant number's index
index = len(n)

for c in n:
    # string to int
    c = int(c)
    # for even position
    if (index % 2 == 0):
        # if c * 2 > 10, add product's digits
        # else just add c * 2
        c = c * 2
        checksum += c // 10 + c % 10 if c >= 10 else c
    else:
        checksum += c
    index -= 1

# check checksum
# if last digit is 0, legit
if checksum % 10 == 0:
    # check head numbers
    if n.startswith(("34", "37")):
        print("AMEX")
    elif n.startswith("4"):
        print("VISA")
    elif n.startswith(("51", "52", "53", "54", "55")):
        print("MASTERCARD")
# not legit
else:
    print("INVALID")