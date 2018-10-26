/*NOTE
1. Variable names go for CamelCase as it is Unreal Engine Standard
2. Constant names, go for ALL CAPS*/
/*TODO later make some code that allows the user to select the difficulty as 3/4/5/6 letters and accordingly
TODO make a map of <length, structure> where structure holds a series of words, and will be randomly selected*/

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"


using FText = std::string;									// In Unreal FText is used to hard print stuff; FString is user modifiable
using int32 = int;											// again, in Unreal coding standard int32 is used instead of int because of cross compatibility of the game

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;										//instantiate i.e. create a new game

int main()
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	}
	while (bPlayAgain);
	return 0;
}

void PrintIntro()	//introduce the game using a function
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;

	
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter word I'm thinking of?\n";
	return;
}

void PlayGame()
{
	BCGame.Reset();	//Resets the initial state so that its a fresh start everytime	
	int32 MaxTries = BCGame.GetMaxTries();

	while( !BCGame.IsGameWon() && BCGame.GetCurrentTry() <= BCGame.GetMaxTries() )	//Loops for given number of terms
	{
		FText UserEntry = "";
		UserEntry = GetValidGuess();
		
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(UserEntry);
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ", Cows = " << BullCowCount.Cows << "\n\n";
	
		PrintGameSummary();
	}
	return;
}

void PrintGameSummary()
{
	if (BCGame.GetCurrentTry() > BCGame.GetMaxTries())
	{
		std::cout << "Sorry, you are out of tries!\n";
	}
	else if ( BCGame.IsGameWon() )
	{
		std::cout << "CONGRATULATIONS! YOU HAVE WON THE GAME!\n";
	}
}

FText GetValidGuess()	//get a valid guess from user by looping continuously
{
	FText Guess = "";
	EGuessWordStatus Status = EGuessWordStatus::Invalid;
	do
	{
		int32 CurrentGuessNumber = BCGame.GetCurrentTry();

		std::cout << "\nTry " << CurrentGuessNumber << " out of " << BCGame.GetMaxTries() << " --> Enter your guess: ";
		std::getline(std::cin, Guess);	//gets user input i.e the word they've guessed

		Status = BCGame.CheckGuessValidity(Guess);	//check for status and give feedback to user
		switch (Status)
		{
		case EGuessWordStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;

		case EGuessWordStatus::Case_Mismatch:
			std::cout << "A case mismatch has occurred. Please enter the word with matching case.\n\n";
			break;

		case EGuessWordStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating the alphabets.\n\n";
			break;

		default:
			break;	//assuming all letters are correct
		}
	} while (Status != EGuessWordStatus::OK);	//Keep looping till we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	FText Response;
	std::cout << "\nDo you want to play again with the same hidden word? (Y/N): ";
	std::getline(std::cin,Response);
	return (Response[0] == 'y' || Response[0] == 'Y');
}
