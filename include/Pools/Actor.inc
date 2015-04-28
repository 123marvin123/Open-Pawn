enum ActorStruct
{
	Model,
	Float:Health,
	Text3D:Label,
	
	aFlags:Flags
};
enum aFlags (<<= 1)
{
	Valid = 1,
	Moveing
};

new Actors[MAX_ACTORS][ActorStruct];