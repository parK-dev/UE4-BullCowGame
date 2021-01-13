// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void SetupGame();
	void GameOver();
	void ProcessPlayerGuess(const FString& Guess);
	bool IsIsogram(const FString& Word) const;
	TArray <FString> GetValidWords(const TArray<FString>& WordList) const;
	void GetBullCow(const FString& Guess, int32& BullCount, int32& CowCount) const;

	// Your declarations go below!
	private:
	
	FString HiddenWord;
	int32 Lives;
	FString TryAgainInput;
	bool bGameOver;
	TArray <FString> Isograms;
};
