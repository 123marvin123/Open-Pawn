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

RespawnActor(actorid)
{
	if(IsValidActor(actorid))
	{
		new Float:Pos[4];
		GetActorPos(actorid, Pos[0], Pos[1], Pos[2]);
		GetActorFacingAngle(actorid, Pos[3]);
		_DestroyActor(actorid);
		CreateActor(Actor->Model[actorid], Pos[0], Pos[1], Pos[2], Pos[3]);
		return true;
	}
	return false;
}