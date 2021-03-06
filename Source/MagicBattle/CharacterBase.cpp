// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "MagicBattle/ActorComponents/HealthComponentBase.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyCharacterMovementComponent.h"

// Sets default values
ACharacterBase::ACharacterBase(const class FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer.SetDefaultSubobjectClass<UMyCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = true;

	SpellThrowing = CreateDefaultSubobject<UCapsuleComponent>(TEXT("SpellThrowing"));
	SpellThrowing->SetupAttachment(RootComponent);

	HealthComponent = CreateDefaultSubobject<UHealthComponentBase>(TEXT("Health Component"));
	DefaultWalkSpeed = 200.f;
	RunSpeed = 350.f;
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACharacterBase::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ACharacterBase::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &ACharacterBase::AddControllerYawInput);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ACharacterBase::StartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ACharacterBase::StopRunning);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacterBase::Jump);

}

void ACharacterBase::LookUp(float Val) 
{
	AddControllerPitchInput(Val);
	FVector Location = FVector(5 * Val, 0, 5 * -Val);
	FRotator Rotator = FRotator(1 * Val, 0, 0);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *(SpellThrowing->GetRelativeLocation().ToString()));
	if (SpellThrowing->GetRelativeLocation().Z <= 100 && SpellThrowing->GetRelativeLocation().Z >= - 100)
		SpellThrowing->AddRelativeLocation(Location);
	SpellThrowing->AddLocalRotation(FQuat(Rotator));
}

void ACharacterBase::Turn(float Val) 
{
	AddControllerYawInput(Val);
}

UMyCharacterMovementComponent* ACharacterBase::GetMyMovementComponent() const
{
	return static_cast<UMyCharacterMovementComponent*>(GetCharacterMovement());
}

void ACharacterBase::MoveForward(float Val) 
{
	AddMovementInput(GetActorForwardVector(), Val);
}

void ACharacterBase::MoveRight(float Val) 
{
	AddMovementInput(GetActorRightVector(), Val);
}

void ACharacterBase::StartRunning() 
{
	//GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	GetMyMovementComponent()->SetSprinting(true);
}

void ACharacterBase::StopRunning() 
{
	//GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
	GetMyMovementComponent()->SetSprinting(false);
}
