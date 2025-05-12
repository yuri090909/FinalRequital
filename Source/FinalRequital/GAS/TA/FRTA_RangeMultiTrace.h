// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/TA/FRTA_Trace.h"
#include "FRTA_RangeMultiTrace.generated.h"

/**
 * 
 */
UCLASS()
class FINALREQUITAL_API AFRTA_RangeMultiTrace : public AFRTA_Trace
{
	GENERATED_BODY()

protected:
	virtual FGameplayAbilityTargetDataHandle MakeTargetData() const override;

};
