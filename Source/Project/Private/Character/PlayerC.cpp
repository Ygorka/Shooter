// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerC.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
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

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) 
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

	CurrentWeapon = GetWorld()->SpawnActor<AActor>(Weapon, SocketTransform);
	CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, SocketWeaponName);
}







