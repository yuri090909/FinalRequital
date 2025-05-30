// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "FRGA_SpawnArrow.generated.h"


/**
 * 
 */
UCLASS()
class FINALREQUITAL_API UFRGA_SpawnArrow : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UFRGA_SpawnArrow();

	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrow")
	TSubclassOf<class AFRArrowProjectile> ArrowClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrow")
	float FirePower = 1000.f;

	void SpawnAndFireArrow();
};
