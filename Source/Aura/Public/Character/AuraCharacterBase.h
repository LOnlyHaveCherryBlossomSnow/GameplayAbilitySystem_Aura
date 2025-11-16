// XiaoJi

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

// 基础角色类
UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	// 设置默认值
	AAuraCharacterBase();
	// 获取能力系统组件
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// 获取属性集
	UAttributeSet* GetAttributeSet() const {return AttributeSet;};

protected:
	// Called when the game starts or when spawned  // 当游戏开始或对象被生成时调用
	virtual void BeginPlay() override;
	// 武器网格组件
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
	// 技能组件
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;//技能组件
	// 属性组件
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;//属性组件
};
