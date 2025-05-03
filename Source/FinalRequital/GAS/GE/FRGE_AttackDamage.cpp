// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GE/FRGE_AttackDamage.h"

UFRGE_AttackDamage::UFRGE_AttackDamage()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;

	FGameplayModifierInfo HealthModifier;

	Modifiers.Add(HealthModifier);
}
