﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FRArrowProjectile.generated.h"

class USphereComponent;

UCLASS()
class FINALREQUITAL_API AFRArrowProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AFRArrowProjectile();

	void InitVelocity(const FVector& Direction, float Speed);

	//class UProjectileMovementComponent* AFRArrowProjectile::GetProjectileMovement() const;
public:
	USphereComponent* GetCollisionComponent() const { return CollisionComponent; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> Mesh;

	// 데미지 전달용 GE 클래스
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	TSubclassOf<class UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Collision")
	TObjectPtr<class USphereComponent> CollisionComponent;
	// 피격 처리 함수
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
