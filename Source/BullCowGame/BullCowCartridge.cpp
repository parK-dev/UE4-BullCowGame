// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    Isograms = GetValidWords(WordList);

    SetupGame(); //Setting up the game
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // Activates When the player hits enter
{
   
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else
    {
        ProcessPlayerGuess(PlayerInput);
    }
}

void UBullCowCartridge::SetupGame() // Sets hiddenword, lives and welcomes the player
{
    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
    Lives = HiddenWord.Len() * 2;
    bGameOver = false;
    
    PrintLine(TEXT("Player, welcome!"));
    PrintLine(TEXT("\nClick to control your movement."));
    PrintLine(TEXT("Press TAB to access the terminal."));
    PrintLine(TEXT("Once you have accessed the terminal, guess the %i letter isogram."), HiddenWord.Len());
    PrintLine(TEXT("\nThe hidden word is %i characters long.\n"),HiddenWord.Len());
}
void UBullCowCartridge::GameOver()
{
    PrintLine(TEXT("\nPress enter to play again..."));
    bGameOver = true;
}

void UBullCowCartridge::ProcessPlayerGuess(const FString& Guess) // looks at the player's input and reacts accordingly
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("\nYou won!"));
        PrintLine(TEXT("\nPress Enter to play again..."));
        bGameOver = true;
        return;
    }

    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("\nOops, don't forget! \nThe hidden word is %i characters long! Try again.\n"), HiddenWord.Len());
        return;
    }

    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("An isogram cannot contain the same letter\n twice!\nTry again.\n"));

        return;
    }

    //Remove a life due to wrong guess
    --Lives;
    PrintLine(TEXT("\nWrong guess. Try again."));
    PrintLine(TEXT("\nYou have %i lives remaining.\n"), Lives);

    if (Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("\nYou ran out of lives."));
        PrintLine(TEXT("\nGame Over!"));
        PrintLine(TEXT("\nThe hidden word was %s."), *HiddenWord);
        GameOver();
        return;
    }

    //Show the bulls and cows to the player
    int32 Bulls, Cows;
    GetBullCow(Guess, Bulls, Cows);

    PrintLine(TEXT("You have %i Bulls and %i Cows."), Bulls, Cows);

}
bool UBullCowCartridge::IsIsogram(const FString& Word) const //Checks if the player guest is an isogram
{

    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }
        }
    }

    return true;
}

// Creates a list of words by taking out non-isograms from the original word list
TArray <FString> UBullCowCartridge::GetValidWords(const TArray <FString>& WordList) const
{
    TArray <FString> ValidWords;

    for (auto Word : WordList)
    {
        if (IsIsogram(Word))
        {
            ValidWords.Emplace(Word);
        }
    }

    return ValidWords;
}

void UBullCowCartridge::GetBullCow(const FString& Guess, int32& BullCount, int32& CowCount) const
{
    BullCount = 0;
    CowCount = 0;

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            BullCount++;
            continue;
        }
        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                CowCount++;
                break;
            }
        }
    }
}