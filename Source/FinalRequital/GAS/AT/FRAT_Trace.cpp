// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AT/FRAT_Trace.h"
#include "GAS/TA/FRTA_Trace.h"
#include "AbilitySystemComponent.h"

UFRAT_Trace::UFRAT_Trace()
{
}

UFRAT_Trace* UFRAT_Trace::CreateTask(UGameplayAbility* OwningAbility, TSubclassOf<AFRTA_Trace> TargetActorClass)
{
	UFRAT_Trace* NewTask = NewAbilityTask<UFRAT_Trace>(OwningAbility);
	NewTask->TargetActorClass = TargetActorClass;
	return NewTask;
}

void UFRAT_Trace::Activate()
{
	Super::Activate();

	SpawnAndInitializeTargetActor();
	FinalizeTargetActor();

	SetWaitingOnAvatar();
}

void UFRAT_Trace::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);

	if(SpawnedTargetActor)
	{
		SpawnedTargetActor->Destroy();
	}
}

void UFRAT_Trace::SpawnAndInitializeTargetActor()
{
	SpawnedTargetActor = Cast<AFRTA_Trace>(Ability->GetWorld()->SpawnActorDeferred<AGameplayAbilityTargetActor>
		(TargetActorClass, FTransform::Identity, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn));
	if(SpawnedTargetActor)
	{
		SpawnedTargetActor->SetShowDebug(true);
		SpawnedTargetActor->TargetDataReadyDelegate.AddUObject(this, &UFRAT_Trace::OnTargetDataReadyCallback);
	}
}

void UFRAT_Trace::FinalizeTargetActor()
{
	UAbilitySystemComponent* ASC = AbilitySystemComponent.Get();

	if(ASC)
	{
		const FTransform SpawnTransform = ASC->GetAvatarActor()->GetTransform();
		SpawnedTargetActor->FinishSpawning(SpawnTransform);

		ASC->SpawnedTargetActors.Push(SpawnedTargetActor);
		SpawnedTargetActor->StartTargeting(Ability);
		SpawnedTargetActor->ConfirmTargetingAndContinue();
	}
}

void UFRAT_Trace::OnTargetDataReadyCallback(const FGameplayAbilityTargetDataHandle& DataHandle)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnComplete.Broadcast(DataHandle);
	}
	
	EndTask();
}
