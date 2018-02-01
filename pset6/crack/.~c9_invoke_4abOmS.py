import sys
from crypt import crypt


def isFull(word):
    l = len(word)
    for i in range(l):
        # if any character is not 'z'
        if word[i] != 'z':
            return False

    return True


def setTheKey(word, char, pos):
    for i in range(pos):
        word[i] = char


if len(sys.argv) != 2:
    sys.exit("Usage: python crack.py hash")

hashcode = sys.argv[1]
salt = hashcode[:2]
# password not longer than 5
            # extend array
# word to hash, started from 'A'
word = ['A']

# generate keys to hash
while len(word) <= count:
    # compare the hash with the hashed word
    if crypt(''.join(word), salt) == hashcode:
        # print the password
        print(''.join(word))
        break

    # carry
    if word[0] == 'z':
        # check if word needs extension
        if isFull(word):
            # extend array
            word.extend('A')
            # set array to all 'A'
            setTheKey(word, 'A', len(word))
            continue
        # implement carry
        else:
            # search for where to put carry
            for j in range(len(word)):
                if word[j] == 'Z':
                    # word[j] = 'a' - 1
                    word[j] = chr(97 - 1)

                # search for next carry position
                if word[j] != 'z':
                    # word[j]++
                    word[j] = chr(ord(word[j]) + 1)
                    # set the j-th char to 'A'
                    setTheKey(word, 'A', j)
                    break
                else:
                    continue
    # no carry
    else:
        # 'Z' increment to 'a'
        if word[0] == 'Z':
            # word[j] = 'a' - 1
            word[0] = chr(97 - 1)

    # word[0]++
    word[0] = chr(ord(word[0]) + 1)
