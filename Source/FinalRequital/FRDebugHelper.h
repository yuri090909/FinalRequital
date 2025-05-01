// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#define D(x) if(GEngine){ GEngine->AddOnScreenDebugMessage(-1, 6.0f, FColor::Cyan, x); }
#define FR_LOG(CategoryName, Verbosity, Format, ...) \
	UE_LOG(CategoryName, Verbosity, Format, ##__VA_ARGS__)

DECLARE_LOG_CATEGORY_EXTERN(FRLOG, Log, All);
/*
*	<Debug용 스크립트>
*	사용할 CPP파일에 FRDebugHelper.h 추가한 후
*	디버그하고 싶은 변수 값을 다음과 같이 사용 가능 :
*
*	해당 스코프에 CurrentHealth, MaxHealth 변수가 접근 가능한 경우,
*	D(FString::Printf(TEXT("Current Health: %f, Max Health: %f"), CurrentHealth, MaxHealth));
*	D(FString::Printf(TEXT("TRIGGER!")));
*   
*   FR_LOG(FRLOG, Error, TEXT("ASC Not Found!"));
*/