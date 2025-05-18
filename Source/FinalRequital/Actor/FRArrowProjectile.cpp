// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/FRArrowProjectile.h"

// Sets default values
AFRArrowProjectile::AFRArrowProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFRArrowProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFRArrowProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

