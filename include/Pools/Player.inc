enum constantvars
{
	uID,
	cName[MAX_PLAYER_NAME],
	Skin,
	Float:Cord[3],
	ActorID,
	CamObj,
	constantflags:cFlags
};

enum constantflags (<<= 1)
{
	Logedin = 1,
	LoginDone
};
new constPlayer[MAX_PLAYERS][constantvars];