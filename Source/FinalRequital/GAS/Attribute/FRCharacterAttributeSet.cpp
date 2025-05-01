// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Attribute/FRCharacterAttributeSet.h"
#include "FRDebugHelper.h"

UFRCharacterAttributeSet::UFRCharacterAttributeSet() :
	AttackRange(100.0f),
	MaxAttackRange(300.0f),
	AttackRadius(50.0f),
	AttackRate(30.0f),
	MaxAttackRadius(150.0f),
	MaxAttackRate(100.0f),
	MaxHealth(100.0f)
{
	InitHealth(GetMaxHealth());
}

void UFRCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute == GetHealthAttribute())
	{
		// MaxHealth값을 넘거나 0아래로 내려가지 않도록 설정
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
}

void UFRCharacterAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	if (Attribute == GetHealthAttribute())
	{
		FR_LOG(FRLOG, Log, TEXT("HEALTH: %f -> %f"), OldValue, NewValue);
	}
}
