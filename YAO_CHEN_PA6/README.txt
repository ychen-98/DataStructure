Spell Checker and Word Suggestion Program

Yao Chen 
Nov 13, 2023 

## Description
This program is a simple spell checker and word suggestion tool developed in C++. It utilizes a given dictionary of words to validate user input and offers suggestions based on the spelling. The execution time for each operation is displayed in microseconds.

The program operates in three main cases: 

	-- Word Exists in Dictionary: It confirms the existence of the word and suggests other words starting with the same first two letters.
	-- Misspelled Word: If the input word does not exist in the dictionary but resembles a word (assuming the first letter is correct), the program suggests a potential correct spelling.
	-- Word Does Not Exist: If there is no similar word in the dictionary, the program simply returns "false".



## Compilation: 
	make

## Execution: 
	make run 

## Cleaning: 
	make clean 


## Single Letter Input Rule
If the user enters only one letter, the program will output "True" if this single-letter word is in the dictionary. Otherwise, the program will check similar word (misspelled situation), and if no "resembling" word found, the program will output "False".  


## Example 1: 
make
make run
[Input] 
Please enter a word: a
[Output] 
True
A
Execution time: 76 micro-sec


## Example 2: 
make
make run
[Input] 
Please enter a word: hi
[Output] 
Do you mean his? (yes/no):
[Input] 
yes
[Output] 
True
his
him
Execution time: 1.85655e+06 micro-sec



## Example 3: 
make
make run
[Input] 
Please enter a word: of
[Output]
True
of
off
Execution time: 105 micro-sec



## Example 4: 
make
make run
[Input] 
Please enter a word: sentenc
[Output] 
Do you mean sentence? (yes/no):
[Input] 
yes
[Output] 
True
sentence
see
set
Execution time: 1.96544e+06 micro-sec


