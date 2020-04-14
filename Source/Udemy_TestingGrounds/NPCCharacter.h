#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "NPCCharacter.generated.h"

UCLASS()
class UDEMY_TESTINGGROUNDS_API ANPCCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* FP_MuzzleLocation;

public:
	ANPCCharacter();

protected:
	virtual void BeginPlay() override;
};
