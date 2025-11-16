// XiaoJi


#include "Player/AuraPlayerController.h"
// #include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Iteraction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
	
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}


void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	// ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());
	ThisActor = CursorHit.GetActor();
	/**
	 *  Line trace from currsor, there are several scenarios:
	 *  A. LastActor is null && ThisActor is null
	 *		-Do nothing
	 *	B. LastActor is null && ThisActor is valid
	 *		-Highlight ThisActor
	 *	C. LastActor is valid && ThisActor is null
	 *		-UnHighlingt LastActor
	 *	D. Both Actors are valid, but LastActor != ThisActor
	 *		-UnHighlight LastActor, and Highlight ThisActor
	 *	E. Both Actors are valid, and are the same actor
	 *		-Do nothing
	 */
	if (LastActor == nullptr )
	{
		if (ThisActor != nullptr)
		{
			//Case B
			ThisActor->HighlightActor();
		}
		else
		{
			//Case A - both are null, do nothing
		}
	}
	else//LastActor is  valid
	{
		if (ThisActor == nullptr)
		{
			//Case C
			LastActor->UnHighlightActor();
		}
		else//both actors ara valid
		{
			if (LastActor != ThisActor)
			{
				//Case D
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			else
			{
				//Case E- do nothing
			}
		}
	}
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraConText);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());//访问控制增强
	//check(Subsystem);
	if (Subsystem)
	{
		Subsystem->AddMappingContext(AuraConText,0);//调用映射上下文  玩家就可以检索
		
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;//UI
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);//打开光标
	InputModeData.SetHideCursorDuringCapture(false);//关闭射线检测
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);//启动后移动
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)//移动函数
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);



	if (APawn* ControlledPawn =  GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

