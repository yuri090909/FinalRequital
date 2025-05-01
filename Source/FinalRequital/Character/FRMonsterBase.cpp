// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FRMonsterBase.h"
#include "GAS/Attribute/FRCharacterAttributeSet.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "Physics/FRCollision.h"

AFRMonsterBase::AFRMonsterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// Capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName(CPROFILE_FRCAPSULE);

	// Movement
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	//ASC
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	AttributeSet = CreateDefaultSubobject<UFRCharacterAttributeSet>(TEXT("AttributeSet"));
}

class UAbilitySystemComponent* AFRMonsterBase::GetAbilitySystemComponent() const
{
	return ASC;
}

void AFRMonsterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	ASC->InitAbilityActorInfo(this, this);
}

void AFRMonsterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

