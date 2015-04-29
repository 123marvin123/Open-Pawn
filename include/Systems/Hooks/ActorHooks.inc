native _CreateActor(modelid, Float:x, Float:y, Float:z, Float:rotation)		= CreateActor;
native _DestroyActor(actorid) 												= DestroyActor;

#define CreateActor															__CreateActor
#define DestroyActor														__DestroyActor

__CreateActor(modelid, Float:x, Float:y, Float:z, Float:rotation)
{
	new actorid = _CreateActor(modelid, x, y, z, rotation);
	Actor->Flags[actorid] |= Valid;
	return actorid;
}

__DestroyActor(actorid)
{
	for(new i; i != _:ActorStruct; i++) Actors[actorid][ActorStruct:i] = 0;
	Actor->Flags[actorid] = aFlags:0; // Turn all Flags off
	return _DestroyActor(actorid);
}