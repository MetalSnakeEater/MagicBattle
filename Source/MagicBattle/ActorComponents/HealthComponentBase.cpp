// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponentBase.h"

// Sets default values for this component's properties
UHealthComponentBase::UHealthComponentBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	DefaultHealth = 100.f;
	Health = DefaultHealth;
}


// Called when the game starts
void UHealthComponentBase::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();

	if (Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponentBase::TakeDamage);
	}
}


// Called every frame
void UHealthComponentBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponentBase::TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser) 
{
	if (Damage <= 0)
		return;

	Health = FMath::Clamp(Health - Damage, 0.f, DefaultHealth);

	if (Health == 0.f)
		GetOwner()->Destroy();	
}

