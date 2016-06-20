// Name: Tyler Gauntlett
// Course: Systems Software
// Date: 6/16/2016

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#define MAX_STRING_LENGTH 11
#define MAX_NUMBER_LENGTH 5
#define NUM_OF_SPECIAL_SYMBOLS 16
#define NUM_OF_RESERVED_WORDS 14
#define NUM_OF_TOKENS 33
#define NUM_OF_INVALID_SYMBOLS 6

void getCleanInput();
void getLexemeTable();
void getLexemeList();
int tokenizeAssigner(char *inputArray);
int isReserveredWord(char *word);
int isIdentifierWord(char *word);
int isValidNumber(char *inputWord);
int isSpecialSymbol(char *word);
int reserveredWordCovnerter(int index);
int specialSymbolCovnerter(int index);

// Delcare constants used below.
const char *tokens[33] = { "nulsym", "identsym", "numbersym", "plussym", "minussym",
"multsym", "slashsym", "oddsym", "eqsym", "neqsym", "lessym", "leqsym",
"gtrsym", "geqsym", "lparentsym", "rparentsym", "commasym", "semicolonsym",
"periodsym", "becomessym", "beginsym", "endsym", "ifsym", "thensym",
"whilesym", "dosym", "callsym", "constsym", "varsym", "procsym", "writesym",
"readsym", "elsesym" };
const char *reserveredWords[14] = { "const", "var", "procedure", "call", "begin", "end", "if", "then", "else", "while", "do", "read", "write", "odd"};
const char *specialSymbols[16] = { "<>", "-", "*", "/", "(", ")", ":=", "=", ",", ".", "<=", ">=", "<", ">", ";", "+" };
const char *invalidSymbols[6] = { "$", "#", "&", "!", "~", "?" };

// LexemeTable and LexemeList are relient on CleanInput's
// ouput file. They must go in this order.
int main() {
	getCleanInput();

	getLexemeTable();

	getLexemeList();

	return 0;
}

// Assing tokens based on what category the input registers to.
// Start with reservered words and symbols. Varibles names must go last.
int tokenizeAssigner(char *input){

	if (isReserveredWord(input)){
		return reserveredWordCovnerter(isReserveredWord(input));
	}

	// Pass the invalid symbol code back to the function.
	if (isSpecialSymbol(input) == -2){
		return -2;
	}

	// Return the symbol token based on what symbol is used.
	if (isSpecialSymbol(input)){
		return specialSymbolCovnerter(isSpecialSymbol(input));
	}

	// Pass the invalid number code back to the function.
	if (isValidNumber(input) == -2){
		return -2;
	}

	// If it is a valid number, return 3 for valid numbers.
	if (isValidNumber(input)){
		return 3;
	}

	// Pass the invalid varible code back to the function.
	if (isIdentifierWord(input) == -2){
		return -2;
	}

	// If it is not a reservered word and is a identifier, return
	// 2 for identifiers.
	if (!isReserveredWord(input) && isIdentifierWord(input)){
		return 2;
	}
	return -1;
}

