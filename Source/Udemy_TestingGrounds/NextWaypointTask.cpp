#include "NextWaypointTask.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PatrolPath.h"

EBTNodeResult::Type UNextWaypointTask::ExecuteTask(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
		return EBTNodeResult::Failed;

	auto PatrolPath =
		OwnerComp.GetAIOwner()->GetPawn()->FindComponentByClass<UPatrolPath>();
	if (!PatrolPath)
		return EBTNodeResult::Failed;

	auto WaypointIndex = BlackboardComp->GetValueAsInt(WaypointIndexKey.SelectedKeyName);

	auto PatrolNodes = PatrolPath->GetPatrolNodes();
	if (PatrolNodes.Num() == 0)
		return EBTNodeResult::Failed;

	if (PatrolNodes.IsValidIndex(WaypointIndex))
		BlackboardComp->SetValueAsObject(
			WaypointKey.SelectedKeyName, PatrolNodes[WaypointIndex]);

	auto NextIndex = (WaypointIndex + 1) % PatrolNodes.Num();
	BlackboardComp->SetValueAsInt(WaypointIndexKey.SelectedKeyName, NextIndex);

	return EBTNodeResult::Succeeded;
}