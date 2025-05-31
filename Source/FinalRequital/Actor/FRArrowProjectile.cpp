// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/FRArrowProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystemGlobals.h"
#include "FRGameplayTag.h"
#include "Components/SphereComponent.h"

AFRArrowProjectile::AFRArrowProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	// 콜리전 컴포넌트 설정 (루트)
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	CollisionComponent->SetNotifyRigidBodyCollision(true);
	CollisionComponent->SetGenerateOverlapEvents(false);
	CollisionComponent->OnComponentHit.AddDynamic(this, &AFRArrowProjectile::OnHit);
	RootComponent = CollisionComponent;

	// 메시 설정
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowMesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); // 메시 충돌 비활성화

	// 이동 컴포넌트
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 0.5f;
	ProjectileMovement->bInitialVelocityInLocalSpace = false;

}

void AFRArrowProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AFRArrowProjectile::InitVelocity(const FVector& Direction, float Speed, float ProjectileGravity)
{
	if (ProjectileMovement)
	{
		ProjectileMovement->Velocity = Direction * Speed;
		ProjectileMovement->ProjectileGravityScale = ProjectileGravity;
	}
}

void AFRArrowProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("화살 OnHit 호출됨!"));

	if (!OtherActor || OtherActor == GetOwner() || !DamageEffectClass)
	{
		Destroy();
		return;
	}

	UAbilitySystemComponent* SourceASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner());
	UAbilitySystemComponent* TargetASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OtherActor);

	if (!SourceASC || !TargetASC)
	{
		Destroy();
		return;
	}

	FGameplayEffectContextHandle EffectContext = SourceASC->MakeEffectContext();
	EffectContext.AddHitResult(Hit);
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, 1.f, EffectContext);
	if (SpecHandle.IsValid())
	{
		// GameplayEffect 적용
		TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);

		FGameplayCueParameters CueParameters;
		CueParameters.EffectContext = SpecHandle.Data->GetEffectContext();
		CueParameters.Location = Hit.ImpactPoint;
		CueParameters.Normal = Hit.ImpactNormal;

		TargetASC->ExecuteGameplayCue(GAMEPLAYCUE_CHARACTER_ARROWHIT, CueParameters);
	}

	Destroy();
}