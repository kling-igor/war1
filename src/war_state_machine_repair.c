WarState* createRepairState(WarContext* context, WarEntity* entity, WarEntityId buildingId)
{
    WarState* state = createState(context, entity, WAR_STATE_REPAIR);
    state->repair.buildingId = buildingId;
    return state;
}

void enterRepairState(WarContext* context, WarEntity* entity, WarState* state)
{
}

void leaveRepairState(WarContext* context, WarEntity* entity, WarState* state)
{
}

void updateRepairState(WarContext* context, WarEntity* entity, WarState* state)
{
    WarUnitComponent* unit = &entity->unit;
    WarUnitStats stats = getUnitStats(unit->type);

    WarEntity* building = findEntity(context, state->repair.buildingId);

    // if the building doesn't exists or is collapsing (it could be attacked by other units), go idle
    if (!building || isCollapsing(building) || isGoingToCollapse(building))
    {
        WarState* idleState = createIdleState(context, entity, true);
        changeNextState(context, entity, idleState, true, true);
        return;
    }

    // if the building is not in range, go to it
    if (!unitInRange(entity, building, stats.range))
    {
        vec2 targetTile = unitPointOnTarget(entity, building);

        WarState* followState = createFollowState(context, entity, building->id, targetTile, stats.range);
        followState->nextState = state;
        changeNextState(context, entity, followState, false, true);
        return;
    }

    // the unit arrive to the building, go repairing
    WarState* repairingState = createRepairingState(context, entity, building->id);
    changeNextState(context, entity, repairingState, true, true);
}

void freeRepairState(WarState* state)
{
}

