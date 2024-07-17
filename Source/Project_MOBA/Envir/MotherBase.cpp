// Cu Nhat Hoang


#include "MotherBase.h"

#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Project_MOBA/FunctionLibrary/MyBlueprintFunctionLibrary.h"
#include "Project_MOBA/GameModeBase/MyGameModeBase.h"

AMotherBase::AMotherBase()
{
	PrimaryActorTick.bCanEverTick = false;
	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere component");
	SphereComponent->SetupAttachment(GetRootComponent());
}

void AMotherBase::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority()) UMyBlueprintFunctionLibrary::GetMyGameModeBase(GetWorld())->GetTeamBaseMap().Add(TeamTag, this);
}

void AMotherBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

