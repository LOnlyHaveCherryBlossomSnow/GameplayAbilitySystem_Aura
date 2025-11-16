// XiaoJi


#include "UI/Widgets/AuraUserWidget.h"
// 设置 Widget 控制器

void UAuraUserWidget::SetWidgetController(UObject* InWidgetController)
{
	// 保存传入的 Widget 控制器
	WidgetController = InWidgetController;
	// 调用 WidgetControllerSet 方法，以便在设置控制器后执行其他操作
	WidgetControllerSet();
}
