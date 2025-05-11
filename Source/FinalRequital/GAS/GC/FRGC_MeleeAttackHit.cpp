// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GC/FRGC_MeleeAttackHit.h"
#include "Particles/ParticleSystem.h"
#include "kismet/GameplayStatics.h"

UFRGC_MeleeAttackHit::UFRGC_MeleeAttackHit()
{
}

bool UFRGC_MeleeAttackHit::OnExecute_Implementation(AActor* Target, const FGameplayCueParameters& Parameters) const
{
	const FHitResult* HitResult = Parameters.EffectContext.GetHitResult();
	if (HitResult)
	{
		UGameplayStatics::SpawnEmitterAtLocation(Target, ParticleEffect, HitResult->ImpactPoint, FRotator::ZeroRotator, true);
	}

	return Super::OnExecute_Implementation(Target, Parameters);
}
