// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Character/FRCharacterBase.h"
#include "FRGASCharacterPlayer.generated.h"

/**
 * 
 */
UCLASS()
class FINALREQUITAL_API AFRGASCharacterPlayer : public AFRCharacterBase, public IAbilitySystemInterface
{

	GENERATED_BODY()

public:
	AFRGASCharacterPlayer();

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	void SetupGASInputComponent();
	void GASInputPressed(int32 InputId);
	void GASInputReleased(int32 InputId);

protected:
	UPROPERTY(EditAnywhere, Category = "GAS")
	TObjectPtr<class UAbilitySystemComponent> ASC;

	UPROPERTY(EditAnywhere, Category="GAS")
	TArray<TSubclassOf<class UGameplayAbility>> StartAbilities;
};
