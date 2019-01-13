// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"


#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandleComponent();

	SetupInputComponent();
	
}


void  UGrabber::FindPhysicsHandleComponent() //component of DefaultPawnBP(Editor)
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle != nullptr)
	{
		/*UE_LOG(LogTemp, Warning, TEXT("Handle Found"));*/
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Handle Not Found"));
}


void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("found input component"));
		InputComponent->BindAction("grab", IE_Pressed, this, &UGrabber::Grab); //input action from editor, the action, on which obj, function
		InputComponent->BindAction("grab", IE_Released, this, &UGrabber::Release);
	}
}


void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Pressed"));

	///Try and reach any physics body collision 
	auto HitResult = GetFirstObjectHit();

	auto ComponentToGrab = HitResult.GetComponent();

	auto ActorHit = HitResult.GetActor();

	///if hit, attach that object to player
	if (ActorHit)
	{
		// Attach Physics handle
		PhysicsHandle->GrabComponentAtLocationWithRotation
		(
			ComponentToGrab,
			NAME_None, //no bone to grab
			ComponentToGrab->GetOwner()->GetActorLocation(), //grab at object's origin
			ComponentToGrab->GetOwner()->GetActorRotation()  //apply constraints to rotation of objects
		);
	}


}


void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Released"));

	//Release Physics handle
	PhysicsHandle->ReleaseComponent();
}


FHitResult UGrabber::GetFirstObjectHit()
{
	/*///ray trace in world to debug
	DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor(255, 0, 0), false, 0.f, 0.f, 10.f);*/

	///setup query params
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	FHitResult HitResult;
	
	///Line-Trace(raycast) to distance
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		GetLineReachStart(),
		GetLineReachEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	//detect hit object
	AActor* HitActor = HitResult.GetActor();

	if (HitActor != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line Trace Hit: %s"), *(HitActor->GetName()));
	}
	return HitResult;
}


FVector UGrabber::GetLineReachStart()
{
	///get player's viewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	//log
	//UE_LOG(LogTemp, Warning, TEXT("location: %s, rotation: %s"), *(PlayerViewPointLocation.ToString()), *(PlayerViewPointRotation.ToString()));

	return PlayerViewPointLocation;
}


FVector UGrabber::GetLineReachEnd()
{
	///get player's viewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	//log
	//UE_LOG(LogTemp, Warning, TEXT("location: %s, rotation: %s"), *(PlayerViewPointLocation.ToString()), *(PlayerViewPointRotation.ToString()));

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//log
	//UE_LOG(LogTemp, Warning, TEXT("location: %s, rotation: %s"), *(PlayerViewPointLocation.ToString()), *(PlayerViewPointRotation.ToString()));

	//if the physics component is attached move
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetLineReachEnd()); //attach object at "LineTraceEnd"
	}
	
}