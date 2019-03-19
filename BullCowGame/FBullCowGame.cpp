/* This file includes function definitions
 * about game logic. For function declarations 
 * look FBullCowGame.h file. */

#pragma once
#include "FBullCowGame.h"
#include <cctype>
#include <map>
#define TMap std::map

using uint16 = unsigned short;

FBullCowGame::FBullCowGame() { Reset(); }
uint16 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
size_t FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bIsGameWon; }


size_t FBullCowGame::GetMaxTries() const
{
	TMap<size_t, size_t> WordLengthToMaxTries{ {3,4},{4,7},{5,10},{6,15},{7,20} };
	return WordLengthToMaxTries[GetHiddenWordLength()];
}

FString FBullCowGame::MakeGuessLower(FString UserGuess)
{
	for (auto &Guess : UserGuess)
	{
		Guess = std::tolower(Guess);
	}
	return UserGuess;
}

EGuessStatus FBullCowGame::CheckGuessValidity(const FString& UserGuess) const
{
	if (GetHiddenWordLength() != UserGuess.length())
	{
		return EGuessStatus::wrong_length;
	}
	if (!IsIsogram(UserGuess))
	{
		return EGuessStatus::not_isogram;
	}
	return EGuessStatus::ok;
}

bool FBullCowGame::IsIsogram(FString UserGuess)
{
	TMap<char,bool> LettersMap;
	for (auto UGChar : UserGuess)
	{
		if(LettersMap[UGChar])
		{
			return false;
		}
		LettersMap[UGChar] = true;
	}
	return true;
}


//Receives a valid guess and submits bulls and cows.
FBullCowCount FBullCowGame::SubmitBullsAndCows(FString UserGuess)
{
	FBullCowCount BullCowCount;
	++MyCurrentTry;
	//MHChar stands for: MyHiddenWordChar; UGChar stands for: UserGuessChar.
	for (size_t MHWChar = 0; MHWChar < MyHiddenWord.length(); ++MHWChar)
	{
		for (size_t UGChar = 0; UGChar < MyHiddenWord.length(); ++UGChar)
		{
			if (MyHiddenWord[MHWChar] == UserGuess[UGChar])
			{
				if (MHWChar == UGChar)
				{
					++BullCowCount.Bulls;
				}
				else
				{
					++BullCowCount.Cows;
				}
			}
		}
	}
	if(BullCowCount.Bulls==GetHiddenWordLength())
	{
		bIsGameWon = true;
	}
	return BullCowCount;
}

void FBullCowGame::ChooseDifficulty(const uint16 WordLength)
{
	TMap<uint16, FString> WordLengthToHiddenWord{ {3,"oba"},{4,"kale"},{5,"avize"},{6,"klavye"},{7,"izogram"} };
	MyHiddenWord = WordLengthToHiddenWord[WordLength];
}

//TODO: Use File operations to store a dictionary and load this file at beginning of game.
//TODO: Extend that dictionary file while user enters valid guesses. 
void FBullCowGame::Reset()
{
	MyCurrentTry = 1;
	bIsGameWon = false;
	system("color f5");
	system("cls");
	return;
}
