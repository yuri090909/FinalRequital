// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FRPlayerState.h"
#include "AbilitySystemComponent.h"

AFRPlayerState::AFRPlayerState()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	ASC->SetIsReplicated(true);
}

class UAbilitySystemComponent* AFRPlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}
