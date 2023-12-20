  
#  Task: CLI program for Fault Code Description Analysis

##  Requirements

- Use any statically typed language (C#, Java, Swift, C++, Kotlin, etc.) Do not use dynamically typed languages (No Python, No Js etc) 
- No help from AI in particular do not use ChatGPT, Copilot, or any other AI tools to complete this task. (Documentation & Google/Stackoverflow etc. allowed)

## Task overview

Create CLI Program, which anlyzes given input and writes the output to a directory. 

##  Arguments

1.  `-i /path/to/input.txt`: Specifies the input text file containing Fault Code Descriptions.

2.  `-o /path/to/output/folder`: Specifies the directory where output CSV files will be stored.

## Extract word Sequences

### Task Description

Analyze the input text to extract and count all unique word sequences of varying lengths (n).
- Line break (`\r` or `\n`) break a word sequence
- Counting of words & word pairs is case insensitive
- Skip empty words
- Words can be separated by any of the following characters: space `' '`, hyphen `'-'`, slash `'/'`, tab `'\t'`, comma `','`.

Output these sequences and their occurrence counts in CSV files named `occurrence_length_n.csv`
	- Where `n` is the length of the word sequence.

###  Output Format

The CSV files have no headers and use a comma `,` as delimiter.
- Column 1: The word sequence, words separated by spaces (`' '`).
- Column 2: The total number of occurrences for that word sequence.

###  Sorting

Sort by number of occurrences in descending order, then by sequences alphabetically

##  Error Handling

Ensure to handle input and output exceptions and argument validation.
 
##  Evaluation Criteria

- Correctness
- Code quality
- ~~Runtime Performance & Space Complexity~~
- ~~Proper error handling and validations~~

