// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AN_GASMeleeAttackHitCheck.h"
#include "AbilitySystemBlueprintLibrary.h"
UAN_GASMeleeAttackHitCheck::UAN_GASMeleeAttackHitCheck()
{
	ComboAttackLevel = 1.0f;
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
			// 페이로드데이터에 콤보어택래밸에 대한 정보를 추가
			FGameplayEventData PayloadData;
			PayloadData.EventMagnitude = ComboAttackLevel;

			// 에님노티파이에서 설정한 트리거게임플레이태그를 통해서 자동으로 Activate를 호출하게됨. MeleeAttackHitCheck
			// 페이로드데이터를 함께 전달.
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerActor, TriggerGameplayTag, PayloadData);
		}
	}
}
