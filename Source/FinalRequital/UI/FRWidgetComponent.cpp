// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FRWidgetComponent.h"
#include "UI/FRUserWidget.h"

void UFRWidgetComponent::InitWidget()
{
	Super::InitWidget();

	UFRUserWidget* GASUserWidget = Cast<UFRUserWidget>(GetWidget());
	if (GASUserWidget)
	{
		GASUserWidget->SetAbilitySystemComponent(GetOwner());
	}
	/*if (UFRUserWidget* FRUserWidget = Cast<UFRUserWidget>(GetWidget()))
	{
		FRUserWidget->SetAbilitySystemComponent(GetOwner());
	}*/
}
