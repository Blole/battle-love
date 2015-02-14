// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "RopeComponentPluginPrivatePCH.h"




class FRopeComponentPlugin : public IModuleInterface
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE( FRopeComponentPlugin, RopeComponent )



void FRopeComponentPlugin::StartupModule()
{
	
}


void FRopeComponentPlugin::ShutdownModule()
{
	
}



