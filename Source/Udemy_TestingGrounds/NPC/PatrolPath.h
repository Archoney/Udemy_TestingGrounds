#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"

#include "PatrolPath.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UDEMY_TESTINGGROUNDS_API UPatrolPath : public UActorComponent
{
	GENERATED_BODY()

public:
	UPatrolPath();

	TArray<AActor*> GetPatrolNodes() const;

protected:
	UPROPERTY(EditInstanceOnly, Category = "Path")
	TArray<AActor*> PatrolNodes;
};
