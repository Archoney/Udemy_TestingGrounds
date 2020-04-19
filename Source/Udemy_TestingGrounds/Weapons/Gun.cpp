#include "Gun.h"

#include "Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

AGun::AGun()
{
	PrimaryActorTick.bCanEverTick = false;

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);
}

void AGun::BeginPlay()
{
	Super::BeginPlay();
}

void AGun::OnFire()
{
	UWorld* const World = GetWorld();
	if (World == NULL || World->TimeSeconds - FireTime < ReloadTime)
		return;

	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		const FRotator SpawnRotation = FP_MuzzleLocation->GetComponentRotation();
		// MuzzleOffset is in camera space, so transform it to world space before
		// offsetting from the character location to find the final muzzle
		// position
		const FVector SpawnLocation =
			((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation()
											: GetActorLocation()) +
			SpawnRotation.RotateVector(GunOffset);

		// Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		// spawn the projectile at the muzzle
		World->SpawnActor<AProjectile>(
			ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);

		FireTime = World->TimeSeconds;
	}

	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation != NULL)
	{
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}
