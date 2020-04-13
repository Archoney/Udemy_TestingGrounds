#include "PatrolPath.h"

UPatrolPath::UPatrolPath()
{
	PrimaryComponentTick.bCanEverTick = false;
}

TArray<AActor*> UPatrolPath::GetPatrolNodes() const
{
	return PatrolNodes;
}
