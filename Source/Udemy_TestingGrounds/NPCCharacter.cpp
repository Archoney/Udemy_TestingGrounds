#include "NPCCharacter.h"

#include "Components/SkeletalMeshComponent.h"

// Sets default values
ANPCCharacter::ANPCCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));
}

void ANPCCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Attach gun mesh component to Skeleton, doing it here because the skeleton is not
	// yet created in the constructor
	FP_Gun->AttachToComponent(GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
		TEXT("GripPoint"));
}
