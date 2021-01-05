// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomNameGenerator.h"
#include "Math/UnrealMathUtility.h"
#include "Containers/UnrealString.h"

FLetters Letters;

// Sets default values for this component's properties
URandomNameGenerator::URandomNameGenerator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URandomNameGenerator::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	
}


// Called every frame
void URandomNameGenerator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FString URandomNameGenerator::GenerateRandomName()
{
	
	Name.Reset();
	
	if (UserSetSyllable <= 1) {
		Syllables = 2;
	}else{
		Syllables = UserSetSyllable; 
	}
	
	
	//Letters.UsableNextLetterContainer.Num();
	

	//Set Previous Letter Type ENUM Randomly and append the first part of the name

	
	switch (FMath::RandRange(0, 4)) {
	case 0:
		PreviousLetterType_Enum = EPreviousLetterType_Enum::Consonant;
		AppendConsonantToName();
		SyllableLoopCount++;
		break;
	case 1:
		PreviousLetterType_Enum = EPreviousLetterType_Enum::Vowel;
		AppendVowelToName();
		SyllableLoopCount++;
		break;
	case 2:
		PreviousLetterType_Enum = EPreviousLetterType_Enum::DoubleVowel;
		AppendDoubleVowelToName();
		SyllableLoopCount++;
		break;
	case 3: 
		PreviousLetterType_Enum = EPreviousLetterType_Enum::ConsonantCombo;
		AppendConsonantComboToName();
		SyllableLoopCount++;
		break;
	case 4:
		PreviousLetterType_Enum = EPreviousLetterType_Enum::ConsonantVowelCombo;
		AppendRandomConsonantVowelComboToName();
		SyllableLoopCount++;
		break;

	}
	
	do {
		
		switch (PreviousLetterType_Enum) {
		case EPreviousLetterType_Enum::Consonant:
			switch (FMath::RandRange(0, 1)) {
			case 0:
				AppendVowelToName();
				PreviousLetterType_Enum = EPreviousLetterType_Enum::Vowel;
				SyllableLoopCount++;
				break;
			case 1:
				AppendDoubleVowelToName();
				PreviousLetterType_Enum = EPreviousLetterType_Enum::DoubleVowel;
				SyllableLoopCount++;
				break;
			}
			break;

		case EPreviousLetterType_Enum::Vowel:
			switch (FMath::RandRange(0, 2)) {
			case 0:
				AppendConsonantToName();
				PreviousLetterType_Enum = EPreviousLetterType_Enum::Consonant;
				SyllableLoopCount++;
				break;
			case 1:
				AppendDoubleConsonantToName();
				PreviousLetterType_Enum = EPreviousLetterType_Enum::DoubleConsonant;
				SyllableLoopCount++;
				break;
			case 2:
				AppendConsonantComboToName();
				PreviousLetterType_Enum = EPreviousLetterType_Enum::ConsonantCombo;
				SyllableLoopCount++;
				break;
			}
			break;

		case EPreviousLetterType_Enum::DoubleVowel:
			switch (FMath::RandRange(0, 1)) {
			case 0: 
				AppendConsonantToName();
				PreviousLetterType_Enum = EPreviousLetterType_Enum::Consonant;
				SyllableLoopCount++;
				break;
			case 1:
				AppendConsonantComboToName();
				PreviousLetterType_Enum = EPreviousLetterType_Enum::ConsonantCombo;
				SyllableLoopCount++;
				break;
			}
			break;

		case EPreviousLetterType_Enum::DoubleConsonant:
			switch (FMath::RandRange(0, 1)) {
			case 0:
				AppendVowelToName();
				PreviousLetterType_Enum = EPreviousLetterType_Enum::Vowel;
				SyllableLoopCount++;
				break;
			case 1:
				AppendDoubleVowelToName();
				PreviousLetterType_Enum = EPreviousLetterType_Enum::DoubleVowel;
				SyllableLoopCount++;
				break;
			}
			break;

		case EPreviousLetterType_Enum::ConsonantCombo:
			AppendVowelToName();
			PreviousLetterType_Enum = EPreviousLetterType_Enum::Vowel;
			SyllableLoopCount++;
			break;

		case EPreviousLetterType_Enum::ConsonantVowelCombo:
			switch (FMath::RandRange(0, 1)) {
			case 0:
				AppendVowelToName();
				PreviousLetterType_Enum = EPreviousLetterType_Enum::Vowel;
				SyllableLoopCount++;
				break;
			case 1:
				AppendDoubleVowelToName();
				PreviousLetterType_Enum = EPreviousLetterType_Enum::DoubleVowel;
				SyllableLoopCount++;
				break;
			}
			break;

		}
		
	} while (SyllableLoopCount != Syllables);

	RandomLetterRuleStart.Reset();
	LastAppendedLetterType.Reset();
	SyllableLoopCount = 0;

	return Name;
}

