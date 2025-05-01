// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "FRCharacterAttributeSet.generated.h"

/*
    어트리뷰트 값을 읽고/쓰기/초기화하고, 프로퍼티 메타데이터 접근까지 한 번에 만들어주는 묶음 매크로
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName)    // UProperty* 반환용 Getter (메타 정보용)  
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)                  // CurrentValue 실제 값 Getter  
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)                  // BaseValue(영구값)값 Setter (확정) 
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)                 // SetBaseValue=CurrentValue 초기값 설정용
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


UCLASS()
class FINALREQUITAL_API UFRCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UFRCharacterAttributeSet();

	// 여기에서 매크로 사용을 위한 연동 설정
	ATTRIBUTE_ACCESSORS(UFRCharacterAttributeSet, AttackRange);
	ATTRIBUTE_ACCESSORS(UFRCharacterAttributeSet, MaxAttackRange);
	ATTRIBUTE_ACCESSORS(UFRCharacterAttributeSet, AttackRadius);
	ATTRIBUTE_ACCESSORS(UFRCharacterAttributeSet, MaxAttackRadius);
	ATTRIBUTE_ACCESSORS(UFRCharacterAttributeSet, AttackRate);
	ATTRIBUTE_ACCESSORS(UFRCharacterAttributeSet, MaxAttackRate);
	ATTRIBUTE_ACCESSORS(UFRCharacterAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UFRCharacterAttributeSet, MaxHealth);

	// PreAttributeChange -> 값이 실제로 적용되기 직전에 호출됨
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	// PostAttributeChange -> 값이 실제로 변경된 직후에 호출됨
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
protected:
	UPROPERTY(BlueprintReadOnly, Category="Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackRange;
	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAttackRange;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackRadius;
	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAttackRadius;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackRate;
	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAttackRate;

	UPROPERTY(BlueprintReadOnly, Category = "Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Health;
	UPROPERTY(BlueprintReadOnly, Category = "Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;
};
