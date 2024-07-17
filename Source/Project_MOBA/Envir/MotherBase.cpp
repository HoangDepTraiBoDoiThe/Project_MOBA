// Cu Nhat Hoang


#include "MotherBase.h"

#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Project_MOBA/Component/EnvironmentComponent.h"
#include "Project_MOBA/FunctionLibrary/MyBlueprintFunctionLibrary.h"
#include "Project_MOBA/GameModeBase/MyGameModeBase.h"
#include "Project_MOBA/GAS/ASC/MyAbilitySystemComponent.h"
#include "Project_MOBA/GAS/AttributeSet/BaseAttributeSet.h"

AMotherBase::AMotherBase()
{
	PrimaryActorTick.bCanEverTick = false;
	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere component");
	SetRootComponent(SphereComponent);
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("Widget Component");
	WidgetComponent->SetupAttachment(SphereComponent);
	
	MyAbilitySystemComponent = CreateDefaultSubobject<UMyAbilitySystemComponent>("ASC");
	BaseAttributeSet = CreateDefaultSubobject<UBaseAttributeSet>("Attribute set");
	EnvironmentComponent = CreateDefaultSubobject<UEnvironmentComponent>("Environment component");
}

void AMotherBase::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		UMyBlueprintFunctionLibrary::GetMyGameModeBase(GetWorld())->GetTeamBaseMap().Add(TeamTag, this);
		for (const auto& EffectClass : DefaultAttributeValues)
		{
			UMyBlueprintFunctionLibrary::MakeMyGameplayEffectSpecHandle(MyAbilitySystemComponent, EffectClass, 1);
		}
	}
	
	EnvironmentComponent->SetWidgetControllerToWidget();
}

void AMotherBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UMyAbilitySystemComponent* AMotherBase::GetASC()
{
	return MyAbilitySystemComponent;
}

UBaseAttributeSet* AMotherBase::GetAS()
{
	return BaseAttributeSet;
}

UWidgetComponent* AMotherBase::GetWidgetComponent()
{
	return WidgetComponent;
}

void AMotherBase::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer.AddTag(ActorTag);
	TagContainer.AddTag(TeamTag);
}

UPrimitiveComponent* AMotherBase::GetAttackableActor_Mesh()
{
	return SphereComponent;
}

void AMotherBase::Die()
{
	if (!HasAuthority()) return;
	UMyBlueprintFunctionLibrary::GetMyGameModeBase(GetWorld())->EndGame();
}

