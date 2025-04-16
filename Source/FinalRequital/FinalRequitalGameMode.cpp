// Copyright Epic Games, Inc. All Rights Reserved.

#include "FinalRequitalGameMode.h"
#include "FinalRequitalCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFinalRequitalGameMode::AFinalRequitalGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
