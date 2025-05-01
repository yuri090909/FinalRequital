// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FRPlayerState.h"
#include "AbilitySystemComponent.h"
#include "GAS/Attribute/FRCharacterAttributeSet.h"

AFRPlayerState::AFRPlayerState()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	ASC->SetIsReplicated(true);
	AttributeSet = CreateDefaultSubobject<UFRCharacterAttributeSet>(TEXT("AttributeSet"));
}

class UAbilitySystemComponent* AFRPlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}
