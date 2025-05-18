// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FRHUDWidget.h"
#include "Components/Image.h"

UFRHUDWidget::UFRHUDWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UFRHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ShowCrosshair(false);
	
}

void UFRHUDWidget::ShowCrosshair(bool bShow)
{
	if (Crosshair)
	{
		Crosshair->SetVisibility(bShow ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}
