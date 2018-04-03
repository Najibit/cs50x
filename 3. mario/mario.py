############################################################################
# mario.py (more)
#
# Minor Programming
# Programming II
# Problem Set 6: Sentimental
# Najib el Moussaoui
#
# Prompt a height of a pyramid and print that pyramid to the console.
###########################################################################

import cs50

# prompt user for pyramid height
while True:
    print("Height of pyramid in blocks: ", end="")
    height = cs50.get_int()
    if height > 0 and height <= 23:
        break

# counters for spaces and hashes
spaces = height - 1
hashes = height - spaces

# iterate and print pyramid
for i in range(height):
    print(" " * spaces, end="")
    print("#" * hashes, end="")
    print("  ", end="")
    print("#" * hashes)
    spaces -= 1
    hashes += 1
