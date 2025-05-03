// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "FRMonsterBase.generated.h"

UCLASS()
class FINALREQUITAL_API AFRMonsterBase : public ACharacter , public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	AFRMonsterBase();

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void PossessedBy(AController* NewController) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;

	UPROPERTY()
	TObjectPtr<class UFRCharacterAttributeSet> AttributeSet;

public:
	UPROPERTY(EditAnywhere, Category = GAS)
	TSubclassOf<class UGameplayEffect> InitStatEffect;

	UPROPERTY(EditAnywhere, Category = GAS)
	float Level;

	//UPROPERTY(EditAnywhere, Category = HP)
	//TSubclassOf<class UUserWidget> HpWidgetClassRef;

	UPROPERTY(EditAnywhere, Category = HP)
	TObjectPtr<class UFRWidgetComponent> HpBar;
};
