// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AN_GASMeleeAttackHitCheck.h"
#include "AbilitySystemBlueprintLibrary.h"
UAN_GASMeleeAttackHitCheck::UAN_GASMeleeAttackHitCheck()
{
}

FString UAN_GASMeleeAttackHitCheck::GetNotifyName_Implementation() const
{
	return TEXT("GASAttackHitCheck");
}

void UAN_GASMeleeAttackHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if(MeshComp)
	{
		AActor* OwnerActor = MeshComp->GetOwner();
		if(OwnerActor)
		{
			FGameplayEventData PayloadData;
			// 에님노티파이에서 설정한 트리거게임플레이태그를 통해서 자동으로 Activate를 호출하게됨.
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerActor, TriggerGameplayTag, PayloadData);
		}
	}
}
