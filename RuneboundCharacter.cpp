// Copyright Epic Games, Inc. All Rights Reserved.
// Modified by: Alexandra Mueller

#include "RuneboundCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "Interactable.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ARuneboundCharacter

/**
 * @brief Constructor
 * @details Constructor for the Runebound character
 */
ARuneboundCharacter::ARuneboundCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

/**
 * @brief Begin play
 * @details Begin play by adding the input mapping context to the local player subsystem
 */
void ARuneboundCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

/**
 * @brief Set up the player input component
 * @details Set up the player input component by binding the input actions to the appropriate functions
 * 
 * @param PlayerInputComponent The player input component to set up
 */
void ARuneboundCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARuneboundCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARuneboundCharacter::Look);

		// Interacting
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ARuneboundCharacter::Interact);

		// Zooming
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ARuneboundCharacter::Zoom);

		// Pausing
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &ARuneboundCharacter::Pause);

		// Reset Camera
		EnhancedInputComponent->BindAction(ResetCameraAction, ETriggerEvent::Triggered, this, &ARuneboundCharacter::ResetCamera);

		// Running
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Triggered, this, &ARuneboundCharacter::Run);

	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

/**
 * @brief Move the character
 * @details Move the character by adding movement input based on the input value
 * 
 * @param Value The input value from the input action
 */
void ARuneboundCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

/**
 * @brief Look around with the camera
 * @details Look around with the camera by adding yaw and pitch input to the controller based on the input value
 * 
 * @param Value The input value from the input action
 */
void ARuneboundCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// Add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

/**
 * @brief Interact with an interactable object
 * @details Interact with an interactable object by calling the Interact function on the first overlapping actor that is an Interactable
 * 
 * @param Value The input value from the input action (not used)
 */
void ARuneboundCharacter::Interact(const FInputActionValue& Value)
{
	// Get all overlapping actors and store them in an array
	TArray<AActor*> OverlappingActors;
    GetOverlappingActors(OverlappingActors, AInteractable::StaticClass());

	// Loop through all overlapping actors
    for (AActor* OverlappingActor : OverlappingActors)
    {
        // Call the Interact function on the overlapping actor if it is an Interactable
        AInteractable* InteractableActor = Cast<AInteractable>(OverlappingActor);
        if (InteractableActor)
        {
            InteractableActor->Interact();
			UE_LOG(LogTemplateCharacter, Warning, TEXT("Interacted with %s"), *InteractableActor->GetName());	// Log the interaction for debugging
			break;	// Only interact with the first object found (remove this line to interact with all overlapping objects)
        }
    }
}

/**
 * @brief Zoom in and out with the camera
 * @details Zoom in and out with the camera by changing the length of the camera boom based on the input value
 * 
 * @param Value The input value from the input action
 */
void ARuneboundCharacter::Zoom(const FInputActionValue& Value)
{
	float ZoomSpeed = 20.0f;								// Set the speed of the zoom
	float ZoomValue = Value.Get<float>() * ZoomSpeed;		// Multiply the input value by the zoom speed

	if (ZoomValue > 0)										// Zoom in if the value is positive
	{
		if (CameraBoom->TargetArmLength + ZoomValue <= 500)	// Limit the zoom in distance
		{
			CameraBoom->TargetArmLength += ZoomValue;		// Zoom in
		}
		
	}
	else 													// Zoom out if the value is negative
	{
		if (CameraBoom->TargetArmLength + ZoomValue >= 200)	// Limit the zoom out distance
		{
			CameraBoom->TargetArmLength += ZoomValue;		// Zoom out
		}
	}
}

/**
 * @brief Pause the game
 * @details Pause the game by toggling the game pause state
 * 
 * @param Value The input value from the input action (not used)
 */
void ARuneboundCharacter::Pause(const FInputActionValue& Value)
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	if (UGameplayStatics::IsGamePaused(GetWorld())) 		// If the game is paused, unpause it
	{
		if (PC) PC->bShowMouseCursor = false;				// Hide the mouse cursor
		UGameplayStatics::SetGamePaused(GetWorld(), false);	// Unpause the game
		PC->SetInputMode(FInputModeGameOnly());				// Set the input mode to game only
	}
	else 													// If the game is not paused, pause it
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);	// Pause the game
		if (PC) PC->bShowMouseCursor = true;				// Show the mouse cursor
		PC->SetInputMode(FInputModeGameAndUI());			// Set the input mode to game and UI (game included to be able to still unpause with the keyboard or controller)
	}

	if (OnPause.IsBound()) OnPause.Broadcast();				// Broadcast the pause event delegate if it is bound
}

/**
 * @brief Reset the camera
 * @details Reset the camera by setting the target arm length to the default length, resetting the controller rotation and adding the character's rotation
 * 
 * @param Value The input value from the input action (not used)
 */
void ARuneboundCharacter::ResetCamera(const FInputActionValue& Value)
{
	CameraBoom->TargetArmLength = 400.0f;											// Set the target arm length to the default length
	Controller->SetControlRotation(FRotator(0.0f, GetActorRotation().Yaw, 0.0f));	// Reset the controller rotation and add the character's rotation
}

/**
 * @brief Run Toggle
 * @details Toggle the character's running state
 * 
 * @param Value The input value from the input action (not used)
 */
void ARuneboundCharacter::Run(const FInputActionValue& Value)
{
	// If the character is running, set the max walk speed to 300, otherwise set it to 500
	GetCharacterMovement()->MaxWalkSpeed = (GetCharacterMovement()->MaxWalkSpeed == 500.f) ? 300.f : 500.f;
}