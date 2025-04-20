// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FRGASCharacterPlayer.h"
#include "AbilitySystemComponent.h"
#include "Player/FRPlayerState.h"
#include "EnhancedInputComponent.h"

AFRGASCharacterPlayer::AFRGASCharacterPlayer()
{
	// ASC는 플레이어스테트에서 관리
	ASC = nullptr;
}

void AFRGASCharacterPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AFRPlayerState* GASPS = GetPlayerState<AFRPlayerState>();

	if(GASPS)
	{
		ASC = GASPS->GetAbilitySystemComponent();
		ASC->InitAbilityActorInfo(GASPS, this);

		int32 InputId = 0;
		for(const auto& StartAbility : StartAbilities)
		{
			FGameplayAbilitySpec StartSpec(StartAbility);
			StartSpec.InputID = InputId++;
			ASC->GiveAbility(StartSpec);

			SetupGASInputComponent();
		}
	}
}

void AFRGASCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	SetupGASInputComponent();
}

void AFRGASCharacterPlayer::SetupGASInputComponent()
{
	if(IsValid(ASC) && IsValid(InputComponent))
	{
		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AFRGASCharacterPlayer::GASInputPressed,0);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AFRGASCharacterPlayer::GASInputReleased,0);
	}
}

void AFRGASCharacterPlayer::GASInputPressed(int32 InputId)
{
	FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromInputID(InputId);
	if(Spec)
	{
		Spec->InputPressed = true;
		if(Spec->IsActive())
		{
			ASC->AbilitySpecInputPressed(*Spec);
		}
		else
		{
			ASC->TryActivateAbility(Spec->Handle);
		}
	}
}

void AFRGASCharacterPlayer::GASInputReleased(int32 InputId)
{
	FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromInputID(InputId);
	if (Spec)
	{
		Spec->InputPressed = false;
		if (Spec->IsActive())
		{
			ASC->AbilitySpecInputReleased(*Spec);
		}
	}
}

class UAbilitySystemComponent* AFRGASCharacterPlayer::GetAbilitySystemComponent() const
{
	return ASC;
}
