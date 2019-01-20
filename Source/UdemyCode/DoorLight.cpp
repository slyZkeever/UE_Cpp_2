// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorLight.h"


// Sets default values for this component's properties
UDoorLight::UDoorLight()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void UDoorLight::BeginPlay()
{
	Super::BeginPlay();

	if (LightComponent != nullptr)
	{
		//LightComponent->SetLightColor(FColor(255, 0, 0, 0));

		UE_LOG(LogTemp, Warning, TEXT("light found"));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("light owner not found"));
}


// Called every frame
void UDoorLight::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	AllowPassing();
}

void UDoorLight::AllowPassing()
{
	//UOpenDoor open;

	/*if (open.GetTotalMassOfActorsOnPlate() > 35.f)
	{
		if (LightOwner != nullptr)
		{
			LightOwner->LightColor = FColor(255, 0, 0);
		}
	}*/
}