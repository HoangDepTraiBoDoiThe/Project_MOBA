// Cu Nhat Hoang


#include "BaseEnvirActor.h"

#include "Project_MOBA/GAS/ASC/MyAbilitySystemComponent.h"
#include "Project_MOBA/GAS/AttributeSet/BaseAttributeSet.h"

ABaseEnvirActor::ABaseEnvirActor()
{
	MyAbilitySystemComponent = CreateDefaultSubobject<UMyAbilitySystemComponent>("Ability system component");
	BaseAttributeSet = CreateDefaultSubobject<UBaseAttributeSet>("Base Attriubute Set");
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
