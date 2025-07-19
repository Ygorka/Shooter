// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerC.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Widgets/MainHUD.h"
#include "Weapon/Rifle.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

APlayerC::APlayerC()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeLocation(FVector(0.f, -10.f, 40.f));
	SpringArm->TargetArmLength = 350.f;
	SpringArm->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArm);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void APlayerC::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController) 
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) 
		{
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}

	SpawnWeapon();

}

void APlayerC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerC::Move);

		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerC::Look);

		Input->BindAction(RunAction, ETriggerEvent::Triggered, this, &APlayerC::Run);
		Input->BindAction(RunAction, ETriggerEvent::Completed, this, &APlayerC::StopRun);
		Input->BindAction(RunAction, ETriggerEvent::Canceled, this, &APlayerC::StopRun);

		Input->BindAction(AimAction, ETriggerEvent::Started, this, &APlayerC::StartAiming);
		Input->BindAction(AimAction, ETriggerEvent::Completed, this, &APlayerC::StopAiming);
		Input->BindAction(AimAction, ETriggerEvent::Canceled, this, &APlayerC::StopAiming);

		Input->BindAction(ShootAction, ETriggerEvent::Started, this, &APlayerC::StartShoot);
		Input->BindAction(ShootAction, ETriggerEvent::Completed, this, &APlayerC::StopShoot);
	}
}

void APlayerC::Move(const FInputActionValue& InputValue)
{
	FVector2D InputVector = InputValue.Get<FVector2D>();

	if (IsValid(Controller)) 
	{
		FRotator Rotation = Controller->GetControlRotation();
		FRotator YawRotation(0, Rotation.Yaw, 0);

		FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, InputVector.Y);
		AddMovementInput(RightDirection, InputVector.X);
	}

}
void APlayerC::Look(const FInputActionValue& InputValue)
{
	FVector2D InputVector = InputValue.Get<FVector2D>();

	if (IsValid(Controller)) 
	{
		AddControllerYawInput(InputVector.X);
		AddControllerPitchInput(InputVector.Y);
	}
}

void APlayerC::Run(const FInputActionValue& InputValue)
{
	if (!GetCharacterMovement()->IsMovingOnGround()) return;
	bIsRunning = true;
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void APlayerC::StopRun(const FInputActionValue& InputValue)
{
	bIsRunning = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void APlayerC::SpawnWeapon()
{
	if (!GetWorld()) return;
	if (!Weapon) return;

	FTransform SocketTransform = GetMesh()->GetSocketTransform(SocketWeaponName);

	CurrentWeapon = GetWorld()->SpawnActor<ARifle>(Weapon, SocketTransform);
	CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, SocketWeaponName);
}
bool APlayerC::GetAiming() const
{
	return bIsAiming;
}

void APlayerC::StartAiming(const FInputActionValue& InputValue)
{
	if (bIsAiming) return;
	bIsAiming = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	OnAiming.Broadcast(bIsAiming);
	bUseControllerRotationYaw =  true;
}

void APlayerC::StopAiming(const FInputActionValue& InputValue)
{
	if (!bIsAiming) return;
	bIsAiming = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	OnAiming.Broadcast(bIsAiming);
	bUseControllerRotationYaw = false;
}

void APlayerC::StartShoot(const FInputActionValue& InputValue)
{
	if (bIsAiming) {
		GetWorld()->GetTimerManager().SetTimer(ShootTimer, this, &APlayerC::Shoot, 0.2f, true, 0.0f);
	}
}

void APlayerC::StopShoot(const FInputActionValue& InputValue)
{
	GetWorld()->GetTimerManager().ClearTimer(ShootTimer);
}

void APlayerC::Shoot()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (!AnimInstance) return;

	if (Ammo > 0 && bIsAiming)
	{
		Shake(CameraShake);
		if (ShootSound)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), ShootSound);
		}
		AnimInstance->Montage_Play(ShootAnimation, 1.0f, EMontagePlayReturnType::Duration, 0.0f, false);
		CurrentWeapon->LightShoot();
		Trace();
		AmmoCount();
	}
	else
	{
		AnimInstance->Montage_Stop(0.1f, ShootAnimation);

		if (EmptyAmmoSound)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), EmptyAmmoSound);
		}
		GetWorld()->GetTimerManager().ClearTimer(ShootTimer);
	}
}

void APlayerC::Trace()
{
	if (!GetWorld() || !CurrentWeapon || !CurrentWeapon->GetArrow()) return;
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) return;

	APlayerCameraManager* CameraManager = PlayerController->PlayerCameraManager;
	if (!CameraManager) return;

	UArrowComponent* Arrow = CurrentWeapon->GetArrow();

	FVector StartTrace = Arrow->GetComponentLocation();
	FVector EndTrace = CameraManager->GetCameraLocation() + CameraManager->GetCameraRotation().Vector() * LenghtTrace;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	FHitResult OutHit;
	GetWorld()->LineTraceSingleByChannel(OutHit, StartTrace, EndTrace, ECollisionChannel::ECC_Visibility, Params);
	DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Red, false, 5.0f, 0, 0.5f);
	if (OutHit.bBlockingHit)
	{
		DrawDebugSphere(GetWorld(), OutHit.ImpactPoint, 5.0f, 8, FColor::Red, false, 5.0f, 0);
	}

}

void APlayerC::AmmoCount()
{
	Ammo = FMath::Clamp(Ammo - 1, 0, MaxAmmo);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("Ammo is %d"), Ammo));
}

void APlayerC::Shake(TSubclassOf<UCameraShakeBase> Camera)
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (APlayerCameraManager* CameraManager = PlayerController->PlayerCameraManager)
		{
			CameraManager->StartCameraShake(Camera);
		}
	}
}
