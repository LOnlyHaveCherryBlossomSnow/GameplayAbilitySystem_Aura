// XiaoJi

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Iteraction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 敌人角色类
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
public:
	// 构造函数
	AAuraEnemy();
	/**Enemy Interface**/
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	/**end enemy interface**/

	/*Combat Interface*/
	virtual int32 GetPlayerLevel() override;
	/*End Combat Interface*/
protected:
	// 当游戏开始或对象被生成时调用
	virtual void BeginPlay() override;//初始化
	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere,  BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;
};