FString URandomNameGenerator::GetRandomConsonant()
{
	FString randConsonant;
	randConsonant = Letters.Consonants[FMath::RandRange(0, consonantsArraySize - 1)];
	return randConsonant;
}

FString URandomNameGenerator::GetRandomVowel()
{
	FString randVowel;
	randVowel = Letters.Vowels[FMath::RandRange(0, vowelsArraySize - 1)];
	return randVowel;
}

FString URandomNameGenerator::GetRandomDoubleVowel()
{
	FString randDoubleVowel;
	randDoubleVowel = Letters.DoubleVowels[FMath::RandRange(0, doubleVowelsArraySize - 1)];
	return randDoubleVowel;
}

FString URandomNameGenerator::GetRandomDoubleConsonants()
{
	FString randDoubleConsonant;
	randDoubleConsonant = Letters.DoubleConsonants[FMath::RandRange(0, doubleConsonantsArraySize - 1)];
	return randDoubleConsonant;
}

FString URandomNameGenerator::GetRandomConsonantCombo()
{
	FString randConsonantCombo;
	randConsonantCombo = Letters.ConsonantCombos[FMath::RandRange(0, consonantCombosArraySize - 1)];
	return randConsonantCombo;
}

FString URandomNameGenerator::GetRandomConsonantVowelCombo()
{
	FString randConsonantVowelCombo;
	randConsonantVowelCombo = Letters.ConsonantVowelCombos[FMath::RandRange(0, consonantVowelCombosArraySize - 1)];
	return randConsonantVowelCombo;
}

void URandomNameGenerator::AppendConsonantToName()
{
	Name.Append(GetRandomConsonant());
}

void URandomNameGenerator::AppendVowelToName()
{
	TCHAR apostrophe = '\'';
	TCHAR q = 'q';
	int32 lastCharIndex = Name.Len() - 1;
		

	if (SyllableLoopCount < Syllables) {
	if (lastCharIndex > 0) {
			if (Name[lastCharIndex] == apostrophe || Name[lastCharIndex] == q) {
				Name.Append(Letters.Vowels[FMath::RandRange(0, 4)]);
			}else{
				Name.Append(GetRandomVowel()); 
			}
		}
		Name.Append(GetRandomVowel());
	}
	else {
		if (PreviousLetterType_Enum == EPreviousLetterType_Enum::Vowel) {
			Name.Append(Letters.Vowels[FMath::RandRange(0, 3)]);
		}
		else {
			Name.Append(GetRandomVowel());
		}
	}
}

void URandomNameGenerator::AppendDoubleVowelToName()
{							
	
	if (SyllableLoopCount == 0) {
		int a = FMath::RandRange(0, doubleVowelsArraySize - 1);
		int b;

		if (a == 34) { 
			b = a - FMath::RandRange(1, 34);
			Name.Append(Letters.DoubleVowels[b-1]);
		}
		else {
			Name.Append(Letters.DoubleVowels[a]); 
		}
			
	}
	else { 
		if (PreviousLetterType_Enum == EPreviousLetterType_Enum::ConsonantVowelCombo) {
			Name.Append(Letters.DoubleVowels[usableDoubleVowelIndexAfterQUArraySize - 1]);
		}
		else {
			if (Name[Name.Len() -1] != 'q') {
				Name.Append(GetRandomDoubleVowel());
			}
			else {
				Name.Append(Letters.DoubleVowels[usableDoubleVowelIndexAfterQArraySize -1]);
			}
		}

	}
}

void URandomNameGenerator::AppendDoubleConsonantToName()
{
	
		
	if (FMath::RandRange(0, 1) == 0) {
		Name.Append(GetRandomDoubleConsonants());
		Name.Append("'");
	}
	else {
		Name.Append(GetRandomDoubleConsonants());
	}
}

void URandomNameGenerator::AppendConsonantComboToName()
{
	if (SyllableLoopCount < Syllables - 1) {
		if (SyllableLoopCount == 0) {
			if (FMath::RandRange(0, 1) == 0) {
				Name.Append(Letters.ConsonantCombos[FMath::RandRange(0, 2)]);
				Name.Append("'");
			}
			else {
				Name.Append(GetRandomConsonantCombo());
			}
		}
		else {
			Name.Append(GetRandomConsonantCombo());
		}
	}
}

void URandomNameGenerator::AppendRandomConsonantVowelComboToName()
{
	Name.Append(GetRandomConsonantVowelCombo());
}
