//Author: Ben Mansfield
//Date: 4/29/26
//Purpose: CS135 Project 10 - Create a wordle-like game

#include <stdio.h>
#include <stdbool.h>

#define WORD_LEN 5
#define MAX_GUESSES 6
#define INPUT_SIZE 100

void loadWord(char word[]);
void removeNewline(char str[]);
int stringLength(char str[]);
bool isLetter(char ch);
char toLower(char ch);
void makeLowercase(char str[]);
bool isValidGuess(char guess[]);
bool wordsMatch(char guess[], char word[]);
bool letterInWord(char letter, char word[]);
void displayGuess(char guess[], char word[]);
void displayAllGuesses(char guesses[][WORD_LEN + 1], int count, char word[]);

int main(void)
{

char word[WORD_LEN + 1];
char input[INPUT_SIZE];
char guesses[MAX_GUESSES][WORD_LEN + 1];

int guessCount = 0;
bool won = false;

loadWord(word);

	while (guessCount < MAX_GUESSES && !won)
	{
		printf("Enter your guess: ");
		fgets(input, INPUT_SIZE, stdin);

		removeNewline(input);
		makeLowercase(input);

		while (!isValidGuess(input))
		{
			printf("Uh oh! That doesn't look right.. Enter exactly 5 letters please: ");
			fgets(input, INPUT_SIZE, stdin);

			removeNewline(input);
			makeLowercase(input);
		}
			
		for (int i = 0; i < WORD_LEN; i++)
		{
			guesses[guessCount][i] = input[i];
		}
		guesses[guessCount][WORD_LEN] = '\0';

		guessCount++;

		displayAllGuesses(guesses, guessCount, word);

		if (wordsMatch(input, word))
		{
			won = true;
		}
	}

	if (won)
	{
		printf("You are the GOAT! The word was %s.\n", word);
	}
	else
	{
		printf(":( Out of guesses.. The word was %s.\n", word);
	}

	return 0;
}

	void loadWord(char word[])
	{
		FILE *file = fopen("mystery.txt", "r");

		if (file == NULL)
		{
			printf("mystery.txt failed to open! :( \n");
			word[0] = '\0';
		return;
		}

		fgets(word, WORD_LEN + 1, file);
		removeNewline(word);
		makeLowercase(word);

		fclose(file);
	}

	void removeNewline(char str[])
	{
	int i = 0;

		while (str[i] != '\0')
		{
			if (str[i] == '\n')
			{
				str[i] = '\0';
			}

			i++;
		}
	}

	int stringLength(char str[])
	{
	int count = 0;

		while (str[count] != '\0')
		{
			count++;
		}

		return count;
	}

	bool isLetter(char ch)
	{
		return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
	}

	char toLower(char ch)
	{
		if (ch >= 'A' && ch <= 'Z')
		{
			return ch + 32;
		}

		return ch;
	}

	void makeLowercase(char str[])
	{
	int i = 0;

		while (str[i] != '\0')
		{
			str[i] = toLower(str[i]);
			i++;
		}
	}

	bool isValidGuess(char guess[])
	{
		if (stringLength(guess) != WORD_LEN)
		{
			return false;
		}

		for (int i = 0; i < WORD_LEN; i++)
		{
			if (!isLetter(guess[i]))
			{
				return false;
			}
		}

		return true;
	}

	bool wordsMatch(char guess[], char word[])
	{
		for (int i = 0; i < WORD_LEN; i++)
		{
			if (guess[i] != word[i])
			{
				return false;
			}
		}

		return true;
	}

	bool letterInWord(char letter, char word[])
	{
		for (int i = 0; i < WORD_LEN; i++)
		{
			if (letter == word[i])
			{
				return true;
			}
		}

		return false;
	}

	void displayGuess(char guess[], char word[])
	{
	char display[WORD_LEN + 1];
	char arrows[WORD_LEN + 1];

		for (int i = 0; i < WORD_LEN; i++)
		{
			display[i] = guess[i];
			arrows[i] = ' ';
		}

	display[WORD_LEN] = '\0';
	arrows[WORD_LEN] = '\0';

		for (int i = 0; i < WORD_LEN; i++)
		{
			if (guess[i] == word[i])
			{
				display[i] = guess[i] - 32;
			}
		}

		for (int i = 0; i < WORD_LEN; i++)
		{
			if (guess[i] != word[i] && letterInWord(guess[i], word))
			{
				bool alreadyCorrect = false;

				for (int j = 0; j < WORD_LEN; j++)
				{
					if (guess[i] == word[j] && guess[j] == word[j])
					{
						alreadyCorrect = true;
					}
				}

				if (!alreadyCorrect)
				{
					arrows[i] = '^';
				}
			}
		}

	printf("%s\n", display);
	printf("%s\n", arrows);
	}

	void displayAllGuesses(char guesses[][WORD_LEN + 1], int count, char word[])
	{
	printf("\nPrevious guesses:\n");

		for (int i = 0; i < count; i++)
		{
			displayGuess(guesses[i], word);
		}

	printf("\n");
	}
