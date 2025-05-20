// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FRArrowProjectile.generated.h"

UCLASS()
class FINALREQUITAL_API AFRArrowProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AFRArrowProjectile();

	void InitVelocity(const FVector& Direction, float Speed);

	//class UProjectileMovementComponent* AFRArrowProjectile::GetProjectileMovement() const;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> Mesh;
};
