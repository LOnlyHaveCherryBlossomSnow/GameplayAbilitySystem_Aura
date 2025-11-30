// XiaoJi


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// 设置此 Actor 每帧调用 Tick()。如果不需要，可以关闭以提高性能。
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot")));
}



// Called when the game starts or when spawned 当游戏开始或对象被生成时调用
void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	// 步骤 1: 获取目标的 Ability System Component (ASC)
	UAbilitySystemComponent* TargetASC =  UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	// 步骤 2: 安全检查
	if (TargetASC == nullptr) return;

	
	// 步骤 3: 强制检查“状态模板”是否有效
	check(GameplayEffectClass);
	// 步骤 4: 创建“状态上下文”
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	// 步骤 5: 在上下文中记录“状态来源”
	EffectContextHandle.AddSourceObject(this);
	// 步骤 6: 创建“状态规格”（根据模板和上下文生成一个具体的状态实例）
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.0f, EffectContextHandle);
	// 步骤 7: 执行！将状态应用到目标身上
	TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}