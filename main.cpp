/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// To make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game, which we re-use across plays

int main()
{
	do {
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());

	return 0;
}

void PrintIntro()
{
	std::cout << "\n		Wilkommen to Bulls and Cows!!!1!" << std::endl;
	std::cout << "       ____        ____" << std::endl;
	std::cout << "          /        \\" << std::endl;
	std::cout << "         (__________)                  " << std::endl;
	std::cout << "             (oo)						" << std::endl;
	std::cout << "      /-------\\/		   ,__," << std::endl;
	std::cout << "     / |     ||			   (00)____" << std::endl;
	std::cout << "    *  ||----||			   (__)    )\\\n";
	std::cout << "       ~~    ~~		   	      ||--|| *" << std::endl;
/*
				             |       ____        ____
                             |          /        \
                             |         (__________)                  
                             |             (oo)						
                             |      /-------\/				   ,__,
                             |     / |     ||				   (00)____
                             |    *  ||----||				   (__)    )\
                             |       ~~    ~~					  ||--|| *
*/
	std::cout << "Rules: Correctly guess a " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram to win in " << BCGame.GetMaxTries() << " or less moves.\n" << std::endl;
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while game 
	// is NOT won and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		// Submit valid guess to the game and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess() 
{	
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Round " << CurrentTry << " out of "<< BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters. \n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lower case letters. \n\n";
			break;
		case EGuessStatus::Non_Latin_Characters:
			std::cout << "Please donot enter numbers or non-latin characters. \n\n";
				break;
		default:
			// assume the guess is valid 
			break;
		}
	} while (Status != EGuessStatus::Ok); // keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word? (y/n)";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');
}

// we only print the game summary
void PrintGameSummary() 
{
	if (BCGame.IsGameWon()) {
		std::cout << "Congratulations!!! you've wond this weird ass game!!!11!!1! \n\n";
	}
	else {
		std::cout << "Yousuck! ya' Jackass! \n\n";
	}
	
	return;
}
