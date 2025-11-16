// XiaoJi

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"
// #include "InputActionValue.H"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();

	virtual void PlayerTick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> AuraConText;//设置映射上下文
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& InputActionValue);

	void CursorTrace();
	//TObjectPtr<IEnemyInterface> LastActor;
	//TObjectPtr<IEnemyInterface> ThisActor;
	
	//IEnemyInterface* LastActor;
	//IEnemyInterface* ThisActor;
	UPROPERTY()
	TScriptInterface<IEnemyInterface> LastActor;

	UPROPERTY()
	TScriptInterface<IEnemyInterface> ThisActor;


};
