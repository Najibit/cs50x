############################################################################
# greedy.py
#
# Minor Programming
# Programming II
# Problem Set 6: Sentimental
# Najib el Moussaoui
#
# Returns change owed in amount of coins.
###########################################################################

import cs50

# prompt user for amount owed
while True:
    dollars = cs50.get_float("How much change is owed (in dollars)? ")
    if dollars > 0:
        break

# convert dollars to cents and initialize counters
cents = dollars * 100
amount = cents
count = 0

# iterate over amount, substract and adjust counters
while True:
    if amount >= 25:
        amount -= 25
        count += 1
    if amount >= 10 and amount < 25:
        amount -= 10
        count += 1
    if amount >= 5 and amount < 10:
        amount -= 5
        count += 1
    if amount >= 1 and amount < 5:
        amount -= 1
        count += 1
    if amount == 0:
        break

# print amount in coins
print(f"Amount in coins: {count}")

