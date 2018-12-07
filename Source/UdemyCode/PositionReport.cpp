// Fill out your copyright notice in the Description page of Project Settings.

#include "PositionReport.h"


// Sets default values for this component's properties(Constructor)
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();

	//owner = owner of the component.
	FString ObjectName = GetOwner()->GetName();  //name = name of the owner as shown in world outliner.

	FString ObjectLoc = GetOwner()->GetTransform().GetLocation().ToString(); //or GetOwner()->GetActorLocation()

	//when using string in LOG, use %s which represent the string, also the string var must have *.
	UE_LOG(LogTemp, Warning, TEXT("object %s at %s"), *ObjectName, *ObjectLoc);
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

