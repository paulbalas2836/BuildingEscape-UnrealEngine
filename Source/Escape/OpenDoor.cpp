// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Components/AudioComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	InitialZLocation = GetOwner()->GetActorLocation().Z;
	CurrentZLocation = InitialZLocation;
	TargetZLocation += InitialZLocation;

	isPressurePlate();
	FindAudioComponent();
	// ...
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TotalMass() > RequiredMass)
	{
		OpenDoor(DeltaTime);
		DoorLastOpen = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if (GetWorld()->GetTimeSeconds() - DoorLastOpen >= DoorCloseDelay)
		{
			CloseDoor(DeltaTime);
		}
	}
	// ...
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	CurrentZLocation = FMath::Lerp(CurrentZLocation, TargetZLocation, DeltaTime * OpenDoorTime);
	FVector DoorLocation = GetOwner()->GetActorLocation();
	DoorLocation.Z = CurrentZLocation;
	GetOwner()->SetActorLocation(DoorLocation);

	OpenDoorSound();
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	CurrentZLocation = FMath::Lerp(CurrentZLocation, InitialZLocation, DeltaTime * CloseDoorTime);
	FVector DoorLocation = GetOwner()->GetActorLocation();
	DoorLocation.Z = CurrentZLocation;
	GetOwner()->SetActorLocation(DoorLocation);

	CloseDoorSound();
}

void UOpenDoor::isPressurePlate()
{
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s There is no pressureplate!!"), *GetOwner()->GetName());
	}
}

float UOpenDoor::TotalMass() const
{
	float TotalMass = 0.f;
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	for (AActor* TempVar : OverlappingActors)
	{
		TotalMass += TempVar->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}

void UOpenDoor::FindAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();

	if (!AudioComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("%s Missing audio component!"), *GetOwner()->GetName());
	}
}

void UOpenDoor::OpenDoorSound()
{
	CheckSoundClose = false;
	if (!AudioComponent) { return; }
	if (!CheckSoundOpen)
	{
		AudioComponent->Play();
		CheckSoundOpen = true;
	}
}

void UOpenDoor::CloseDoorSound()
{
	CheckSoundOpen = false;
	if (!AudioComponent) { return; }
	if (!CheckSoundClose)
	{
		AudioComponent->Play();
		CheckSoundClose = true;
	}
}