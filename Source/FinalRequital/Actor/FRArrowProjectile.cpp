// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/FRArrowProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"

AFRArrowProjectile::AFRArrowProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowMesh"));
	RootComponent = Mesh;

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

void AFRArrowProjectile::InitVelocity(const FVector& Direction, float Speed)
{
	if (ProjectileMovement)
	{
		ProjectileMovement->Velocity = Direction * Speed;
	}
}
