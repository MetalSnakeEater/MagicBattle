// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class UCapsuleComponent;
class UCameraComponent;
class UMyCharacterMovementComponent;
class UHealthComponentBase;
class USpringArmComponent;

UCLASS()
class MAGICBATTLE_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Camera, meta=(AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Health, meta=(AllowPrivateAccess = "true"))
	UHealthComponentBase* HealthComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Spell, meta=(AllowPrivateAccess = "true"))
	UCapsuleComponent* SpellThrowing;

public:
	// Sets default values for this character's properties
	ACharacterBase(const class FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float DefaultWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float RunSpeed;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void LookUp(float Val);
	void Turn(float Val);
	void MoveForward(float Val);
	void MoveRight(float Val);
	virtual void StartRunning();
	virtual void StopRunning();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	UMyCharacterMovementComponent* GetMyMovementComponent() const;

};
