// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/FRUserWidget.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "FRDebugHelper.h"

class UAbilitySystemComponent* UFRUserWidget::GetAbilitySystemComponent() const
{
	return ASC;
}

void UFRUserWidget::SetAbilitySystemComponent(AActor* InOwner)
{
	if(IsValid(InOwner))
	{
		ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InOwner);
		//FR_LOG(FRLOG, Warning, TEXT("UFRUserWidget::SetASC ASC Valid?: %s"), ASC ? TEXT("Yes") : TEXT("No"));
	}
}
