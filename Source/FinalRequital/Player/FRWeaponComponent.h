// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EWeaponType WeaponType = EWeaponType::None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UGameplayAbility> AttackAbility;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UGameplayAbility> SpecialAttackAbility;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class USkeletalMesh> WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName AttachSocketName = "hand_rSocket";
};

UCLASS(ClassGroup = (Custom), BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))
class FINALREQUITAL_API UFRWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFRWeaponComponent();

	void EquipWeapon(EWeaponType WeaponType);
	void ClearWeapon();
	bool IsUnarmed() const;

protected:
	virtual void BeginPlay() override;

	void AttachWeaponMesh(USkeletalMesh* Mesh, FName SocketName);
	void GiveAbility(TSubclassOf<class UGameplayAbility> AbilityClass, int32 InputID, FGameplayAbilitySpecHandle& OutHandle);
	void ClearAbility(FGameplayAbilitySpecHandle& Handle);

protected:
	UPROPERTY(EditAnywhere, Category = Weapon)
	TArray<FWeaponData> WeaponSlots;

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
};