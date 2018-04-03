############################################################################
# vigenere.py
#
# Minor Programming
# Programming II
# Problem Set 6: Sentimental
# Najib el Moussaoui
#
# Encrypt a message with a special alphabetical key.
###########################################################################

import cs50 as cs
import sys

# ensure proper usage
if len(sys.argv) != 2:
    print("Use two command-line arguments bro")
    exit(1)

# extract the secret key from command-line (sssht)
key = sys.argv[1]

# check if cipherkey is all alphabetical
if key.isalpha() == False:
    print("Only alphabetical characters pls")
    exit(2)

# prompt user for plaintext to cipher
plain = cs.get_string("plaintext: ")

# counters
index = 0
j = 0


def convert(letter):
    """Returns an index between 0-25 for every letter."""
    if letter.islower():
        return ord(letter) - ord('a')
    elif letter.isupper():
        return ord(letter) - ord('A')

print("ciphertext: ", end="")

# loop over plaintext, and shift with key's index, with wraparound.
for i in range(len(plain)):
    if plain[i].isalpha():
        index = (convert(plain[i]) + convert(key[j % len(key)])) % 26
        j += 1
    if plain[i].isupper():
        print(chr(index + ord('A')), end="")
    elif plain[i].islower():
        print(chr(index + ord('a')), end="")
    else:
        print(plain[i], end="")

# Aloha and au revoir
print()



