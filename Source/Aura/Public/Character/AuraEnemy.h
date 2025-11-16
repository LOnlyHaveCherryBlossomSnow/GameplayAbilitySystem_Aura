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
protected:
	// 当游戏开始或对象被生成时调用
	virtual void BeginPlay() override;//初始化
};
