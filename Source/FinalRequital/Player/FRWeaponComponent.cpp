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

		// Attach MeshComponent to Character's Mesh
		if (WeaponMeshComponent && OwnerCharacter->GetMesh())
		{
			WeaponMeshComponent->RegisterComponent();
			WeaponMeshComponent->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("hand_rSocket"));
		}
	}
}

void UFRWeaponComponent::EquipWeapon(int32 SlotIndex)
{
	if (!WeaponSlots.IsValidIndex(SlotIndex) || !ASC || !OwnerCharacter)
		return;

	// 이미 장착 중인 무기면 해제 (맨손 전환)
	if (CurrentWeaponIndex == SlotIndex)
	{
		ClearWeapon();
		return;
	}

	// 해제
	ClearWeapon();

	const FWeaponData& WeaponData = WeaponSlots[SlotIndex];

	// 메시 장착
	AttachWeaponMesh(WeaponData.WeaponMesh, WeaponData.AttachSocketName);

	// 어빌리티 장착
	if (WeaponData.AttackAbility)
	{
		GiveAbility(WeaponData.AttackAbility, 1, AttackAbilityHandle); // 왼클릭
	}
	if (WeaponData.SubAttackAbility)
	{
		GiveAbility(WeaponData.SubAttackAbility, 2, SubAttackAbilityHandle); // 오른클릭
	}

	CurrentWeaponIndex = SlotIndex;
}

void UFRWeaponComponent::AttachWeaponMesh(USkeletalMesh* Mesh, FName SocketName)
{
	if (!WeaponMeshComponent || !Mesh || !OwnerCharacter)
		return;

	WeaponMeshComponent->SetSkeletalMesh(Mesh);
	WeaponMeshComponent->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
	WeaponMeshComponent->SetVisibility(true);
}

void UFRWeaponComponent::ClearWeapon()
{
	WeaponMeshComponent->SetSkeletalMesh(nullptr);
	WeaponMeshComponent->SetVisibility(false);

	ClearAbility(AttackAbilityHandle);
	ClearAbility(SubAttackAbilityHandle);

	CurrentWeaponIndex = -1;
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
