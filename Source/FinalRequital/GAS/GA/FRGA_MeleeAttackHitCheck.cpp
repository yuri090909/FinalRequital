// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/FRGA_MeleeAttackHitCheck.h"
#include "GAS/AT/FRAT_Trace.h"
#include "GAS/TA/FRTA_Trace.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "FRDebugHelper.h"
#include "GAS/Attribute/FRCharacterAttributeSet.h"

UFRGA_MeleeAttackHitCheck::UFRGA_MeleeAttackHitCheck()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UFRGA_MeleeAttackHitCheck::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	//D(FString::Printf(TEXT("TRIGGER1!")));

	UFRAT_Trace* AttackTraceTask = UFRAT_Trace::CreateTask(this, AFRTA_Trace::StaticClass());
	AttackTraceTask->OnComplete.AddDynamic(this, &UFRGA_MeleeAttackHitCheck::OnTraceResultCallback);
	AttackTraceTask->ReadyForActivation();

}

void UFRGA_MeleeAttackHitCheck::OnTraceResultCallback(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	if(UAbilitySystemBlueprintLibrary::TargetDataHasHitResult(TargetDataHandle,0))
	{
		// 타겟데이터 0번째 배열에 결과값이 존재하는지
		FHitResult HitResult = UAbilitySystemBlueprintLibrary::GetHitResultFromTargetData(TargetDataHandle, 0);
		D(FString::Printf(TEXT("Target: %s Detected"), *(HitResult.GetActor()->GetName())));

		UAbilitySystemComponent* SourceASC = GetAbilitySystemComponentFromActorInfo_Checked();
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitResult.GetActor());
		if(!SourceASC||!TargetASC)
		{
			// 감지한 액터의 ASC(타겟ASC)가 없고 나의 ASC(소스ASC)의 액터중 하나라도 없으면 에러
			FR_LOG(FRLOG, Error, TEXT("ASC Not Found!"));
			return;
		}
		//소스는 데미지를 불러오고 타겟은 값을 변경해줘야함.
		const UFRCharacterAttributeSet* SourceAttribute = SourceASC->GetSet<UFRCharacterAttributeSet>();
		// const UFRCharacterAttributeSet* TargetAttribute = SourceASC->GetSet<UFRCharacterAttributeSet>();
		// 값을 변경해야하는데 const 이기 때문에 C++로우레벨 const 케스팅 진행
		UFRCharacterAttributeSet* TargetAttribute = const_cast<UFRCharacterAttributeSet*>(TargetASC->GetSet<UFRCharacterAttributeSet>());
		if(!SourceAttribute||!TargetAttribute)
		{
			FR_LOG(FRLOG, Error, TEXT("Attribute Not Found!"));
			return;
		}

		const float AttackDamage = SourceAttribute->GetAttackRate();
		TargetAttribute->SetHealth(TargetAttribute->GetHealth() - AttackDamage);
	}

	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
