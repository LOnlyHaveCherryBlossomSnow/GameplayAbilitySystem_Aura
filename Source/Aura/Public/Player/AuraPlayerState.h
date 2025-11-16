// XiaoJi

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"


class UAbilitySystemComponent;
class UAttributeSet;
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
		GENERATED_BODY()
	public:
		AAuraPlayerState();
		/**GAS 接口实现**/
		virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
		/**提供A他tributeSet 给Character使用**/
		UAttributeSet* GetAttributeSet() const {return AttributeSet;};
	protected:
		UPROPERTY()
		TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
		UPROPERTY()
		TObjectPtr<UAttributeSet> AttributeSet;
};
