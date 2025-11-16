// XiaoJi

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * @class UAuraUserWidget
 * @brief Extends UUserWidget to provide additional functionality for Aura project, specifically for handling widget controllers.
 *
 * This class is designed to be used within the Aura project to manage and interact with widget controllers. It provides
 * a method to set the widget controller, which is a key component for updating and controlling the user interface.
 * Additionally, it includes a BlueprintImplementableEvent to notify when the widget controller has been set, allowing
 * for custom logic to be executed in derived classes or blueprints.
 *
 * @note Ensure that the Overlay Widget Class and Overlay Widget Controller Class are properly initialized in BP_AuraHUD.
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);
	
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
	
};
