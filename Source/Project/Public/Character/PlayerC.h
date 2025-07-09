// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerC.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAimingSignature, bool, NewIsAiming);

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class PROJECT_API APlayerC : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerC();

	bool GetAiming();

	UPROPERTY(BlueprintAssignable)
	FOnAimingSignature OnAiming;

protected:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly, Category="EnhancedInput")
	UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, Category="EnhancedInput")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, Category="EnhancedInput")
	UInputAction* RunAction;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	UInputAction* AimAction;


private:

	UPROPERTY(EditDEfaultsOnly, Category = "Speed")
	float RunSpeed;

	UPROPERTY(EditDEfaultsOnly, Category = "Speed")
	float WalkSpeed;

	void Move(const FInputActionValue& InputValue);
	void Look(const FInputActionValue& InputValue);

	void Run(const FInputActionValue& InputValue);
	void StopRun(const FInputActionValue& InputValue);

	void StartAiming(const FInputActionValue& InputValue);
	void StopAiming(const FInputActionValue& InputValue);

	bool bIsRunning;

	bool bIsAiming;

	void SpawnWeapon();

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TSubclassOf<AActor> Weapon;

	UPROPERTY()
	AActor* CurrentWeapon;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	FName SocketWeaponName = "WeaponSocket";


};
