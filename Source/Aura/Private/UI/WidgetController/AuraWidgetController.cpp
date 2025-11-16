// XiaoJi


#include "UI/WidgetController/AuraWidgetController.h"
// 设置 Widget 控制器参数
void UAuraWidgetController::SetWidgetControllerParams(const FWidgetControllerParams WCParams)
{
	// 保存玩家控制器
	PlayerController = WCParams.PlayerController;
	// 保存玩家状态
	PlayerState = WCParams.PlayerState;
	// 保存能力系统组件
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	// 保存属性集
	AttributeSet = WCParams.AttributeSet;
}
// 广播初始值
void UAuraWidgetController::BroadcastInitialValues()
{
	
}
// 绑定回调到依赖项
void UAuraWidgetController::BindCallbackToDependencies()
{
	
}
