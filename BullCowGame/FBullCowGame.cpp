/* The game logic i.e. the classes and other structures we're using.
It is based on the fundamental concept of Mastermind */

#pragma once

#include "FBullCowGame.h"
#include <map>
#define TMap std::map


using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameWon; }

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3,8}, {4,10}, {5,15}, {6,20}, {7,24} }; //sets up the no. of tries acccording to the length of the word
	return WordLengthToMaxTries[MyHiddenWord.length()];
}



void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planes"; //the hidden word must be an isogram i.e. that the letters are not repeated
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameWon = false;
	return;
}

//recieves a valid guess, increments the turn number and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	
	//loop thrugh each letter in the guess and compare the letters against the letters of the hidden word
	int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 MHWChar = 0; MHWChar < HiddenWordLength; MHWChar++) //MHW = My Hidden Word Character
	{
		for (int32 GuessChar = 0; GuessChar < HiddenWordLength; GuessChar++)
		{
			if (Guess[GuessChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GuessChar)
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}

		}
	}
	if (BullCowCount.Bulls == HiddenWordLength)
	{
		bGameWon = true;
	}
	else
	{
		bGameWon = false;
	}
	return BullCowCount;
}


EGuessWordStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) //if word is not isogram
	{
		return EGuessWordStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess)) //if case mismatch occurs
	{
		return EGuessWordStatus::Case_Mismatch;
	}
	else if ( Guess.length() != GetHiddenWordLength() ) //if wrong length is entered
	{
		return EGuessWordStatus::Wrong_Length;
	}
	else //if no other errors send OK
	{
		return EGuessWordStatus::OK;
	}
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) { return true; }	//treat 0 and 1 letter strings as isograms

	TMap<char, bool> LastLetterSeen;			//Create the T-Map
	for (auto Letter : Word)					//Ranged for; create a 'Letter' for every element in 'Word'
	{
		Letter = tolower(Letter);				//makes everything lower-case
		if (LastLetterSeen[Letter])
			return false;						//this means letter is previously present in the string
		else
			LastLetterSeen[Letter] = true;		//this means the letter is not previously present so add it tot he TMap
	}
	return true;
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}
