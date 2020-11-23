// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HitReceiver.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HITS_API UHitReceiver : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHitReceiver();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	UPROPERTY()
		TArray<UMaterialInstanceDynamic*> DynMaterials;

	UPROPERTY(EditAnywhere)
		float Radius = 10.0f;

	UPROPERTY(EditAnywhere)
		float Power = 1.0f;

	UFUNCTION(BlueprintCallable)
		void  ReceiveHit(const FHitResult& Hit);

	UFUNCTION(BlueprintCallable)
		void Init(const TArray<UMaterialInstanceDynamic*>& InDynMats);

private:

	int32 CurrentIndex;

};
