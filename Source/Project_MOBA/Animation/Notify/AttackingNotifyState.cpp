// Cu Nhat Hoang


#include "AttackingNotifyState.h"

#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Project_MOBA/Project_MOBA.h"
#include "Project_MOBA/Character/BaseCharacter.h"

void UAttackingNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                        float TotalDuration)
{
	ABaseCharacter* Character = Cast<ABaseCharacter>(MeshComp->GetOwner());
	if (Character && Character->HasAuthority())
	{
		UKismetSystemLibrary::PrintString(Character,TEXT("NotifyBegin"));
		FCollisionResponseContainer CollisionResponseContainer;
		CollisionResponseContainer.SetResponse(ECC_Character, ECR_Overlap);
		CollisionResponseContainer.SetResponse(ECC_EnvirCombatActor, ECR_Overlap);
		Character->GetMeleCollisionBoundary()->SetCollisionResponseToChannels(CollisionResponseContainer);
		
	}	
}

void UAttackingNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	ABaseCharacter* Character = Cast<ABaseCharacter>(MeshComp->GetOwner());
	if (Character && Character->HasAuthority())
	{
		Character->GetMeleCollisionBoundary()->SetCollisionResponseToAllChannels(ECR_Ignore);
	}	
}
