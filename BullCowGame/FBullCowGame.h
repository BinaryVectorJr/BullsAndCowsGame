/* The game logic i.e. the classes and other structures we're using.
It is based on the fundamental concept of Mastermind */ 

#pragma once

#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum EGuessWordStatus
{
	Invalid,											//Always try to give first error as Invalid
	OK,
	Case_Mismatch,
	Wrong_Length,
	Not_Isogram,
};

class FBullCowGame										//The actual game class
{
public:
	FBullCowGame();										//Constructor Initialized

	int32 GetMaxTries() const;							//Methods are like variable names only with () at the end
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const;
	EGuessWordStatus CheckGuessValidity(FString) const;
	
	void Reset();										//all these functions are called a METHOD

	FBullCowCount SubmitValidGuess(FString Guess);		//once a valid guess comes in update the number of tries

private:
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameWon;

	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};