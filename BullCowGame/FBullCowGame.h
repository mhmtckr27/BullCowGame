#pragma once
#include <string>

using uint16 = unsigned short;
using FString = std::string;

struct FBullCowCount
{
	uint16 Bulls = 0;
	uint16 Cows = 0;
};

enum class EGuessStatus
{
	ok,
	wrong_length,
	not_isogram
};

class FBullCowGame
{
public:
	FBullCowGame();

	size_t GetMaxTries() const;			//DONE
	uint16 GetCurrentTry() const;		//DONE
	size_t GetHiddenWordLength() const;	//DONE
	EGuessStatus CheckGuessValidity(const FString&) const;//DONE
	bool IsGameWon() const;			//DONE

	void Reset();	//DONE
	static FString MakeGuessLower(FString);	//DONE

	FBullCowCount SubmitBullsAndCows(FString);//DONE
	void ChooseDifficulty(uint16); //DONE



private:
	uint16 MyCurrentTry{};
	bool bIsGameWon;
	FString MyHiddenWord;

	static bool IsIsogram(FString);			//DONE
};