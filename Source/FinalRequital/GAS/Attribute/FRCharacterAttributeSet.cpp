// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Attribute/FRCharacterAttributeSet.h"
#include "FRDebugHelper.h"
#include "GameplayEffectExtension.h"

UFRCharacterAttributeSet::UFRCharacterAttributeSet() :
	AttackRange(100.0f),
	AttackRadius(50.f),
	AttackRate(30.0f),
	MaxAttackRange(300.0f),
	MaxAttackRadius(150.0f),
	MaxAttackRate(100.0f),
	MaxHealth(100.0f),
	Damage(0.0f)
{
	InitHealth(GetMaxHealth());
}

void UFRCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	/*if (Attribute == GetHealthAttribute())
	{
		// MaxHealth값을 넘거나 0아래로 내려가지 않도록 설정
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}*/

	if(Attribute == GetDamageAttribute())
	{
		NewValue = NewValue < 0.0f ? 0.0f : NewValue;
	}
}

void UFRCharacterAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	float MinimumHealth = 0.0f;

	if(Data.EvaluatedData.Attribute==GetHealthAttribute())
	{
		FR_LOG(FRLOG, Warning, TEXT("Direct HEALTH Access: %f "), GetHealth());
		SetHealth(FMath::Clamp(GetHealth(), MinimumHealth, GetMaxHealth()));
	}
	else if(Data.EvaluatedData.Attribute==GetDamageAttribute())
	{
		FR_LOG(FRLOG, Log, TEXT("Damage: %f "), GetDamage());
		SetHealth(FMath::Clamp(GetHealth()- GetDamage(),MinimumHealth, GetMaxHealth()));
		SetDamage(0.0f);
	}
}

/*void UFRCharacterAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    // 이펙트로만 활성화 하면 의미없음.
	if (Attribute == GetHealthAttribute())
	{
		FR_LOG(FRLOG, Log, TEXT("HEALTH: %f -> %f"), OldValue, NewValue);
	}
}*/
