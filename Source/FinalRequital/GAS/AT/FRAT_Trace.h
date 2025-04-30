// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "FRAT_Trace.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTraceResultDelegate, const FGameplayAbilityTargetDataHandle&, TargetDataHandle);
/**
 *  AT와 TA 사이의 실행 흐름
============================================================

[AT]                                           [TA]
------------------------------------------------------------
1. 타겟 액터 생성 시작
   SpawnActorDeferred()
                                               → 액터 초기 변수 설정

2. TA의 타겟팅 결과 델리게이트 구독                    
3. 타겟 액터 생성 마무리
   FinishSpawning()							   → 타겟팅 시작
                                                 StartTargeting()
                                               → 소스 액터 설정
                                                 (필요시 레티클 액터 생성)
                                               → 타겟 컨펌
                                                 ConfirmTargeting()
                                               → 최종 타겟 데이터 생성
                                               → TargetDataReady 델리게이트를 통해
                                                 최종 타겟 데이터 전달
4. 태스크 종료
   EndTask()
 */
UCLASS()
class FINALREQUITAL_API UFRAT_Trace : public UAbilityTask
{
	GENERATED_BODY()

public:
	UFRAT_Trace();

	static UFRAT_Trace* CreateTask(UGameplayAbility* OwningAbility, TSubclassOf<class AFRTA_Trace> TargetActorClass);
	virtual void Activate() override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

	void SpawnAndInitializeTargetActor();
	void FinalizeTargetActor();

protected:
	void OnTargetDataReadyCallback(const FGameplayAbilityTargetDataHandle& DataHandle);

public:
	FTraceResultDelegate OnComplete;

protected:
	UPROPERTY()
	TSubclassOf<class AFRTA_Trace> TargetActorClass;

	UPROPERTY()
	TObjectPtr<class AFRTA_Trace> SpawnedTargetActor;
};
