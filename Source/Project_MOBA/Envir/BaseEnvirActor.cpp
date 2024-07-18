// Cu Nhat Hoang


#include "BaseEnvirActor.h"

#include "Project_MOBA/GAS/ASC/MyAbilitySystemComponent.h"
#include "Project_MOBA/GAS/AttributeSet/BaseAttributeSet.h"

ABaseEnvirActor::ABaseEnvirActor()
{
	MyAbilitySystemComponent = CreateDefaultSubobject<UMyAbilitySystemComponent>("Ability system component");
	BaseAttributeSet = CreateDefaultSubobject<UBaseAttributeSet>("Base Attribute Set");
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Static mesh");
	StaticMeshComponent->SetupAttachment(GetRootComponent());
}

UPrimitiveComponent* ABaseEnvirActor::GetAttackableActor_Mesh()
{
	return StaticMeshComponent;
}

void ABaseEnvirActor::BeginPlay()
{
	Super::BeginPlay();

}

void ABaseEnvirActor::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	MyAbilitySystemComponent->ActorASCInitialize(this, this);
}
