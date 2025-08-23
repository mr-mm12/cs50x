import csv
import sys


def main():
    # Verify command-line arguments
    if len(sys.argv) != 3:
        print("Usage: python dna.py database.csv sequence.txt")
        sys.exit(1)

    db_path = sys.argv[1]  # First argument: path to database CSV
    sequence_path = sys.argv[2]  # Second argument: path to DNA sequence text file


    with open(db_path, newline='') as db_file:
        # Load DNA database
        csv_reader = csv.DictReader(db_file)  # Read CSV as dictionary
        profiles = list(csv_reader)  # Convert reader object to list of dictionaries
        STR_markers = csv_reader.fieldnames[1:]  # List of STR markers (skip 'name' column)


    with open(sequence_path, 'r') as seq_file:
        # Load DNA sequence
        dna_strand = seq_file.read().strip()  # Read DNA sequence and remove whitespace

    # Calculate the longest consecutive repeats for each STR
    str_counts = {marker: longest_match(dna_strand, marker) for marker in STR_markers}


    for profile in profiles:
        # Compare STR counts with each profile in the database
        if all(int(profile[marker]) == str_counts[marker] for marker in STR_markers):
            print(profile['name'])  # Print matching profile name
            return

    print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0  # Initialize longest run counter
    subsequence_length = len(subsequence)  # Length of the STR
    sequence_length = len(sequence)  # Length of the DNA sequence

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length  # Start index of current substring
            end = start + subsequence_length  # End index of current substring

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()

# Mohammadreza_mokhtari_kia
