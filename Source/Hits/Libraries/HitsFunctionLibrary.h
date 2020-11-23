// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HitsFunctionLibrary.generated.h"

/**
 *
 */
UCLASS()
class HITS_API UHitsFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Hits", meta = (WorldContext = "WorldContextObject"))
		static FVector GetHitLocationInRefPose(UObject* WorldContextObject, const FHitResult& Hit);

	static FTransform GetWorldSpaceTransform(FReferenceSkeleton RefSkel, int32 BoneIdx);

	static FTransform GetRefPoseBoneTransform(USkeletalMeshComponent* SkelMesh, FName BoneName);

	static FTransform GetBoneTransform(USkeletalMeshComponent* SkelMesh, FName BoneName);
};
