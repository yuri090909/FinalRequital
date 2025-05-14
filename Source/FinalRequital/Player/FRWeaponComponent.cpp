// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FRWeaponComponent.h"
#include "Player/FRGASCharacterPlayer.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

UFRWeaponComponent::UFRWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMeshComponent"));
	WeaponMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponMeshComponent->SetOnlyOwnerSee(false);
	WeaponMeshComponent->bCastDynamicShadow = false;
	WeaponMeshComponent->CastShadow = false;
}

void UFRWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<AFRGASCharacterPlayer>(GetOwner());
	if (OwnerCharacter)
	{
		ASC = OwnerCharacter->GetAbilitySystemComponent();

		if (WeaponMeshComponent && OwnerCharacter->GetMesh())
		{
			WeaponMeshComponent->RegisterComponent();
			WeaponMeshComponent->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("hand_rSocket"));
		}
	}
}

void UFRWeaponComponent::EquipWeapon(EWeaponType WeaponType)
{
	if (!ASC || !OwnerCharacter || WeaponType == CurrentWeaponType)
	{
		ClearWeapon();
		return;
	}

	const FWeaponData* WeaponData = WeaponSlots.Find(WeaponType);
	if (!WeaponData)
		return;

	ClearWeapon();

	AttachWeaponMesh(WeaponData->WeaponMesh, WeaponData->AttachSocketName);

	if (WeaponData->AttackAbility)
		GiveAbility(WeaponData->AttackAbility, 1, AttackAbilityHandle);

	if (WeaponData->SpecialAttackAbility)
		GiveAbility(WeaponData->SpecialAttackAbility, 2, SubAttackAbilityHandle);

	CurrentWeaponType = WeaponType;

	// 무기 타입에 따라 애니메이션 레이어 조정
	switch (WeaponType)
	{
	case EWeaponType::Sword:
	case EWeaponType::IronMace:
		OwnerCharacter->AdjustMeleeLayerAnim();
		break;
	case EWeaponType::Bow:
		OwnerCharacter->AdjustBowLayerAnim();
		break;
	case EWeaponType::BronzeBell:
		OwnerCharacter->AdjustBronzeBellLayerAnim();
		break;
	default:
		break;
	}
}


void UFRWeaponComponent::ClearWeapon()
{
	WeaponMeshComponent->SetSkeletalMesh(nullptr);
	WeaponMeshComponent->SetVisibility(false);

	ClearAbility(AttackAbilityHandle);
	ClearAbility(SubAttackAbilityHandle);

	CurrentWeaponType = EWeaponType::None;

	if (OwnerCharacter)
	{
		OwnerCharacter->AdjustUnarmedLayerAnim();
	}
}

void UFRWeaponComponent::AttachWeaponMesh(USkeletalMesh* Mesh, FName SocketName)
{
	if (!WeaponMeshComponent || !Mesh || !OwnerCharacter)
		return;

	WeaponMeshComponent->SetSkeletalMesh(Mesh);
	WeaponMeshComponent->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
	WeaponMeshComponent->SetVisibility(true);
}

void UFRWeaponComponent::GiveAbility(TSubclassOf<UGameplayAbility> AbilityClass, int32 InputID, FGameplayAbilitySpecHandle& OutHandle)
{
	if (!ASC || !AbilityClass)
		return;

	FGameplayAbilitySpec Spec(AbilityClass, 1, InputID);
	OutHandle = ASC->GiveAbility(Spec);
}

void UFRWeaponComponent::ClearAbility(FGameplayAbilitySpecHandle& Handle)
{
	if (ASC && Handle.IsValid())
	{
		ASC->ClearAbility(Handle);
		Handle = FGameplayAbilitySpecHandle();
	}
}
