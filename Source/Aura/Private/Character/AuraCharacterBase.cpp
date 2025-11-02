// XiaoJi


#include "Character/AuraCharacterBase.h"

// Sets default values
AAuraCharacterBase::AAuraCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//设置武器
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");//初始化组件 
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));//添加武器骨骼
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);//关闭碰撞
}

// Called when the game starts or when spawned
void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

