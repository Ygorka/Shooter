// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IOnTakeHealth.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerC.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAimingSignature, bool, NewIsAiming);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeAmmoSignature, int32, NewAmmo);

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class ARifle;
class USoundBase;
class UAnimMontage;
class UCameraShakeBase;
class UHealthComponent;

UCLASS()
class PROJECT_API APlayerC : public ACharacter, public IIOnTakeHealth
{
	GENERATED_BODY()

public:
	APlayerC();

	bool GetAiming() const;

	UPROPERTY(BlueprintAssignable)
	FOnAimingSignature OnAiming;

	UPROPERTY(BlueprintAssignable)
	FOnChangeAmmoSignature OnChangeAmmo;

	int32 GetAmmo() { return Ammo; }
	int32 SetAmmo(int32 NewAmmo) { Ammo = NewAmmo; return Ammo; }
	int32 GetMaxAmmo() { return MaxAmmo; }

	UFUNCTION(BlueprintCallable)
	UHealthComponent* GetHealthComponent() { return HealthComponent; }


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UCameraComponent* CameraComponent;

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void OnTakeHeal_Implementation(float Amount) override;

	virtual void GetCurrentAndMaxHealth_Implementation(float& CurrentHealth, float& MaxHealth) override;
private:
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	UInputAction* RunAction;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	UInputAction* AimAction;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	UInputAction* ShootAction;

	UPROPERTY(EditDEfaultsOnly, Category = "Speed")
	float RunSpeed;

	UPROPERTY(EditDEfaultsOnly, Category = "Speed")
	float WalkSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ARifle> Weapon;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	TSubclassOf<UCameraShakeBase> CameraShake;

	UPROPERTY()
	ARifle* CurrentWeapon;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName SocketWeaponName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* ShootAnimation;

	UPROPERTY(EditDefaultsOnly)
	float LenghtTrace;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	int32 Ammo = 30;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	int32 MaxAmmo = 60;

	FTimerHandle ShootTimer;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* ShootSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* EmptyAmmoSound;

	UPROPERTY(EditDefaultsOnly)
	UHealthComponent* HealthComponent;

	void Move(const FInputActionValue& InputValue);
	void Look(const FInputActionValue& InputValue);

	void Run(const FInputActionValue& InputValue);
	void StopRun(const FInputActionValue& InputValue);

	void StartAiming(const FInputActionValue& InputValue);
	void StopAiming(const FInputActionValue& InputValue);

	void StartShoot(const FInputActionValue& InputValue);
	void StopShoot(const FInputActionValue& InputValue);

	void SpawnWeapon();

	void Trace();

	void AmmoCount();

	void Shoot();

	void Shake(TSubclassOf<UCameraShakeBase> Camera);

	bool bIsRunning;

	bool bIsAiming;
};
