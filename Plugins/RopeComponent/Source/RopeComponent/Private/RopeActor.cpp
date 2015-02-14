// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "RopeComponentPluginPrivatePCH.h"


ARopeActor::ARopeActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	RopeComponent = ObjectInitializer.CreateDefaultSubobject<URopeComponent>(this, TEXT("RopeComponent0"));
	RootComponent = RopeComponent;
}