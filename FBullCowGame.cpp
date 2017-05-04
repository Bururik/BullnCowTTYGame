#pragma once

#include "FBullCowGame.h"
#include <map>

// to make syntax Unreal friendly
#define Tmap std::map // (the #define) this is like using the using syntax as seen below but more simple (more research needed)
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } // default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const
{
	Tmap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,15}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}


void FBullCowGame::Reset()
{	
	const FString HIDDEN_WORD = "planet";
	
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) 
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))
	{ // this also takes care of non-latin characters but the warning is not specific enough
		return EGuessStatus::Not_Lowercase; 
	}
	else if (Guess.length() != GetHiddenWordLength()) 
	{
		return EGuessStatus::Wrong_Length; 
	}
	else if (false) // TODO make a specific warning about non-latin characters (order of if else muct change)
	{
		return EGuessStatus::Non_Latin_Characters; 
	}
	else
	{
		return EGuessStatus::Ok;
	}
}

// receives VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming the same length as guess

	//loop through all letters in the hidden word
	
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) 
	{
		//compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			// if letters match then 
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				// if letters are in the same place
				if (MHWChar == GChar) 
				{
					// incriment bulls 
					BullCowCount.Bulls++;
				}
				// increment cows if they aren't in the same place
				else 
				{
					//increment cows
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) 
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	Tmap<char, bool> LetterSeen; // setup our map
	for (auto Letter : Word)	 // for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case

		if (LetterSeen[Letter]) { // if the letter is in the map
			return false; // we DO NOT have an isogram
		}
		else {
			LetterSeen[Letter] = true; // add letter to the map as seen
		}
	}
	return true; // for exampe in cases where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word) 
	{
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}
