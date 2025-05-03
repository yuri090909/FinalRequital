// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "FRGA_MeleeAttackHitCheck.generated.h"

/**
 * 밀리어택 애님몽타주에서 트리거할 게임플레이태그를 설정
 * 이 클래스를 상속받은 블루프린트클래스에서 트리거태그를 동일하게 설정
 * 자동으로 동일하게 설정된 게임플레이태그로 인해서 ActivateAbility가 호출됨.
 */
UCLASS()
class FINALREQUITAL_API UFRGA_MeleeAttackHitCheck : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UFRGA_MeleeAttackHitCheck();

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	UFUNCTION()
	void OnTraceResultCallback(const FGameplayAbilityTargetDataHandle& TargetDataHandle);

	UPROPERTY(EditAnywhere, Category = GAS)
	TSubclassOf<class UGameplayEffect> AttackDamageEffect;

	float CurrentLevel;
};
