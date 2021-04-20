// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h" 
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	void isPressurePlate();
	float TotalMass() const;
	void OpenDoorSound();
	void CloseDoorSound();
	void FindAudioComponent();


private:
	float CurrentZLocation;
	float InitialZLocation;
	float DoorLastOpen = 0.f;
	bool CheckSoundClose = true;
	bool CheckSoundOpen = false;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
		float RequiredMass = 30.f;
	UPROPERTY(EditAnywhere)
		float OpenDoorTime = 0.5f;
	UPROPERTY(EditAnywhere)
		float TargetZLocation=248.f ;
	UPROPERTY(EditAnywhere)
		float CloseDoorTime = 0.5f;
	UPROPERTY(EditAnywhere);
	float DoorCloseDelay = 2.f;
	UPROPERTY();
	UAudioComponent* AudioComponent = nullptr;
	
};
