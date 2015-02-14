// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "RopeComponent.generated.h"

/** Struct containing information about a point along the Rope */
struct FRopeParticle
{
	FRopeParticle()
	: bFree(true)
	, Position(0,0,0)
	, OldPosition(0,0,0)
	{}

	/** If this point is free (simulating) or fixed to something */
	bool bFree;
	/** Current position of point */
	FVector Position;
	/** Position of point on previous iteration */
	FVector OldPosition;
};

/** Component that allows you to specify custom triangle mesh geometry */
UCLASS(hidecategories=(Object, Physics, Collision, Activation, "Components|Activation"), editinlinenew, meta=(BlueprintSpawnableComponent), ClassGroup=Rendering)
class URopeComponent : public UMeshComponent
{
	GENERATED_UCLASS_BODY()

public:

	// Begin UActorComponent interface.
	virtual void OnRegister() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void SendRenderDynamicData_Concurrent() override;
	// Begin UActorComponent interface.

	// Begin USceneComponent interface.
	virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;
	// Begin USceneComponent interface.

	// Begin UPrimitiveComponent interface.
	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;
	// End UPrimitiveComponent interface.

	// Begin UMeshComponent interface.
	virtual int32 GetNumMaterials() const override;
	// End UMeshComponent interface.


	/** Actor or Component that the end of the Rope should be attached to */
	UPROPERTY(EditAnywhere, Category="Rope")
	FComponentReference AttachEndTo;

	/** End location of Rope, relative to AttachEndTo if specified, otherwise relative to Rope component. */
	UPROPERTY(EditAnywhere, Category="Rope")
	FVector EndLocation;

	/** Rest length of the Rope */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Rope", meta=(ClampMin = "0.0", UIMin = "0.0", UIMax = "1000.0"))
	float RopeLength;

	/** How many segments the Rope has */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Rope", meta=(ClampMin = "1", UIMin = "1", UIMax = "20"))
	int32 NumSegments;

	/** Controls the simulation substep time for the Rope */
	UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadOnly, Category="Rope", meta=(ClampMin = "0.005", UIMin = "0.005", UIMax = "0.1"))
	float SubstepTime;

	/** The number of solver iterations controls how 'stiff' the Rope is */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Rope", meta=(ClampMin = "1", ClampMax = "8"))
	int32 SolverIterations;


	/** How wide the Rope geometry is */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Rope Rendering", meta=(ClampMin = "0.01", UIMin = "0.01", UIMax = "50.0"))
	float RopeWidth;

	/** Number of sides of the Rope geometry */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Rope Rendering", meta=(ClampMin = "1", ClampMax = "16"))
	int32 NumSides;

	/** How many times to repeat the material along the length of the Rope */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Rope Rendering", meta=(UIMin = "0.1", UIMax = "8"))
	float TileMaterial;

private:

	/** Solve the Rope spring constraints */
	void SolveConstraints();
	/** Integrate Rope point positions */
	void VerletIntegrate(float SubstepTime, const FVector& Gravity);
	/** Perform a simulation substep */
	void PerformSubstep(float SubstepTime, const FVector& Gravity);
	/** Get start and end position for the Rope */
	void GetEndPositions(FVector& OutStartPosition, FVector& OutEndPosition);
	/** Amount of time 'left over' from last tick */
	float TimeRemainder;
	/** Array of Rope particles */
	TArray<FRopeParticle>	Particles;


	friend class FRopeSceneProxy;
};


