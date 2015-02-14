// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "RopeActor.generated.h"

/** An actor that renders a simulated Rope */
UCLASS(hidecategories=(Input,Collision,Replication), showcategories=("Input|MouseInput", "Input|TouchInput"))
class ARopeActor : public AActor
{
	GENERATED_UCLASS_BODY()

	/** Rope component that performs simulation and rendering */
	UPROPERTY(Category=Rope, VisibleAnywhere, BlueprintReadOnly)
	class URopeComponent* RopeComponent;
};
