// XiaoJi


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"
// 广播初始值
void UOverlayWidgetController::BroadcastInitialValues()
{// 将属性集转换为 AuraAttributeSet
	const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
	// 广播当前生命值
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	// 广播最大生命值
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());

	//广播当前法力值
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	//广播最大法力值
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());	

	
}
// 绑定回调到依赖项
void UOverlayWidgetController::BindCallbackToDependencies()
{ // 将属性集转换为 AuraAttributeSet
	const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
	// 绑定生命值变化委托
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
	// 绑定最大生命值变化委托
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);

	// 绑定蓝条变化委托
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);
	// 绑定最大蓝条值变化委托
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
}
// 生命值变化时调用
void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{ // 广播新的生命值
	OnHealthChanged.Broadcast(Data.NewValue);
}
// 最大生命值变化时调用
void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
