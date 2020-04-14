#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "CoreMinimal.h"

#include "NextWaypointTask.generated.h"

UCLASS()
class UDEMY_TESTINGGROUNDS_API UNextWaypointTask : public UBTTaskNode
{
	GENERATED_BODY()

	EBTNodeResult::Type ExecuteTask(
		UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Keys")
	FBlackboardKeySelector WaypointIndexKey;

	UPROPERTY(EditAnywhere, Category = "Keys")
	FBlackboardKeySelector WaypointKey;
};
