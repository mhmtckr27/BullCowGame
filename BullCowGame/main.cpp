/* This is the main file. This is responsible for
 * direct interaction with user.
 * Printing screen operations are here. 
 * For Game Logic, look FBullCowGame.cpp file. */

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"


using uint16 = unsigned short;
using int32 = int;
using FText = std::string;

FText GetValidGuess();
void PrintIntro();
void PlayGame();
bool AskToPlayAgain();
void PrintGameSummary();
void SetDifficulty();


FBullCowGame BCGame;

int main()
{
	do
	{
		BCGame.Reset();
		SetDifficulty();
		PrintIntro();
		PlayGame();
		PrintGameSummary();
	} while (AskToPlayAgain());
	return 0;
}


void PrintIntro()
{
	const size_t WordLength = BCGame.GetHiddenWordLength();
	std::cout << R"( ____        _ _                       _    _____)" << std::endl;
	std::cout << R"(|  _ \      | | |                     | |  / ____|)" << std::endl;
	std::cout << R"(| |_) |_   _| | |___    __ _ _ __   __| | | |     _____      _____)" << std::endl;
	std::cout << R"(|  _ <| | | | | / __|  / _` | '_ \ / _` | | |    / _ \ \ /\ / / __|)" << std::endl;
	std::cout << R"(| |_) | |_| | | \__ \ | (_| | | | | (_| | | |___| (_) \ V  V /\__ \)" << std::endl;
	std::cout << R"(|____/ \__,_|_|_|___/  \__,_|_| |_|\__,_|  \_____\___/ \_/\_/ |___/)" << std::endl;
	std::cout << "\n\nWelcome to the Bulls and Cows, a stupid word game for jet brains." << std::endl << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << R"(   /-------\ /          \ /-------\ )" << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl << std::endl;
	std::cout << "Can you guess the " << WordLength << " letter isogram I'm thinking of?" << std::endl << std::endl;
}


void PlayGame()
{
	const size_t MaxTries = BCGame.GetMaxTries();
	//use while instead of for to check guess validity
	while (!BCGame.IsGameWon() && MaxTries >= BCGame.GetCurrentTry())
	{
		const FText UserGuess = GetValidGuess();
		const FBullCowCount BullCowCount = BCGame.SubmitBullsAndCows(UserGuess);
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " . Cows = " << BullCowCount.Cows << "\n\n";
	}
	return;
}


FText GetValidGuess()
{
	const uint16 CurrentTry = BCGame.GetCurrentTry();
	while(true)
	{
		std::cout << "You have " << BCGame.GetMaxTries() - CurrentTry + 1 << " Guesses Left. Enter your guess: ";
		FText UserGuess;
		getline(std::cin, UserGuess);
		UserGuess = FBullCowGame::MakeGuessLower(UserGuess);
		const EGuessStatus GuessStatus = BCGame.CheckGuessValidity(UserGuess);
		switch (GuessStatus)
		{
		case EGuessStatus::wrong_length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::not_isogram:
			std::cout << "Please enter an isogram.\n";
			break;
		default:
			return UserGuess;
			break;
		}
		std::cout << std::endl;
	}
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n): ";
	FText Response;
	getline(std::cin, Response);
	return (Response[0] == 'y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Well Done!\n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
	std::cout << std::endl;
	return;
}

void SetDifficulty()
{
	FText UserInput;
	do
	{
		std::cout << "Select difficulty [3 to 7]: ";
		getline(std::cin, UserInput);
	} while (!isdigit(UserInput[0]) || (std::stoi(UserInput) < 3) || (std::stoi(UserInput) > 7));
	const uint16 DifficultyLevel = std::stoi(UserInput);
	BCGame.ChooseDifficulty(DifficultyLevel);
	return;
}