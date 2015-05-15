/*
 * ----------------------------------------
 * Native Part
 * ----------------------------------------
 */

native _DestroyActor(actorid) 	= DestroyActor;

#define DestroyActor			__DestroyActor

/*
 * ----------------------------------------
 * Useing the Hook
 * ----------------------------------------
 */

__DestroyActor(actorid)
{
	if(IsValidActor(actorid))
	{
		for(new i; i != _:ActorStruct; i++) Actors[actorid][ActorStruct:i] = 0;
		// Actor->Flags[actorid] = aFlags:0; // Turn all Flags off
	}
	return _DestroyActor(actorid);
}

RespawnActor(actorid, model = -1)
{
	if(IsValidActor(actorid))
	{
		new Float:Pos[4], world;
		GetActorPos(actorid, Pos[0], Pos[1], Pos[2]);
		GetActorFacingAngle(actorid, Pos[3]);
		
		world = GetActorVirtualWorld(actorid);
		
		_DestroyActor(actorid);
		actorid = CreateActor((model == -1) ? (Actor->Model[actorid]) : (model), Pos[0], Pos[1], Pos[2], Pos[3]);
		SetActorVirtualWorld(actorid, world);
		return actorid;
	}
	return INVALID_ACTOR_ID;
}