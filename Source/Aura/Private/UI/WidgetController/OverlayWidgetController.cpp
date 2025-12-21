// XiaoJi


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
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
		AuraAttributeSet->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);
	// 绑定最大生命值变化委托
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);
	// 绑定蓝条变化委托
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	AuraAttributeSet->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}
	);
	// 绑定最大蓝条值变化委托
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	AuraAttributeSet->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		}
	);
	//获取tag 变化
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			for (const FGameplayTag& Tag:AssetTags)//循环所有的标签
			{
				const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());//存储标签
				GEngine->AddOnScreenDebugMessage(-1,8.f, FColor::Blue, Msg);//打印标签
				
				//"A.1".MatchesTag("A") will return True, "A".MatchesTag("A.1") will return False 

				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if (Tag.MatchesTag(MessageTag))
				{
					//TODO: Broadcast the tag to the widget controll
					const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					if (Row!=nullptr)
					{
						MessageWidgetRowDelegate.Broadcast(*Row);		
					}
				}
			}
		}
	);
}


