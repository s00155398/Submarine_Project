// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "SubmarineProjectGameMode.h"
#include "SubmarineProjectPawn.h"

ASubmarineProjectGameMode::ASubmarineProjectGameMode()
{
	// set default pawn class to our flying pawn
	DefaultPawnClass = ASubmarineProjectPawn::StaticClass();
}
