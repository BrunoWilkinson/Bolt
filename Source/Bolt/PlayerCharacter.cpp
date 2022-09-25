// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "TP_WeaponComponent.h"
#include "Weapon.h"
#include "SpellComponent.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"

APlayerCharacter::APlayerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	TurnRateGamepad = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	SpellComponent = CreateDefaultSubobject<USpellComponent>(TEXT("Spell Component"));
}

void APlayerCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (WeaponClass != nullptr && World != nullptr)
	{
		FActorSpawnParameters ActorSpawnParams;
		Weapon = World->SpawnActor<AWeapon>(WeaponClass, GetActorLocation() + 100, GetActorRotation(), ActorSpawnParams);
		if (Weapon != nullptr)
		{
			UTP_WeaponComponent* WeaponComponent = Weapon->GetWeaponComponent();
			if (WeaponComponent != nullptr)
			{
				// Change the type for the argument
				// WeaponComponent->AttachWeapon(this);
			}
		}
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	// Set up gameplay key bindings
	check(InputComponent);

	// Bind jump events
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	InputComponent->BindAction("PrimaryAction", IE_Pressed, this, &APlayerCharacter::OnPrimaryAction);
	InputComponent->BindAction("Spell", IE_Pressed, this, &APlayerCharacter::OnSpellAction);
	InputComponent->BindAction("Reload", IE_Pressed, this, &APlayerCharacter::OnReload);

	// Enable touchscreen input
	EnableTouchscreenMovement(InputComponent);

	// Bind movement events
	InputComponent->BindAxis("Move Forward / Backward", this, &APlayerCharacter::MoveForward);
	InputComponent->BindAxis("Move Right / Left", this, &APlayerCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "Mouse" versions handle devices that provide an absolute delta, such as a mouse.
	// "Gamepad" versions are for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("Turn Right / Left Gamepad", this, &APlayerCharacter::TurnAtRate);
	InputComponent->BindAxis("Look Up / Down Gamepad", this, &APlayerCharacter::LookUpAtRate);
}

bool APlayerCharacter::EnableTouchscreenMovement(UInputComponent* InputComponent)
{
	if (FPlatformMisc::SupportsTouchInput() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &APlayerCharacter::BeginTouch);
		InputComponent->BindTouch(EInputEvent::IE_Released, this, &APlayerCharacter::EndTouch);

		return true;
	}

	return false;
}


void APlayerCharacter::OnPrimaryAction()
{
	OnUseItem.Broadcast();
}

void APlayerCharacter::OnSpellAction()
{
	OnUseSpell.Broadcast();
}

void APlayerCharacter::OnReload()
{
	OnUseReload.Broadcast();
}

void APlayerCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	{
		OnPrimaryAction();
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void APlayerCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	TouchItem.bIsPressed = false;
}

void APlayerCharacter::MoveForward(float Val)
{
	if (Val != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Val);
	}
}

void APlayerCharacter::MoveRight(float Val)
{
	if (Val != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Val);
	}
}

void APlayerCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}
