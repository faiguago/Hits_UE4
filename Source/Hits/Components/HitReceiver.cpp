// Fill out your copyright notice in the Description page of Project Settings.


#include "HitReceiver.h"
#include "../Libraries/HitsFunctionLibrary.h"

// Sets default values for this component's properties
UHitReceiver::UHitReceiver()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHitReceiver::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UHitReceiver::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (int32 i = 0; i < DynMaterials.Num(); i++)
	{
		DynMaterials[i]->SetScalarParameterValue(TEXT("HitRadius"), Radius);
		DynMaterials[i]->SetScalarParameterValue(TEXT("HitPower"), Power);
	}
}

void UHitReceiver::ReceiveHit(const FHitResult& Hit)
{
	if (DynMaterials.Num() == 0)
		return;

	FName ParameterName = *FString::Printf(TEXT("Location_%d"), CurrentIndex + 1);
	FVector HitLocation = UHitsFunctionLibrary::GetHitLocationInRefPose(this, Hit);
	for (int32 i = 0; i < DynMaterials.Num(); i++)
	{
		DynMaterials[i]->SetVectorParameterValue(ParameterName, HitLocation);
	}

	CurrentIndex++;
	CurrentIndex %= 10;
}

void UHitReceiver::Init(const TArray<UMaterialInstanceDynamic*>& InDynMats)
{
	DynMaterials = InDynMats;
}