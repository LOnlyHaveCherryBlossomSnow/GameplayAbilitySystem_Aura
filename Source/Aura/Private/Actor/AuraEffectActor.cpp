// XiaoJi


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// 设置此 Actor 每帧调用 Tick()。如果不需要，可以关闭以提高性能。
	PrimaryActorTick.bCanEverTick = false;
	// 创建并设置静态网格组件
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);//设置为根
	// 创建并设置球体组件
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());//把sphere 绑定到根
}
// 当发生重叠时调用
void AAuraEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)//范围检测  开始碰撞
{
	//TODO:Change this to apply a Game[lay Effect, For now, using const_cast as a hack!
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))//连接到ASC 联网
	{
		// 获取属性集
	 	const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));
		// 临时修改属性集
		UAuraAttributeSet* MutableAuraAttributeSet = const_cast<UAuraAttributeSet*>(AuraAttributeSet);
		// 修改生命值
		MutableAuraAttributeSet->SetHealth(AuraAttributeSet->GetHealth() + AddHealth);//修改血条
		Destroy();//删除自己
	}
}//碰撞后 添加玩家血量 联网

void AAuraEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)//范围检测  结束碰撞
{
	
}

// Called when the game starts or when spawned 当游戏开始或对象被生成时调用
void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	// 绑定重叠开始事件
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnOverlap);
	// 绑定重叠结束事件
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::EndOverlap);
}