// Check if the word starts wtih a alpha character and is 
// followed by alpha numarical characters. Check for length > 11.
int isIdentifierWord(char *word){
	int i = 0, length = strlen(word);

	// If invalid  size, return error code -2.
	if (length > MAX_STRING_LENGTH){
		return -2;
	}

	// Verify the string has some length.
	if (length > 0){
		// Check if the first letter is alpha and
		// all others are alphanumaric.
		if (isalpha(word[i])){
			for (i; i < length; i++){
				if (isalnum(word[i])){
					continue;
				}
				else{
					return 0;
				}
			}
			return 1;
		}
		else{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

// Returns 0 for not a reservered word or the index + 1 of the reservered word.
// This is later sumbtracted out in the corrisponding switch statement.
int isReserveredWord(char *word){
	int i, found = 0;
	for (i = 0; i < NUM_OF_RESERVED_WORDS; i++){
		if (strcmp(word, reserveredWords[i]) == 0){
			found = i + 1;
		}
	}
	return found;
}

// Loops up the reservered word base on the corrisponding index
// of the reservered words array.
int reserveredWordCovnerter(int index){
	switch (index-1)
	{
	// const
	case 0:
		return 28;
	// var
	case 1:
		return 29;
	// procedure
	case 2:
		return 30;
	// call
	case 3:
		return 27;
	// begin
	case 4:
		return 21;
	// end
	case 5:
		return 22;
	// if
	case 6:
		return 23;
	// then
	case 7:
		return 24;
	// else
	case 8:
		return 33;
	// while
	case 9:
		return 25;
	// do
	case 10:
		return 26;
	// read
	case 11:
		return 32;
	// write
	case 12:
		return 31;
	// odd
	case 13:
		return 8;
	default:
		return -1;
	}
}

// Check if it is a special symbol. Add one to the index to account for it
// being the first element in the list.
int isSpecialSymbol(char *word){
	int i, found = 0;
	for (i = 0; i < NUM_OF_SPECIAL_SYMBOLS; i++){
		if (strcmp(word, specialSymbols[i]) == 0){
			found = i + 1;
		}
	}
	for (i = 0; i < NUM_OF_INVALID_SYMBOLS; i++){
		if (strcmp(word, invalidSymbols[i]) == 0){
			found = -2;
		}
	}
	
	return found;
}

// Get the corrisponding value associated with the special symbol.
// Subtract 1 to conteract the extra one assinged in the function above.
int specialSymbolCovnerter(int index){
	switch (index-1)
	{
	// <>
	case 0:
		return 10;
	// -
	case 1:
		return 5;
	// *
	case 2:
		return 6;
	// /
	case 3:
		return 7;
	// (
	case 4:
		return 15;
	// )
	case 5:
		return 16;
	// :=
	case 6:
		return 20;
	// =
	case 7:
		return 9;
	// ,
	case 8:
		return 17;
	// .
	case 9:
		return 19;
	// <=
	case 10:
		return 12;
	// >=
	case 11:
		return 14;
	// <
	case 12:
		return 11;
	// >
	case 13:
		return 13;
	// ;
	case 14:
		return 18;
	// +
	case 15:
		return 4;
	default:
		return -1;
	}
}

// Returns 1 if the number is of valid size (less than 5 digits).
int isValidNumber(char *inputWord){
	int isNumber = 1;
	int j;
	int length = strlen(inputWord);
	// Check if each number in the total number is an integer.
	for (j = 0; j < length; j++){
		if (isdigit(inputWord[j]))
		{
			continue;
		}
		else
		{
			isNumber = 0;
		}
	}
	// At this point, we can be sure it is a number.
	if (isNumber){
		int count = 0;
		int tempNumber = atoi(inputWord);
		while (tempNumber != 0)
		{
			tempNumber /= 10;
			++count;
		}
		if (count > MAX_NUMBER_LENGTH){
			return -2;
		}
		else
			return isNumber;
	}
	else
		return isNumber;
}

// Removes all comments from the input file.
void getCleanInput() {
	FILE *inputFile, *outputFile;
	char outputFileName[] = "cleaninput.txt";
	char *mode = "r";
	int line = 0;

	inputFile = fopen("input.txt", mode);
	outputFile = fopen(outputFileName, "w");

	if (inputFile == NULL)
	{
		perror("Error");
		return;
	}
	else {
		// Count the amount of open and close comments.
		int openComment = 0;
		int closeComment = 0;
		int endOfComment = 0;
		while (!feof(inputFile))
		{
			char *inputWord = (char*)malloc(sizeof(char*) * 100);
			char whitespace;
			fscanf(inputFile, "%s%c", inputWord, &whitespace);
			
			// Here's where I would check if whitepace == '\n' and 
			// inputWord == undefined (e.g. empty line) and properly \n
			// but I can't because C is old and limited.

			// Break if at the end of the input.
			if (feof(inputFile)){
				break;
			}

			// Check if the word contains a close comment at the beginning or end.
			int length = strlen(inputWord);
			if (inputWord[0] == '*' && inputWord[1] == '/' || (inputWord[length - 2] == '*' && inputWord[length - 1] == '/')){
				closeComment++;
			}

			// Remove the content inside the comment from the output file.
			while ((openComment > closeComment) && !feof(inputFile)){
				int length = strlen(inputWord);
				if ((inputWord[0] == '*' && inputWord[1] == '/') || (inputWord[length-2] == '*' && inputWord[length-1] == '/')){
					closeComment++;
					endOfComment = 1;
				}
				else{
					fscanf(inputFile, "%s%c", inputWord, &whitespace);
				}
			}

			// Check if the closing comment brace occurse at the end of a file (prevents printing random chars
			// because inputWord is uninitialized).
			if ((openComment > closeComment) && feof(inputFile)){
				int length = strlen(inputWord);
				if ((inputWord[0] == '*' && inputWord[1] == '/') || (inputWord[length - 2] == '*' && inputWord[length - 1] == '/')){
					closeComment++;
					endOfComment = 1;
				}
			}

			// Prints a new line in the event the closing comment brace is at the end of the line.
			if (endOfComment){
				endOfComment = 0;
				if (whitespace == '\n'){
					fprintf(outputFile, "\n");
				}
				continue;
			}

			// Check if the word begins with the open comment symbols.
			if (inputWord[0] == '/' && inputWord[1] == '*'){
				openComment++;
				free(inputWord);
				continue;
			}

			// Writes word to output file and checks if the line needs a new line char.
			fprintf(outputFile, "%s ", inputWord);
			if (whitespace == '\n'){
				fprintf(outputFile, "\n");
			}

			free(inputWord);
		}
	}
	fclose(inputFile);
	fclose(outputFile);
}

void getLexemeTable() {
	FILE *inputFile, *outputFile;
	char outputFileName[] = "lexemetable.txt";
	char *mode = "r";
	int round = 0;

	inputFile = fopen("cleaninput.txt", mode);
	outputFile = fopen(outputFileName, "w");

	if (inputFile == NULL)
	{
		perror("Error");
	}
	else {

		while (!feof(inputFile))
		{
			char *inputWord = (char*)malloc(sizeof(char*) * 100);
			char whitespace;
			fscanf(inputFile, "%s%c", inputWord, &whitespace);

			// Break if at the end of the input.
			if (feof(inputFile)){
				break;
			}

			int tokenValue = tokenizeAssigner(inputWord);

			// If the token value is -2, than there is an invalid number
			// or varible. Exit porgram without printing.
			if (tokenValue == -2){
				return;
			}

			// Dont header if the file contains an error.
			if (round == 0){
				fprintf(outputFile, "lexeme \t\t token type\n");
			}
			round++;

			// If it came back with a vlaid token value, print it.
			if (tokenValue != -1){
				fprintf(outputFile, "%s \t\t %d\n", inputWord, tokenValue);
			}
			// If it was not valid, tear the word down and try substrings.
			else{
				// Begin making works starting with the first and last element.
				// If it does not exist, move the end counter down. If it does,
				// swith the beginning with the end and end to length of total size.
				int start = 0, length = strlen(inputWord), end = length;
				while (start < length) {
					char *temp = (char*)malloc(sizeof(char*) * 100);

					memcpy(temp, &inputWord[start], (sizeof(char)*(end-start)));
					temp[end - start] = '\0';

					int tokenValue = tokenizeAssigner(temp);

					if (tokenValue == -1){
						end--;
					}
					else{
						fprintf(outputFile, "%s \t\t %d\n", temp, tokenValue);
						start = end;
						end = length;
					}

					free(temp);
				}
			}

			free(inputWord);
		}
	}

	fclose(inputFile);
	fclose(outputFile);
}

void getLexemeList() {
	FILE *inputFile, *outputFile;
	char outputFileName[] = "lexemelist.txt";
	char *mode = "r";

	inputFile = fopen("cleaninput.txt", mode);
	outputFile = fopen(outputFileName, "w");

	if (inputFile == NULL)
	{
		perror("Error");
	}
	else {

		while (!feof(inputFile))
		{
			char *inputWord = (char*)malloc(sizeof(char*) * 100);
			char whitespace;
			fscanf(inputFile, "%s%c", inputWord, &whitespace);

			// Break if at the end of the input.
			if (feof(inputFile)){
				break;
			}

			int tokenValue = tokenizeAssigner(inputWord);

			// If the token value is -2, than there is an invalid number
			// or varible. Exit porgram without printing.
			if (tokenValue == -2){
				return;
			}

			// If it came back with a vlaid token value, print it.
			if (tokenValue != -1){
				if (tokenValue == 2 || tokenValue == 3)
					fprintf(outputFile, "%d %s ", tokenValue, inputWord);
				else{
					fprintf(outputFile, "%d ", tokenValue);
				}
			}
			// If it was not valid, tear the word down and try substrings.
			else{
				// Begin making works starting with the first and last element.
				// If it does not exist, move the end counter down. If it does,
				// swith the beginning with the end and end to length of total size.
				int start = 0, length = strlen(inputWord), end = length;
				while (start < length) {
					char *temp = (char*)malloc(sizeof(char*) * 100);

					memcpy(temp, &inputWord[start], (sizeof(char)*(end - start)));
					temp[end - start] = '\0';

					int tokenValue = tokenizeAssigner(temp);

					if (tokenValue == -1){
						end--;
					}
					else{
						if (tokenValue == 2 || tokenValue == 3)
							fprintf(outputFile, "%d %s ", tokenValue, temp);
						else{
							fprintf(outputFile, "%d ", tokenValue);
						}
						start = end;
						end = length;
					}

					free(temp);
				}
			}

			free(inputWord);
		}
	}

	fclose(inputFile);
	fclose(outputFile);
}