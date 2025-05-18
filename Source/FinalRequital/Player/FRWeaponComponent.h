// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Components/ActorComponent.h"
#include "FRWeaponComponent.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	None			UMETA(DisplayName = "Unarmed"),
	Sword		    UMETA(DisplayName = "Sword"),
	IronMace	    UMETA(DisplayName = "IronMace"),
	Bow             UMETA(DisplayName = "Bow"),
	BronzeBell      UMETA(DisplayName = "BronzeBell")
};

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	EWeaponType WeaponType;

	UPROPERTY(EditAnywhere)
	USkeletalMesh* WeaponMesh;

	//hand_rSocket
	UPROPERTY(EditAnywhere)
	FName AttachSocketName;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayAbility> AttackAbility;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayAbility> SpecialAttackAbility;
};

UCLASS(ClassGroup = (Custom), BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))
class FINALREQUITAL_API UFRWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFRWeaponComponent();

	void EquipWeapon(EWeaponType WeaponType);
	void ClearWeapon();

protected:
	virtual void BeginPlay() override;

	void AttachWeaponMesh(USkeletalMesh* Mesh, FName SocketName);
	void GiveAbility(TSubclassOf<class UGameplayAbility> AbilityClass, int32 InputID, FGameplayAbilitySpecHandle& OutHandle);
	void ClearAbility(FGameplayAbilitySpecHandle& Handle);

protected:
	UPROPERTY(EditAnywhere, Category = Weapon)
	TMap<EWeaponType, FWeaponData> WeaponSlots;

	UPROPERTY()
	EWeaponType CurrentWeaponType = EWeaponType::None;

	UPROPERTY()
	FGameplayAbilitySpecHandle AttackAbilityHandle;

	UPROPERTY()
	FGameplayAbilitySpecHandle SubAttackAbilityHandle;

	UPROPERTY()
	TObjectPtr<class AFRGASCharacterPlayer> OwnerCharacter;

	UPROPERTY()
	TObjectPtr<class USkeletalMeshComponent> WeaponMeshComponent;

	UPROPERTY()
	TObjectPtr<class UAbilitySystemComponent> ASC;

	UPROPERTY()
	TObjectPtr<class UFRHUDWidget> HUD;

};