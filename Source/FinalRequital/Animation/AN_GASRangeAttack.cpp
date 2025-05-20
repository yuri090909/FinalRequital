// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AN_GASRangeAttack.h"
#include "AbilitySystemBlueprintLibrary.h"

UAN_GASRangeAttack::UAN_GASRangeAttack()
{
}

FString UAN_GASRangeAttack::GetNotifyName_Implementation() const
{
	return TEXT("GASRangeAttackHit");
}

void UAN_GASRangeAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		AActor* OwnerActor = MeshComp->GetOwner();
		if (OwnerActor)
		{
			// 페이로드데이터에 콤보어택래밸에 대한 정보를 추가
			FGameplayEventData PayloadData;

			// 에님노티파이에서 설정한 트리거게임플레이태그를 통해서 자동으로 Activate를 호출하게됨. MeleeAttackHitCheck
			// 페이로드데이터를 함께 전달.
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerActor, TriggerGameplayTag, PayloadData);
		}
	}
}

