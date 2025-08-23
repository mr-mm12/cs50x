# Importing string module for letter checking
import string

def count_sentences(text):
    """Count the number of sentences in the text."""
    count = 0
    for ch in text:
        # Separating sentences, whenever you see
        # the '!', '.', '?' signs, the sentence
        if ch in '.!?':
            count += 1  # Adds one to the sentence
    return count

def count_words(text):
    """Count the number of words in the text."""
    # Assuming words are separated by spaces
    return len(text.split())

def count_letters(text):
    """Count the number of alphabetic letters in the text."""
    letters = 0
    for ch in text:
        # Moves over the text by the number of
        # letters and separates the letters
        if ch.isalpha():
            letters += 1  # Adds to the word
    return letters

# Prompt user for input text
user_text = input("Text: ")

# Count letters, words, and sentences
total_letters = count_letters(user_text)
total_words = count_words(user_text)
total_sentences = count_sentences(user_text)

# Calculate averages per 100 words
avg_letters = (total_letters / total_words) * 100
avg_sentences = (total_sentences / total_words) * 100

# Coleman-Liau index calculation
index = 0.0588 * avg_letters - 0.296 * avg_sentences - 15.8
grade = round(index)


if index < 1:
    # Display the grade level
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {grade}")

# Mohammadreza_mokhtari_kia
