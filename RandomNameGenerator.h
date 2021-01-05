// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RandomNameGenerator.generated.h"

UENUM()
enum class EPreviousLetterType_Enum : uint8{

	Consonant,
	Vowel,
	DoubleVowel,
	DoubleConsonant,
	ConsonantCombo,
	ConsonantVowelCombo
};

USTRUCT()
struct FLetters {

	GENERATED_BODY()

	UPROPERTY()
	TArray<FString> Consonants{"b","c","d","f","g","h","j","k","l","m","n","p","q","r","s","t","v","w","x","z"};
	
	UPROPERTY()
	TArray<FString> Vowels{"a","e","i","o","u","y"};
	

	UPROPERTY()
		TArray<FString> DoubleVowels{"ae","ai","ao","au","ay","ea","ee","ei","eo","eu","ey","ia","ie","ii","io","iu","iy","oa","oe","oi","oo","ou","oy","ua","ue","ui","uo","uu","uy","ya","ye","yi","yo","yu","yy","aa"};

	UPROPERTY()
		TArray<FString> DoubleConsonants{"bb","cc","dd","ff","gg","kk","ll","mm","nn","pp","rr","ss","tt","vv","zz"};

	UPROPERTY()
		TArray<FString> ConsonantCombos{"ch","ph","sh","tch"};

	UPROPERTY()
		TArray<FString> ConsonantVowelCombos{"qu"};

	UPROPERTY()
		TArray<FString> UsableNextLetterContainer{"Consonant","Vowel","DoubleVowel","ConsonantCombo","ConsonantVowelCombo"};

	UPROPERTY()
		TArray<int32> UsableDoubleVowelIndexAfterQU{0,1,2,4,5,6,7,8,9,10,13,17,18,19,20,29,30,31,32,33};

	UPROPERTY()
		TArray<int32> UsableDoubleVowelIndexAfterQ{23,24,25,26};

};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ORION_API URandomNameGenerator : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URandomNameGenerator();
	
	UFUNCTION(BLUEPRINTCALLABLE)
	FString GenerateRandomName();

	UFUNCTION()
	FString GetRandomConsonant();

	UFUNCTION()
	FString GetRandomVowel();

	UFUNCTION()
	FString GetRandomDoubleVowel();

	UFUNCTION()
	FString GetRandomDoubleConsonants();

	UFUNCTION()
	FString GetRandomConsonantCombo();

	UFUNCTION()
	FString GetRandomConsonantVowelCombo();

	UFUNCTION()
	void AppendConsonantToName();

	UFUNCTION()
	void AppendVowelToName();

	UFUNCTION()
	void AppendDoubleVowelToName();

	UFUNCTION()
	void AppendDoubleConsonantToName();

	UFUNCTION()
	void AppendConsonantComboToName();

	UFUNCTION()
	void AppendRandomConsonantVowelComboToName();

	UPROPERTY()
	int Syllables;

	UPROPERTY()
	int SyllableLoopCount = 0;

	UPROPERTY()
	FString RandomLetterRuleStart;

	UPROPERTY()
	FString Name;

	UPROPERTY()
	FString	LastAppendedLetterType;

	UPROPERTY()
	EPreviousLetterType_Enum  PreviousLetterType_Enum;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int UserSetSyllable = FMath::Clamp(UserSetSyllable, 2, 100);

	UPROPERTY()
	int vowelsArraySize = 6;
	UPROPERTY()
	int consonantsArraySize = 20;
	UPROPERTY()
	int doubleVowelsArraySize = 36;
	UPROPERTY()
		int doubleConsonantsArraySize = 15;
	UPROPERTY()
		int consonantCombosArraySize = 4;
	UPROPERTY()
		int consonantVowelCombosArraySize = 1;
	UPROPERTY()
		int usableNextLetterContainerArraySize = 5;
	UPROPERTY()
		int usableDoubleVowelIndexAfterQUArraySize = 20;
	UPROPERTY()
		int usableDoubleVowelIndexAfterQArraySize = 4;
	


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};


