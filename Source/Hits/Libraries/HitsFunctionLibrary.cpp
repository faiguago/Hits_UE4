// Fill out your copyright notice in the Description page of Project Settings.


#include "HitsFunctionLibrary.h"

FVector UHitsFunctionLibrary::GetHitLocationInRefPose(UObject* WorldContextObject, const FHitResult& Hit)
{
	USkeletalMeshComponent* Mesh = Cast<USkeletalMeshComponent>(Hit.GetComponent());
	if (Mesh)
	{
		FVector RelativeImpactPointPos;
		FRotator RelativeImpactPointRot;
		Mesh->TransformToBoneSpace(Hit.BoneName, Hit.ImpactPoint, FRotator::ZeroRotator, RelativeImpactPointPos, RelativeImpactPointRot);

		FTransform BoneTransform = GetRefPoseBoneTransform(Mesh, Hit.BoneName);
		FVector ImpactLocation = BoneTransform.TransformPosition(RelativeImpactPointPos);

		return ImpactLocation;
	}
	else
	{
		return FVector::DownVector * -100.0f;
	}
}

FTransform UHitsFunctionLibrary::GetWorldSpaceTransform(FReferenceSkeleton RefSkel, int32 BoneIdx)
{
	FTransform BoneTransform;

	if (BoneIdx > 0)
	{
		BoneTransform = RefSkel.GetRefBonePose()[BoneIdx];

		FMeshBoneInfo BoneInfo = RefSkel.GetRefBoneInfo()[BoneIdx];
		if (BoneInfo.ParentIndex != 0)
		{
			BoneTransform *= GetWorldSpaceTransform(RefSkel, BoneInfo.ParentIndex);
		}
	}

	return BoneTransform;
}

FTransform UHitsFunctionLibrary::GetRefPoseBoneTransform(USkeletalMeshComponent* SkelMesh, FName BoneName)
{
	FTransform BoneTransform;

	if (SkelMesh && !BoneName.IsNone())
	{
		SkelMesh->ClearRefPoseOverride();
		FReferenceSkeleton RefSkel;
		RefSkel = SkelMesh->SkeletalMesh->RefSkeleton;

		BoneTransform = GetWorldSpaceTransform(RefSkel, RefSkel.FindBoneIndex(BoneName));
	}

	return BoneTransform;
}

FTransform UHitsFunctionLibrary::GetBoneTransform(USkeletalMeshComponent* SkelMesh, FName BoneName)
{
	FTransform BoneTransform;

	if (SkelMesh && !BoneName.IsNone())
	{
		FReferenceSkeleton RefSkel;
		RefSkel = SkelMesh->SkeletalMesh->RefSkeleton;
		BoneTransform = SkelMesh->GetBoneTransform(RefSkel.FindBoneIndex(BoneName));
	}

	return BoneTransform;
}