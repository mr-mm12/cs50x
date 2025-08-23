while True:
    try:
        number = int(input("Height: "))  # Geting a number(Height) from user
        if (1 <= number <= 8):  # Check if it is between 1 and 8
            break  # True input, exits the loop
    except ValueError:
        pass  # If the input was non-numeric, prompt the user again

for i in range(1, number + 1):  # Outer ring: every line
    for j in range(number - i):  # Print spaces
        print(" ", end="")  # Print a space without going to the next line
    for k in range(i):  # Print '#'
        print("#", end="")  # Print a '#' without going to the next line
    print("")  # Go to the next line after printing all spaces and '#'s on that line

# Mohammadreza_mokhtari_kia
